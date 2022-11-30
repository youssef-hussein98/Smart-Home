#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


/* PORT functions  */
void MDIO_voidSetPortDirection(uint_8 copy_u8PortId, uint_8 copy_u8PortDirection);
void MDIO_voidSetPortValue(uint_8 copy_u8PortId, uint_8 copy_u8PortValue);

/* PIN functions */
void MDIO_voidSetPinDirection(uint_8 copy_u8PortId, uint_8 copy_u8PinId, uint_8 copy_u8PinDirection);
void MDIO_voidSetPinValue(uint_8 copy_u8PortId, uint_8 copy_u8PinId, uint_8 copy_u8PinValue);
uint_8 MDIO_u8GetPinValue(uint_8 copy_u8PortId, uint_8 copy_u8PinId);



#endif
