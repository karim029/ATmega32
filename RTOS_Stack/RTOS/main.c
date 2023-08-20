/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: karim
 */


#include "../../Libraries/STD_Types.h"
#include "../../Libraries/bit_calc.h"

#include "../../Drivers/MCAL/DIO/DIO_Interface.h"
#include "../TIMER0/TIMERS_Interface.h"

#include "RTOS_Config.h"
#include "RTOS_Interface.h"
#include "RTOS_Private.h"


void led1(){

	DIO_void_toggle_pin(PORTA, PIN0);
}

void led2(){

	DIO_void_toggle_pin(PORTA, PIN1);
}

void led3(){

	DIO_void_toggle_pin(PORTA, PIN2);
}

int main(){

DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT);
DIO_void_set_pin_dir(PORTA, PIN1, OUTPUT);
DIO_void_set_pin_dir(PORTA, PIN2, OUTPUT);

	RTOS_createTask(0, 1000, led1);
	RTOS_createTask(1, 2000, led2);
	RTOS_createTask(2, 3000, led3);

	RTOS_start();

	while(1){


	}
	return 0;
}
