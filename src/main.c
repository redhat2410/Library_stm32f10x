#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x.h"
#include "enc28j60.h"
#include "math.h"


uint16_t dem= 0x0000;

int main(){
	peripheral_register_init();
	SystemInit();
	Systick_Config(72);
	
	//Config pin Enable SPI
	GPIO_configuration(GPIOPORT_C, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 13);
	
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 5);
	//Config pin MISO
	GPIO_configuration(GPIOPORT_A, MODE_INPUT, IN_FLOATING_MODE, 6);
	//Config pin MOSI
 	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 7);
	//Config pin NSS
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_PUSHPULL, 4);
	
	SPI_configuration(SPIx1, SPI_MASTER, SPI_DFF_8_BITS, SPI_FCLK_128, SPI_NO, SPI1_IRQn);
	
	while(1){
		for(dem = 0; dem < 100; dem++){
			GPIO_WriteBit(GPIOPORT_C, 13, BIT_RESET);
			SPI_WriteData(SPIx1, dem);
			GPIO_WriteBit(GPIOPORT_C, 13, BIT_SET);
			delay_ms(1000);
		}
	}
	
} 


void SPI1_IRQHandler(){
	dem = SPI_ReadData(SPIx1);
}



