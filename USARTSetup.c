/*
 * USARTSetup.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */
#include <RBELib/RBELib.h>


/**
 * @brief Initializes USART1 as a print terminal to the PC. This function
 * must check the incoming baudrate against the valid baudrates
 * from the data-sheet. If the baudrate is invalid, then the
 * DEFAULT_BAUD constant must be used instead.
 *
 * @param baudrate The desired baudrate to set for USART1.
 *
 * @todo Create the function that will initialize USART1 for debugging use.
 */
void debugUSARTInit(unsigned long baudrate) {
	UBRR1H = (unsigned char) (baudrate >> 8);
	UBRR1L = (unsigned char) baudrate;
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << USBS1) | (3 << UCSZ10);
}

/**
 * @brief Sends one byte to the USART1 Tx pin (Transmits one byte).
 *
 * @param byteToSend The byte that is to be transmitted through USART1.
 *
 * @todo Make the function that will put a character on the USART1 TX line.
 */
void putCharDebug(char byteToSend){
	while (!(UCSR1A & (1<<UDRE1)));
	UDR1 = byteToSend;
}

/**
 * @brief Receives one byte of data from the serial port (i.e. from the PC).
 *
 * @return byteReceived Character that was received on the USART.
 *
 * @todo Make the function that will listen for input on the USART1 RX line.
 */
unsigned char getCharDebug(void){
	while (!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

