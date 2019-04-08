#include "stm32f10x.h"


#define SysTick_LOAD_RELOAD_Msk				0xFFFFFFul
#define __NVIC_PRIO_BITS							4

static uint16_t fac_us;
static uint16_t fac_ms;

uint32_t Systick_Config(uint32_t SYSCLK){
	NVIC_SetPriority_SysTick((1 << __NVIC_PRIO_BITS) - 1);
	*STK.VAL		=	0;
	*STK.CTRL	=	(1 << 2) | (1 << 1) | (1 << 0);
	fac_us = SYSCLK / 8;
	fac_ms = (uint16_t)(fac_us * 1000);
	
	return 0;
}

void delay_ms(uint16_t ms){
	uint32_t temp;
	*STK.LOAD = (uint32_t)(ms * fac_ms);
	*STK.VAL = 0x00;
	*STK.CTRL = 0x01;
	do{
		temp = *STK.CTRL;
	}
	while((temp & 0x01) && !(temp & ( 1 << 16)));
	
	*STK.CTRL = 0x00;
	*STK.VAL = 0x00;
}

void delay_us(uint32_t us){
	uint32_t temp;
	*STK.LOAD = us * fac_us;
	*STK.VAL = 0x00;
	*STK.CTRL = 0x01;
	
	do{
		temp = *STK.CTRL;
	}
	while((temp & 0x01) && !(temp & (1 << 16)));
	*STK.CTRL = 0x00;
	*STK.VAL = 0x00;
}
