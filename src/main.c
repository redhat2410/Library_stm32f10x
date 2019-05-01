#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x.h"
#include "enc28j60.h"
#include "math.h"


uint16_t dem= 0x0000;

uint8_t temp_1 = 0x00;
uint8_t temp_2 = 0x00;

int main(){
	//SPI_Configure config;
	USART_Configure config;
	
	peripheral_register_init();
	SystemInit();
	Systick_Config(72);
	
	//configure pinout for usart
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 9); // TX
	GPIO_configuration(GPIOPORT_A, MODE_INPUT, IN_FLOATING_MODE, 10); // RX
		
	config.usart = USARTx1;
	config.baud = USART_BR_9600;
	config.length = USART_D_8_BITS;
	config.stop = USART_SP_1BIT;
	config.it = USART_IT_RXNEIE_RST & USART_IT_TCIE_RST & USART_IT_TXEIE_RST;
	
	USART_Init(config);
	
	while(1){
		temp_1 = USART_ReadData(config.usart);
	}
	
} 


void SPI1_IRQHandler(){
	SPI_HandleError(SPIx1);
}



