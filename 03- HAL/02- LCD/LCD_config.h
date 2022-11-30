#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

// command pins
#define LCD_COMMAND_PORT PORTB
#define LCD_EN PIN2
#define LCD_RW PIN1
#define LCD_RS PIN0

// data pins
#define LCD_DATA_PORT PORTB
// pins DB0 ~ DB3 ignored in 4 bit mode
#define LCD_DB0 PIN0
#define LCD_DB1 PIN1
#define LCD_DB2 PIN2
#define LCD_DB3 PIN3

#define LCD_DB4 PIN4
#define LCD_DB5 PIN5
#define LCD_DB6 PIN6
#define LCD_DB7 PIN7

/* Options for LCD_DL:
	1-  LCD_8_BIT_MODE   // use all Data pins
	2-  LCD_4_BIT_MODE   // use DB4 ~ DB7
*/
#define LCD_DL LCD_4_BIT_MODE

/* Options for LCD_NO_OF_LINES:
	1-  LCD_1_LINE_MODE   // use first row only
	2-  LCD_2_LINE_MODE   // use both rows
*/
#define LCD_NO_OF_LINES LCD_2_LINE_MODE

/* Options for LCD_FONT_SIZE:
	1-  LCD_FONT_5x7
	2-  LCD_FONT_5x10
*/
#define LCD_FONT_SIZE LCD_FONT_5x7

/*  Note:
 * Cursor & blink are switched off by default
 */
#endif
