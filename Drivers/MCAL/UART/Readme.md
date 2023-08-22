# UART Communication Protocol for ATmega32

This repository contains a UART (Universal Asynchronous Receiver/Transmitter) communication protocol driver for the ATmega32 microcontroller. UART is a widely used serial communication protocol that allows data transmission and reception between devices asynchronously.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [How to Use](#how-to-use)
  - [Initialization](#initialization)
  - [Basic Transmission](#basic-transmission)
  - [Receiving a String Using Callbacks](#receiving-a-string-using-callbacks)
- [Important Notes](#important-notes)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Introduction

UART (Universal Asynchronous Receiver/Transmitter) is a popular serial communication protocol used in embedded systems to enable communication between microcontrollers and other devices, such as sensors, displays, or other microcontrollers. It operates in an asynchronous manner, meaning that data is transmitted without a shared clock signal between the sender and receiver.

## Features

- Configurable operation mode: Async or Sync
- Support for different character sizes (5-bit, 6-bit, 7-bit, 8-bit, or 9-bit)
- Adjustable number of stop bits (1 or 2)
- Optional parity mode (even or odd parity) for data integrity
- Configurable Baud Rate for communication speed
- Support for interrupt-driven or polling-based communication
- Callback functions for TX complete, RX complete, and UDR empty interrupts

## How to Use

### Initialization

1. Include the necessary header files in your project:
   - `UART_Interface.h`: Contains the function prototypes and macros for UART driver usage.
   - `UART_Config.h`: Adjust the driver options, such as the operation mode, stop bits, parity mode, and character size.
   - `UART_Private.h`: Contains the UART registers and interrupt vectors.

2. Initialize the UART by calling `UART_Init()` function in your setup code. This function sets up the UART configuration based on the options provided in `UART_Config.h`.

### Basic Transmission

Use `UART_Transmit_char(u8 data)` function to transmit a single character through UART.

### Receiving a String Using Callbacks

To receive a string, use `UART_Receive_String(u8* arr)`. This function receives a string of characters through UART and stores it in the provided array.

````c
#include "UART_Interface.h"

void RX_complete_callback(void) {
    // Handle received data here
    // This function will be called when a character is received
}

int main(void) {
    UART_Init(); // Initialize UART with default settings
    UART_set_Callback_function(RX_complete, RX_complete_callback);

    while (1) {
        // Your main code here
    }

    return 0;
}
`````

## Important Notes

- Ensure that the UART configuration in `UART_Config.h` matches the settings of your target device and the connected device.
- The UART driver can be used in either asynchronous or synchronous mode as configured in `UART_Config.h`.
- Make sure to handle the UART interrupts properly if you enable interrupt-driven communication.
- The driver assumes you have set up the necessary clock source and baud rate for UART communication. The actual Baud Rate used will depend on the oscillator frequency and the UBR_Val defined in `UART_Config.h`.
- For synchronous mode, ensure that you configure the `UCSRC_UCPOL` bit in `UART_Config.h` to select the desired clock polarity.

## Examples

### Initialization and Basic Transmission

```c
#include "UART_Interface.h"

int main(void) {
    UART_Init(); // Initialize UART with default settings

    while (1) {
        UART_Transmit_char('H'); // Transmit character 'H'
        UART_Transmit_char('i'); // Transmit character 'i'
        UART_Transmit_char('\n'); // Transmit newline character
    }

    return 0;
}


#include "UART_Interface.h"

void RX_complete_callback(void) {
    // Handle received data here
    // This function will be called when a character is received
}

int main(void) {
    UART_Init(); // Initialize UART with default settings
    UART_set_Callback_function(RX_complete, RX_complete_callback);

    while (1) {
        // Your main code here
    }

    return 0;
}
````
## Contributing
Contributions to this project are welcome. If you find any issues or have any improvements, please feel free to open a pull request or an issue.

## License
This project is licensed under the MIT License.