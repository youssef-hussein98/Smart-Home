#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

#define KEYPAD_ROW_PORT     PORTD
#define START_ROW           PIN0
#define END_ROW             PIN3

#define KEYPAD_COL_PORT     PORTD
#define START_COL           PIN4
#define END_COL             PIN7

uint_8 Global_u8KeypadKeys[4][4] = {
    {'7', '8', '9', 'S'},
    {'4', '5', '6', 'C'},
    {'1', '2', '3', 'B'},
    {'*', '0', '#', '='},
};

#endif
