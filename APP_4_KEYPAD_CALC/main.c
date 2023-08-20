/**********************************************************************/
/*                      Created on: Jul 24, 2023                      */
/*                      Created By: Karim Tarek                       */
/*     Calculator Using keypad driver for Atmega32  Version 1.0       */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/

/*
 *  This calculator is in an early version
 *  so far it only calculate single digit
 *  but handle negative numbers and floating numbers
 *  more features to be added soon!
 *
 */



// standard libraries
#include <util/delay.h>
#include "../Libraries/STD_Types.h"
#include "../Libraries/bit_calc.h"
//MCAL
#include "../Drivers/MCAL/DIO/DIO_Interface.h"
//HAL
#include "../Drivers/HAL/KEYPAD/KEYPAD_Interface.h"
#include "../Drivers/HAL/LCD/LCD_Interface.h"

// error Macro
#define ERROR 16

//Enum for every state in the calculator program
// the name of each state is self explanable
typedef enum {

	state_Wait_NUM1,
	state_Wait_NUM2,
	state_Operation,
	state_Result,
	state_Calculate,
	state_Error

}calculatorStates;


void welcome_Msg(u16 delay){
	/*
	 * function is only for the Welcome Message to be displayed on the LCD
	 *
	 * return nothing.
	 * takes an u16 input (delay variable)
	 *
	 *
	 *
	 */

	LCD_set_cursor(0, 4);
	LCD_write_string((u8*)"Welcome!");
	LCD_set_cursor(1, 1);
	LCD_write_string((u8*)"calc Version:1");
	_delay_ms(delay);
	LCD_set_cursor(0, 0);
	LCD_clear_display();

}

u8 KPD_get_number(u8 copy_u8_key) {
	/*
	 *  after Using the Get_key function i made this function
	 *
	 *  to convert the character returned from the function
	 *  to a real number ofr the 0-9 numbers of the keypad
	 *  also included the C (reset button)
	 *
	 *  function takes AS INPUT the key returned from the KPD_Get_key function
	 *  and return the corresponding number to be used in calculations
	 *
	 *
	 *
	 */
    switch (copy_u8_key) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'c':
            LCD_clear_display();
            return ERROR;

        default:

        	break;//return ERROR; // Return an error value for any other case
    }
}

void error_message(u8 index) {

	/* Error handling function that prints on the LCD a message when an error occurs
	 * the function takes as input a u8 index 0-1 depends on the message you want for the error
	 * you can add more cases in the switch statement to your liking.
	 *
	 *
	 *
	 */
    switch (index) {
        case 0:
            LCD_write_string((u8*)"Wrong Function!");
            _delay_ms(100);
            LCD_clear_display();
            break;
        case 1:
            LCD_write_string((u8*)"Wrong input!");
            _delay_ms(100);
            LCD_clear_display();

            break;
    }
}

u8 KPD_get_function(u8 copy_u8_func) {
	/*
	 *  function used to check for operator clicked when looking for the operation to be made
	 *
	 *  this is an error handling function if the copy_u8_func doesnt equal the operations available
	 *
	 *  return 'x' ---> error to reset calculations
	 *
	 *  if the operation is correct the input is returned as it is
	 *
	 *
	 *
	 */
    if (copy_u8_func == 'c') {
        LCD_clear_display();
        return 'x';
    }
    if (copy_u8_func != '+' && copy_u8_func != '-' && copy_u8_func != '*' && copy_u8_func != '/' && copy_u8_func != '=') {
        return 'x';
    }
    return copy_u8_func;
}

int main() {
	// initialize the lcd
    LCD_init();
    //print welcome message with 1000 ms delay
    welcome_Msg(1000);

    // initialize the keypad
    KPD_Active_Col_init();
    /* variables used for calculations */

    u8 state[16]; // store the key states in it
    u8 key; // store the return of the function kpd_get_key
    f32 num_1 = 0; // used as the left operand
    f32 num_2 = 0; // used as the right operand
    u8 operation = 'x'; // operation variable (initialized with false operation)
    f32 result = 0;  // result variable
    u8 op = 'x'; // container to contain the operation (except the = )
    u8 is_negative = 0; // flag if the left operand is smaller than the right operand (will result in negative result)

    u8 is_devision = 0; // flag if the operation is division to use lcd write float function
    calculatorStates calcState = state_Wait_NUM1; // create an enum object calcState and intialize it
    // with state wait for num1

    while (1) {

    	// reset the state array to make sure we dont get false readings
    	// this is a safety precaution only!

    	 for (u8 i = 0; i < 16; i++) {
    	            state[i] = 1;
    	   }
        KPD_read_key(state);
        key = KPD_get_key(state);

        // reset the calculations and clear the lcd
        if (key == 'c') {
                    LCD_clear_display();
                    num_1 = 0;
                    num_2 = 0;
                    operation = 'x';
                    result = 0;
                    op = 'x';
                    calcState = state_Wait_NUM1;
                }else{ // calculation mode

        switch(calcState){

        	case state_Wait_NUM1:
        		// condition to not assign the number and echo it on the lcd if it is  equal the error
        		if(key != ERROR){
        			if(key != '+' && key != '-' && key != '*' && key != '/'){

        				num_1 = KPD_get_number(key);
        				LCD_write_number(num_1);
        				calcState = state_Operation;
        			}else{
        				calcState = state_Wait_NUM1;
        			}
        		}
        		break;

        	case state_Operation:
        		if(key == '='){
        			num_1 = 0;
        			operation = 'x';
        			LCD_clear_display();
        			error_message(0);
        			calcState = state_Wait_NUM1;

        		}else if((key != ERROR) && (key == '+' || key == '-' || key == '*' || key == '/')){

        			operation = key;
        			op = operation;
        			LCD_write_char(op);
        			calcState = state_Wait_NUM2;

    			}
        		break;

        	case state_Wait_NUM2:
        		if(key != ERROR){
        			if(key == '='){
        				LCD_clear_display();
        				error_message(0);
        				num_1 = 0;
        				operation = 'x';
        				calcState = state_Wait_NUM1;

        			}else if(key != '+' && key != '-' && key != '*' && key != '/' ){

        				num_2 = KPD_get_number(key);
        				LCD_write_number(num_2);
        				calcState = state_Calculate;

        			}
        		}
        		break;

        	case state_Calculate:
        		if(key == '='){
        		switch (op) {

					case '+':
						result = num_1 + num_2;
						break;
					case '-':

						if(num_2 > num_1){

							result = num_2 - num_1;
							is_negative = 1;

						}else{
							result = num_1 - num_2;
						}

						break;
					case '*':
						result = num_1 * num_2;
						break;
					case '/':
						if(num_2 != 0){
							result = (f32)num_1 / (f32)num_2;
							is_devision = 1;
						}else{
							calcState = state_Error;
						}
						break;

				}

        		if (calcState != state_Error){

					LCD_write_char('=');
					if(is_negative){
						LCD_write_char('-');

					}
					if(is_devision){
						LCD_write_float(result, 1);
						is_devision = 0;
					}
					LCD_write_number(result);
					calcState = state_Result;


        		        		}
        		}

        		break;

        	case state_Result:
					if (key == '=') {
						num_1 = result; // Set the result as the new num_1
						LCD_clear_display();
						LCD_write_number(num_1);
						is_negative = 0;
						calcState = state_Operation; // Wait for the next operation
						}
					break;

        		case state_Error:
        			LCD_clear_display();
        			error_message(0);
        			calcState = state_Wait_NUM1;
        			num_1 =0;
        			num_2 = 0;
        			operation = 'x';

        			break;




        }
                }


    }

    return 0;
}
