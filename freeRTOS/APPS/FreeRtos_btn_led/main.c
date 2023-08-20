/*
 * main.c
 *
 *  Created on: Aug 15, 2023
 *      Author: karim
 */
#include <util/delay.h>

// std libs
#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"

//mcal
#include "../../../Drivers/MCAL/DIO/DIO_Interface.h"

//hal
#include "LCD_Interface.h"


//FreeRtos libs
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


//CREATING A SEMAPHORE OBJECT

SemaphoreHandle_t x_semaphore;


void scanButton(void* pv){


	u8 btn_State = pdFALSE;
	u8 flag;


	while(1){
		flag = DIO_u8_get_pin(PORTA, PIN0);
		if((flag == 0) && (btn_State == pdFALSE)){

			// button is pressed
			// change state to true
			btn_State = pdTRUE;
			// give back the semaphore;
			xSemaphoreGive(x_semaphore);

		}else if ((flag == 1)&&(btn_State == pdTRUE)){

			// button was pressed and now is released
			btn_State = pdFALSE;
			//try to take the semaphore
			xSemaphoreTake(x_semaphore,0);
		}


		vTaskDelay(10);

	}

}


void toggle_led(void* pv){

	while(1){


		//check on the semaphore if it is available (means button pressed)

		if(xSemaphoreTake(x_semaphore,10) == pdPASS){
		DIO_void_toggle_pin(PORTB, PIN0);
		}

	}

}

int main(){

	// BUTTON
	DIO_void_pin_pullup(PORTA, PIN0);
	// LED
	DIO_void_set_pin_dir(PORTB, PIN0, OUTPUT);
	//create binary semaphore
	vSemaphoreCreateBinary(x_semaphore);
	// allocate memory for the 2 tasks (Create them)
	xTaskCreate(scanButton,"button",250,NULL,2,NULL);
	xTaskCreate(toggle_led,"led",250,NULL,1,NULL);


	//initiate the scheduler.
	vTaskStartScheduler();

	while(1){

	}

	return 0;
}




