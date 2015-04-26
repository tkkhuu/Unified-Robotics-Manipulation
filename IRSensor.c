/*
 * IRSensor.c
 *
 *  Created on: Feb 21, 2015
 *      Author: Tri
 */

#include "main.h"
/**
 * @brief Function to calibrate and output the sensor in mm
 * @param sensor Set of constants used to linearize
 * @param adc_value The ADC value read
 * @return Return the distance in mm
 */
float CalculateIRSensor(irSensorCalibration sensor, unsigned short adc_value) {
	if (adc_value + sensor.b <= 0) {
		return -1;
	} else {
		return 10 * (sensor.a / (adc_value + sensor.b) - sensor.k);
	}
}
//***********************************************************************************************************
/**
 * @brief Function to detect the objects
 * @param sensor Sensor used to detect
 * @param SharpIR Calibrate constant for the IR Sensor
 * @param ADCchannel The channel to read the IR Sensor from
 * @param setPoint The highest point for the counter to reach
 * @return Return the updated Sensor
 */
IRSensor detectObject(IRSensor sensor, irSensorCalibration SharpIR,
		int ADCchannel, int setPoint, int calibration) {
	sensor.calibration = calibration;//the furthest that the sensor will read

	sensor.valueInMili = CalculateIRSensor(SharpIR, getADC(ADCchannel));//read the distance in milisecond
	unsigned short distance = 0;
	if (sensor.valueInMili < sensor.calibration) {//if the sensor read something less than the furthest range
		sensor.detectFilter++;//increase the counter to make sure it's not noise
		if(sensor.detectFilter > setPoint){//when counter reach the highest point
			distance = sensor.valueInMili;//record the stable value
		}
	} else {
		sensor.detectFilter--;//decrease the counter if the reading is not stable
		if (sensor.detectFilter < 0) {
			sensor.detectFilter = 1;
			distance = 0;
		}
	}


	sensor.distance = distance;

	return sensor;
}
