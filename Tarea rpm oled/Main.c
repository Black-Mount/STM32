#include <stm32f4xx.h>
#include "stdio.h"
#include "Init.h"
#include "oled.h"

int cont=0;
int matlab=0;

void Delay(int x){
	for(volatile int i=0;i<x*700; i++){
		__ASM("NOP"); 
	}
}
void configUsart(void){
	RCC->APB1ENR|=1<<17;//Activar USART2
	USART2->BRR=0X683;//9600b/s
	USART2->CR1=0X212C;//Enable Usart, Tx,Rx, Interrupci?n Rx
	NVIC_EnableIRQ(USART2_IRQn);
	
}
void sendUsart(){
	
	USART2->DR='#';
	Delay(30);
	
	
		USART2->DR=matlab;
	Delay(30);
		
	USART2->DR='#';
	Delay(30);
	
	}
int main(){
	InitComponents();
	configUsart();
	GPIOA->MODER |= 0XA0;// PA(2-3)Alterno
	  GPIOA->AFR[0]|=0X7700;//Tx,Rx
	Interfaz_OLED();
	InitInterrupt();
	GPIOC-> MODER =0x5;
	Config_TIMER();
	


while (1){
	
 }
}


void EXTI4_IRQHandler(void){
	EXTI->PR|=0Xffff;
//	while (GPIOA-> IDR &0x10){}
	cont++;
	
	
}

void TIM2_IRQHandler(void){
	TIM2->SR =~1;
	GPIOC -> ODR ^=1;

  char rpm[10]={'0','0','0'};
	OLED_GotoXY (60,35);
	sprintf(rpm, "%d", (cont*60));
	matlab=cont;
	sendUsart();
	if (cont==0){sprintf(rpm, "%d", (0));}
	OLED_Puts (rpm, &Font_7x10, 1);
  OLED_UpdateScreen();

	cont=0;
}