#include "stm32f10x.h"
#include "stm32f10x_spi.h"

SPI_Typedef*	SPI_SELECT_X(SPIx SPI){
	SPI_Typedef* tmp;
	switch(SPI){
		case SPIx1:	tmp	=	&SPI1; break;
		case SPIx2:	tmp	=	&SPI2; break;
		case SPIx3:	tmp	=	&SPI3;	break;
	}
	return tmp;
}
/*Function SPI_configuration with parametes
	SPIx
	SPI_MODE
	SPI_FRAME
	BAUDRATE
	SPI_IT
	vector interrupt
Implement configure features for SPI about 
	MODE	(MASTER, SLAVE)
	FRAME (8	BIT, 16	BIT)
	BAUD	(/2, /4, /8 ...)
	
*/
void SPI_configuration(SPIx SPI, SPI_MODE mode, SPI_FRAME frame, SPI_BAUDRATE baud, SPI_IT it, unsigned char vector){
	//Select spi 
	SPI_Typedef* spi	=	SPI_SELECT_X(SPI);
	//enable clock for spi
	if(SPI	==	SPIx1)	*RCC.APB2ENR	|=	SPI;
	else *RCC.APB1ENR	|=	SPI;
	//Select mode for SPI ( master or slave)
	if(mode == SPI_MASTER){
		//set mode master
		*spi->CR1 |= (1 << 2);
		//set baud rate only mode master
		*spi->CR1	|= (baud << 3);
	}
	else
		//set mode slave
		*spi->CR1 &=	~(1 << 2);
	//set data frame 8 or 16 bits
	if(frame == DFF_8_BITS) *spi->CR1 &=	~(1 << 11);
	else *spi->CR1	|=	(1 << 11);
	//Configure LSBFIRST bit
	*spi->CR1 &= ~(1 << 7);
	//Setup interrupt receiver
	*spi->CR2 |=	(it << 6);
	//Set up NSS software 
	*spi->CR1 |=	(1 << 9);
	*spi->CR1	|=	(1 << 8);
	//Enable SPI
	*spi->CR1 |=	(1 << 6);
	if(it == SPI_YES) NVIC_SetPriority((IRQn_Typedef)vector, 1);
}
/*	Fucntion SPI_WriteData with parametes
	SPIx
	Data
Function implement send data 
*/
void SPI_WriteData(SPIx SPI, unsigned char data){
	SPI_Typedef*	spi	=	SPI_SELECT_X(SPI);
	//write data into DR register
	*spi->DR	= (uint32_t)data;
	//Wait flag TXE set
	while(!(*spi->SR >> 1) & (uint32_t)0x01);
}

/*	Function SPI_ReadData with parameter
	SPIx
Function implement receiver data
*/
unsigned char SPI_ReadData(SPIx SPI){
	SPI_Typedef* spi	=	SPI_SELECT_X(SPI);
	//Wait flag RXE set
	while(!(*spi->SR & (uint32_t)0x01));
	//Read data in DR register
	return (uint8_t)*spi->DR;
}

