#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "enc28j60.h"


#define		SCK		5
#define		MISO	6
#define		MOSI	7
#define		NSS		8

void initSPI(void){
	//Config pinout for SPI
	//Config pin SCK
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, SCK);
	//Config pin MISO
	GPIO_configuration(GPIOPORT_A, MODE_INPUT, IN_FLOATING_MODE, MISO);
	//Config pin MOSI
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_AFPUSHPULL, MOSI);
	//Config pin NSS
	GPIO_configuration(GPIOPORT_A, MODE_OUTPUT_50M, OUT_PUSHPULL, NSS);
	//Conifguration SPI in mode MASTER, data bit 8bit, div SCK 16, interrupt NO
	SPI_configuration(SPIx1, SPI_MASTER, SPI_DFF_8_BITS, SPI_FCLK_16, SPI_NO, 0);
}

void enableChip(void){
	//Set pin NSS to LOW (0)
	GPIO_WriteBit(GPIOPORT_A, NSS, BIT_RESET);
}

void disableChip(void){
	//Set pin NSS to HIGH (1)
	GPIO_WriteBit(GPIOPORT_A, NSS, BIT_SET);
}

void writeOp(uint8_t op, uint8_t address, uint8_t data){
	//enable chip
	enableChip();
	//send operation and address of register to enc28j60
	SPI_WriteData(SPIx1, op | address);
	//send data will be written for register
	SPI_WriteData(SPIx1, data);
	//disable chip
	disableChip();
}

uint8_t readOp(uint8_t op, uint8_t address){
	uint8_t rev = 0;
	//enable chip
	enableChip();
	//Send operation and address of register to enc28j60
	SPI_WriteData(SPIx1, op | address);
	SPI_WriteData(SPIx1, 0x00);
	//Verify address is MII or MAC
	if(address & 0x80)
		SPI_WriteData(SPIx1, 0x00);
	//Receiver data from enc28j60
	rev = SPI_ReadData(SPIx1);
	//disable chip
	disableChip();
	return rev;
}



