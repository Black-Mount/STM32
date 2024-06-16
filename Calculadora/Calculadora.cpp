#include "stm32f401xe.h"

int matriz[]={0x1EFF,0X1DFF,0X1BFF,0X17FF,0X0FFF};
int hexadecimal[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71};
int teclado[4][5]={
	{7,8,9,12,16},
	{4,5,6,13,17},
	{1,2,3,14,18},
	{10,0,11,15,19}
};

void delay(void) {
	for(int x=0; x<180000;x++);
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
	
	
}

extern "C" {
	void EXTI4_IRQHandler(void){
		
	EXTI->PR|=0xFFFF;
	
	}
	
	void EXTI9_5_IRQHandler(void){
	
	EXTI->PR|=0xFFFF;
		
		if(!(GPIOB->IDR & (1UL<<5))) {
				
		}
		
		if(!(GPIOB->IDR & (1UL<<6))) {
			
			
		}
		
		if(!(GPIOB->IDR & (1UL<<7))) {
			
			
		}
		
		
	}
}

void configura(void) {

	RCC->AHB1ENR=0XF;
	RCC->APB2ENR|=(1UL<<14);
	GPIOA->MODER=0X1550000;
	GPIOC->MODER=0X1555555;
	GPIOA->PUPDR=0X1550000;
	EXTI->IMR|=0xF0;
	EXTI->FTSR|=0xF0;
	SYSCFG->EXTICR[1]=0x1111;
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	
}



void control(void) {
	
	for(int i=0; i<5; i++) {
	GPIOA->ODR=matriz[i];
		delay();
	}
	imprimir(1,2,2,5,6);
}


int main(void) {
	configura();
	while (1) {
	control();
	}
}
