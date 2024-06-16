#include <stm32f4xx.h>

int dato=0;
int matlab=0;
int matlab2=0;


	void USART2_Config(void){
		GPIOA->MODER|=0x80;// Se configura el pin a3 en alterno, por donde se conecta la com serial
		GPIOA->AFR[0]|=0x7000;// Se configura el pin A3 para el af7=USART2
		RCC->APB1ENR|=(1UL<<17); //Habilita el usart2, valor por defecto
		USART2->BRR=0x683; //9600 Bausios 
		USART2->CR1|=0x2D; //Interrupcion habiliatado Se habilita el tx, el rx y la interrupción del usart
		USART2->CR1|=0x2000;  //Activa el usart
		NVIC_EnableIRQ(USART2_IRQn); //Activa vector de interrupción
	 USART2->CR1|=USART_CR1_RXNEIE; // Activa servicio de interrupción
		
	}
extern "C" {
	void USART2_IRQHandler(void)
	{
		matlab=USART2->SR; //Limpia bandera
		matlab=USART2->DR; //Lee dato recibido
		while(!(USART2->SR&USART_SR_TXE)); // Espera puerto disponible 
    USART2->DR=matlab; // Transmite dato
			matlab2=matlab;
    SystemCoreClockUpdate();
			SysTick_Config(SystemCoreClock);
		
		
	}
	
	void SysTick_Handler(void) {
	
		
	}
	
}

int main(void) {
	RCC->AHB1ENR|=7;
	RCC->APB1ENR|=(1UL<<1);
	USART2_Config();
	GPIOB->MODER=0x10004001;
	GPIOC->MODER=0;
	
	GPIOA->MODER|=0X8000;
	GPIOA->AFR[0]=0X20000000;
	TIM3->EGR|=(1UL<<0);
	TIM3->PSC=15;
	TIM3->ARR=20000;
	TIM3->DIER|=(1UL<<0);
	
	TIM3->CR1|=(1UL<<0);
	TIM3->CCMR1=0X6000;
	TIM3->CCER|=(1UL<<0);
	TIM3->CCR2=510;
	
	
	while(true) {
		
	
			if(matlab2>2400){
				matlab2=510;
		
		TIM3->CCR2=matlab2;
		for (int i=0;i<2000000;i++);
	}
}
}