///*
// * main.c
// *
// *  Created on: Feb 18, 2015
// *      Author: Tri
// */
//
//#include <avr/io.h>
//#include "main.h"
//void closeGripper();
//void openGripper();
//int main(void) {
//	sei();
//	//enable global interrupt
//	initRBELib(); //initialize RBE Lib to use printf
//	debugUSARTInit(9); //initialize the USART at 115200 baud rate
//	initADC(2); //initialize the ADC
//	initTimer(0, 0, 0);
//	initSPI();
//	const irSensorCalibration SharpIR = { 6787, -3, 4 };
//	Link upper_link;
//	Link lower_link;
//	IRSensor irsensor1;
//	IRSensor irsensor2;
//	signed short distance1 = 0, distance2 = 0;
//	long i;
//	signed short distance = 0;
//
//	jointAngles inverse = { 0, 0 };
//	coordinates distanceSection;
//
//	//-----------------------Initialize Global Variables-----------------------
//	timer = 0;
//	millisecond = 0;
//	IRSensorSampleTime = 0;
//	flag = 0;
//
//	upper_link.DACbackwardport = 0; //the port that drive upper motor backward
//	upper_link.DACforwardport = 1; // the port that drive upper motor forward
//	lower_link.DACforwardport = 2; // the port that drive lower motor forward
//	lower_link.DACbackwardport = 3; // the port that drive lower motor backward
//	lower_link.pidInput = 0;
//	upper_link.pidInput = 0;
//
//	lower_link.error = 0;
//	upper_link.error = 0;
//	lower_link.previousError = 0;
//	upper_link.previousError = 0;
//	lower_link.sumError = 0;
//	upper_link.sumError = 0;
//	int home_theta1 = 40;
//	int home_theta2 = -60;
//
//	//-----------------------Assembly Line-----------------------
//	int detectFlag1 = 0;
//	int detectFlag2 = 0;
//	int droptheta1, droptheta2;
//	typedef enum {
//		Home, Detect, Control, Gripper, MoveBlock, Sensing, Drop
//	} _assembly;
//
//	typedef enum {
//		Unknown, Light, Heavy
//	} _block;
//	_block block = Unknown;
//	_assembly assembly_line = Home;
//
//	i = 0;
////	while (1) {
////		upper_link.potADCReading = getADC(2);
////		lower_link.potADCReading = getADC(3);
////		lower_link.linkDegree = map(lower_link.potADCReading, 330, 730, 0, 90); //map the lower link degree
////		upper_link.linkDegree = map(upper_link.potADCReading, 310, 1010, -90,
////				80);
////		inverse = inverseKinematics(245, -20);
////		controlSystem(lower_link, upper_link, inverse.thetaOne,
////				inverse.thetaTwo, 4095);
////	}
//	while (1) {
//
//		upper_link.potADCReading = getADC(2);
//		lower_link.potADCReading = getADC(3);
//		lower_link.linkDegree = map(lower_link.potADCReading, 330, 730, 0, 90); //map the lower link degree
//		upper_link.linkDegree = map(upper_link.potADCReading, 310, 1010, -90,
//				80);
//
//		//map the upper link degree
//
//		while (flag) {
//			flag = 0;
//
//			switch (assembly_line) {
//			//Reset mode: reset all the variables before starting a new loop
//			case Home:
//				setServo(7, 0);
//				//printf("Home\r\n");
//				controlSystem(lower_link, upper_link, home_theta1, home_theta2,
//						4095);
//				int u = upper_link.linkDegree - (home_theta2);
//				int l = lower_link.linkDegree - home_theta1;
//				printf("upper %d, lower %d\r\n", u, l);
//				setServo(1,105);
//				if ((u < 3) && (u > -3) && (l < 3) && (l > -3)) {
//					i++;
//					if (i == 90) {
//						detectFlag1 = 0;
//						detectFlag2 = 0;
//						irsensor1.detectFilter = 1;
//						irsensor2.detectFilter = 1;
//						irsensor1.distance = 0;
//						irsensor2.distance = 0;
//						distance1 = 0;
//						distance2 = 0;
//						assembly_line = Detect;
//					} else {
//						assembly_line = Home;
//					}
//					printf("%ld\r\n", i);
//				} else {
//
//					assembly_line = Home;
//
//				}
//				break;
//				//Detect mode: detect the block
//			case Detect:
//				printf("Detect: ");
//				setServo(0, 0);
//				controlSystem(lower_link, upper_link, home_theta1, home_theta2,
//						4095);
//				irsensor1 = detectObject(irsensor1, SharpIR, 7, 20, 220);
//
//				irsensor2 = detectObject(irsensor2, SharpIR, 5, 20, 220);
//
//				if ((irsensor1.distance != 0) && (detectFlag1 == 0)) {
//					detectFlag1 = 1;
//					distance1 = irsensor1.distance + 60;
//
//				}
//				if ((irsensor2.distance != 0) && (detectFlag2 == 0)) {
//					detectFlag2 = 1;
//					distance2 = irsensor2.distance + 60;
//
//				}
//
//				if ((distance1 != 0) && (distance2 != 0)) {
//					distance = (distance1 + distance2) / 2;
//					distanceSection = linearFit(distance);
//					_delay_ms(2000);
//					assembly_line = Control;
//
//				} else {
//					assembly_line = Detect;
//				}
//				printf("distance 1: %d, distance 2: %d, distance: %d\r\n",
//						distance1, distance2, distance);
////				printf("filter: %d, %d\r\n", irsensor1.detectFilter, irsensor2.detectFilter);
//
//				break;
//				//Control Mode: move the arm to pick up the block using inverse kinematics
//			case Control:
//				printf("Control\r\n");
//				inverse = inverseKinematics(distanceSection.x,
//						distanceSection.y);
//				controlSystem(lower_link, upper_link, inverse.thetaOne,
//						inverse.thetaTwo, 4095);
////				printf(
////						"set theta1 %ld, set theta2 %ld,distance 1: %d, distance 2: %d, distance: %d\r\n",
////						inverse.thetaOne, inverse.thetaTwo, distance1,
////						distance2, distance);
//
//				u = upper_link.linkDegree - inverse.thetaTwo;
//				l = lower_link.linkDegree - inverse.thetaOne;
//
//				if ((u < 3) && (u > -3) && (l < 3) && (l > -3)) {
////					_delay_ms(500);
//					assembly_line = Gripper;
//				} else {
//					assembly_line = Control;
//
//				}
//
//				break;
//			case Gripper:
//				printf("Gripper");
//
//				controlSystem(lower_link, upper_link, inverse.thetaOne,
//						inverse.thetaTwo, 4095);
//
//				setServo(0, 170);
//				printf("Gripper\r\n");
//
//				assembly_line = MoveBlock;
//				i = 0;
//				_delay_ms(500);
//				break;
//
//			case MoveBlock:
//				printf("MoveBlock\r\n");
//				setServo(0, 170);
//				controlSystem(lower_link, upper_link, 90, -90, 4095);
//
//				u = upper_link.linkDegree - (-90);
//				l = lower_link.linkDegree - 90;
//
//				if ((u < 3) && (u > -3) && (l < 3) && (l > -3)) {
//					i++;
//					if (i == 300) {
//						assembly_line = Sensing;
//					} else {
//						assembly_line = MoveBlock;
//					}
//					printf("%ld\r\n", i);
//				} else {
//					assembly_line = MoveBlock;
//
//				}
//
//				break;
//
//			case Sensing:
//
//				for (i = 0; i < 1000; i++) {
//					controlSystem(lower_link, upper_link, 90, -60, 750);
//					upper_link.potADCReading = getADC(2);
//					upper_link.linkDegree = map(upper_link.potADCReading, 310,
//							1010, -90, 80);
//					if (upper_link.linkDegree < -85) {
//						block = Heavy;
//
//						printf("Sensing: heavy\r\n");
//					} else if (upper_link.linkDegree > -85) {
//						block = Light;
//
//						printf("Sensing: light\r\n");
//					}
//					printf("%ld\r\n", upper_link.linkDegree);
//				}
//				i = 0;
//				assembly_line = Drop;
//				break;
//
//			case Drop:
//				droptheta1 = 90;
//				droptheta2 = 80;
//				if (block == Heavy) {
//					setServo(1, 70);
//					printf("Heavy\r\n");
//				} else {
//					setServo(1, 145);
//					printf("Light\r\n");
//				}
//				controlSystem(lower_link, upper_link, droptheta1, droptheta2,
//						4095);
//				u = upper_link.linkDegree - (droptheta2);
//				l = lower_link.linkDegree - droptheta1;
//				printf("%d, %d\r\n", u, l);
//				if ((u < 4) && (u > -4) && (l < 3) && (l > -3)) {
//					i++;
//					if (i == 300) {
//
//						for (i = 0; i < 500; i++) {
//							setServo(0, 0);
//						}
//						i = 0;
//						assembly_line = Home;
//					} else {
//						assembly_line = Drop;
//					}
//					printf("%ld\r\n", i);
//				} else {
//					assembly_line = Drop;
//
//				}
//
//				break;
//			}
//
//		}
//
//	}
//	return 0;
//}
//
//ISR(TIMER0_COMPA_vect) {
//	timer++;
//	IRSensorSampleTime++;
//	if (timer == 9) {
//		millisecond++;
//	}
//	if (IRSensorSampleTime == 90) {
//		flag = 1;
//		IRSensorSampleTime = 0;
//	}
//}
//void closeGripper() {
//	setServo(7, 0);
//}
//void openGripper() {
//	setServo(7, 180);
//}
