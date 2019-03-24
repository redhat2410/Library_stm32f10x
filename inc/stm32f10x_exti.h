#define __STM32F10x_EXTI_H

typedef enum{
	EXTIPORT_A	=	0x00,
	EXTIPORT_B	=	0x01,
	EXTIPORT_C	=	0x02,
	EXTIPORT_D	=	0x03,
	EXTIPORT_E	=	0x04
}EXTIPORT;


typedef enum{
	TG_RISING		=	0x00,
	TG_FALLING	=	0x01
}TRIGGER;


void EXTI_configuration(EXTIPORT port, TRIGGER trigger, unsigned char pin, unsigned char IRQn);
void EXTI_ClearFlag(unsigned char pin);
