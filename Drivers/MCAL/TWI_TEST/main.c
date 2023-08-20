/*
 * main.c
 *
 *  Created on: Aug 7, 2023
 *      Author: karim
 */


#include <util/delay.h>
#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"

#include "TWI_Interface.h"
#include "TWI_Private.h"
#include "../DIO/DIO_Interface.h"

#define EEPROM_ADDRESS 0b1010000


int main(){
	u8 buffer[] = {0x00,0x6B,0x61,0x72,0x69,0x6D};
	u8 len = 6;

		SREG |= (1<<7);
		DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT);

TWI_masterTransmit(buffer, len, EEPROM_ADDRESS);
_delay_ms(250);
TWI_readEeprom(EEPROM_ADDRESS, len, 0x00);


	while(1){





	}

	return 0;
}
