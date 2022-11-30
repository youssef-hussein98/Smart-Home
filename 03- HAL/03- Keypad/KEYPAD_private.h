#ifndef KEYPAD_PRIVATE_H_
#define KEYPAD_PRIVATE_H_

#if START_ROW < END_ROW
    #define UPDATE_ROW      1
    #define SELECTED_ROW    row - START_ROW
#else
    #define UPDATE_ROW      -1
    #define SELECTED_ROW    START_ROW - row
#endif

#if START_COL < END_COL
    #define UPDATE_COL 1
    #define SELECTED_COL column - START_COL
#else
    #define UPDATE_COL -1
    #define SELECTED_COL START_COL - column
#endif

#define KEYPAD_NOTPRESSED   0
#define KEYPAD_PRESSED      1

#endif