#ifndef SERVO_CONFIG_H_
#define SERVO_CONFIG_H_


/* Please specify dutycycle which make servo goes to minimum angle */
#define SERVO_DUTYCYCLE_MIN         32

/* Please specify dutycycle which make servo goes to maximum angle */
#define SERVO_DUTYCYCLE_MAX         158


/* NOTE: only timer0 is working other timers' drivers aren't finished yet */

/* Choose the timer used:
 - TIMER0       -> PB3
 - TIMER1       ->PD5  OC1A
                ->PD4  OC1B
 - TIMER2       ->PD7
*/

#define SERVO_TIMER_USED TIMER0


/* as timer1 has 2 channels we need to specify which channel the servo is connected to
    - OC1A
    - OC1B
 */
#define SERVO_TIMER1_CHANNEL       OC1A


#endif