/*
 * MathFunction.h
 *
 *  Created on: Feb 21, 2015
 *      Author: Tri
 */

#ifndef MATHFUNCTION_H_
#define MATHFUNCTION_H_
#include "EndEffector.h"
float map(float x, float in_min, float in_max, float out_min, float out_max);
coordinates linearFit(signed short xdistance);
#endif /* MATHFUNCTION_H_ */
