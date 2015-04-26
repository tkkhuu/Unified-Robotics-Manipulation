/*
 * DAC.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */

#include "RBELib/RBELib.h"
#include "RBELib/SPI.h"
#include "RBELib/SlaveSelects.h"
/**
 * @brief Set the DAC to the given value on the chosen channel.
 * @param  DACn The channel that you want to set.
 * @param SPIVal The value you want to set it to.
 * @todo Make the function that is able to set the DAC to a given value
 * from 0 - 4095.
 */

void setDAC(int DACn, int SPIVal) {
	DAC_SS = LOW; //activate chip select
	unsigned char packageOne, packageTwo, packageThree; //define three package to send
	packageOne = (0x03 << 4) | DACn; //send the command code
	packageTwo = ((int) SPIVal >> 4); //send the first 12 bit of the data
	packageThree = (char) SPIVal << 4; //send the last 4 bit of the data
	spiTransceive(packageOne); //send the first package
	spiTransceive(packageTwo); //send the second package
	spiTransceive(packageThree); // send the third package
	DAC_SS = HIGH; //de select the chip select
}
