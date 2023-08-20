/**********************************************************************/
/*                      Created on: Jul 16, 2023                      */
/*                      Created By: Karim Tarek                       */
/*        Digital i/0 driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

/* Standard Library */

#include "../../../Libraries/bit_calc.h"
#include "../../../Libraries/STD_Types.h"

/* Private libraries */

#include "../DIO/DIO_Interface.h"
#include "../DIO/DIO_Registers.h"

// pointer for callback func



/* Global Variables */
static volatile u8* DIO_PINx[4] = {DIO_PINA, DIO_PINB, DIO_PINC, DIO_PIND};
static volatile u8* DIO_DDRx[4] = {DIO_DDRA, DIO_DDRB, DIO_DDRC, DIO_DDRD};
static volatile u8* DIO_PORTx[4] = {DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD};



/* implementing the driver functions  */
/* set Portx Direction Function       */

void DIO_void_set_port_dir(u8 copy_u8_portID, u8 port_copy_dir){

	/* the function takes 2 parameters the portID and the user desired direction
	 *
	 *  copy_u8_portID -->> PORTA --> 0 // PORTB --> 1 // PORTC --> 2 // PORTD --> 3
	 *
	 *  port_copy_dir takes the value for the whole port you can use decimal 0-255
	 *  or hexadecimal or binary ex: 0b11100000 or use the macro predfined MAX_port
	 *  for the whole port to be output
	 *  Also general rule INPUT --> 0 // OUTPUT --> 1
	 *
	 *
	 */

	*(DIO_DDRx[copy_u8_portID]) = port_copy_dir;

}

void DIO_void_set_pin_dir(u8 copy_u8_portID, u8 copy_u8_pinID, u8 pin_copy_dir){

	/*  the function works like the one before it however this gives you an extra
	 *  option if you want a specific pin in the port to be an input or an output
	 *
	 *  pin_copy_dir using the predefined macro INPUT //OUTPUT
	 *
	 *
	 */

	assign_Bit(*(DIO_DDRx[copy_u8_portID]),copy_u8_pinID,pin_copy_dir);

}

void DIO_void_port_pullup(u8 copy_u8_portID){

	/*  the function only takes 1 parameter which is the portID
	 *
	 *  the atmega32 has an internal pullup resistor that you can use
	 *  so that is what the function does
	 *  using the pullup for any button prevents the floating effect
	 *
	 *
	 */
	*(DIO_DDRx[copy_u8_portID]) = INPUT;
	*(DIO_PORTx[copy_u8_portID]) = PORT_MAX;
}

void DIO_void_pin_pullup(u8 copy_u8_portID, u8 copy_u8_pinID){

	/*  the function works as the one that set pullup for the whole port
	 *
	 *
	 */

	clear_Bit(*(DIO_DDRx[copy_u8_portID]),copy_u8_pinID);
	set_Bit(*(DIO_PORTx[copy_u8_portID]),copy_u8_pinID);

}

void DIO_void_set_port(u8 copy_u8_portID){

	/* this functions set the entire port to high
	 *
	 *
	 */



	*(DIO_PORTx[copy_u8_portID]) = PORT_MAX;

}

void DIO_void_clear_port(u8 copy_u8_portID){

	/* this function set the entire port to low
	 *
	 *
	 */


	*(DIO_PORTx[copy_u8_portID]) = LOW;

}

void DIO_void_assign_port(u8 copy_u8_portID, u8 copy_value){

	/* this function assigns a value in decimal or binary or hexa for the entire 8 pins of the port
	 *
	 * ex: 0b11100110
	 *
	 */



	*(DIO_PORTx[copy_u8_portID]) = copy_value;

}

void DIO_void_toggle_port(u8 copy_u8_portID){

	/* this function toggle the entire port
	 *
	 *
	 */


	*(DIO_PORTx[copy_u8_portID]) ^= PORT_MAX;
}

void DIO_void_set_pin(u8 copy_u8_portID , u8 copy_u8_pinID){

	/* this function set the desired pin to high
	 *
	 *
	 */


	set_Bit(*(DIO_PORTx[copy_u8_portID]),copy_u8_pinID);
}

void DIO_void_clear_pin(u8 copy_u8_portID , u8 copy_u8_pinID){

	/* this function set the desired pin to low
	 *
	 *
	 */


	clear_Bit(*(DIO_PORTx[copy_u8_portID]),copy_u8_pinID);
}

void DIO_void_assign_pin(u8 copy_u8_portID,u8 copy_u8_pinID ,u8 copy_value){

	/* this function assign a value to a specific pin in a specific port
	 *
	 * ex portA pin0 HIGH
	 *
	 */



	assign_Bit(*(DIO_PORTx[copy_u8_portID]),copy_u8_pinID,copy_value);
}

void DIO_void_toggle_pin(u8 copy_u8_portID , u8 copy_u8_pinID){

	/* this function toggle a specific bit in a specific port
	 *
	 *
	 */


	toggle_Bit(*(DIO_PORTx[copy_u8_portID]),copy_u8_pinID);

}

u8 DIO_u8_get_port(u8 copy_u8_portID){

	/* this function reads the value in the entire port
	 * used commonly for inputs to read the value
	 * the function returns the value read in the entire port
	 *  1 byte data
	 */



	return *(DIO_PINx[copy_u8_portID]);
}

u8 DIO_u8_get_pin(u8 copy_u8_portID, u8 copy_u8_pinID){

	/* this functions read the value from a specific pin
	 * and return the read value
	 * also 1 byte
	 *
	 *
	 */


	return get_Bit(*(DIO_PINx[copy_u8_portID]),copy_u8_pinID);
}



