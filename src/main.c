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
	SPI_Configure config;
	
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
	
	config.spi 					= SPIx1;
	config.spiMode 			= SPI_MASTER;
	config.spiFrame 		= SPI_DFF_8_BITS;
	config.spiBaudrate	= SPI_FCLK_128;
	config.spiIT				=	SPI_NO;
	config.spiFirst			=	SPI_FirstLSB;
	config.spiModeClock	=	SPI_CLOCK_1;
	config.spiNSS				=	SPI_NSS_Software;
	SPI_Init(config);
	
	GPIO_WriteBit(GPIOPORT_C, 13, BIT_SET);
	
	while(1){
		//Write data in control register
		GPIO_WriteBit(GPIOPORT_C, 13, BIT_RESET);
		SPI_WriteData(SPIx1, ENC28J60_WRITE_CTRL_REG | ECON1 );
		//delay_ms(10);
		SPI_WriteData(SPIx1, ECON1_BSEL0); // ECON1_BSEL1   ECON1_BSEL0
		GPIO_WriteBit(GPIOPORT_C, 13, BIT_SET);
		//delay_ms(50);
		
		//Read dat in control register
		GPIO_WriteBit(GPIOPORT_C, 13, BIT_RESET);
		SPI_WriteData(SPIx1, ENC28J60_READ_CTRL_REG | ECON1 );
		delay_us(10);
		temp_1 = SPI_ReadData(SPIx1);
		GPIO_WriteBit(GPIOPORT_C, 13, BIT_SET);
	}
	
} 


void SPI1_IRQHandler(){
	dem = SPI_ReadData(SPIx1); 
}



