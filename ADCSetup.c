/*
 * ADCSetup.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */


/**
 * @brief Initializes the ADC and make one channel active.
 * You can choose to use either interrupts or polling to read
 * the desired channel.
 *
 * @param channel The ADC channel to initialize.
 *
 * @todo Create the corresponding function to initialize the ADC
 * using the channel parameter.
 */
#include <RBELib/RBELib.h>
#include "RBELib/ADC.h"

void initADC(int channel) {
	// Setting the Timer/Counter Control Register A
	//Setting bit REFS0 to 1 to use Vcc as Vref
	//Or ADMUX with channel to determine the ADC channel to be read from
	ADMUX = (1 << REFS0) | (channel);
	// Set bit ADEN to 1 to enable the ADC, Set ADPS2:0 to 111 to set the prescaler to 128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

/**
 * @brief Run a conversion on and get the analog value from one ADC
 * channel if using polling.
 *
 * @param channel  The ADC channel to run a conversion on.
 * @return adcVal The 8-10 bit value returned by the ADC
 * conversion.  The precision depends on your settings and
 * how much accuracy you desire.
 *
 * @todo Create the corresponding function to obtain the value of the
 * last calculation if you are using polling.
 */
unsigned short getADC(int channel) {
	//Setting bit REFS0 to 1 to use Vcc as Vref
	//Or ADMUX with channel to determine the ADC channel to be read from
	ADMUX = (1 << REFS0) | (channel);
	// ADLAR bit is set to 0 so that the ADC is read from bit 9, producing value from 0-1023
	// Set ADSC to 1 to start the conversion
	ADCSRA |= (1 << ADSC);
	//Polling the status bit
	while (!(ADCSRA & (1 << ADIF)));
	return ADCW; //return the value of the ADC reading after conversion
}
