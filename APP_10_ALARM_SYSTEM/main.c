/*
 * main.c
 *
 *  Created on: Sep 16, 2023
 *      Author: karim
 */

//std libs
#include "../LIBRARIES/STD_Types.h"
#include "../LIBRARIES/bit_calc.h"
#include "util/delay.h"
//HAL
#include "LCD_Interface.h"
#include "application.h"

extern u8 isrFlag;


int main(){

	/* declaration */
	//used to store the alarm time
	u8 alarmSeconds = 0, alarmMinutes = 0, alarmHours = 0;
	DIO_void_set_pin_dir(PORTB, PIN7, OUTPUT);


	// initialization
	alarmInit();
	buttonsInit();
	buzzerInit();
	LCD_init();


	while(1){

		if(isrFlag){
			LCD_set_cursor(0, 0);
			if(hours <10){

				LCD_write_char('0');

			}
			LCD_write_number(hours);
			LCD_write_char(':');
			if(minutes <10){

				LCD_write_char('0');


			}
			LCD_write_number(minutes);
			LCD_write_char(':');
			if(seconds < 10){

				LCD_write_char('0');

			}
			LCD_write_number(seconds);
			isrFlag = 0;

		}


		if(!buttonReading(ALARM_ON_OFF)){

			LCD_set_cursor(0, 9);
			LCD_write_string((u8*)"ALM:ON ");

			if((alarmSeconds == seconds)&&(alarmMinutes == minutes)&&(alarmHours == hours)){

				buzzerState(buzzerOn);
			}
		}else{
			LCD_set_cursor(0, 9);
			LCD_write_string((u8*)"ALM:OFF");
			buzzerState(buzzerOff);

		}

		LCD_set_cursor(1, 0);
		LCD_write_string((u8*)"ALARM:");

		LCD_set_cursor(1, 7);
			if(alarmHours <10){

				LCD_write_char('0');

			}
			LCD_write_number(alarmHours);
			LCD_write_char(':');
			if(alarmMinutes <10){

				LCD_write_char('0');


			}
			LCD_write_number(alarmMinutes);
			LCD_write_char(':');
			if(alarmSeconds < 10){

				LCD_write_char('0');

			}
			LCD_write_number(alarmSeconds);

		// if button time_alarm is not pressed then modify the time itself
		// if it pressed modify alarm time itself

			if(!buttonReading(TIME_ALARM_ADJUST)){

				if(!buttonReading(MIN_INCR)){
					_delay_ms(220);
					if(alarmMinutes < 60){
						alarmMinutes++;
					}
					if(alarmMinutes == 60){
						if(alarmHours <24){
							alarmHours++;
				}
						alarmMinutes = 0;
			}

				}

				if(!buttonReading(MIN_DECR)){
					_delay_ms(250);
					if(alarmMinutes >0)
						alarmMinutes--;

				}


				if(!buttonReading(HOURS_INCR)){
					_delay_ms(250);

					if(alarmHours <24)
						alarmHours++;
					if(alarmHours == 24)
						alarmHours = 0;
				}

				if(!buttonReading(HOURS_DECR)){
					_delay_ms(250);

					if(alarmHours >0)
						alarmHours--;
				}

			}else{
				if(!buttonReading(MIN_INCR)){
					_delay_ms(220);
					if(minutes < 60){
						minutes++;
					}
					if(minutes == 60){
						if(hours <24){
							hours++;
				}
						minutes = 0;
			}

				}

				if(!buttonReading(MIN_DECR)){
					_delay_ms(250);
					if(minutes >0)
						minutes--;

				}


				if(!buttonReading(HOURS_INCR)){
					_delay_ms(250);

					if(hours <24)
						hours++;
					if(hours == 24)
						hours = 0;
				}

				if(!buttonReading(HOURS_DECR)){
					_delay_ms(250);

					if(hours >0)
						hours--;
				}


			}

	}

	return 0;
}
