/**********************************************************************/
/*                      Created on: Jul 25, 2023                      */
/*                      Created By: Karim Tarek                       */
/*        External Interrupt driver for Atmega32  Version 1.0         */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

// standard lib
#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

//MCAL
#include "../Drivers/MCAL/DIO/DIO_Interface.h"


//Private Libs
#include "../Drivers/MCAL/EXTI/EXTI_Interface.h"
#include "../Drivers/MCAL/EXTI/EXTI_Private.h"
#include "../Drivers/MCAL/EXTI/EXTI_Registers.h"
#define Mapping 5
#define Error 99
// array of pointers to functions void void to store the callback function of the ISR

void(*call_back_func[3])(void);

//INT0
void __vector_1(){

	if(call_back_func[1] != null){
		call_back_func[1]();
	}
}
//INT1
void __vector_2(){

	if(call_back_func[2] != null){
		call_back_func[2]();
	}
}
//INT2
void __vector_3(){

	if(call_back_func[0] != null){
		call_back_func[0]();
	}
}

void EXTI_set_callBack_func(u8 copy_u8_id,void (*ptr_callBack)(void)){
	/*
	 *  function assigns the callback function to the array using the correct indexing
	 *  copy_u8_id should be used with INT0 INT1 INT2 Macros only
	 *  using a different value will result in a wrong behavior
	 *
	 */

	call_back_func[copy_u8_id - Mapping] = ptr_callBack;

}

void EXTI_global_Int(u8 copy_En_Dis){

	/* function Enable the global interrupt in the atmega32
	 * takes 1 input Enable or Disable Macros (0-1)
	 *
	 * ex global_Int(Enable);
	 *
	 */

	switch(copy_En_Dis){

		case Enable:
			set_Bit(SREG,GIE);
			break;
		case Disable:
			clear_Bit(SREG,GIE);

	}
}

void EXTI_ISR(u8 copy_u8_id,u8 copy_En_Dis ){

	/* function enable or disable ISR for the int0 int1 int2
	 * 	ex EXTI_ISR(int0,Enable);
	 *
	 */

	assign_Bit(GICR,copy_u8_id,copy_En_Dis);

}


void EXTI_sensingLevel(u8 copy_u8_id, u8 copy_u8_sensingLevel){

	/*
	 *  function that sets the sensing level based on the user input
	 *  and handle the hardware configuration of int2
	 *
	 *  the function return nothing
	 * 	for the sensing levels you can use the predefined macros in Interface.h
	 * 	or use binary or hexa representations of the desired value
	 *
	 * 	wrong input will result in a wrong behavior
	 * 	be careful!
	 *
	 */

	switch(copy_u8_id){

	case INT0:
		assign_Bit(MCUCR,ISC01,get_Bit(copy_u8_sensingLevel,bit1));
		assign_Bit(MCUCR,ISC00,get_Bit(copy_u8_sensingLevel,bit0));
		break;
	case INT1:
		assign_Bit(MCUCR,ISC11,get_Bit(copy_u8_sensingLevel,bit1));
		assign_Bit(MCUCR,ISC10,get_Bit(copy_u8_sensingLevel,bit0));
		break;
	case INT2:
		if((copy_u8_sensingLevel == EXTI_INT2_fallin_Edge) || (copy_u8_sensingLevel == EXTI_INT2_rising_Edge)){
			assign_Bit(MCUCSR,ISC2,copy_u8_sensingLevel);
		}
		break;

	}
}

u8 EXTI_read_INT_Flag(u8 copy_u8_id){


	/*
	 *  Function that reads the status of the interrupt flag and return it
	 *
	 *  use this function if you're using the polling method and no ISR
	 *
	 *  do you not Use this function when using ISR
	 *
	 *
	 */
switch(copy_u8_id){
	case INT0:
		return get_Bit(GIFR,INTF0);
		break;
	case INT1:
		return get_Bit(GIFR,INTF1);
		break;
	case INT2:
		return get_Bit(GIFR,INTF2);
		break;
	default:
		return Error;


}
}


