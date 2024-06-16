#include "GY-271.h"
#include "I2C.h"
#include "Delay.h"
char ValoresX [2];
char ValoresY [2];
char Valoresz [2];
int xx,yy,zz;
void IniciarGY271(void){
	I2CWrite(0x3C, 0x00, 0x08);
	Dalay(100000);
	I2CWrite(0x3C, 0x01, 0x20);
	Dalay(100000);
	I2CWrite(0x3C, 0x02, 0x00);
	Dalay(100000);
}
void ReadGY271 (void){
		ValoresX[0]=I2CRead(0x3C,0x03);
		Dalay(30000);
		
		ValoresX[1]=I2CRead(0x3C,0x04);
		Dalay(30000);
		
		ValoresY[0]=I2CRead(0x3C,0x05);
		Dalay(30000);
		
		ValoresY[1]=I2CRead(0x3C,0x06);
		Dalay(30000);
		
		Valoresz[0]=I2CRead(0x3C,0x07);
		Dalay(30000);
		
		Valoresz[1]=I2CRead(0x3C,0x08);
		Dalay(30000);
		
		xx=(short)(ValoresX[0]<<8) | ValoresX[1];
		yy=(short)(ValoresY[0]<<8) | ValoresY[1];
		zz=(short)(Valoresz[0]<<8) | Valoresz[1];
		
		//Dalay(3000000);	
}