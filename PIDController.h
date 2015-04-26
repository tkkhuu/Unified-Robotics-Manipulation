/*
 * PIDController.h
 *
 *  Created on: Feb 22, 2015
 *      Author: Tri
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_
typedef struct {
	unsigned short potADCReading;
	signed long linkDegree;
	double error;
	double sumError;
	double previousError;
	long pidInput;
	int DACforwardport;
	int DACbackwardport;
	double compensationTorque;
	float mass;
	unsigned short currentSense;
} Link;
long pidController(double Kp, double Ki, double Kd, long degreeSetPoint, Link link, double gravity);
void driveMotor(long input, int forwardPort, int backwardPort, int maxval);
void controlSystem(Link lower, Link upper, long lowerSetpoint,
		long upperSetpoint, int maxval);


#endif /* PIDCONTROLLER_H_ */
