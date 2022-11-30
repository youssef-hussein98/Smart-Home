#ifndef EEPROM_REGISTERS_H_
#define EEPROM_REGISTERS_H_


#define EEAR    *((volatile uint_16*) 0x3E)

#define EEDR    *((volatile uint_8*) 0x3D )    

#define EECR    *((volatile uint_8*) 0x3C )  
/* EECR bits*/
#define EERE        0
#define EEWE        1
#define EEMWE       2
#define EERIE       3


#endif /* EEPROM_REGISTERS_H_ */
