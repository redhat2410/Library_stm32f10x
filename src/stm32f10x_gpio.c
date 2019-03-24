#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


GPIO_Typedef* GPIO_SELECT_PORT(GPIOPORT port){
	GPIO_Typedef* tmp;
	switch(port){
		case GPIOPORT_A:	tmp = &GPIOA; break;
		case GPIOPORT_B:	tmp = &GPIOB; break;
		case GPIOPORT_C:	tmp = &GPIOC; break;
		case GPIOPORT_D:	tmp = &GPIOD; break;
		case GPIOPORT_E:	tmp = &GPIOE; break;
		default:	break;
	}
	return tmp;
}

uint32_t GPIO_SELECT_MODE(GPIOMODE mode, GPIOCONF conf){
	if(mode == MODE_INPUT)
			return (uint32_t)conf;
	else
			return (uint32_t)(conf >> 2);
}

void GPIO_configuration(GPIOPORT port, GPIOMODE mode, GPIOCONF conf, unsigned char pin){
	GPIO_Typedef* GPIO = GPIO_SELECT_PORT(port);
	//Enable clock for GPIO port
	*RCC.APB2ENR	|=	(uint32_t)port;
	//Configuration for port with mode and conf
	//reset CRH and CRL
	if((*GPIO->CRH & 0x88800000) == 0x88800000 || (*GPIO->CRL & 0x88800000) == 0x88800000
			|| (*GPIO->CRH & 0x44400000) == 0x44400000 || (*GPIO->CRL & 0x44400000) == 0x44400000){
		*GPIO->CRH = 0x00000000;
		*GPIO->CRL = 0x00000000;
	}
	if(pin > (unsigned char)7){
		//Set mode for GPIO
		*GPIO->CRH 	|=	(uint32_t)((uint32_t)mode << ((pin - 8) * 4));
		//Set configuration for GPIO
		*GPIO->CRH	|=	(uint32_t)(GPIO_SELECT_MODE(mode, conf) << ((pin - 8) * 4 + 2));
	}
	else{
		*GPIO->CRL	|=	(uint32_t)(mode << (pin * 4));
		*GPIO->CRL	|=	(uint32_t)(GPIO_SELECT_MODE(mode, conf) << (pin * 4 + 2));
	}
	
}

void GPIO_WriteBit(GPIOPORT port, unsigned char pin, BIT bit){
	GPIO_Typedef* GPIO = GPIO_SELECT_PORT(port);
	if(bit == BIT_SET)	*GPIO->ODR	|=	(1 << pin);
	else	*GPIO->ODR	&=	~(1 << pin);
}

BIT	GPIO_ReadBit(GPIOPORT port, unsigned char pin){
	GPIO_Typedef*	GPIO = GPIO_SELECT_PORT(port);
	return ((*GPIO->IDR >> pin) & 0x0001) ? BIT_SET : BIT_RESET;
}

void GPIO_Write(GPIOPORT port, unsigned short data){
	GPIO_Typedef* GPIO = GPIO_SELECT_PORT(port);
	*GPIO->ODR = (unsigned long)data;
}

unsigned short GPIO_Read(GPIOPORT port){
	GPIO_Typedef*	GPIO = GPIO_SELECT_PORT(port);
	return (unsigned short)*GPIO->IDR;
}
