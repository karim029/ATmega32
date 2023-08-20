/*
 * main.c
 *
 *  Created on: Jul 17, 2023
 *      Author: karim
 *
 *      this is a test app for the DIO driver
 *      you can modify the code or try other functions
 *
 */

#define F_CPU 8000000UL

//standard lib section
#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

// MCAL DRIVERS SECTION
#include "../Drivers/MCAL/DIO/DIO_Interface.h"

/*
 * this code will toggle a led connected to PORT A pin 0 using a button connected to PORT B pin 0
 *
 */

int main(){

		//set desired direction for led --> output and for the button --> input
	 	DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT); //led
	 	DIO_void_pin_pullup(PORTB, PIN0); // button input and activated internal pullup

	 	//set the led to low
	 	DIO_void_clear_pin(PORTA, PIN0);

	while(1){

		/* if condition if the button is pressed (Active high) because of the pullup
		 * if the pin reads 0 then toggle the led using the dio function made for the driver
		 * you can find the proteus simulation of this code using a led and a button
		 * if you want to test it
		 *
		 * feel free to edit this code and implement more creative tests
		 */
			if(DIO_u8_get_pin(PORTB, PIN0) == 0 ){

				DIO_void_toggle_pin(PORTA, PIN0);
				_delay_us(250);
			}

	}
	return 0;
}

