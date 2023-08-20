/**********************************************************************/
/*                      Created on: Jul 21, 2023                      */
/*                      Created By: Karim Tarek                       */
/*        	   KEYPAD driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/



#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


void KPD_Active_Col_init();
void KPD_read_key(u8* copy_u8_key);
u8 KPD_get_key(u8* copy_u8_key);


#endif /* KEYPAD_INTERFACE_H_ */
