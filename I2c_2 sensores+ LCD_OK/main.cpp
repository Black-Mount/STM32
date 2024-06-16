#include "stm32f4xx.h"                  // Device header
#include "LcdI2c.h"
#include "Delay.h"
#include "GY-271.h"
#include "I2C.h"
#include "stdio.h"
#include "Acelerometro.h"
char  bufferTex [16];
char  bufferTex1 [16];
void IniciarStmF4(void){
	RCC->AHB1ENR |=7;
}
int main(void){
	IniciarStmF4();
	IniciarI2C();
	IniciarAcelerometro();
	IniciarLCdConI2C();
  IniciarGY271();
	while(1){
		ReadAcelerometro();
		Dalay(1000);
		ReadGY271();
		Dalay(1000);
		sprintf(bufferTex,"%0.1f ANG       ",ang);
		sprintf(bufferTex1,"%dX %dy %dz    ",xx,yy,zz);
		EnviarString(bufferTex,0,0);
		Dalay(1000);
		EnviarString(bufferTex1,1,0);
		Dalay(1000);
	}
	return 0;
	}