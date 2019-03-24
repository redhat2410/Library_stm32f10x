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
}WORD_LENGTH;

typedef enum{
	SP_1BIT		=	0x00,
	SP_05BIT	=	0x01,	//thuong hop nay khong su dung cho UART4 va UART5
	SP_2BIT		=	0x10,
	SP_15BIT	=	0x11	//thuong hop nay khong su dung cho UART4 va UART5
}BIT_STOP;

typedef enum{
	IT_NO	=	0x00,
	IT_YES	=	0x01
}IT_USART;

typedef enum{
	BR_2400			=	0x7530,
	BR_9600			=	0x1D4C,
	BR_19200		=	0xEA6,
	BR_57600		=	0x4E2,
	BR_115200		=	0x271
}BAUDRATE;



void USART_configuration(USARTX usart, WORD_LENGTH length, BIT_STOP bstop, BAUDRATE baud, IT_USART it, unsigned char vector);
void USART_WriteData(USARTX usart, unsigned char data);
unsigned char USART_ReadData(USARTX usart);

