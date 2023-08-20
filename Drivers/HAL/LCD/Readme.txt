/**********************************************************************/
/*                      Created on: Jul 17, 2023                      */
/*                      Created By: Karim Tarek                       */
/*         LCD DRIVER driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

************************************************************************
*                Please Read this before trying the driver             *
*                                                                      *
************************************************************************


# LCD Driver for Atmega32

This is a simple LCD driver for the Atmega32 microcontroller, designed to interface with a 16x2 LCD display. The driver provides basic functions to initialize the LCD, write characters and strings, set the cursor, and display integer and floating-point numbers.

## Features

- Supports 8-bit and 4-bit interface modes for easy configuration.
- Provides functions to initialize the LCD and clear the display.
- Allows writing characters and strings on the LCD.
- Enables setting the cursor to a specific location on the display.
- Includes a function to display integer numbers with the option to specify decimal places for floating-point numbers.
- Works with Atmega32 and similar microcontrollers.

## Getting Started

1. Clone or download the repository.
2. Include the required files in your project.
3. Configure the driver according to your LCD specifications in `LCD_Config.h`.
4. Use the provided functions in your code to interact with the LCD.

## Usage

- First, initialize the LCD using `LCD_init()` before any other operations.
- Clear the display with `LCD_clear_display()` if needed.
- Write characters or strings using `LCD_write_char()` and `LCD_write_string()`.
- Set the cursor position with `LCD_set_cursor(row, column)`.
- Display integer numbers using `LCD_write_s32_number()`, specifying the number and decimal places.

## Dependencies

- The driver requires `util/delay.h` for delays.
- The MCU's GPIO interface must be properly configured using `DIO_Interface.h`.

## Example

```c
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_Interface.h"

int main() {
    // Initialize the LCD
    LCD_init();

    // Clear the display
    LCD_clear_display();

    // Write a string
    LCD_write_string("Hello, LCD!");

    // Set the cursor to the second row, fourth column
    LCD_set_cursor(1, 3);

    // Display a number with two decimal places
    float number = 3.14159;
    LCD_write_float_with_decimals(number, 2);

    while (1) {
        // Your code here
    }

    return 0;
}
```

## Contributions

Contributions and improvements to the LCD driver are welcome! Feel free to fork the repository, make changes, and submit pull requests.

## License

This LCD driver is released under the MIT License. See `LICENSE` for more details.

For any questions or issues, please feel free to contact me.

Happy coding!