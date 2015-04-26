/*
 * EndEffector.h
 *
 *  Created on: Feb 21, 2015
 *      Author: Tri
 */

#ifndef ENDEFFECTOR_H_
#define ENDEFFECTOR_H_

typedef struct {
	float x;
	float y;
} coordinates;

typedef struct {
	long thetaOne;
	long thetaTwo;
} jointAngles;

coordinates forwardKinematics(double theta1, double theta2);
jointAngles inverseKinematics(double endX, double endY);

#endif /* ENDEFFECTOR_H_ */
