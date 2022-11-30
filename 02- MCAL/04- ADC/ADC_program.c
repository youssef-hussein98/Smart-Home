#include "../../01- LIB/common_macros.h"
#include "../../01- LIB/std_types.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"
#include "ADC_config.h"

/*Private Global Objects */
/* hold the address of the function to be called back */
static void (*G_ptr_AdcIsrNotification)(void) = NULL;
/* hold the address of result to be updated */
static uint_16 *G_Ptr_AdcReading = NULL;

void MADC_voidInit(void)
{
    ADMUX_REG  &= REFERENCE_MASK;
    ADMUX_REG  |= REFERENCE_SELECTION ;     //select reference voltage
    ADMUX_REG  &= ADJUSTMENT_MASK;
    ADMUX_REG  |= DATA_ADJUSTMENT_MODE;     //choose left adjusted or right adjusted
    ADCSRA_REG &= PRESCALER_MASK;
    ADCSRA_REG |= ADC_PRESCALER_VALUE ;     //Select prescaler value
    SET_BIT(ADCSRA_REG, ADEN);              //ENABLE ADC
}

uint_16 MADC_uint_16GetChannelValue(uint_8 copy_Channel_ID)
{
    /* Select the specified Channel */
    ADMUX_REG &= CHANNEL_MASK;
    ADMUX_REG |= copy_Channel_ID;
    /* Start the Conversion */
    SET_BIT(ADCSRA_REG, ADSC);
    /* Busy-Wait Polling till conversion complete */
    while ((GET_BIT(ADCSRA_REG, ADIF)) != 1);
    /* Clear the ADC complete conversion flag */
    SET_BIT(ADCSRA_REG, ADIF);
    /* return the result based on number of bits and adjustment mode*/
    #if BITS_NO == _8_BITS
        #if DATA_ADJUSTMENT_MODE == RIGHT_ADJUSTED
            return ADCH_REG;
        #elif DATA_ADJUSTMENT_MODE == LEFT_ADJUSTED
            return ADCL_REG;
        #endif
    #elif BITS_NO == _10_BITS
        return ADC_DATA_REG;
    #endif
}


/* It enables ADC ISR and it is the registeration function at the same time */
void MADC_voidReadDigital_Async(uint_8 copy_Channel_ID,uint_16 *ptr_u16_ReturnedResult,
                                 void (*ptr_AdcIsrFuncLogic)(void))
{
    /* Initialize the global pointer to variable with 
	   the address of the variable to be updated */
    G_Ptr_AdcReading = ptr_u16_ReturnedResult;

    /* Initialize the global pointer to function with 
	   the address of the function to be called */
    G_ptr_AdcIsrNotification = ptr_AdcIsrFuncLogic;

    /* Select the specified Channel */
    ADMUX_REG &= CHANNEL_MASK;
    ADMUX_REG |= copy_Channel_ID;

    /* Enable the ADC interrupt */
    SET_BIT(ADCSRA_REG, ADIE);

    /* Start the Conversion */
    SET_BIT(ADCSRA_REG, ADSC);
}

/* ISR Definition Call-Back Mechanism */
void __vector_16(void)
{
    /* return the result based on number of bits and adjustment mode*/
    #if BITS_NO == _8_BITS
        #if DATA_ADJUSTMENT_MODE == RIGHT_ADJUSTED
        *G_Ptr_AdcReading = ADCH_REG;
        #elif DATA_ADJUSTMENT_MODE == LEFT_ADJUSTED
        *G_Ptr_AdcReading = ADCL_REG;
        #endif
    #elif BITS_NO == _10_BITS
        *G_Ptr_AdcReading = ADC_DATA_REG;
    #endif

    /* Update the ADC return variable */
    *G_Ptr_AdcReading = ADC_DATA_REG;

    /* Invoke the call back function through the pointer */
    G_ptr_AdcIsrNotification();

    /* Disable the ADC interrupt */
    CLEAR_BIT(ADCSRA_REG, ADIE);
}