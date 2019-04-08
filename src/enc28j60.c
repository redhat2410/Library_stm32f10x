#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "enc28j60.h"


#define		SCK		5
#define		MISO	6
#define		MOSI	7
#define		NSS		4
#define		CS		13


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
	//Config pin chip select
	GPIO_configuration(GPIOPORT_C, MODE_OUTPUT_50M, OUT_PUSHPULL, CS);
	//Conifguration SPI in mode MASTER, data bit 8bit, div SCK 16, interrupt NO
	SPI_configuration(SPIx1, SPI_MASTER, SPI_DFF_16_BITS, SPI_FCLK_2, SPI_NO, SPI1_IRQn);
	//Disable Chip
	GPIO_WriteBit(GPIOPORT_A, NSS, BIT_SET);
}

void enableChip(void){
	//Set pin NSS to LOW (0)
	GPIO_WriteBit(GPIOPORT_C, CS, BIT_RESET);
}

void disableChip(void){
	//Set pin NSS to HIGH (1)
	GPIO_WriteBit(GPIOPORT_C, CS, BIT_SET);
}

void writeOp(uint8_t op, uint8_t address, uint8_t data){
	uint16_t tmp = 0x0000;
	//enable chip
	enableChip();
	//send operation and address of register to enc28j60
	tmp |= ( op | address) << 8;
	//send data will be written for register
	tmp |= data;
	//Send data to enc28j60
	SPI_WriteData_16bit(SPIx1, tmp);
	//disable chip
	disableChip();
}

uint16_t readOp(uint8_t op, uint8_t address){
	uint16_t rev = 0;
	uint16_t tmp = 0x0000;
	//enable chip
	enableChip();
	//Send operation and address of register to enc28j60
	tmp |= ( op | address ) << 8;
	SPI_WriteData_16bit(SPIx1, op | address);
	//Verify address is MII or MAC
	if(address & 0x80)
		SPI_WriteData(SPIx1, 0x00);
	//Receiver data from enc28j60
	rev = SPI_ReadData_16bit(SPIx1);
	//disable chip
	disableChip();
	return rev;
}





