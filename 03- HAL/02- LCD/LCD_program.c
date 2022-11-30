#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"
#include "../../01- LIB/string.h"

#include "../../02- MCAL/01- DIO/DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

#include <util/delay.h>
static uint_8 Global_CursorState = 0, Global_BlinkState = 0;

static void HLCD_voidSendData(uint_8 copy_u8Data)
{
#if LCD_DL == LCD_8_BIT_MODE
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB0, GET_BIT(copy_u8Data, 0));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB1, GET_BIT(copy_u8Data, 1));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB2, GET_BIT(copy_u8Data, 2));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB3, GET_BIT(copy_u8Data, 3));
#elif LCD_DL == LCD_4_BIT_MODE
	/* get the last 4 bits of data */
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB4, GET_BIT(copy_u8Data, 4));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB5, GET_BIT(copy_u8Data, 5));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB6, GET_BIT(copy_u8Data, 6));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB7, GET_BIT(copy_u8Data, 7));
	/* EN = 1 */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_EN, HIGH);
	_delay_ms(1);
	/* EN = 0 */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_EN, LOW);
	_delay_ms(2);
	/* get the first 4 bits of data */
	copy_u8Data <<= 4;
#endif
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB4, GET_BIT(copy_u8Data, 4));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB5, GET_BIT(copy_u8Data, 5));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB6, GET_BIT(copy_u8Data, 6));
	MDIO_voidSetPinValue(LCD_DATA_PORT, LCD_DB7, GET_BIT(copy_u8Data, 7));

	/* EN = 1 */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_EN, HIGH);
	_delay_ms(1);
	/* EN = 0 */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_EN, LOW);
	_delay_ms(2);
}

static void HLCD_voidSendCommand(uint_8 copy_u8Command)
{
	/* RS = 0 */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_RS, LOW);
	/* RW = 0 */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_RW, LOW);
	/* Send data */
	HLCD_voidSendData(copy_u8Command);
}

void HLCD_voidInitialize(void)
{
	// set used pins to output
	MDIO_voidSetPinDirection(LCD_COMMAND_PORT, LCD_RS, OUTPUT);
	MDIO_voidSetPinDirection(LCD_COMMAND_PORT, LCD_RW, OUTPUT);
	MDIO_voidSetPinDirection(LCD_COMMAND_PORT, LCD_EN, OUTPUT);
#if LCD_DL == LCD_8_BIT_MODE
	MDIO_voidSetPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
#elif LCD_DL == LCD_4_BIT_MODE
	MDIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB4, OUTPUT);
	MDIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB5, OUTPUT);
	MDIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB6, OUTPUT);
	MDIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DB7, OUTPUT);
#endif
	_delay_ms(30); /* LCD Power ON delay always >30ms */

	/* Return Home  */
	HLCD_voidSendCommand(LCD_RETURN_HOME);
	_delay_ms(1);

	/* Function Set  */
	HLCD_voidSendCommand(LCD_FUNCTION_SET);
	_delay_ms(1);

	/* Initialize Display */
	HLCD_voidSendCommand(LCD_DISPLAY_INIT);
	_delay_ms(1);

	/* Clear display screen */
	HLCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);

	HLCD_voidSendCommand(LCD_ENTRY_MODE); /* Increment cursor (shift cursor to right) */
}

void HLCD_voidSendChar(char copy_s8_Data)
{
	/* Set RS to HIGH */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_RS, HIGH);
	/* Set R/W to LOW */
	MDIO_voidSetPinValue(LCD_COMMAND_PORT, LCD_RW, LOW);
	/* Send data */
	HLCD_voidSendData(copy_s8_Data);
}

void HLCD_voidCreateChar(uint_8 copy_CharLocation, uint_8 copy_RowsOfChar[])
{
	uint_8 local_counter;
	/*DDRAM-->CGRAM*/
	HLCD_voidSendCommand(64 + 8 * copy_CharLocation);
	for (local_counter = 0; local_counter < 8; local_counter++)
	{
		HLCD_voidSendChar(copy_RowsOfChar[local_counter]);
	}
	/*CGRAM-->DDRAM*/
	HLCD_voidSendCommand(128);
	_delay_ms(5);
}

void HLCD_voidSendString(char *ptr_s8_String)
{
	while (*ptr_s8_String != '\0')
	{
		/* Write Character on LCD */
		HLCD_voidSendChar(*ptr_s8_String);
		ptr_s8_String++;
		/* Delay to let the LCD show the character */
		_delay_ms(1);
	}
}

void HLCD_voidClearScreen(void)
{
	HLCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);
}

void HLCD_voidSetCursor(uint_8 copy_u8Raw, uint_8 copy_u8Col)
{
	HLCD_voidSendCommand((copy_u8Col) + LCD_Col_OFFSET + LCD_ROW_OFFSET * (copy_u8Raw));
	_delay_ms(1);
}

void HLCD_voidSendNumber(float_32 copy_f32_Number)
{
	char local_string[16];
	uint_32 local_integerValue = copy_f32_Number;
	HLCD_voidSendString(itoa(copy_f32_Number,local_string,10));
	if(copy_f32_Number<0)
	{
		copy_f32_Number = -copy_f32_Number;
	}
	if(copy_f32_Number > local_integerValue)
	{
		HLCD_voidSendChar('.');
		local_integerValue = copy_f32_Number*100;
		local_integerValue%=100;
		HLCD_voidSendString(itoa(local_integerValue,local_string,10));
	}
}

void HLCD_voidCursorEnable(void)
{
	Global_CursorState = 2;
	HLCD_voidSendCommand(LCD_DISPLAY_INIT | Global_CursorState | Global_BlinkState);
	_delay_ms(1);
}

void HLCD_voidCursorDisable(void)
{
	Global_CursorState = 0;
	HLCD_voidSendCommand(LCD_DISPLAY_INIT | Global_CursorState | Global_BlinkState);
	_delay_ms(1);
}

void HLCD_voidBlinkEnable(void)
{
	Global_BlinkState = 1;
	HLCD_voidSendCommand(LCD_DISPLAY_INIT | Global_CursorState | Global_BlinkState);
	_delay_ms(1);
}

void HLCD_voidBlinkDisable(void)
{
	Global_BlinkState = 0;
	HLCD_voidSendCommand(LCD_DISPLAY_INIT | Global_CursorState | Global_BlinkState);
	_delay_ms(1);
}

void HLCD_voidDisplayEnable(void)
{
	HLCD_voidSendCommand(LCD_DISPLAY_INIT | Global_CursorState | Global_BlinkState);
}

void HLCD_voidDisplayDisable(void)
{
	HLCD_voidSendCommand(LCD_DISPLAY_OFF);
}

void HLCD_voidShiftRight(void)
{
	HLCD_voidSendCommand(LCD_SHIFT_RIGHT);
}

void HLCD_voidShiftLeft(void)
{
	HLCD_voidSendCommand(LCD_SHIFT_LEFT);
}
