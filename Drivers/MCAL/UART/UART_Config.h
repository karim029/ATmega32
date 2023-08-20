/*
 * UART_Config.h
 *
 *  Created on: Jun 18, 2023
 *      Author: karim
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define True 1
#define False 0


#define TX_Comp_Interrupt False
#define RX_Comp_Interrupt False
#define UDR_Empty_Interrupt False

#define UBR_Val 51
#define Max_8Bit_Val 255


//mode of operation
#define sync 0
#define Async 1
#define operation_mode Async


//stop bits
#define single_stop_bit 0
#define two_stop_bits 1

#define Stop_Bits_selection single_stop_bit

//parity mode
#define Parity_disabled 0
#define Parity_enabled_even 1
#define Parity_enabled_odd 2

#define Parity_mode_select Parity_disabled

//character size select
#define char_size_5_bit 0
#define char_size_6_bit 1
#define char_size_7_bit 2
#define char_size_8_bit 3
#define char_size_9_bit 4

#define char_size_Select char_size_8_bit





#endif /* UART_CONFIG_H_ */
