#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


/* write a byte on specific address in internal eeprom memory */
void M_EEPROM_voidWriteByte(uint_16 copy_address, uint_8 copy_data);

/*read from eeprom memory and return the data in specific address*/
uint_8 M_EEPROM_u8ReadByte(uint_16 copy_address);

/** WARNING: Interrupts must be disabled while using eeprom **/

#endif /* EEPROM_INTERFACE_H_ */
