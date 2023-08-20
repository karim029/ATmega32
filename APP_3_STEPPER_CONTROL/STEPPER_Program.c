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


// Standard libs
#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

// MCAL lib
#include "../Drivers/MCAL/DIO/DIO_Interface.h"

// Private libs
#include "STEPPER_Interface.h"

#define MIN_SPEED 10
#define MAX_SPEED 1000

//array of tyoe stepperstate storing the sequence of the full step
const StepperState full_Step_Sequence[4][4] = {
    {STEPPER_HIGH, STEPPER_LOW, STEPPER_LOW, STEPPER_LOW},
    {STEPPER_LOW, STEPPER_HIGH, STEPPER_LOW, STEPPER_LOW},
    {STEPPER_LOW, STEPPER_LOW, STEPPER_HIGH, STEPPER_LOW},
    {STEPPER_LOW, STEPPER_LOW, STEPPER_LOW, STEPPER_HIGH}
};

//array of tyoe stepperstate storing the sequence of the half step
const StepperState half_Step_Sequence[8][4] = {
    {STEPPER_HIGH, STEPPER_LOW, STEPPER_LOW, STEPPER_LOW},
    {STEPPER_HIGH, STEPPER_HIGH, STEPPER_LOW, STEPPER_LOW},
    {STEPPER_LOW, STEPPER_HIGH, STEPPER_LOW, STEPPER_LOW},
    {STEPPER_LOW, STEPPER_HIGH, STEPPER_HIGH, STEPPER_LOW},
    {STEPPER_LOW, STEPPER_LOW, STEPPER_HIGH, STEPPER_LOW},
    {STEPPER_LOW, STEPPER_LOW, STEPPER_HIGH, STEPPER_HIGH},
    {STEPPER_LOW, STEPPER_LOW, STEPPER_LOW, STEPPER_HIGH},
    {STEPPER_HIGH, STEPPER_LOW, STEPPER_LOW, STEPPER_HIGH}
};

// Define the coil states for the full step sequence
const u8 coils[4] = {blue_Coil,pink_Coil,yellow_Coil,orange_Coil};


u16 map_value(u16 val , u16 in_min, u16 in_max, u16 out_min, u16 out_max){

	/*
	 *  function purpose to map values for the correct motor speed range using stepper motor freq.
	 *
	 *  the function uses logarithmic scalling to smooth its output
	 *  so the user can have more control over the desired spped
	 *
	 * 	DO NOT USE THIS FUNCTION OUTSIDE OF THE DRIVER
	 */

	if(val < in_min){
		val = in_min;
	}else if(val > in_max){
		val = in_max;

	}

	 float input_range = in_max - in_min;
	    float output_range = out_max - out_min;
	    float scaled_value = (val - in_min) / input_range; // Value between 0 and 1
	    float scaled_output = (scaled_value * scaled_value)*(0.25); // Apply logarithmic scaling to smooth speed

	    return (u16)(scaled_output * output_range + out_min);
}


void stepper_Init(){


	/*
	 * this function sets the direction of the stepper coil to output
	 *
	 *
	 */
	for(u8 i = 0; i<4;i++){

		DIO_void_set_pin_dir(coil_Port, coils[i],OUTPUT);

	}

}

void stepper_Rotation_CW(u16 copy_speed_val){

	/*
	 * 	This function control the rotation of the stepper motor
	 * 	using the clockwise rotation sequence
	 * 	it supports 2 modes the full step and the half step modes
	 *
	 * 	to change the mode modify the operation mode macro in the STEPPER_Interface.h file
	 *
	 * 	also the function takes an input (the motor speed)
	 * 	we control the stepper motor speed by increasing or decreasing the frequency
	 * 	between each step of the motor
	 *
	 * 	The tested speed range is from 10 ms -- 1000 ms
	 *
	 *
	 * 	do you not edit this function it will result in wrong behaviors
	 *
	 *
	 */


	u16 result = map_value(copy_speed_val, 0 , 255 , MIN_SPEED, MAX_SPEED);

#if operation_Mode == full_Step

	    for (u8 step = 0; step < 4; step++) {
	        DIO_void_assign_pin(coil_Port, blue_Coil, full_Step_Sequence[step][0]);
	        DIO_void_assign_pin(coil_Port, pink_Coil, full_Step_Sequence[step][1]);
	        DIO_void_assign_pin(coil_Port, yellow_Coil, full_Step_Sequence[step][2]);
	        DIO_void_assign_pin(coil_Port, orange_Coil, full_Step_Sequence[step][3]);
	        _delay_ms(result);
	    }

#elif operation_Mode == half_Step

	    for (u8 step = 0; step < 8; step++) {
	    	        DIO_void_assign_pin(coil_Port, blue_Coil, half_Step_Sequence[step][0]);
	    	        DIO_void_assign_pin(coil_Port, pink_Coil, half_Step_Sequence[step][1]);
	    	        DIO_void_assign_pin(coil_Port, yellow_Coil, half_Step_Sequence[step][2]);
	    	        DIO_void_assign_pin(coil_Port, orange_Coil, half_Step_Sequence[step][3]);
	    	        _delay_ms(result);
	    	    }

#endif


}
void stepper_Rotation_CCW(u16 copy_speed_val){

	/*
		 * 	This function control the rotation of the stepper motor
		 * 	using the Counter-clockwise rotation sequence
		 * 	it supports 2 modes the full step and the half step modes
		 *
		 * 	to change the mode modify the operation mode macro in the STEPPER_Interface.h file
		 *
		 * 	also the function takes an input (the motor speed)
		 * 	we control the stepper motor speed by increasing or decreasing the frequency
		 * 	between each step of the motor
		 *
		 * 	The tested speed range is from 10 ms -- 1000 ms
		 *
		 *
		 * 	do you not edit this function it will result in wrong behaviors
		 *
		 *
		 */


	u16 result = map_value(copy_speed_val, 0 , 255 , MIN_SPEED, MAX_SPEED);

#if operation_Mode == full_Step
	for (s8 step = 3; step >= 0; step--) {
	        DIO_void_assign_pin(coil_Port, blue_Coil, full_Step_Sequence[step][0]);
	        DIO_void_assign_pin(coil_Port, pink_Coil, full_Step_Sequence[step][1]);
	        DIO_void_assign_pin(coil_Port, yellow_Coil, full_Step_Sequence[step][2]);
	        DIO_void_assign_pin(coil_Port, orange_Coil, full_Step_Sequence[step][3]);
	        _delay_ms(result);
	    }
#elif operation_Mode == half_Step

	 for (s8 step = 7; step >= 0; step--) {
	         DIO_void_assign_pin(coil_Port, blue_Coil, half_Step_Sequence[step][0]);
	         DIO_void_assign_pin(coil_Port, pink_Coil, half_Step_Sequence[step][1]);
	         DIO_void_assign_pin(coil_Port, yellow_Coil, half_Step_Sequence[step][2]);
	         DIO_void_assign_pin(coil_Port, orange_Coil, half_Step_Sequence[step][3]);
	         _delay_ms(result);
	     }


#endif
	}

void stepper_stop(){

	/*
	 *
	 *  Function to stop the Stepper motor
	 *
	 */
	for(u8 i = 0; i<4; i++){

		DIO_void_clear_pin(coil_Port, coils[i]);
	}

}

