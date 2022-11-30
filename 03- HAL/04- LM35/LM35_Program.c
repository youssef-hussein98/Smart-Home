#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "../../02- MCAL/04- ADC/ADC_interface.h"

static void HLM35_conversion(void);

void (*G_ptr_LM35callbackfunction)(void) = NULL;
static uint_16 G_conversionResult;
static float_32 *G_tempResult;

void HLM35_Init(void)
{
    MADC_voidInit();

}
float_32 HLM35_Reading(uint_8 copy_Analog_PinID)
{
//	return MADC_uint_16GetChannelValue(copy_Analog_PinID) ;

	return MAP( ((MADC_uint_16GetChannelValue(copy_Analog_PinID) * 500.0) / 256)
																				,41, 701.4, -40, 125);
}


void HLM35_Reading_Async(uint_8 copy_Channel_ID,float_32 *ptr_f32_ReturnedResult,
                                 void (*ptr_AdcIsrFuncLogic)(void))
{

	G_tempResult = ptr_f32_ReturnedResult;
	G_ptr_LM35callbackfunction = ptr_AdcIsrFuncLogic;

	MADC_voidReadDigital_Async(copy_Channel_ID, &G_conversionResult, &HLM35_conversion);

}

static void HLM35_conversion(void)
{
	*G_tempResult =  MAP( (( G_conversionResult * 500.0) / 256) ,41, 701.4, -40, 125);
	G_ptr_LM35callbackfunction();

}
