

# ATmega32 Internal EEPROM Driver

This repository contains a simple internal EEPROM driver for the ATmega32 microcontroller. The driver provides functions to read and write data to the EEPROM memory.

## How to Use

### Functions

1. **`void eepromWriteByte(u16 address, u8 data)`**
   - Description: Writes a single byte of data to the specified EEPROM address.
   - Parameters:
     - `address`: Address to write data to.
     - `data`: Data byte to be written.
   - **Usage Example**:
     ```c
     eepromWriteByte(0x0100, 0xAA);
     ```

2. **`u8 eepromReadByte(u16 address)`**
   - Description: Reads a single byte of data from the specified EEPROM address.
   - Parameters:
     - `address`: Address to read data from.
   - Returns: The read data byte.
   - **Usage Example**:
     ```c
     u8 readData = eepromReadByte(0x0100);
     ```

3. **`eepromResult eepromWriteBytes(u16 address, u8* data, u16 length)`**
   - Description: Writes multiple bytes of data to consecutive addresses in the EEPROM memory.
   - Parameters:
     - `address`: Starting address for writing data.
     - `data`: Pointer to the array of data bytes.
     - `length`: Number of bytes to write.
   - Returns: An `eepromResult` indicating the operation status.
   - **Usage Example**:
     ```c
     u8 data[] = {0xAA, 0xBB, 0xCC};
     eepromResult result = eepromWriteBytes(0x0200, data, sizeof(data));
     ```

4. **`eepromResult eepromReadBytes(u16 address, u8* data, u16 length)`**
   - Description: Reads multiple bytes of data from consecutive addresses in the EEPROM memory.
   - Parameters:
     - `address`: Starting address for reading data.
     - `data`: Pointer to the array for storing read data.
     - `length`: Number of bytes to read.
   - Returns: An `eepromResult` indicating the operation status.
   - **Usage Example**:
     ```c
     u8 readData[3];
     eepromResult result = eepromReadBytes(0x0200, readData, sizeof(readData));
     ```

## Important Notes

- The maximum EEPROM size for the ATmega32 is 1024 bytes.
- Use the provided functions to access the EEPROM memory safely.



