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



void delay(void) {
	for (int i = 0; i < (15*100000); i++) {__asm("NOP");
        // Pequeña función de retardo
    }
}

void delay2(void) {
    for (int i = 0; i < 1000*1000; i++) {__asm("NOP");
        // Pequeña función de retardo
    }
}

void secuencia1 (void) {
	
	
			// Secuencia 000
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
	
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();
	
	
			// Secuencia 001
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BS_3;
	
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();
	

        // Secuencia 010
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BR_3;
	
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

        // Secuencia 011
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BS_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

        // Secuencia 100
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

        // Secuencia 101
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BS_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

        // Secuencia 110
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BR_3;
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

        // Secuencia 111
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BS_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

}

void secuencia2 (void){
	        // Secuencia 111
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BS_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

         // Secuencia 110
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BR_3;
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

  // Secuencia 101
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BS_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

          // Secuencia 100
        GPIOC->BSRR = GPIO_BSRR_BS_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();


        // Secuencia 011
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BS_3;
				
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

       // Secuencia 010
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BS_2 | GPIO_BSRR_BR_3;
	
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();

      		// Secuencia 001
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BS_3;
	
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();
				
				// Secuencia 000
        GPIOC->BSRR = GPIO_BSRR_BR_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3;
	
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BS_4; //Trigger
				delay2();
				GPIOC->BSRR = GPIO_BSRR_BR_4; //Trigger
        delay();
	

}

extern "C"
{

	void UART4_IRQHandler(void) {
		
	recibido= UART4-> RDR; //Lee dato recibido
		if (recibido==49) { //Recibe un uno en ASCII 
			//Poner algo para que la transportadora inicie
			compara=1;
			secuencia1();
			//recibido=0;
		}
		if (recibido==50) { //Recibe un dos en ASCII
			//Poner algo para que la transportadora pare
			compara=2;
			secuencia2();
			//recibido=0;
		}
		
 dacsaso=recibido-48;
	 rpm=(3000/9)*dacsaso;
		
		
			 	switch (compara) {
		
		case 1:
			
		codigodac = ((rpm - 1) / (3000 - 1)) * (2048 - 1) + 1;
		
		break;
		
		case 2:
		codigodac = ((rpm - 1) / (3000 - 1)) * (4095 - 2049) + 2049;
		
		break;
		
	}

		
	}
//	void USART1_IRQHandler (void) {
//	
//	recibido= USART1-> RDR; //Lee dato recibido
//		if (recibido==49) { //Recibe un uno en ASCII 
//			//Poner algo para que la transportadora inicie
//			compara=0;
//		}
//		if (recibido==50) { //Recibe un dos en ASCII
//			//Poner algo para que la transportadora pare
//			compara=1;
//		}
//		
//	}
	}

	void UART4_Config(void){
	RCC ->AHB1ENR |=0X6; //Puertos B y C Habilitados
	RCC ->APB1ENR |=0x80000; //Habilitar UART 4
	GPIOC-> MODER |=0xA00000; //Pines en alterno
	GPIOC ->AFR[1]= 0X8800; //pc10/pc11
	UART4->BRR=0X683; //Velocidad 9600 Baudios
	UART4 ->CR1=0X2D; //Habilitar el uart
	
	NVIC_EnableIRQ(UART4_IRQn); //Habilitar interrupción uart 4
	
	
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
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Habilitar el reloj para el puerto GPIOC
	
 GPIOA->MODER|=(3UL<<GPIO_MODER_MODER4_Pos); // Activa PA4 como pin análogo  
 GPIOC->MODER |= GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0; // Pines C1, C2, C3 y C4 como salidas  
	UART4_Config();
 RCC->APB1ENR|=RCC_APB1ENR_DACEN; // Activación del reloj DAC
 DAC->CR|=DAC_CR_EN1; // Activación del módulo DAC 
 DAC->DHR12R1=0; // Ajusta 0 voltios
//	USART1_Config();
	
	
 while(1) {
	 
	DAC->DHR12R1=codigodac;

 }; // Bucle infinito
 //return 0;
}
