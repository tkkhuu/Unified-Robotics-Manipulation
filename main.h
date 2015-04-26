/*
 * main.h
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */

#ifndef MAIN_H_
#define MAIN_H_

//----------------------------------Encoder Register----------------------------------
#define WR 7
#define RD 6
#define CNTR 5
#define MDR0 3
#define MDR1 4
#define ONE_COUNT 0
#define FREE_RUNNING
#define RESET_COUNTER 5
#define SYNCHRONOUS 6
#define THREE_BYTE_COUNTER 0
#define BW 6
#define CY 7
//************************************************************************************
//----------------------------------Struct Definitions----------------------------------
#include <RBELib/RBELib.h>
#include "RBELib/timer.h"
#include "IRSensor.h"
#include "EndEffector.h"
#include "MathFunction.h"
#include "PIDController.h"
#include <math.h>

volatile unsigned long timer;
volatile unsigned long millisecond;
volatile unsigned long IRSensorSampleTime;
volatile unsigned char flag;
//************************************************************************************


#endif /* MAIN_H_ */
