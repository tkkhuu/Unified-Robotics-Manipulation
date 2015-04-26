/*
 * main.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */

#include <avr/io.h>
#include "main.h"

int main(void) {
	sei();
	//enable global interrupt
	initRBELib(); //initialize RBE Lib to use printf
	debugUSARTInit(9); //initialize the USART at 115200 baud rate
	initADC(2); //initialize the ADC
	initTimer(0, 0, 0); //Initilize timer for ISR
	initSPI(); //Initialize the use of SPI

	const irSensorCalibration SharpIR = { 6787, -3, 4 }; //Constants for linearizing the distance measured from IR sensors
	Link upper_link; //struct Link of the upper link
	Link lower_link; //struct Link of the lower link
	IRSensor irsensor1; //Defining sensor 1 as a struct
	IRSensor irsensor2; //Defining sensor 2 as a struct
	irsensor1.distance = 0; //initialize the irsensor
	irsensor2.distance = 0; //initialize the ir sensor

	signed short distance1 = 0, distance2 = 0; //two variables to store the distance from the IR sensor
	unsigned int i = 0; //loop counter
	signed short distance = 0; //the average of distance1 and distance2

	jointAngles inverse = { 0, 0 }; //A struct of joint angles to store the result of the inverse kinematic
	coordinates distanceSection; //a struct of coordinates to calibrate the distance read

	//-----------------------Initialize Global Variables-----------------------
	timer = 0;
	millisecond = 0;
	IRSensorSampleTime = 0;
	flag = 0;

	upper_link.DACbackwardport = 0; //the port that drive upper motor backward
	upper_link.DACforwardport = 1; // the port that drive upper motor forward
	lower_link.DACforwardport = 2; // the port that drive lower motor forward
	lower_link.DACbackwardport = 3; // the port that drive lower motor backward
	lower_link.pidInput = 0;
	upper_link.pidInput = 0;

	lower_link.error = 0;
	upper_link.error = 0;
	lower_link.previousError = 0;
	upper_link.previousError = 0;
	lower_link.sumError = 0;
	upper_link.sumError = 0;
	const int home_theta1 = 40;
	const int home_theta2 = -60;

	//-----------------------Assembly Line-----------------------
	int detectFlag1 = 0; // detect flags to make sure the sensor only sense the block once
	int detectFlag2 = 0;
	const int droptheta1 = 90, droptheta2 = 80; //joint angles to determine the position at which the block is dropped

	//enum that determine all the state to implement a state machine for the assembly line
	typedef enum {
		Home, Detect, Control, Gripper, MoveBlock, Sensing, Drop
	} _assembly;

	//enum do determine the different state of the block
	typedef enum {
		Unknown, Light, Heavy
	} _block;
	_block block = Unknown;
	_assembly assembly_line = Home;

	while (1) {
		while (flag) {
			flag = 0;
			//***************************************************************************
			// keep updating the link degree
			upper_link.potADCReading = getADC(2);
			lower_link.potADCReading = getADC(3);
			lower_link.linkDegree = map(lower_link.potADCReading, 330, 730, 0,
					90); //map the lower link degree
			upper_link.linkDegree = map(upper_link.potADCReading, 310, 1010,
					-90, 80);
			//****************************Assembly Line State Machine*****************************
			switch (assembly_line) {
			//Home mode: reset all the variables and home the robot before starting a new loop
			case Home:
				printf("Home\r\n");
				setServo(7, 0); //Run the conveyor belt
				controlSystem(lower_link, upper_link, home_theta1, home_theta2,
						4095);//move the arm to the home thetas

				int u = upper_link.linkDegree - (home_theta2);//determine the error of the links
				int l = lower_link.linkDegree - home_theta1;

				setServo(1, 105);//set the sorter to the middle
				if ((u < 3) && (u > -3) && (l < 3) && (l > -3)) {//go to the next state when the errors are less than 3
					i++;//delay to make sure the arm is stable
					if (i == 90) {
						//reset al variables
						detectFlag1 = 0;
						detectFlag2 = 0;
						irsensor1.detectFilter = 1;
						irsensor2.detectFilter = 1;
						irsensor1.distance = 0;
						irsensor2.distance = 0;
						distance1 = 0;
						distance2 = 0;

						//go to next stage
						assembly_line = Detect;
					} else {
						assembly_line = Home;
					}
				} else {

					assembly_line = Home;

				}
				break;


				//Detect mode: detect the block
			case Detect:
				printf("Detect\r\n");
				setServo(0, 0);//Open the gripper
				controlSystem(lower_link, upper_link, home_theta1, home_theta2,
						4095);//home the arm
				irsensor1 = detectObject(irsensor1, SharpIR, 7, 20, 220);//detecting the block on sensor 1

				irsensor2 = detectObject(irsensor2, SharpIR, 5, 20, 220);// detecting the block on sensor 2

				if ((irsensor1.distance != 0) && (detectFlag1 == 0)) {
					detectFlag1 = 1;
					distance1 = irsensor1.distance + 60;//store the value once detected on sensor 1 and add the offset

				}
				if ((irsensor2.distance != 0) && (detectFlag2 == 0)) {
					detectFlag2 = 1;
					distance2 = irsensor2.distance + 60;//store the value once detected on sensor 2 and add the offset

				}

				if ((distance1 != 0) && (distance2 != 0)) {
					distance = (distance1 + distance2) / 2;//average out the 2 values
					distanceSection = linearFit(distance);// calibrate the values
					_delay_ms(2000);//delay before move the arm down
					assembly_line = Control;//go to control state

				} else {
					assembly_line = Detect;
				}
				printf("distance 1: %d, distance 2: %d, distance: %d\r\n",
						distance1, distance2, distance);

				break;
				//Control Mode: move the arm to pick up the block using inverse kinematics
			case Control:
				printf("Control\r\n");

				inverse = inverseKinematics(distanceSection.x,
						distanceSection.y);//apply inverse kinematic to sove for joint angles
				controlSystem(lower_link, upper_link, inverse.thetaOne,
						inverse.thetaTwo, 1000);//move the arm to pick up the block

				u = upper_link.linkDegree - inverse.thetaTwo;
				l = lower_link.linkDegree - inverse.thetaOne;

				if ((u < 3) && (u > -3) && (l < 3) && (l > -3)) {

					assembly_line = Gripper;//go to gripper state
				} else {
					assembly_line = Control;

				}

				break;
			case Gripper:
				printf("Gripper\r\n");

				controlSystem(lower_link, upper_link, inverse.thetaOne,
						inverse.thetaTwo, 4095);// control the arm

				setServo(0, 170);//close the gripper

				assembly_line = MoveBlock;//move to move block state
				i = 0;//reset loop counter
				_delay_ms(500);
				break;

			case MoveBlock:
				printf("MoveBlock\r\n");

				setServo(0, 170);//close gripper
				controlSystem(lower_link, upper_link, 90, -90, 4095);//move to theta1 = 90, theta2 = -90

				u = upper_link.linkDegree - (-90);
				l = lower_link.linkDegree - 90;

				if ((u < 3) && (u > -3) && (l < 3) && (l > -3)) {// wait til arm is stable
					i++;
					if (i == 300) {
						assembly_line = Sensing;//go to sensing
					} else {
						assembly_line = MoveBlock;
					}
					printf("distance 1: %d, distance 2: %d, distance: %d\r\n",
							distance1, distance2, distance);
				} else {
					assembly_line = MoveBlock;

				}

				break;

			case Sensing:

				for (i = 0; i < 1000; i++) {
					controlSystem(lower_link, upper_link, 90, -60, 750);//apply a smalle torque enough to lift the light block
					upper_link.potADCReading = getADC(2);
					upper_link.linkDegree = map(upper_link.potADCReading, 310,
							1010, -90, 80);
					if (upper_link.linkDegree < -85) {//if the arm doesn't move=>heavy block
						block = Heavy;

						printf("Sensing: heavy\r\n");
					} else if (upper_link.linkDegree > -85) {//if the arm move => light block
						block = Light;

						printf("Sensing: light\r\n");
					}
					printf("%ld\r\n", upper_link.linkDegree);
				}
				i = 0;
				assembly_line = Drop;
				break;

			case Drop:
				//set sorter to right position
				if (block == Heavy) {
					setServo(1, 70);
					printf("Heavy\r\n");
				} else {
					setServo(1, 145);
					printf("Light\r\n");
				}
				//control arm to drop angles
				controlSystem(lower_link, upper_link, droptheta1, droptheta2,
						4095);
				u = upper_link.linkDegree - (droptheta2);
				l = lower_link.linkDegree - droptheta1;
				printf("%d, %d\r\n", u, l);
				if ((u < 4) && (u > -4) && (l < 3) && (l > -3)) {
					i++;
					if (i == 300) {

						for (i = 0; i < 500; i++) {
							//open gripper
							setServo(0, 0);
						}
						i = 0;
						assembly_line = Home;
					} else {
						assembly_line = Drop;
					}
					printf("%d\r\n", i);
				} else {
					assembly_line = Drop;

				}

				break;
			}
			//*********************End State Machine************************

		}
		//****************End Sample************************

	}
	//******************End While(1)**************************
	return 0;
}


//***********Timer Interrupt********************
ISR(TIMER0_COMPA_vect) {
	timer++;
	IRSensorSampleTime++;
	if (timer == 9) {
		millisecond++;
	}
	if (IRSensorSampleTime == 90) {
		flag = 1;
		IRSensorSampleTime = 0;
	}
}

