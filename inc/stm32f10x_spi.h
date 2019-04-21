
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
	SPI_MASTER		= 1,
	SPI_SLAVE			=	0
}SPI_MODE;

//SPI DATA BIT
typedef enum{
	SPI_DFF_8_BITS		=	0,
	SPI_DFF_16_BITS		=	1
}SPI_FRAME;


//SPI INTERUPPT
typedef enum{
	SPI_NO,
	SPI_TX,
	SPI_RX,
	SPI_ERR
}SPI_IT;

//NSS Hardware or Software
typedef enum{
	SPI_NSS_Hardware,
	SPI_NSS_Software
}SPI_NSS;

// 4 mode in phase clock
/*
	4 mode in config phase clock and relationship between data transfer serial clock
	Config 2 bit CPOL and CPHA in register CR1 of SPI
	MODE 1
		+ Data transfer when clock in falling edge
		+ First clock for first data
			-> Shall be reset CPOL
			-> Shall be reset CPHA
	MODE 2
		+ Data transfer when clock in falling edge
		+ Second clock for first data
			-> Shall be reset CPOL
			-> Shall be set		CPHA
	MODE 3
		+ Data transfer when clock in rising edge
		+ First clock for first data
			-> Shall be set 	CPOL
			-> Shall be reset CPHA
	MODE 4
		+ Data transfer when clock in rising edge
		+ Second clock for first data
			-> Shall be set CPOL
			-> Shall be set CPHA
*/
typedef enum{
	SPI_CLOCK_1,
	SPI_CLOCK_2,
	SPI_CLOCK_3,
	SPI_CLOCK_4
}SPI_MODE_CLOCK;

typedef enum{
	SPI_FirstMSB,
	SPI_FirstLSB
}SPI_FIRSTBIT;

//BAUD RATE only use with mode MASTER
typedef enum{
	SPI_FCLK_2		=	0x0,
	SPI_FCLK_4		=	0x1,
	SPI_FCLK_8		=	0x2,
	SPI_FCLK_16		=	0x3,
	SPI_FCLK_32		=	0x4,
	SPI_FCLK_64		=	0x5,
	SPI_FCLK_128	=	0x6,
	SPI_FLCK_256	=	0x7
}SPI_BAUDRATE;



typedef struct{
	SPIx						spi;
	SPI_MODE 				spiMode;
	SPI_BAUDRATE 		spiBaudrate;
	SPI_MODE_CLOCK	spiModeClock;
	SPI_FRAME				spiFrame;
	SPI_NSS					spiNSS;
	SPI_FIRSTBIT		spiFirst;
	SPI_IT					spiIT;
}SPI_Configure;


/**************SPI FUNCTION CONFIGURATION**************/
void SPI_configuration(SPIx SPI, SPI_MODE mode, SPI_FRAME frame, SPI_BAUDRATE baud, SPI_IT it, unsigned char vector);
void SPI_Init(SPI_Configure config);
void SPI_WriteData(SPIx SPI, unsigned char data);
unsigned char SPI_ReadData(SPIx SPI);
void SPI_WriteData_16bit(SPIx SPI, unsigned short data);
unsigned short SPI_ReadData_16bit(SPIx SPI);
/**************SPI FUNCTION CONFIGURATION**************/

