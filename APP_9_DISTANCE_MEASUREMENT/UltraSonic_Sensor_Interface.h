/*
 * UltraSonic_Sensor_Interface.h
 *
 *  Created on: Aug 26, 2023
 *      Author: karim
 */

#ifndef ULTRASONIC_SENSOR_INTERFACE_H_
#define ULTRASONIC_SENSOR_INTERFACE_H_

#include "../DRIVERS/MCAL/DIO/DIO_Interface.h"


#define ULTRASONIC_TRIGGER_PORT 	PORTC
#define ULTRASONIC_TRIGGER_PIN 	    PIN5

#define ULTRASONIC_ECHO_PORT		PORTD
#define ULTRASONIC_ECHO_PIN			PIN6

#define TRIGGER_DURATION			10 //10 us

//Public function declaration//
void ultraSonicInit();
u16 ultraSonicReadDistance();
void ultraSonicEdgeCalc();


//Private function declaration//
static void ultraSonicPulse();


#endif /* ULTRASONIC_SENSOR_INTERFACE_H_ */
