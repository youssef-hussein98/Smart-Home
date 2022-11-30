#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "../01- DIO/DIO_interface.h"

/* Module Files */
#include "TIMER_interface.h"
#include "TIMER_registers.h"
#include "TIMER_private.h"
#include "TIMER_config.h"


/************************************** Timer0 ******************************************/

/*
 * Global Object
 */
static uint_32 Global_NumOfCountsNeeded = 0;
static void (* G_ptr_TIMER0Notification) (void) = NULL;

/*
 * Function Definition 
 */
void M_TIMER0_void_Init()
{

	/* clear previous Initializations */
	TCCR0 = 0;
	/* Initialize the mode for the selected option in configuration file */
	TCCR0 |=  TIMER0_MODE;

	/* the oc0 configuration */
	TCCR0 |= TIMER0_OC0_PIN_CONFIG;

	/* Select the CTC Top */
	OCR0 = TIMER0_CTC_TOP_VALUE;

	/* Initialize the Counter */
	TCNT0 = TIMER0_PRELOAD_VALUE;

	/* Enable the Interrupt for the required mode */
	#if   TIMER0_MODE == TIMER0_MODE_OVERFLOW
		SET_BIT(TIMSK, TOIE0);
	#elif TIMER0_MODE == TIMER0_MODE_CTC
		SET_BIT(TIMSK, OCIE0);
	#endif

	/* Mainly used in PWM modes*/
	#if (TIMER0_OC0_PIN_CONFIG != NORMAL_PORT_OPERATION)
	MDIO_voidSetPinDirection(PORTB,PIN3,OUTPUT);
	#endif

}

void M_TIMER0_void_StartClock(void)
{
	/* start the Clock Source for the selected option in configuration file */
	TCCR0 = (TCCR0 & TIMER0_SELECT_CLOCK_MASKING) | (TIMER0_CLOCK_SOURCE);
}

void M_TIMER0_void_StopClock(void)
{
	/* stop the Clock Source  */
	TCCR0 = (TCCR0 & TIMER0_SELECT_CLOCK_MASKING) | (0);
}

void M_TIMER0_void_TimerStartCounting(void (* ptr_TIMER0SetCallBack)(void), uint_32 copy_counts)
{
	/* stop clock to prevent data corruption */
	M_TIMER0_void_StopClock();

	Global_NumOfCountsNeeded = copy_counts;

	if (ptr_TIMER0SetCallBack != NULL){
		G_ptr_TIMER0Notification = ptr_TIMER0SetCallBack;

	}else
	{
		/* Error */
	}
	/* restore clock */
	M_TIMER0_void_StartClock();
}


void M_TIMER0_void_SetDutyCycle(uint_8 copy_DutyCycle)
{
	/* stop clock to prevent data corruption */
	M_TIMER0_void_StopClock();

	OCR0 = copy_DutyCycle;

	/* restore clock */
	M_TIMER0_void_StartClock();

}

/*
 * ISR body definition 
 */
#if  TIMER0_MODE == TIMER0_MODE_CTC
/* ISR for CTC */
 void __vector_10 (void) {
	 static volatile uint_32 local_CTC_counter = 0;
	 local_CTC_counter++;
	 if (local_CTC_counter >= Global_NumOfCountsNeeded){
		 TCNT0 = TIMER0_PRELOAD_VALUE;
		 if (G_ptr_TIMER0Notification != NULL){
			 G_ptr_TIMER0Notification();
		 }else {
			 /* Error */
		 }
		 /* to allow the required time to be measured again */
		 local_CTC_counter = 0;
		/* stop clock in one shot mode */
		#if TIMER0_AUTO_RESTART == 0
		 M_TIMER0_void_StopClock();
		#endif
	 }
}
#elif TIMER0_MODE == TIMER0_MODE_NORMAL
/* ISR for Overflow */
 void __vector_11 (void) {

	 static volatile uint_32 local_OV_counter = 0;
	 local_OV_counter++;
	 if (local_OV_counter >= Global_NumOfCountsNeeded){
		 TCNT0 = TIMER0_PRELOAD_VALUE;
		 if (G_ptr_TIMER0Notification != NULL){
			 G_ptr_TIMER0Notification();
		 }else {
			 /* Error */
		 }
		 /* to allow the required time to be measured again */
		 local_OV_counter = 0;
		/* stop clock in one shot mode */
		#if TIMER0_AUTO_RESTART == 0
		 M_TIMER0_void_StopClock();
		#endif
	 }
 }
#endif

/************************************** Timer1 ******************************************/

/*
 * Global Object
 */
void (* G_ptr_TIMER1IcuNotification) (void) = NULL;
uint_16 *G_ptr_u16_Counts = NULL;

/*
 * Function Definition 
 */
void M_TIMER1_void_Init(void){
	/* Initialize the Clock Source for the selected option in configuration file */
	TCCR1B = (TCCR1B & TIMER1_SELECT_CLOCK_MASKING) | (TIMER1_CLOCK_SOURCE);

/* Initialize the mode for the selected option in configuration file */
	#if   TIMER1_MODE == TIMER1_MODE_FAST_PWM_TOP_ICR1
	/* Set the channel & Inverting or Non-Inverting Mode */
	#if   TIMER1_CHANNEL == TIMER1_CHANNEL_A
		/* Set pin as output */
		M_DIO_void_WritePinDir(M_DIO_PORTID_PORTD, M_DIO_PINID_PIN5, M_DIO_PINDIR_OUTPUT);
		#if   TIMER1_CHANNEL_MODE == TIMER1_CHANNEL_MODE_INVERTING
			SET_BIT(TCCR1A, COM1A1);
			SET_BIT(TCCR1A, COM1A0);
		#elif TIMER1_CHANNEL_MODE == TIMER1_CHANNEL_MODE_NON_INVERTING
			SET_BIT(TCCR1A, COM1A1);
			CLR_BIT(TCCR1A, COM1A0);
		#endif
	#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B
		/* Set pin as output */
		M_DIO_void_WritePinDir(M_DIO_PORTID_PORTD, M_DIO_PINID_PIN4, M_DIO_PINDIR_OUTPUT);
		#if   TIMER1_CHANNEL_MODE == TIMER1_CHANNEL_MODE_INVERTING
			SET_BIT(TCCR1A, COM1B1);
			SET_BIT(TCCR1A, COM1B0);
		#elif TIMER1_CHANNEL_MODE == TIMER1_CHANNEL_MODE_NON_INVERTING
			SET_BIT(TCCR1A, COM1B1);
			CLR_BIT(TCCR1A, COM1B0);
		#endif
	#endif
	

	/* Initialize the top */
	ICR1 = TIMER1_TOP_VALUE;
	
	/* Initialize the counter */
	TCNT1 = 0;
	
#elif TIMER1_MODE == TIMER1_MODE_ICU
	MDIO_voidSetPinDirection(PORTD, PIN6, INPUT);
	SET_BIT(TCCR1B,	ICES1);
#endif
}

void M_TIMER1_void_SetDuty(uint_8 copy_u8_DutyCycle){
#if TIMER1_CHANNEL == TIMER1_CHANNEL_A
	OCR1A = copy_u8_DutyCycle;
#elif TIMER1_CHANNEL == TIMER1_CHANNEL_B
	OCR1B = copy_u8_DutyCycle;
#endif
}

void M_TIMER1_void_SetIcuCallBack(void (* ptr_FunSetCallBack)(void)){
#if TIMER1_MODE == TIMER1_MODE_ICU
	/* Store the function to be called */
	if (ptr_FunSetCallBack != NULL){
		G_ptr_TIMER1IcuNotification = ptr_FunSetCallBack;
	}else{
		/* Error */
	}
	/* Enable ICU interrupt */
	SET_BIT(TIMSK, TICIE1);
#endif
}

void M_TIMER1_void_SetTriggeringEdge(uint_8 copy_EdgeID){
	if (copy_EdgeID == M_TIMER1_TRIGGERING_MODE_FALLING){
		SET_BIT(TCCR1B,	ICES1);
	}else if (copy_EdgeID == M_TIMER1_TRIGGERING_MODE_RISING){
		CLEAR_BIT(TCCR1B,	ICES1);
	}
}

void M_TIMER1_void_ClearTimerValue(void){
	TCNT1 = 0;
}

void M_TIMER1_void_GetIcuValue(uint_16 * ptr_u16_IcuValue){
	*ptr_u16_IcuValue = ICR1;
}

/*
 * ISR body definition 
 */

/* ISR for ICU */
void __vector_6 (void) {
	if (G_ptr_TIMER1IcuNotification != NULL){
		G_ptr_TIMER1IcuNotification();
	}else {
		/* Error */
	}

}

