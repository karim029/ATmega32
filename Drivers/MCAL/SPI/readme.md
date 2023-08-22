# ATmega32 SPI Driver

This is a simple SPI (Serial Peripheral Interface) driver for the ATmega32 microcontroller. The driver provides functions to configure and communicate with devices using the SPI protocol.

## Features

- Supports both master and slave mode of operation.
- Configurable data order (MSB or LSB).
- Configurable clock polarity and phase.
- Adjustable clock frequency settings.
- Supports interrupt-driven communication (optional).
- Provides callback mechanism for interrupt-based communication.

## Files

- `SPI_Config.h`: Contains configuration macros for SPI settings.
- `SPI_Interface.h`: Contains the function prototypes and definitions for SPI control.
- `SPI_Private.h`: Contains private definitions used by the driver.
- `SPI_Program.c`: Contains the driver implementation.

## Functions

- `void set_Callback_function(void(*ptr_function)(void))`: Set a callback function to be called upon SPI interrupt.
- `void SPI_masterInit()`: Initialize the SPI module in master mode.
- `void SPI_slaveInit()`: Initialize the SPI module in slave mode.
- `u8 SPI_Tranciever(u8 data)`: Transmit and receive data using the SPI module.

## Example Usage

```c
#include "SPI_Interface.h"

void main() {
    // Initialize SPI in master mode
    SPI_masterInit();
    
    // Set callback function for interrupt
    set_Callback_function(&myInterruptHandler);
    
    u8 txData = 0x55;
    u8 rxData = SPI_Tranciever(txData);
    
    // Rest of the code...
}

void myInterruptHandler() {
    // SPI interrupt callback function
    // Perform necessary actions here
}
```
## Note
This driver is designed specifically for the ATmega32 microcontroller. It includes both master and slave mode functions and supports interrupt-driven communication if desired. Make sure to include the necessary header files and adjust the configuration macros according to your application's requirements.

Feel free to customize and extend this driver to suit your project's needs.

## License
This driver is released under the MIT License.