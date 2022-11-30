#ifndef LM35_INTERFAVE_H
#define LM35_INTERFAVE_H

void HLM35_Init(void);
float_32 HLM35_Reading(uint_8 copy_Analog_PinID);
void HLM35_Reading_Async(uint_8 copy_Channel_ID,float_32 *ptr_u16_ReturnedResult,
                                 void (*ptr_AdcIsrFuncLogic)(void));
#endif
