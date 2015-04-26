/*
 * Encoder.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */


#include "RBELib/RBELib.h"
#include "RBELib/SPI.h"
#include "RBELib/SlaveSelects.h"
#include "main.h"
/**
 * @brief Initialize the encoders with the desired settings.
 * @param chan Channel to initialize.
 * @todo Make a function that can setup both encoder chips on the board.
 */
void encInit(int chan) {
	if (chan == 1) {// set up encoder 1
		ENCODER_SS_1 = LOW;// select encoder 1
		char IR;
		char MDR0register;
		char MDR1register;
		IR = (1 << WR) | (1 << MDR0);//set up the command package: writing to MDR0
		MDR0register = 0b00000000;//Using the default setting
		spiTransceive(IR);//send the command package
		spiTransceive(MDR0register);//send the package that set up MDR0
		ENCODER_SS_1 = HIGH;//deselect encoder 1


		ENCODER_SS_1 = LOW;// select encoder 1 to set up MDR1
		IR = (1 << WR) | (1 << MDR1);//set up the command package: writing to MDR1
		MDR1register = 0b00000000;//Using the default setting
		spiTransceive(IR);//send the command package
		spiTransceive(MDR1register);//send the package that set up MDR1
		ENCODER_SS_1 = HIGH;//deselect encoder 1
		//set up the same for encoder 0
	} else {
		ENCODER_SS_0 = LOW;
		char IR;
		char MDR0register;
		char MDR1register;
		IR = (1 << WR) | (1 << MDR0);
		MDR0register = 0b00000000;
		spiTransceive(IR);
		spiTransceive(MDR0register);
		ENCODER_SS_0 = HIGH;
//
//
		ENCODER_SS_0 = LOW;
		IR = (1 << WR) | (1 << MDR1);
		MDR1register = 0b00000000;
		spiTransceive(IR);
		spiTransceive(MDR1register);
		ENCODER_SS_0 = HIGH;
	}
}
/**
 * @brief Finds the current count of one of the encoders.
 * @param  chan Channel that the encoder is on that you would like to read.
 * @return count The current count of the encoder.
 *
 * @todo Find the current encoder ticks on a given channel.
 */
signed long encCount(int chan) {
	if (chan == 1) {
		unsigned char IR;

		signed long a, b, c, d, e;

		ENCODER_SS_1 = LOW;

		IR = 0b01100000;//set up command package: read counter
		a = spiTransceive(IR);//send the command package
		//send 4 package of don't care bits
		b = spiTransceive(0x00);
		c = spiTransceive(0x00);
		d = spiTransceive(0x00);
		e = spiTransceive(0x00);
		// data are read on the MISO line
		ENCODER_SS_1 = HIGH;

		return (b << 24) | (c << 16) | (d << 8) | (e);
	}
	//Same for encoder 0
	else {
		unsigned char IR;

		signed long a, b, c, d, e;

		ENCODER_SS_0 = LOW;

		IR = 0b01100000;
		a = spiTransceive(IR);

		b = spiTransceive(0x00);
		c = spiTransceive(0x00);
		d = spiTransceive(0x00);
		e = spiTransceive(0x00);

		ENCODER_SS_0 = HIGH;

		return (b << 24) | (c << 16) | (d << 8) | (e);
	}
}

/**
 * @brief Reset the current count of the encoder ticks.
 * @param chan The channel to clear.
 *
 * @todo Clear the encoder count (set to 0).
 */
void resetEncCount(int chan) {
	unsigned char IR;
	unsigned char a;
	if (chan == 1) {
		ENCODER_SS_1 = LOW;
	}
	else if(chan == 0){
		ENCODER_SS_0 = LOW;
	}
		IR = 0b00100000;//set up command package: clear counter

		a = spiTransceive(IR);//send command package

		ENCODER_SS_1 = HIGH;
	    ENCODER_SS_0 =HIGH;
}
