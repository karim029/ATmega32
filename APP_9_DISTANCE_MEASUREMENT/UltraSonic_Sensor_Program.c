/*
 * UltraSonic_Sensor_Program.c
 *
 *  Created on: Aug 26, 2023
 *      Author: karim
 */


// standard libs
#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

//MCAL
#include "../Drivers/MCAL/TIMERS/TIMERS_Interface.h"

//Private
#include "UltraSonic_Sensor_Interface.h"


//global variables

static volatile u8 edgeCount = 0;
static volatile u16 dutyCycle = 0;


void ultraSonicInit(){

	/*
	 *  - initialize timer1 and ICU
	 *  - set icp1 pin direction to input
	 *  - set callback function (edge calculations)
	 *  - set trigger pin to output
	 */

	TMR1_Init();
	TMR1_ICU_Enable(ICU_RISING_EDGE);
	Timer_set_Callback_Func(TIMER1_ICU, ultraSonicEdgeCalc);
	DIO_void_set_pin_dir(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, OUTPUT);

}


static void ultraSonicPulse(){

	/*
	 *  send pulse to trigger pin each 10 us
	 */

	DIO_void_set_pin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN);

	_delay_us(10);

	DIO_void_clear_pin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN);
}


u16 ultraSonicReadDistance(){

	ultraSonicPulse();

	return (0.017 * dutyCycle);


}


void ultraSonicEdgeCalc(){

	/*
	 *
	 *  This function will be the icu callback function
	 *  and will be called everytime the isr is called (in a rising edge or in a fallin edge)
	 *
	 */

	//increment counter
	edgeCount ++;

	if(edgeCount == 1){

		//clear timer value
		TMR1_Clear_value();


		// change the sensing control to detect falling edge on the echo pin
		TMR1_ICU_Enable(ICU_FALLING_EDGE);

	}else if (edgeCount == 2){

		//store the on time of the pulse in the global var
		dutyCycle = TMR1_ICU_read();

		// change the sensing control to detect rising edge on the echo pin
		TMR1_ICU_Enable(ICU_RISING_EDGE);

		//clear timer value

		TMR1_Clear_value();

		//reset counter
		edgeCount = 0;

	}


}


