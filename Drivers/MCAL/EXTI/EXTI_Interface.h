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


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define Enable 1
#define Disable 0

#define bit0 0
#define bit1 1
/* GICR */
// External interrupt request enable (sreg global interrupt should be enabled)
#define INT1 7
#define INT0 6
#define INT2 5

/* Sensing levels  */
/*
 *  int 0 and int 1 has 4 sensing levels
 *  int 2 only got 2 rising edge or falling edge (1 bit) in MCUCSR
 *
 *
 */

#define EXTI_low_Level 0b00
// interrupt on level change
#define EXTI_IOC 0b01
// falling edge
#define EXTI_fallin_Edge 0b10
//rising edge
#define EXTI_rising_Edge 0b11

// Sensing levels for INT2

#define EXTI_INT2_rising_Edge 1

#define EXTI_INT2_fallin_Edge 0


/* Functions declaration */
void EXTI_set_callBack_func(u8 copy_u8_id , void (*ptr_callBack)(void));
void EXTI_global_Int(u8 copy_En_Dis);
void EXTI_ISR(u8 copy_u8_id,u8 copy_En_Dis);
void EXTI_sensingLevel(u8 copy_u8_id, u8 copy_u8_sensingLevel);
u8 EXTI_read_INT_Flag(u8 copy_u8_id);

#endif /* EXTI_INTERFACE_H_ */
