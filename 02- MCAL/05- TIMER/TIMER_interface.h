#ifndef _TIMER0_INT_H
#define _TIMER0_INT_H

/************************************** Timer0 ******************************************/

void M_TIMER0_void_Init(void);
/*enable global interrupt before this function call */
/* timer will start automatically after this function */
void M_TIMER0_void_TimerStartCounting(void (* ptr_TIMER0SetCallBack)(void), uint_32 copy_counts);
/* used in PWM modes*/
void M_TIMER0_void_SetDutyCycle(uint_8 copy_DutyCycle);

void M_TIMER0_void_StartClock(void);

void M_TIMER0_void_StopClock(void);

/************************************** Timer1 ******************************************/

#define M_TIMER1_TRIGGERING_MODE_FALLING    0
#define M_TIMER1_TRIGGERING_MODE_RISING     1

void M_TIMER1_void_Init(void);

void M_TIMER1_void_SetDuty(uint_8 copy_u8_DutyCycle);

/* ICU */
void M_TIMER1_void_SetIcuCallBack(void (* ptr_FunSetCallBack)(void));

void M_TIMER1_void_SetTriggeringEdge(uint_8 copy_EdgeID);

void M_TIMER1_void_ClearTimerValue(void);

void M_TIMER1_void_GetIcuValue(uint_16 * ptr_u16_IcuValue);


#endif /* _TIMER0_INT_H */
