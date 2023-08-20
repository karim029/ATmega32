/*
 * TIMERS_Registers.h
 *
 *  Created on: Jul 29, 2023
 *      Author: karim
 */


#ifndef TIMERS_PRIVATE_H_
#define TIMERS_PRIVATE_H_

#define NULL ((void*)0)

/* STATUS REGISTER */
#define SREG *((volatile u8*)0x5F)

/************************ WATCHDOG TIMER ************************/
#define WDTCR *((volatile u8*)0x41)

#define WDTOE 4
#define WDE   3
#define WDP2  2
#define WDP1  1
#define WDP0  0



/*************************** TIMER 0 ***************************/
/* TIMER0 REGISTER AND MACROS */

// timer0 counter control register
#define TCCR0 *((volatile u8*)0x53)
// timer0 counter register
#define TCNT0 *((volatile u8*)0x52)
// output compare register
#define OCR0 *((volatile u8*)0x5C)

#define FOC0  7
#define WGM00 6
#define COM01 5
#define COM00 4
#define WGM01 3
#define CS02  2
#define CS01  1
#define CS00  0

/* Driver functions NOT FOR USER */
/* timer 0 */
void TMR0_prescallar();
void TMR0_0C0_setup();
void TMR0_mode();

// ISR of Timer/Counter0 Compare Match
void __vector_10(void)__attribute__((signal));
// ISR of Timer/Counter0 Overflow
void __vector_11(void)__attribute__((signal));


/*************************** TIMER 1 ***************************/
/* Timer 1 registers and Macros */

#define TCCR1A  *((volatile u8*)0x4F)
#define TCCR1B	*((volatile u8*)0x4E)
#define TCNT1   *((volatile u16*)0x4C)
#define OCR1A   *((volatile u16*)0x4A)
#define OCR1B   *((volatile u16*)0x48)
#define ICR1    *((volatile u16*)0x46)

/* CONTROL REGISTER A */
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A  3
#define FOC1B  2
#define WGM11  1
#define WGM10  0

/* CONTROL REGISTER B */
//ICU

#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12  2
#define CS11  1
#define CS10  0

/* Driver functions NOT FOR USER */
/* timer 1 */
void TMR1_mode();
void TMR1_OC_Setup();
void TMR1_prescallar();

// ISR OF ICU timer1
void __vector_6(void)__attribute__((signal));
// ISR of Timer/Counter1 Match B Compare Match
void __vector_7(void)__attribute__((signal));
// ISR of Timer/Counter1 Match A Compare Match
void __vector_8(void)__attribute__((signal));
// ISR of Timer/Counter1 Overflow
void __vector_9(void)__attribute__((signal));


/*************************** TIMER2 ***************************/
/* Timer 2 registers and Macros */

#define TCCR2  *((volatile u8*)0x45)
#define TCNT2  *((volatile u8*)0x44)
#define OCR2   *((volatile u8*)0x43)

#define TIFR   *((volatile u8*)0x58)

#define TOV2 6
#define OCF2 7

#define WGM20 6
#define WGM21 3
#define COM21 5
#define COM20 4
#define CS22  2
#define CS21  1
#define CS20  0

/* Driver functions NOT FOR USER */
/* timer 2 */
void TMR2_prescaller();
void TMR2_OC2_setup();
void TMR2_mode();


// ISR of Timer/Counter2 Compare Match
void __vector_4(void)__attribute__((signal));
	// ISR of Timer/Counter2 Overflow
void __vector_5(void)__attribute__((signal));



/*************************** TIMSK ***************************/

/* TIMER INTERRPUT MASK REGISTER TIMSK */

#define TIMSK *((volatile u8*)0x59)

#define OCIE2 7
#define TOIE2 6

#define TICIE1 5
#define OCIE1A 4
#define OCIE1B 3
#define TOIE1  2

#define OCIE0  1
#define TOIE0  0

#endif /* TIMERS_PRIVATE_H_ */
