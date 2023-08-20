/**********************************************************************/
/*                      Created on: Jul 21, 2023                      */
/*                      Created By: Karim Tarek                       */
/*        	   KEYPAD 4x4 driver for Atmega32  Version 1.0            */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/


// standard lib
#include <util/delay.h>
#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"

// MCAL
#include "../../MCAL/DIO/DIO_Interface.h"


// private libs
#include "KEYPAD_Config.h"
#include "KEYPAD_Interface.h"

// global arrays

u8 KPD_Row_Pin[row_Number] = {row_0,row_1,row_2,row_3};
u8 KPD_Col_Pin[col_Number] = {col_0,col_1,col_2,col_3};



void KPD_Active_Col_init(){

	//set the columns to output
	for(u8 col = 0; col<col_Number;col++){

		DIO_void_set_pin_dir(col_Port,KPD_Col_Pin[col],OUTPUT);
		// set to high (pullup)
		DIO_void_set_pin(col_Port, KPD_Col_Pin[col]);
	}

	//set rows to input and activate internal pullup
	for(u8 row = 0; row<row_Number;row++){

		DIO_void_pin_pullup(row_Port, KPD_Row_Pin[row]);

	}
}

void KPD_read_key(u8* copy_u8_key){

	u8 key_index = 0;

	//nested for loop clear each column and check every row then set the column pin high again
	/* ex 0111
	 * 	  1011
	 *    1101
	 *    1110
	 *
	 *     for columns
`    */

	for(u8 col = 0; col<col_Number; col++){

		//clear column pins
		DIO_void_clear_pin(col_Port, KPD_Col_Pin[col]);

		for(u8 row = 0; row < row_Number; row++){

			key_index = (row * 4)+ col;
			copy_u8_key[key_index] = DIO_u8_get_pin(row_Port, KPD_Row_Pin[row]);

		}

		DIO_void_set_pin(col_Port, KPD_Col_Pin[col]);

	}




}


u8 KPD_get_key(u8* copy_u8_key) {

	/*
	 * Mapping function used to Map the index of the array of elements with low Value
	 *
	 * To its corresponding location on the 4x4 keypad
	 *
	 * the function takes the array as input
	 *
	 * and return the correct key for the keypad
	 *
	 *
	 *
	 *
	 */


    u8 key_index = KPD_size; // Initialize to an invalid value that does not correspond to any key
    u8 key_pressed = 0; // Flag to indicate if any key is pressed

    for (u8 i = 0; i < KPD_size; i++) {
        if (copy_u8_key[i] == LOW) {
            key_index = i;
            key_pressed = 1;
            break;
        }
    }

    if (key_pressed) {
        switch (key_index) {
            case 0: return '7';
            case 1: return '8';
            case 2: return '9';
            case 3: return '/';
            case 4: return '4';
            case 5: return '5';
            case 6: return '6';
            case 7: return '*';
            case 8: return '1';
            case 9: return '2';
            case 10: return '3';
            case 11: return '-';
            case 12: return 'c';
            case 13: return '0';
            case 14: return '=';
            case 15: return '+';
          //  default: return 16;
        }
    }else{

    	return 16;

    }


}







