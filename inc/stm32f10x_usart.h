#define __STM32F10X_USART_H

typedef enum{
	USARTx1	=	(1 << 14),
	USARTx2	=	(1 << 17),
	USARTx3	=	(1 << 18),
	UARTx4	=	(1 << 19),
	UARTx5	=	(1 << 20)
}USARTX;

typedef enum{
	D_8_BITS	=	0x00,
	D_9_BITS	=	0x01
}USART_WordLength;

typedef enum{
	SP_1BIT		=	0x00,
	SP_05BIT	=	0x01,	//thuong hop nay khong su dung cho UART4 va UART5
	SP_2BIT		=	0x10,
	SP_15BIT	=	0x11	//thuong hop nay khong su dung cho UART4 va UART5
}USART_BitStop;

typedef enum{
	USART_IT_NO,
	USART_IT_TXEIE,
	USART_IT_TCIE,
	USART_IT_RXNEIE
}USART_IT;

typedef enum{
	BR_2400			=	0x7530,
	BR_9600			=	0x1D4C,
	BR_19200		=	0xEA6,
	BR_57600		=	0x4E2,
	BR_115200		=	0x271
}USART_BAUDRATE;

typedef struct{
	USARTX						usart;
	USART_WordLength	length;
	USART_BAUDRATE		baud;
	USART_BitStop			stop;
	USART_IT					it;
}USART_Configure;



void USART_configuration(USARTX usart, USART_WordLength length, USART_BitStop bstop, USART_BAUDRATE baud, USART_IT it, unsigned char vector);
void USART_Init(USART_Configure config);
void USART_WriteData(USARTX usart, unsigned char data);
unsigned char USART_ReadData(USARTX usart);

