#include "stm32f401xe.h"
#include <math.h>
#include <stdio.h>

int matriz[]={0x1EFF,0X1DFF,0X1BFF,0X17FF,0X0FFF};
int hexadecimal[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71};
void delay(void) {
	for(int x=0; x<300000;x++){asm("nop");}//180000-1800
}	
/*int teclado[4][5]={
	{1,2,3,15,16},		//S123+S	{1,2,3,13,18},	
	{4,5,6,14,17},		//456-C		{4,5,6,12,17},
	{7,8,9,13,18},		//789*T		{7,8,9,14,16},
	{10,0,11,12,10}		//L0=/L		{10,0,11,15,10}
}; */ //matriz para teclado 5*4 

int teclado[4][5]={
	{16,1,4,7,10},		//S123+S	{1,2,3,13,18},	
	{17,2,5,8,0},		//456-C		{4,5,6,12,17},
	{18,3,6,9,11},		//789*T		{7,8,9,14,16},
	{10,15,14,13,12}		//L0=/L		{10,0,11,15,10}
};
int c=0,d=0,u=0,m1=0,m2=0,p1=0,p2=0,fila,columna,tecla=0;
float num=0,op=1,error=0;

void actualizar(int operacion, float valor){
	for(int x=0;x<160000;x++){asm("nop");}
	switch(operacion){
		case 0:
			num=num;
		break;
		case 1:
			num=num+valor;
		break;
		case 2:
			num=num-valor;
		break;
		case 3:
			num=num*valor;
		break;
		case 4:
			if(valor == 0){error=1;}else{
			num=num / valor;}
		break;
		case 5:
		num = sin(valor);
		break;
		case 6:
		num = cos(valor);
		break;
		case 7:
			if(valor==90){error=1;
			}else{
		num = tan(valor);}
			break;
	}
}
void analisis(void){
	switch(teclado[fila][columna]){
		case 10://borrar todo
			actualizar(3,0);
			op=0;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 11://igual
			actualizar(op,(u+(d*10)+(c*100)));
			op=0;
		if(error==1){
			u=14;d=14;c=14;m1=14;m2=14;p1=14;p2=14;
		}else{
			if(num>=0){
			c=num/100;
			d=(num-100*c)/10;
			u=num-(100*c)-(10*d);
			m1=(num-(100*c)-(10*d)-u)*10;
			m2=(num*100-(100*c*100)-(100*d*10)-u*100-10*m1);
			}else{
			c=-num/100;
			d=(-num-100*c)/10;
			u=-num-(100*c)-(10*d);
			m1=(-num-(100*c)-(10*d)-u)*10;
			m2=15;
			}
		}
		break;
		case 12://division
			actualizar(op,(u+(d*10)+(c*100)));
			op=4;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 13://multiplicacion
			actualizar(op,(u+(d*10)+(c*100)));
			op=3;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 14://resta
			actualizar(op,(u+(d*10)+(c*100)));
			op=2;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 15://suma
			actualizar(op,(u+(d*10)+(c*100)));
			op=1;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 16://sin
			actualizar(op,(u+(d*10)+(c*100)));
			op=5;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 17://cos
			actualizar(op,(u+(d*10)+(c*100)));
			op=6;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 18://tan
			actualizar(op,(u+(d*10)+(c*100)));
			op=7;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		case 19:
			actualizar(3,0);
			op=1;
			u=0;d=0;c=0;m1=0;m2=0;p1=0;p2=0;
		break;
		default:
		if(p1==0){u=teclado[fila][columna];p1++;}else{
		d=teclado[fila][columna];
		}
		break;
		
	}
}


void imprimir(int a, int b, int c, int d, int e) {
	
	GPIOC->ODR=hexadecimal[a];
	GPIOC->ODR|=0X1E00;//0001 1110 0000 0000
	delay();
	GPIOC->ODR=hexadecimal[b];
	GPIOC->ODR|=0X1D00;//0001 1101 0000 0000
	delay();
	GPIOC->ODR=hexadecimal[c];
	GPIOC->ODR|=0X1B00;//0001 1011 0000 0000
	GPIOC->ODR|=(1UL<<7);
	delay();
	GPIOC->ODR=hexadecimal[d];
	GPIOC->ODR|=0X1700;//0001 0111 0000 0000
	delay();
	GPIOC->ODR=hexadecimal[e];
	GPIOC->ODR|=0X0F00;//0000 1111 0000 0000
	delay();
	delay();
}

extern "C" {
	void EXTI4_IRQHandler(void){
	EXTI->PR|=0xFFFF;fila=0;
		analisis();
	}
	
	void EXTI9_5_IRQHandler(void){
		if(!(GPIOA->IDR & (1UL<<5))) {
			EXTI->PR|=0xFFFF;fila=1;}
		if(!(GPIOA->IDR & (1UL<<6))) {
			EXTI->PR|=0xFFFF;fila=2;}
		if(!(GPIOA->IDR & (1UL<<7))) {
			EXTI->PR|=0xFFFF;fila=3;}
		analisis();}
}

void configura(void) {

	RCC->AHB1ENR=0X7;
	RCC->APB2ENR|=(1UL<<14);
	GPIOA->MODER=0X1550000;
	GPIOC->MODER=0X1555555;
	GPIOA->PUPDR=0X1555500;//0001 0101 0101 0101 0101 0000 0000
	
	EXTI->FTSR|=0xF0;
	
	EXTI->IMR|=0xF0;
	SYSCFG->EXTICR[1]=0x0000;
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	
}



void control(void) {
	
	for(int i=0; i<5; i++) {
	GPIOA->ODR=matriz[i];
	columna=i;delay();}
	imprimir(c,d,u,m1,m2);
}


int main(void) {
	configura();
	while (1) {
	control();
	}
}