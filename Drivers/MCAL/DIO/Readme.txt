# Atmega32 Digital I/O (DIO) Driver

**Version:** 1.0  
**Created on:** Jul 16, 2023  
**Created By:** Karim Tarek

## Overview

This is a simple Digital I/O (DIO) driver for the Atmega32 microcontroller. The driver provides functions to control the direction of the pins, assign values to the output pins (low/high), and read the value of the input pins.

## Features

- Supports four ports: GROUP'A', GROUP'B', GROUP'C', and GROUP'D of the Atmega32 MCU.
- Provides functions to set the direction of pins as input or output.
- Allows assigning values to output pins (low or high) - 0V or 5V.
- Enables reading the value of input pins.
- Utilizes the Data Register (PORTx), Data Direction Register (DDRx), and Port Input Pins (PINx) as per Atmega32 datasheet specifications.

## Getting Started

1. Clone or download the repository.
2. Include the required files in your project.
3. Configure the driver according to your needs in `DIO_Interface.h`.
4. Use the provided functions in your code to interact with the microcontroller's ports.

## Usage

The following functions are available in the DIO driver:

1. `void DIO_void_set_port_dir(u8 copy_u8_portID, u8 port_copy_dir)`: Configures the direction of all pins on a specific port as input or output.
2. `void DIO_void_port_pullup(u8 copy_u8_portID)`: Enables internal pull-up resistors for all pins on a specific port.

3. `void DIO_void_set_pin_dir(u8 copy_u8_portID, u8 copy_u8_pinID, u8 pin_copy_dir)`: Configures the direction of a specific pin on a chosen port as input or output.
4. `void DIO_void_pin_pullup(u8 copy_u8_portID, u8 copy_u8_pinID)`: Enables internal pull-up resistor for a specific pin on a chosen port.

5. `void DIO_void_set_port(u8 copy_u8_portID)`: Sets all pins on a specific port to high (5V).
6. `void DIO_void_clear_port(u8 copy_u8_portID)`: Sets all pins on a specific port to low (0V).
7. `void DIO_void_assign_port(u8 copy_u8_portID, u8 copy_value)`: Assigns a value (low or high) to all pins on a specific port.
8. `void DIO_void_toggle_port(u8 copy_u8_portID)`: Toggles the value of all pins on a specific port.

9. `void DIO_void_set_pin(u8 copy_u8_portID, u8 copy_u8_pinID)`: Sets a specific output pin on a chosen port to high (5V).
10. `void DIO_void_clear_pin(u8 copy_u8_portID, u8 copy_u8_pinID)`: Sets a specific output pin on a chosen port to low (0V).
11. `void DIO_void_assign_pin(u8 copy_u8_portID, u8 copy_u8_pinID, u8 copy_value)`: Assigns a value (low or high) to a specific output pin on a chosen port.
12. `void DIO_void_toggle_pin(u8 copy_u8_portID, u8 copy_u8_pinID)`: Toggles the value of a specific output pin on a chosen port.

13. `u8 DIO_u8_get_port(u8 copy_u8_portID)`: Reads and returns the value of all input pins on a specific port.
14. `u8 DIO_u8_get_pin(u8 copy_u8_portID, u8 copy_u8_pinID)`: Reads and returns the value of a specific input pin on a chosen port.

## Important Notes

All information provided in this file is based on the Atmega32 datasheet. Modifying any content in these files will directly impact the behavior of the MCU. It is strongly advised not to make any changes unless you fully understand the implications and intended behavior.

## Example

```c
#include <avr/io.h>
#include "DIO_Interface.h"

int main() {
    // Configure pin PA0 as an output
    DIO_void_set_pin_dir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

    while (1) {
        // Set PA0 to HIGH (5V)
        DIO_void_set_pin(DIO_PORTA, DIO_PIN0);

        // Wait for a while
        _delay_ms(1000);

        // Set PA0 to LOW (0V)
        DIO_void_clear_pin(DIO_PORTA, DIO_PIN0);

        // Wait for a while
        _delay_ms(1000);
    }

    return 0;
}
```

## Contributions

Contributions and improvements to the DIO driver are welcome! Feel free to fork the repository, make changes, and submit pull requests.

## License

This DIO driver is released under the MIT License. See `LICENSE` for more details.

For any questions or issues, please feel free to contact me.

Happy coding!