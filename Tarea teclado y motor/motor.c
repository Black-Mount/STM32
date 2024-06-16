#include "STM32F4xx.h"

int DEC [10]={63, 6, 91, 79, 102, 109, 125, 7, 127, 103};
int OCT [8]={63, 6, 91, 79, 102, 109, 125, 7};
int HEX [16]={63, 6, 91, 79, 102, 109, 125, 7, 127, 103, 119, 124, 57, 94, 121, 113};

int btn=1,est=0;


int main (void){
	
	RCC->AHB1ENR=0xF; //activación puertos
	GPIOC->MODER|=0x5555; //salida display
	GPIOB->MODER|=0x25525; //salida 8 LEDS
	GPIOC->PUPDR|=1UL<<26; //pull-up PC13 btn usuario
	GPIOA->PUPDR|=1;//pull-up PC1 btn externo
	
	while(1){
		
		
		if((GPIOC->IDR&(1UL<<13))==0){//presiona btn de usuario
			btn=2; //Contador descendente
			
			if(est==0){
					for(int a=8;a>=0;a--){
						GPIOC->ODR=OCT[a]; //Octal
						for(int i=0;i<10000000;i++);
					}
				}
				if(est==1){
					for(int a=9;a>=0;a--){
						GPIOC->ODR=DEC[a]; //Decimal
						for(int i=0;i<10000000;i++);
					}
				}
				if(est==2){
					for(int a=16;a>=0;a--){
						GPIOC->ODR=HEX[a]; //hexa
						for(int i=0;i<10000000;i++);
					}
				}
			
		} else {
				btn=1; //Contador ascendente
			
				if(est==0){			
					for(int a=0;a<9;a++){
						GPIOC->ODR=OCT[a]; //Octal
						for(int i=0;i<10000000;i++);	
					}
				}
				if(est==1){
					for(int a=0;a<10;a++){
						GPIOC->ODR=DEC[a]; //Decimal
						for(int i=0;i<10000000;i++);
					}
				}
				if(est==2){
					for(int a=0;a<17;a++){
						GPIOC->ODR=HEX[a]; //hexa
						for(int i=0;i<10000000;i++);
					}
				}
			
		}
		
		
		
		if((GPIOA->IDR&1)==0){//presiona btn externo
			if(est<4){est++;}
			else est=0;
		}
		
		if ((GPIOA -> IDR & 1)==0){
		for (int i=0;i<10;i++){
		GPIOB -> ODR = 1UL<<((2*i)+1);
		for(int i=0;i<10000000;i++);
		}
		
		} else {
		for (int a=10;a>=0;a--){
		GPIOB -> ODR = 1UL<<((2*a)+1);
		for(int i=0;i<10000000;i++);	
		}
		
	}
}
}