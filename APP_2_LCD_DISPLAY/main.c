/**********************************************************************/
/*                      Created on: Jul 18, 2023                      */
/*                      Created By: Karim Tarek                       */
/*                LCD driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

//standard libs
#include <util/delay.h>
#include "../Libraries/bit_calc.h"
#include "../Libraries/STD_Types.h"

// MCAL lib
#include "../Drivers/MCAL/DIO/DIO_Interface.h"

// HAL lib

#include "LCD_Interface.h"

/*
 *  this is a simple test for the LCD driver
 *  if you want to test more functions
 *  modify the code below to your liking
 *
 *
 */

int main(){

	// initialize the lcd
	// the function set the direction of the required pins
	LCD_init();

	LCD_set_cursor(0, 3);
	LCD_write_string((u8*)"LCD DRIVER");
	LCD_set_cursor(1, 0);
	LCD_write_string((u8*)"VER:");
	LCD_write_float(1.00, 1);
	LCD_write_string((u8*)" BY KARIM");


	while(1){



	}

	return 0;
}

