#ifndef COMMON_MACROS
#define COMMON_MACROS

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT)                                            (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT)                                          (REG&=(~(1<<BIT)))

/* Check a specific bit Value */
#define GET_BIT(REG, BIT)                                           ((REG>>BIT)&1)

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT)                                         (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num)                                                ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num)                                                ( REG= (REG<<num) | (REG>>(8-num)) )

/* used with pointer to remove the pointer value*/

#define NULL                                                        ((void *) 0)

/* used to indecate if the proccess is done with no errors*/
#define OK                                                          ((uint_8) 0)
#define NOK                                                         ((uint_8) -1)


/* user interface PORTs  */
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/* user interface port directions */
#define PORT_OUTPUT 0xFF
#define PORT_INPUT 0x00

/* user interface port states  */
#define PORT_HIGH 0xFF
#define PORT_LOW 0x00

/* user interface pin directions */
#define OUTPUT 1
#define INPUT  0

/* user interface pin states  */
#define TOGGLE 2
#define HIGH   1
#define LOW    0

/* user interface Pins */
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


/*return the value or variable after changing the range*/
#define MAP(var, INPUT_START, INPUT_END, OUTPUT_START, OUTPUT_END)  \
                                                                    \
    (( (float)((OUTPUT_END) - (OUTPUT_START))                       \
    / ((INPUT_END) - (INPUT_START))) * (var - INPUT_START))         \
    + (OUTPUT_START)

#endif
