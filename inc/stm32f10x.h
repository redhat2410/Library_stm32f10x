#define __STM32F10x_H
#include "define.h"

typedef unsigned char		uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long		uint64_t;

typedef signed char		s8;
typedef signed short	s16;
typedef signed int		s32;
typedef signed long		s64;

//define vector interrupt IRQn
typedef enum IRQn{
	SysTick_IRQn				=	-1,
	WWDG_IRQn						=	0,
	PVD_IRQn						=	1,
	TAMPER_IRQn					=	2,
	RTC_IRQn						=	3,
	FLASH_IRQn					=	4,
	RCC_IRQn						=	5,
	EXTI0_IRQn					=	6,
	EXTI1_IRQn					=	7,
	EXTI2_IRQn					=	8,
	EXTI3_IRQn					=	9,
	EXTI4_IRQn					=	10,
	DMA1_Channel1_IRQn	=	11,
	DMA1_Channel2_IRQn	=	12,
	DMA1_Channel3_IRQn	=	13,
	DMA1_Channel4_IRQn	=	14,
	DMA1_Channel5_IRQn	=	15,
	DMA1_Channel6_IRQn	=	16,
	DMA1_Channel7_IRQn	=	17,
	ADC1_2_IRQn					=	18,
	USB_HP_CAN_TX_IRQn	=	19,
	USB_LP_CAN_RX0_IRQn	=	20,
	CAN_RX1_IRQn				=	21,
	CAN_SCE_IRQn				=	22,
	EXTI9_5_IRQn				=	23,
	TIM1_BRK_IRQn				=	24,
	TIM1_UP_IRQn				=	25,
	TIM1_TRG_COM_IRQn		=	26,
	TIM1_CC_IRQn				=	27,
	TIM2_IRQn						=	28,
	TIM3_IRQn						=	29,
	TIM4_IRQn						=	30,
	I2C1_EV_IRQn				=	31,
	I2C1_ER_IRQn				=	32,
	I2C2_EV_IRQn				=	33,
	I2C2_ER_IRQn				=	34,
	SPI1_IRQn						=	35,
	SPI2_IRQn						=	36,
	USART1_IRQn					=	37,
	USART2_IRQn					=	38,
	USART3_IRQn					=	39,
	EXTI15_10_IRQn			=	40,
	RTCAlarm_IRQn				=	41,
	USBWakeup_IRQn			=	42,
	TIM8_BRK_IRQn				=	43,
	TIM8_UP_IRQn				=	44,
	TIM8_TRG_COM_IRQn		=	45,
	TIM8_CC_IRQn				=	46,
	ADC3_IRQn						=	47,
	FSMC_IRQn						=	48,
	SDIO_IRQn						=	49,
	TIM5_IRQn						=	50,
	SPI3_IRQn						=	51,
	UART4_IRQn					=	52,
	UART5_IRQn					=	53,
	TIM6_IRQn						=	54,
	TIM7_IRQn						=	55,
	DMA2_Channel1_IQRn	=	56,
	DMA2_Channel2_IRQn	=	57,
	DMA2_Channel3_IRQn	=	58,
	DMA2_Channel4_5_IRQn=	59
	
}IRQn_Typedef;

/*****************************************************************************/
/*Define function init*/
//define function system_stm32f10x.c
extern void SystemInit(void);
extern void peripheral_register_init(void);
/*****************************************************************************/

/*****************************************************************************/
/*												Define function interrupt													 */
/*****************************************************************************/
//define function interrupt IRQ
extern void EXTI15_10_IRQHandler(void);
extern void USART1_IRQHandler(void);
extern void USART2_IRQHandler(void);
extern void SPI1_IRQHandler(void);
extern void SysTick_Handler(void);

//define function stm32f10x_nvic.c
void NVIC_SetPriority(IRQn_Typedef IRQn, uint32_t priority);
void NVIC_SetPriority_SysTick(uint32_t priority);
//define function stm32f10x_systick.c
uint32_t Systick_Config(uint32_t SYSCLK);
void delay_ms(uint16_t ms);
void delay_us(uint32_t us);
/*****************************************************************************/

typedef struct{
	volatile uint32_t*	CR;
	volatile uint32_t*	CFGR;
	volatile uint32_t*	CIR;
	volatile uint32_t*	APB2RSTR;
	volatile uint32_t*	APB1RSTR;
	volatile uint32_t*	AHBENR;
	volatile uint32_t*	APB2ENR;
	volatile uint32_t*	APB1ENR;
	volatile uint32_t*	BDCR;
	volatile uint32_t*	CSR;
	volatile uint32_t*	AHBRSTR;
	volatile uint32_t*	CFGR2;
}RCC_Typedef;

typedef struct{
	volatile uint32_t*	ACR;
}FLASH_Typedef;

typedef struct{
	volatile uint32_t*	CRL;
	volatile uint32_t*	CRH;
	volatile uint32_t*	IDR;
	volatile uint32_t*	ODR;
	volatile uint32_t*	BSRR;
	volatile uint32_t*	BRR;
	volatile uint32_t*	LCKR;
}GPIO_Typedef;

typedef struct{
	volatile uint32_t*	EVCR;
	volatile uint32_t*	MAPR;
	volatile uint32_t*	EXTICR[4];
	volatile uint32_t*	MAPR2;
}AFIO_Typedef;

typedef struct{
	volatile uint32_t*	IMR;
	volatile uint32_t*	EMR;
	volatile uint32_t*	RTSR;
	volatile uint32_t*	FTSR;
	volatile uint32_t*	SWIER;
	volatile uint32_t*	PR;
}EXTI_Typedef;

typedef struct{
	volatile uint32_t*	ISER[8];
	volatile uint32_t*	ICER[8];
	volatile uint32_t*	ISPR[8];
	volatile uint32_t*	ICPR[8];
	volatile uint32_t*	IABR[8];
	volatile uint8_t*		IPR[240];
	volatile uint32_t*	STIR;
}NVIC_Typedef;

typedef struct{
	volatile uint32_t*	ACTLR;
	volatile uint32_t*	CPUID;
	volatile uint32_t*	ICSR;
	volatile uint32_t*	VTOR;
	volatile uint32_t*	AIRCR;
	volatile uint32_t*	SCR;
	volatile uint32_t*	CCR;
	volatile uint32_t*	SHPR[3];
	volatile uint32_t*	SHCRS;
	volatile uint32_t*	CFSR;
	volatile uint32_t*	MMSR;
	volatile uint32_t*	BFSR;
	volatile uint32_t*	UFSR;
	volatile uint32_t*	HFSR;
	volatile uint32_t*	MMAR;
	volatile uint32_t*	BFAR;
	volatile uint32_t*	AFSR;
}SCB_Typedef;

typedef struct{
	volatile uint32_t*	CTRL;
	volatile uint32_t*	LOAD;
	volatile uint32_t*	VAL;
	volatile uint32_t*	CALIB;
}STK_Typedef;


#ifdef __STM32F10X_USART__

typedef struct{
	volatile uint32_t*	SR;
	volatile uint32_t*	DR;
	volatile uint32_t*	BRR;
	volatile uint32_t*	CR1;
	volatile uint32_t*	CR2;
	volatile uint32_t*	CR3;
	volatile uint32_t*	GTPR;
}USART_Typedef;

#endif

#ifdef __STM32F10X_SPI__
typedef struct{
	volatile uint32_t*	CR1;
	volatile uint32_t*	CR2;
	volatile uint32_t*	SR;
	volatile uint32_t*	DR;
	volatile uint32_t*	CRCPR;
	volatile uint32_t*	RXCRCR;
	volatile uint32_t*	TXCRCR;
	volatile uint32_t*	I2SCFGR;
	volatile uint32_t*	I2SPR;
}SPI_Typedef;

#endif

#ifdef USE_I2C

typedef struct{
	volatile uint32_t*	CR1;
	volatile uint32_t*	CR2;
	volatile uint32_t*	OAR1;
	volatile uint32_t*	OAR2;
	volatile uint32_t*	DR;
	volatile uint32_t*	SR1;
	volatile uint32_t*	SR2;
	volatile uint32_t*	CCR;
	volatile uint32_t*	TRISE;
}I2C_Typedef;

#endif

#ifdef USE_TIM
//Typedef register for TIM1 - 8
typedef struct{
	volatile uint32_t*	CR1;
	volatile uint32_t*	CR2;
	volatile uint32_t*	SMCR;
	volatile uint32_t*	DIER;
	volatile uint32_t*	SR;
	volatile uint32_t*	EGR;
	volatile uint32_t*	CCMR1;
	volatile uint32_t*	CCMR2;
	volatile uint32_t*	CCER;
	volatile uint32_t*	CNT;
	volatile uint32_t*	PSC;
	volatile uint32_t*	ARR;
	volatile uint32_t*	RCR;
	volatile uint32_t*	CCR1;
	volatile uint32_t*	CCR2;
	volatile uint32_t*	CCR3;
	volatile uint32_t*	CCR4;
	volatile uint32_t*	BDTR;
	volatile uint32_t*	DCR;
	volatile uint32_t*	DMAR;
}TIM1_8_Typedef;

//Typedef register for TIM2 -> 5
typedef struct{
	volatile uint32_t*	CR1;
	volatile uint32_t*	CR2;
	volatile uint32_t*	SMCR;
	volatile uint32_t*	DIER;
	volatile uint32_t*	SR;
	volatile uint32_t*	EGR;
	volatile uint32_t*	CCMR1;
	volatile uint32_t*	CCMR2;
	volatile uint32_t*	CCER;
	volatile uint32_t*	CNT;
	volatile uint32_t*	PSC;
	volatile uint32_t*	ARR;
	volatile uint32_t*	CCR1;
	volatile uint32_t*	CCR2;
	volatile uint32_t*	CCR3;
	volatile uint32_t*	CCR4;
	volatile uint32_t*	DCR;
	volatile uint32_t*	DMAR;
}TIM2_5_Typedef;

//Typedef register for TIM9 and 12
typedef struct{
	volatile uint32_t*	CR1;
	volatile uint32_t*	SMCR;
	volatile uint32_t*	DIER;
	volatile uint32_t*	SR;
	volatile uint32_t*	EGR;
	volatile uint32_t*	CCMR1;
	volatile uint32_t*	CCER;
	volatile uint32_t*	CNT;
	volatile uint32_t*	PSC;
	volatile uint32_t*	APR;
	volatile uint32_t*	CCR1;
	volatile uint32_t*	CCR2;
}TIM9_12_Typedef;

//Typedef register for basic timer TIM6 and TIM7
typedef struct{
	volatile uint32_t*	CR1;
	volatile uint32_t*	CR2;
	volatile uint32_t*	DIER;
	volatile uint32_t*	SR;
	volatile uint32_t*	EGR;
	volatile uint32_t*	CNT;
	volatile uint32_t*	PSC;
	volatile uint32_t*	ARR;
}TIM6_7_Typedef;
#endif

extern RCC_Typedef		RCC;
extern FLASH_Typedef	FLASH;
extern GPIO_Typedef		GPIOA;
extern GPIO_Typedef		GPIOB;
extern GPIO_Typedef		GPIOC;
extern GPIO_Typedef		GPIOD;
extern GPIO_Typedef		GPIOE;
extern NVIC_Typedef		NVIC;
extern SCB_Typedef		SCB;
extern AFIO_Typedef		AFIO;
extern EXTI_Typedef		EXTI;
extern STK_Typedef		STK;

#ifdef __STM32F10X_USART__
extern USART_Typedef	USART1;
extern USART_Typedef	USART2;
extern USART_Typedef	USART3;
extern USART_Typedef	UART4;
extern USART_Typedef	UART5;
#endif

#ifdef __STM32F10X_SPI__
extern SPI_Typedef		SPI1;
extern SPI_Typedef		SPI2;
extern SPI_Typedef		SPI3;
#endif

#ifdef USE_I2C
extern I2C_Typedef		I2C1;
extern I2C_Typedef		I2C2;
#endif

#ifdef USE_TIM
extern TIM1_8_Typedef	TIM1;
extern TIM2_5_Typedef	TIM2;
extern TIM6_7_Typedef	TIM6;
extern TIM6_7_Typedef TIM7;
#endif

