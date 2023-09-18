#include <util/delay.h>
#include "../Libraries/bit_calc.h"
#include "../Libraries/STD_Types.h"
#include "../Drivers/MCAL/DIO/DIO_Interface.h"
#include "../Drivers/HAL/LCD/LCD_Config.h"
#include "LCD_Interface.h"
#include "../Drivers/HAL/LCD/LCD_Private.h"

static void array_Swap(u8* arr, u8 length) {
    u8 start = 0;
    u8 end = length - 1;

    while (start < end) {
        u8 temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

static s32 power_10(u8 power) {
    s32 result = 1;

    while (power > 0) {
        result *= 10;
        power--;
    }

    return result;
}

#if LCD_interface_mode == interface_8bit
static void LCD_write_data_8bit(u8 data_8bit) {
    DIO_void_set_pin(lcd_control_port, lcd_RS);
    DIO_void_clear_pin(lcd_control_port, lcd_RW);
    _delay_us(50);

    DIO_void_set_pin(lcd_control_port, lcd_enable);
    _delay_us(50);

    DIO_void_assign_port(lcd_data_port, data_8bit);

    DIO_void_clear_pin(lcd_control_port, lcd_enable);
}

static void LCD_write_command_8bit(u8 command_8bit) {
    DIO_void_clear_pin(lcd_control_port, lcd_RS);
    DIO_void_clear_pin(lcd_control_port, lcd_RW);
    _delay_us(1);

    DIO_void_set_pin(lcd_control_port, lcd_enable);
    _delay_us(1);

    DIO_void_assign_port(lcd_data_port, command_8bit);

    DIO_void_clear_pin(lcd_control_port, lcd_enable);
}
#endif

#if LCD_interface_mode == interface_4bit
static void LCD_write_data_4bit(u8 data_4bit) {
    DIO_void_set_pin(lcd_control_port, lcd_RS);
    DIO_void_clear_pin(lcd_control_port, lcd_RW);
    _delay_us(1);

    DIO_void_set_pin(lcd_control_port, lcd_enable);
    _delay_us(1);

    for (u8 i = 4; i < 8; i++) {
        DIO_void_assign_pin(lcd_data_port, i, get_Bit(data_4bit, i));
    }

    DIO_void_clear_pin(lcd_control_port, lcd_enable);
    _delay_us(10);

    DIO_void_set_pin(lcd_control_port, lcd_enable);
    _delay_us(1);

    for (u8 i = 4; i < 8; i++) {
        DIO_void_assign_pin(lcd_data_port, i, get_Bit(data_4bit, i - 4));
    }

    DIO_void_clear_pin(lcd_control_port, lcd_enable);
}

static void LCD_write_command_4bit(u8 command_4bit) {
    DIO_void_clear_pin(lcd_control_port, lcd_RS);
    DIO_void_clear_pin(lcd_control_port, lcd_RW);
    _delay_us(1);

    DIO_void_set_pin(lcd_control_port, lcd_enable);
    _delay_us(1);

    for (u8 i = 4; i < 8; i++) {
        DIO_void_assign_pin(lcd_data_port, i, get_Bit(command_4bit, i));
    }

    DIO_void_clear_pin(lcd_control_port, lcd_enable);
    _delay_us(10);

    DIO_void_set_pin(lcd_control_port, lcd_enable);
    _delay_us(1);

    for (u8 i = 4; i < 8; i++) {
        DIO_void_assign_pin(lcd_data_port, i, get_Bit(command_4bit, i - 4));
    }

    DIO_void_clear_pin(lcd_control_port, lcd_enable);
}


static void LCD_function_Set_4bit() {
    u8 data[] = { 0b0010, 0b0010, 0b1000 };

    DIO_void_clear_pin(lcd_control_port, lcd_RS);
    DIO_void_clear_pin(lcd_control_port, lcd_RW);
    _delay_us(1);

    for (u8 step = 0; step < 3; step++) {
        DIO_void_set_pin(lcd_control_port, lcd_enable);
        _delay_us(1);

        for (u8 i = 0; i < 4; i++) {
            DIO_void_assign_pin(lcd_data_port, i + 4, get_Bit(data[step], i));
        }

        DIO_void_clear_pin(lcd_control_port, lcd_enable);
        _delay_us(10);
    }
}

#endif

void LCD_init() {
#if LCD_interface_mode == interface_8bit
    DIO_void_set_port_dir(lcd_data_port, PORT_MAX);
    DIO_void_set_pin_dir(lcd_control_port, lcd_RS, OUTPUT);
    DIO_void_set_pin_dir(lcd_control_port, lcd_RW, OUTPUT);
    DIO_void_set_pin_dir(lcd_control_port, lcd_enable, OUTPUT);
    _delay_ms(50);
    LCD_write_command_8bit(function_set_8bit);
    _delay_us(50);
    LCD_write_command_8bit(display_On);
    _delay_us(50);
    LCD_write_command_8bit(clear_Display);
    _delay_ms(2);
#elif LCD_interface_mode == interface_4bit
    DIO_void_set_pin_dir(lcd_data_port, B7, OUTPUT);
    DIO_void_set_pin_dir(lcd_data_port, B6, OUTPUT);
    DIO_void_set_pin_dir(lcd_data_port, B5, OUTPUT);
    DIO_void_set_pin_dir(lcd_data_port, B4, OUTPUT);
    DIO_void_set_pin_dir(lcd_control_port, lcd_RS, OUTPUT);
    DIO_void_set_pin_dir(lcd_control_port, lcd_RW, OUTPUT);
    DIO_void_set_pin_dir(lcd_control_port, lcd_enable, OUTPUT);
    _delay_ms(50);
    LCD_function_Set_4bit();
    _delay_us(50);
    LCD_write_command_4bit(display_On);
    _delay_us(50);
    LCD_write_command_4bit(clear_Display);
    _delay_ms(2);
#endif
}

void LCD_set_cursor(u8 row, u8 column) {
    u8 loc_Address = 128 + (row * line2_Start) + column;
#if LCD_interface_mode == interface_8bit
    LCD_write_command_8bit(loc_Address);
    _delay_us(50);
#elif LCD_interface_mode == interface_4bit
    LCD_write_command_4bit(loc_Address);
    _delay_us(50);
#endif
}

void LCD_on() {
#if LCD_interface_mode == interface_8bit
    LCD_write_command_8bit(display_On);
    _delay_us(50);
#elif LCD_interface_mode == interface_4bit
    LCD_write_command_4bit(display_On);
    _delay_us(50);
#endif
}

void LCD_off() {
#if LCD_interface_mode == interface_8bit
    LCD_write_command_8bit(display_Off);
    _delay_us(50);
#elif LCD_interface_mode == interface_4bit
    LCD_write_command_4bit(display_Off);
    _delay_us(50);
#endif
}

void LCD_clear_display() {
#if LCD_interface_mode == interface_8bit
    LCD_write_command_8bit(clear_Display);
    _delay_ms(2);
    LCD_write_command_8bit(return_Home);
    _delay_ms(2);
#elif LCD_interface_mode == interface_4bit
    LCD_write_command_4bit(clear_Display);
    _delay_ms(2);
    LCD_write_command_4bit(return_Home);
    _delay_ms(2);
#endif
}

void LCD_write_char(u8 character) {
#if LCD_interface_mode == interface_8bit
    LCD_write_data_8bit(character);
    _delay_us(50);
#elif LCD_interface_mode == interface_4bit
    LCD_write_data_4bit(character);
    _delay_us(50);
#endif
}

void LCD_write_string(u8* str) {
    u8 i = 0;

    while (str[i] != '\0') {
        LCD_write_char(str[i]);
        i++;
    }
}

void LCD_write_number(s32 number) {
    if (number == 0) {
        LCD_write_char('0');
    } else if (number < 0) {
        LCD_write_char('-');
        number *= -1;
    }

    if (number > 0) {
        u8 digits[10];
        u8 i = 0;

        while (number != 0) {
            digits[i] = number % 10;
            number /= 10;
            i++;
        }

        array_Swap(digits, i);

        for (u8 j = 0; j < i; j++) {
            LCD_write_char(digits[j] + '0');
        }
    }
}

void LCD_write_float(f32 number, u8 decimal_point) {
s32 int_part = (s32)number;
s32 float_part = (s32)((number - (f32)int_part) * power_10(decimal_point));

LCD_write_number(int_part);
LCD_write_char('.');

if (float_part > 0) {
	LCD_write_number(float_part);
} else {
LCD_write_number(float_part * -1);
}
}
