#include <stdio.h>
#include "STM32F7xx.h"

// Javier Buitrago			Ángela Hurtado			Miguel Cruz
// 				 1803312						 1803168					1803288

int teclado=0;
bool conteo=0;//Define si el conteo es ascendente o descendente
int vInicial=0;
int segmentos[10]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
bool stop=0;
int visualizacion=0;

int main(void){
	{
	//Clocks
	RCC->AHB1ENR|=0x6;//Activar relojes puerto B y C "110"
	RCC->APB2ENR |= 0x4000;//activación del reloj del EXTI 
	}
	{//Puerto B 
	GPIOB->MODER = 0x55555555; 
	GPIOB->OSPEEDR =0x55555555; 
	GPIOB->OTYPER = 0; 
	GPIOB->PUPDR = 0x55555555; 
}
	{//Puerto C Filas
	GPIOC->MODER = 0x5500;//Filas Teclado pines 4-7 "Salidas" Columnas Teclado pines 0-3 ""Entrada"
	GPIOC->OSPEEDR = 0x5500; //Velocidad del pin, Vel intermedia, "00" bajo,"10" alto
	GPIOC->PUPDR = 0xAAAA; 
	GPIOC->OTYPER = 0; 
	}
	{//Interrupciones para el teclado
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	SYSCFG->EXTICR[0]=0x2222;//interrupciones pines 0-3 puerto C
	EXTI->IMR |= 0xF;
	EXTI->RTSR|= 0xF;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
		
	}
	while(true){
		GPIOC->ODR = 0xf0;// Envia un uno a todas las filas del teclado en espera de una interrupcion de las columnas
		
		GPIOB->ODR=segmentos[vInicial];
		
	}//FinWhile
}//Fin main
extern "C"{

	void EXTI0_IRQHandler(void){
		EXTI->PR=0x1;
		GPIOC->ODR=0;	
		GPIOC->ODR=0x10; 
		if((GPIOC->IDR & 0x1)==0x1){//tecla D
			teclado=13;
		}
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x1)==0x1){//tecla C
			stop=0;
		}
		GPIOC->ODR=0x40; 
		if((GPIOC->IDR & 0x1)==0x1){//tecla B
			stop=1;
		}
		GPIOC->ODR=0x80; 
		if((GPIOC->IDR & 0x1)==0x1){//tecla A
				conteo=!conteo;
		}
	}	
	void EXTI1_IRQHandler(void){
		EXTI->PR=0x2;
		GPIOC->ODR=0;	
		GPIOC->ODR=0x10; 
		if((GPIOC->IDR & 0x2)==0x2){//tecla #
			teclado=14;
		}
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x2)==0x2){//tecla 9
			vInicial=9;
		}
		GPIOC->ODR=0x40; 
		if((GPIOC->IDR & 0x2)==0x2){//tecla 6
			vInicial=6;
		}
		GPIOC->ODR=0x80; 
		if((GPIOC->IDR & 0x2)==0x2){//tecla 3
			vInicial=3;
		}
	}
	void EXTI2_IRQHandler(void){
		EXTI->PR=0x4;
		GPIOC->ODR=0;	
		GPIOC->ODR=0x10; 
		if((GPIOC->IDR & 0x4)==0x4){//tecla 0
			vInicial=0;
		}
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x4)==0x4){//tecla 8
			vInicial=8;
		}
		GPIOC->ODR=0x40; 
		if((GPIOC->IDR & 0x4)==0x4){//tecla 5
			vInicial=5;
		}
		GPIOC->ODR=0x80; 
		if((GPIOC->IDR & 0x4)==0x4){//tecla 2
			vInicial=2;
		}
	}
	void EXTI3_IRQHandler(void){
		EXTI->PR=0x8;
		GPIOC->ODR=0;	
		GPIOC->ODR=0x10; 
		if((GPIOC->IDR & 0x8)==0x8){//tecla *
			teclado=15;
		}
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x8)==0x8){//tecla 7
			vInicial=7;
		}
		GPIOC->ODR=0x40; 
		if((GPIOC->IDR & 0x8)==0x8){//tecla 4
			vInicial=4;
		}
		GPIOC->ODR=0x80; 
		if((GPIOC->IDR & 0x8)==0x8){//tecla 1
			vInicial=1;
		}
		
	}
	
	void SysTick_Handler (){	

		visualizacion++;
		if(visualizacion>=1000) 
		{
			visualizacion=0;
			
			if(stop==1)
			{
				if(conteo==1){ //Ascendente
				vInicial++;
				}
				if(conteo==0){ //Descendente
				vInicial--;
				}
			}
			
			if(vInicial>9){vInicial=0;}
			if(vInicial<0){vInicial=9;}
		}
	}
}
