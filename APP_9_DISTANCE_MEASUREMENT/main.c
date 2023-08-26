/*
 * main.c
 *
 *  Created on: Aug 26, 2023
 *      Author: karim
 */

#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

#include "LCD_Interface.h"
#include "UltraSonic_Sensor_Interface.h"


int main(){


	u16 distance = 0;

	//initialize lcd and ultrasonic sensor
	LCD_init();
	ultraSonicInit();


	//write fixed text on lcd
	LCD_write_string((u8*)"Distance =   cm");


	while(1){

		//get readings and store it in variable distance
		distance = ultraSonicReadDistance();

		LCD_set_cursor(0, 10);

		LCD_write_number((s32)distance);



		if(distance < 100 || distance < 10){
			LCD_write_char(' ');
		}


	}

	return 0;
}
