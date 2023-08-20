/*
 * SPI_Private.h
 *
 *  Created on: Aug 3, 2023
 *      Author: karim
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


#define SPCR *((volatile u8*)0x2D)
#define SPSR *((volatile u8*)0x3E)
#define SPDR *((volatile u8*)0X2F)
#define SREG *((volatile u8*)0x5F)

void __vector_12(void)__attribute__((signal));


#endif /* SPI_PRIVATE_H_ */
