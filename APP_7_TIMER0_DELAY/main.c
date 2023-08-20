/*
 * main.c
 *
 *  Created on: Aug 2, 2023
 *      Author: karim
 */


// STD libs
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

//MCAL
#include "../Drivers/MCAL/DIO/DIO_Interface.h"
#include "../Drivers/MCAL/TIMERS/TIMERS_Interface.h"
#include "../Drivers/MCAL/TIMERS/TIMERS_Config.h"


/*
 * this application is so simple
 * it only creates a delay of 1 second to toggle a led using timer0 overflow mode
 *
 *	prescaller 8 and clock 8mhz
 *	desired time 1 sec = 1000000 microsec
 *	number of overflow = 3906.25
 *	preload value  = 255 - (0.25*255) = 192
 *
 *
 */
u8 flag = 0; // flag to make sure 1 second delay passed
u16 overflow_Count;
void timer_count(){

	overflow_Count++;
	if(overflow_Count == 3907){

		overflow_Count = 0;
		TMR0_loadTCNT0(192);
		flag = 1;
	}


}

int main(){

		DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT);
		Timer_set_Callback_Func(TIMER0_OVF, timer_count);
		TMR0_Init();
		TMR0_loadTCNT0(192);



	while(1){

			if(flag){

				DIO_void_toggle_pin(PORTA, PIN0);
				flag = 0;

			}


	}

	return 0;
}
