#ifndef ADC_REGISTERS_H
#define ADC_REGISTERS_H

#define ADMUX_REG               *((volatile uint_8*)0x27)
#define REFS1                   7
#define REFS0                   6
#define ADLAR                   5
#define MUX4                    4
#define MUX3                    3
#define MUX2                    2
#define MUX1                    1
#define MUX0                    0

#define ADCSRA_REG              *((volatile uint_8 *)0x26)
#define ADEN                    7
#define ADSC                    6
#define ADATE                   5
#define ADIF                    4
#define ADIE                    3
#define ADPS2                   2
#define ADPS1                   1
#define ADPS0                   0

#define ADCH_REG                *((volatile uint_8 *)0x25)
#define ADCL_REG                *((volatile uint_8 *)0x24)
#define ADC_DATA_REG            *((volatile uint_16 *)0x24)
#endif