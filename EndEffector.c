/*
 * EndEffector.c
 *
 *  Created on: Feb 21, 2015
 *      Author: Tri
 */
#include <math.h>
#include <RBELib/RBELib.h>
#include "main.h"

const double length0 = 139.7; //mm
const double length1 = 152.4; //mm
const double length2 = 165; //mm
/**
 * @brief Function to determine the forward kinematic of the end effector
 * @param theta1 Joint angle of the lower link
 * @param theta2 Joint angle of the upper link
 * @return The coordinates of the end effector
 */
coordinates forwardKinematics(double theta1, double theta2) {
	//convert theta1 and theta2 to radiant
	double theta1Radiant, theta2Radiant;
	theta1Radiant = (theta1 * M_PI) / 180;
	theta2Radiant = (theta2 * M_PI) / 180;
	coordinates position; // define a struct to be returned
	//calculate the x and y position using forward kinematic equation
	position.x = length1 * cos(theta1Radiant)
			+ length2 * cos(theta1Radiant) * cos(theta2Radiant)
			- length2 * sin(theta1Radiant) * sin(theta2Radiant); // calculate the forward kinematic for x
	position.y = length0 + length1 * sin(theta1Radiant)
			+ length2 * cos(theta1Radiant) * sin(theta2Radiant)
			+ length2 * cos(theta2Radiant) * sin(theta1Radiant); // calculate the forward kinematic for y
	return position; // return it
}

/**
 * @brief Function to determine the inverse kinematic of the arm
 * @param endX The x coordinates of the end effector
 * @param endY The y coordinates of the end effector
 * @return The joint angles of the links
 */
jointAngles inverseKinematics(double endX, double endY) {

	float theta2input1, theta2input2, theta1input1, theta1input2;
	//-------calculating theta2 using inverse kinematic equation--------------------------------------------------------------------------------
	theta2input2 = (pow(endX, 2) + pow(endY, 2) - pow(length1, 2)
			- pow(length2, 2)) / (2 * length1 * length2);
	theta2input1 = sqrt(1 - pow(theta2input2, 2));
	jointAngles inverseJoints;
	float radiantTheta2, degreeTheta2;
	radiantTheta2 = atan2(-
			theta2input1, theta2input2);
	degreeTheta2 = (radiantTheta2 * 180) / M_PI;
	inverseJoints.thetaTwo = degreeTheta2;
	//--------calculating theta1 using inverse kinematic equation--------------------------------------------------------------------------------------------------
	theta1input2 = (endX * (length1 + length2 * cos(radiantTheta2))
			+ (endY) * length2 * sin(radiantTheta2))
			/ (pow(endX, 2) + pow(endY, 2));
	theta1input1 = sqrt(1 - pow(theta1input2, 2));
	float radiantTheta1, degreeTheta1;
	radiantTheta1 = atan2(theta1input1, theta1input2);
	degreeTheta1 = (radiantTheta1 * 180) / M_PI;
	inverseJoints.thetaOne = degreeTheta1;
	return inverseJoints;

}
