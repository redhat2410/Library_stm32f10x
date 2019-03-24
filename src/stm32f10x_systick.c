#include "stm32f10x.h"


#define SysTick_LOAD_RELOAD_Msk				0xFFFFFFul
#define __NVIC_PRIO_BITS							4

uint32_t Systick_Config(uint32_t tick){
	if(tick > SysTick_LOAD_RELOAD_Msk) return (1);
	
	*STK.LOAD	=	(tick & SysTick_LOAD_RELOAD_Msk) - 1;
	NVIC_SetPriority_SysTick((1 << __NVIC_PRIO_BITS) - 1);
	*STK.VAL		=	0;
	*STK.CTRL	=	(1 << 2) | (1 << 1) | (1 << 0);
	
	return 0;
}
