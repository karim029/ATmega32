/*
 * RTOS_Program.c
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
#define NULL ((void*)0)

Task_t systemTasks[TASK_NUM] = {{NULL}};

void RTOS_start(){

	//SET THE Scheduler function to be the callback function for ctc iSR
	Timer_set_Callback_Func(TIMER0_COMP, RTOS_scheduler);
	// enable Global interrupt

	//initialize timer0
	TMR0_Init();


}

void RTOS_resumeTask(u8 priority){

	systemTasks[priority].state = resumed;

}

void RTOS_suspendTask(u8 priority){

	systemTasks[priority].state = suspended;


}
void RTOS_createTask(u8 priority , u16 periodicity, void(*fptr)(void),u16 firstDelay){

	if(systemTasks[priority].taskfunc == NULL){
	systemTasks[priority].periodicity = periodicity;
	systemTasks[priority].taskfunc = fptr;
	systemTasks[priority].state = resumed;
	systemTasks[priority].firstDelay = firstDelay;
	}


}
void RTOS_deleteTask(u8 priority){

	systemTasks[priority].taskfunc = NULL;
}


static void RTOS_scheduler(){

	u8 taskCounter;


	// loop on all task each tick time = 1ms


	for(taskCounter = 0; taskCounter < TASK_NUM; taskCounter++){
		if(systemTasks[taskCounter].state == resumed){

		if((systemTasks[taskCounter].firstDelay) == 0){

			// invoke the task function
			if(systemTasks[taskCounter].taskfunc != NULL){

				systemTasks[taskCounter].taskfunc();
				systemTasks[taskCounter].firstDelay = systemTasks[taskCounter].periodicity-1;

			}else{

				systemTasks[taskCounter].firstDelay--;

			}

		}

		}
	}

}
