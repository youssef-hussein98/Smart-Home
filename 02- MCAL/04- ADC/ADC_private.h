#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define PRESCALER_MASK          0x11111000        
#define ADC_PRESCALER_2         1
#define ADC_PRESCALER_4         2
#define ADC_PRESCALER_8         3
#define ADC_PRESCALER_16        4
#define ADC_PRESCALER_32        5
#define ADC_PRESCALER_64        6
#define ADC_PRESCALER_128       7

#define REFERENCE_MASK          0x00111111
#define TURN_OFF                0
#define AVCC                    1<<6
#define INTERNAL_2_56V          3<<6

#define _8_BITS                 0
#define _10_BITS                1

#define ADJUSTMENT_MASK         0b11011111
#define RIGHT_ADJUSTED          0
#define LEFT_ADJUSTED           1<<5

#define CHANNEL_MASK            0x11100000


void __vector_16(void) __attribute__((signal));

#endif