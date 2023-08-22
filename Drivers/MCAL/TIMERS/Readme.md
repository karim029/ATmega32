
# Timers Driver for Atmega32 MCU

This repository contains a Timers driver for the Atmega32 microcontroller. The driver provides functions to configure and use Timer0, Timer1, and Timer2.

## Contents

1. [Introduction](#introduction)
2. [Driver Files](#Driver-Files)
3. [How to Use](#how-to-use)
4. [Features](#features)
5. [Timer0 Configuration](#timer0-configuration)
6. [Timer1 Configuration](#timer1-configuration)
7. [Timer2 Configuration](#timer2-configuration)
8. [Input Capture Configuration](#input-capture-configuration)
9. [Watchdog Timer](#watchdog-timer)
10. [Interrupt Mapping](#interrupt-mapping)
11. [Callback Functions](#callback-functions)
12. [Contributions](#Contributions)
12. [License](#license)

## Introduction

Timers are essential peripherals in microcontrollers for various timing and timekeeping tasks. This driver provides a set of functions to configure and utilize Timer0, Timer1, and Timer2 on the Atmega32 microcontroller.

## Driver Files

The driver consists of the following files:

`TIMERS_Program.c`: The main source file that contains the implementation of the timer functions.\
`TIMERS_Config.h`: Configuration file where the user can set the desired timer settings.\
`TIMERS_Interface.h`: Header file that contains the public functions and constants for the timer driver.\
`TIMERS_Private.h`: Private header file that contains the registers and macros used internally by the driver.

## How to Use

To use the Timer driver, follow these steps:

1. Clone or download this repository.
2. Include the necessary header files in your project.
3. Configure the settings for the desired timer in the `TIMERS_Config.h` file.
4. Implement the callback functions for each timer interrupt as needed.
5. Call the appropriate initialization function (e.g., `TMR0_Init()`, `TMR1_Init()`, or `TMR2_Init()`) to configure the timers according to your requirements.
6. Use the timer functions provided to start, stop, or modify the timers as needed.

## Features

- Timer0, Timer1, and Timer2 are supported.
- Configurable timer modes: Normal, CTC, Fast PWM, and Phase Correct PWM (PC PWM).
- Configurable output compare modes: Disconnected, Toggle, Set, and Clear.
- Input Capture Unit (ICU) for Timer1 with configurable edge detection (Rising or Falling).
- Watchdog Timer with selectable sleep times.
- Callback functions for each timer interrupt to execute custom code on timer events.
- Timer prescaler configuration options.
- Simple and easy-to-use API.

## Timer0 Configuration

### Prescaler

The Timer0 prescaler can be configured with the following options:

- No clock source (Timer0 is stopped).
- Clock without prescaling.
- Clock with prescaler 8.
- Clock with prescaler 64.
- Clock with prescaler 256.
- Clock with prescaler 1024.
- External clock source with falling edge trigger.
- External clock source with rising edge trigger.

### Modes

Timer0 supports four modes: 
- Normal 
- CTC
- FAST PWM
- PHASE CORRECT PWM

### User Functions

- `void TMR0_loadTCNT0(u8 value);`
- `void TMR0_loadOCR0(u8 value);`
- `void TMR0_Stop();`
- `void TMR0_Init();`

### Output Compare Configuration

Timer0 supports output compare modes for OC0 as follows:

- Disconnected.
- Toggle.
- Set.
- Clear.

## Timer1 Configuration

### Prescaler

The Timer1 prescaler can be configured with the following options:

- No clock source (Timer1 is stopped).
- Clock without prescaling.
- Clock with prescaler 8.
- Clock with prescaler 64.
- Clock with prescaler 256.
- Clock with prescaler 1024.
- External clock source with falling edge trigger.
- External clock source with rising edge trigger.

### Modes

Timer1 supports various modes as follows:

- Normal Mode
- PWM, Phase Correct - 8-bit
- PWM, Phase Correct - 9-bit
- PWM, Phase Correct - 10-bit
- CTC Mode - OCR1A as TOP
- Fast PWM - 8-bit
- Fast PWM - 9-bit
- Fast PWM - 10-bit
- PWM, Phase and Frequency Correct - ICR1 as TOP
- PWM, Phase and Frequency Correct - OCR1A as TOP
- PWM, Phase Correct - ICR1 as TOP
- PWM, Phase Correct - OCR1A as TOP
- CTC Mode - ICR1 as TOP
- Fast PWM - ICR1 as TOP
- Fast PWM - OCR1A as TOP

### User Functions 
- `void TMR1_loadTCNT1(u16 value);`
- `void TMR1_loadOCR1A(u16 value);`
- `void TMR1_loadOCR1B(u16 value);`
- `void TMR1_Stop();`
- `void TMR1_Init();`

### Output Compare Configuration

Timer1 supports output compare modes for OC1A and OC1B as follows:

- Disconnected.
- Toggle.
- Set.
- Clear.

### Input Capture Configuration

Timer1 supports the Input Capture Unit (ICU) with configurable edge detection (Rising or Falling).

`void TMR1_ICU_Enable(u8 copy_u8_edge_select)` \
Where Function input should be `ICU_FALLING_EDGE` or `ICU_RISING_EDGE` \

Other functions for the ICU Mode:
- `void TMR1_ICU_Disable()`
- `u16 TMR1_ICU_read()` 
- `void TMR1_ICU_Set_TCNT1(u16 value)`
## Timer2 Configuration

### Prescaler

The Timer2 prescaler can be configured with the following options:

- No clock source (Timer2 is stopped).
- Clock without prescaling.
- Clock with prescaler 8.
- Clock with prescaler 32.
- Clock with prescaler 64.
- Clock with prescaler 128.
- Clock with prescaler 256.
- Clock with prescaler 1024.
- External clock source with rising edge trigger.
- External clock source with falling edge trigger.

### Modes

Timer2 supports four modes:
 
- Normal 
- CTC
- FAST PWM
- PHASE CORRECT PWM

### User Functions

- `void TMR2_loadTCNT0(u8 value);`
- `void TMR2_loadOCR0(u8 value);`
- `void TMR2_Stop();`
- `void TMR2_Init();`

### Output Compare Configuration

Timer2 supports output compare modes for OC2 as follows:

- Disconnected.
- Toggle.
- Set.
- Clear.

## Watchdog Timer

The driver provides functions to enable and disable the watchdog timer with selectable sleep times.

The available sleep times are:

- 16.3 ms
- 32.5 ms
- 65 ms
- 0.13 sec
- 0.26 sec
- 0.52 sec
- 1 sec
- 2.1 sec

## Interrupt Mapping

In this timers driver for the Atmega32 MCU, interrupt mapping and callback functions are used to provide a flexible and efficient way for users to handle timer-related events. The driver supports multiple timers (Timer0, Timer1, and Timer2), each with its own set of interrupt types, such as overflow and compare match interrupts. Users can register their own callback functions to be executed when these interrupts occur, allowing them to respond to specific timer events in their application code.

The interrupt mapping is implemented using an array of function pointers, named callback_func, which is defined as a static array in the driver implementation file TIMERS_Program.c. The array size is set to 8, as it accommodates all the possible interrupt sources for Timer0, Timer1, and Timer2.

The mapping is as follows:

Using the predefined macros in the interface.h

`callback_func[TIMER0_OVF]`: Timer0 Overflow interrupt\
`callback_func[TIMER0_COMP]`: Timer0 Compare Match interrupt (CTC mode)\
`callback_func[TIMER1_OVF]`: Timer1 Overflow interrupt\
`callback_func[TIMER1_COMPB]`: Timer1 Compare Match B interrupt\
`callback_func[TIMER1_COMPA]`: Timer1 Compare Match A interrupt\
`callback_func[TIMER1_ICU]`: Timer1 Input Capture Unit (ICU) interrupt\
`callback_func[TIMER2_OVF]`: Timer2 Overflow interrupt\
`callback_func[TIMER2_COMP]`: Timer2 Compare Match interrupt\

## Callback Functions:

Users can register their own callback functions for each timer interrupt. To register a callback function, the driver provides a public function named `void Timer_set_Callback_Func(u8 timer_type, void(*ptr_to_callback)(void))`. This function takes two parameters: `timer_type` and `ptr_to_callback`. The timer_type parameter specifies the type of timer interrupt (e.g., Timer0 Overflow, Timer1 Compare Match A), and the `ptr_to_callback` parameter is a pointer to the user-defined callback function.

For example, to register a callback function for Timer0 Overflow interrupt, the user can call the `Timer_set_Callback_Func()` function as follows:

````c
Timer_set_Callback_Func(TIMER0_OVF, my_timer0_overflow_callback);
`````
Where `my_timer0_overflow_callback` is the user-defined callback function that will be executed when Timer0 Overflow interrupt occurs.

## Contributions

Contributions and improvements to the TIMERS driver are welcome! Feel free to fork the repository, make changes, and submit pull requests.

## License

This TIMERS driver is released under the MIT License. See `LICENSE` for more details.

For any questions or issues, please feel free to contact me.

Happy coding!






