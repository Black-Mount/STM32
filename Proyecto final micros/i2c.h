#include "stm32f4xx.h"  
#include "stdlib.h"


void I2C_init(void);
void I2C_writeByte(char saddr,char maddr,char data);
void I2C_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length);
