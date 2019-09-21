#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x.h"

uint8_t data	= 0;
uint8_t loop	= 0;
uint8_t i 		= 0;

BIT read;

int main(){
	
	SPI_Configure config;
	
	// Init register
	peripheral_register_init();
	SystemInit();
	Systick_Config(72);
	
	//Configure pinout SPI1
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 5); // SCK
	GPIO_configuration(GPIOPORT_A, MODE_INPUT, IN_FLOATING_MODE, 6); 		//MISO
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, 7); //MOSI
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_PUSHPULL, 4);		//NSS
	
	GPIO_configuration(GPIOPORT_C, MODE_OUTPUT_50M, OUT_PUSHPULL, 14); //NSS
	
	GPIO_configuration(GPIOPORT_C, MODE_OUTPUT_50M, OUT_PUSHPULL, 13); // LED error
	
	GPIO_configuration(GPIOPORT_C, MODE_OUTPUT_50M, OUT_PUSHPULL, 15); //PWR_UP
	
	GPIO_configuration(GPIOPORT_B, MODE_INPUT, IN_PULLUpDown, 0); // TRX_CE
	
	GPIO_configuration(GPIOPORT_B, MODE_OUTPUT_50M, OUT_PUSHPULL, 1); // TX_EN
	
	//Config SPI1

	config.spi		=	SPIx1;
	config.spiMode	=	SPI_MASTER;
	config.spiModeClock = SPI_CLOCK_1;
	config.spiBaudrate	= SPI_FCLK_128;
	config.spiFrame			=	SPI_DFF_8_BITS;
	config.spiFirst			=	SPI_FirstMSB;
	config.spiNSS				=	SPI_NSS_Software;
	config.spiIT				=	SPI_RX;
	
	SPI_Init(config);

	GPIO_WriteBit(GPIOPORT_C, 13, (BIT)SPI_Error(SPIx1));
	
	//Mode power down and SPI programming
	// Active mode - Radio Enable - ShockBurst TX
	// PWR_UP = 1 - TRX-CE = 1 - TX-EN = 0
	GPIO_WriteBit(GPIOPORT_C, 15, BIT_SET);		//	Set PWR_UP	High
//	GPIO_WriteBit(GPIOPORT_B, 0, BIT_RESET);		//	Set TRX-CE	High
	GPIO_WriteBit(GPIOPORT_B, 1, BIT_SET);		//	Set TX-EN		High
	
	read = GPIO_ReadBit(GPIOPORT_B, 0);
	
	GPIO_WriteBit(GPIOPORT_A, 14, BIT_RESET);
	SPI_WriteData(SPIx1, 0x01);
	delay_ms(10);
	SPI_WriteData(SPIx1, 0x00);
	GPIO_WriteBit(GPIOPORT_A, 14, BIT_SET);
	

	
	while(1);
}



void SPI1_IRQHandler(void){
	data = SPI_ReadData(SPIx1);
}

