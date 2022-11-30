#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC0                    0
#define ADC1                    1
#define ADC2                    2
#define ADC3                    3
#define ADC4                    4
#define ADC5                    5
#define ADC6                    6
#define ADC7                    7
#define ADC0_ADC0_10x           8
#define ADC1_ADC0_10x           9
#define ADC0_ADC0_200x          10
#define ADC1_ADC0_200x          11
#define ADC2_ADC2_10x           12
#define ADC3_ADC2_10x           13
#define ADC2_ADC2_200x          14
#define ADC3_ADC2_200x          15
#define ADC0_ADC1_1x            16
#define ADC1_ADC1_1x            17
#define ADC2_ADC1_1x            18
#define ADC3_ADC1_1x            19
#define ADC4_ADC1_1x            20
#define ADC5_ADC1_1x            21
#define ADC6_ADC1_1x            22
#define ADC7_ADC1_1x            23
#define ADC0_ADC2_1x            24
#define ADC1_ADC2_1x            25
#define ADC2_ADC2_1x            26
#define ADC3_ADC2_1x            27
#define ADC4_ADC2_1x            28
#define ADC5_ADC2_1x            29
#define VBG                     30
#define ZERO_VOLT               31

void MADC_voidInit(void);

uint_16 MADC_uint_16GetChannelValue(uint_8 copy_Channel_ID);

/* It enables ADC ISR and it is the registeration function at the same time */
void MADC_voidReadDigital_Async(uint_8 copy_u8_ChannelID,
                                uint_16 *ptr_u16ReturnedResult,
                                void (*ptr_AdcIsrFuncLogic)(void));
#endif