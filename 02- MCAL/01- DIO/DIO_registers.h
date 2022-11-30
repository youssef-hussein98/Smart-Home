#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

// &3 to be sure x will not exceed 3
#define PORTx_REG(x)    *((volatile uint_8 *)0x3B - 3 * ((x)&3))
#define DDRx_REG(x)     *((volatile uint_8 *)0x3A - 3 * ((x)&3))
#define PINx_REG(x)     *((volatile uint_8 *)0x39 - 3 * ((x)&3))

#endif
