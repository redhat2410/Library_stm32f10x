#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "Queue.h"
#include "Stack.h"
#include "stm32f10x.h"
#include "math.h"

static int tick = 0;
int main(){
	peripheral_register_init();
	SystemInit();
	Systick_Config(1000);
	while(1);
}

void SysTick_Handler(void){
	tick++;
}



