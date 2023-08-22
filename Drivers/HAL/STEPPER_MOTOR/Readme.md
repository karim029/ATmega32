# Stepper Motor Driver for Atmega32

This is a simple and efficient stepper motor driver for Atmega32 microcontroller. The driver provides easy-to-use functions to control the stepper motor in both clockwise and counterclockwise directions. It supports two operation modes: full step and half step.

## Features
- Control stepper motor in both clockwise and counterclockwise directions
- Support for two operation modes: full step and half step
- Adjustable motor speed using a smooth mapping function
- Tested speed range from 10ms to 1000ms
- Configurable coil pins for easy integration with your setup

## Usage

### Initializing the Stepper Motor
Before using the stepper motor, you need to initialize it by calling the `stepper_Init()` function. This sets the direction of the stepper coil pins to output.

### Rotating the Stepper Motor
To rotate the stepper motor in the clockwise direction, use the `stepper_Rotation_CW(u16 copy_speed_val)` function, where `copy_speed_val` is the desired speed value (0 to 255). The function takes care of mapping the speed value to the appropriate frequency range for the motor.

For counterclockwise rotation, use the `stepper_Rotation_CCW(u16 copy_speed_val)` function in the same manner.

### Stopping the Stepper Motor
To stop the stepper motor, simply call the `stepper_stop()` function.

### Operation Modes
You can choose between full step and half step operation modes. To change the mode, modify the `operation_Mode` macro in the `STEPPER_Interface.h` file.

## Note
This driver is designed for the Atmega32 microcontroller and is based on the datasheet specifications. Please avoid editing anything in these files unless you fully understand the expected behavior.

Feel free to use, modify, and integrate this stepper motor driver into your projects. Enjoy your smooth and precise stepper motor control with this easy-to-use driver!