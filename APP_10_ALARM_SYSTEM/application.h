/*
 * application.h
 *
 *  Created on: Sep 16, 2023
 *      Author: karim
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_


#include "../DRIVERS/MCAL/DIO/DIO_Interface.h"

extern volatile u16 hours;
extern volatile u16 minutes;
extern volatile u16 seconds;

typedef enum{

	buzzerOn,
	buzzerOff

}sirenState_t;

#define BUZZER_PORT 		PORTD
#define BUZZER_PIN			PIN0

#define BUTTONS_PORT		PORTC

//buttons
#define HOURS_INCR			PIN0
#define HOURS_DECR			PIN1
#define MIN_INCR			PIN2
#define MIN_DECR			PIN3
#define TIME_ALARM_ADJUST	PIN4
#define ALARM_ON_OFF		PIN5

void alarmInit();
void buttonsInit();
void buzzerInit();
void alarmISR_calculation();
u8 buttonReading(u8 button);
void buzzerState(u8 state);
#endif /* APPLICATION_H_ */
