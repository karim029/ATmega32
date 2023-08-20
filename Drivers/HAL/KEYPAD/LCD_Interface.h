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


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/*
 *  Two modes of interfacing with the LCD
 *  the 8 bit mode (using D0-D7) Pins in the lcd
 *  the 4 bit mode (using D4-D7) Pins only in the lcd
 */
#define interface_8bit 0
#define interface_4bit 1

// YOU CAN SELECT THE DESIRED MODE OF INTERFACE HERE BY CHANGING THE VALUE OF THE MACRO

#define LCD_interface_mode interface_4bit

/* PORT SELECTION */

//the 8 bit mode (using D0-D7) Pins in the lcd
//the 4 bit mode (using D4-D7) Pins only in the lcd

#define lcd_data_port PORTA // Change the data port as you like

#define lcd_control_port PORTB // change the data port as you like

/* CONTROL PINS SELECTION */

/*
 * based on the port you selected, you select the index of the pins you want to use for the control
 */

//enable pin
#define lcd_enable 0
//Read/Write pin
#define lcd_RW 1
//Register Select pin
#define lcd_RS 2

/* functions decleration for user to use */
void LCD_init();
void LCD_clear_display();
void LCD_write_char(u8 copy_u8_char);
void LCD_write_string(u8* Copy_pu8_str);
void LCD_set_cursor(u8 copy_u8_row , u8 copy_u8_Column);
void LCD_on();
void LCD_off();
void LCD_clear_display();
void LCD_write_number(s32 copy_s32_number);
void LCD_write_float(f32 copy_f32_number, u8 copy_decimal_point);

#endif /* LCD_INTERFACE_H_ */
