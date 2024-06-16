#include "STM32F4xx.h"
#include <cmath>
#include <stdio.h>



int u=0;
char recibido[]= {' '};
float TLM35=0,temp=0,joystick=0,LDR=0,envioadc=0;
int sensor=0;
char comando[]={' '};
char comando2[]={' '};
float rpm = 0,velocidad = 0,conver = 0,potenciometro=0,tiempo = 0;
int cont_init = 0,cont_usart=0,conta = 0,siu = 0,vueltas = 0,cen = 0,unid = 0,dec = 0,mil = 0,mil2 = 0,n = 0;
double tiempo_transcurrido;
char modo;
char control_pwm2;
char manual2;

void basicdelay(){for(int x=0;x<800000;x++);}
void hall_config(void) {
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN; // Activa reloj TIM2
  TIM5->CNT=0xFFFFFFFF; // Valor inicial del contador
  TIM5->CR1|=TIM_CR1_CEN; // Encendido del TIM2
  // Periodo de 1 usegundo
  TIM5->ARR=999;//63999; 999
  TIM5->PSC=15;//249;15
  NVIC_EnableIRQ(TIM5_IRQn); // Activa interrupción
  TIM5->DIER|=TIM_DIER_UIE; // Enciende interrupción TIM2
}

float RADC(int canal){
	ADC1 ->SQR3=(unsigned int)canal;
	ADC1->CR2|=(1UL<<30);
	while((ADC1 -> SR & 0X2)==1);
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
	
void TIM5_IRQHandler(void){
  TIM5->SR&=(~TIM_SR_UIF); // Apagado de bandera
	 if(cont_init == 1){
   tiempo++;}
 }
 
 	void EXTI0_IRQHandler(void){
		EXTI ->PR |= 0X8007; 
		vueltas++;
		if(cont_init == 0){
			cont_init = 1;
			tiempo = 0; 
			tiempo_transcurrido = 0;
		}else{
			cont_init = 0;
			tiempo_transcurrido = tiempo;
			rpm = (60000.0/(tiempo_transcurrido));
			velocidad = (rpm *(2.0* 3.141592))/60.0;
			if(rpm>9999){rpm=9999;}
			
			 
	mil = rpm/1000;
	n = (int)rpm%1000;
	cen = n/100;
	n= n%100;
	dec = n/10;
	n= n%10;
	unid = n;
 
 delay(500);
 
 rpm = 0;
		}	
		
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
	RCC ->APB2ENR |= (1UL<<14);               //Encender el Reloj de las interrupciones
	EXTI -> FTSR |= 0X1;
	EXTI -> IMR |= 0X1;                  //Activar las interrupcion 0
	SYSCFG -> EXTICR[0] |= 0X0001;         //Interrupciones en PB0 0000 0000 0000 0001
	NVIC_EnableIRQ(EXTI0_IRQn);       //Activa Interrupción 0
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
	hall_config();
	
	while (true){		
		
		//Lectura lm35
		float temp= (3.3*RADC(0)/4095)/0.01;//0.01
	basicdelay();
	
	//Lectura Foto celda
	float LDR=128-((3.3*RADC(1)/4095)*41.166-13.996);
	basicdelay();

		sendUsart();
	}
	
}
