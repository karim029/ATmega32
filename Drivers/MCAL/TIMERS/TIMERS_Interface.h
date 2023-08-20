/*
 * TIMERS_Interface.h
 *
 *  Created on: Jul 29, 2023
 *      Author: karim
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

/*INTERRUPT MAPPING FOR EACH TIMER FOR THE CALLBACK FUNCTION */

// Callback reference constants
#define TIMER0_OVF      0   // Timer/Counter0 Overflow Interrupt
#define TIMER0_COMP     1   // Timer/Counter0 Compare Match Interrupt
#define TIMER1_OVF      2   // Timer/Counter1 Overflow Interrupt
#define TIMER1_COMPB    3   // Timer/Counter1 Match A Compare Match Interrupt
#define TIMER1_COMPA    4   // Timer/Counter1 Match B Compare Match Interrupt
#define TIMER1_ICU		5
#define TIMER2_OVF      6   // Timer/Counter2 Overflow Interrupt
#define TIMER2_COMP     7   // Timer/Counter2 Compare Match Interrupt


/*************************** WATCHDOG TIMER SLEEP TIME ***************************/
//16.3 MS
#define WDT_MODE1 0b000
//32.5 MS
#define WDT_MODE2 0b001
//65 MS
#define WDT_MODE3 0b010
//0.13 S
#define WDT_MODE4 0b011
//0.26 S
#define WDT_MODE5 0b100
//0.52 S
#define WDT_MODE6 0b101
//1 S
#define WDT_MODE7 0b110
//2.1 S
#define WDT_MODE8 0b111

/*************************** TIMER 0 - TIMER 2 MODES ***************************/

#define NORMAL_MODE 0
#define CTC			1
#define FAST_PWM    2
#define PC_PWM		3 // PC --> PHASE CORRECT

/*************************** TIMER 1 MODES ***************************/
#define TMR1_NORMAL   		0
#define TMR1_PWM_PC_8BIT    1
#define TMR1_PWM_PC_9BIT	2
#define TMR1_PWM_PC_10BIT	3
#define TMR1_CTC_OCR_TOP	4
#define TMR1_FAST_PWM_8BIT	5
#define TMR1_FAST_PWM_9BIT	6
#define TMR1_FAST_PWM_10BIT	7
#define TMR1_PC_FC_ICR		8
#define TMR1_PC_FC_OCR		9
#define TMR1_PWM_PC_ICR		10
#define TMR1_PWM_PC_OCR		11
#define TMR1_CTC_ICR_TOP	12
#define TMR1_FAST_PWM_ICR	14
#define TMR1_FAST_PWM_OCR	15





/* OC0 Config */
#define OC_DISCONNECTED 0
#define OC_TOGGLE 		 1
#define OC_SET			 2
#define OC_CLEAR		 3

/* ICU edge select */

#define ICU_RISING_EDGE 	0
#define ICU_FALLING_EDGE 	1

/*******************************************************************/

#define NO_CLOCK 			0  //timer/counter stops
#define CLOCK_NO_PRESCALE   1

/*************************** TIMER 0 CLK ***************************/

#define TMR0_CLK_8			2
#define TMR0_CLK_64			3
#define TMR0_CLK_256		4
#define TMR0_CLK_1024	 	5
#define TMR0_EXT_FALL 		6
#define TMR0_EXT_RISE		7

/*************************** TIMER 1 CLK ***************************/

#define TMR1_CLK_8			2
#define TMR1_CLK_64			3
#define TMR1_CLK_256		4
#define TMR1_CLK_1024	 	5
#define TMR1_EXT_FALL 		6
#define TMR1_EXT_RISE		7

/*************************** TIMER 2 CLK ***************************/

#define TMR2_CLK_8			2
#define TMR2_CLK_32			3
#define TMR2_CLK_64			4
#define TMR2_CLK_128		5
#define TMR2_CLK_256		6
#define TMR2_CLK_1024		7

/* FUNCTIONS DECLARATIONS */

void Timer_set_Callback_Func(u8 timer_type,void(*ptr_to_callback)(void));

// TIMER 0 FUNCTIONS //

void TMR0_loadTCNT0(u8 value);
void TMR0_loadOCR0(u8 value);
void TMR0_Stop();
void TMR0_Init();

// TIMER 1 FUNCTIONS //
void TMR1_loadTCNT1(u16 value);
void TMR1_loadOCR1A(u16 value);
void TMR1_loadOCR1B(u16 value);
void TMR1_Stop();
void TMR1_Init();
//ICU
void TMR1_ICU_Enable(u8 copy_u8_edge_select);
void TMR1_ICU_Disable();
u16 TMR1_ICU_read();
void TMR1_ICU_Set_TCNT1(u16 value);


// TIMER 2 FUNCTIONS //
void TMR2_loadTCNT2(u8 value);
void TMR2_loadOCR2(u8 value);
void TMR2_Stop();
void TMR2_Init();

// WATCHDOG FUNCTIONS //
void WDT_Enable(u8 copy_mode);
void WDT_Disable();

#endif /* TIMERS_INTERFACE_H_ */
