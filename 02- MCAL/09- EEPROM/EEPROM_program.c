#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "../02- GIE/GIE_interface.h"

#include "EEPROM_registers.h"
#include "EEPROM_interface.h"

/* write a byte on specific address in internal eeprom memory */
void M_EEPROM_voidWriteByte(uint_16 copy_address, uint_8 copy_data)
{
    /* Wait for completion of previous write */
    while(GET_BIT(EECR,EEWE))
    ;
    /* Set up address and data registers */
    EEAR = copy_address;
    EEDR = copy_data;
    /* Write logical one to EEMWE */
    SET_BIT(EECR,EEMWE);
    /* Start eeprom write by setting EEWE */
    SET_BIT(EECR,EEWE);
}

/*read from eeprom memory and return the data in specific address*/
uint_8 M_EEPROM_u8ReadByte(uint_16 copy_address)
{
    /* Wait for completion of previous write */
    while(GET_BIT(EECR,EEWE))
    ;
    /* Set up address register */
    EEAR = copy_address;
    /* Start eeprom read by writing EERE */
    SET_BIT(EECR,EERE);
    /* Return data from data register */
    return EEDR;
}
