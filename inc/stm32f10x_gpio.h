#define __STM32F10x_GPIO_H

typedef enum{
	GPIOPORT_A	= 0x04,
	GPIOPORT_B	=	0x08,
	GPIOPORT_C	=	0x10,
	GPIOPORT_D	=	0x20,
	GPIOPORT_E	=	0x40
}GPIOPORT;

typedef enum{
	MODE_INPUT			=	0x00,
	MODE_OUTPUT_10M	=	0x01,
	MODE_OUTPUT_2M	=	0x02,
	MODE_OUTPUT_50M	=	0x03
}GPIOMODE;

typedef enum{
	IN_ANALOG_MODE		= 0x00,
	IN_FLOATING_MODE 	= 0x01,
	IN_PULLUpDown			= 0x02,
	OUT_PUSHPULL			=	0x10,	//00
	OUT_OPENDRAIN			=	0x04,	//01
	OUT_AFPUSHPULL		=	0x08,	//10
	OUT_AFOPENDRAIN		=	0x0C	//11
}GPIOCONF;

typedef enum{
	BIT_RESET		=	0,
	BIT_SET			=	1,
	
}BIT;

//define function stm32f10x_gpio.c

void GPIO_configuration(GPIOPORT port, GPIOMODE mode, GPIOCONF conf, unsigned char pin);
void GPIO_WriteBit(GPIOPORT port, unsigned char pin, BIT bit);
BIT	GPIO_ReadBit(GPIOPORT port, unsigned char pin);
void GPIO_Write(GPIOPORT port, unsigned short data);
unsigned short GPIO_Read(GPIOPORT port);

