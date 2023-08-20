/**********************************************************************/
/*                      Created on: Jul 25, 2023                      */
/*                      Created By: Karim Tarek                       */
/*        External Interrupt driver for Atmega32  Version 1.0         */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/



#ifndef EXTI_REGISTERS_H_
#define EXTI_REGISTERS_H_

/* Registers Addresses */


/* MCU Control Register – MCUCR */
#define MCUCR *((volatile u8*)0x55)

/* MCU Control and Status Register – MCUCSR */
#define MCUCSR *((volatile u8*)0x54)

/* General Interrupt Control Register – GICR */
#define GICR *((volatile u8*)0x5B)

/* General Interrupt Flag Register – GIFR */
#define GIFR *((volatile u8*)0x5A)

/* Gloval Status Register - SREG */
#define SREG *((volatile u8*)0x5F)

#endif /* EXTI_REGISTERS_H_ */
