
/********************************Description SPI******************************/
/*
	- In stm32f103C8 has three module SPIx (SPI1, SPI, SPI3)
	- SPI active in two mode: Master and Slave
	- Configuration pinout SPI in a mode MASTER
		.	SPIx_SCK		AF-push-pull
		.	SPIx_MOSI		AF-push-pull
		.	SPIx_MISO		Input floating / Input pull-up
		.	SPIx_NSS(Hardware master/slave)								Input floating / Input pull-up / Input pull-down
			SPIx_NSS(Hardware master/ NSS output enable)	AF-push pull
			SPIx_NSS(Software)														No used, Can be used as GPIO
	-	Configuration pinout SPI in a mode SLAVE
		.	SPIx_SCK		Input floating
		.	SPIx_MOSI		Input floating / Input pull-up
		.	SPIx_MISO		AF-push-pull(point to point) / AF-open-drain(multi-slave)
		.	SPIx_NSS		similar NSS of mode Master
	- Pinout SPIx in stm32f103c8
		. Pinout SPI1
				Alternate funtion				remap = 0							remap = 1
				SPI_NSS									PA4										PA15
				SPI_SCK									PA5										PB3
				SPI_MISO								PA6										PB4
				SPI_MOSI								PA7										PB5
		
		.	Pinout SPI3
				Alternate funtion				remap = 0							remap = 1
				SPI_NSS									PA15									PA4
				SPI_SCK									PB3										PC10
				SPI_MISO								PB4										PC11
				SPI_MOSI								PB5										PC12
*/
/********************************Description SPI******************************/
#define __STM32F10X_SPI_H

//SPIx
typedef enum{
	SPIx1		=	(1 << 12),
	SPIx2		=	(1 << 14),
	SPIx3		=	(1 << 15)
}SPIx;


//SPI MODE ( MASTER and SLAVE)
typedef enum{
	SPI_MASTER		= 	1,
	SPI_SLAVE		=	0
}SPI_MODE;

//SPI DATA BIT
typedef enum{
	SPI_DFF_8_BITS		=	0,
	SPI_DFF_16_BITS		=	1
}SPI_FRAME;


//SPI INTERUPPT
typedef enum{
	SPI_NO,
	SPI_YES
}SPI_IT;


//BAUD RATE only use with mode MASTER
typedef enum{
	SPI_FCLK_2		=	0x000,
	SPI_FCLK_4		=	0x001,
	SPI_FCLK_8		=	0x010,
	SPI_FCLK_16		=	0x011,
	SPI_FCLK_32		=	0x100,
	SPI_FCLK_64		=	0x101,
	SPI_FCLK_128	=	0x110,
	SPI_FLCK_256	=	0x111
}SPI_BAUDRATE;


/**************SPI FUNCTION CONFIGURATION**************/
void SPI_configuration(SPIx SPI, SPI_MODE mode, SPI_FRAME frame, SPI_BAUDRATE baud, SPI_IT it, unsigned char vector);
void SPI_WriteData(SPIx SPI, unsigned char data);
unsigned char SPI_ReadData(SPIx SPI);
void SPI_WriteData_16bit(SPIx SPI, unsigned short data);
unsigned short SPI_ReadData_16bit(SPIx SPI);
/**************SPI FUNCTION CONFIGURATION**************/

