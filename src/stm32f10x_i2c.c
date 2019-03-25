#include "stm32f10x.h"
#include "stm32f10x_i2c.h"

#ifdef	USE_I2C
void I2C_configuration_master(void){
	//Enable clock for I2C1
	*RCC.APB1ENR	|= (1 << 21);
	//config CR2 register in order to generate correct timing usage frequency 8Mhz ( FREQ = 125ns)
	*I2C1.CR2 = (uint32_t)0x08;
	//Select mode clock master Sm/Fm ( select Sm mode)
	*I2C1.CCR &= ~(1 << 15);
	//config clock control register in Fm/Sm mode
	/*
		+ With Sm mode __/--T(high)--\__T(low)____/
				With T(high) == T(low)
					T(high) = CCR(11:0) * FREQ
					T(low)	=	CCR(11:0) * FREQ
		+ With Fm mode
				Check DUTY = 0
					T(high) = CCR(11:0) * FREQ
					T(low)	=	CCR(11:0) * FREQ * 2
				Check DUTY = 1 ( to reach 400 KHz)
					T(high) = CCR(11:0) * FREQ * 9
					T(low)	=	CCR(11:0) * FREQ * 16
	----------------------------------------------------------------
		Instance I want SCL = 100kHz in Sm mode with FREQ = 125ns
			<=> T(high) = T(low) = (1/(SCL)) / 2  = 5000ns
			<=> 5000ns = CCR * 125ns => CCR = 40d = 0x28h = CCR(11:0)
			<=> CCR(11:0) = 0x28h
	*/
	*I2C1.CCR |= (uint32_t)0x28;
	//config the rise time register
	*I2C1.TRISE = (uint32_t)0x09;
	//Enable peripheral
	*I2C1.CR1 |= (1 << 0);
	//generates START and STOP bit condition
	*I2C1.CR1 |= (1 << 8) | (1 << 9);
}

void I2C_configuration_slave(void){
	
}

#endif
