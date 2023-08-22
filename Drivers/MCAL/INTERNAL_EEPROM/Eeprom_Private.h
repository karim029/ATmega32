/*
 * Eeprom_Private.h
 *
 *  Created on: Aug 22, 2023
 *      Author: karim
 */

#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_

/* Registers Addresses */

// eeprom Adress register
#define EEAR *((volatile u16*)0x3E)

// eeprom Data register
#define EEDR *((volatile u8*)0x3D)

//eeprom Control register
#define EECR *((volatile u8*)0x3C)
/* Bits */
/* Eeprom Interrupt ready enable */
#define EERIE 3

/* Eeprom Master Write enable */
#define EEMWE 2

/* Eeprom Write enable */
#define EEWE  1

/* Eeprom Read enable */
#define EERE  0

/*Private Function Not for User to Use*/

static void eepromWaitUntilReady();

#endif /* EEPROM_PRIVATE_H_ */
