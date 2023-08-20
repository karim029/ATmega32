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

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADC_u8_ADMUX *((volatile u8*)0x27)
#define ADC_u8_ADCSRA *((volatile u8*)0x26)
#define ADC_u8_ADCL *((volatile u8*)0x24)
#define ADC_u8_ADCH *((volatile u8*)0x25)
#define ADC_u8_SFIOR *((volatile u8*)0x50)
#define ADC_u8_SREG *((volatile u8*)0x5F)


void __vector_16(void)__attribute__((signal));

#endif /* ADC_PRIVATE_H_ */
