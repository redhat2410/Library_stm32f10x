#include "stm32f10x.h"
#include "stm32f10x_exti.h"


void EXTI_configuration(EXTIPORT port, TRIGGER trigger, unsigned char pin, unsigned char IRQn){
	//Cap clock cho thanh ghi AFIO
	*RCC.APB2ENR |= (1 << 0);
	//Enable interrupt mask
	*EXTI.IMR	|=	(1 << pin);
	//Cau hinh ngat cho PORT va pin
	*AFIO.EXTICR[pin/4] |= (port << (pin - ((pin / 4) * 4)) * 4);
	//Cau hinh trigger cho pin
	if(trigger == TG_RISING)
		*EXTI.RTSR |= (1 << pin);
	else
		*EXTI.FTSR |=	(1 << pin);
	//Enable ngat cho pin
	NVIC_SetPriority((IRQn_Typedef)IRQn, 1);
}

void EXTI_ClearFlag(unsigned char pin){
	*EXTI.PR	|=	(1 << pin);
}
