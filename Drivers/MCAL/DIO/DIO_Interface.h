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



#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/* Define Ports and pins */

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define B0 0
#define B1 1
#define B2 2
#define B3 3
#define B4 4
#define B5 5
#define B6 6
#define B7 7

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

#define PORT_MAX 0xFF

/* Declaring DIO Driver Functions  */

/*
 *  THE FUNCTIONS WILL BE SPLIT INTO 3 PARTS SORTED BY WHAT IT DOES
 */

/*
 * 1) PIN/PORT DIRECTION FUNCTIONS
 */

void DIO_void_set_port_dir(u8 copy_u8_portID, u8 port_copy_dir);
void DIO_void_port_pullup(u8 copy_u8_portID);

void DIO_void_set_pin_dir(u8 copy_u8_portID, u8 copy_u8_pinID, u8 pin_copy_dir);
void DIO_void_pin_pullup(u8 copy_u8_portID, u8 copy_u8_pinID);

/*
 * 2) PIN/PORT OUTPUT VALUE FUNCTIONS
 */

void DIO_void_set_port(u8 copy_u8_portID);
void DIO_void_clear_port(u8 copy_u8_portID);
void DIO_void_assign_port(u8 copy_u8_portID, u8 copy_value);
void DIO_void_toggle_port(u8 copy_u8_portID);

void DIO_void_set_pin(u8 copy_u8_portID , u8 copy_u8_pinID);
void DIO_void_clear_pin(u8 copy_u8_portID , u8 copy_u8_pinID);
void DIO_void_assign_pin(u8 copy_u8_portID,u8 copy_u8_pinID ,u8 copy_value);
void DIO_void_toggle_pin(u8 copy_u8_portID , u8 copy_u8_pinID);

/*
 * 3) PIN/PORT READ INPUT VALUE
 */
u8 DIO_u8_get_port(u8 copy_u8_portID);
u8 DIO_u8_get_pin(u8 copy_u8_portID, u8 copy_u8_pinID);

#endif /* DIO_INTERFACE_H_ */
