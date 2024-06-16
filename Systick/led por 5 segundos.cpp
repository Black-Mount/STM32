# include "stm32f4xx.h"
int a=0;

extern "C" {
	
	void SysTick_Handler(void) {
		a++;
		if (a==5) {
			a=0;
			GPIOB -> ODR= 0x1;
		}
	}
}

int main(void) {
	
	RCC ->AHB1ENR=3; //0011 Puerto A/B
	GPIOA ->PUPDR=2; //0010 Pulldown el botón
	GPIOB ->MODER= 1; //0001 Salida led
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock);
	
	while (1) {
	a=0; while( (GPIOA->IDR &1));
	}
}