/*****************************Description ENC28J60****************************/
/*

*/
/*****************************Description ENC28J60****************************/
#define __ENC28J60_H__

#define	ADDR_MASK		0x1F
#define	BANK_MASK		0x60
#define	SPRD_MASK		0x80

/******************SPI operation code******************/
/*
						Description SPI operation code
					
					Instruction	name											Opcode						Argument										Data
		Read Control Register 	(RCR)								 0 0 0						a a a a a										N/A
		Read Buffer Memory 			(RBM)								 0 0 1						1 1 0 1 0										N/A
		Write Control Register	(WCR)								 0 1 0						a a a a a								d d d d d d d d
		Write Buffer Memory			(WBM)								 0 1 1						1 1 0 1 0								d d d d d d d d
		Bit Field Set						(BFS)								 1 0 0						a a a a a								d d d d d d d d
		Bit Field Clear					(BFC)								 1 0 1						a a a a a								d d d d d d d d
		System Reset Command		(SRC)								 1 1 1						1 1 1 1 1										N/A
		
		Legend:		a = control register address, d = data payload
*/

#define	ENC28J60_READ_CTRL_REG		0x00	//(RCR)
#define ENC28J60_READ_BUF_MEM			0x3A	//(RBM)
#define	ENC28J60_WRITE_CTRL_REG		0x40	//(WCR)
#define	ENC28J60_WRITE_BUF_MEM		0x7A	//(WBM)
#define	ENC28J60_BIT_FIELD_SET		0x80	//(BFS)
#define	ENC28J60_BIT_FIELD_CLR		0xA0	//(BFC)
#define	ENC28J60_SOFT_RESET				0xFF	//(SRC)
/******************SPI operation code******************/

/*********************Memory Oganization*********************/
/*
			Description about memory oganization
				- In ENC28J60 memory include 4 bank
				- Bank memory configuration (MAC, MII, PHY)
				- Control Register ( ECON2, ECON1, EIE, EIR )
				
*/
/*********************All-bank Register**********************/
#define	EIE			0x1B
#define	EIR			0x1C
#define	ESTAT		0x1D
#define	ECON2		0x1E
#define	ECON1		0x1F

/**********************Bank 0 Register***********************/
#define	ERDPT		(0x00 | 0x00)
#define	EWRPT		(0x02	|	0x00)
#define	ETXST		(0x04	|	0x00)
#define	ETXND		(0x06	|	0x00)
#define	ERXST		(0x08	|	0x00)
#define	ERXND		(0x0A	|	0x00)
#define	ERXRDPT	(0x0C	|	0x00)
#define	ERXWRPT	(0x0E	|	0x00)
#define	EDMAST	(0x10	|	0x00)
#define	EDMAND	(0x12	|	0x00)
#define	EDMADST	(0x14	|	0x00)
#define	EDMACS	(0x16	|	0x00)
/**********************Bank 1 Register***********************/
#define	EHT0		(0x00	|	0x20)
#define	EHT1		(0x01	|	0x20)
#define	EHT2		(0x02	|	0x20)
#define	EHT3		(0x03	|	0x20)
#define	EHT4		(0x04	|	0x20)
#define	EHT5		(0x05	|	0x20)
#define	EHT6		(0x06	|	0x20)
#define	EHT7		(0x07	|	0x20)
#define	EPMM0		(0x08	|	0x20)
#define	EPMM1		(0x09	|	0x20)
#define	EPMM2		(0x0A	|	0x20)
#define	EPMM3		(0x0B	|	0x20)
#define	EPMM4		(0x0C	|	0x20)
#define	EPMM5		(0x0D	|	0x20)
#define	EPMM6		(0x0E	|	0x20)
#define	EPMM7		(0x0F	|	0x20)
#define	EPMCS		(0x10	|	0x20)
#define	EPMO		(0x14	|	0x20)
#define	ERXFCON	(0x18	|	0x20)
#define	ERKTCNT	(0x19	|	0x20)
/**********************Bank 2 Register***********************/
#define	MACON1		(0x00	|	0x40	|	0x80)
#define	MACON3		(0x02	|	0x40	|	0x80)
#define	MACON4		(0x03	|	0x40	|	0x80)
#define	MABBIPG		(0x04	|	0x40	|	0x80)
#define	MAIPG			(0x06	|	0x40	|	0x80)
#define	MACLCON1	(0x08	|	0x40	|	0x80)
#define	MACLCON2	(0x09	|	0x40	|	0x80)
#define	MAMXFL		(0x0A	|	0x40	|	0x80)
#define	MICMD			(0x12	|	0x40	|	0x80)
#define	MIREGADR	(0x14	|	0x40	|	0x80)
#define	MIWR			(0x16	|	0x40	|	0x80)
#define	MIRD			(0x18	|	0x40	|	0x80)
/**********************Bank 3 Register***********************/
#define	MAADR5		(0x00	|	0x60	|	0x80)
#define	MAADR6		(0x01	|	0x60	|	0x80)
#define	MAADR3		(0x02	|	0x60	|	0x80)
#define	MAADR4		(0x03	|	0x60	|	0x80)
#define	MAADR1		(0x04	|	0x60	|	0x80)
#define	MAADR2		(0x05	|	0x60	|	0x80)
#define	EBSTSD		(0x06	|	0x60	|	0x80)
#define	EBSTCON		(0x07	|	0x60	|	0x80)
#define	EBSTCS		(0x08	|	0x60	|	0x80)
#define	MISTAT		(0x0A	|	0x60	|	0x80)
#define	EREVID		(0x12	|	0x60	|	0x80)
#define	ECOCON		(0x15	|	0x60	|	0x80)
#define	EFLOCON		(0x17	|	0x60	|	0x80)
#define	EPAUS			(0x18	|	0x60	|	0x80)
/*********************Memory Oganization*********************/

