#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_


typedef struct 
{
    uint_8 port_ID :4;
    uint_8 pin_ID  :4;
}ST_Buzzer;

typedef enum
{
    BUZZER_OFF, BUZZER_ON
}EN_Buzzerstate;

/* Initialize Buzzer */
void H_BuzzerInit(ST_Buzzer Buzzer_object);
/* change Buzzer state */
void H_Buzzer_voidChangeState (ST_Buzzer Buzzer_object, EN_Buzzerstate newState);
/* return Buzzer state */
EN_Buzzerstate H_Buzzer_EnGetState (ST_Buzzer Buzzer_object);

#endif /* Buzzer_INTERFACE_H_ */
