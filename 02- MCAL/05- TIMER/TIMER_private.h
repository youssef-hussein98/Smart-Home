#ifndef _TIMER_PRI_H
#define _TIMER_PRI_H

/************************************** Timer0 ******************************************/

/* Max number of counts */
#define TIMER0_MAX_COUNT_VALUE                  256

/* Options for Timer modes */
#define TIMER0_MODE_NORMAL   				    (0)
#define TIMER0_MODE_PWM	  				        (1<<WGM00)
#define TIMER0_MODE_CTC	  				        (1<<WGM01)
#define TIMER0_MODE_FAST_PWM			        ((1<<WGM01)|(1<<WGM00))

/* Masking for the Select Clock Bits */
#define TIMER0_SELECT_CLOCK_MASKING		        0xF8

/* Option for Clock Source */
#define TIMER0_CLOCK_SOURCE_STOP                0
#define TIMER0_CLOCK_SOURCE_PRESCALER_1         1
#define TIMER0_CLOCK_SOURCE_PRESCALER_8         2
#define TIMER0_CLOCK_SOURCE_PRESCALER_64        3
#define TIMER0_CLOCK_SOURCE_PRESCALER_256       4
#define TIMER0_CLOCK_SOURCE_PRESCALER_1024      5
#define TIMER0_CLOCK_SOURCE_EXTERNAL_RISING     6
#define TIMER0_CLOCK_SOURCE_EXTERNAL_FALLING    7

/* OC0 pin configuration */
 #define NORMAL_PORT_OPERATION			(0<<4)
 #define TOGGLE_ON_COMPARE_MATCH 		(1<<4)
 #define CLEAR_ON_COMPARE_MATCH			(2<<4)
 #define SET_ON_COMPARE_MATCH			(3<<4)

/*
 * ISR Compiler Attribute 
 */
void __vector_10 (void) __attribute__((signal));
void __vector_11 (void) __attribute__((signal));


/************************************** Timer1 ******************************************/


/* Masking for the Select Clock Bits */
#define TIMER1_SELECT_CLOCK_MASKING		   0xF8

/* Options for Timer modes */
#define TIMER1_MODE_FAST_PWM_TOP_ICR1		   0
#define TIMER1_MODE_ICU	  				   1

/* Options for selecting a channel */
#define TIMER1_CHANNEL_A 					   0
#define TIMER1_CHANNEL_B				       1

/* Options for selecting leading edge */
#define TIMER1_CHANNEL_MODE_INVERTING	       0
#define TIMER1_CHANNEL_MODE_NON_INVERTING	   1

/* Option for Clock Source */
#define TIMER1_CLOCK_SOURCE_STOP             0
#define TIMER1_CLOCK_SOURCE_PRESCALER_1      1
#define TIMER1_CLOCK_SOURCE_PRESCALER_8      2
#define TIMER1_CLOCK_SOURCE_PRESCALER_64     3
#define TIMER1_CLOCK_SOURCE_PRESCALER_256    4
#define TIMER1_CLOCK_SOURCE_PRESCALER_1024   5
#define TIMER1_CLOCK_SOURCE_EXTERNAL_RISING  6
#define TIMER1_CLOCK_SOURCE_EXTERNAL_FALLING 7

/*
 * ISR Compiler Attribute 
 */
/* ICU Interrupt */
void __vector_6 (void) __attribute__((signal));


#endif /* _TIMER0_PRI_H */
