

# ATmega32 TWI Driver

This is a simple TWI (Two-Wire Interface or I2C) driver for the ATmega32 microcontroller. The driver provides functions to configure and communicate with devices using the TWI protocol.

## Features

- Supports both master and slave mode of operation.
- Configurable clock frequency settings.
- Provides functions for transmitting and receiving data.
- Supports interrupt-driven communication (optional).
- Provides status and result codes for better error handling.

## Files

- `TWI_Interface.h`: Contains the function prototypes and definitions for TWI control.
- `TWI_Private.h`: Contains private definitions used by the driver.
- `TWI_Program.c`: Contains the driver implementation.

## Functions

### Private Functions

- `void TWI_init()`: Initialize the TWI module.
- `void TWI_start()`: Send a start condition on the bus.
- `u8 TWI_getStatus()`: Get the current TWI status code.
- `void TWI_write(u8 data)`: Write data to the TWI bus.
- `u8 TWI_read()`: Read data from the TWI bus.

### Public Functions
- `TWI_Result TWI_masterTransmit(u8* buffer, u16 length, u8 address)`: Initiate master transmitter mode.
- `TWI_Status TWI_readEeprom(u8 address, u16 length, u8 block_byte)`: Read data from EEPROM.

## Example Usage

```c
#include "TWI_Interface.h"

void main() {
    // Initialize TWI
    TWI_init();
    
    // Example: Master transmitter
    u8 data[] = {0x01, 0x02, 0x03};
    TWI_Result result = TWI_masterTransmit(data, sizeof(data), 0xA0);
    
    if (result == result_successful) {
        // Data transmitted successfully
    } else {
        // Handle errors
    }
    
   
    
    // Rest of the code...
}
```

## Note

This driver is designed specifically for the ATmega32 microcontroller. It includes both master transmitter and receiver modes, along with functions for reading data from an EEPROM. Make sure to include the necessary header files and adjust the configuration macros according to your application's requirements.

Feel free to customize and extend this driver to suit your project's needs.

## License

This driver is released under the [MIT License](LICENSE).


