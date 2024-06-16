#include "stm32f4xx.h"
#include <stdio.h>

double dist=0;
double  dist2=0;
double total=0;
int ty=0,grados=0;
char yu[10]={0};

//void configUsart(void){
//	RCC->APB1ENR|=1<<17;//Activar USART2
//	USART2->BRR=0X683;//9600b/s
//	GPIOA->AFR[0]|=0x7700;// Se configura el pin A3 para el af7=USART2, tx, rx
//	USART2->CR1|=0X212C;//Enable Usart, Tx,Rx, Interrupci?n Rx
//	USART2->CR1|=0x2D; //Interrupcion habiliatado Se habilita el tx, el rx y la interrupción del usart
//	USART2->CR1|=0x2000;  //Activa el usart
//	NVIC_EnableIRQ(USART2_IRQn);
//	 USART2->CR1|=USART_CR1_RXNEIE; // Activa servicio de interrupción
//}

int main (void)
{

	RCC->AHB1ENR|=0x7; //Habilitar puertos A-B-C
	GPIOC->MODER|=0x4;//Pin C1 de salida
	GPIOB -> MODER |= 0X4;//Pin B1 de salida 
	
	//TIMER ULTRASONIDO
	RCC->APB1ENR|=1;// Se habilita el reloj del TIM2 
	TIM2 -> CR1 = 1;// Contador habilitado
	TIM2 -> PSC = 16; //Base d etiempo de 1 us
	TIM2 -> ARR = 0xf0000; // Limite de cuenta  
	
//	//TIMER PWM
//	RCC->APB1ENR|=0x8;// Se habilita el reloj del TIM5
//	TIM5->CR1=0x1;// Contador habilitado
//	TIM5->PSC=15; // Base de tiempo 1 us
//	TIM5->ARR=20000;// Limite de tiempo de 20ms
//	GPIOA->MODER|= 0x2;// PA0 modo alterna(10)
//	GPIOA ->AFR[0]=0x2; // funcion alterna AF2=TIM5_CH1
//	TIM5->CCMR1=0X60; // PWM modo 1
//	TIM5->CCER= 0x1;//Se activa el canal 1


//	RCC-> APB2ENR |= (1UL << 5);//Se habilit el reloj del USART
//	USART6 -> BRR = 0x683; // 9600 Baudios
//	USART6 -> CR1 = 0x2D; // Tx habilitado, Rx habilitado
//	USART6 -> CR1 |=0x2000; // Se activa el modulo USART
//	GPIOA->MODER |=0xAA00000; // PA11 -PA12 modo alterno
//	GPIOA->AFR[1]|=0x88000; // PA11 -PA12 -> AF8= USART6 Tx y Rx
//	configUsart();
	
	while (true)
	{
//		GPIOC->ODR=2; // Se acciona el triger del ultrasonido
//		TIM2->CNT=0; // Se reinicia el conteo del TIM
//		while(TIM2 -> CNT < 12){} // Se cuenta 12us
//		GPIOC-> ODR = 0;// Se apaga el triger del ultrasonido
//		while ((GPIOC -> IDR & 0x1)==0); // Se espera a que la señal ECO se ponga en 1
//		TIM2 -> CNT = 0;// Se apaga reinicia el contero del TIM
//		while((GPIOC->IDR&1)==1); // Se espera a que la señal de ECO sea 0
//		dist=((double)TIM2->CNT)*17/1000+0.5; // Calculo de distancia
//		for(int t=0;t<10000;t++);//delay 
		
		GPIOB->ODR=2;// Se acciona el triger del ultrasonido
		TIM2->CNT=0;// Se reinicia el conteo del TIM
		while(TIM2 -> CNT < 12){}// Se cuenta 12us
		GPIOB-> ODR = 0;// Se apaga el triger del ultrasonido
		while ((GPIOB -> IDR & 0x1)==0);// Se espera a que la señal ECO se ponga en 1
		TIM2 -> CNT = 0;// Se apaga reinicia el contero del TIM
		while((GPIOB->IDR&1)==1);// Se espera a que la señal de ECO sea 0
		dist2=((double)TIM2->CNT)*17/1000+0.5; // Calculo de distancia
			for(int t=0;t<10000;t++);//delay
//			
//		if(dist < 30 && dist2 >30) //VARIa con prioridad el puerto C
//		{
//			ty=(int)dist*39+505; // Calculo entre la distancia y el CCR
//			TIM5->CCR1=ty; 
//			grados = (ty - 700) * 90 / (1675 - 700);// Se pasa el valor del CCR a grados
//		}
//		else if(dist>30 && dist2<30)//Varia con prioridad el puerto B
//		{
//			ty=(int)dist2*39+1480;// Calculo entre la distancia y el CCR
//			TIM5->CCR1=ty;
//			grados = (ty - 1675) * 90 / (2650 - 1675) + 90;// Se pasa el valor del CCR a grados
//		}
//		else if ( dist <30 && dist2 <30)//Varia respecto al promedio 
//		{
//			total= (dist+dist2)/2 ;// Promedio entre la distancia
//			ty= (int)total*78+310;// Calculo entre la distancia y el CCR
//			TIM5-> CCR1=ty;	
//			grados = (ty - 700) * 180 / ( 2650-700);// Se pasa el valor del CCR a grados
//		}
//		sprintf(yu,"%i" ,grados);// se introduccen los digitos separados en un vector tipo char para ser enviados
//		
//	for(int r=0;r<4;r++){
//			USART6->DR=yu[r]; //dato
//			for(int p=0;p<40000;p++);
//		}
//		USART6->DR=10; //separacion
//		for(int b=0;b<50000;b++);

//		USART2->DR=dist2;
	}}