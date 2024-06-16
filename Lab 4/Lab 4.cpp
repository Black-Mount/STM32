#include <stm32f4xx.h>
#include <stdio.h>
#include <math.h>
int RESULTADO[5]={0,0,0,0,0};
int cont=0;
float RPM=0;
char NU[10]={'0','1','2','3','4','5','6','7','8','9'};
char MEN[4]={'R','P','M',':'};

void display(void);

extern "C"{
	void EXTI0_IRQHandler(void){
				cont++;
	}
	
	void Systick_Handler(void){
		RPM=cont*60;
		cont=0;
		display();
	}
}

void send_comando(char a){
	GPIOC -> ODR = a|1UL<<9;
	for (int j=0;j<10000;j++){asm("nop");}
	GPIOC ->ODR &=~ (1UL<<9);
}

void send_dato(char b){
	GPIOC -> ODR = b|1UL<<8|1UL<<9;
	for (int j=0;j<10000;j++){asm("nop");}
	GPIOC ->ODR &=~ (1UL<<9);
}

void delay(int x){
	for(int i=0;i<x*500;i++){
      asm("nop");
  }
}

void obten_resultado(void){
	
	RESULTADO[0]=RPM/1000;
	RESULTADO[1]=(RPM/100)-(RESULTADO[0]*10);
	RESULTADO[2]=(RPM/10)-(RESULTADO[0]*100)-(RESULTADO[1]*10);
	RESULTADO[3]=(RPM)-(RESULTADO[0]*1000)-(RESULTADO[1]*100)-(RESULTADO[2]*10);
	RESULTADO[4]=(RPM*10)-(RESULTADO[0]*10000)-(RESULTADO[1]*1000)-(RESULTADO[2]*100)-(RESULTADO[3]*10);
	
}

void display(void){
	
	obten_resultado();
	
	for (int j=0; j<4;j++){
		send_comando(0x80+j);
		send_dato(NU[MEN[j]]);
		delay(50);
	}
	
	for (int j=0; j<4;j++){
		send_comando(0x85+j);
		send_dato(NU[RESULTADO[j]]);
		delay(50);
	}
	
		send_comando(0x89);
		send_dato('.');
		delay(50);
	
		send_comando(0x8A);
		send_dato(NU[RESULTADO[4]]);
		delay(50);
	
}


int main(void){
	RCC->AHB1ENR=0XF;
	RCC->APB2ENR|=(1<<14);

	GPIOB->PUPDR=0x2;
	GPIOC->MODER=0X5555555;
	
	SYSCFG->EXTICR[0]|=0x0001;
	EXTI -> IMR|=0X17;
	EXTI -> RTSR|=0X17;
	NVIC->ISER[0]=1UL<<6;
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock);
	
	while(1){
		
		__NOP();
			
	}
	
}