#ifndef _TIMER_CFG_H
#define _TIMER_CFG_H

/************************************** Timer0 ******************************************/

/* Select the required option for Timer mode
 * TIMER0_MODE_NORMAL             - TIMER0_MODE_CTC
 * TIMER0_MODE_PWM                  - TIMER0_MODE_FAST_PWM
 */
#define TIMER0_MODE TIMER0_MODE_PWM

/* Select the required option for timer clock source
 * TIMER0_CLOCK_SOURCE_STOP            - TIMER0_CLOCK_SOURCE_PRESCALER_1
 * TIMER0_CLOCK_SOURCE_PRESCALER_8     - TIMER0_CLOCK_SOURCE_PRESCALER_64
 * TIMER0_CLOCK_SOURCE_PRESCALER_256   - TIMER0_CLOCK_SOURCE_PRESCALER_1024
 * TIMER0_CLOCK_SOURCE_EXTERNAL_RISING - TIMER0_CLOCK_SOURCE_EXTERNAL_FALLING
 */
#define TIMER0_CLOCK_SOURCE TIMER0_CLOCK_SOURCE_PRESCALER_8

/* Set the Top value for CTC mode */
/*Max value id 255 */
#define TIMER0_CTC_TOP_VALUE         50

/* Set the required initial value */
/* NOTE: the timer count from 0 to 255
 * 		the first count will start from the pre-load value
 *		then the timer will start from 0 to 255
 *		until it reach the desired number of counts
 */
/*Max value id 255 */
#define TIMER0_PRELOAD_VALUE         0

/* Select the required option for OC0 pin configuration
 * - NORMAL_PORT_OPERATION
 * - TOGGLE_ON_COMPARE_MATCH 		NOTE: only valid in non-PWM modes
 * - CLEAR_ON_COMPARE_MATCH
 * - SET_ON_COMPARE_MATCH
 */
#define TIMER0_OC0_PIN_CONFIG CLEAR_ON_COMPARE_MATCH

/* if enabled the timer will auto restart  */
#define TIMER0_AUTO_RESTART			1

/************************************** Timer1 ******************************************/

/* Select the required option for Timer mode 
 * TIMER1_MODE_FAST_PWM_TOP_ICR1 - TIMER1_MODE_ICU
 */
#define TIMER1_MODE 				TIMER1_MODE_ICU


/* Select the required option for timer clock source
 * TIMER1_CLOCK_SOURCE_STOP            - TIMER1_CLOCK_SOURCE_PRESCALER_1
 * TIMER1_CLOCK_SOURCE_PRESCALER_8     - TIMER1_CLOCK_SOURCE_PRESCALER_64
 * TIMER1_CLOCK_SOURCE_PRESCALER_256   - TIMER1_CLOCK_SOURCE_PRESCALER_1024
 * TIMER1_CLOCK_SOURCE_EXTERNAL_RISING - TIMER1_CLOCK_SOURCE_EXTERNAL_FALLING
 */
#define TIMER1_CLOCK_SOURCE       TIMER1_CLOCK_SOURCE_PRESCALER_8


/* Set the top value */
#define TIMER1_TOP_VALUE			2500


/* Select the Required Channel to output PWM
 * TIMER1_CHANNEL_A - TIMER1_CHANNEL_B
 */
#define TIMER1_CHANNEL			TIMER1_CHANNEL_A


/* Select the Required leading edge
 * TIMER1_CHANNEL_MODE_INVERTING - TIMER1_CHANNEL_MODE_NON_INVERTING 
 */
#define TIMER1_CHANNEL_MODE 		TIMER1_CHANNEL_MODE_NON_INVERTING

#endif /* _TIMER0_CFG_H */
