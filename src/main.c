#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x.h"
#include "enc28j60.h"
#include "math.h"


uint8_t dem= 0x00;

int main(){
	peripheral_register_init();
	SystemInit();
	Systick_Config(72);
	
	GPIO_configuration(GPIOPORT_C, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 13);
	
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 5);
	//Config pin MISO
	GPIO_configuration(GPIOPORT_A, MODE_INPUT, IN_FLOATING_MODE, 6);
	//Config pin MOSI
 	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 7);
	//Config pin NSS
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_PUSHPULL, 4);
	
	SPI_configuration(SPIx1, SPI_MASTER, SPI_DFF_8_BITS, SPI_FCLK_16, SPI_YES, SPI1_IRQn);
	GPIO_WriteBit(GPIOPORT_C, 13, BIT_SET);
	delay_ms(1000);
	while(1){
		GPIO_WriteBit(GPIOPORT_C, 13, BIT_RESET);
		SPI_WriteData(SPIx1, 0x1F);
		GPIO_WriteBit(GPIOPORT_C, 13, BIT_SET);
		delay_ms(100);
	}
	
}


void SPI1_IRQHandler(){
	dem = SPI_ReadData(SPIx1);
}



