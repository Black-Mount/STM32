#include "STM32F4xx.h"
#include "OLED.h"
#include "stdio.h"
#define LEDON GPIOB->ODR^=0x1;
int cont=0;
int recibido=0, recibido2=0;
uint8_t RxData[100];
int flag=0;
char* p;


void TIM3_init(void){				//Inicialización del TIMER3
	
	TIM3 -> PSC =15;					//Prescaler con una frecuencia de 1MHz
	TIM3 -> ARR = 20000;			//Una frecuencia máxima de PWM de 20ms
	
	TIM3 -> CR1|= (1UL<<0);		
	TIM3 -> CCMR1 = 0x60;			//Modo PWM
	TIM3 -> CCER = (1UL<<0);
	TIM3 -> CCR1 = 1200;			//Inicio del PWM
	
}

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

void delay (int ms){
	
	ms=ms*5000;
	for(int z=0;z<ms;z++){__ASM("NOP");}

}

void ServoWrite(int ang){		//Función que si se le introduce un angulo especifico el servomotor MG995 se mueve esa cantidad de grados
	float tem=0;
	
	if (ang<0){
		ang=0;
	}else if(ang>120){
		ang=120;
	}
	tem=(8.333*ang)+1000;
	
	TIM3 -> CCR1 = tem;
	delay(20);
}

void USART1_Config(void){
	GPIOA->MODER |= 0X280000;// PA(10-9)Alterno
	GPIOA->AFR[1]|=0X0770;//Tx,Rx
	RCC->APB2ENR|=1<<4;//Activar USART1
	USART1->BRR=0X684;//9600b/s
	USART1->CR1=0X212C;//Enable Usart, Tx,Rx,
	NVIC_EnableIRQ(USART1_IRQn);
}
void levantamiento (void){	//Función de ascensión
	
	SSD1306_GotoXY (5, 35);
	SSD1306_Puts ("SUBE", &Font_16x26, 1);
	SSD1306_UpdateScreen();
	
	for (int i=0;i<121;i++){	
		ServoWrite(i);
		delay(30);
	}
	
}

void descenso (void){				//Función de descenso
	
	SSD1306_GotoXY (5, 35);
	SSD1306_Puts ("BAJA", &Font_16x26, 1);
	SSD1306_UpdateScreen();
	
	for (int i=120;i>=0;i--){
		ServoWrite(i);
		delay(30);
	}
}

void fun1 (void){						//Si se llama una vez a esta función se realiza un levantamiento del peso y se mantiene en el aire, una segunda llamada desciende
	
	SSD1306_GotoXY (5, 35);
	SSD1306_Puts ("         ", &Font_16x26, 1);
	SSD1306_UpdateScreen(); 
	
	if (cont==0){
		levantamiento();
		cont++;
	}
	else {
		descenso();
		cont=0;
	}
	SSD1306_GotoXY (5, 35);
	SSD1306_Puts ("NEUTRO", &Font_16x26, 1);
	SSD1306_UpdateScreen(); 
	
}

void fun2 (void){						//levantamiento rápido, consta de ascenso y descenso rápidamente
	
	SSD1306_GotoXY (5, 35);
	SSD1306_Puts ("         ", &Font_16x26, 1);
	SSD1306_UpdateScreen(); 
	
	if(cont==1){__NOP();}
	else{
		levantamiento();
		delay(80);
		descenso();
		delay(80);
	}

	SSD1306_GotoXY (5, 35);
	SSD1306_Puts ("NEUTRO", &Font_16x26, 1);
	SSD1306_UpdateScreen(); 

}


extern "C" {
	
	void USART1_IRQHandler(void)
	{
		recibido=USART1->DR; //Lee dato recibido
		if (recibido==50) { //Recibe un uno en ASCII
			fun2();
		}
		if (recibido==49) { //Recibe un dos en ASCII
			fun1();
		}
		
	}
	

}
int main (void){
	RCC -> AHB1ENR = 0xF;
	RCC -> APB1ENR |= 2;
	TIM3_init();
	USART1_Config();
	GPIOA -> MODER |= 0x2000;
	GPIOA -> AFR[0] = 0x2000000;
	GPIOB -> MODER = 0x5;
	
	GPIOC->PUPDR=(1UL<<26); //Pull Up PC13

	
	ServoWrite(0);
	
	i2c_init();
  oled_Init();
	
	SSD1306_GotoXY (5, 5);
	SSD1306_Puts ("STATUS:", &Font_16x26, 1); //Muestra el estado en el que se encuentra la polea mientras se está moviendo
	SSD1306_UpdateScreen(); 
	
	SSD1306_GotoXY (5, 35);
	SSD1306_Puts ("NEUTRO", &Font_16x26, 1);
	SSD1306_UpdateScreen(); 
	
	while (true){
		
		__NOP();
		
		
		
	}
}