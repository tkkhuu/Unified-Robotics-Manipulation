/*
 * TimerSetup.c
 *
 *  Created on: Feb 21, 2015
 *      Author: Tri
 */


#include <RBELib/RBELib.h>


/**
 * @brief Initializes the specified timer in the specified mode. This
 * header file provides constants for NORMAL operation mode and
 * CTC operation mode, however there are many more modes of operation
 * for the Timers that can be experimented with.
 *
 * @todo Create a function that initializes the desired timer
 */

void initTimer(int timer, int mode, unsigned int comp) {
	TCCR0A = (1 << WGM01); //Set WGM01 = 1 to operate the timer at CTC Mode
	OCR0A = 255;			//Set the compare value for the timer to reset, in this case the top value
	TIMSK0 = (1 << OCIE0A); //Enable the compare interrupt vector, used for CTC Mode
	TCCR0B = (1 << CS01);//Setting the prescaler to 8
}
