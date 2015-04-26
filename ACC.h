/*
 * ACC.h
 *
 *  Created on: Feb 18, 2015
 *      Author: Tri
 */

#ifndef ACC_H_
#define ACC_H_

#define ACC_SS_ddr DDRDbits._P7
#define ACC_SS PORTDbits._P7
/**
 * @brief Counts the encoder count
 * @param __chan The channel to output the number of counts
 * @return The number of counts for the channel, return -1 if invalid channel is requested
 *
 * @todo Outputs the number of encoder pulses received since the last sample time
 */
int EncoderCounts(int __chan);


/**
 * @brief Get the acceleration
 * @param __axis Selected axis to be read
 * @return The acceleration from read
 *
 * @todo Read 12-bit data from the H48C accelerometer module
 */
int GetAccelerationH48C(int __axis);

#endif /* ACC_H_ */
