/*
 *
 *
 *  Created on: Jul 25, 2023
 *      Author: karim
 */

//standard libs
#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

//MCAL
#include "../Drivers/MCAL/DIO/DIO_Interface.h"
#include "../Drivers/MCAL/EXTI/EXTI_Interface.h"
#include "../Drivers/MCAL/EXTI/EXTI_Private.h"



// simple program to test EXTI Driver

// a led will toggle by the isr whenever a switch is pressed connected to INT0


void toggle_led(){

	DIO_void_toggle_pin(PORTA, PIN0);

}

int main(){

	//initialize the EXTI by the Sensing level
	EXTI_sensingLevel(INT0, EXTI_fallin_Edge);

	//Set the dio pins for the button and for the led
	DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT); //led

	DIO_void_pin_pullup(PORTD, PIN2); // button set in int0 pin location in atmega32
	//set callback function
	EXTI_set_callBack_func(INT0, toggle_led);
	//enable int0 interrupt
	EXTI_ISR(INT0, Enable);

	EXTI_global_Int(Enable);




	while(1){

	}

	return 0;
}
