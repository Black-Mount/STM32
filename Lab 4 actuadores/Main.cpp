// Código Ejemplo 12 1 // 
// Archivo *.cpp //
#include "stm32f746xx.h"
#include "stdio.h"

void USART1_Config(void);
void SysTick_Handler(void);

int compara=0;
float recibido=0;
float dacsaso=0;
float rpm=0;
int codigodac=0;

extern "C"
{

	void USART1_IRQHandler (void) {
	
	recibido=USART1->DR; //Lee dato recibido
		if (recibido==49) { //Recibe un uno en ASCII 
			//Poner algo para que la transportadora inicie
			compara=0;
		}
		if (recibido==50) { //Recibe un dos en ASCII
			//Poner algo para que la transportadora pare
			compara=1;
		}
		
	}
	}


void USART1_Config(void){
	GPIOA->MODER |= 0X280000;// PA(10-9)Alterno
	GPIOA->AFR[1]|=0X0770;//Tx,Rx
	RCC->APB2ENR|=1<<4;//Activar USART1
	USART1->BRR=0X684;//9600b/s 0x28B1 para 100Mhz, y 0x684 normal
	USART1->CR1=0X212C;//Enable Usart, Tx,Rx,
	NVIC_EnableIRQ(USART1_IRQn);
}

int main(void){
 RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; // Activa reloj GPIOA
 GPIOA->MODER|=(3UL<<GPIO_MODER_MODER4_Pos); // Activa PA4 como pin análogo    
 RCC->APB1ENR|=RCC_APB1ENR_DACEN; // Activación del reloj DAC
 DAC->CR|=DAC_CR_EN1; // Activación del módulo DAC 
 DAC->DHR12R1=0; // Ajusta 0 voltios
	USART1_Config();
	
 while(1) {
	 
	 dacsaso=recibido-48;
	 rpm=dacsaso*30;
	 	switch (compara) {
		
		case 1:
			
		codigodac = ((rpm - 1) / (3000 - 1)) * (2048 - 1) + 1;
		
		break;
		
		case 2:
		codigodac = ((rpm - 1) / (3000 - 1)) * (4095 - 2049) + 2049;
		
		break;
		
	}
	
DAC->DHR12R1=codigodac;
 }; // Bucle infinito
 //return 0;
}

