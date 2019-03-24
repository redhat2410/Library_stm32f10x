#include "stm32f10x.h"

//Set priority for systick 
void NVIC_SetPriority_SysTick(uint32_t priority){
	//Set prority for systick in SCB because systick in system interrupt
	*SCB.SHPR[2] = ((priority << 4) & 0xff) << 24;
}

void NVIC_SetPriority(IRQn_Typedef IRQn, uint32_t priority){
	//Set priority vector interrupt IRQn
	*NVIC.IPR[IRQn]	=	((1 << 4) & 0xff);
	//Enable interrupt vector interrupt IRQn
	*NVIC.ISER[IRQn / 32] = ( priority << ( IRQn & 0x1F));
	//Enable global interrupt
	__enable_irq();
}

