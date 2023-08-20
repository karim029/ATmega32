/*
 * UART_Private.h
 *
 *  Created on: Jun 16, 2023
 *      Author: Mosta
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR   *((volatile u8*)0x2C)
#define UCSRA *((volatile u8*)0x2B)
#define UCSRB *((volatile u8*)0x2A)
#define UCSRC *((volatile u8*)0x40) //same address
#define UBRRL *((volatile u8*)0x29)
#define UBRRH *((volatile u8*)0x40) // same address
#define SREG  *((volatile u8*)0x5F)

void __vector_14(void)__attribute__((signal)); //data registry empty
void __vector_13(void)__attribute__((signal)); // receive complete
void __vector_15(void)__attribute__((signal)); // transmit complete





#endif /* UART_PRIVATE_H_ */
