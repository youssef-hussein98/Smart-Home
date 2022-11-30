#ifndef PASSWORD_INTERFACE_H_
#define PASSWORD_INTERFACE_H_

#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"


#define PASSWORD_CORRECT    ((uint_8)0)
#define PASSWORD_INCORRECT  ((uint_8)1)

#define PASSWORD_CHANGE_SUCCEED ((uint_8)0)
#define PASSWORD_CHANGE_FAILED  ((uint_8)1)

extern char G_password[4] ;
/* take the password from the address where it is saved in and save it in RAM */
void S_PASSWORD_voidInit(void);

/* Check if the password in correctly typed 
 * return PASSWORD_CORRECT if password right
 * return PASSWORD_INCORRECT if password Wrong
 */
uint_8 S_PASSWORD_u8_Check(char copy_password[]);

/* Check if the two string matches
 * return PASSWORD_CORRECT if matching
 * return PASSWORD_INCORRECT if not matching
 */
uint_8 S_PASSWORD_u8_CheckMatching(char copy_Password[],char copy_ConfirmPassword[]);

/* change the password 
 * return PASSWORD_CHANGE_SUCCEED if password copy_OldPassword equals copy_NewPassword
 * return PASSWORD_CHANGE_FAILED if password copy_OldPassword not equals copy_NewPassword
*/
uint_8 S_PASSWORD_u8_Change(char copy_NewPassword[]);


#endif
