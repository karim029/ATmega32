# KEYPAD Driver

This is a keypad driver for the Atmega32 microcontroller, written in C language. It provides functions to interact with a 4x4 keypad matrix.

## Table of Contents

- [Introduction](#introduction)
- [Port Configuration](#port-configuration)
- [Driver Functions](#driver-functions)
- [Usage](#usage)
- [Author](#author)

## Introduction

The keypad driver is designed to work with a 4x4 matrix keypad. The driver provides functions to initialize the keypad, read the pressed key, and map the key index to its corresponding value.

## Port Configuration

The driver requires the user to configure the ports and pins used for the keypad. The port and pin configuration can be done in the `KEYPAD_Config.h` file. In this file, you can define the number of rows and columns in the keypad, as well as the specific port and pin used for each row and column.

```c
// KEYPAD_Config.h

#define col_Number 4
#define row_Number 4
#define KPD_size (col_Number * row_Number)

// Column pins
#define col_Port PORTC
#define col_0 PIN0
#define col_1 PIN1
#define col_2 PIN2
#define col_3 PIN3

// Row pins
#define row_Port PORTD
#define row_0 PIN0
#define row_1 PIN1
#define row_2 PIN2
#define row_3 PIN3
```

## Driver Functions

The keypad driver provides the following functions:

- `void KPD_Active_Col_init()`: Initializes the keypad by setting the column pins as outputs and the row pins as inputs with internal pull-up resistors.

- `void KPD_read_key(u8* copy_u8_key)`: Reads the state of the keypad and stores it in the given array `copy_u8_key`. Each element in the array corresponds to the state of a specific key on the keypad.

- `u8 KPD_get_key(u8* copy_u8_key)`: Maps the index of the array of elements with low value to its corresponding key on the 4x4 keypad and returns the key value.

## Usage

1. Configure the ports and pins used for the keypad in `KEYPAD_Config.h`.

2. Include the necessary files in your project:

   - `KEYPAD_Interface.h`
   - `KEYPAD_Config.h`
   - `KEYPAD_Private.h`

3. Call the `KPD_Active_Col_init()` function to initialize the keypad before reading any keys.

4. Create an array to store the keypad state, and call `KPD_read_key()` to read the state of the keypad and store it in the array.

5. Call `KPD_get_key()` function to get the pressed key value based on the keypad state array.

## Author

This keypad driver was created by Karim Tarek on Jul 21, 2023.

## License

This driver is released under the MIT License. You are free to modify and distribute it as needed. Please see the `LICENSE` file for more details.