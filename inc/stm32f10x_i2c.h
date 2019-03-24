#define __STM32F10X_I2C_H

typedef enum{
	I2Cx1,
	I2Cx2
}I2Cx;

typedef enum{
	I2C_MASTER,
	I2C_SLAVE
}I2C_MODE;


void I2C_configuration_master(void);
void I2C_configuration_slave(void);
void I2C_WriteData(unsigned char data);
unsigned char I2C_ReadData(void);
