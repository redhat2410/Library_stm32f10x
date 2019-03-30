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


int dem= 0;
void delay(long time);
int main(){
	peripheral_register_init();
	SystemInit();
	//Cau hinh pin C13 output
	GPIO_configuration(GPIOPORT_C, MODE_OUTPUT_50M, OUT_PUSHPULL, 13);
	//Configuration pinout for SPI1
	//NSS
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 4);
	//SCK
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 5);
	//MISO
	GPIO_configuration(GPIOPORT_A, MODE_INPUT,	IN_FLOATING_MODE, 6);
	//MOSI
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 7);
	
	SPI_configuration(SPIx1, SPI_MASTER, SPI_DFF_8_BITS, SPI_FCLK_8, SPI_NO, SPI1_IRQn); 
	while(1){
		SPI_WriteData(SPIx1, 0x01);
		dem = SPI_ReadData(SPIx1);
		
	}
}

void delay(long time){
	while(time-- >= 0);
}

//void SPI1_IRQHandler(){
//	if(SPI_ReadData(SPIx1) == 0x01) dem++;
//}



