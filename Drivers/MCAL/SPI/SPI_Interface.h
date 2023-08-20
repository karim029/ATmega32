/*
 * SPI_Interface.h
 *
 *  Created on: Aug 3, 2023
 *      Author: karim
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#define NULL ((void*)0)

// SPI Control Register
// • Bit 7 – SPIE: SPI Interrupt Enable
#define SPIE 7
// Bit 6 – SPE: SPI Enable
#define SPE 6
// Bit 5 – DORD: Data Order
#define DORD 5
// • Bit 4 – MSTR: Master/Slave Select
#define MSTR 4 // 1 for master 0 for slave
// • Bit 3 – CPOL: Clock Polarity
#define CPOL 3
// • Bit 2 – CPHA: Clock Phase
#define CPHA 2
// • Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0
#define SPR1 1
#define SPR0 0

//SPI Status Register – SPSR
//• Bit 7 – SPIF: SPI Interrupt Flag
#define SPIF 7
// • Bit 6 – WCOL: Write COLlision Flag
#define WCOL 6
//• Bit 0 – SPI2X: Double SPI Speed Bit
#define SPI2X 0

// PIN CONFIGURATIONS

#define SPI_REF_PORT PORTB

#define SS	 PIN4
#define MOSI PIN5
#define MISO PIN6
#define SCK  PIN7


#endif /* SPI_INTERFACE_H_ */
