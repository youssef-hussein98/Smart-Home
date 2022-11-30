#ifndef _TIMER_REG_H
#define _TIMER_REG_H

/************************************** Timer0 ******************************************/

/* Timer/Counter 0 Control Register */
#define TCCR0  *((volatile uint_8 *)0x53)
#define FOC0   7
#define WGM00  6
#define COM01  5
#define COM00  4
#define WGM01  3
#define CS02   2
#define CS01   1
#define CS00   0

/* Timer/Counter 0 Register */
#define TCNT0  *((volatile uint_8 *)0x52)

/* Timer/Counter 0 Output Compare Register */
#define OCR0   *((volatile uint_8 *)0x5C)

/* Timer/Counter 0 Interrupt Mask Register */
#define TIMSK  *((volatile uint_8 *)0x59)
#define OCIE2  7
#define TOIE2  6
#define TICIE1 5
#define OCIE1A 4
#define OCIE1B 3
#define TOIE1  2
#define OCIE0  1
#define TOIE0  0

/* Timer/Counter 0 Interrupt Flag Register */
#define TIFR   *((volatile uint_8 *)0x58)
#define OCF2   7        
#define TOV2   6
#define ICF1   5
#define OCF1A  4
#define OCF1B  3
#define TOV1   2
#define OCF0   1
#define TOV0   0


/************************************** Timer1 ******************************************/


/* 
 * Timer/Counter1 Control Register A 
 */
#define TCCR1A    *((volatile uint_8  *)0x4F)
#define COM1A1    7
#define COM1A0    6
#define COM1B1    5
#define COM1B0    4
#define FOC1A     3
#define FOC1B     2
#define WGM11     1
#define WGM10     0


/* 
 * Timer/Counter1 Control Register B
 */
#define TCCR1B    *((volatile uint_8  *)0x4E)
#define ICNC1     7
#define ICES1     6
/* Bit Number 5 is reserved */
#define WGM13     4
#define WGM12     3
#define CS12   	  2
#define CS11      1
#define CS10      0


/* 
 * Timer/Counter1 
 */
#define TCNT1H    *((volatile uint_8  *)0x4D)
#define TCNT1L    *((volatile uint_8  *)0x4C)
#define TCNT1     *((volatile uint_16 *)0x4C)


/* 
 * Output Compare Register 1 A 
 */
#define OCR1AH    *((volatile uint_8  *)0x4B)
#define OCR1AL    *((volatile uint_8  *)0x4A)
#define OCR1A     *((volatile uint_16 *)0x4A)


/* 
 * Output Compare Register 1 B 
 */
#define OCR1BH    *((volatile uint_8  *)0x49)
#define OCR1BL    *((volatile uint_8  *)0x48)
#define OCR1B     *((volatile uint_16 *)0x48)


/* 
 * Input Capture Register 1 
 */
#define ICR1H     *((volatile uint_8  *)0x47)
#define ICR1L     *((volatile uint_8  *)0x46)
#define ICR1      *((volatile uint_16 *)0x46)


/* 
 * Timer/Counter Interrupt Mask Register 
 */
#define TIMSK     *((volatile uint_8  *)0x59)
/* Bits 6 - 7 are not related to this module */
#define TICIE1    5
#define OCIE1A    4
#define OCIE1B    3
#define TOIE1     2
/* Bits 1 - 2 are not related to this module */


/* 
 * Timer/Counter Interrupt Flag Register 
 */
#define TIFR      *((volatile uint_8  *)0x58)
/* Bits 6 - 7 are not related to this module */
#define ICF1      5
#define OCF1A     4
#define OCF1B     3
#define TOV1      2
/* Bits 1 - 2 are not related to this module */


#endif /* _TIMER_REG_H */