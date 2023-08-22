/*
 * Eeprom_Interface.h
 *
 *  Created on: Aug 22, 2023
 *      Author: karim
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

typedef enum{

	eepromAddressOverFlow,
	eepromWriteOK,
	eepromWriteNOK,
	eepromReadOK,
	eepromReadNOK



}eepromResult;

/* Public Function Declaration */
void eepromWriteByte(u16 copy_u16_Address, u8 copy_u8_Data);
u8 eepromReadByte(u16 copy_u16_Address);
eepromResult eepromWriteBytes(u16 copy_u16_Address,u8* copy_pu8_Data,u16 copy_u16_Length);
eepromResult eepromReadBytes(u16 copy_u16_Address,u8* copy_pu8_Data,u16 copy_u16_Length);



#endif /* EEPROM_INTERFACE_H_ */
