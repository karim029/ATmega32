/*
 * SPI_Config.h
 *
 *  Created on: Aug 3, 2023
 *      Author: karim
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define Enable 1
#define Disable 0

#define SPI_Interrupt Enable

//data order
#define LSB 0
#define MSB 1
//choose the data order by selected LSB OR MSB
#define Data_Order MSB

#define Rising 0
#define Falling 1
#define Leading_Edge_Pol Rising

#define sample 0
#define setup 1
#define Leading_Edge_Phase sample

#define freq_2 0
#define freq_4 1
#define freq_8 2
#define freq_16 3
#define freq_32 4
#define freq_64_double_Speed 5
#define freq_64 6
#define freq_128 7

#define SCK_FREQ freq_16

#define double_Speed Disable

#endif /* SPI_CONFIG_H_ */
