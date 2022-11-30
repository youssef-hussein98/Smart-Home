#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "DIO_interface.h"
#include "DIO_registers.h"


void MDIO_voidSetPortDirection(uint_8 copy_u8PortId, uint_8 copy_u8PortDirection)
{
    if (copy_u8PortId<=PORTD)
    {
        DDRx_REG(copy_u8PortId) = copy_u8PortDirection;
    }    
}

void MDIO_voidSetPortValue(uint_8 copy_u8PortId, uint_8 copy_u8PortValue)
{
    if (copy_u8PortId <= PORTD)
    {
        PORTx_REG(copy_u8PortId) = copy_u8PortValue;
    }
}

void MDIO_voidSetPinDirection(uint_8 copy_u8PortId, uint_8 copy_u8PinId, uint_8 copy_u8PinDirection)
{
    if (copy_u8PortId <= PORTD && copy_u8PinId <= 7)
    {
        switch (copy_u8PinDirection&1)
        {
        case (OUTPUT&1):
            SET_BIT(DDRx_REG(copy_u8PortId), copy_u8PinId);
            break;

        case (INPUT&1):
            CLEAR_BIT(DDRx_REG(copy_u8PortId), copy_u8PinId);
            break;
        }
    }
}

void MDIO_voidSetPinValue(uint_8 copy_u8PortId, uint_8 copy_u8PinId, uint_8 copy_u8PinValue)
{
    if (copy_u8PortId <= PORTD && copy_u8PinId <= 7)
    {
        switch (copy_u8PinValue&3)
        {
        case (HIGH&3):
            SET_BIT(PORTx_REG(copy_u8PortId), copy_u8PinId);
            break;

        case (LOW&3):
            CLEAR_BIT(PORTx_REG(copy_u8PortId), copy_u8PinId);
            break;

        case (TOGGLE&3):
            TOGGLE_BIT(PORTx_REG(copy_u8PortId), copy_u8PinId);
            break;
        }
    }
}

uint_8 MDIO_u8GetPinValue(uint_8 copy_u8PortId, uint_8 copy_u8PinId)
{
    if (copy_u8PortId <= PORTD && copy_u8PinId <= 7)
    {
        return GET_BIT(PINx_REG(copy_u8PortId), copy_u8PinId);
    }
    else
        return NOK;
}
