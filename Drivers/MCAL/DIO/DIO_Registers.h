/**********************************************************************/
/*                      Created on: Jul 16, 2023                      */
/*                      Created By: Karim Tarek                       */
/*        Digital i/o driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

/*
 * these are the addresses for the atmega32 mcu i recommend not editing anything in this file!
 *
 *
 */

#ifndef DIO_REGISTERS_H_
#define DIO_REGISTERS_H_


/* Define PortA register */

#define DIO_PINA  ((volatile u8*)0x39)
#define DIO_DDRA  ((volatile u8*)0x3A)
#define DIO_PORTA ((volatile u8*)0x3B)

/* Define PortB register */

#define DIO_PINB  ((volatile u8*)0x36)
#define DIO_DDRB  ((volatile u8*)0x37)
#define DIO_PORTB ((volatile u8*)0x38)

/* Define PortC register */

#define DIO_PINC  ((volatile u8*)0x33)
#define DIO_DDRC  ((volatile u8*)0x34)
#define DIO_PORTC ((volatile u8*)0x35)

/* Define PortD register */

#define DIO_PIND  ((volatile u8*)0x30)
#define DIO_DDRD  ((volatile u8*)0x31)
#define DIO_PORTD ((volatile u8*)0x32)

#endif /* DIO_REGISTERS_H_ */
