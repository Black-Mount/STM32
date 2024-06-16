#include "stm32f4xx.h"
#include "config.h"
#include "Init.h"
#include "oled.h"
#include "i2c.h"


char Pal[20]={'|','-','B','A','N','D','A',' ','T','R','A','N','S','P','O','R','T','-','|'};
//char var[12]={'R','P','M','=','>'};
char PM1[9]={'T','A','N','Q','U','E',' ','1',' '};
char PM2[9]={'T','A','N','Q','U','E',' ','2',' '};
char VEL[9]={'M','O','D','O',' ','V','E','L',':'};


void Interfaz_OLED(){
	OLED_Clear();

	OLED_DrawLine(5, 5, 123, 5, OLED_COLOR_WHITE);
	OLED_DrawLine(5, 5, 5, 60, OLED_COLOR_WHITE);
	OLED_DrawLine(5, 60, 123, 60, OLED_COLOR_WHITE);
	OLED_DrawLine(123, 5, 123, 60, OLED_COLOR_WHITE);
	OLED_GotoXY (8,10);
	OLED_Puts (Pal, &Font_6x8, 0);// titulo
	OLED_GotoXY (15,22);
	OLED_Puts (VEL, &Font_6x8, 1);
	OLED_GotoXY (13,38);
	OLED_Puts (PM1, &Font_6x8, 1);
	OLED_GotoXY (69,38);
	OLED_Puts (PM2, &Font_6x8, 1);
	
	  OLED_DrawLine(5, 34, 123, 34, OLED_COLOR_WHITE);
		OLED_DrawLine(63, 34, 63, 60, OLED_COLOR_WHITE);
	  OLED_DrawLine(64, 34, 64, 60, OLED_COLOR_WHITE);
  OLED_UpdateScreen();
}

void configP(){
	RCC-> AHB1ENR |= 0xF;
	I2C_init();
	OLED_Init();
}
void PWM (){
	RCC-> APB1ENR |= 0x2; //TIM3
  GPIOA-> MODER |= 0xA000;	//PA6 OUT
	GPIOA-> AFR[0] = 0x22000000;
  
	TIM3-> EGR  |=1;
	TIM3-> PSC   =15; //señal de 1MHz//aumento de conteo =1us
  TIM3-> ARR   =20000; // peiodo de 20ms
	TIM3-> DIER |=1;
	TIM3-> CR1  |=1;
	TIM3-> CCMR1 =0x6060;
	TIM3-> CCER |=1;
	TIM3-> CCER |=1<<4;
	TIM3-> CCR1  =2000;
	TIM3-> CCR2  =2000;
}
