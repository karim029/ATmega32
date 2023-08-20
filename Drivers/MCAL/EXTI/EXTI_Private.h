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


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_



#define  GIE 7
// null definition
#define null ((void *)0)

// definition of bits used in the registers of the external interrupt

/* MCUCR */
// interrupt sense control bits for INT 1
#define ISC11 3
#define ISC10 2
// interrupt sense control bits for INT 0
#define ISC01 1
#define ISC00 0

/* MCUCSR */
// interrupt sense control bit for INT 2
#define ISC2 6



/* GIFR */
// External Interrupt flag for intx x--> 0,1,2
#define INTF1 7
#define INTF0 6
#define INTF2 5

/* Interrupt Service Routine Declaration */
// INT0 ISR
void __vector_1 (void)__attribute__((signal));
// INT1 ISR
void __vector_2 (void)__attribute__((signal));
// INT2 ISR
void __vector_3 (void)__attribute__((signal));

#endif /* EXTI_PRIVATE_H_ */
