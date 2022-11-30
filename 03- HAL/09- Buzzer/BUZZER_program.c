#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "../../02- MCAL/01- DIO/DIO_interface.h"

#include "BUZZER_interface.h"

/* Initialize Buzzer */
void H_BuzzerInit(ST_Buzzer Buzzer_object)
{
    MDIO_voidSetPinDirection(Buzzer_object.port_ID, Buzzer_object.pin_ID, OUTPUT);
}

/* change Buzzer state */
void H_Buzzer_voidChangeState (ST_Buzzer Buzzer_object, EN_Buzzerstate newState)
{
    MDIO_voidSetPinValue(Buzzer_object.port_ID, Buzzer_object.pin_ID, (uint_8)newState);
}

/* return Buzzer state */
EN_Buzzerstate H_Buzzer_EnGetState (ST_Buzzer Buzzer_object)
{
    return MDIO_u8GetPinValue(Buzzer_object.port_ID, Buzzer_object.pin_ID);
}
