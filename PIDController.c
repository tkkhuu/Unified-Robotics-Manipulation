/*
 * PIDController.c
 *
 *  Created on: Feb 22, 2015
 *      Author: Tri
 */

#include "main.h"
#include <RBELib/DAC.h>
#include <RBELib/RBELib.h>
#include <math.h>
/**
 * @brief PID Controller for a link
 * @param Kp Proportional gain
 * @param Kd Derivation gain
 * @param Ki Integral gain
 * @param degreeSetPoint The desired angle
 * @param link Link to control
 * @gravity Gravity compensation
 * @return The control equation
 */
long pidController(double Kp, double Ki, double Kd, long degreeSetPoint,
		Link link, double gravity) {
	long u;
	double derivative;
	link.error = degreeSetPoint - link.linkDegree;
	link.sumError += link.error;
	derivative = link.error - link.previousError;
	link.previousError = link.error;
	u = (Kp * link.error + Ki * (link.sumError) + Kd * derivative) + gravity;
	return u;
}

/**
 * @brief Function to drive the motor
 * @param input PID input
 * @param forwardPort Motor port to drive the motor forward
 * @param backwardPort Motor port to drive the motor backward
 * @param maxval Maximum speed for the motor to drive
 *
 */
void driveMotor(long input, int forwardPort, int backwardPort, int maxval) {
	long forward;
	long backward;

	forward = input;
	backward = 0 - input;

	if (forward > maxval) {
		forward = maxval;
	} else if (forward < -maxval) {
		forward = -maxval;
	}

	if (backward < -maxval) {
		backward = -maxval;
	} else if (backward > maxval) {
		backward = maxval;
	}

	if (input < 0) {
		setDAC(backwardPort, backward);
		setDAC(forwardPort, 0);
	} else {
		setDAC(forwardPort, forward);
		setDAC(backwardPort, 0);
	}

}

/**
 * @brief Function to calculate the PID and drive the motor
 * @param lower The lower link to be passed in
 * @param upper The upper link to be passed in
 * @param lowerSetpoint The desired lower joint angle
 * @param lowerSetpoint The desired upper joint angle
 * @param maxval Max speed for the motor to control
 */
void controlSystem(Link lower, Link upper, long lowerSetpoint,
		long upperSetpoint, int maxval) {
	upper.mass = 0.280;
	lower.mass = 0.485;
	upper.compensationTorque = upper.mass * 9.8 * 0.1524
			* cos(lower.linkDegree + upper.linkDegree); //gravity compensation for the upper link
	lower.compensationTorque = (lower.mass + upper.mass) * 9.8 * 0.1524
			* cos(lower.linkDegree)
			+ upper.mass * 9.8 * 0.1524
					* cos(lower.linkDegree + upper.linkDegree);

	upper.pidInput = pidController(195, 1, 20, upperSetpoint, upper,
			upper.compensationTorque);
	lower.pidInput = pidController(260, 1, 1, lowerSetpoint, lower,
			lower.compensationTorque);
	driveMotor(upper.pidInput, upper.DACforwardport, upper.DACbackwardport,maxval);
	driveMotor(lower.pidInput, lower.DACforwardport, lower.DACbackwardport,maxval);
}


