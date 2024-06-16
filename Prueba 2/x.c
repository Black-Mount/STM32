#include "STM32F4xx.h"
#include <stdio.h>

int HEX [16]={63, 6, 91, 79, 102, 109, 125, 7, 127, 103, 119, 124, 57, 94, 121, 113};
int uni=0, con=0;


	void EXTI9_5_IRQHandler(void){ 		
		
	con++;
		
	int cl=0;
		
	GPIOC -> ODR = 0XE;
		cl=((GPIOC -> IDR)&0x1E0);
		if (cl==0x1C0){uni= HEX [7];}
		else if (cl==0X1A0) {uni= HEX [8];}
		else if (cl==0X160) {uni= HEX [9];}
		else if (cl==0XE0) {uni= HEX [10];}

		
	GPIOC -> ODR = 0XD;
		cl=((GPIOC -> IDR)&0x1E0);
		if (cl==0x1C0){uni = HEX [4];}
		else if (cl==0x1A0) {uni= HEX [5];}
		else if (cl==0X160) {uni= HEX [6];}
		else if (cl==0XE0) {uni= HEX [11];}

		
	GPIOC -> ODR = 0XB;
		cl=((GPIOC -> IDR)&0x1E0);
		if (cl==0x1C0){uni = HEX [1];}
		else if (cl==0x1A0) {uni= HEX [2];}
		else if (cl==0X160) {uni= HEX [3];}
		else if (cl==0XE0) {uni= HEX [12];}
		
		
	GPIOC -> ODR = 0X7;
		cl=((GPIOC -> IDR)&0x1E0);
		if (cl==0x1C0){uni = HEX [15];}
		else if (cl==0x1A0) {uni= HEX [0];}
		else if (cl==0X160) {uni= HEX [14];}
		else if (cl==0XE0) {uni= HEX [13];}
		
		
		EXTI->PR=0XFFFF;
		


	}


int main (void){
	
	RCC -> APB2ENR|=(1UL<<14);
	RCC -> AHB1ENR = 0xF;
	GPIOC -> MODER = 0x55;
	GPIOC -> PUPDR = 0x15400;
	GPIOB -> MODER = 0x55555555;
	GPIOA -> MODER = 0x5;
	
	SYSCFG->EXTICR[1]|=0x2220;
	SYSCFG->EXTICR[2]|=0x0002;
	EXTI -> IMR|=0X1E0;
	EXTI -> FTSR|=0X1E0;
	NVIC-> ISER[0]=1UL<<23;
	
	int dec=0;
	
	while(1){
		
		GPIOC -> ODR = 0x0;

		switch(con){
			
			case 0:
				GPIOB -> ODR = 63;
			break;
			
			case 1:
					GPIOB -> ODR = uni;
			break;
			
			default:
				for (int i=0; i<2;i++){
					GPIOB -> ODR = (0ul<<7);
					GPIOB -> ODR = uni;
					dec=uni;
					for(int j=0;j<100;j++);
					GPIOB -> ODR = (0ul<<7);
					GPIOB -> ODR = dec;
				}
			break;
		}
		
	}
}
