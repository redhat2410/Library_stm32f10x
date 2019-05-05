#include "stm32f10x.h"
#include "stm32f10x_spi.h"

#ifdef	USE_SPI

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
		//set baud rate only mode master
		*spi->CR1	|= (baud << 3);
<<<<<<< HEAD
		// In mode master, config clock and NSS
		*spi->CR1 &= ~(1 << 1); //config bit CPOL in CR1
		*spi->CR1 &= ~(1 << 0); //config bit CPHA in CR1
=======
		
>>>>>>> 833e508470e45a4c18d086b1920e221120141996
		//config NSS in SOFTWARE (HARDWARE)
		/*
			How to config NSS pin
			Case SSM = 1 (Software)
				pinout NSS of stm32f10x isn't use and it can use as GPIO
				* Need set bit SSOE, if it wasn't set, The flag MODF should be set. (MODF fault)
			Case SSM = 0 (Hardware)
		*/
		*spi->CR1 |= (1 << 9); //config bit SSM
		*spi->CR1 |= (1 << 8); //config bit SSI
<<<<<<< HEAD
		//set mode master
		*spi->CR1 |= (1 << 2);
=======
>>>>>>> 833e508470e45a4c18d086b1920e221120141996
	}
	else{
		//set mode slave
		*spi->CR1 &=	~(1 << 2);
	}
	//Configure MSBFIRST bit
	*spi->CR1 &= ~(1 << 7);
	//Configure Clock about clock phase
	*spi->CR1 &= ~(1 << 1); // config bit CPOL in CR1
	*spi->CR1 &= ~(1 << 0); // config bit CPHA in CR1
	//set data frame 8 or 16 bits
	if(frame == SPI_DFF_8_BITS) *spi->CR1 &=	~(1 << 11);
	else *spi->CR1	|=	(1 << 11);

	//Setup interrupt receiver
	*spi->CR2 |=	(it << 6);
	//Enable SPI
	*spi->CR1 |=	(1 << 6);
	//if(it == SPI_YES) NVIC_SetPriority((IRQn_Typedef)vector, 1);
}

void SPI_Init(SPI_Configure config){
	SPI_Typedef* spi = SPI_SELECT_X(config.spi);
	//enable clock for spi
	if(config.spi	==	SPIx1)	*RCC.APB2ENR	|=	config.spi;
	else *RCC.APB1ENR	|=	config.spi;
	if(config.spiMode == SPI_MASTER){
		//Configure SPI master mode
		/*
			In master mode would configure
					+ Master mode bit
					+	Baudrate
					+ Config NSS hardware/software
		*/
		*spi->CR1 |= (1 << 2); // config master mode
		//configure baudrate
		*spi->CR1 |= ((uint8_t)config.spiBaudrate << 3);
		//configure NSS hardware or software
		if(config.spiNSS == SPI_NSS_Hardware){
			//reset bit SSM in CR1
			*spi->CR1 &= ~(1 << 9); //SSI
			//config pinout NSS default in GPIO in hardware mode
			*spi->CR2 |= (1 << 2);
		}
		else{
			//configure NSS software
			//set bit SSM and SSI
			*spi->CR1 |= (1 << 9);// bit SSM
			*spi->CR1 |= (1 << 8);// bit SSI
		}
		
	}
	else{
		//Configure SPI slave mode
		/*
			In slave mode woudl configue:
					+	Slave mode bit
					+	Config NSS hardware/software
		*/
		*spi->CR1 &= ~(1 << 2); // config slave mode
		if(config.spiNSS == SPI_NSS_Hardware){
			*spi->CR1 &= ~(1 << 9);
			*spi->CR2 |= (1 << 2);
		}
		else{
			*spi->CR1 |= (1 << 9);
			*spi->CR1 |= (1 << 8);
		}
	}
	//Configure common
	/*
		+	Config phase clock and relationships between the data transfer and the serial clock
		+ Set data frame for SPI ( 8 or 16 bit)
		+	Config the first bit transfer is ( LSB or MSB )
		+ Config enable interrupt in SPI include transmission, receiver, fault flag... .
		+	Set enable SPI
	*/
	/*Config phase clock with CPHA and CPOL in CR1*/
	switch((uint8_t)config.spiModeClock){
		case SPI_CLOCK_1:
				*spi->CR1 &= ~(1 << 0); //CPHA
				*spi->CR1 &= ~(1 << 1); //CPOL
			break;
		case SPI_CLOCK_2:
				*spi->CR1 |= (1 << 0);
				*spi->CR1 &= ~(1 << 1);
			break;
		case SPI_CLOCK_3:
				*spi->CR1 &= ~(1 << 0);
				*spi->CR1 |= (1 << 1);
			break;
		case SPI_CLOCK_4:
				*spi->CR1 |= (1 << 0);
				*spi->CR1 |= (1 << 1);
			break;
		default:
			break;
	}
	
	//Config data frame in spi 8 or 16 bit
	if(config.spiFrame == SPI_DFF_8_BITS) *spi->CR1 &= ~(1 << 11);
	else *spi->CR1 |= (1 << 11);
	
	//config the first bit transfer (LSB or MSB)
	if(!config.spiFirst) *spi->CR1 &= ~(1 << 7);
	else *spi->CR1 |= (1 << 7);
	
	//Configure interrupt in SPI
	switch((uint8_t)config.spiIT){
		case SPI_NO:
				*spi->CR2 &= ~(1 << 5); // interrupt fault flag
				*spi->CR2 &= ~(1 << 6); // interrupt RX
				*spi->CR2 &= ~(1 << 7); // interrupt TX
			break;
		case SPI_TX:
				*spi->CR2 &= ~(1 << 5); // disable interrupt fault flag
				*spi->CR2 &= ~(1 << 6); // disable interrupt RX
				*spi->CR2 |= (1 << 7); //enable interrupt TX
			break;
		case SPI_RX:
				*spi->CR2 &= ~(1 << 5);
				*spi->CR2 |= (1 << 6);
				*spi->CR2 &= ~(1 << 7);
			break;
		case SPI_ERR:
				*spi->CR2 |= (1 << 5);
				*spi->CR2 &= ~(1 << 6);
				*spi->CR2 &= ~(1 << 7);
			break;
		default:
			break;
	}
	
	//Enable SPI
	*spi->CR1 |= (1 << 6);
	
	NVIC_SetPriority((IRQn_Typedef)SPI1_IRQn, 1);
}

/*	Fucntion SPI_WriteData with parametes
	SPIx
	Data
Function implement send data 
*/
void SPI_WriteData(SPIx SPI, unsigned char data){
	SPI_Typedef*	spi	=	SPI_SELECT_X(SPI);
	uint32_t temp;
	//Check flag TXE is reset 
	if((*spi->SR & (uint32_t)0x40) == (uint32_t)0x40)
			temp = *spi->DR;
	//write data into DR register
	*spi->DR	= (uint8_t)data;
	//Wait flag TXE set
	while(!((*spi->SR >> 1) & (uint32_t)0x01));
	//otherwise shall not be write data in reg DR
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

/*
	Function SPI_WriteData_16bit implement write data with length 16bit
*/
void SPI_WriteData_16bit(SPIx SPI, uint16_t data){
	SPI_Typedef*	spi = SPI_SELECT_X(SPI);
	//write data into DR register
	*spi->DR = data;
	//Wait flag TXE set
	while(!(*spi->SR >> 1) & (uint32_t)0x01);
}
/*
	Function SPI_ReadData_16bit implement read data with length 16bit
*/
uint16_t SPI_ReadData_16bit(SPIx SPI){
	SPI_Typedef* spi = SPI_SELECT_X(SPI);
	//Wait flag RXE set
	while(!(*spi->SR & (uint32_t)0x01));
	//Read data in DR register
	return (uint16_t)*spi->DR;
}

/*
	Function HandleError implement process when error flags was set
*/
uint32_t SPI_HandleError(SPIx SPI){
	uint32_t temp = 0;
	SPI_Typedef* spi = SPI_SELECT_X(SPI);
	//process error flag OVR
	if((*spi->SR & (uint32_t)0x40) == (uint32_t)0x40)
		temp = *spi->DR;
	return temp;
}


#endif
