/*
 * TIMERS_Program.c
 *
 *  Created on: Jul 29, 2023
 *      Author: karim
 */


// standard libs
#include "../../Libraries/STD_Types.h"
#include "../../Libraries/bit_calc.h"

//MCAL
#include "../../Drivers/MCAL/DIO/DIO_Interface.h"

//private
#include "TIMERS_Config.h"
#include "TIMERS_Interface.h"
#include "TIMERS_Private.h"


static void(*callback_func[8])(void);


void Timer_set_Callback_Func(u8 timer_type,void(*ptr_to_callback)(void)){


	if((timer_type>= 0)&&(timer_type <= 7)){

		callback_func[timer_type] = ptr_to_callback;

	}

}


/*************************** TIMER0 ***************************/

void TMR0_prescallar(){

#if TMR0_PRESCALE == NO_CLOCK
	clear_Bit(TCCR0,CS00);
	clear_Bit(TCCR0,CS01);
	clear_Bit(TCCR0,CS02);

#elif TMR0_PRESCALE == CLOCK_NO_PRESCALE
	set_Bit(TCCR0,CS00);
	clear_Bit(TCCR0,CS01);
	clear_Bit(TCCR0,CS02);

#elif TMR0_PRESCALE == TMR0_CLK_8

	set_Bit(TCCR0,CS01);
	clear_Bit(TCCR0,CS00);
	clear_Bit(TCCR0,CS02);

#elif TMR0_PRESCALE == TMR0_CLK_64

	set_Bit(TCCR0, CS00);
	set_Bit(TCCR0, CS01);
	clear_Bit(TCCR0,CS02);

#elif TMR0_PRESCALE == TMR0_CLK_256

	clear_Bit(TCCR0,CS00);
	clear_Bit(TCCR0,CS01);
	set_Bit(TCCR0,CS02);

#elif TMR0_PRESCALE == TMR0_CLK_1024

	set_Bit(TCCR0,CS00);
	clear_Bit(TCCR0,CS01);
	set_Bit(TCCR0,CS02);

#elif TMR0_PRESCALE == TMR0_EXT_FALL
	set_Bit(TCCR0,CS02);
	set_Bit(TCCR0,CS01);
	clear_Bit(TCCR0,CS00);

#elif TMR0_PRESCALE == TMR0_EXT_RISE

	set_Bit(TCCR0,CS02);
	set_Bit(TCCR0,CS01);
	set_Bit(TCCR0,CS00);

#else
#warning "please choose the correct prescaling configuration from the config file"
#endif


}


void TMR0_0C0_setup(){

#if TMR0_MODE == NORMAL_MODE || TMR0_MODE == CTC
#if TMR0_OC0_MODE == OC_DISCONNECTED
	clear_Bit(TCCR0, COM00);
	clear_Bit(TCCR0,COM01);

#elif TMR0_OC0_MODE == OC_TOGGLE
	clear_Bit(TCCR0,COM01);
	set_Bit(TCCR0,COM00);

#elif TMR0_OC0_MODE == OC_CLEAR
	clear_Bit(TCCR0,COM00);
	set_Bit(TCCR0,COM01);

#elif TMR0_OC0_MODE == OC_SET
	set_Bit(TCCR0,COM00);
	set_Bit(TCCR0,COM01);

#else
#warning "please choose the correct OC0 configuration from the configuration file"
#endif
#elif TMR0_MODE == FAST_PWM
#if TMR0_OC0_MODE == OC0_DISCONNECTED
	clear_Bit(TCCR0, COM00);
	clear_Bit(TCCR0,COM01);
#elif TMR0_OC0_MODE == OC_CLEAR
	//Clear OC0 on compare match, set OC0 at TOP
	// non inverted PWM
	set_Bit(TCCR0,COM01);
	clear_Bit(TCCR0, COM00);
#elif TMR0_OC0_MODE == OC_SET
	// Set OC0 on compare match, clear OC0 at TOP
	// inverted PWM
	set_Bit(TCCR0,COM01);
	set_Bit(TCCR0,COM00);
#endif
#elif TMR0_MODE == PC_PWM
#if TMR0_OC0_MODE == OC_DISCONNECTED
	clear_Bit(TCCR0, COM00);
	clear_Bit(TCCR0,COM01);
#elif TMR0_OC0_MODE == OC_CLEAR
	//Clear OC0 on compare match, set OC0 at TOP
	// non inverted PWM
	set_Bit(TCCR0,COM01);
	clear_Bit(TCCR0, COM00);
#elif TMR0_OC0_MODE == OC_SET
	// Set OC0 on compare match, clear OC0 at TOP
	// inverted PWM
	set_Bit(TCCR0,COM01);
	set_Bit(TCCR0,COM00);
#endif


#endif
}


void TMR0_mode(){

#if TMR0_MODE == NORMAL_MODE
	// WGM01 AND WGM00 --> 0,0
	clear_Bit(TCCR0,WGM01);
	clear_Bit(TCCR0,WGM00);

#elif TMR0_MODE == CTC

	set_Bit(TCCR0,WGM01);
	clear_Bit(TCCR0,WGM00);

#elif TMR0 == FAST_PWM

	set_Bit(TCCR0,WGM00);
	set_Bit(TCCR0,WGM01);

#elif TMR0_MODE == PC_PWM
	clear_Bit(TCCR0,WGM01);
	set_Bit(TCCR0,WGM00);

#else

#error "please choose the correct timer0 mode from the configuration file"


#endif

}


void TMR0_Stop(){

	clear_Bit(TCCR0, CS02);
	clear_Bit(TCCR0, CS01);
	clear_Bit(TCCR0, CS00);

}


void TMR0_loadTCNT0(u8 value){

	TCNT0 = value;
}

void TMR0_loadOCR0(u8 value){

	OCR0 = value;
}

void TMR0_Init(){


	TMR0_mode();
	TMR0_0C0_setup();
	TMR0_prescallar();

#if TMR0_OVF_INTERRUPT == ENABLE && TMR0_OC_INTERRUPT == DISABLE
	//enable timer0 overflow interrupt
	set_Bit(TIMSK,TOIE0);
	//enable global interrupt
	set_Bit(SREG,7);
#elif TMR0_OVF_INTERRUPT == DISABLE && TMR0_OC_INTERRUPT == ENABLE
	//enable timer0 ctc interrupt
	set_Bit(TIMSK,OCIE0);
	//enable global interrupt
	set_Bit(SREG,7);

#else
	//enable timer0 overflow interrupt
		set_Bit(TIMSK,TOIE0);
		//enable timer0 ctc interrupt
		set_Bit(TIMSK,OCIE0);
		//enable global interrupt
		set_Bit(SREG,7);


#endif



}


// ISR FOR OVERFLOW TIMER 0 INTERRUPT
void __vector_11(){

	if(callback_func[TIMER0_OVF] != NULL){

		callback_func[TIMER0_OVF]();

	}

}

// ISR FOR CTC TIMER 0 INTERRUPT
void __vector_10(){

	if(callback_func[TIMER0_COMP] != NULL){

			callback_func[TIMER0_COMP]();

		}
}



/*************************** TIMER 1 ***************************/


void TMR1_mode(){

#if TMR1_MODE == TMR1_NORMAL

	clear_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_PWM_PC_8BIT

	set_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_PWM_PC_9BIT

	set_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_PWM_PC_10BIT

	set_Bit(TCCR1A,WGM10);
	set_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_CTC_OCR_TOP

	set_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_FAST_PWM_8BIT

	set_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM11);
	set_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_FAST_PWM_9BIT

	set_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM10);
	set_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_FAST_PWM_10BIT

	set_Bit(TCCR1A,WGM11);
	set_Bit(TCCR1A,WGM10);
	set_Bit(TCCR1A,WGM12);
	clear_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_PC_FC_ICR

	clear_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM12);
	set_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_PC_FC_OCR

	set_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM12);
	set_Bit(TCCR1A,WGM13);


#elif TMR1_MODE == TMR1_PWM_PC_ICR

	clear_Bit(TCCR1A,WGM10);
	set_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM12);
	set_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_PWM_PC_OCR

	set_Bit(TCCR1A,WGM10);
	set_Bit(TCCR1A,WGM11);
	clear_Bit(TCCR1A,WGM12);
	set_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_CTC_ICR_TOP

	clear_Bit(TCCR1A,WGM10);
	clear_Bit(TCCR1A,WGM11);
	set_Bit(TCCR1A,WGM12);
	set_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_FAST_PWM_ICR

	clear_Bit(TCCR1A,WGM10);
	set_Bit(TCCR1A,WGM11);
	set_Bit(TCCR1A,WGM12);
	set_Bit(TCCR1A,WGM13);

#elif TMR1_MODE == TMR1_FAST_PWM_OCR

	set_Bit(TCCR1A,WGM10);
	set_Bit(TCCR1A,WGM11);
	set_Bit(TCCR1A,WGM12);
	set_Bit(TCCR1A,WGM13);




#endif
}


void TMR1_OC_Setup(){

#if (TMR1_CHANNEL_A == ENABLE && TMR1_CHANNEL_B == DISABLE)

#if TMR1_OCA_MODE == OC_CLEAR

	set_Bit(TCCR1A,COM1A1);
	clear_Bit(TCCR1A,COM1A0);

#elif TMR1_OCA_MODE == OC_SET

	set_Bit(TCCR1A,COM1A1);
	set_Bit(TCCR1A,COM1A0);

#elif TMR1_OCA_MODE == OC_TOGGLE

	set_Bit(TCCR1A,COM1A0);
	clear_Bit(TCCR1A,COM1A1);

#elif TMR1_OCA_MODE == NORMAL_MODE

	clear_Bit(TCCR1A,COM1A1);
	clear_Bit(TCCR1A,COM1A0);

#endif

#elif (TMR1_CHANNEL_A == DISABLE && TMR1_CHANNEL_B == ENABLE)

#if TMR1_OCB_MODE == OC_CLEAR

	set_Bit(TCCR1A,COM1B1);
	clear_Bit(TCCR1A,COM1B0);

#elif TMR1_OCB_MODE == OC_SET

	set_Bit(TCCR1A,COM1B1);
	set_Bit(TCCR1A,COM1B0);

#elif TMR1_OCB_MODE == OC_TOGGLE

	set_Bit(TCCR1A,COM1B0);
	clear_Bit(TCCR1A,COM1B1);

#elif TMR1_OCB_MODE == NORMAL_MODE

	clear_Bit(TCCR1A,COM1B1);
	clear_Bit(TCCR1A,COM1B0);

#endif

#elif (TMR1_CHANNEL_A == ENABLE && TMR1_CHANNEL_B == ENABLE)

#if TMR1_OCA_MODE == OC_CLEAR

	set_Bit(TCCR1A,COM1A1);
	clear_Bit(TCCR1A,COM1A0);

#elif TMR1_OCA_MODE == OC_SET

	set_Bit(TCCR1A,COM1A1);
	set_Bit(TCCR1A,COM1A0);

#elif TMR1_OCA_MODE == OC_TOGGLE

	set_Bit(TCCR1A,COM1A0);
	clear_Bit(TCCR1A,COM1A1);

#elif TMR1_OCA_MODE == NORMAL_MODE

	clear_Bit(TCCR1A,COM1A1);
	clear_Bit(TCCR1A,COM1A0);

#endif
#if TMR1_OCB_MODE == OC_CLEAR

	set_Bit(TCCR1A,COM1B1);
	clear_Bit(TCCR1A,COM1B0);

#elif TMR1_OCB_MODE == OC_SET

	set_Bit(TCCR1A,COM1B1);
	set_Bit(TCCR1A,COM1B0);

#elif TMR1_OCB_MODE == OC_TOGGLE

	set_Bit(TCCR1A,COM1B0);
	clear_Bit(TCCR1A,COM1B1);

#elif TMR1_OCB_MODE == NORMAL_MODE

	clear_Bit(TCCR1A,COM1B1);
	clear_Bit(TCCR1A,COM1B0);

#endif


#endif

}

void TMR1_prescallar(){


#if TMR1_PRESCALE == NO_CLOCK
	clear_Bit(TCCR1B,CS10);
	clear_Bit(TCCR1B,CS11);
	clear_Bit(TCCR1B,CS12);

#elif TMR1_PRESCALE == CLOCK_NO_PRESCALE
	set_Bit(TCCR1B,CS10);
	clear_Bit(TCCR1B,CS11);
	clear_Bit(TCCR1B,CS12);

#elif TMR1_PRESCALE == TMR1_CLK_8

	set_Bit(TCCR1B,CS11);
	clear_Bit(TCCR1B,CS10);
	clear_Bit(TCCR1B,CS12);

#elif TMR1_PRESCALE == TMR1_CLK_64

	set_Bit(TCCR1B, CS10);
	set_Bit(TCCR1B, CS11);
	clear_Bit(TCCR1B,CS12);

#elif TMR1_PRESCALE == TMR1_CLK_256

	clear_Bit(TCCR1B,CS10);
	clear_Bit(TCCR1B,CS11);
	set_Bit(TCCR1B,CS12);

#elif TMR1_PRESCALE == TMR1_CLK_1024

	set_Bit(TCCR1B,CS10);
	clear_Bit(TCCR1B,CS11);
	set_Bit(TCCR1B,CS12);

#elif TMR1_PRESCALE == TMR1_EXT_FALL
	set_Bit(TCCR1B,CS12);
	set_Bit(TCCR1B,CS11);
	clear_Bit(TCCR1B,CS10);

#elif TMR1_PRESCALE == TMR1_EXT_RISE

	set_Bit(TCCR1B,CS12);
	set_Bit(TCCR1B,CS11);
	set_Bit(TCCR1B,CS10);

#else
#warning "please choose the correct prescaling configuration from the config file"
#endif


}


void TMR1_loadTCNT1(u16 value){

	TCNT1 = value;
}


void TMR1_loadOCR1A(u16 value){

	OCR1A = value;

}

void TMR1_loadOCR1B(u16 value){

	OCR1B = value;

}


void TMR1_Stop(){

	clear_Bit(TCCR1B,CS10);
	clear_Bit(TCCR1B,CS11);
	clear_Bit(TCCR1B,CS12);


}

void TMR1_Init(){

	TMR1_mode();
	TMR1_OC_Setup();
	TMR1_prescallar();

	ICR1 = TMR1_ICR_VALUE;

#if TMR1_OVF_INTERRUPT == ENABLE

	set_Bit(TIMSK, TOIE1);
	set_Bit(SREG,7);

#elif TMR1_OCA_INTERRUPT == ENABLE
	set_Bit(TIMSK, OCIE1A);
	set_Bit(SREG,7);

#elif TMR1_OCB_INTERRUPT == ENABLE
	set_Bit(TIMSK, OCIE1B);
	set_Bit(SREG,7);

#elif TMR1_IC_INTERRUPT == ENABLE
	set_Bit(TIMSK, TICIE1);
	set_Bit(SREG,7);



#endif

}


/*************************** TIMER 1 ICU ***************************/


void TMR1_ICU_Enable(u8 copy_u8_edge_select){

	switch(copy_u8_edge_select){

	case ICU_FALLING_EDGE:
		clear_Bit(TCCR1B,ICES1); // select falling edge for icu
		set_Bit(TCCR1B,ICNC1); // enable noise canceling
		break;

	case ICU_RISING_EDGE:
		set_Bit(TCCR1B,ICES1); // select rising edge for icu
		set_Bit(TCCR1B,ICNC1); // enable noise canceling
		break;


	}
}

void TMR1_ICU_Disable(){

	/*
	 * disables icu interrupt
	 *
	 */

	clear_Bit(TIMSK,TICIE1); // disable icu interrupt
}

u16 TMR1_ICU_read(){

	return ICR1;
}

void TMR1_ICU_Set_TCNT1(u16 value){

	TCNT1 = value;

}

// ISR for timer1 ICU
void __vector_6(){

	if(callback_func[TIMER1_ICU] != NULL){

			callback_func[TIMER1_ICU]();

		}


}

// ISR for timer1 on compare channel B
void __vector_7(){

	if(callback_func[TIMER1_COMPB] != NULL){

			callback_func[TIMER1_COMPB]();

		}

}
//ISR for timer1 on compare channel A
void __vector_8(){

	if(callback_func[TIMER1_COMPA] != NULL){

			callback_func[TIMER1_COMPA]();

		}



}
// ISR for timer1 Overflow
void __vector_9(){

	if(callback_func[TIMER1_OVF] != NULL){

			callback_func[TIMER1_OVF]();

		}

}



/*************************** TIMER2 ***************************/

void TMR2_prescaller() {
#if TMR2_PRESCALE == NO_CLOCK
    clear_Bit(TCCR2, CS20);
    clear_Bit(TCCR2, CS21);
    clear_Bit(TCCR2, CS22);
#elif TMR2_PRESCALE == CLOCK_NO_PRESCALE
    set_Bit(TCCR2, CS20);
    clear_Bit(TCCR2, CS21);
    clear_Bit(TCCR2, CS22);
#elif TMR2_PRESCALE == TMR2_CLK_8
    set_Bit(TCCR2, CS21);
    clear_Bit(TCCR2, CS20);
    clear_Bit(TCCR2, CS22);
#elif TMR2_PRESCALE == TMR2_CLK_32
    set_Bit(TCCR2, CS20);
    set_Bit(TCCR2, CS21);
    clear_Bit(TCCR2, CS22);
#elif TMR2_PRESCALE == TMR2_CLK_64
    clear_Bit(TCCR2, CS20);
    clear_Bit(TCCR2, CS21);
    set_Bit(TCCR2, CS22);
#elif TMR2_PRESCALE == TMR2_CLK_128
    set_Bit(TCCR2, CS20);
    clear_Bit(TCCR2, CS21);
    set_Bit(TCCR2, CS22);
#elif TMR2_PRESCALE == TMR2_CLK_256
    clear_Bit(TCCR2, CS20);
    set_Bit(TCCR2, CS21);
    set_Bit(TCCR2, CS22);
#elif TMR2_PRESCALE == TMR2_CLK_1024
    set_Bit(TCCR2, CS20);
    set_Bit(TCCR2, CS21);
    set_Bit(TCCR2, CS22);
#else
#warning "Please choose the correct prescaling configuration from the config file"
#endif
}

void TMR2_OC2_setup() {
#if TMR2_OC2_MODE == OC_DISCONNECTED
    clear_Bit(TCCR2, COM20);
    clear_Bit(TCCR2, COM21);
#elif TMR2_OC2_MODE == OC_TOGGLE
    clear_Bit(TCCR2, COM21);
    set_Bit(TCCR2, COM20);
#elif TMR2_OC2_MODE == OC_CLEAR
    clear_Bit(TCCR2, COM20);
    set_Bit(TCCR2, COM21);
#elif TMR2_OC2_MODE == OC_SET
    set_Bit(TCCR2, COM20);
    set_Bit(TCCR2, COM21);
#else
#warning "Please choose the correct OC2 configuration from the configuration file"
#endif
}

void TMR2_mode(){
#if TMR2_MODE == NORMAL_MODE
    clear_Bit(TCCR2, WGM20);
    clear_Bit(TCCR2, WGM21);
#elif TMR2_MODE == CTC
    clear_Bit(TCCR2, WGM20);
    set_Bit(TCCR2, WGM21);
#elif TMR2_MODE == FAST_PWM
    set_Bit(TCCR2, WGM20);
    set_Bit(TCCR2, WGM21);
#else
#warning "Please choose the correct Timer2 mode from the configuration file"
#endif
}

void TMR2_Stop() {
    clear_Bit(TCCR2, CS20);
    clear_Bit(TCCR2, CS21);
    clear_Bit(TCCR2, CS22);
}

void TMR2_loadTCNT2(u8 value) {
    TCNT2 = value;
}

void TMR2_loadOCR2(u8 value) {
    OCR2 = value;
}

void TMR2_Init() {
    TMR2_mode();
    TMR2_OC2_setup();
    TMR2_prescaller();

#if TMR2_OVF_INTERRUPT == ENABLE && TMR2_OC_INTERRUPT == DISABLE
    // Enable Timer2 overflow interrupt
    set_Bit(TIMSK, TOIE2);
    // Enable global interrupt
    set_Bit(SREG, 7);
#elif TMR2_OVF_INTERRUPT == DISABLE && TMR2_OC_INTERRUPT == ENABLE
    // Enable Timer2 output compare interrupt
    set_Bit(TIMSK, OCIE2);
    // Enable global interrupt
    set_Bit(SREG, 7);
#else
    // Enable Timer2 overflow interrupt
    set_Bit(TIMSK, TOIE2);
    // Enable Timer2 output compare interrupt
    set_Bit(TIMSK, OCIE2);
    // Enable global interrupt
    set_Bit(SREG, 7);
#endif
}

// ISR for Timer2 overflow interrupt
void __vector_5(){

	if(callback_func[TIMER2_OVF] != NULL){

			callback_func[TIMER2_OVF]();

		}

}

// ISR for Timer2 output compare interrupt
void __vector_4(){

	if(callback_func[TIMER2_COMP] != NULL){

			callback_func[TIMER2_COMP]();

		}


}


/*************************** WATCHDOG TIMER ***************************/



void WDT_Enable(u8 copy_mode){

	set_Bit(WDTCR,WDE);
	SREG |= (1<<7);
    WDTCR &= ~((1 << WDP2) | (1 << WDP1) | (1 << WDP0));
	WDTCR |= (0b00000111 & copy_mode);

}

void WDT_Disable(){

	WDTCR = ((1<<WDTOE) | (1<<WDE));
	WDTCR = 0;

}

