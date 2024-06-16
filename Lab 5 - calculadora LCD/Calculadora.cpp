#include "stm32f401xe.h"
#include <math.h>
#include <stdio.h>

int matriz[]={0x1EFF,0X1DFF,0X1BFF,0X17FF,0X0FFF};
void delay(void) {
	for(int x=0; x<180000;x++){asm("nop");}//180000-1800
}	
int teclado[4][5]={
	{10,1,4,7,19},		//123+S	{1,2,3,13,18},	
	{17,2,5,8,0},		//456-C		{4,5,6,12,17},
	{18,3,6,9,11},		//789*T		{7,8,9,14,16},
	{16,15,14,13,12}		//L0=/L		{10,0,11,15,10}
};
int mil=0,c1=0,d1=0,u1=0,m1=0,m2=0,p1=0,p2=0,fila,columna,pos=0,posnum=0, posope=0,correr=0,mp=0, grafica=0, caracter=0;
int d=0,u=0,reboot=0;
float num=0,op=1,error=0;
int registro[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float valor[10]={0,0,0,0,0,0,0,0,0,0};
int operacion[10]={0,0,0,0,0,0,0,0,0,0};
void clasificar(){
	for(int x=0;x<pos;x++){
		if(registro[x]<10){
			if(correr==0){
				u=registro[x];
				correr++;
			}else{
				d=u;
				u=registro[x];
			}
		}else{
			valor[posnum]=(u+10*d);
			operacion[posope]=registro[x];
			u=0;
			d=0;
			posope++;
			posnum++;
			correr=0;
		}
	}
	valor[posnum]=(u+10*d);
		u=0;
		d=0;
		posope=0;
		posnum=0;
		correr=0;
}
void operar(){
	//operar a lo mal hecho xd
	for(int x=0;x<10;x++){
		if(operacion[x]==0){
			x=20;
		}else{
		switch(operacion[x]){
		case 12://division
			valor[0]=valor[0]/valor[x+1];
			if(valor[x+1]==0){
				error=1;
			}
		break;
		case 13://multiplicacion
			valor[0]=valor[0]*valor[x+1];
		break;
		case 14://resta
			valor[0]=valor[0]-valor[x+1];
		break;
		case 15://suma
			valor[0]=valor[0]+valor[x+1];
		break;
		case 16://sin
			valor[0]=sin(valor[0]*3.1416/180);
//			x=20;
		break;
		case 17://cos
			valor[0]=cos(valor[0]*3.1416/180);
//			x=20;
		break;
		case 18://tan
			valor[0]=tan(valor[0]*3.1416/180);
			if(valor[0]==90){
				error=1;
			}
		break;
		case 19: 
			if( 0<=valor[0] && valor[0]<=18) {
				caracter=0;
			}
			if( 19<=valor[0] && valor[0]<=36) {
				caracter=1;
			}
			if( 37<=valor[0] && valor[0]<=54) {
				caracter=2;
			}
			if( 55<=valor[0] && valor[0]<=72) {
				caracter=3;
			}
			if( 73<=valor[0] && valor[0]<=99) {
				caracter=4;
			}
			x=20;
		break;
		}
	}}}

void Delay(int x){
	for(volatile int i=0;i<x*700; i++){asm("nop");}}
void confi_LCD(int n1, int n2){
	  Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= n1;
	  Delay(10);
	  GPIOC -> ODR &= ~(1UL<<5); //RS = 0
	  GPIOC -> ODR |=(1UL<<4);   //E = 1
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
	
		Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= n2;
	  Delay(10);
	  GPIOC -> ODR &= ~(1UL<<5); //RS = 0
	  GPIOC -> ODR |=(1UL<<4);   //E = 1
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
}
	
void write_LCD(int n1, int n2){
		Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= n1;
	  Delay(10);
	  GPIOC -> ODR |= (1UL<<5); //RS = 1
	  GPIOC -> ODR |=(1UL<<4);   //E = 1
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
	
		Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= n2;
	  Delay(10);
	  GPIOC -> ODR |= (1UL<<5); //RS = 1
	  GPIOC -> ODR |=(1UL<<4);   //E = 1
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
}

void desp_pant(){
		Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= 0; 
		GPIOC -> ODR |= (1<<4);
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
	
		Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= 7; 
		GPIOC -> ODR |= (1<<4);
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
}

void clear_screen(){
		 Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= 0;
	  Delay(10);
	  GPIOC -> ODR &= ~(1UL<<5); //RS = 0
	  GPIOC -> ODR |=(1UL<<4);   //E = 1
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
	
		Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= 1;
	  Delay(10);
	  GPIOC -> ODR &= ~(1UL<<5); //RS = 0
	  GPIOC -> ODR |=(1UL<<4);   //E = 1
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
}



void camb_pos(int sa, int sb){
	Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= 8+sa; 
		GPIOC -> ODR |= (1<<4);
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
	
		Delay(50);		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
		GPIOC -> ODR |= sb; 
		GPIOC -> ODR |= (1<<4);
		Delay(10);
	  GPIOC -> ODR &=~(1UL<<4);  //Enable 0
}
void create_draw(void){		
  	GPIOC -> ODR &=(1UL<<4);
	  GPIOC -> ODR &=(1UL<<5);
	  confi_LCD(4,0);
	
		//Seno original arriba
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x6);
		write_LCD(0x0,0x9);
	  write_LCD(0x1,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  
		//Seno original abajo
	
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x1,0x0);
	  write_LCD(0x0,0x9);
	  write_LCD(0x0,0x6);
	  write_LCD(0x0,0x0);
		///////////////////////////////
		
			//Desfase 1 arriba
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0xC);
		write_LCD(0x1,0x2);
	  write_LCD(0x0,0x1);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  
		//Desfase 1 abajo
	
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x1);
	  write_LCD(0x1,0x2);
	  write_LCD(0x0,0xC);
	  write_LCD(0x0,0x0);
		
		//////////////////////////
		
		//Desfase 2 arriba
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x1,0x8);
		write_LCD(0x0,0x4);
	  write_LCD(0x0,0x2);
	  write_LCD(0x0,0x1);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  
		//Desfase 2 abajo
	
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x1);
	  write_LCD(0x0,0x2);
	  write_LCD(0x0,0x4);
	  write_LCD(0x1,0x8);
	  write_LCD(0x0,0x0);
		
		/////////////////////////////////////////
		
		//Desfase 3 arriba
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x1,0x0);
		write_LCD(0x0,0x8);
	  write_LCD(0x0,0x4);
	  write_LCD(0x0,0x3);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
	  
		//Desfase 3 abajo
	
		write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
		write_LCD(0x0,0x3);
	  write_LCD(0x0,0x4);
	  write_LCD(0x0,0x8);
	  write_LCD(0x1,0x0);
	  write_LCD(0x0,0x0);
	  write_LCD(0x0,0x0);
}
void mostrar(){
	clear_screen();
	camb_pos(0,0);
	for(int x=0;x<pos;x++){		
		switch(registro[x]){
		case 10://borrar todo
			for(int x=0;x<16;x++){
				registro[x]=0;
				pos=0;
				error=0;
				grafica=0;
			}
			clear_screen();
		break;
		case 11://igual
			clear_screen();//limpiar
			camb_pos(0,0);//ubica posicion al inicio
			clasificar();
			operar();
		
		
		if(grafica>0){
			
			camb_pos(0,0);
			
				for(int x=0; x<=9; x++) {
			write_LCD(0,0);
			write_LCD(0,1);
				}
				
				camb_pos(4,0);
	
				if (caracter==4) {
					for(int x=0; x<=9; x++) {
			write_LCD(0,1); ///Para la parte de arriba es 0,2,4,6,1
			write_LCD(0,0); ///Para la parte de abajo  es 1,3,5,7,0
			}		
				}
				else {
	for(int x=0; x<=9; x++) {
			write_LCD(0,0+caracter*2); ///Para la parte de arriba es 0,2,4,6,1
			write_LCD(0,1+caracter*2); ///Para la parte de abajo  es 1,3,5,7,0
			}		
				}
	
			
			}
		
		else {
			
		if(error==0){
		if(valor[0]>=0){
			write_LCD(3,13);//pone el igual
			mil=valor[0]/1000;
			c1=(valor[0]-1000*mil)/100;
			d1=(valor[0]-1000*mil-100*c1)/10;
			u1=valor[0]-1000*mil-(100*c1)-(10*d1);
			m1=(valor[0]-(100*c1)-(10*d1)-u1)*10;
			m2=(valor[0]*100-(1000*mil*100)-(100*c1*100)-(100*d1*10)-u1*100-10*m1);
		}
		else{
			write_LCD(3,13);//pone el igual
			write_LCD(2,13);
			mil=-valor[0]/1000;
			c1=(-valor[0]-1000*mil)/100;
			d1=(-valor[0]-1000*mil-100*c1)/10;
			u1=-valor[0]-1000*mil-(100*c1)-(10*d1);
			m1=(-valor[0]-(100*c1)-(10*d1)-u1)*10;
			m2=(-valor[0]*100-(1000*mil*100)-(100*c1*100)-(100*d1*10)-u1*100-10*m1);
		}}else{
			mil=15;c1=15;d1=15;u1=15;m1=15;m2=15;
		}
			write_LCD(3,mil);
			write_LCD(3,c1);
			write_LCD(3,d1);
			write_LCD(3,u1);
			write_LCD(2,14);
			write_LCD(3,m1);
			write_LCD(3,m2);
	}
		
		Delay(1000);
			
		break;
		case 12://division
			write_LCD(2,15);
			
		break;
		case 13://multiplicacion
			write_LCD(2,10);
			
		break;
		case 14://resta
			write_LCD(2,13);
			
		break;
		case 15://suma
			write_LCD(2,11);
			
		break;
		case 16://sin
			write_LCD(5,3);
			
		break;
		case 17://cos
			write_LCD(4,3);
			
		break;
		case 18://tan
			write_LCD(5,4);
			
		break;
		case 19://caracteres especiales
		
    	write_LCD(0,0);
			write_LCD(0,1);
		  grafica++;
		
//	
//		
//		
		break;
		default:
		write_LCD(3,registro[x]);
	}
}
}
extern "C" {
	void EXTI0_IRQHandler(void){
		while(!(GPIOA->IDR & (1UL<<0))) {
			if(!(GPIOA->IDR & (1UL<<0))) {
			mp++;delay();delay();delay();}
		}
		if(grafica>0){
			caracter++;
			if(caracter>4) {
				caracter=0;
			}
			camb_pos(0,0);
			
				for(int x=0; x<=9; x++) {
			write_LCD(0,0);
			write_LCD(0,1);
				}
				
				camb_pos(4,0);
	
				if (caracter==4) {
					for(int x=0; x<=9; x++) {
			write_LCD(0,1); ///Para la parte de arriba es 0,2,4,6,1
			write_LCD(0,0); ///Para la parte de abajo  es 1,3,5,7,0
			}		
				}
				else {
	for(int x=0; x<=9; x++) {
			write_LCD(0,0+caracter*2); ///Para la parte de arriba es 0,2,4,6,1
			write_LCD(0,1+caracter*2); ///Para la parte de abajo  es 1,3,5,7,0
			}		
				}
	
			
			}
		camb_pos(0,pos-mp);
		EXTI->PR|=0xFFFF;
		}
	void EXTI1_IRQHandler(void){
		while(!(GPIOA->IDR & (1UL<<1))) {
			if(!(GPIOA->IDR & (1UL<<1))) {
			mp--;delay();delay();delay();}
		}
		if(grafica>0){
			caracter--;
			if(caracter<0) {
				caracter=4;
			}
			camb_pos(0,0);
			
				for(int x=0; x<=9; x++) {
			write_LCD(0,0);
			write_LCD(0,1);
				}
				
				camb_pos(4,0);
	
				if (caracter==4) {
					for(int x=0; x<=9; x++) {
			write_LCD(0,1); ///Para la parte de arriba es 0,2,4,6,1
			write_LCD(0,0); ///Para la parte de abajo  es 1,3,5,7,0
			}		
				}
				else {
	for(int x=0; x<=9; x++) {
			write_LCD(0,0+caracter*2); ///Para la parte de arriba es 0,2,4,6,1
			write_LCD(0,1+caracter*2); ///Para la parte de abajo  es 1,3,5,7,0
			}		
				}
	
			
			}
		camb_pos(0,pos-mp);
		EXTI->PR|=0xFFFF;
	}
	
	void EXTI4_IRQHandler(void){
		while(!(GPIOA->IDR & (1UL<<4))) {
			if(!(GPIOA->IDR & (1UL<<4))) {
			fila=0;delay();delay();delay();}
		}
		if(mp!=0){
		registro[pos-mp]=teclado[fila][columna];
		mp=0;
		}else{
		registro[pos]=teclado[fila][columna];pos++;
		}
		EXTI->PR|=0xFFFF;
		mostrar();
	}
	
	void EXTI9_5_IRQHandler(void){
		while((!(GPIOA->IDR & (1UL<<5)))||(!(GPIOA->IDR & (1UL<<6)))||(!(GPIOA->IDR & (1UL<<7)))){
		if(!(GPIOA->IDR & (1UL<<5))) {
			fila=1;delay();delay();delay();}
		if(!(GPIOA->IDR & (1UL<<6))) {
			fila=2;delay();delay();delay();}
		if(!(GPIOA->IDR & (1UL<<7))) {
			fila=3;delay();delay();delay();}
		}
		if(mp!=0){
		registro[pos-mp]=teclado[fila][columna];
		mp=0;
		}else{
		registro[pos]=teclado[fila][columna];pos++;
		}
		EXTI->PR|=0xFFFF;
		mostrar();
	}
}

void configura(void) {

	RCC->AHB1ENR=0X7;
	RCC->APB2ENR|=(1UL<<14);
	GPIOA->MODER|=0X1550000;
	GPIOA->PUPDR=0X1555505;//0001 0101 0101 0101 0101 0000 0000
	GPIOC -> MODER |= 0X5555555;
	//CONFIGURACION LCD
	confi_LCD(0,1); //Clear LCD
	confi_LCD(3,8);//8 bits
	Delay(10);
	confi_LCD(3,2);
	confi_LCD(0,14);
	confi_LCD(0,6);
	confi_LCD(0,1); //Clear LCD
	confi_LCD(2,8); // 2 y 8 para dos lineas
  confi_LCD(8,0);
	//configuracion interrupciones del teclado	
	EXTI->FTSR|=0xF3;
	EXTI->IMR|=0xF3;
	SYSCFG->EXTICR[0]=0x0000;
	SYSCFG->EXTICR[1]=0x0000;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	create_draw();
	camb_pos(0,0);
	write_LCD(14,15);
	Delay(1000);
	clear_screen();//limpiar
}



void control(void) {
	for(int i=0; i<5; i++) {
	GPIOA->ODR=matriz[i];
	columna=i;delay();}
}


int main(void) {
	configura();
	while (1) {
	control();
	}
}