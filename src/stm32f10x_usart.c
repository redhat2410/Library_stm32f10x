#include "stm32f10x.h"
#include "stm32f10x_usart.h"


USART_Typedef* USART_SELECT_X(USARTX usart){
	USART_Typedef* tmp;
	switch(usart){
		case USARTx1:	tmp = &USART1;	break;
		case USARTx2:	tmp = &USART2;	break;
		case USARTx3:	tmp = &USART3;	break;
		case UARTx4	:	tmp = &UART4;		break;
		case UARTx5	:	tmp	=	&UART5;		break;
	}
	return tmp;
}

void USART_configuration(USARTX usart, WORD_LENGTH length, BIT_STOP bstop, BAUDRATE baud, IT_USART it, unsigned char vector){
	//uint32_t read_error = 0;
	//select usart 
	USART_Typedef* usartx = USART_SELECT_X(usart);
	//Enable clock for USART
	if(usart == USARTx1)
		*RCC.APB2ENR	|= usart;
	else
		*RCC.APB1ENR	|=	usart;
	//enable usart
	*usartx->CR1	|=	(1 << 13);
	//set word length
	*usartx->CR1	|=	(length << 12);
	//set bit stop
	*usartx->CR2	|=	(bstop << 12);
	//set baud rate for usart
	*usartx->BRR	=		(uint32_t)baud;
	//set transmitter and receiver
	*usartx->CR1	|=	(1 << 3); //transmitter
	*usartx->CR1	|=	(1 << 2); //receiver
	//set receiver interrupt
	*usartx->CR1	|=	(it << 5);
	//clear bit TC in SR
	*usartx->SR		&=	~(1 << 6);
	if(it == IT_YES) NVIC_SetPriority((IRQn_Typedef)vector, 1);

}


void USART_WriteData(USARTX usart, unsigned char data){
	USART_Typedef* usartx	=	USART_SELECT_X(usart);
	*usartx->DR	=	(uint32_t)data;
	while((*usartx->SR & (uint32_t)0x20) == (uint32_t)0x20);
}

unsigned char USART_ReadData(USARTX usart){
	USART_Typedef*	usartx = USART_SELECT_X(usart);
	while(!(*usartx->SR & (uint32_t)0x10));
	return (uint8_t)*usartx->DR;
}

