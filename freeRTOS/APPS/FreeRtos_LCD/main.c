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

SemaphoreHandle_t LCDsem;


void LCD1(void* vp){

u8 var;

	while(1){
		var = xSemaphoreTake(LCDsem,10);

		if(var == pdTRUE){
			LCD_write_string("TSK1");
			xSemaphoreGive(LCDsem);
		}
		vTaskDelay(2000);

	}


}
void LCD2(void* vp){

u8 var2;

	while(1){

		var2 = xSemaphoreTake(LCDsem,10);

		if(var2 == pdTRUE){

			LCD_write_string("TSK2");


			xSemaphoreGive(LCDsem);
		}

		vTaskDelay(2000);
	}


}


int main(){


	LCD_init();


	//LCD_write_number(650);
	vSemaphoreCreateBinary(LCDsem);

	xTaskCreate(LCD1,NULL,250,NULL,1,NULL);
	xTaskCreate(LCD2,NULL,250,NULL,1,NULL);


	vTaskStartScheduler();

	while(1){

	}

	return 0;
}




