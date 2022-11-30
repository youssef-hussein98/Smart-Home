#include "../01- LIB/std_types.h"
#include "../01- LIB/common_macros.h"

#include "../03- HAL/01- LED/LED_interface.h"
#include "../03- HAL/02- LCD/LCD_interface.h"
#include "../03- HAL/03- Keypad/KEYPAD_interface.h"
#include "../03- HAL/04- LM35/LM35_interface.h"
#include "../03- HAL/07- Servo/SERVO_interface.h"
#include "../03- HAL/08- DCmotor/DCMOTOR_interface.h"
#include "../03- HAL/09- Buzzer/BUZZER_interface.h"

#include "../04- SERVICE/03- Password/PASSWORD_interface.h"

#include "main.h"

/* initialize Struct for each led with the port and pin connected to */
ST_LED alert_led 	= {PORTC,PIN3};
ST_LED bath_led 	= {PORTC,PIN4};
ST_LED living_led 	= {PORTC,PIN5};
ST_LED bed_led 		= {PORTC,PIN6};
ST_LED kitchen_led 	= {PORTC,PIN7};

/* initialize Struct for each motor with the port and pin connected to */
ST_DCmotor living_fan 	= {PORTC,PIN0};
ST_DCmotor bed_fan 		= {PORTC,PIN1};

/* initialize Struct for each buzzer with the port and pin connected to */
ST_Buzzer buzzer = {PORTC,PIN2};

/* global variables used in the program */
EN_systemState G_system_State = IDLE;
EN_systemState G_system_PreviousState = IDLE;

/* lock flag is initially high */
ST_flags G_system_flags = {.lock = 1};
char G_EnteredString[4] = {};
char G_NewPassword[4] = {};


int main(void)
{
	APP_hardware_Init();
	HLCD_voidSendString(G_password);
	while(1)
	{
//		APP_CheckTemperature();
		/* start keypad handling */
//		HKEYPAD_voidManage(&APP_keypad_Handler);
	}
	return 0;
}

/* Start hardware initialization */
void APP_hardware_Init(void)
{
	/* LEDs */
	H_LED_void_init(alert_led);
	H_LED_voidChangeState(alert_led,LED_OFF);
	H_LED_void_init(bath_led);
	H_LED_voidChangeState(bath_led,LED_OFF);
	H_LED_void_init(living_led);
	H_LED_voidChangeState(living_led,LED_OFF);
	H_LED_void_init(bed_led);
	H_LED_voidChangeState(bed_led,LED_OFF);
	H_LED_void_init(kitchen_led);
	H_LED_voidChangeState(kitchen_led,LED_OFF);

	/* LCD */
	HLCD_voidInitialize();

	/* keypad */
	HKEYPAD_voidInitialize();

	/* LM35 */
	HLM35_Init();

	/* Servo */
	H_Servo_init();
	H_Servo_ChangeAngle(DOOR_LOCKED);

	/* DC motors */
	H_DCmotorInit(living_fan);
	H_DCmotor_voidChangeState(living_fan,MOTOR_STOP);
	H_DCmotorInit(bed_fan);
	H_DCmotor_voidChangeState(bed_fan,MOTOR_STOP);

	/* Buzzer */
	H_BuzzerInit(buzzer);

	/* Password */
	S_PASSWORD_voidInit();
	/* end hardware initialization */

	/* create some emojis */
	HLCD_voidCreateChar(CHAR_UNLOCKED,LCD_UNLOCKED);
	HLCD_voidCreateChar(CHAR_LOCKED,LCD_LOCKED);
	HLCD_voidCreateChar(CHAR_HEART,LCD_HEART);

	/* welcome message */
//	HLCD_voidSendString("Welcome ");
	/* print Heart */
//	HLCD_voidSendChar(CHAR_HEART);
//	HLCD_voidSetCursor(1,0);
//	HLCD_voidSendString("press any key");
}


void APP_CheckTemperature(void)
{
	/* check the reading of the sensor if temperature exceed critical limit */
	G_system_flags.alert = (HLM35_Reading(0) > TEMPERATURE_CRITICAL_VALUE)? 1:0;


	if((G_system_flags.alert == 0))
	{

		switch(G_system_State)
		{

		case TEMP_WINDOW:
			/* update temperature */
			HLCD_voidSetCursor(1,0);
			HLCD_voidSendNumber(HLM35_Reading(0));
			HLCD_voidSendString("C   ");
			break;
		default:

			break;
		}
	}
	else if ((G_system_flags.alert == 0) && (G_system_State == ALERT_WINDOW))
	{
		/* if the critical case finished and alert window was displayed
		 * go to BACK_TO_NORMAL window
		 */
		G_system_State = BACK_TO_NORMAL;
		/* display BACK_TO_NORMAL window */
		APP_SetSystemWindow();

	}
	else if((G_system_flags.alert == 1))
	{
		G_system_State = ALERT_WINDOW;
		/* if emergency happened the password string will reset */
		G_system_flags.Password_NumOfCharEntered = 0;
		APP_SetSystemWindow();

	}else
	{
		/* do nothing */
	}

}

/* LCD window */
void APP_SetSystemWindow(void)
{
	uint_8 local_characterCounter = 0;
	HLCD_voidClearScreen();
	switch (G_system_State)
	{

						/*************************************** IDLE ***************************************/
				case IDLE:
				/* do nothing */
				break;

					/*************************************** MAIN_WINDOW ***************************************/
				case MAIN_WINDOW:


					HLCD_voidSendString("1-LOCK   2-LIGHT");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("3-FANS   4-Temp.");
					G_system_PreviousState = MAIN_WINDOW;
					break;
					/*************************************** LOCK_OPTIONS ***************************************/
				case LOCK_OPTIONS:

					/* print options on LCD */
					/* print unlock if the door is Locked */
					/* print lock if the door is unlocked */
					/* return unlocked string if the door is already locked*/
					HLCD_voidSendString((G_system_flags.lock ==1)?"1-UnLock":"1-Lock");
					/* return unlocked character if the door is already locked*/
					HLCD_voidSetCursor(0,11);
					HLCD_voidSendChar((G_system_flags.lock ==1)?CHAR_UNLOCKED:CHAR_LOCKED);
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("2-Change Pass.");


					break;
					/*************************************** ENTER_PASSWORD ***************************************/
				case ENTER_PASSWORD:

					HLCD_voidSendString("Enter Password: ");
					for(local_characterCounter = 1;local_characterCounter <= 4;local_characterCounter++)
					{
						HLCD_voidSetCursor(1,3*local_characterCounter);
						if(local_characterCounter <= G_system_flags.Password_NumOfCharEntered)
						{
							HLCD_voidSendChar('*');
						}
						else
						{
							HLCD_voidSendChar('_');
						}
					}
					HLCD_voidSetCursor(1,1);


					break;
					/*************************************** CORRECT_PASSWORD ***************************************/
				case LOCK_STATE_CHANGE:


					/* change lock state */
					H_Servo_ChangeAngle(G_system_flags.lock *DOOR_LOCKED);

					if(G_system_flags.lock == 1)
					{
						HLCD_voidSendString("Door Locked   ");
						HLCD_voidSendChar(CHAR_LOCKED);

					}else
					{
						HLCD_voidSendString("Door Unlocked ");
						HLCD_voidSendChar(CHAR_UNLOCKED);

					}
						HLCD_voidSetCursor(1,0);
						HLCD_voidSendString("1-Lock  2-Unlock");

					break;
					/*************************************** INCORRECT_PASSWORD ***************************************/
				case INCORRECT_PASSWORD:

					HLCD_voidSendString("Wrong password");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("Try again");

					break;
					/*************************************** CHANGE_PASSWORD ***************************************/
				case CHANGE_PASSWORD:
					HLCD_voidSendString("Enter old Pass: ");

					for(local_characterCounter = 1;local_characterCounter <= 4;local_characterCounter++)
					{
						HLCD_voidSetCursor(1,3*local_characterCounter);
						if(local_characterCounter <= G_system_flags.Password_NumOfCharEntered)
						{
							HLCD_voidSendChar('*');
						}
						else
						{
							HLCD_voidSendChar('_');
						}
					}
					HLCD_voidSetCursor(1,1);

					break;
					/*************************************** NEW_PASSWORD ***************************************/
				case NEW_PASSWORD:

					HLCD_voidSendString("Enter new Pass: ");

					for(local_characterCounter = 1;local_characterCounter <= 4;local_characterCounter++)
					{
						HLCD_voidSetCursor(1,3*local_characterCounter);
						if(local_characterCounter <= G_system_flags.Password_NumOfCharEntered)
						{
							HLCD_voidSendChar('*');
						}
						else
						{
							HLCD_voidSendChar('_');
						}
					}
					HLCD_voidSetCursor(1,1);


					break;
					/*************************************** CONFIRM_NEW ***************************************/
				case CONFIRM_NEW:

					HLCD_voidSendString("Re-enter new P.:");

					for(local_characterCounter = 1;local_characterCounter <= 4;local_characterCounter++)
					{
						HLCD_voidSetCursor(1,3*local_characterCounter);
						if(local_characterCounter <= G_system_flags.Password_NumOfCharEntered)
						{
							HLCD_voidSendChar('*');
						}
						else
						{
							HLCD_voidSendChar('_');
						}
					}
					HLCD_voidSetCursor(1,1);


					break;
					/*************************************** PASSWORD_NOT_MATCH ***************************************/
				case PASSWORD_MATCH:

					HLCD_voidSendString("Password changed");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("Successfully");
					break;
					/*************************************** PASSWORD_NOT_MATCH ***************************************/
				case PASSWORD_NOT_MATCH:

					HLCD_voidSendString("Password Don't");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("Match");

					break;
					/*************************************** LIGHT_OPTIONS ***************************************/
				case LIGHT_OPTIONS:

					HLCD_voidSendString("1-Bath 2-Living ");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("3-Bed 	4-Kitchen");

					break;
					/*************************************** LIGHT_BATH ***************************************/
				case LIGHT_BATH:

					/* print the selected room and the light state */
					/* Check led state and print it on LCD */
					HLCD_voidSendString("1-Bath: ");
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString(H_LED_EnGetState(bath_led)?"ON ":"OFF");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("1-ON       2-OFF");

					break;
					/*************************************** LIGHT_LIVING ***************************************/
				case LIGHT_LIVING:

					/* print the selected room and the light state */
					/* Check led state and print it on LCD */
					HLCD_voidSendString("2-Living: ");
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString(H_LED_EnGetState(living_led)?"ON ":"OFF");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("1-ON       2-OFF");
					break;
					/*************************************** LIGHT_BED ***************************************/
				case LIGHT_BED:

					/* print the selected room and the light state */
					/* Check led state and print it on LCD */
					HLCD_voidSendString("3-Bed: ");
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString(H_LED_EnGetState(bed_led)?"ON ":"OFF");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("1-ON       2-OFF");
					break;

					/*************************************** LIGHT_KITCHEN ***************************************/
				case LIGHT_KITCHEN:

					/* print the selected room and the light state */
					/* Check led state and print it on LCD */
					HLCD_voidSendString("4-Kitchen: ");
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString(H_LED_EnGetState(kitchen_led)?"ON ":"OFF");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("1-ON       2-OFF");
					break;

					/*************************************** FAN_OPTIONS ***************************************/
				case FAN_OPTIONS:

					HLCD_voidSendString("1-Bed");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("2-Living");

					break;
					/*************************************** FAN_BED ***************************************/
				case FAN_BED:

					/* print the selected room and the light state */
					/* Check led state and print it on LCD */
					HLCD_voidSendString("1-Bed:");
					/* return ON if state is high and OFF if state low */
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString(H_DCmotor_EnGetState(bed_fan)?"ON ":"OFF");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("1-ON       2-OFF");
					break;
					/*************************************** FAN_LIVING ***************************************/
				case FAN_LIVING:

					/* print the selected room and the light state */
					/* Check led state and print it on LCD */
					HLCD_voidSendString("2-Living:");
					/* return ON if state is high and OFF if state low */
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString(H_DCmotor_EnGetState(living_fan)?"ON ":"OFF");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("1-ON       2-OFF");
					break;

					/*************************************** TEMP_WINDOW ***************************************/
				case TEMP_WINDOW:

					HLCD_voidSendString("4-Temperature:- ");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendNumber(HLM35_Reading(0));
					HLCD_voidSendString("C   ");
					break;
					/*************************************** ALERT_WINDOW ***************************************/

				case ALERT_WINDOW:
					/* Unlock Door */
					H_Servo_ChangeAngle(DOOR_UNLOCKED);
					/* turn off buzzer */
					H_Buzzer_voidChangeState(buzzer,BUZZER_ON);
					/* turn off alert led */
					H_LED_voidChangeState(alert_led,LED_ON);
					/* print alert */
					HLCD_voidSendString(" !!! ALERT !!!  ");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString("DOOR ULOCKED   ");
					/* print unlock special character */
					HLCD_voidSendChar(CHAR_UNLOCKED);
					break;
					/*************************************** BACK_TO_NORMAL ***************************************/

				case BACK_TO_NORMAL:
					/* return to previous state */
					H_Servo_ChangeAngle((G_system_flags.lock*90));
					/* turn off buzzer */
					H_Buzzer_voidChangeState(buzzer,BUZZER_OFF);
					/* turn off alert led */
					H_LED_voidChangeState(alert_led,LED_OFF);
					/* print welcome back message */
					HLCD_voidSendString(" Hope you are ");
					HLCD_voidSetCursor(1,0);
					HLCD_voidSendString(" safe   ");
					HLCD_voidSendChar(CHAR_HEART);

					break;
				}
}


void APP_keypad_Handler(void)
{
	G_system_PreviousState = G_system_State;

	switch (G_system_State) {
		case IDLE:
			G_system_State = MAIN_WINDOW;
		break;
		/*************************************** MAIN_WINDOW ***************************************/
		case MAIN_WINDOW:

			switch(HKEYPAD_u8GetPressedKey())
			{
			case '1':
				G_system_State = LOCK_OPTIONS;
				break;

			case '2':
				G_system_State = LIGHT_OPTIONS;
				break;

			case '3':
				G_system_State = FAN_OPTIONS;
				break;

			case '4':
				G_system_State = TEMP_WINDOW;
				break;

			default:
				break;
			}
		break;
		/*************************************** LOCK_OPTIONS ***************************************/
	case LOCK_OPTIONS:

		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
			G_system_State = ENTER_PASSWORD;
			break;

		case '2':
			G_system_State = CHANGE_PASSWORD;
			break;
		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = MAIN_WINDOW;
			break;
		default:
			break;
		}

		break;

		/*************************************** ENTER_PASSWORD ***************************************/
	case ENTER_PASSWORD:
		/* if the user pressed on a number the value will be saved in global array
		 * until the string reached 4 characters the press will have no effect
		 */
		if((HKEYPAD_u8GetPressedKey() >= '0') && (HKEYPAD_u8GetPressedKey() <= '9')
				&& (G_system_flags.Password_NumOfCharEntered < 4))
		{
			G_EnteredString[G_system_flags.Password_NumOfCharEntered] = HKEYPAD_u8GetPressedKey();

			G_system_flags.Password_NumOfCharEntered++;
			/* print star */
			HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
			HLCD_voidSendChar('*');

		}else if(HKEYPAD_u8GetPressedKey() == 'S' )
		{
			/* clear password character counter and return to main window */
			G_system_flags.Password_NumOfCharEntered = 0 ;
			G_system_State = MAIN_WINDOW;
		}
		else if(HKEYPAD_u8GetPressedKey() == 'C' )
		{
			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			HLCD_voidSetCursor(1,3);
			HLCD_voidSendString("_  _  _  _");
			HLCD_voidSetCursor(1,1);
		}
		else if(HKEYPAD_u8GetPressedKey() == 'B' )
		{
			if(G_system_flags.Password_NumOfCharEntered > 0)
			{
				/* print space */
				HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
				HLCD_voidSendChar('_');

				/* remove one character */
				G_system_flags.Password_NumOfCharEntered--;
			}else
			{
				/* if there was no character entered return to lock options */
				G_system_State = LOCK_OPTIONS;
			}
		}
		else if(HKEYPAD_u8GetPressedKey() == '='  && G_system_flags.Password_NumOfCharEntered == 4 )
		{

			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			/* check password  */
			if(S_PASSWORD_u8_Check(G_EnteredString) == PASSWORD_CORRECT)
			{
				/* toggle lock */
				G_system_flags.lock ^=1;
				G_system_State = LOCK_STATE_CHANGE;
			}
			else
			{
				G_system_State =  INCORRECT_PASSWORD;
			}
		}
		break;
		/*************************************** LOCK_STATE_CHANGE ***************************************/
	case LOCK_STATE_CHANGE:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
				/* lock door */
				G_system_flags.lock = 1;
				H_Servo_ChangeAngle(G_system_flags.lock * DOOR_LOCKED);
				HLCD_voidSetCursor(0,5);
				HLCD_voidSendString("Locked   ");
				HLCD_voidSendChar(CHAR_LOCKED);
			break;

		case '2':
				/* unlock door */
				G_system_flags.lock = 0;
				H_Servo_ChangeAngle(G_system_flags.lock * DOOR_LOCKED);
				HLCD_voidSetCursor(0,5);
				HLCD_voidSendString("Unlocked ");
				HLCD_voidSendChar(CHAR_UNLOCKED);
			break;
		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to LOCK_OPTIONS window  */
			G_system_State = LOCK_OPTIONS;
			break;
		default:
			break;
		}

		break;

		/*************************************** INCORRECT_PASSWORD ***************************************/
	case INCORRECT_PASSWORD:
			G_system_State = LOCK_OPTIONS;
		break;
		/*************************************** CHANGE_PASSWORD ***************************************/
	case CHANGE_PASSWORD:
		/* if the user pressed on a number the value will be saved in global array
		 * until the string reached 4 characters the press will have no effect
		 */
		if((HKEYPAD_u8GetPressedKey() >= '0') && (HKEYPAD_u8GetPressedKey() <= '9')
				&& (G_system_flags.Password_NumOfCharEntered < 4))
		{
			G_EnteredString[G_system_flags.Password_NumOfCharEntered] = HKEYPAD_u8GetPressedKey();

			G_system_flags.Password_NumOfCharEntered++;
			/* print star */
			HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
			HLCD_voidSendChar('*');

		}else if(HKEYPAD_u8GetPressedKey() == 'S' )
		{
			/* clear password character counter and return to main window */
			G_system_flags.Password_NumOfCharEntered = 0 ;
			G_system_State = MAIN_WINDOW;
		}
		else if(HKEYPAD_u8GetPressedKey() == 'C' )
		{
			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			HLCD_voidSetCursor(1,3);
			HLCD_voidSendString("_  _  _  _");
			HLCD_voidSetCursor(1,1);
		}
		else if(HKEYPAD_u8GetPressedKey() == 'B' )
		{
			if(G_system_flags.Password_NumOfCharEntered > 0)
			{
				/* print space */
				HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
				HLCD_voidSendChar('_');

				/* remove one character */
				G_system_flags.Password_NumOfCharEntered--;
			}else
			{
				/* if there was no character entered return to lock options */
				G_system_State = LOCK_OPTIONS;
			}
		}
		else if(HKEYPAD_u8GetPressedKey() == '='  && G_system_flags.Password_NumOfCharEntered == 4 )
		{

			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			/* check password  */
			G_system_State =(S_PASSWORD_u8_Check(G_EnteredString) == PASSWORD_CORRECT)?
									NEW_PASSWORD : INCORRECT_PASSWORD;
		}
		break;
		/*************************************** NEW_PASSWORD ***************************************/
	case NEW_PASSWORD:

		/* if the user pressed on a number the value will be saved in global array
		 * until the string reached 4 characters the press will have no effect
		 */
		if((HKEYPAD_u8GetPressedKey() >= '0') && (HKEYPAD_u8GetPressedKey() <= '9')
				&& (G_system_flags.Password_NumOfCharEntered < 4))
		{
			G_NewPassword[G_system_flags.Password_NumOfCharEntered] = HKEYPAD_u8GetPressedKey();

			G_system_flags.Password_NumOfCharEntered++;
			/* print star */
			HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
			HLCD_voidSendChar('*');

		}else if(HKEYPAD_u8GetPressedKey() == 'S' )
		{
			/* clear password character counter and return to main window */
			G_system_flags.Password_NumOfCharEntered = 0 ;
			G_system_State = MAIN_WINDOW;
		}
		else if(HKEYPAD_u8GetPressedKey() == 'C' )
		{
			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			HLCD_voidSetCursor(1,3);
			HLCD_voidSendString("_  _  _  _");
			HLCD_voidSetCursor(1,1);
		}
		else if(HKEYPAD_u8GetPressedKey() == 'B' )
		{
			if(G_system_flags.Password_NumOfCharEntered > 0)
			{
				/* print space */
				HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
				HLCD_voidSendChar('_');

				/* remove one character */
				G_system_flags.Password_NumOfCharEntered--;
			}else
			{
				/* if there was no character entered return to lock options */
				G_system_State = LOCK_OPTIONS;
			}
		}
		else if(HKEYPAD_u8GetPressedKey() == '='  && G_system_flags.Password_NumOfCharEntered == 4 )
		{

			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			/* check password  */
			G_system_State = CONFIRM_NEW ;
		}

		break;
		/*************************************** CONFIRM_NEW ***************************************/
	case CONFIRM_NEW:
		/* if the user pressed on a number the value will be saved in global array
		 * until the string reached 4 characters the press will have no effect
		 */
		if((HKEYPAD_u8GetPressedKey() >= '0') && (HKEYPAD_u8GetPressedKey() <= '9')
				&& (G_system_flags.Password_NumOfCharEntered < 4))
		{
			G_EnteredString[G_system_flags.Password_NumOfCharEntered] = HKEYPAD_u8GetPressedKey();

			G_system_flags.Password_NumOfCharEntered++;
			/* print star */
			HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
			HLCD_voidSendChar('*');

		}else if(HKEYPAD_u8GetPressedKey() == 'S' )
		{
			/* clear password character counter and return to main window */
			G_system_flags.Password_NumOfCharEntered = 0 ;
			G_system_State = MAIN_WINDOW;
		}
		else if(HKEYPAD_u8GetPressedKey() == 'C' )
		{
			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			HLCD_voidSetCursor(1,3);
			HLCD_voidSendString("_  _  _  _");
			HLCD_voidSetCursor(1,1);
		}
		else if(HKEYPAD_u8GetPressedKey() == 'B' )
		{
			if(G_system_flags.Password_NumOfCharEntered > 0)
			{
				/* print space */
				HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
				HLCD_voidSendChar('_');

				/* remove one character */
				G_system_flags.Password_NumOfCharEntered--;
			}else
			{
				/* if there was no character entered return to lock options */
				G_system_State = LOCK_OPTIONS;
			}
		}
		else if(HKEYPAD_u8GetPressedKey() == '='  && G_system_flags.Password_NumOfCharEntered == 4 )
		{
			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			/* check password  */

			if(S_PASSWORD_u8_CheckMatching(G_EnteredString,G_NewPassword) == PASSWORD_CORRECT)
			{
				G_system_State = PASSWORD_MATCH;
				S_PASSWORD_u8_Change(G_EnteredString);
			}else
			{
				G_system_State = PASSWORD_NOT_MATCH;
			}
		}
		break;
		/*************************************** PASSWORD_MATCH ***************************************/
		case PASSWORD_MATCH:
			G_system_State = LOCK_OPTIONS;
		break;
		/*************************************** PASSWORD_NOT_MATCH ***************************************/
	case PASSWORD_NOT_MATCH:
			G_system_State = NEW_PASSWORD;
		break;
		/*************************************** LIGHT_OPTIONS ***************************************/
	case LIGHT_OPTIONS:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
			G_system_State = LIGHT_BATH;
			break;

		case '2':
			G_system_State = LIGHT_LIVING;
			break;

		case '3':
			G_system_State = LIGHT_BED;
			break;

		case '4':
			G_system_State = LIGHT_KITCHEN;
			break;

		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = MAIN_WINDOW;
			break;
		default:
			break;
		}
		break;
		/*************************************** LIGHT_BATH ***************************************/
	case LIGHT_BATH:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':

			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("ON ");
			H_LED_voidChangeState(bath_led,LED_ON);
			break;

		case '2':
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("OFF");
			H_LED_voidChangeState(bath_led,LED_OFF);
			break;
		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = LIGHT_OPTIONS;
			break;
		default:
			break;
		}

		break;
		/*************************************** LIGHT_LIVING ***************************************/
	case LIGHT_LIVING:
		/* if key pressed change state */
				switch(HKEYPAD_u8GetPressedKey())
				{
				case '1':
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString("ON ");
					H_LED_voidChangeState(living_led,LED_ON);
					break;

				case '2':
					HLCD_voidSetCursor(0,10);
					HLCD_voidSendString("OFF");
					H_LED_voidChangeState(living_led,LED_OFF);
					break;
				case 'S':
					G_system_State = MAIN_WINDOW;
					break;
				case 'B':
					/* return to the window before */
					G_system_State = LIGHT_OPTIONS;
					break;
				default:
					break;
				}

				break;
		break;
		/*************************************** LIGHT_BED ***************************************/
	case LIGHT_BED:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("ON ");
			H_LED_voidChangeState(bed_led,LED_ON);
			break;

		case '2':
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("OFF");
			H_LED_voidChangeState(bed_led,LED_OFF);
			break;
		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = LIGHT_OPTIONS;
			break;
		default:
			break;
		}

		break;
		/*************************************** LIGHT_KITCHEN ***************************************/
	case LIGHT_KITCHEN:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("ON ");
			H_LED_voidChangeState(kitchen_led,LED_ON);
			break;

		case '2':
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("OFF");
			H_LED_voidChangeState(kitchen_led,LED_OFF);
			break;
		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = LIGHT_OPTIONS;
			break;
		default:
			break;
		}

		break;
		/*************************************** FAN_OPTIONS ***************************************/
	case FAN_OPTIONS:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
			G_system_State = FAN_BED;
			break;

		case '2':
			G_system_State = FAN_LIVING;
			break;

		case 'S':
			G_system_State = MAIN_WINDOW;
			break;

		case 'B':
			/* return to the window before */
			G_system_State = MAIN_WINDOW;
			break;

		default:
			break;
		}

		break;

		/*************************************** FAN_BED ***************************************/
	case FAN_BED:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
				/* turn Fan on */
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("ON ");
			H_DCmotor_voidChangeState(bed_fan,MOTOR_MOVE);
			break;

		case '2':
				/* turn Fan off */
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("OFF");
			H_DCmotor_voidChangeState(bed_fan,MOTOR_STOP);
			break;
		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = FAN_OPTIONS;
			break;
		default:
			break;
		}

		break;
		/*************************************** FAN_LIVING ***************************************/
	case FAN_LIVING:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{
		case '1':
			/* turn Fan on */
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("ON ");
			H_DCmotor_voidChangeState(living_fan,MOTOR_MOVE);
			break;

		case '2':
			/* turn Fan off */
			HLCD_voidSetCursor(0,10);
			HLCD_voidSendString("OFF");
			H_DCmotor_voidChangeState(living_fan,MOTOR_STOP);
			break;
		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = FAN_OPTIONS;
			break;
		default:
			break;
		}

		break;
		/*************************************** TEMP_WINDOW ***************************************/
	case TEMP_WINDOW:
		/* if key pressed change state */
		switch(HKEYPAD_u8GetPressedKey())
		{

		case 'S':
			G_system_State = MAIN_WINDOW;
			break;
		case 'B':
			/* return to the window before */
			G_system_State = MAIN_WINDOW;
			break;
		default:
			break;
		}


		break;

		/*************************************** ALERT_WINDOW ***************************************/
		case ALERT_WINDOW:

			break;
	case BACK_TO_NORMAL:
			G_system_State = MAIN_WINDOW;
		break;

		/*************************************** DEFAULT ***************************************/
	default:
		break;
	}
	/* if window changed clear LCD screen */
	if(G_system_State != G_system_PreviousState)
	{

		/* start system */
		APP_SetSystemWindow();
	}
}




void APP_Password_handler(void)
{
switch (HKEYPAD_u8GetPressedKey()) {
	case 'S':
		/* clear password character counter and return to main window */
		G_system_flags.Password_NumOfCharEntered = 0 ;
		G_system_State = MAIN_WINDOW;
		break;
	case 'B':
		if(G_system_flags.Password_NumOfCharEntered > 0)
		{
			/* print space */
			HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
			HLCD_voidSendChar('_');

			/* remove one character */
			G_system_flags.Password_NumOfCharEntered--;
		}else
		{
			/* if there was no character entered return to lock options */
			G_system_State = LOCK_OPTIONS;
		}
		break;
	case 'C':
		/* clear password character counter */
		G_system_flags.Password_NumOfCharEntered = 0;
		HLCD_voidSetCursor(1,3);
		HLCD_voidSendString("_  _  _  _");
		HLCD_voidSetCursor(1,1);
		break;
	case '=':
		if(G_system_flags.Password_NumOfCharEntered == 4 )
		{
			/* clear password character counter */
			G_system_flags.Password_NumOfCharEntered = 0;
			/* check password  */
			switch (G_system_State) {
				case ENTER_PASSWORD:

					break;
				case CHANGE_PASSWORD:

					break;
				case NEW_PASSWORD:
					/* go to Confirm new*/
					G_system_State = CONFIRM_NEW;
					break;
				case CONFIRM_NEW:
					/* check if the 2 strings match */
					if(S_PASSWORD_u8_CheckMatching(G_EnteredString,G_NewPassword) == PASSWORD_CORRECT)
					{
						G_system_State = PASSWORD_MATCH;
						S_PASSWORD_u8_Change(G_EnteredString);
					}else
					{
						G_system_State = PASSWORD_NOT_MATCH;
					}
					break;
				default:/* G_system_State */

					break;
			}
		}
		break;
	default: /* HKEYPAD_u8GetPressedKey() */
		/* if the user pressed on a number the value will be saved in global array
		 * until the string reached 4 characters the press will have no effect
		 */
		if((HKEYPAD_u8GetPressedKey() >= '0') && (HKEYPAD_u8GetPressedKey() <= '9')
				&& (G_system_flags.Password_NumOfCharEntered < 4))
		{
			if(G_system_State != NEW_PASSWORD)
			{
				G_EnteredString[G_system_flags.Password_NumOfCharEntered] = HKEYPAD_u8GetPressedKey();
			}else
			{
				G_NewPassword[G_system_flags.Password_NumOfCharEntered] = HKEYPAD_u8GetPressedKey();
			}

			G_system_flags.Password_NumOfCharEntered++;
			/* print star */
			HLCD_voidSetCursor(1,3*G_system_flags.Password_NumOfCharEntered);
			HLCD_voidSendChar('*');

		}
		break;
}

}

void APP_Light_handler(void)
{
	if(HKEYPAD_u8GetPressedKey() == 'S')
	{
		G_system_State = MAIN_WINDOW;
		G_system_flags.Password_NumOfCharEntered = 0;
		return;
	}
	switch (G_system_State) {
	case LOCK_OPTIONS:

		break;
	case LOCK_OPTIONS:

		break;
	case LOCK_OPTIONS:

		break;
	case LOCK_OPTIONS:

		break;
	case LOCK_OPTIONS:

		break;
	case LOCK_OPTIONS:

		break;
	case LOCK_OPTIONS:

		break;
		default:
			break;
	}
}

void APP_Fan_handler(void)
{

	switch (G_system_State) {


		default:
			break;
	}
}

/* for testing assign 0 to KEYPAD_PRINT_TEST when you complete the project  */
#if KEYPAD_PRINT_TEST
void keypad_printkey(void)
{
	HLCD_voidSendChar(HKEYPAD_u8GetPressedKey());

}
#endif
