/*
 * main.c
 *
 *  Created on: Aug 15, 2023
 *      Author: karim
 */


/*
 *  SIMPLE IMPLEMENTATION OF FREERTOS USING 2 TASKS WITH DIFFRENT PRIORITIES
 *  AND DIFFRENT PERIODICITY TO USE THE FREERTOS APIS FUNCTIONS
 *
 *  THE CODE BLINKS 2 LEDS IN A PARRALEL WAY.
 *
 */



// std libs
#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"

//mcal
#include "../../../Drivers/MCAL/DIO/DIO_Interface.h"
//FreeRtos libs
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"



void toggle_led1(void* ptr){

	while(1){

		DIO_void_toggle_pin(PORTA, PIN0);
			vTaskDelay(500);

	}

}

void toggle_led2(void* ptr){

	while(1){

		DIO_void_toggle_pin(PORTA, PIN1);
		vTaskDelay(1000);
	}
}

int main(){

	DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT);
	DIO_void_set_pin_dir(PORTA, PIN1, OUTPUT);


	xTaskCreate(toggle_led1,NULL,100,NULL,3,NULL);
	xTaskCreate(toggle_led2,NULL,100,NULL,1,NULL);

	vTaskStartScheduler();

	while(1){

	}

	return 0;
}




