#include "stm32f10x.h"
#include "stm32f10x_tim.h"

// This file implement configure basic timer TIM6 - TIM7
// configure TIM6 TIM7 use counter

void TIM_configuration(void){
	//enable clock for TIM6 in RCC
	*RCC.APB2ENR	|=	(1 << 4);
	
}
