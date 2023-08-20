/*
 * TWI_Program.c
 *
 *  Created on: Aug 7, 2023
 *      Author: karim
 */

#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"
#include <util/delay.h>
#include "../DIO/DIO_Interface.h"

#include "TWI_Interface.h"
#include "TWI_Private.h"

u8 repStart = 0;
//data container
u8* dataBuffer;
u8* RXdataBuffer;

//address container
u8 slave_address;
//block byte for eeprom
u8 blockByte;
// to check if data complete or not we need to track the data using an index variable
// and a length container variable
u16 buffer_Index = 0;
u16 buffer_Len   = 0;

u16 RXbuffer_Index = 0;
u16 RXbufer_len;

TWI_Mode mode = Idle;
TWI_Result result = result_successful;


void TWI_init(){


	TWSR = 0;
	TWBR = 32;
	TWCR |= (1<<TWEN)|(1<<TWIE);

}

u8 TWI_getStatus(){



	volatile u8 result = (TWSR & 0xf8);

		return result;
}

void TWI_start(){

	TWCR |= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

}

void TWI_slave_W(){

	TWDR = (slave_address <<1);
}

void TWI_slave_R(){

	TWDR = ((slave_address <<1) |1);
}

void TWI_write(u8 data){

	TWDR = data;
	TWCR |= (1<<TWINT)|(1<<TWEN);
	SREG |= (1<<7);


}

u8 TWI_read(){

	return TWDR;
}

TWI_Result TWI_masterReceive(u8 address , u16 length){

	TWI_Result status = status_ready;
	if(mode == Idle){
		mode = MasterReciever;
		RXbufer_len = length;
		RXbuffer_Index = 0;
		result = result_waiting;
		slave_address = address;
		TWI_init();
		TWI_start();

	}else{
		status = status_busy;
	}

return status;
}


TWI_Result TWI_masterTransmit(u8* buffer, u16 length, u8 address){

	TWI_Status status = status_ready;
	if(mode == Idle){
		mode = MasterTransmitter;
		dataBuffer = buffer;
		buffer_Len = length;
		buffer_Index = 0;
		result = result_waiting;
		slave_address = address;
		TWI_init();
		TWI_start();

	}else {
		status = status_busy;
	}

	return status;
}


TWI_Status TWI_readEeprom(u8 address ,u16 length, u8 block_byte){

	TWI_Status status = status_ready;
	if(mode == Idle){
		mode = ReadEeprom;
		slave_address = address;
		RXbufer_len = length;
		blockByte = block_byte;
		result  = result_waiting;
		TWI_init();
		TWI_start();
	}else{
		status = status_busy;
	}
return status;



}

void __vector_19(){

switch (mode){

case Idle:
	break;

case MasterReciever:
	switch(TWI_getStatus()){

	case TWI_START_SENT:
		// load slave address + operation (read) into twdr
		TWI_slave_R();
		//TWIResumeTransmit();
		clear_Bit(TWCR,TWSTA);
		break;

	case TWI_REP_START_SENT:
		// load slave address + operation (read) into twdr
		TWI_slave_R();
		//TWIResumeTransmit();
		clear_Bit(TWCR,TWSTA);
		break;


	case TWI_MR_SLAR_ACK:

		if(RXbuffer_Index < RXbufer_len-1){

			TWISendNACK();
		}else{

		TWISendACK();

		}
		break;
	case TWI_MR_SLAR_NACK:
		result = result_No_ack;
		TWISendStop();
		break;

	case TWI_MR_DATA_ACK:
		if(RXbuffer_Index == RXbufer_len){
			result = result_successful;
			TWISendNACK();
		}else{

			RXdataBuffer[RXbuffer_Index++] = TWI_read();

		}

		break;

	case TWI_MR_DATA_NACK:

		result = result_No_ack;
		TWISendStop();
		break;

	case TWI_LOST_ARBIT:

		result = result_lost_Arb;
		TWISendStop();

		break;

	}


	break;

	case SlaveReciever:
		// will be added in the next version

		break;

	case SlaveTransmitter:
		//will be added in the next version

		break;

case ReadEeprom:

	 switch (TWI_getStatus()) {

	        case TWI_START_SENT:
	            // Load slave address + write operation
	            TWI_slave_W();
	            clear_Bit(TWCR, TWSTA);
	            break;

	        case TWI_MT_SLAW_ACK:
	            // Load EEPROM block byte
	            TWI_write(blockByte);
	            break;

	        case TWI_MT_DATA_ACK:
	            // Send repeated start
	            TWI_start();
	            break;

	        case TWI_REP_START_SENT:
	            // Load slave address + read operation
	            TWI_slave_R();
	            clear_Bit(TWCR, TWSTA);
	            break;

	        case TWI_MR_SLAR_ACK:
	            // Read first byte and send ACK
	            RXdataBuffer[RXbuffer_Index++] = TWI_read();
	            TWISendACK();
	            break;

	        case TWI_MR_DATA_ACK:
	            RXdataBuffer[RXbuffer_Index++] = TWI_read();

	            if (RXbuffer_Index == RXbufer_len) {
	                // All data received, send NACK and then STOP
	                TWISendNACK();
	                TWISendStop();
	                result = result_successful;
	            } else {
	                // More data to receive, send ACK for the next byte
	                TWISendACK();
	            }
	            break;


	        case TWI_MR_DATA_NACK:
	            // Read last byte and then send stop condition
	            RXdataBuffer[RXbuffer_Index++] = TWI_read();
	            result = result_successful;
	            TWISendStop();
	            break;
	    }
	break;


case MasterTransmitter:


				switch(TWI_getStatus()){

				case TWI_REP_START_SENT:

					TWI_slave_R();
					clear_Bit(TWCR,TWSTA);
					break;

				case TWI_START_SENT:

				// load slave address in the twdr
				TWI_slave_W();
				// clear the start condition bit
				clear_Bit(TWCR,TWSTA);
				break;

				case TWI_MT_SLAW_ACK:

				//start to load data in the twdr
				TWI_write(dataBuffer[buffer_Index++]);
				// clear flag to go to the next step
				TWIResumeTransmit();
				break;

				case TWI_MT_SLAW_NACK:

				// if slave send NACK
				//change result and stop the frame
				result = result_No_ack;
				TWISendStop();

				break;

				case TWI_MT_DATA_ACK:

				// data handling
				// send data until the end of the buffer
				// if all data sent change result to succesful and send stop condition

				if(buffer_Index == buffer_Len){

					result = result_successful;

					//TWCR |=(1<<TWINT)|(1<<TWSTO);
					TWISendStop();

				}else{

					TWI_write(dataBuffer[buffer_Index++]);

					TWIResumeTransmit();

				}

				break;

				case TWI_MT_DATA_NACK:
				// if all data sent and NACK received
				// change result to successful
				//else result NACK
				if(buffer_Index == buffer_Len){

					result = result_successful;
				}else{

					result = result_No_ack;
				}

				TWISendStop();

				break;

				case TWI_LOST_ARBIT:

				result = result_lost_Arb;
				TWISendStop();
				break;

				}
	break;


}
if(result != result_waiting){
	mode = Idle;
	//TWCR = 0;

}


}
