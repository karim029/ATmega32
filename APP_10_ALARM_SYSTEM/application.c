/*
 * application.c
 *
 *  Created on: Sep 16, 2023
 *      Author: karim
 */


#include "../LIBRARIES/STD_Types.h"
#include "../LIBRARIES/bit_calc.h"
#include "application.h"

#include "../DRIVERS/MCAL/DIO/DIO_Interface.h"
#include "TIMERS_Interface.h"


#include "TIMERS_Config.h"

#include "../DRIVERS/MCAL/TIMERS/TIMERS_Private.h"
#define BUTTONS 6
#define OCR1A_VALUE 31499


volatile u8 isrFlag = 0;

volatile u16 seconds;
volatile u16 minutes;
volatile u16 hours;



void alarmISR_calculation(){



	DIO_void_toggle_pin(PORTB	, PIN7);
	TMR1_loadOCR1A(OCR1A_VALUE);
	//the callback function that edit the values of the global variables
	//do you not use it outside of this scope!

	if(seconds<60){
		seconds++;
	}
	if(seconds == 60){

		if(minutes <60)
			minutes++;

		seconds = 0;
	}
	if(minutes == 60){

		if(hours<24)
			hours++;

		minutes = 0;
	}
	if(hours ==24){

		hours =0;
	}


	isrFlag = 1;

}

void alarmInit(){

	TMR1_loadOCR1A(31499);
	TMR1_Init();

	Timer_set_Callback_Func(TIMER1_COMPA,alarmISR_calculation);



}




void buttonsInit(){

	/*
	 * set 4 pins in the desired port to input and enable pullup
	 * must be 6 pins for example 012345  any 6 pins that are after each other
	 */

	if(BUTTONS_PORT>= 0 && BUTTONS_PORT <= 3 ){

		for(int i =0; i<BUTTONS; i++)
			DIO_void_pin_pullup(BUTTONS_PORT, i);

	}


}



u8 buttonReading(u8 button){

	/*
	 *  Read button state and return the value 0~1
	 *  use predefined macro for the desired buttton to read in the application.h
	 */

	return DIO_u8_get_pin(BUTTONS_PORT, button);

}



void buzzerInit(){

	DIO_void_set_pin_dir(BUZZER_PORT, BUZZER_PIN, OUTPUT);

}


void buzzerState(u8 state){

	switch(state){

	case buzzerOn:
			DIO_void_set_pin(BUZZER_PORT, BUZZER_PIN);
			break;

	case buzzerOff:
			DIO_void_clear_pin(BUZZER_PORT, BUZZER_PIN);
			break;
	}



}

