#include "stm32f4xx.h"

int recibido=0;
int Prueba1=0;


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
	
	Prueba1=1;
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
	
	Prueba1=2;
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

void USART1_Config(void){
	GPIOA->MODER |= 0X280000;// PA(10-9)Alterno
	GPIOA->AFR[1]|=0X0770;//Tx,Rx
	RCC->APB2ENR|=1<<4;//Activar USART1
	USART1->BRR=0X684;//9600b/s
	USART1->CR1=0X212C;//Enable Usart, Tx,Rx,
	NVIC_EnableIRQ(USART1_IRQn);
}


extern "C" {
	
	void USART1_IRQHandler(void)
	{
		recibido=USART1->DR; //Lee dato recibido
		if (recibido==49) { //Recibe un uno en ASCII
			secuencia1();
		
		}
		if (recibido==50) { //Recibe un dos en ASCII
			secuencia2();

		}
		
	}
	

}




int main(){
	
	RCC -> AHB1ENR = 0xF;
	USART1_Config();
	GPIOC->MODER |= GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0; // Pines C1, C2, C3 y C4 como salidas
	
	
	while (1){
		__NOP();
	}
}