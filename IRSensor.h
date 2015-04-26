/*
 * IRSensor.h
 *
 *  Created on: Feb 21, 2015
 *      Author: Tri
 */

#ifndef IRSENSOR_H_
#define IRSENSOR_H_

typedef const struct {
	float a;
	float b;
	float k;
} irSensorCalibration;

typedef struct {
	int detectFilter;
	int calibration;
	unsigned short valueInMili;
	unsigned short previousValue;
	unsigned short distance;
}IRSensor;

float CalculateIRSensor(irSensorCalibration sensor, unsigned short adc_value);
IRSensor detectObject(IRSensor sensor, irSensorCalibration SharpIR, int ADCchannel, int setPoint, int calibration);
#endif /* IRSENSOR_H_ */
