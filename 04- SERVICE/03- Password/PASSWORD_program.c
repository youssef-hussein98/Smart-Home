#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#if PASSWORD_SAVE_DIRECTORY == INTERNAL_EEPROM
    #include "../../02- MCAL/09- EEPROM/EEPROM_interface.h"
#elif PASSWORD_SAVE_DIRECTORY == EXTERNAL_EEPROM
    #include "../../03- HAL/external_eeprom.h"
#endif /* #if PASSWORD_SAVE_DIRECTORY */

#include "PASSWORD_interface.h"
#include "PASSWORD_config.h"
#include "PASSWORD_private.h"


char G_password[PASSWORD_LENGTH] = PASSWORD_INTIAL_VALUE;

void S_PASSWORD_voidInit(void)
{
    /* read the password from EEPROM and save it in global variable*/
    #if PASSWORD_SAVE_DIRECTORY == INTERNAL_EEPROM
    uint_8 local_counter = 0;
        for(local_counter = 0; local_counter < PASSWORD_LENGTH; local_counter++)
        {
            G_password[local_counter] = M_EEPROM_u8ReadByte(PASSWORD_START_ADDRESS + local_counter);
        }
        /* External EEPROM need to be initialized  */
    #elif PASSWORD_SAVE_DIRECTORY == EXTERNAL_EEPROM
        uint_8 local_counter = 0;
        H_EEPROM_init();
        for(local_counter =0; local_counter < PASSWORD_LENGTH; local_counter++)
        {
            G_password[local_counter] = H_EEPROM_readByte(PASSWORD_START_ADDRESS+local_counter);
        }
    #endif /* #if PASSWORD_SAVE_DIRECTORY */
}

uint_8 S_PASSWORD_u8_Check(char copy_password[])
{
    uint_8 local_counter = 0;
    for(local_counter =0; local_counter < PASSWORD_LENGTH; local_counter++)
    {
        /* if there is a different char the function will return incorrect */
        if( copy_password[local_counter] != G_password[local_counter])
        {
            return PASSWORD_INCORRECT;
        }
        else
        {
            /* Do nothing */
        }
    }
    return PASSWORD_CORRECT;
}
uint_8 S_PASSWORD_u8_CheckMatching(char copy_Password[],char copy_ConfirmPassword[])
{
    uint_8 local_counter = 0;
    for(local_counter =0; local_counter < PASSWORD_LENGTH; local_counter++)
    {
        /* if there is a different char the function will return incorrect */
        if( copy_Password[local_counter] != copy_ConfirmPassword[local_counter])
        {
            return PASSWORD_INCORRECT;
        }
        else
        {
            /* Do nothing */
        }
    }
    return PASSWORD_CORRECT;

}

uint_8 S_PASSWORD_u8_Change(char copy_NewPassword[])
{
    uint_8 local_counter = 0;
    /* copy password and save it in global variable*/
    /* if eeprom is used the new password then will be saved in the password start address */
    #if PASSWORD_SAVE_DIRECTORY == RAM
        for(local_counter =0; local_counter < PASSWORD_LENGTH; local_counter++)
        {
            G_password[local_counter] = copy_NewPassword[local_counter];
        }
        return PASSWORD_CHANGE_SUCCEED;
    #elif PASSWORD_SAVE_DIRECTORY == INTERNAL_EEPROM
        uint_8 local_save_flag;
        for(local_counter =0; local_counter < PASSWORD_LENGTH; local_counter++)
        {
            G_password[local_counter] = copy_NewPassword[local_counter];
            M_EEPROM_voidWriteByte(PASSWORD_START_ADDRESS + local_counter, G_password[local_counter]);
            /* check if the password is saved successfully in eeprom */
            if(copy_NewPassword[local_counter] == M_EEPROM_u8ReadByte(PASSWORD_START_ADDRESS + local_counter))
            {
                local_save_flag = PASSWORD_CHANGE_SUCCEED;
            }
            else
            {
                local_save_flag = PASSWORD_CHANGE_FAILED;
                break;
            }
        }
        return local_save_flag;
    #elif PASSWORD_SAVE_DIRECTORY == EXTERNAL_EEPROM
        /* check if the password is saved successfully in eeprom */
        for(local_counter =0; local_counter < PASSWORD_LENGTH; local_counter++)
        {
            G_password[local_counter] = copy_NewPassword[local_counter];
            H_EEPROM_writeByte(PASSWORD_START_ADDRESS + local_counter, G_password[local_counter]);
            if(copy_NewPassword[local_counter] == H_EEPROM_ReadByte(PASSWORD_START_ADDRESS + local_counter))
            {
                local_save_flag = PASSWORD_CHANGE_SUCCEED;
            }
            else
            {
                local_save_flag = PASSWORD_CHANGE_FAILED;
                break;
            }
        }
        return local_save_flag;
    #endif /* #if PASSWORD_SAVE_DIRECTORY */
}
