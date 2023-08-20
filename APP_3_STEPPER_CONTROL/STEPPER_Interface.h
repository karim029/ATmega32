/**********************************************************************/
/*                      Created on: Jul 19, 2023                      */
/*                      Created By: Karim Tarek                       */
/*           Stepper Motor driver for Atmega32  Version 1.0           */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

#include "../Drivers/MCAL/DIO/DIO_Interface.h"

#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_


// Enum for the stepper coils state high or low
typedef enum {
    STEPPER_LOW = 0,
    STEPPER_HIGH = 1
} StepperState;
// select disered port to use PORTx --> A B C D
#define coil_Port PORTC
// defining the coil pins based on their color
#define blue_Coil PIN0
#define pink_Coil PIN1
#define yellow_Coil PIN2
#define orange_Coil PIN3

// mode of operation ~~~ half step or full step

#define full_Step 0
#define half_Step 1

#define operation_Mode half_Step


/* Functions declaration */
void stepper_Rotation_CCW(u16 copy_speed_val);
void stepper_Rotation_CW(u16 copy_speed_val);
void stepper_Init();
void stepper_stop();


#endif /* STEPPER_INTERFACE_H_ */
