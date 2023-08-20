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



#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_



/* Commands for initialization */

//formating     RS-RW-DB7-DB6-DB5-DB4-DB3-DB2-DB1-DB0

//for function set 8bit  0-0-0-0-1-1-N-F-X-X
// N 0:1 (1 line display - 2 lines display) F 0:1 ( character size 5x7 or 8x10)
#define function_set_8bit 0b00111000

// display ON/OFF control 0-0-0-0-1-D-C-B
// D:1 display on C:0 cursor off B:0 Blinking cursor off
#define display_On 0b00001100
// D:0 for display off
#define display_Off 0b00001000

//clear display
#define clear_Display 0b00000001
// entry mode set    0-0-0-0-0-1-I/D-SH
// I/D :1 increment mode SH:0 NO displat shift operation
#define entry_Mode 0b00000110
//return home
#define return_Home 0b00000010

#define line2_Start 64
#define busy_Flag 7

#define DB0 0
#define DB1 1
#define DB2 2
#define DB3 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7


/* PRIVATE FUNCTIONS DECLARATION */

static void LCD_write_data_8bit(u8 copy_data_8bit);
static void LCD_write_command_8bit(u8 copy_command_8bit);
static void LCD_write_data_4bit(u8 copy_data_4bit);
static void LCD_write_command_4bit(u8 copy_command_4bit);
static void LCD_function_Set_4bit();





#endif /* LCD_PRIVATE_H_ */
