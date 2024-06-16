#include "stm32f7xx.h"
#include "math.h"

void DAC_cfg();

int A=2048,seno=0,t=0,f=10; //
#define WORKING GPIOB->ODR^=1


int main(void) {
	DAC_cfg();
	GPIOB->MODER|=1;
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	while (true) {
	if((GPIOC -> IDR&0X2000)==0) {A=A;}
	seno=A*sin(2*3.14159*f*t);
	DAC -> DHR12R1 =2000+seno;
}
	
}


void DAC_cfg() {
	RCC ->AHB1ENR=7;
	RCC ->APB1ENR|= 0X2000000;
	DAC ->CR= 0X1;
	DAC -> DHR12R1 = 0xDAC;
}


extern "C" {
	void SysTick_Handler(void) {
		t++;
		if (t>=1000) {
			t=0;
		}
		WORKING;
	}
}