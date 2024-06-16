#include "Init.h"
#include "oled.h"
#include "i2c.h"

char Pal[12]={'|','T','A','L','L','E','R',' ','R','P','M','|'};
char var[12]={'R','P','M','=','>'};

void InitComponents(){
	RCC->AHB1ENR|=0xF;
	I2C_init();
	OLED_Init();
	SystemCoreClockUpdate();
	
}

void Interfaz_OLED(){
	OLED_Clear();

	OLED_DrawLine(5, 5, 123, 5, OLED_COLOR_WHITE);
	OLED_DrawLine(5, 5, 5, 60, OLED_COLOR_WHITE);
	OLED_DrawLine(5, 60, 123, 60, OLED_COLOR_WHITE);
	OLED_DrawLine(123, 5, 123, 60, OLED_COLOR_WHITE);
	OLED_GotoXY (25,10);
	OLED_Puts (Pal, &Font_7x10, 1);// titulo
	OLED_GotoXY (15,35);
	OLED_Puts (var, &Font_7x10, 1);
  OLED_UpdateScreen();
}

void InitInterrupt(){
	RCC -> APB2ENR |= (1UL<<14);
	GPIOA -> PUPDR |=0X200;
	EXTI -> RTSR =0X10;
	EXTI -> IMR  =0X10;
	SYSCFG -> EXTICR [1]=0X0000;   // pin 4 interupt; Puerto A
	NVIC_EnableIRQ(EXTI4_IRQn);	
}	

void Config_TIMER(){
	RCC->APB1ENR |=0x1    ; //Timer 2
	TIM2 -> CR1 =0X1;
	TIM2 ->DIER =0X1;
	TIM2 -> ARR=320;    //0.5seg ->   
	TIM2 -> PSC=50000;  // 25ms/8---3.125ms
	NVIC_EnableIRQ(TIM2_IRQn);
	
}
