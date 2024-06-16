#include "I2C.h"
#include "Delay.h"
#include "Acelerometro.h"
#include "math.h"
char x1, x2, y1, y2,z1, z2;
int16_t x, y,z;
double ang;
//Configuracion I2C para Acelerometro
char Aceleracion_write=0xA6;
char Aceleracion_read=0xA7;
char Grabedad=0x00;
char RegistroGrabedad[2]={0x31,0x00};
char RegistroOn1[2]={0x2D,0x08};
char RegistroOn2[2]={0x2C,0x07};
void IniciarAcelerometro(void){
	I2CWrite(0xA6,0x2d,0x00);
	Dalay(1000);
	I2CWrite(0xA6,0x031,0x0);
	Dalay(1000);
	I2CWrite(0xA6,0x2d,0x8);
	Dalay(1000);
}
void ReadAcelerometro (void){
	
		Dalay(1000);
		x1=I2CRead(0xA6,0x32);
		Dalay(1000);
		x2=I2CRead(0xA6,0x33);
		Dalay(1000);
		x =(short)((x2 << 8) | x1);

		///Y
		y1=I2CRead(0xA6,0x34);
		Dalay(1000);
		y2=I2CRead(0xA6,0x35);
		Dalay(1000);
		y =(short)((y2 << 8) + y1);
		///z
		z1=I2CRead(0xA6,0x36);
		Dalay(1000);
		z2=I2CRead(0xA6,0x37);
		Dalay(1000);
		z =(short)((z2 << 8) + z1);
		
		ang =(double) 180.0 * (atan2(y /256.5, x /256.0)) / 3.1415;
		if(ang < 0.0){ang+=360.0;}
		//Dalay(3000000);	
}