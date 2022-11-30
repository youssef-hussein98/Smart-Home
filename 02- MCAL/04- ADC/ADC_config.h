#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/* Select an option for the ADC prescaller value:
 * 1- ADC_PRESCALER_2 
 * 2- ADC_PRESCALER_4  
 * 3- ADC_PRESCALER_8
 * 4- ADC_PRESCALER_16 
 * 5- ADC_PRESCALER_32 
 * 6- ADC_PRESCALER_64
 * 7- ADC_PRESCALER_128 
 */
#define ADC_PRESCALER_VALUE            ADC_PRESCALER_128

/* Select an option for the Reference value:
NOTE: External capacitor must be connected at AREF pin
1- TURN_OFF
2- AVCC             
3- INTERNAL_2_56V
*/
#define REFERENCE_SELECTION             AVCC

/* Select an option for data adjustment value:
1- LEFT_ADJUSTED
2- RIGHT_ADJUSTED
*/
#define DATA_ADJUSTMENT_MODE            LEFT_ADJUSTED

/* Select an option for data adjustment value:
 * 1- _10_BITS
 * 2- _8_BITS
 */
#define BITS_NO                         _10_BITS

#endif