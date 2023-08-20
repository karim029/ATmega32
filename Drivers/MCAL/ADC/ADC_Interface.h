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

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef void (*callBack_func)(u32 adc_Value);

//**************************************//
//TO CUSTOMIZE THE ADC TO YOUR LIKING   //
//          CHECK ADC_CONFIG.H          //
//**************************************//
//global interrupt bit
#define SREG_GI_ENABLE 7

//+++++ADMUX REGISTER+++++// multiplexer selection register

//Bit 7:6 – REFS1:0: Reference Selection Bits
#define ADMUX_REFS1 7
#define ADMUX_REFS0 6
//Bit 5 – ADLAR: ADC Left Adjust Result SET 1 To left adjust
#define ADMUX_ADLAR 5
//Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits
#define ADMUX_MUX4 4
#define ADMUX_MUX3 3
#define ADMUX_MUX2 2
#define ADMUX_MUX1 1
#define ADMUX_MUX0 0

//+++++ADCSRA REGISTER+++++// control and status register

// Bit 7 – ADEN: ADC Enable Write 1 to enable ADC if set 0 ADC won't work
#define ADCSRA_ADEN 7
// Bit 6 – ADSC: ADC Start Conversion
#define ADSCRA_ADSC 6
// Bit 5 – ADATE: ADC Auto Trigger Enable
#define ADSCRA_ADATE 5
// Bit 4 – ADIF: ADC Interrupt Flag ++used in case of polling++
#define ADSCRA_ADIF 4
// Bit 3 – ADIE: ADC Interrupt Enable
#define ADSCRA_ADIE 3
// Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
#define ADSCRA_ADPS2 2
#define ADSCRA_ADPS1 1
#define ADSCRA_ADPS0 0

//+++++SFIOR REGISTER+++++// Special function I/O register

// Bit 7:5 – ADTS2:0: ADC Auto Trigger Source
#define SFIOR_ADTS2 7
#define SFIOR_ADTS1 6
#define SFIOR_ADTS0 5

//ADC Channels
#define ADC_Channel_0 0b00000000
#define ADC_Channel_1 0b00000001
#define ADC_Channel_2 0b00000010
#define ADC_Channel_3 0b00000011
#define ADC_Channel_4 0b00000100
#define ADC_Channel_5 0b00000101
#define ADC_Channel_6 0b00000110
#define ADC_Channel_7 0b00000111


/* Function declaration */

void ADC_startConversion();
void ref_voltage();
void auto_trigger_source();
void preScalar_setup();
void ADC_Void_Init();
u32 ADC_Read_Channel(u8 channel);
void set_callBack_function(callBack_func callBack);

#endif /* ADC_INTERFACE_H_ */
