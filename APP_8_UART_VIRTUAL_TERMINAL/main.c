/*
 * main.c
 *
 *  Created on: Aug 2, 2023
 *      Author: karim
 */

/* Standard Libraries */

#include "../Libraries/bit_calc.h"
#include "../Libraries/STD_Types.h"

/* MCAL */
#include "../Drivers/MCAL/DIO/DIO_Interface.h"
#include "../Drivers/MCAL/UART/UART_Interface.h"

/*
 * Using the virtual terminal when transmitting to the MCU
 * 1 - 2 - 3 different leds turn on
 *
 *
 *
 */


int main(){

	u8 data;
	u8 rcv_data;
	DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT);
	DIO_void_set_pin_dir(PORTA, PIN1, OUTPUT);
	DIO_void_set_pin_dir(PORTA, PIN2, OUTPUT);
	UART_Init();

	while(1){


		UART_Transmit_String((u8*)"1-Yellow \n2-Red\n 3-Green\n");
				data = UART_Receive_char();
				if(data != 0){
					rcv_data = data;
					data = 0;

					switch(rcv_data){


						case '1':
							DIO_void_toggle_pin(PORTA, PIN0);
						break;
						case '2':
							DIO_void_toggle_pin(PORTA, PIN1);
						break;
						case '3':
							DIO_void_toggle_pin(PORTA, PIN2);
						break;


					}
				}
	}



	return 0;
}
