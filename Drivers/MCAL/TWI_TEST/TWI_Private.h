/*
 * TWI_Private.h
 *
 *  Created on: Aug 7, 2023
 *      Author: karim
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_


#define TWAR *((volatile u8*)0x22)
#define TWBR *((volatile u8*)0x20)
#define TWCR *((volatile u8*)0x56)
#define TWDR *((volatile u8*)0x23)
#define TWSR *((volatile u8*)0x21)
#define SREG *((volatile u8*)0x5F)

//TWCR
//bit7 TWI interrupt flag
#define TWINT 7
//Bit 6 TWEA TWI Enable Acknowledge Bit
#define TWEA 6
//Bit 5 TWSTA TWI START Condition Bit
#define TWSTA 5
//Bit 4 TWSTO: TWI STOP Condition Bit
#define TWSTO 4
//Bit 3 TWWC: TWI Write Collision Flag
#define TWWC 3
//Bit 2 TWEN: TWI Enable Bit
#define TWEN 2
//Bit 0 TWIE: TWI Interrupt Enable
#define TWIE 0

//TWSR
//prescaler bits
#define TWPS1 1
#define TWPS0 0


//TWAR
//global call bit
#define TWGCE 0

void __vector_19(void)__attribute__((signal));



#endif /* TWI_PRIVATE_H_ */
