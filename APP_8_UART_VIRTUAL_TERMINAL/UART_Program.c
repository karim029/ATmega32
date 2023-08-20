/*
 * UART_Program.c
 *
 *  Created on: Jun 16, 2023
 *      Author: karim
 */

#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"

#include "../Drivers/MCAL/DIO/DIO_Interface.h"
#include "../Drivers/MCAL/UART/UART_Private.h"
#include "../Drivers/MCAL/UART/UART_Interface.h"
#include "../Drivers/MCAL/UART/UART_Config.h"


void (*callback_func[3])(void);

void UART_set_Callback_function(u8 copy_index, void(*ptr_to_func)(void)){

	if (copy_index >=0 && copy_index <3){

		callback_func[copy_index] = ptr_to_func;

	}

}


void char_size_select(){

#if char_size_Select == char_size_5_bit

	set_Bit(UCSRC,UCSRC_URSEL);
	clear_Bit(UCSRC,UCSRC_UCZ1);
	clear_Bit(UCSRC,UCSRC_UCZ0);
	clear_Bit(UCSRB,UCSRB_UCZ2);

#elif char_size_Select == char_size_6_bit

	set_Bit(UCSRC,UCSRC_URSEL);
	set_Bit(UCSRC,UCSRC_UCZ0);
	clear_Bit(UCSRC,UCSRC_UCZ1);
	clear_Bit(UCSRB,UCSRB_UCZ2);

#elif char_size_Select == char_size_7_bit

	set_Bit(UCSRC,UCSRC_URSEL);
	clear_Bit(UCSRC,UCSRC_UCZ0);
	set_Bit(UCSRC,UCSRC_UCZ1);
	clear_Bit(UCSRB,UCSRB_UCZ2);

#elif char_size_Select == char_size_8_bit

	set_Bit(UCSRC,UCSRC_URSEL);
	set_Bit(UCSRC,UCSRC_UCZ0);
	set_Bit(UCSRC,UCSRC_UCZ1);
	clear_Bit(UCSRB,UCSRB_UCZ2);

#elif char_size_Select == char_size_9_bit

	set_Bit(UCSRC,UCSRC_URSEL);
	set_Bit(UCSRC,UCSRC_UCZ0);
	set_Bit(UCSRC,UCSRC_UCZ1);
	set_Bit(UCSRB,UCSRB_UCZ2);
#endif

}

void Parity_mode(){


#if Parity_mode_select == Parity_enabled_even
	set_Bit(UCSRC,UCSRC_URSEL);
	set_Bit(UCSRC,UCSRC_UPM1);
	clear_Bit(UCSRC,UCSRC_UPM0);

#elif Parity_mode_select == Parity_enabled_odd
	set_Bit(UCSRC,UCSRC_URSEL);
	set_Bit(UCSRC,UCSRC_UPM1);
	set_Bit(UCSRC,UCSRC_UPM0);

#endif
}

void UART_Init(){



	//Set BAUD rate value

#if UBR_Val > Max_8Bit_Val

	clear_Bit(UBRRH,UBRRH_URSEL);
	UBRRH = (UBR_Val >> 8) & 0XFF;
	UBRRL = (UBR_Val & 0XFF);
#else
	UBRRL = UBR_Val;

#endif

	// set operation mode
#if operation_mode == Async
	set_Bit(UCSRC,UCSRC_URSEL);
	clear_Bit(UCSRC,UCSRC_UMSEL);
#else
	set_Bit(UCSRC,UCSRC_URSEL);
	set_Bit(UCSRC,UCSRC_UMSEL);
#endif
	//select the number of stop bits in the frame
#if Stop_Bits_selection == single_stop_bit
	set_Bit(UCSRC,UCSRC_URSEL);
	clear_Bit(UCSRC,UCSRC_USBS);
#else
	set_Bit(UCSRC,UCSRC_URSEL);
	set_Bit(UCSRC,UCSRC_USBS);
#endif

#if Parity_mode_select != Parity_disabled
	Parity_mode();
#endif

	char_size_select();


//enable tx rx pins

	set_Bit(UCSRB,UCSRB_TXEN);
	set_Bit(UCSRB,UCSRB_RXEN);

#if TX_Comp_Interrupt == True
	set_Bit(SREG,7);
	set_Bit(UCSRB,UCSRB_TXCIE);

#endif
#if RX_Comp_Interrupt == True
	set_Bit(SREG,7);
	set_Bit(UCSRB,UCSRB_RXCIE);
#endif
#if UDR_Empty_Interrupt == True
	set_Bit(SREG,7);
	set_Bit(UCSRB,UCSRB_UDRIE);

#endif
}



void UART_Transmit_char(u8 data){

#if UDR_Empty_Interrupt == True

	UDR = data;

#else

	while(get_Bit(UCSRA,UCSRA_UDRE) == 0);
	UDR = data;

#endif
}

u8 UART_Receive_char(){

	u8 result;
#if RX_Comp_Interrupt == True

	result =  UDR;

	return result;
#else

	while(get_Bit(UCSRA,UCSRA_RXC) == 0);

	result = UDR;

	return result;

#endif
}


void UART_Transmit_String(u8* copy_string){

	while(*copy_string){

		UART_Transmit_char((u8)*copy_string);
		copy_string++;
	}
	UART_Transmit_char('\0');

}

void UART_Receive_String(u8* arr){

	u8 i =0;


		arr[i] = UART_Receive_char();

	while(arr[i]){

		arr[i] = UART_Receive_char();
		i++;


	}




}

// RX Complete
void __vector_13(){

	if(callback_func[RX_complete] != NULL){

		callback_func[RX_complete]();

	}

}

// UDR empty
void __vector_14(){

	if(callback_func[UDR_empty]!= NULL){

		callback_func[UDR_empty]();
	}
}
// TX Complete
void __Vector_15(){

	if(callback_func[TX_complete]!= NULL){

		callback_func[TX_complete]();
	}
}

