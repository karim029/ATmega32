
# Ultrasonic Distance Measurement Application

This module contains an Ultrasonic Distance Measurement Application implemented for the ATmega32 microcontroller using the HC-SR04 ultrasonic sensor. The application measures distances using the sensor and displays the readings on an LCD.

## Features

- Measures distances using the HC-SR04 ultrasonic sensor.
- Displays distance (cm) readings on an LCD screen.


![Simulation overview](image/Proteus_image.png)

## Calculation

````txt
/* Calculation (distance in cm)

       Sound velocity = 340.00 m/s = 34000 cm/s

     * As Signal travels from HCSR04 to object and returns to the module HCSR04

	   The distance of Object (in cm) = (340000 * Time)/2
                                      = 17000 * Time

	 * As an internal 8MHz oscillator frequency is selected for ATmega32, with Prescaler F_CPU/8 for timer frequency.
	 * Then F(timer) = FCPU/8 = 1 MHZ ---> T(timer) = 1us.

	   Distance = 17000 x (TIMER value) x 1 x 10^-6 cm
                = 0.017 x (TIMER value) cm

	 * Note TIMER VALUE is the pulse width time calculated by the ICU
	
````


## Usage

1. Include the necessary header files in your project:

   ```c
   #include "UltraSonic_Sensor_Interface.h"
   ```

2. Initialize the ultrasonic sensor module using the `ultraSonicInit` function. This function sets up the required configurations for the timer, ICU, and trigger pin.

3. Use the `ultraSonicReadDistance` function to read distance measurements from the HC-SR04 sensor. This function triggers a pulse and calculates the distance based on the duty cycle.

## Hardware Setup

1. Connect the HC-SR04 ultrasonic sensor to the microcontroller's pins as follows:

   - Connect the sensor's VCC pin to a suitable power supply voltage (5V).
   - Connect the sensor's GND pin to the ground.
   - Connect the sensor's TRIG pin to the microcontroller's trigger pin (e.g., PORTC, PIN5).
   - Connect the sensor's ECHO pin to the microcontroller's echo pin (e.g., PORTD, PIN6).

2. Make sure to configure your LCD and set up the necessary connections for displaying distance readings.

## Example Usage

```c
#include "UltraSonic_Sensor_Interface.h"

int main() {
    // Initialize microcontroller and peripherals
    // Initialize LCD screen

    // Initialize the ultrasonic sensor module
    ultraSonicInit();

    while (1) {
        // Read distance measurement
        u16 distance = ultraSonicReadDistance();

        // Display distance on the LCD screen
        // Update the display as needed
    }

    return 0;
}
```

## License

This project in this repository is licensed under the MIT License.




