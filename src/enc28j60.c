#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "enc28j60.h"


#define		SCK		5
#define		MISO	6
#define		MOSI	7
#define		NSS		4
#define		CS		13

static uint8_t	Enc28j60Bank;

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
	SPI_configuration(SPIx1, SPI_MASTER, SPI_DFF_8_BITS, SPI_FCLK_2, SPI_NO, SPI1_IRQn);
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

void setBank(unsigned char address){
	if((address & BANK_MASK) != Enc28j60Bank){
		writeOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_BSEL1|ECON1_BSEL0);
		Enc28j60Bank = address & BANK_MASK;
		writeOp(ENC28J60_BIT_FIELD_SET, ECON1, Enc28j60Bank>>5);
	}
}

uint8_t	readRegByte(uint8_t address){
	setBank(address);
	return readOp(ENC28J60_READ_CTRL_REG, address);
}

uint16_t	readReg(uint8_t address){
	return readRegByte(address) + (readRegByte(address + 1) << 8);
}

void writeRegByte(uint8_t address, uint8_t data){
	setBank(address);
	writeOp(ENC28J60_WRITE_CTRL_REG, address, data);
}

void writeReg(uint8_t address, uint16_t data){
	writeRegByte(address, data);
	writeRegByte(address + 1, data >> 8);
}

uint16_t readPhyByte(uint8_t address){
	writeRegByte(MIREGADR, address);
	writeRegByte(MICMD, MICMD_MIIRD);
	while(readRegByte(MISTAT) & MISTAT_BUSY)
		;
	writeRegByte(MICMD, 0x00);
	return readRegByte(MIRD + 1);
}

void writePhy(uint8_t address, uint16_t data){
	writeRegByte(MIREGADR, address);
	writeReg(MIWR, data);
	while(readRegByte(MISTAT) & MISTAT_BUSY)
		;
}




