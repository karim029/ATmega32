/*
 * RTOS_Private.h
 *
 *  Created on: Aug 13, 2023
 *      Author: karim
 */

#ifndef RTOS_PRIVATE_H_
#define RTOS_PRIVATE_H_

#define SREG *((volatile u8*)0x5F)

typedef enum{

	suspended,
	resumed

}Task_State;


typedef struct{

	u16 periodicity;
	void(*taskfunc)(void);
	Task_State state;
	u16 firstDelay;

}Task_t;

static void RTOS_scheduler();


#endif /* RTOS_PRIVATE_H_ */
