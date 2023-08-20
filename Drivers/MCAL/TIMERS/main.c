/*
 * main.c
 *
 *  Created on: Jul 29, 2023
 *      Author: karim
 */


// standard libs
#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"

//MCAL
#include "../DIO/DIO_Interface.h"

//private
#include "TIMERS_Config.h"
#include "TIMERS_Interface.h"
#include "TIMERS_Private.h"




int main(){

	DIO_void_set_pin_dir(PORTA, PIN0, OUTPUT);
	TMR1_Init();
	TMR1_loadTCNT1(49152);

	while(1){




	}

	return 0;
}
