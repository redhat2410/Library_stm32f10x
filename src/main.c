#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "Queue.h"
#include "Stack.h"
#include "stm32f10x.h"
#include "enc28j60.h"
#include "math.h"


uint8_t dem= 0;
void delay(long time);
int main(){
	peripheral_register_init();
	SystemInit();
	initSPI();
	writeOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_BSEL1|ECON1_BSEL0);
	delay(10000);
	dem = readOp(ENC28J60_READ_CTRL_REG, ECON1);
	
}

void delay(long time){
	while(time-- >= 0);
}

//void SPI1_IRQHandler(){
//	if(SPI_ReadData(SPIx1) == 0x01) dem++;
//}



