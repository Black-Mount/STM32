#include "stm32f4xx.h"                  // Device header

char I2CRead(char address,char registry );
void I2CWriteOneBuff(char address, uint8_t registry);
void I2CWrite  (char address, char registry, char data);
void IniciarI2C(void);