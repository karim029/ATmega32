/**********************************************************************/
/*                      Created on: Jul 21, 2023                      */
/*                      Created By: Karim Tarek                       */
/*        	   KEYPAD driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

#include "../../MCAL/DIO/DIO_Interface.h"


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_
// this setting is for the default size of the keypad 4x4
#define col_Number 4
#define row_Number 4
#define KPD_size (col_Number * row_Number)

// choosing the desired ports and pins

#define col_Port PORTC
#define row_Port PORTD
/* Column pins */
#define col_0 PIN0
#define col_1 PIN1
#define col_2 PIN2
#define col_3 PIN3
/* Row pins */
#define row_0 PIN0
#define row_1 PIN1
#define row_2 PIN2
#define row_3 PIN3



#endif /* KEYPAD_CONFIG_H_ */
