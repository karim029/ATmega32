/*
 * UART_Interface.h
 *
 *  Created on: Jun 16, 2023
 *      Author: karim
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define NULL ((void*)0)

// FOR the callback function

#define TX_complete 0
#define RX_complete 1
#define UDR_empty   2



//TO ADJUST THE DRIVER OPTIONS GO TO UART_Config.h

/*///////////////////////////////////*/
//UART control and status register A//
/*/////////////////////////////////*/

//Bit 7 – RXC: USART Receive Complete
#define UCSRA_RXC 7
//Bit 6 – TXC: USART Transmit Complete
#define UCSRA_TXC 6
//Bit 5 – UDRE: USART Data Register Empty
#define UCSRA_UDRE 5
//  Bit 4 – FE: Frame Error
#define UCSRA_FE 4
// Bit 3 – DOR: Data OverRun
#define UCSRA_DOR 3
// Bit 2 – PE: Parity Error
#define UCSRA_PE 2
// Bit 1 – U2X: Double the USART Transmission Speed
#define UCSRA_U2X 1
// Bit 0 – MPCM: Multi-processor Communication Mode
#define UCSRA_MPCM 0

/*///////////////////////////////////*/
//UART control and status register B//
/*/////////////////////////////////*/

// Bit 7 – RXCIE: RX Complete Interrupt Enable
#define UCSRB_RXCIE 7
// Bit 6 – TXCIE: TX Complete Interrupt Enable
#define UCSRB_TXCIE 6
// Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
#define UCSRB_UDRIE 5
// Bit 4 – RXEN: Receiver Enable
#define UCSRB_RXEN 4
// Bit 3 – TXEN: Transmitter Enable
#define UCSRB_TXEN 3
// Bit 2 – UCSZ2: Character Size (combined with UCSZ 1:0 bits in UCSRC)
#define UCSRB_UCZ2 2
// Bit 1 – RXB8: Receive Data Bit 8 -- ninth bit of data must be read before udr lows
#define UCSRB_RXB8 1
// Bit 1 – TXB8: Transmit Data Bit 8 -- ninth bit of data must be read before udr lows
#define UCSRB_TXB8 0

/*///////////////////////////////////*/
//UART control and status register C//
/*/////////////////////////////////*/

// The UCSRC Register shares the same I/O location as the UBRRH Register.

// Bit 7 – URSEL: Register Select 1 for UCSRC and 0 for UBBRH
#define UCSRC_URSEL 7
// Bit 6 – UMSEL: USART Mode Select 0 for async 1 for sync
#define UCSRC_UMSEL 6
// Bit 5:4 – UPM1:0: Parity Mode
#define UCSRC_UPM1 5
#define UCSRC_UPM0 4
// Bit 3 – USBS: Stop Bit Select
#define UCSRC_USBS 3
// Bit 2:1 – UCSZ1:0: Character Size
#define UCSRC_UCZ1 2
#define UCSRC_UCZ0 1
// Bit 0 – UCPOL: Clock Polarity !!USED FOR SYNCHRONOUS MODE ONLY!!
#define UCSRC_UCPOL 0


//for UBRRH Register
#define UBRRH_URSEL 7

void UART_set_Callback_function(u8 copy_index, void(*ptr_to_func)(void));
u8 UART_Receive_char();
void UART_Transmit_char(u8 data);
void UART_Init();
void Parity_mode();
void char_size_select();
void UART_Transmit_String(u8* copy_string);
void UART_Receive_String(u8* arr,u8 size);


#endif /* UART_INTERFACE_H_ */
