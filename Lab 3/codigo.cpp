#include <stm32f4xx.h>
int numerosb[]={0x3f0,0x060,0x5b0,0x4f0,0x660,0x6d0,0x7d0,0x070,0x7f0,0x6f0,0x770,0x7c0,0x390,0x5e0,0x790,0x710};
int numerosc[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int tiempoenseg=5;
int contador=0;
int possieteseg=0;

extern "C"{		
	void EXTI0_IRQHandler(void){
		EXTI->PR |=0XFFFF;
		//mostrar numero 0 en el 7 seg
		GPIOB->ODR=numerosb[0];
		}
	void EXTI1_IRQHandler(void){
		EXTI->PR |=0XFFFF;
		//mostrar numero 1 en el 7 seg
		GPIOB->ODR=numerosb[1];
		}
	void EXTI2_IRQHandler(void){
		EXTI->PR |=0XFFFF;
		//mostrar numero 2 en el 7 seg
		GPIOB->ODR=numerosb[2];
		}
//		void EXTI9_5_IRQHandler(void){
//			if(!(GPIOA->IDR & 1UL<<7)){
//			EXTI->PR |=0XFFFF;
//		//mostrar numero 2 en el 7 seg
//		GPIOB->ODR=numerosb[2];
//			}
//		}

		void SysTick_Handler(void){
			int tiempoenmiliseg=tiempoenseg*10;
			if(contador==(tiempoenmiliseg/2)){
				GPIOA->ODR = 0x20;//Activa led A5
			}else{
				if(contador==tiempoenmiliseg){
					GPIOA->ODR = 0x20;//Activa led A5
				}else{GPIOA->ODR = 0x0;//Desactiva led A5
				}	
			}
			
			
			if(contador==tiempoenmiliseg)
			{
				//hace alguna accion cada num de segndos
				
				GPIOC->ODR=numerosc[possieteseg];
				possieteseg++;//va aumentando la posicion 7 segmentos de 1 en 1
				if(possieteseg>=10)
				{
					possieteseg=0;
				}
				contador=0;
			}
			contador++;
		}
}

void configuracion(void){
	RCC->AHB1ENR = 0X7;//   Habilita puertos A B C
	RCC->APB2ENR |= (1UL<<14);// Habilita el reloj de las interrupciones
	GPIOA->MODER = 0x400;//	Habilita puerto A5 salida
	GPIOB->MODER = 0x155500;// Habilita el B4 al B10
	GPIOC->MODER = 0x1555;//	 Habilita el C0 al C6
	
	GPIOB -> PUPDR = 0X15;           //PullUp   01 0101
	
	EXTI->IMR |= 0X7;	//Habilitar interrupcion 2 1 0  PINES
	EXTI->FTSR |= 0X7;	//Habilitar flanco subida 2 1 0 PINES
	
	SYSCFG->EXTICR[0]=0X0111;//letra a la que esta conectada la interrucpion 3, 2 ,1 , 0 LETRA CONECTADO
	//SYSCFG->EXTICR[1]=0X1111;//letra a la que esta conectada la interrucpion 7, 6 ,5 , 4 LETRA CONECTADO
	//SYSCFG->EXTICR[2]=0X1111;//letra a la que esta conectada la interrucpion 11, 10 ,9 , 8 LETRA CONECTADO
	//SYSCFG->EXTICR[3]=0X2110;//letra a la que esta conectada la interrucpion 15, 14 ,13 , 12 LETRA CONECTADO
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn); 
	//NVIC_EnableIRQ(EXTI3_IRQn); 
	//NVIC_EnableIRQ(EXTI4_IRQn); 
	//NVIC_ENABLEIRQ(EXTI9_5_IRQn);
	//NVIC_ENABLEIRQ(EXTI15_10_IRQn);
	
	SysTick -> LOAD = (1600000)-1; //valor de val, dividido velocidad reloj16.000.000
	SysTick -> VAL = 0;
	SysTick -> CTRL = 0X7;
}

void principal(void){
}

int main(void){
	configuracion();
	while(1){
		principal();
	}
	return 0;
}