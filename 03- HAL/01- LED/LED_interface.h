#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


typedef struct ST_LED
{
    uint_8 port_ID:4;
    uint_8 pin_ID :4;

}ST_LED;

typedef enum EN_LED
{
	LED_OFF, LED_ON, LED_TOGGLE
}EN_LED;

void H_LED_void_init(ST_LED LED_Object);
void H_LED_voidChangeState(ST_LED LED_Object,EN_LED NewState);
EN_LED H_LED_EnGetState(ST_LED LED_Object);

#endif
