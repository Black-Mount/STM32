#include <stm32f4xx.h>
#include <cmath>
#include <stdio.h>


#define PLL_M 5
#define PLL_N 225
#define PLL_P 0
void basicdelay(){for(int x=0;x<800000;x++);}
float TLM35=0,temp=0,joystick=0,LDR=0,envioadc=0;

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
	USART2->BRR=0X493E;//9600b/s a 18 mhz
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
	
	USART2->DR=envioadc;
	delay(1000);
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
		
		////////////PLL
	RCC->CR|=0X10000; //Activar el oscilador HSI
while((RCC->CR&0X20000)==0); //Esperar a que se active
RCC->APB1ENR=0X10000000; //Habilitar reloj
RCC->CFGR=0X9400; //Configuración para 746
RCC->PLLCFGR=(PLL_M<<0)|(PLL_N<<6)|(PLL_P<<16)|(RCC_PLLCFGR_PLLSRC_HSI); //Configuración MNP 
RCC->CR|=0X010000000; //Activar el PLL
while ((RCC->CR & 0X02000000)==0); //Esperar a que el pll este listo
FLASH->ACR=0x205; //Activar el ART Accelerator
RCC->CFGR|=2; //Seleccionar PLL como fuente de reloj

RCC->AHB1ENR|=(1UL<<1); //Eencender el reloj del ptb
GPIOB->MODER|=0X10004001; //Configuración ptb en salida

	configUsart();
	
	
	while (true){		
		
		envioadc= (3.3*RADC(1)/4095)*50; //Envío
	basicdelay();
		sendUsart();
		
	}
	
}