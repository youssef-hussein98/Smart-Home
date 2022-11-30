#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "../../02- MCAL/01- DIO/DIO_interface.h"

#include "DCMOTOR_interface.h"

/* intialize motor */
void H_DCmotorInit(ST_DCmotor DcMotor_object)
{
    MDIO_voidSetPinDirection(DcMotor_object.port_ID, DcMotor_object.pin_ID, OUTPUT);
}

/* change motor state */
void H_DCmotor_voidChangeState (ST_DCmotor dcmotor_object, EN_DCMotorstate newState)
{
    MDIO_voidSetPinValue(dcmotor_object.port_ID, dcmotor_object.pin_ID, (uint_8)newState);
}

/* return motor state */
EN_DCMotorstate H_DCmotor_EnGetState (ST_DCmotor dcmotor_object)
{
    return MDIO_u8GetPinValue(dcmotor_object.port_ID, dcmotor_object.pin_ID);
}
