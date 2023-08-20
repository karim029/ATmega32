/*
 * SPI_Program.c
 *
 *  Created on: Aug 3, 2023
 *      Author: karim
 */


//STD LIB
#include "../../../Libraries/bit_calc.h"
#include "../../../Libraries/STD_Types.h"

//MCAL
#include "../DIO/DIO_Interface.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"
#include "SPI_Private.h"

void(*ptr_callback_function)(void) = NULL;

void set_Callback_function(void(*ptr_function)(void)){

	ptr_callback_function = ptr_function;

}

void SPI_masterInit(){

	// set pin direction for master

	//slave select pin
	DIO_void_set_pin_dir(SPI_REF_PORT, SS, OUTPUT);
	// MOSI pin
	DIO_void_set_pin_dir(SPI_REF_PORT, MOSI, OUTPUT);
	// MISO pin
	DIO_void_set_pin_dir(SPI_REF_PORT, MISO, INPUT);



#if SPI_Interrupt == Enable
	// enable SPI interrupt
	SPCR |= (1<<SPIE);
	SREG |= (1<<7); // enable global interrupt

#endif

#if Data_Order == MSB

	clear_Bit(SPCR,DORD);
#else
	SPCR |= (1<<DORD);

#endif

#if Leading_Edge_Pol == Rising

	clear_Bit(SPCR,CPOL);
#else
	set_Bit(SPCR,CPOL);
#endif

#if Leading_Edge_Phase == sample

	clear_Bit(SPCR,CPHA);
#else
	set_Bit(SPCR,CPHA);
#endif

#if SCK_FREQ == freq_16
	clear_Bit(SPSR,SPI2X);
	clear_Bit(SPCR,SPR1);
	set_Bit(SPCR,SPR0);
#elif SCK_FREQ == freq_4
	clear_Bit(SPSR,SPI2X);
	clear_Bit(SPCR,SPR1);
	clear_Bit(SPCR,SPR0);
#elif SCK_FREQ == freq_64
	clear_Bit(SPSR,SPI2X);
	set_Bit(SPCR,SPR1);
	clear_Bit(SPCR,SPR0);
#elif SCK_FREQ	== freq_128
	clear_Bit(SPSR,SPI2X);
	set_Bit(SPCR,SPR1);
	set_Bit(SPCR,SPR0);
#elif SCK_FREQ == freq_2
	set_Bit(SPSR,SPI2X);
	clear_Bit(SPCR,SPR1);
	clear_Bit(SPCR,SPR0);
#elif SCK_FREQ == freq_8
	set_Bit(SPSR,SPI2X);
	clear_Bit(SPCR,SPR1);
	set_Bit(SPCR,SPR0);
#elif SCK_FREQ == freq_32
	set_Bit(SPSR,SPI2X);
	set_Bit(SPCR,SPR1);
	clear_Bit(SPCR,SPR0);
#elif SCK_FREQ == freq_64_double_Speed
	set_Bit(SPSR,SPI2X);
	set_Bit(SPCR,SPR1);
	set_Bit(SPCR,SPR0);
#endif

#if double_Speed == Enable
	set_Bit(SPSR,SPI2X);
#endif
	//select master

	set_Bit(SPCR,MSTR);

	//enable SPI
	set_Bit(SPCR,SPE);

}



void SPI_slaveInit(){

	//configure pin for the slave
	//ss
	DIO_void_set_pin_dir(SPI_REF_PORT, SS, INPUT);
	// MISO
	DIO_void_set_pin_dir(SPI_REF_PORT, MISO,OUTPUT);
	//MOSI
	DIO_void_set_pin_dir(SPI_REF_PORT, MOSI,INPUT);


#if SPI_Interrupt == Enable
	// enable SPI interrupt
		SPCR |= (1<<SPIE);
		SREG |= (1<<7); // enable global interrupt
#endif

#if Data_Order == MSB

	clear_Bit(SPCR,DORD);
#else
	SPCR |= (1<<DORD);

#endif

#if Leading_Edge_Pol == Rising

	clear_Bit(SPCR,CPOL);
#else
	set_Bit(SPCR,CPOL);
#endif

#if Leading_Edge_Phase == sample

	clear_Bit(SPCR,CPHA);
#else
	set_Bit(SPCR,CPHA);
#endif


	// select slave
	clear_Bit(SPCR,MSTR);
	//enable spi
	set_Bit(SPCR,SPE);


}


u8 SPI_Tranciever(u8 data){

	/*
	 *  function that transmit and recieve from master/slaves
	 *
	 *
	 */
#if SPI_Interrupt == Enable

	SPDR = data;

#else
	SPDR = data;
	while(get_Bit(SPSR,SPIF)==0); // check for transmission complete flag

		return SPDR;

#endif

}


void __vector_12(){

	if(ptr_callback_function != NULL){

		ptr_callback_function();
	}

}
