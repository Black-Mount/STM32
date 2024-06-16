#include "STM32F4xx.h"
#include <cmath>
#include <stdio.h>



int u=0;
char recibido[]= {' '};
float TLM35=0,temp=0,joystick=0,LDR=0,envioadc=0;
int sensor=1;
char comando[]={' '};
char comando2[]={' '};

void basicdelay(){for(int x=0;x<800000;x++);}

float RADC(int canal){
	ADC1 ->SQR3=(unsigned int)canal;
	ADC1->CR2|=(1UL<<30);
	while((ADC1 -> SR & 0X2)==1);
	//float voltaje=3.3*(ADC1->DR)/4095;
	float medicion=(ADC1->DR);
	return medicion;
}

void configUsart(void){
	RCC->APB1ENR|=1<<17;//Activar USART2
	USART2->BRR=0X683;//9600b/s
	GPIOA->AFR[0]|=0x7700;// Se configura el pin A3 para el af7=USART2, tx, rx
	USART2->CR1|=0X212C;//Enable Usart, Tx,Rx, Interrupci?n Rx
	USART2->CR1|=0x2D; //Interrupcion habiliatado Se habilita el tx, el rx y la interrupción del usart
	USART2->CR1|=0x2000;  //Activa el usart
	NVIC_EnableIRQ(USART2_IRQn);
	 USART2->CR1|=USART_CR1_RXNEIE; // Activa servicio de interrupción
}

void delay(int x){
	for(int i=0;i<x*500;i++){
      asm("nop");
  }
}

void sendUsart(){
	
	if (sensor!=0){
	
	USART2->DR=envioadc;
	delay(1000);
	}
	}

extern "C"{
	
	void EXTI0_IRQHandler(void){//code}
		sensor++;
		if (sensor==4) {
			sensor=0;
		}
		EXTI->PR |=0XFFFF;     //(1ul<<pin)
	}
	void USART2_IRQHandler(void) /// Revisar
	{
	USART2->SR; //Limpia bandera
		
		recibido[0]=USART2->DR; //Lee dato recibido
		while(!(USART2->SR&USART_SR_TXE)); // Espera puerto disponible  

    SystemCoreClockUpdate();
			SysTick_Config(SystemCoreClock);
	}
}

int main (void){
	RCC -> AHB1ENR|= 0xF;
	RCC -> AHB1ENR|= 0x7;				//Activa todos los puertos
	RCC -> 	APB2ENR |= 0X100;		//Activa el adc1
	GPIOA -> MODER |= 0X30F;
	RCC->APB2ENR |=(1ul<<14);
	GPIOA->MODER |= 0XA0;// PA(2-3)Alterno
	GPIOA->AFR[0]|=0X7700;//Tx,Rx
	GPIOB->MODER =4;
	GPIOB-> PUPDR =1;
	EXTI->IMR |=1;
	EXTI->RTSR |=1;
	SYSCFG->EXTICR[0]=0x0001;
	NVIC_EnableIRQ(EXTI0_IRQn);
	ADC1 -> CR1 = 0X0;
	ADC1 -> CR2 = 0X1;
	ADC1->SMPR1=0xFFFFFFFF;
	ADC1->SMPR2=0xFFFFFFFF;
	ADC1 ->SQR1=0;
	ADC1 ->SQR2=0;
	ADC1 ->SQR3=0;
	configUsart();
	
	
	while (true){		
		
		switch(sensor) {
			
			case 1:
				 envioadc= (3.3*RADC(1)/4095)/0.01;//0.01
	basicdelay();
			break;
			
		 case 2:
				 envioadc= (3.3*RADC(1)/4095)*50;
	basicdelay();
			break;
					
		 case 3:
				 envioadc=128-((3.3*RADC(1)/4095)*41.166-13.996);
	basicdelay();
			break;
		 
		 default:
			 envioadc=0;
		 break;
		}

		sendUsart();
	}
	
}
