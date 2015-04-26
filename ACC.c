/*
 * ACC.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */


#include "RBELib/RBELib.h"
#include <avr/io.h>
#include "ACC.h"
/**
 * @brief Find the acceleration in the given axis (X, Y, Z).
 * @param  axis The axis that you want to get the measurement of.
 * @return gVal Value of  acceleration.
 *
 * @todo Create a function that is able to find the acceleration of a given axis.
 */
signed int getAccel(int axis){
	unsigned char inputAxis = (axis<<6);
	unsigned char a,b,c;
	signed int result;

	ACC_SS = LOW;
	a = spiTransceive(0b00000110);//send the first package: start bit and single ended mode
	b = spiTransceive(inputAxis);//send the second package that ask for the axis desired
	b &= 0x0F;//preventing garbage data, keep the last 4 bits
	result = (b <<8);//bit shift to read the result correctly
	c = spiTransceive(0x00);//send the last package, don't care bit, receive the last 8 bits on the MISO

	ACC_SS = HIGH;//deselect chip select
	result |= (c);//update result
	return result;

}
