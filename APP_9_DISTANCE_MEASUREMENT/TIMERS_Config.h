/*
 * TIMERS_Config.h
 *
 *  Created on: Jul 29, 2023
 *      Author: karim
 */

#include "../Drivers/MCAL/TIMERS/TIMERS_Interface.h"



#ifndef TIMERS_CONFIG_H_
#define TIMERS_CONFIG_H_

#define ENABLE 1
#define DISABLE 0


/*************************** TIMER 0 CONFIG ***************************/

#define TMR0_MODE 			NORMAL_MODE
#define TMR0_OC0_MODE   	OC0_DISCONNECTED
#define TMR0_PRESCALE   	TMR0_CLK_8
#define TMR0_OVF_INTERRUPT	ENABLE
#define TMR0_OC_INTERRUPT	DISABLE

/*************************** TIMER 1 CONFIG ***************************/

#define TMR1_MODE			TMR1_NORMAL
#define TMR1_OCA_MODE		OC_DISCONNECTED
#define TMR1_OCB_MODE		OC_DISCONNECTED
#define TMR1_PRESCALE		TMR1_CLK_8
#define TMR1_CHANNEL_A		DISABLE
#define TMR1_CHANNEL_B		DISABLE
#define TMR1_ICR_VALUE		0
#define TMR1_OVF_INTERRUPT	DISABLE
#define TMR1_OCA_INTERRUPT	DISABLE
#define TMR1_OCB_INTERRUPT	DISABLE
#define TMR1_IC_INTERRUPT	ENABLE

/*************************** TIMER 2 CONFIG ***************************/

#define TMR2_MODE 			NORMAL_MODE
#define TMR2_OC2_MODE   	OC_DISCONNECTED
#define TMR2_PRESCALE   	TMR2_CLK_8
#define TMR2_OVF_INTERRUPT	ENABLE
#define TMR2_OC_INTERRUPT	DISABLE




#endif /* TIMERS_CONFIG_H_ */
