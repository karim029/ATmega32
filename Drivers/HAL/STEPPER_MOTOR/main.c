/**********************************************************************/
/*                      Created on: Jul 19, 2023                      */
/*                      Created By: Karim Tarek                       */
/*           Stepper Motor driver for Atmega32  Version 1.0           */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

// Standard libs
#include <util/delay.h>
#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"

// MCAL lib
#include "../../MCAL/DIO/DIO_Interface.h"

// Private libs
#include "STEPPER_Interface.h"



int main(){

	stepper_Init();

	//assign PIN0-1-2 as input will be used for the button
	//button 0 --> rotate cw
	//button 1 --> rotate ccw
	//button 3 --> stops motor

enum stepper_State{

		stepper_CW = 0,
		stepper_CCW = 1,
		Stepper_Stop = 2


	};

enum stepper_State state = Stepper_Stop;

	for(u8 i = 0; i<3;i++){
	DIO_void_pin_pullup(PORTA, i);
	}


	// leds for indicating the cases
	for(u8 i = 0; i<3;i++){
	DIO_void_set_pin_dir(PORTB, i, OUTPUT);
	}
	//led 0 (green) rotation cw
	//led 1 (blue)  rotation ccw
	//led 2 (red)   motor stopped

	while(1){





		if((DIO_u8_get_pin(PORTA, PIN0) == 0))
		{

			state = stepper_CW;

		}

		else if((DIO_u8_get_pin(PORTA, PIN1)==0))
		{

			state = stepper_CCW;

		}

		else if((DIO_u8_get_pin(PORTA, PIN2))==0)
		{

			state = Stepper_Stop;

		}



		switch(state){

		case stepper_CW:
			//turn on indicating led
			DIO_void_set_pin(PORTB, PIN0);
						//turn off the rest of the leds
			DIO_void_clear_pin(PORTB, PIN1);
			DIO_void_clear_pin(PORTB,PIN2);
			//rotate motor cw
			stepper_Rotation_CW(0);
			break;
		case stepper_CCW:
			//turn on indicating led
			DIO_void_set_pin(PORTB, PIN1);
			//turn off the rest of the leds
			DIO_void_clear_pin(PORTB, PIN0);
			DIO_void_clear_pin(PORTB,PIN2);
			//rotate motor ccw
			stepper_Rotation_CCW(0);
			break;
		case Stepper_Stop:

			//turn on indicating led
			DIO_void_set_pin(PORTB, PIN2);
			//turn off the rest of the leds
			DIO_void_clear_pin(PORTB, PIN0);
			DIO_void_clear_pin(PORTB,PIN1);
			//stops motor
			stepper_stop();
			break;


		}



		}



}
