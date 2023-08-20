/**********************************************************************/
/*                      Created on: Jul 18, 2023                      */
/*                      Created By: Karim Tarek                       */
/*                LCD driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/


//Standard libs
#include<util/delay.h>
#include "../Libraries/bit_calc.h"
#include "../Libraries/STD_Types.h"

//Driver lib
#include "../Drivers/MCAL/DIO/DIO_Interface.h"

//private libs
#include "../Drivers/HAL/LCD/LCD_Config.h"
#include "LCD_Interface.h"
#include "../Drivers/HAL/LCD/LCD_Private.h"


static void array_Swap(u8* copy_pu8_arr, u8 copy_length){

	/* function that reverse the order of the array used inside the lcd driver functions
	 *
	 *  the function takes 2 inputs the array (Recieved as a pointer pointing to the first element of the array
	 *  and the length of the array
	 *
	 *  the function doesn't return anything it manipulates the passed array
	 *
	 *
	 */


	u8 start = 0;
	u8 end = copy_length - 1;

	while(start < end){

		u8 temp = copy_pu8_arr[start];
		copy_pu8_arr[start] = copy_pu8_arr[end];
		copy_pu8_arr[end] = temp;

		start++;
		end--;
	}




}

s32 power_10(u8 power){
	/*
	 *  helper function for the functionality of the driver
	 *
	 *  this function only calculates the power ex 10^2 used for printing the floating numbers
	 *  on lcd
	 *
	 * do you not use this function outside this driver
	 *
	 */

	s32 result = 1;

	while(power > 0){

		result *= 10;
		power--;
	}

	return result;
}

/* 8bit mode functions */


static void LCD_write_data_8bit(u8 copy_data_8bit){
	/*
	 *  Function set up the control pins and the sequence to write data in the data register
	 *
	 *  INPUT: 8bit data
	 *  OUTPUT: NONE
	 *
	 *  function will only be used inside this source file
	 *  do you not use it in your code!
	 *
	 */

	DIO_void_set_pin(lcd_control_port, lcd_RS); // set RS pin high select data register
	DIO_void_clear_pin(lcd_control_port, lcd_RW); // clear RW pin  0 for writing operation

	_delay_us(50);
	//enable pin high
	DIO_void_set_pin(lcd_control_port, lcd_enable);
	_delay_us(50);
	//send data to the entire port


	DIO_void_clear_pin(lcd_control_port, lcd_enable);


}

static void LCD_write_command_8bit(u8 copy_command_8bit){
	/*
		 *  Function set up the control pins and the sequence to write command in the instruction register
		 *
		 *  INPUT: 8bit command
		 *  OUTPUT: NONE
		 *
		 *  function will only be used inside this source file
		 *  do you not use it in your code!
		 *
		 */
	DIO_void_clear_pin(lcd_control_port, lcd_RS); // clear the RS pin to select instruction register
	DIO_void_clear_pin(lcd_control_port, lcd_RW); // clear RW pin  0 for writing operation

	_delay_us(1);
	//enable pin high
	DIO_void_set_pin(lcd_control_port, lcd_enable);
	_delay_us(1);
	//send command to the entire port
	DIO_void_assign_port(lcd_data_port, copy_command_8bit);
	//enable pin low
	DIO_void_clear_pin(lcd_control_port, lcd_enable);

}


/* 4bit mode functions */

static void LCD_write_data_4bit(u8 copy_data_4bit){


	/*
		 *  Function set up the control pins and the sequence to write data in the data register
		 *	this function is for the 4bit initialization and interfacing
		 *  INPUT: 8bit command
		 *  OUTPUT: NONE
		 *
		 *  function will only be used inside this source file
		 *  do you not use it in your code!
		 *
		 */

	DIO_void_set_pin(lcd_control_port, lcd_RS); // set RS pin high select data register
	DIO_void_clear_pin(lcd_control_port, lcd_RW); // clear RW pin  0 for writing operation

	_delay_us(1);
	//enable pin high
	DIO_void_set_pin(lcd_control_port, lcd_enable);
	_delay_us(1);
	// send the higher nibble

	/*
	 *  NOTE!!!!!
	 *  this function is configured that the connection in the case of 4 bit
	 *  is from P4-P7 of the MCU to DB4-DB7 of the LCD
	 *  any change in this sequence will result in a wrong behavior
	 *  i will try to make it more generic in the next versions
	 *
	 */

	for(u8 i = 4; i < 8; i++){

		DIO_void_assign_pin(lcd_data_port, i, get_Bit(copy_data_4bit,i));
		// the for loop assigns the data value in the function input
		// by starting by the most significant 4 bits b4-b7

	}
	// set enable to low to send the lower nibble
	DIO_void_clear_pin(lcd_control_port, lcd_enable);
	//delay to smooth things out
	_delay_us(10);
	//enable HIGH
	DIO_void_set_pin(lcd_control_port, lcd_enable);
	_delay_us(1);
	//send lower nibble
	for(u8 i = 4; i < 8; i++){

			DIO_void_assign_pin(lcd_data_port, i, get_Bit(copy_data_4bit,i-4));
			// the for loop assigns the data value in the function input
			// by starting by the least significant 4 bits b0-b3

		}
	//enable low
	DIO_void_clear_pin(lcd_control_port, lcd_enable);


}

static void LCD_write_command_4bit(u8 copy_command_4bit){


	/*
		 *  Function set up the control pins and the sequence to write command in the instruction register
		 *	this function is for the 4bit initialization and interfacing
		 *  INPUT: 8bit command
		 *  OUTPUT: NONE
		 *
		 *  function will only be used inside this source file
		 *  do you not use it in your code!
		 *
		 */

	DIO_void_clear_pin(lcd_control_port, lcd_RS); // set RS pin high select data register
	DIO_void_clear_pin(lcd_control_port, lcd_RW); // clear RW pin  0 for writing operation

	_delay_us(1);
	//enable pin high
	DIO_void_set_pin(lcd_control_port, lcd_enable);
	_delay_us(1);
	// send the higher nibble

	/*
	 *  NOTE!!!!!
	 *  this function is configured that the connection in the case of 4 bit
	 *  is from P4-P7 of the MCU to DB4-DB7 of the LCD
	 *  any change in this sequence will result in a wrong behavior
	 *  i will try to make it more generic in the next versions
	 *
	 */

	for(u8 i = 4; i < 8; i++){

		DIO_void_assign_pin(lcd_data_port, i, get_Bit(copy_command_4bit,i));
		// the for loop assigns the data value in the function input
		// by starting by the most significant 4 bits b4-b7

	}
	// set enable to low to send the lower nibble
	DIO_void_clear_pin(lcd_control_port, lcd_enable);
	//delay to smooth things out
	_delay_us(10);
	//enable HIGH
	DIO_void_set_pin(lcd_control_port, lcd_enable);
	_delay_us(1);
	//send lower nibble
	for(u8 i = 4; i < 8; i++){

			DIO_void_assign_pin(lcd_data_port, i, get_Bit(copy_command_4bit,i-4));
			// the for loop assigns the data value in the function input
			// by starting by the least significant 4 bits b0-b3

		}
	//enable low
	DIO_void_clear_pin(lcd_control_port, lcd_enable);


}

static void LCD_function_Set_4bit(){

	/*
			 *  Function set up the control pins and the sequence to write command in the instruction register
			 *	this function is for the 4bit initialization and interfacing
			 *  INPUT: 8bit command
			 *  OUTPUT: NONE
			 *
			 *
			 *
			 *  function will only be used inside this source file
			 *  do you not use it in your code!
			 *
			 */



	DIO_void_clear_pin(lcd_control_port, lcd_RS);// RS:0 to select instruction register
	DIO_void_clear_pin(lcd_control_port, lcd_RW);// RW:0 write operation
	_delay_us(1);
	DIO_void_set_pin(lcd_control_port, lcd_enable); // enable high
	_delay_us(1);
	//send the high nibble

	for(u8 i=0; i<4;i++){

		DIO_void_assign_pin(lcd_data_port, i+4, get_Bit(0b0010,i));
	}
	//enable pin low
	DIO_void_clear_pin(lcd_control_port, lcd_enable);
	_delay_us(10);
	//send again high nibble to make sure
	DIO_void_set_pin(lcd_control_port, lcd_enable); // enable high
	_delay_us(1);
	//send the high nibble

	for(u8 i=0; i<4;i++){

		DIO_void_assign_pin(lcd_data_port, i+4, get_Bit(0b0010,i));
	}
	//enable pin low
	DIO_void_clear_pin(lcd_control_port, lcd_enable);
	_delay_us(10);
	//send the low nibble
	DIO_void_set_pin(lcd_control_port, lcd_enable); // enable high
	_delay_us(1);
	//send the high nibble

	for(u8 i=0; i<4;i++){

		DIO_void_assign_pin(lcd_data_port, i+4, get_Bit(0b1000,i));
	}
	//enable pin low
	DIO_void_clear_pin(lcd_control_port, lcd_enable);
	_delay_us(10);

}



/* Driver features functions for the user */

void LCD_init(){

	/*
	 * this function initiate the interfacing of the lcd
	 * based on the specs configured in the lcd_config.h file
	 * the function supports the 2 modes 4bit init and 8bit init
	 *
	 *        user can use this function in his code
	 *        editing this function can result in unexpected behaviors
	 *        so be careful!
	 *
	 */

#if LCD_interface_mode == interface_8bit

	// configure the data pins direction
	DIO_void_set_port_dir(lcd_data_port, PORT_MAX);
	// RS,RW,E as  output
	DIO_void_set_pin_dir(lcd_control_port, lcd_RS, OUTPUT);
	DIO_void_set_pin_dir(lcd_control_port, lcd_RW, OUTPUT);
	DIO_void_set_pin_dir(lcd_control_port, lcd_enable, OUTPUT);
	//wait > 30 ms
	_delay_ms(50);
	LCD_write_command_8bit(function_set_8bit);
	// wait > 39 us
	_delay_us(50);
	LCD_write_command_8bit(display_On);
	// wait > 39 us
	_delay_us(50);
	LCD_write_command_8bit(clear_Display);
	// wait > 1.53 ms
	_delay_ms(2);

	//LCD_write_command_8bit(entry_Mode);



#elif LCD_interface_mode == interface_4bit


	// configure data pins direction
	DIO_void_set_pin_dir(lcd_data_port, B7, OUTPUT);
	DIO_void_set_pin_dir(lcd_data_port, B6, OUTPUT);
	DIO_void_set_pin_dir(lcd_data_port, B5, OUTPUT);
	DIO_void_set_pin_dir(lcd_data_port, B4, OUTPUT);
	// RS,RW,E as  output
	DIO_void_set_pin_dir(lcd_control_port, lcd_RS, OUTPUT);
	DIO_void_set_pin_dir(lcd_control_port, lcd_RW, OUTPUT);
	DIO_void_set_pin_dir(lcd_control_port, lcd_enable, OUTPUT);
	//wait for
	_delay_ms(50);
	// init 4bit
	LCD_function_Set_4bit();
	// wait > 30 us
	_delay_us(50);
	LCD_write_command_4bit(display_On);
	// wait > 30 us
	_delay_us(50);
	LCD_write_command_4bit(clear_Display);
	// wait > 1.53 ms
	_delay_ms(2);
//	LCD_write_data_4bit(entry_Mode);

#endif

}

void LCD_set_cursor(u8 copy_u8_row , u8 copy_u8_Column){
	/*
	 * this function gives the user the freedom to set the location for writing
	 * and not using the incrementing method
	 * the function takes two argument row (0,1) and column (0,15)
	 * line two starts at 64
	 * the equation is based on the 16x2 lcd if the lcd used is different the equation will provide
	 * wrong values **** these values are based on the ddram address for each location ***
	 *
	 *
	 */

#if LCD_interface_mode == interface_8bit

	u8 loc_Address = 128+(copy_u8_row*line2_Start)+(copy_u8_Column);
	LCD_write_command_8bit(loc_Address);
	//delay to smooth things out
	_delay_us(50);

#elif LCD_interface_mode == interface_4bit

	u8 loc_Address = 128+(copy_u8_row*line2_Start)+(copy_u8_Column);
		LCD_write_command_4bit(loc_Address);
		//delay to smooth things out
		_delay_us(50);


#endif



}

void LCD_on(){

	/* this function turn on the backlight of the LCD
	 *
	 *
	 *
	 */

#if LCD_interface_mode == interface_8bit

	LCD_write_command_8bit(display_On);
	_delay_us(50);

#elif LCD_interface_mode == interface_4bit

	LCD_write_command_4bit(display_On);
	_delay_us(50);

#endif


}

void LCD_off(){

	/* this function turn off the backlight of the LCD
	 *
	 *
	 *
	 */

#if LCD_interface_mode == interface_8bit

	LCD_write_command_8bit(display_Off);
	_delay_us(50);

#elif LCD_interface_mode == interface_4bit

	LCD_write_command_4bit(display_Off);
	_delay_us(50);

#endif


}

void LCD_clear_display(){


	/*
	 * this function clears the display of the lcd and returns to the first position on the display
	 * the function doesn't take any inputs and doesnt return anything
	 *
	 *
	 */
#if LCD_interface_mode == interface_8bit
	LCD_write_command_8bit(clear_Display);
	//wait more than 1.53 ms
	_delay_ms(2);
	//return home
	LCD_write_command_8bit(return_Home);
	_delay_ms(2);

#elif LCD_interface_mode == interface_4bit
	LCD_write_command_4bit(clear_Display);
	//wait more than 1.53 ms
	_delay_ms(2);
	//return home
	LCD_write_command_4bit(return_Home);
	// wait more han 1.53 ms
	_delay_ms(2);
#endif


}

void LCD_write_char(u8 copy_u8_char){

	/* this function takes a character as an input
	 * this function takes the character and send it to the lcd
	 * the function doesn't return anything
	 *
	 *
	 */

#if LCD_interface_mode == interface_8bit
	//send character
	LCD_write_data_8bit(copy_u8_char);
	// wait more than 39 us
	_delay_us(50);
#elif LCD_interface_mode == interface_4bit
	// send character
	LCD_write_data_4bit(copy_u8_char);
	_delay_us(50);
#endif

}


void LCD_write_string(u8* Copy_pu8_str){

	/*
	 *
	 * this function takes a pointer to a string u8
	 * and send it to the lcd to write on it the desired string
	 *
	 */

	u8 i = 0;

	while(Copy_pu8_str[i] != '\0'){

		LCD_write_char(Copy_pu8_str[i]);
		i++;
	}

}


void LCD_write_number(s32 copy_s32_number){

	/* the function writes a number on the lcd
	 * it handle many cases depending on the user input
	 *
	 * 1) 0 case
	 * 2) negative number case
	 * 3)positive numbers (multiple digits)
	 *
	 *
	 */
	// if number is 0

	if(copy_s32_number == 0){

		LCD_write_char('0');
		//negative number
	}else if(copy_s32_number < 0){

		LCD_write_char('-');
		//convert the number to the absolute value
		copy_s32_number *= -1;

	}
	if(copy_s32_number > 0){
	//container to store the number
	u8 numbers[10];
	u8 i = 0;

	while(copy_s32_number != 0){

		//retreive the last digit from the number
		numbers[i] = copy_s32_number%10;
		copy_s32_number /= 10;
		i++;
	}

	// reverse array order
	array_Swap(numbers, i);

	// print the correct order of the number
	for(u8 j = 0; j < i; j++){

		LCD_write_char(numbers[j]+'0');
	}

	}
}

void LCD_write_float(f32 copy_f32_number, u8 copy_decimal_point){


	/* function used to print any floating number on the lcd
	 *
	 * takes 2 input the number itself and the decimal point
	 *
	 * ex number 2.3453 and decimal point = 2
	 *
	 * the number printed will be 2.34
	 *
	 * the function doesn't return anything
	 *
	 */

	// store the integer part
	s32 int_value = (s32)copy_f32_number;

	// store the decimal part
	s32 float_value = (s32)((copy_f32_number -(f32)int_value)*power_10(copy_decimal_point));

	// print the int part
	LCD_write_number(int_value);
	//print the floating point
	LCD_write_char('.');
	//print the decimal part
	if(float_value > 0 ){
	LCD_write_number(float_value);
	}else{
	LCD_write_number((float_value * -1));

	}


}






