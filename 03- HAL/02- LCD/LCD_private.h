#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

// for LCD_DL:
#define LCD_4_BIT_MODE          0
#define LCD_8_BIT_MODE          1

// for LCD_LINE_DISPLAY:
#define LCD_1_LINE_MODE         0
#define LCD_2_LINE_MODE         1

// for LCD_FONT_SIZE:
#define LCD_FONT_5x7            0
#define LCD_FONT_5x10           1

#define LCD_FUNCTION_SET        (0x20 | (LCD_DL << 4) | (LCD_NO_OF_LINES << 3) | (LCD_FONT_SIZE << 2))

// Common commands
#define LCD_CLEAR               0x01    /* replace all characters with ASCII 'space'     */
#define LCD_RETURN_HOME         0x02    /* return to row 0 column 0 without changing display*/
#define LCD_ENTRY_MODE          0x06    /* left to right */
#define LCD_DISPLAY_INIT        0x0C    /* display on/ cursor off/ blink off */
#define LCD_DISPLAY_OFF         0x08    
#define LCD_Col_OFFSET          0x80    /* set cursor column*/
#define LCD_ROW_OFFSET          0x40    /* set cursor row */
#define LCD_SHIFT_RIGHT         0x1C
#define LCD_SHIFT_LEFT          0x18

/* private function to set data bits */
static void HLCD_voidSendData(uint_8 copy_u8Data);
/* private function to send commands */
static void HLCD_voidSendCommand(uint_8 copy_u8Command);

#endif
