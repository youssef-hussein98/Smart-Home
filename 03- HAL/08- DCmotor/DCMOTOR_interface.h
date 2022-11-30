#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_


typedef struct 
{
    uint_8 port_ID :4;
    uint_8 pin_ID  :4;
}ST_DCmotor;

typedef enum
{
    MOTOR_STOP, MOTOR_MOVE
}EN_DCMotorstate;

/* Initialize motor */
void H_DCmotorInit(ST_DCmotor DcMotor_object);
/* change motor state */
void H_DCmotor_voidChangeState (ST_DCmotor dcmotor_object, EN_DCMotorstate newState);
/* return motor state */
EN_DCMotorstate H_DCmotor_EnGetState (ST_DCmotor dcmotor_object);

#endif /* DCMOTOR_INTERFACE_H_ */
