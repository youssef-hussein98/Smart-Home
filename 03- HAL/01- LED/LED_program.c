#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "../../02- MCAL/01- DIO/DIO_interface.h"

#include "LED_interface.h"


/* initialize the pin as output*/
void H_LED_void_init(ST_LED LED_Object)
{
    MDIO_voidSetPinDirection(LED_Object.port_ID,LED_Object.pin_ID,OUTPUT);
}




/* set pin value to high*/
void H_LED_voidChangeState(ST_LED LED_Object,EN_LED NewState)
{

    MDIO_voidSetPinValue(LED_Object.port_ID,LED_Object.pin_ID,(uint_8)NewState);

}



/* set pin value to low*/
EN_LED H_LED_EnGetState(ST_LED LED_Object)
{

	return MDIO_u8GetPinValue(LED_Object.port_ID, LED_Object.pin_ID);

}
