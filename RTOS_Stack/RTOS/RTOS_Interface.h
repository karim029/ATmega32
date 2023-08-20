/*
 * RTOS_Interface.h
 *
 *  Created on: Aug 13, 2023
 *      Author: karim
 */

#include "../../Libraries/STD_Types.h"
#include "../../Libraries/bit_calc.h"

#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_



void RTOS_start();
void RTOS_createTask(u8 priority , u16 periodicity, void(*fptr)(void),u16 firstDelay);
void RTOS_suspendTask(u8 priority);
void RTOS_resumeTask(u8 priority);
void RTOS_deleteTask(u8 priority);

#endif /* RTOS_INTERFACE_H_ */
