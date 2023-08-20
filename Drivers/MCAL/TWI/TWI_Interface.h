/*
 * TWI_Interface.h
 *
 *  Created on: Aug 7, 2023
 *      Author: karim
 */

#include "TWI_Private.h"
#include "../../../Libraries/STD_Types.h"


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

#define Read  1
#define write 0


#define NULL ((void*)0)


#define F_CPU 8000000
#define TWI_FRQ 20000
#define TWI_STATUS (TWSR & 0XF8)


typedef enum{

	status_ready,
	status_busy

}TWI_Status;

typedef enum{

	result_successful,
	result_No_ack,
	result_lost_Arb,
	result_incomplete,
	result_waiting

}TWI_Result;

typedef enum{

	Idle,
	MasterTransmitter,
	MasterReciever,
	SlaveTransmitter,
	SlaveReciever,
	ReadEeprom

}TWI_Mode;



//Status code for TWI
#define TWI_START_SENT 			0X08
#define TWI_REP_START_SENT 		0X10

//MT MODE (MASTER TRANSMITTER)
#define TWI_MT_SLAW_ACK			0X18 //sla +w sent and ack received
#define TWI_MT_SLAW_NACK		0X20 //sla +w sent and nack received
#define TWI_MT_DATA_ACK			0X28 //data sent and ack received
#define TWI_MT_DATA_NACK		0X30 //data sent and nack received
//MR MODE (MASTER RECEIVER)
#define TWI_MR_SLAR_ACK			0X40 //sla+r sent and ack received
#define TWI_MR_SLAR_NACK		0X48 //sla+r sent and nack received
#define TWI_MR_DATA_ACK			0X50 //data received, ack returned
#define TWI_MR_DATA_NACK		0X58 // data received, nack returned
// Miscellaneous States
#define TWI_LOST_ARBIT			0x38 // Arbitration has been lost
#define TWI_NO_RELEVANT_INFO	0xF8 // No relevant information available
#define TWI_ILLEGAL_START_STOP	0x00 // Illegal START or STOP condition has been detected
#define TWI_SUCCESS				0xFF // Successful transfer, this state is impossible from TWSR as bit2 is 0 and read only

// some function macros to use for driver implementation
/*
 * Send Start signal, enable TWI and interrupt and clear twi flag to go to next step
 */
#define TWISendStart() 		(TWCR |=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWIE))

/*
 * Send stop signal, enable TWI and interrupt and clear twi flag to go to next step
 */

#define TWISendStop()  		(TWCR |=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN))
/*
 * Used to resume a transfer, clear TWINT and ensure that TWI and interrupts are enabled.
 */
#define TWIResumeTransmit() (TWCR |=(1<<TWINT)|(1<<TWEN)|(1<<TWIE))
/*
 * FOR MR mode. Resume a transfer, ensure that TWI and interrupts are enabled and respond with an ACK if the device is addressed as a slave or after it receives a byte.
 */
#define TWISendACK()		(TWCR |= (1<<TWINT)|(1<<TWEN)|(1<<TWEA))
/*
 * FOR MR mode. Resume a transfer, ensure that TWI and interrupts are enabled but DO NOT respond with an ACK if the device is addressed as a slave or after it receives a byte.
 */
#define TWISendNACK()		(TWCR |= (1<<TWINT)|(1<<TWEN)|(1<<TWIE))


// PUBLIC FUNCTIONS//
void TWI_write(u8 data);
void TWI_start();
u8 TWI_getStatus();
void TWI_init();
TWI_Result TWI_masterTransmit(u8* buffer, u16 length, u8 address);
void TWI_slave_W();
u8 TWI_read();
TWI_Result TWI_masterReceive(u8 address , u16 length);
TWI_Status TWI_readEeprom(u8 address ,u16 length, u8 block_byte);
#endif /* TWI_INTERFACE_H_ */
