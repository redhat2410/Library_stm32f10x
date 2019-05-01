#include "stm32f10x.h"
#include "stm32f10x_usart.h"

#ifdef	USE_UART

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

void USART_configuration(USARTX usart, USART_WordLength length, USART_BitStop bstop, USART_BAUDRATE baud, USART_IT it, unsigned char vector){
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
	//if(it == IT_YES) NVIC_SetPriority((IRQn_Typedef)vector, 1);

}

void USART_Init(USART_Configure config){
	//Select usart
	USART_Typedef* usartx = USART_SELECT_X(config.usart);
	//Enable clock for USART
	if(config.usart == USARTx1)
		*RCC.APB2ENR |= config.usart; // Enable clock USARTx1 in APB2ENR of RCC
	else
		*RCC.APB1ENR |= config.usart; // Enable clock USARTx2, USARTx3, UARTx4, UARTx5 in APB1ENR of RCC
	
	//Enable USART
	*usartx->CR1 |= (1 << 13);
	
	//set word length
	*usartx->CR1 |= (config.length << 12);
	
	//set bit stop
	*usartx->CR2 |= (config.stop << 12);
	//set transmitter and receiver
	*usartx->CR1 |= (1 << 3); //Transmitter
	*usartx->CR1 |= (1 << 2); //Receiver
	//Interrupt TXEIE, TCIE and RXNEIE
	switch((uint8_t)config.it){
		case USART_IT_NO:
				*usartx->CR1 &= ~(1 << 7); // disable interrupt TXEIE
				*usartx->CR1 &= ~(1 << 6); // disable interrupt TCIE ( transmission complete interrupt enable)
				*usartx->CR1 &= ~(1 << 5); // disable interrupt RXNE
			break;
		case USART_IT_RXNEIE:
				*usartx->CR1 |= (1 << 5); //Enable interrupt RXNE
				*usartx->CR1 &= ~(1 << 6);
				*usartx->CR1 &= ~(1 << 7);
			break;
		case USART_IT_TCIE:
				*usartx->CR1 |= (1 << 6);
			break;
		case USART_IT_TXEIE:
			break;
		default:
			break;
	}
	
	
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

#endif
