#include <stm32f4xx.h>
#include <stdio.h>
#include "Init.h"
#include "oled.h"

int cont=0;

int main(){
	InitComponents();
	Interfaz_OLED();
	InitInterrupt();
//	Config_TIMER();


while (1){
/*	char rpm[6];
	OLED_GotoXY (55,35);
	sprintf(rpm,"%.0f",(cont*240));
	OLED_Puts (rpm, &Font_7x10, 1);
  OLED_UpdateScreen();
	*/
 }
}


void Exti4_IRQHandler(void){
	cont++;
	char rpm[3]={'0','0','0'};
	OLED_GotoXY (55,35);
	sprintf(rpm,"%.0f",(cont));
	OLED_Puts (rpm, &Font_7x10, 1);
  OLED_UpdateScreen();
	EXTI->PR|=1;
}/*
void TIM3_IRQHandler(void){
	TIM3->SR &=~(1<<10);
	
	
	cont=0;
}*/
