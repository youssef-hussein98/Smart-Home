#include "../../01- LIB/std_types.h"
#include "../../01- LIB/common_macros.h"

#include "GIE_interface.h"
#include "GIE_register.h"

void MGIE_voidEnable(void)
{
	SET_BIT(SREG,GIE_PIN);
}

void MGIE_voidDisable(void)
{
	CLEAR_BIT(SREG,GIE_PIN);
}
