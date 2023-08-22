/*
 * Eeprom_Program.c
 *
 *  Created on: Aug 22, 2023
 *      Author: karim
 */

//STD LIBs
#include "../../../Libraries/bit_calc.h"
#include "../../../Libraries/STD_Types.h"

//Private MCAL
#include "Eeprom_Interface.h"
#include "Eeprom_Private.h"


#define MAX_EEPROM 1024

//Global Var


static void eepromWaitUntilReady(){

	/* Waiting for the previous writing operation */
	while(EECR & (1<<EEWE));


}

void eepromWriteByte(u16 copy_u16_Address, u8 copy_u8_Data){

	eepromWaitUntilReady();

	//load address and data
	EEAR = copy_u16_Address;
	EEDR = copy_u8_Data;

	//Enable EEprom Master Write
	EECR |= (1<<EEMWE);

	//enable Eeprom Write within 4 clock cycles
	EECR |= (1<<EEWE);

}


u8 eepromReadByte(u16 copy_u16_Address){

	eepromWaitUntilReady();

	//load address
	EEAR = copy_u16_Address;

	//enable Eeprom Read

	EECR |= (1<<EERE);

	//return data

	return EEDR;

}

eepromResult eepromWriteBytes(u16 copy_u16_Address,u8* copy_pu8_Data,u16 copy_u16_Length ){

	eepromResult Result;

	if((copy_u16_Address + copy_u16_Length)< MAX_EEPROM){


		for(u16 i = 0; i < copy_u16_Length; i++){

			eepromWriteByte(copy_u16_Address + i, copy_pu8_Data[i]);

		}

		Result = eepromWriteOK;

	} else {

		Result = eepromAddressOverFlow;

	}

	return Result;

}

eepromResult eepromReadBytes(u16 copy_u16_Address,u8* copy_pu8_Data,u16 copy_u16_Length){

	eepromResult result;

	if((copy_u16_Address + copy_u16_Length) <MAX_EEPROM){

		for(u16 i = 0; i < copy_u16_Length; i++){

			copy_pu8_Data[i] = eepromReadByte(copy_u16_Address + i);

		}

		result = eepromWriteOK;
	}else{

		result = eepromAddressOverFlow;
	}

	return result;
}







