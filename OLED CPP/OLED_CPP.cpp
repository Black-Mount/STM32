#include "OLED.h"
#include "stdio.h"

void delay(int ms){ms=ms*2000;
for(int z=0;z<ms;z++){__asm("NOP");}
}

char cont[10];
void i2c_init(void){
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; 
RCC->APB1ENR|=RCC_APB1ENR_I2C1EN; 
GPIOB->MODER|=0xA0000; 
GPIOB->PUPDR|=0x50000; 
GPIOB->AFR[1]|=0x44;  
GPIOB->OTYPER|=GPIO_OTYPER_OT8|GPIO_OTYPER_OT9; 
I2C1->CR1=I2C_CR1_SWRST;
I2C1->CR1&=~I2C_CR1_SWRST;	
I2C1->CR2|=16;  // reloj a 16MHz
I2C1->CCR|=(0<<15)|(0<<14)|(80<<0);  // SM 100Kbps
I2C1->TRISE=17; //output max rise 
I2C1->CR1|=I2C_CR1_PE;
}


int main(void){
  i2c_init();
  oled_Init();
	RCC->AHB1ENR|=7;
	SSD1306_GotoXY (5, 5);
	SSD1306_Puts ("UMNG", &Font_16x26, 0);
  SSD1306_GotoXY (30, 35);
	SSD1306_Puts ("MICROS", &Font_16x26, 0);
	SSD1306_UpdateScreen();
	delay (3000);	delay (3000);
while(1){
	SSD1306_Clear();
	SSD1306_GotoXY (20, 10);
	SSD1306_Puts ("CONTEO", &Font_16x26, 0);
	SSD1306_UpdateScreen(); 
	for (int i=0; i<100;i++){
		while(GPIOC->IDR&0X2000){__asm("NOP");}
		delay (500);
		while(!GPIOC->IDR&0X2000){__asm("NOP");}
		sprintf(cont,"= %i",i);
		SSD1306_GotoXY (40, 37);	
		SSD1306_Puts (cont, &Font_16x26, 1);
		SSD1306_UpdateScreen();
  }
 }
}