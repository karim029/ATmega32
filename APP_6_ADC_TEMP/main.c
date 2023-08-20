/**********************************************************************/
/*                      Created on: Jul 26, 2023                      */
/*                      Created By: Karim Tarek                       */
/*            ADC driver Application for Atmega32  Version 1.0        */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"
#include "../Drivers/MCAL/DIO/DIO_Interface.h"


#include "../Drivers/MCAL/ADC/ADC_Interface.h"


/*
 *   This is a simple test code for the ADC Driver
 *   with a temperature sesnor and 3 leds
 *   when the temperature is in a certain range a led will turn on
 *
 *   temp < 25 green led
 *   temp > 25 and < 40 blue led
 *   temp > 41 red led
 *
 */


void led_temperature_light(u32 adc_Result){

	u32 analog = (adc_Result * 5000)/1024;
	u32 temp = analog /10;

	if(temp <= 25){

		DIO_void_set_pin(PORTC, PIN0);
		DIO_void_clear_pin(PORTC, PIN1);
		DIO_void_clear_pin(PORTC, PIN2);

	}else if ((temp >= 26) && (temp <= 40)){
		DIO_void_set_pin(PORTC, PIN1);
		DIO_void_clear_pin(PORTC, PIN0);
		DIO_void_clear_pin(PORTC, PIN2);

	}else{

		DIO_void_set_pin(PORTC, PIN2);
		DIO_void_clear_pin(PORTC, PIN1);
		DIO_void_clear_pin(PORTC, PIN0);
	}


}

int main(){


	//SET 3 LEDS GREEN RED BLUE
	for(u8 i =0; i<3; i++){
		/*
		 * PC0 GREEN
		 * PC1 BLUE
		 * PC2 RED
		 */
	DIO_void_set_pin_dir(PORTC, i, OUTPUT);
	}

	DIO_void_set_pin_dir(PORTA, PIN0, INPUT); // TEMP SENSOR


	// adc initialization
	ADC_Void_Init();
	set_callBack_function(led_temperature_light);


	while(1){

		ADC_startConversion();


	}

	return 0;

}
