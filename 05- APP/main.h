/*
 * main.h
 *
 *  Created on: Nov 12, 2022
 *      Author: Youssef
 */

#ifndef __APP_MAIN_H_
#define __APP_MAIN_H_


#define BED_LED		((uint_8)0)
#define LIVING_LED	((uint_8)1)
#define BATH_LED	((uint_8)2)
#define KITCHEN_LED	((uint_8)3)

#define BED_FAN		((uint_8)4)
#define LIVING_FAN	((uint_8)5)

#define DOOR_UNLOCKED 	((uint_8)0)
#define DOOR_LOCKED 	((uint_8)90)

#define CHAR_UNLOCKED	((char)2)
#define CHAR_LOCKED		((char)3)
#define CHAR_HEART		((char)4)

#define TEMPERATURE_CRITICAL_VALUE ((float_32)45.0)

/* Enum to define system states */
typedef enum EN_systemState
{
	IDLE,
	MAIN_WINDOW,
	LOCK_OPTIONS,
	ENTER_PASSWORD, LOCK_STATE_CHANGE, INCORRECT_PASSWORD,
	CHANGE_PASSWORD, NEW_PASSWORD, CONFIRM_NEW, PASSWORD_MATCH, PASSWORD_NOT_MATCH,
	LIGHT_OPTIONS, LIGHT_BATH, LIGHT_LIVING, LIGHT_BED, LIGHT_KITCHEN,
	FAN_OPTIONS, FAN_BED,FAN_LIVING,
	TEMP_WINDOW,
	ALERT_WINDOW, BACK_TO_NORMAL
}EN_systemState;

typedef struct ST_flags
{
	uint_8 lock							:1;
	uint_8 alert						:2;
	uint_8 Password_NumOfCharEntered	:3;
}ST_flags;


/* initialize all hardware components */
void APP_hardware_Init(void);

/* System_start */
void APP_SetSystemWindow(void);
/* define what does each button do in keypad in each window */
void APP_keypad_Handler(void);

/* handle emergency */
void APP_CheckTemperature(void);

/* for testing assign 0 to KEYPAD_PRINT_TEST when you complete the project  */
#define KEYPAD_PRINT_TEST  0

#if KEYPAD_PRINT_TEST
	void keypad_printkey(void);
#endif

#endif /* 05__APP_MAIN_H_ */
