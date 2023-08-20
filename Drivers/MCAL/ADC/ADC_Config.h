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

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#define True 1
#define False 0

#define null ((void*)0)

//ref voltage mode selection
#define Voltage_Ref_AREF 0
#define Voltage_Ref_AVCC 1
#define Voltage_Ref_Int_VREF 2
#define Voltage_Reference_Mode Voltage_Ref_AVCC

//Left Adjust enabled or not
#define is_Left_Adj True

//auto trigger enabled or not
#define is_Auto_trigger False
//auto trigger sources
#define Free_Running 0
#define Analog_Comparator 1
#define External_Int0 2
#define TC0_Compare_Match 3
#define TC0_Overflow 4
#define TC_Compare_Match_B 5
#define TC1_Overflow 6
#define TC1_Capture_Event 7

#define Auto_Trigger_Source External_Int0 // set the trigger source from here!

#define is_interrupt_Enable True


//presalar settings
#define Prescalar_2 0
#define Prescalar_4 1
#define Prescalar_8 2
#define Prescalar_16 3
#define Prescalar_32 4
#define Prescalar_64 5
#define Prescalar_128 6


#define Prescalar_Setting Prescalar_128



#endif /* ADC_CONFIG_H_ */
