#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "enc28j60.h"


#define		SCK		5
#define		MISO	6
#define		MOSI	7
#define		NSS		8

void initSPI(void){
	//Conifguration SPI in mode MASTER, data bit 8bit, div SCK 16, interrupt NO
	SPI_configuration(SPIx1, SPI_MASTER, SPI_DFF_8_BITS, SPI_FCLK_16, SPI_NO, 0);
	//Config pinout for SPI
	
}
