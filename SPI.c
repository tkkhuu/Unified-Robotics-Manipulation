/*
 * SPI.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */


#include "RBELib/RBELib.h"
#include "RBELib/SPI.h"
#include "RBELib/SlaveSelects.h"
#include "ACC.h"
//#include "RBELib/DAC.h"

/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */

void initSPI() {
	// Initialize SPRC: SPI Control Register

	SPI_MISO_DDR = INPUT; //initialize miso
	SPI_MOSI_DDR = OUTPUT; //initialize mosi
	SPI_SCK_DDR = OUTPUT; //set clk as output
	SPI_MASTER_SS = HIGH; //make the chip master

	DAC_SS_ddr = OUTPUT; //set CS for DAC as output
	ENCODER_SS_1_ddr = OUTPUT;
	ENCODER_SS_0_ddr = OUTPUT;
	ACC_SS_ddr = OUTPUT;

	//deselect all other SPI device
	ACC_SS = HIGH;
	ENCODER_SS_0 = HIGH;
	DAC_SS = HIGH;
	ENCODER_SS_1 = HIGH;
	ENCODER_SS_2 = HIGH;
	ENCODER_SS_3 = HIGH;
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPR1); //enable spi, make it master, set prescale for clock by 16

}
/**
 * @brief Send and receive a byte out of the MOSI line.
 *
 * Please note that even if you do not want to receive any data back
 * from a SPI device, the SPI standard requires you still receive something
 * back even if it is junk data.
 *
 * @param data The byte to send down the SPI bus.
 * @return value The byte shifted in during transmit
 *
 * @todo Make a function that will send a byte of data through the SPI
 * and return whatever was sent back.
 */
unsigned char spiTransceive(BYTE data) {
	//SPI_MISO = data;
	SPDR = data;
	/* Wait for reception complete */
	while (!(SPSR & (1 << SPIF)))
		; //poll status bit
	return SPDR;
}
