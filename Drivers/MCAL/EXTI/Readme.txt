# Atmega32 External Interrupt Driver

**Version:** 1.0  
**Created on:** Jul 25, 2023  
**Created By:** Karim Tarek

## Overview

This is an external interrupt driver for the Atmega32 microcontroller. It provides a user-friendly interface to configure and handle external interrupts on INT0, INT1, and INT2 pins. The driver allows you to set the sensing level (low level, level change, falling edge, or rising edge) and define callback functions for each interrupt source.

## Features

- Support for INT0, INT1, and INT2 external interrupts.
- Configurable sensing levels for each interrupt source.
- Ability to set callback functions for each interrupt.
- Enable and disable global interrupts.

## Usage

1. Include the `EXTI_Interface.h` header file in your project.
2. Configure the desired sensing level using the `EXTI_sensingLevel()` function.
3. Assign callback functions for each interrupt source using `EXTI_set_callBack_func()`.
4. Enable the global interrupt using `EXTI_global_Int(Enable)`.
5. Enable each interrupt source individually using `EXTI_ISR()`.

## Sensing Levels

The following sensing levels are available:

- `EXTI_low_Level`: Interrupt on a low level.
- `EXTI_IOC`: Interrupt on a level change.
- `EXTI_fallin_Edge`: Interrupt on a falling edge.
- `EXTI_rising_Edge`: Interrupt on a rising edge.

## Functions

1. `void EXTI_set_callBack_func(u8 copy_u8_id, void (*ptr_callBack)(void))`: Assigns the callback function to the specified interrupt source.

2. `void EXTI_global_Int(u8 copy_En_Dis)`: Enables or disables global interrupts.

3. `void EXTI_ISR(u8 copy_u8_id, u8 copy_En_Dis)`: Enables or disables the ISR for the specified interrupt source.

4. `void EXTI_sensingLevel(u8 copy_u8_id, u8 copy_u8_sensingLevel)`: Sets the sensing level for the specified interrupt source.

5. `u8 EXTI_read_INT_Flag(u8 copy_u8_id)`: Reads the status of the interrupt flag for the specified interrupt source.

## Example

```c
#include "EXTI_Interface.h"

void my_callback_func(void) {
    // Your code here
}

int main(void) {
    // Initialize hardware and other settings

    // Set the sensing level for INT0 to a falling edge
    EXTI_sensingLevel(INT0, EXTI_fallin_Edge);

    // Set the callback function for INT0
    EXTI_set_callBack_func(INT0, my_callback_func);

    // Enable global interrupts
    EXTI_global_Int(Enable);

    // Enable INT0 interrupt
    EXTI_ISR(INT0, Enable);

    while (1) {
        // Your main program loop
    }

    return 0;
}
```

## License

This driver is licensed under the MIT License. See the LICENSE file for details.

## Note

All information provided in this file is based on the Atmega32 datasheet. Modifying any content in these files will directly impact the behavior of the MCU. It is strongly advised not to make any changes unless you fully understand the implications and intended behavior.