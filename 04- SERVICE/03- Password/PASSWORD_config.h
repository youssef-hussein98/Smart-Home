#ifndef PASSWORD_CONFIG_H_
#define PASSWORD_CONFIG_H_


/* configure password length */
#define PASSWORD_LENGTH                 ((uint_8)4)

/* configure password save directory
 * RAM
 * INTERNAL_EEPROM
 * EXTERNAL_EEPROM
 */
#define PASSWORD_SAVE_DIRECTORY         RAM
#define PASSWORD_START_ADDRESS          ((uint_16)0x0000)  
/* only used if PASSWORD_SAVE_DIRECTORY equals RAM */
#define PASSWORD_INTIAL_VALUE           "0000"

#endif
