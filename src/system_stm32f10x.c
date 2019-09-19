#include "stm32f10x.h"

RCC_Typedef 		RCC;
FLASH_Typedef 		FLASH;
GPIO_Typedef		GPIOA;
GPIO_Typedef		GPIOB;
GPIO_Typedef		GPIOC;
GPIO_Typedef		GPIOD;
GPIO_Typedef		GPIOE;
AFIO_Typedef		AFIO;
EXTI_Typedef		EXTI;


#ifdef	__STM32F10X_USART__
USART_Typedef		USART1;
USART_Typedef		USART2;
USART_Typedef		USART3;
USART_Typedef		UART4;
USART_Typedef		UART5;
#endif


NVIC_Typedef		NVIC;
SCB_Typedef			SCB;
STK_Typedef			STK;


#ifdef	__STM32F10X_SPI__
SPI_Typedef			SPI1;
SPI_Typedef			SPI2;
SPI_Typedef			SPI3;
#endif


#ifdef	USE_I2C
I2C_Typedef			I2C1;
I2C_Typedef			I2C2;
#endif


#ifdef	USE_TIM
TIM1_8_Typedef		TIM1;
TIM2_5_Typedef		TIM2;
TIM6_7_Typedef		TIM6;
TIM6_7_Typedef		TIM7;
#endif


void SetSysClock72(void);

void SystemInit(){
	//Init register
	//REG_init();
	//Enable xung HSI
	*RCC.CR |= (1 << 0);
	/*reset bit SW, HPRE, PPRE1, PPRE2, ADVPRE, MCO*/
	//reset bits SW
	*RCC.CFGR |= (1 << 0) | (1 << 1);
	//reset bit HPRE
	*RCC.CFGR &= ~(1 << 7);
	//reset PPRE1
	*RCC.CFGR &= ~(1 << 10);
	//reset PPRE2
	*RCC.CFGR &= ~(1 << 13);
	//reset ADCPRE
	*RCC.CFGR &= ~(1 << 15) | ~(1 << 14);
	//reset MCO
	*RCC.CFGR &= ~(1 << 26) | ~(1 << 25);
	/*reset HSEON, CSSON, PLLON*/
	//reset HSEON
	*RCC.CR &= ~(1 << 16);
	//reset CSSON
	*RCC.CR &= ~(1 << 19);
	//reset PLLON
	*RCC.CR &= ~(1 << 24);
	//reset HSEBYP
	*RCC.CR &= ~(1 << 18);
	/*reset PLLSRC, PLLXTPRE, PLLMUL, USBPRE / OTGFSPRE*/
	//reset PLLSRC
	*RCC.CFGR &= ~(1 << 16);
	//reset PLLMUL
	*RCC.CFGR &= ~(1 << 21) | ~(1 << 20) | ~(1 << 19);
	//reset OTGFSPRE
	*RCC.CFGR &= ~(1 << 22);
	//clear all interrupt and clear pending bits
	*RCC.CIR |= (1 << 23) | (1 << 22) | (1 << 21) | (1 << 20) | (1 << 19);
	*RCC.CIR |= (1 << 18) | (1 << 17) | (1 << 16);
	
	SetSysClock72();
}

void SetSysClock72(void){
	volatile uint32_t StartUpCounter = 0, HSEStatus = 0;
	
	//Enable HSE
	*RCC.CR |= (1 << 16);
	do{
		HSEStatus = *RCC.CR & 0x00020000;
		StartUpCounter++;
	}while((HSEStatus == 0) && (StartUpCounter != 0x05000));
	
	if((*RCC.CR & 0x00020000) != 0) HSEStatus = (uint32_t)0x01;
	else HSEStatus = (uint32_t)0x00;
	
	if(HSEStatus == (uint32_t)0x01){
		//configure FLASH wait 2 state
		*FLASH.ACR |= (uint32_t)0x10;
		*FLASH.ACR &= (uint32_t)((uint32_t)~0x03);
		*FLASH.ACR |= (uint32_t)0x02;
		//config div HPRE div1
		*RCC.CFGR &= ~(1 << 7);
		//config div PPRE2 div1
		*RCC.CFGR &= ~(1 << 13);
		//config div PPRE1 div2
		*RCC.CFGR |= (1 << 10);
		*RCC.CFGR &= ~(1 << 9) | ~(1 << 8);
		
		/*config PLLCLK = 72MHZ*/
		//clear PLLXTRE, PLLSRC, PLLMUL
		*RCC.CFGR &= ~(1 << 17) | ~(1 << 16);
		*RCC.CFGR &= ~(1 << 21) | ~(1 << 20) | ~(1 << 19);
		/*set PLLXTPRE, PLLSRC, PLLMULL*/
		//set PLLXTPRE
		*RCC.CFGR &= ~(1 << 17);
		//set PLLSRC
		*RCC.CFGR |= (1 << 16);
		//set PLLMUL
		*RCC.CFGR &= ~(1 << 21);
		*RCC.CFGR |= (1 << 20) | (1 << 19) | (1 << 18);
		
		//Enable PLL
		
		*RCC.CR |= (1 << 24);
		
		//wait PLL ready
		while(!(*RCC.CR & 0x02000000));
		
		//clear PLL SW
		*RCC.CFGR &= ~(1 << 0) | ~(1 << 1);
		//Select PLL system clock source
		*RCC.CFGR |= (1 << 1);
		*RCC.CFGR &= ~(1 << 0);
		
		//wait PLL is use sysem clock source
		
		while((*RCC.CFGR & 0x0000000C) != (uint32_t)0x08);
		
	}
}

void RCC_init(void){
	RCC.CR					=	(uint32_t*)0x40021000;
	RCC.CFGR				=	(uint32_t*)0x40021004;
	RCC.CIR					=	(uint32_t*)0x40021008;
	RCC.APB1RSTR		=	(uint32_t*)0x4002100C;
	RCC.APB2RSTR		=	(uint32_t*)0x40021010;
	RCC.AHBENR			=	(uint32_t*)0x40021014;
	RCC.APB2ENR			=	(uint32_t*)0x40021018;
	RCC.APB1ENR			=	(uint32_t*)0x4002101C;
	RCC.BDCR				=	(uint32_t*)0x40021020;
	RCC.CSR					=	(uint32_t*)0x40021024;
	RCC.AHBRSTR			=	(uint32_t*)0x40021028;
	RCC.CFGR2				=	(uint32_t*)0x4002102C;
	
	FLASH.ACR				=	(uint32_t*)0x40022000;
}
void GPIOA_init(void){
	GPIOA.CRL			=	(uint32_t*)0x40010800;
	GPIOA.CRH			=	(uint32_t*)0x40010804;
	GPIOA.IDR			=	(uint32_t*)0x40010808;
	GPIOA.ODR			=	(uint32_t*)0x4001080C;
	GPIOA.BSRR		=	(uint32_t*)0x40010810;
	GPIOA.BRR			=	(uint32_t*)0x40010814;
	GPIOA.LCKR		=	(uint32_t*)0x40010818;
}
void GPIOB_init(void){
	GPIOB.CRL			=	(uint32_t*)0x40010C00;
	GPIOB.CRH			=	(uint32_t*)0x40010C04;
	GPIOB.IDR			=	(uint32_t*)0x40010C08;
	GPIOB.ODR			=	(uint32_t*)0x40010C0C;
	GPIOB.BSRR		=	(uint32_t*)0x40010C10;
	GPIOB.BRR			=	(uint32_t*)0x40010C14;
	GPIOB.LCKR		=	(uint32_t*)0x40010C18;
}
void GPIOC_init(void){
	GPIOC.CRL			=	(uint32_t*)0x40011000;
	GPIOC.CRH			=	(uint32_t*)0x40011004;
	GPIOC.IDR			=	(uint32_t*)0x40011008;
	GPIOC.ODR			=	(uint32_t*)0x4001100C;
	GPIOC.BSRR		=	(uint32_t*)0x40011010;
	GPIOC.BRR			=	(uint32_t*)0x40011014;
	GPIOC.LCKR		=	(uint32_t*)0x40011018;
}
void GPIOD_init(void){
	GPIOD.CRL			=	(uint32_t*)0x40011400;
	GPIOD.CRH			=	(uint32_t*)0x40011404;
	GPIOD.IDR			=	(uint32_t*)0x40011408;
	GPIOD.ODR			=	(uint32_t*)0x4001140C;
	GPIOD.BSRR		=	(uint32_t*)0x40011410;
	GPIOD.BRR			=	(uint32_t*)0x40011414;
	GPIOD.LCKR		=	(uint32_t*)0x40011418;
}
void GPIOE_init(void){
	GPIOE.CRL			=	(uint32_t*)0x40011800;
	GPIOE.CRH			=	(uint32_t*)0x40011804;
	GPIOE.IDR			=	(uint32_t*)0x40011808;
	GPIOE.ODR			=	(uint32_t*)0x4001180C;
	GPIOE.BSRR		=	(uint32_t*)0x40011810;
	GPIOE.BRR			=	(uint32_t*)0x40011814;
	GPIOE.LCKR		=	(uint32_t*)0x40011818;
}
void GPIO_register_init(void){
	GPIOA_init();
	GPIOB_init();
	GPIOC_init();
	GPIOD_init();
	GPIOE_init();
}

void AFIO_init(void){
	AFIO.EVCR			=	(uint32_t*)0x40010000;
	AFIO.MAPR			=	(uint32_t*)0x40010004;
	AFIO.EXTICR[0]=	(uint32_t*)0x40010008;
	AFIO.EXTICR[1]=	(uint32_t*)0x4001000C;
	AFIO.EXTICR[2]=	(uint32_t*)0x40010010;
	AFIO.EXTICR[3]=	(uint32_t*)0x40010014;
	AFIO.MAPR2		=	(uint32_t*)0x40010018;
}

void EXTI_init(void){
	EXTI.IMR			=	(uint32_t*)0x40010400;
	EXTI.EMR			=	(uint32_t*)0x40010404;
	EXTI.RTSR			=	(uint32_t*)0x40010408;
	EXTI.FTSR			=	(uint32_t*)0x4001040C;
	EXTI.SWIER		=	(uint32_t*)0x40010410;
	EXTI.PR				=	(uint32_t*)0x40010414;
}
#ifdef	__STM32F10X_USART__
void USART1_init(void){
	USART1.SR				=	(uint32_t*)0x40013800;
	USART1.DR				=	(uint32_t*)0x40013804;
	USART1.BRR			=	(uint32_t*)0x40013808;
	USART1.CR1			=	(uint32_t*)0x4001380C;
	USART1.CR2			=	(uint32_t*)0x40013810;
	USART1.CR3			=	(uint32_t*)0x40013814;
	USART1.GTPR			=	(uint32_t*)0x40013818;
}

void USART2_init(void){
	USART2.SR				=	(uint32_t*)0x40004400;
	USART2.DR				=	(uint32_t*)0x40004404;
	USART2.BRR			=	(uint32_t*)0x40004408;
	USART2.CR1			=	(uint32_t*)0x4000440C;
	USART2.CR2			=	(uint32_t*)0x40004410;
	USART2.CR3			=	(uint32_t*)0x40004414;
	USART2.GTPR			=	(uint32_t*)0x40004418;
}

void USART3_init(void){
	USART3.SR				=	(uint32_t*)0x40004800;
	USART3.DR				=	(uint32_t*)0x40004804;
	USART3.BRR			=	(uint32_t*)0x40004808;
	USART3.CR1			=	(uint32_t*)0x4000480C;
	USART3.CR2			=	(uint32_t*)0x40004810;
	USART3.CR3			=	(uint32_t*)0x40004814;
	USART3.GTPR			=	(uint32_t*)0x40004818;
}

void UART4_init(void){
	UART4.SR				=	(uint32_t*)0x40004C00;
	UART4.DR				=	(uint32_t*)0x40004C04;
	UART4.BRR				=	(uint32_t*)0x40004C08;
	UART4.CR1				=	(uint32_t*)0x40004C0C;
	UART4.CR2				=	(uint32_t*)0x40004C10;
	UART4.CR3				=	(uint32_t*)0x40004C14;
	UART4.GTPR			=	(uint32_t*)0x40004C18;
}

void UART5_init(void){
	UART5.SR				=	(uint32_t*)0x40005000;
	UART5.DR				=	(uint32_t*)0x40005004;
	UART5.BRR				=	(uint32_t*)0x40005008;
	UART5.CR1				=	(uint32_t*)0x4000500C;
	UART5.CR2				=	(uint32_t*)0x40005010;
	UART5.CR3				=	(uint32_t*)0x40005014;
	UART5.GTPR			=	(uint32_t*)0x40005018;
}

void USART_register_init(void){
	USART1_init();
	USART2_init();
	USART3_init();
	UART4_init();
	UART5_init();
}
#endif

void NVIC_init(void){
	uint32_t address_0 = 0xE000E100;
	uint32_t address_1 = 0xE000E180;
	uint32_t address_2 = 0xE000E200;
	uint32_t address_3 = 0xE000E280;
	uint32_t address_4 = 0xE000E300;
	uint32_t address_5 = 0xE000E400;
	uint32_t address_6 = 0xE000EF00;
	
	uint8_t i = 0;
	for(i = 0; i < 8; i++){
		NVIC.ISER[i]	=	(uint32_t*)(address_0 + 4 * i);
		NVIC.ICER[i]	=	(uint32_t*)(address_1 + 4 * i);
		NVIC.ISPR[i]	=	(uint32_t*)(address_2 + 4 * i);
		NVIC.ICPR[i]	=	(uint32_t*)(address_3 + 4 * i);
		NVIC.IABR[i]	=	(uint32_t*)(address_4 + 4 * i);
	}
	
	for(i = 0; i < 240; i++)
		NVIC.IPR[i]		=	(uint8_t*)(address_5 + i);
	
	NVIC.STIR				=	(uint32_t*)address_6;

}

void SYST_init(void){
	STK.CTRL			=	(uint32_t*)0xE000E010;
	STK.LOAD			=	(uint32_t*)0xE000E014;
	STK.VAL				=	(uint32_t*)0xE000E018;
	STK.CALIB			=	(uint32_t*)0xE000E01C;
}

void SCB_init(void){
	SCB.ACTLR			=	(uint32_t*)0xE000E008;
	SCB.CPUID			=	(uint32_t*)0xE000E00C;
	SCB.ICSR			=	(uint32_t*)0xE000E010;
	SCB.VTOR			=	(uint32_t*)0xE000E014;
	SCB.AIRCR			=	(uint32_t*)0xE000E018;
	SCB.SCR				=	(uint32_t*)0xE000E01C;
	SCB.CCR				=	(uint32_t*)0xE000E020;
	SCB.SHPR[0]		=	(uint32_t*)0xE000E024;
	SCB.SHPR[1]		=	(uint32_t*)0xE000E028;
	SCB.SHPR[2]		=	(uint32_t*)0xE000E02C;
	SCB.SHCRS			=	(uint32_t*)0xE000E030;
	SCB.CFSR			=	(uint32_t*)0xE000E034;
	SCB.MMSR			=	(uint32_t*)0xE000E038;
	SCB.BFSR			=	(uint32_t*)0xE000E03C;
	SCB.UFSR			=	(uint32_t*)0xE000E040;
	SCB.HFSR			=	(uint32_t*)0xE000E044;
	SCB.MMAR			=	(uint32_t*)0xE000E048;
	SCB.BFAR			=	(uint32_t*)0xE000E04C;
	SCB.MMAR			=	(uint32_t*)0xE000E050;
	
}

#ifdef	__STM32F10X_SPI__
void SPI1_init(void){
	SPI1.CR1			=	(uint32_t*)0x40013000;
	SPI1.CR2			=	(uint32_t*)0x40013004;
	SPI1.SR				=	(uint32_t*)0x40013008;
	SPI1.DR				=	(uint32_t*)0x4001300C;
	SPI1.CRCPR		=	(uint32_t*)0x40013010;
	SPI1.RXCRCR		=	(uint32_t*)0x40013014;
	SPI1.TXCRCR		=	(uint32_t*)0x40013018;
	SPI1.I2SCFGR	=	(uint32_t*)0x4001301C;
	SPI1.I2SPR		=	(uint32_t*)0x40013020;
}

void SPI2_init(void){
	SPI2.CR1			=	(uint32_t*)0x40003800;
	SPI2.CR2			=	(uint32_t*)0x40003804;
	SPI2.SR				=	(uint32_t*)0x40003808;
	SPI2.DR				=	(uint32_t*)0x4000380C;
	SPI2.CRCPR		=	(uint32_t*)0x40003810;
	SPI2.RXCRCR		=	(uint32_t*)0x40003814;
	SPI2.TXCRCR		=	(uint32_t*)0x40003818;
	SPI2.I2SCFGR	=	(uint32_t*)0x4000381C;
	SPI2.I2SPR		=	(uint32_t*)0x40003820;
}

void SPI3_init(void){
	SPI3.CR1			=	(uint32_t*)0x40003C00;
	SPI3.CR2			=	(uint32_t*)0x40003C04;
	SPI3.SR				=	(uint32_t*)0x40003C08;
	SPI3.DR				=	(uint32_t*)0x40003C0C;
	SPI3.CRCPR		=	(uint32_t*)0x40003C10;
	SPI3.RXCRCR		=	(uint32_t*)0x40003C14;
	SPI3.TXCRCR		=	(uint32_t*)0x40003C18;
	SPI3.I2SCFGR	=	(uint32_t*)0x40003C1C;
	SPI3.I2SPR		=	(uint32_t*)0x40003C20;
}

void SPI_register_init(void){
	SPI1_init();
	SPI2_init();
	SPI3_init();
}
#endif

#ifdef	USE_I2C
void I2C1_init(void){
	I2C1.CR1			=	(uint32_t*)0x40005400;
	I2C1.CR2			=	(uint32_t*)0x40005404;
	I2C1.OAR1			=	(uint32_t*)0x40005408;
	I2C1.OAR2			=	(uint32_t*)0x4000540C;
	I2C1.DR				=	(uint32_t*)0x40005410;
	I2C1.SR1			=	(uint32_t*)0x40005414;
	I2C1.SR2			=	(uint32_t*)0x40005418;
	I2C1.CCR			=	(uint32_t*)0x4000541C;
	I2C1.TRISE		=	(uint32_t*)0x40005420;
}

void I2C2_init(void){
	I2C2.CR1			=	(uint32_t*)0x40005800;
	I2C2.CR2			=	(uint32_t*)0x40005804;
	I2C2.OAR1			=	(uint32_t*)0x40005808;
	I2C2.OAR2			=	(uint32_t*)0x4000580C;
	I2C2.DR				=	(uint32_t*)0x40005810;
	I2C2.SR1			=	(uint32_t*)0x40005814;
	I2C2.SR2			=	(uint32_t*)0x40005818;
	I2C2.CCR			=	(uint32_t*)0x4000581C;
	I2C2.TRISE		=	(uint32_t*)0x40005820;
}

void I2C_register_init(void){
	I2C1_init();
	I2C2_init();
}
#endif

#ifdef	USE_TIM
void TIM1_init(void){	
	TIM1.CR1			=	(uint32_t*)0x40012C00;
	TIM1.CR2			=	(uint32_t*)0x40012C04;
	TIM1.SMCR			=	(uint32_t*)0x40012C08;
	TIM1.DIER			=	(uint32_t*)0x40012C0C;
	TIM1.SR				=	(uint32_t*)0x40012C10;
	TIM1.EGR			=	(uint32_t*)0x40012C14;
	TIM1.CCMR1		=	(uint32_t*)0x40012C18;
	TIM1.CCMR2		=	(uint32_t*)0x40012C1C;
	TIM1.CCER			=	(uint32_t*)0x40012C20;
	TIM1.CNT			=	(uint32_t*)0x40012C24;
	TIM1.PSC			=	(uint32_t*)0x40012C28;
	TIM1.ARR			=	(uint32_t*)0x40012C2C;
	TIM1.RCR			=	(uint32_t*)0x40012C30;
	TIM1.CCR1			=	(uint32_t*)0x40012C34;
	TIM1.CCR2			=	(uint32_t*)0x40012C38;
	TIM1.CCR3			=	(uint32_t*)0x40012C3C;
	TIM1.CCR4			=	(uint32_t*)0x40012C40;
	TIM1.BDTR			=	(uint32_t*)0x40012C44;
	TIM1.DCR			=	(uint32_t*)0x40012C48;
	TIM1.DMAR			=	(uint32_t*)0x40012C4C;
	
}

void TIM2_init(void){
	TIM2.CR1			=	(uint32_t*)0x40000000;
	TIM2.CR2			=	(uint32_t*)0x40000004;
	TIM2.SMCR			=	(uint32_t*)0x40000008;
	TIM2.DIER			=	(uint32_t*)0x4000000C;
	TIM2.SR				=	(uint32_t*)0x40000010;
	TIM2.EGR			=	(uint32_t*)0x40000014;
	TIM2.CCMR1		=	(uint32_t*)0x40000018;
	TIM2.CCMR2		=	(uint32_t*)0x4000001C;
	TIM2.CCER			=	(uint32_t*)0x40000020;
	TIM2.CNT			=	(uint32_t*)0x40000024;
	TIM2.PSC			=	(uint32_t*)0x40000028;
	TIM2.ARR			=	(uint32_t*)0x4000002C;
	TIM2.CCR1			=	(uint32_t*)0x40000030;
	TIM2.CCR2			=	(uint32_t*)0x40000034;
	TIM2.CCR3			=	(uint32_t*)0x40000038;
	TIM2.CCR4			=	(uint32_t*)0x4000003C;
	TIM2.DCR			=	(uint32_t*)0x40000040;
	TIM2.DMAR			=	(uint32_t*)0x40000044;
	
}

void TIM6_init(void){
	TIM6.CR1			= (uint32_t*)0x40001000;
	TIM6.CR2			= (uint32_t*)0x40001004;
	TIM6.DIER			= (uint32_t*)0x40001008;
	TIM6.SR				= (uint32_t*)0x4000100C;
	TIM6.EGR			= (uint32_t*)0x40001010;
	TIM6.CNT			= (uint32_t*)0x40001014;
	TIM6.PSC			= (uint32_t*)0x40001018;
	TIM6.ARR			=	(uint32_t*)0x4000101C;
}

void TIM_register_init(void){
	TIM1_init();
	TIM2_init();
	TIM6_init();
}
#endif

void peripheral_register_init(void){
	//khoi tao dia chi thanh ghi cho RCC va FLASH
	RCC_init();
	//Khoi tao dia chi thanh ghi cho AFIO
	AFIO_init();
	EXTI_init();
	GPIO_register_init();
	NVIC_init();
	SYST_init();
	SCB_init();
	
	
#ifdef	__STM32F10X_USART__
	USART_register_init();
#endif
#ifdef	__STM32F10X_SPI__
	SPI_register_init();
#endif
#ifdef	USE_I2C
	I2C_register_init();
#endif
#ifdef	USE_TIM
	TIM_register_init();
#endif
}
