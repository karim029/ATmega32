/**********************************************************************/
/*                      Created on: Jul 26, 2023                      */
/*                      Created By: Karim Tarek                       */
/*                ADC driver for Atmega32  Version 1.0                */
/**********************************************************************/
/* NOTE: all the data in this file is based on the atmega32 datasheet */
/*       editing anything in these files will affect the MCU behavior */
/*       i dont recommend editing anything unless you know            */
/*          what you're doing and the expected behavior               */
/**********************************************************************/


// Standard libs
#include <util/delay.h>
#include "../../../Libraries/STD_Types.h"
#include "../../../Libraries/bit_calc.h"


//MCAL
#include "../DIO/DIO_Interface.h"

//private libs
#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"

static callBack_func adc_callback = null;


void ADC_startConversion(){

#if is_interrupt_Enable == True
	//start conversion bit
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADSC);
#else
	//start conversion bit
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADSC);
	//Poll on adc conversion complete flag
	while(get_Bit(ADC_u8_ADCSRA,ADSCRA_ADIF) == 0);
	// reset the adc interrupt flag
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADIF);
#endif

}

void ref_voltage(){
	// AVCC 5v
#if Voltage_Reference_Mode == Voltage_Ref_AVCC
	clear_Bit(ADC_u8_ADMUX,ADMUX_REFS1);
	set_Bit(ADC_u8_ADMUX,ADMUX_REFS0);

#elif Voltage_Reference_Mode == Voltage_Ref_AREF
	clear_Bit(ADC_u8_ADMUX,ADMUX_REFS0);
	clear_Bit(ADC_u8_ADMUX,ADMUX_REFS1);

#elif Voltage_Reference_Mode == Voltage_Ref_Int_VREF
	set_Bit(ADC_u8_ADMUX,ADMUX_REFS0);
	set_Bit(ADC_u8_ADMUX,ADMUX_REFS1);

#else

	#error "Please choose correct voltage reference mode from the config file"

#endif
}

void auto_trigger_source(){

#if Auto_Trigger_Source == Free_Running

	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);

#elif Auto_Trigger_Source == Analog_Comparator

	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);

#elif Auto_Trigger_Source == External_Int0

	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);

#elif Auto_Trigger_Source == TC0_Compare_Match

	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);

#elif Auto_Trigger_Source == TC0_Overflow

	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);

#elif Auto_Trigger_Source == TC_Compare_Match_B

	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);

#elif Auto_Trigger_Source == TC1_Overflow


	clear_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);

#elif Auto_Trigger_Source == TC1_Capture_Event


	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS0);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS1);
	set_Bit(ADC_u8_SFIOR,SFIOR_ADTS2);
#else

#endif
}


void preScalar_setup(){

#if Prescalar_Setting == Prescalar_2

	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS2);
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS1);
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS0);

#elif Prescalar_Setting == Prescalar_4

	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS2);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS1);
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS0);

#elif Prescalar_Setting == Prescalar_8

	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS2);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS1);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS0);

#elif Prescalar_Setting == Prescalar_16

	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS2);
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS1);
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS0);

#elif Prescalar_Setting == Prescalar_32

	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS2);
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS1);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS0);

#elif Prescalar_Setting == Prescalar_64

	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS2);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS1);
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS0);

#elif Prescalar_Setting == Prescalar_128

	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS2);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS1);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADPS0);

#endif
}


void ADC_Void_Init(){
	//ADC enable
	set_Bit(ADC_u8_ADCSRA,ADCSRA_ADEN);
	//prescalar setting
	preScalar_setup();
	//set ref voltage --> Avcc
	ref_voltage();

	//left adjustment
#if is_Left_Adj == True
	set_Bit(ADC_u8_ADMUX,ADMUX_ADLAR);
#else
	clear_Bit(ADC_u8_ADMUX,ADMUX_ADLAR);
#endif

	//Auto trigger
#if is_Auto_trigger == True

	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADATE);
	//determine auto trigger source
	auto_trigger_source();
#else
	//disable auto triggering
	clear_Bit(ADC_u8_ADCSRA,ADSCRA_ADATE);
#endif

#if is_interrupt_Enable == True
	set_Bit(ADC_u8_SREG,SREG_GI_ENABLE);
	set_Bit(ADC_u8_ADCSRA,ADSCRA_ADIE);
#endif

}

u32 ADC_Read_Channel(u8 channel) {

	//ADC_startConversion();
    u32 result;

    ADC_u8_ADMUX &= 0b11100000;
    ADC_u8_ADMUX |= channel;

#if is_Left_Adj == True
    result = ADC_u8_ADCL >> 6;
    result |= ((u16)ADC_u8_ADCH << 2);
#elif is_Left_Adj == False
    result = ADC_u8_ADCL;
    result |= ((u16)ADC_u8_ADCH << 8);

#endif

    return result;
}

void set_callBack_function(callBack_func callBack){

	adc_callback = callBack;

}

void __vector_16(){


	/* generic callback function for the user to use
	 *
	 * in the isr, Please change the channel you want to read
	 *
	 * in the adc_interface.h you can find predefined macros for the channels available
	 * in the atmega32 mcu
	 *
	 *
	 */

	// ADC ISR
	if(adc_callback != null){
		u32 adc_val = ADC_Read_Channel(ADC_Channel_0);
		adc_callback(adc_val);
	}

}


