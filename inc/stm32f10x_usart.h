/********************************Description USART******************************/
/*
		In stm32f10x has five module uart and three module USART ( USART1, USART2, USART3, UART4, UART5)
		- USART is universal synchronous asynchronous receiver transmitter
		- Configuration pinout for USART
			+ USARTx_TX		AF push-pull									( for asynchronous )
			+ USARTx_RX		Input floating/Input pull-up	( for asynchronous )
			+ USARTx_CK		AF push-pull									( for synchronous )
			+ USARTx_RTS	AF push-pull									( Hardware flow control)
			+ USARTx_CTS	Input floating/Input pull-up	( Hardware flow control)
		- Pinout of USART in stm32f10x
				.	Pinout USART1
						Alternate funtion				remap = 0							remap = 1
							USART1_TX								PA9										PB6
							USART1_RX								PA10									PB7
				.	Pinout USART2
						Alternate funtion				remap = 0							remap = 1
							USART2_CTS							PA0										PD3
							USART2_RTS							PA1										PD4
							USART2_TX								PA2										PD5
							USART2_RX								PA3										PD6
							USART2_CK								PA4										PD7
				.	Pinout USART3
						Alternate funtion				remap = 0							remap = 1
							USART3_TX								PB10									PC10
							USART3_RX								PB11									PC11
							USART3_CK								PB12									PC12
							USART3_CTS							PB13									PB13
							USART3_RTS							PB14									PB14
		
*/
/********************************Description USART******************************/
#define __STM32F10X_USART_H

typedef enum{
	USARTx1	=	(1 << 14),
	USARTx2	=	(1 << 17),
	USARTx3	=	(1 << 18),
	UARTx4	=	(1 << 19),
	UARTx5	=	(1 << 20)
}USARTX;

typedef enum{
	USART_D_8_BITS	=	0x00,
	USART_D_9_BITS	=	0x01
}USART_WordLength;

typedef enum{
	USART_SP_1BIT		=	0x00,
	USART_SP_05BIT	=	0x01,	//thuong hop nay khong su dung cho UART4 va UART5
	USART_SP_2BIT		=	0x10,
	USART_SP_15BIT	=	0x11	//thuong hop nay khong su dung cho UART4 va UART5
}USART_BitStop;

typedef enum{
	USART_IT_TXEIE_RST	= ~(1 << 7),
	USART_IT_TXEIE			= (1 << 7),
	USART_IT_TCIE_RST		= ~(1 << 6),
	USART_IT_TCIE				= (1 << 6),
	USART_IT_RXNEIE_RST	= ~(1 << 5),
	USART_IT_RXNEIE			= (1 << 5)
}USART_IT;

typedef enum{
	USART_BR_2400			=	0x7530,
	USART_BR_9600			=	0x1D4C,
	USART_BR_19200		=	0xEA6,
	USART_BR_57600		=	0x4E2,
	USART_BR_115200		=	0x271
}USART_BAUDRATE;

typedef struct{
	USARTX						usart;
	USART_WordLength	length;
	USART_BAUDRATE		baud;
	USART_BitStop			stop;
	signed int				it;
}USART_Configure;



void USART_configuration(USARTX usart, USART_WordLength length, USART_BitStop bstop, USART_BAUDRATE baud, USART_IT it, unsigned char vector);
void USART_Init(USART_Configure config);
void USART_WriteData(USARTX usart, unsigned char data);
unsigned char USART_ReadData(USARTX usart);

