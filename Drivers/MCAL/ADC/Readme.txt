# ADC Driver for Atmega32

This repository contains the ADC driver for the Atmega32 microcontroller. The driver allows you to interface with the Analog to Digital Converter (ADC) module on the Atmega32 to read analog signals and convert them to digital values.

## Contents

- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Configuration](#configuration)
- [Usage](#usage)
- [Callback Function](#callback-function)
- [Important Notes](#important-notes)
- [License](#license)

## Introduction

The ADC driver is designed for the Atmega32 microcontroller and is based on the Atmega32 datasheet. The driver provides functions to initialize the ADC, read analog channels, and configure various settings such as reference voltage, auto-triggering, and prescaler settings.

## Getting Started

To use the ADC driver in your Atmega32 project, follow these steps:

1. Copy the `ADC_Interface.c`, `ADC_Config.h`, and `ADC_Private.h` files to your project folder.
2. Include the necessary files in your main code:

```c
#include "ADC_Config.h"
#include "ADC_Interface.h"
```

3. Initialize the ADC by calling `ADC_Void_Init()` before reading analog values.

## Configuration

You can customize the ADC driver to your liking by editing the `ADC_Config.h` file. The configuration options include:

- Voltage Reference Mode: Choose the reference voltage for the ADC (AVCC, AREF, or Internal VREF).
- Left Adjustment: Enable or disable left adjustment of ADC result.
- Auto Trigger: Enable or disable auto-triggering mode for the ADC.
- Auto Trigger Source: Choose the auto-trigger source from available options (Free Running, Analog Comparator, External Int0, etc.).
- Interrupt Enable: Enable or disable ADC interrupts.

## Usage

1. Initialize the ADC by calling `ADC_Void_Init()` in your code.
2. Read analog channels using `ADC_Read_Channel(u8 channel)`. Pass the desired channel as an argument to this function.
3. Optionally, you can enable auto-trigger mode and set up the auto-trigger source using `auto_trigger_source()` in `ADC_Interface.c`.

## Callback Function

The ADC driver allows you to use a callback function to process ADC results in the Interrupt Service Routine (ISR). To use the callback function, follow these steps:

1. Define your callback function with the following signature:

```c
void my_callback_function(u32 adc_Value);
```

2. Set the callback function using `set_callBack_function(my_callback_function)`. This function must be called before starting ADC conversions.
3. When the ADC conversion is complete, the callback function will be called with the ADC result as an argument.

## Important Notes

- Editing anything in the ADC driver files without proper knowledge may affect the MCU behavior. Avoid editing unless you fully understand the expected behavior.
- The driver is based on the Atmega32 datasheet, and its behavior is tailored to this specific microcontroller.

## License

This ADC driver is distributed under the [MIT License](LICENSE).

**Author: Karim Tarek**  
**Created on: Jul 26, 2023**