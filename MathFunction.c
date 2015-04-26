/*
 * MathFunction.c
 *
 *  Created on: Feb 21, 2015
 *      Author: Tri
 */
#include <math.h>
#include "EndEffector.h"


float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @brief Divide the conveyor belt into sections
 * @param xdistance The distance read on the conveyor belt
 * @return The coordinates to for the end effector to pick the block up
 */

coordinates linearFit(signed short xdistance) {
	coordinates pos;
	if (xdistance < 215) {
		pos.x = 235;
		pos.y = -27;
	} else if (xdistance < 220) {
		pos.x = 242;
		pos.y = -23;
	} else if (xdistance < 225) {
		pos.x = 245;
		pos.y = -20;
	} else if (xdistance < 230) {
		pos.x = 252;
		pos.y = -20;
	} else if (xdistance < 235) {
		pos.x = 260;
		pos.y = -16+10;
	} else if (xdistance < 240) {
		pos.x = 265;
		pos.y = -12+10;
	} else if (xdistance < 245) {
		pos.x = 265;
		pos.y = -10+10;
	} else if (xdistance < 250) {
		pos.x = 275;
		pos.y = -6;
	} else {
		pos.x = 285;
		pos.y = -10;
	}
	return pos;
}


