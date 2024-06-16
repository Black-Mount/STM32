#include "STM32F4xx.h"

int teclado(void){
int cl=0;
while (1){
	for (int i=0;i<100000;i++){GPIOC -> ODR=1;};

	GPIOA -> ODR = 1;
		cl=(GPIOA -> IDR)&0xF0;
		if (cl==16){return 7;}
		else if (cl==32) {return 127;}
		else if (cl==64) {return 103;}
		else if (cl==128) {return 119;}

	GPIOA -> ODR = 2;
		cl=(GPIOA -> IDR)&0xF0;
		if (cl==16){return 102;}
		else if (cl==32) {return 109;}
		else if (cl==64) {return 125;}
		else if (cl==128) {return 124;}

	GPIOA -> ODR = 4;
		cl=(GPIOA -> IDR)&0xF0;
		if (cl==16){return 6;}
		else if (cl==32) {return 91;}
		else if (cl==64) {return 79;}
		else if (cl==128) {return 57;}

	GPIOA -> ODR = 8;
		cl=(GPIOA -> IDR)&0xF0;
		if (cl==16){return 113;}
		else if (cl==32) {return 63;}
		else if (cl==64) {return 121;}
		else if (cl==128) {return 94;}	
	
	
}
}

int main (void){
	
	RCC -> AHB1ENR = 0xF;
	GPIOA -> MODER = 0x55;
	GPIOA -> PUPDR = 0xAA00;
	GPIOB -> MODER = 0x5555;
	
	while(1){
	
		GPIOB -> ODR = teclado();
		
	}
}