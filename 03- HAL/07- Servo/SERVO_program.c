#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"
#include "../../02- MCAL/02- GIE/GIE_interface.h"
#include "../../02- MCAL/05- TIMER/TIMER_interface.h"


#include "SERVO_config.h"
#include"SERVO_interface.h"

void H_Servo_init(void)
{
	MGIE_voidEnable();
    #if (SERVO_TIMER_USED == TIMER0)
        /* Initialize timer0 PWM mode*/
        M_TIMER0_void_Init();
        /* timer 1 driver isn't completed yet */
    #elif SERVO_TIMER_USED == TIMER1
        /*Initialize timer0 PWM mode */
        M_TIMER1_void_Init();
        
        #if SERVO_TIMER1_CHANNEL == OC1A
            M_TIMER1_void_SelectChannel(OC1A);
        #elif SERVO_TIMER1_CHANNEL == OC1B
            M_TIMER1_void_SelectChannel(OC1B);
        #endif
    #elif SERVO_TIMER_USED == TIMER2
        /* Initialize timer2 PWM mode*/
        M_TIMER2_void_Init();
    #endif
}

void H_Servo_ChangeAngle(uint_8 angle)
{
    angle = MAP(angle, 0, 180, SERVO_DUTYCYCLE_MIN, SERVO_DUTYCYCLE_MAX);
    M_TIMER0_void_SetDutyCycle(angle);
}
