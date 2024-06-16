#include "LCD.h"

void LCD::Config(void){
	GPIOB->MODER=0X55555555;
	Set(0x06);//Configurar LCD-> Activar Cursor A la Derecha
	Set(0x38);//Setea Disp - [8 Bits, Dos lineas, Matriz:5x8]
	Set(0xC);//Prender Disp- Enable 1
}

void LCD::Set(char x){
	GPIOX=x|(1UL<<9);//Mode Set=1
	delayLCD;//Delay
	GPIOX&=~(1UL<<9);//Enable 0
}

void LCD::WriteLetter(char x){
	GPIOX=x|(3<<8);//FS RS 1, Enable 1
	delayLCD;
	GPIOX&=~(1UL<<9);//Enable 0
}

void LCD::WriteWord(char x[],int start,int end){
	for(int i=start;i<end;i++){
		GPIOX=x[i]|(3<<8);//FS RS 1, Enable 1
		delayLCD;
		GPIOX&=~(1UL<<9);//Enable 0
	}
}

void LCD::SetSpecialChart(char x[]){
	Set(CGram);//Comando CGRAM
	WriteWord(x,0,8);//Guardar Cada Caracter
	CGram+=8;
}

void LCD::SaveSpecialCharts(){
	char A[8]={0X0,0X1F,0X4,0X4,0X4,0X4,0X4,0X4};
	char B[8]={0X0,0X11,0X11,0X11,0X11,0X11,0X11,0X11};
	char C[8]={0X0,0X1F,0X11,0X11,0X11,0X11,0X11,0X11};
	char D[8]={0X0,0X11,0X19,0X15,0X13,0X11,0X11,0X11};
	char E[8]={0X4,0X4,0X4,0X4,0X14,0X14,0X1C,0X0};
	char F[8]={0X11,0X11,0X11,0X11,0X11,0X11,0X1F,0};
	char G[8]={0X1F,0X11,0X11,0X11,0X11,0X11,0X11,0X0};
	char H[8]={0X11,0X11,0X11,0X11,0X11,0X11,0X11,0};
	
	SetSpecialChart(A);
	SetSpecialChart(B);
	SetSpecialChart(C);
	SetSpecialChart(D);
	SetSpecialChart(E);
	SetSpecialChart(F);
	SetSpecialChart(G);
	SetSpecialChart(H);
	
}
void LCD::Clear(){
	Set(0x01);
}