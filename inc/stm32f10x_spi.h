#define __STM32F10X_SPI_H

typedef enum{
	SPIx1		=	(1 << 12),
	SPIx2		=	(1 << 14),
	SPIx3		=	(1 << 15)
}SPIx;

typedef enum{
	SPI_MASTER		= 	1,
	SPI_SLAVE		=	0
}SPI_MODE;

typedef enum{
	DFF_8_BITS		=	0,
	DFF_16_BITS		=	1
}SPI_FRAME;

typedef enum{
	SPI_NO,
	SPI_YES
}SPI_IT;


//BAUD RATE only use with mode MASTER
typedef enum{
	FCLK_2		=	0x000,
	FCLK_4		=	0x001,
	FCLK_8		=	0x010,
	FCLK_16		=	0x011,
	FCLK_32		=	0x100,
	FCLK_64		=	0x101,
	FCLK_128	=	0x110,
	FLCK_256	=	0x111
}SPI_BAUDRATE;

void SPI_configuration(SPIx SPI, SPI_MODE mode, SPI_FRAME frame, SPI_BAUDRATE baud, SPI_IT it, unsigned char vector);
void SPI_WriteData(SPIx SPI, unsigned char data);
unsigned char SPI_ReadData(SPIx SPI);

