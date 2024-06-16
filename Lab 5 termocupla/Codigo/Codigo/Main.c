#include <stm32f4xx.h>
#include <stdio.h>
#include "oled.h"


char* celcius = "000";
char* kelvin = "000";
char* fahrenheit = "000";	
char dato_char1[4]; //Son usados para guardar la cadena de caracteres convertida
char dato_char2[4];
char dato_char3[4];


float TLM35=0;
float TCupla=0;
float KCupla=0;
float FCupla=0;

void InitADC();
void InitUSART();
void SendUSART();
void InitSPI();
void ReadLM35();
void ReadTermo();
void StartLCD();
void ShowLCD();

void delay (float ms){
	
	ms=ms*5333;
	for(int z=0;z<ms;z++){__ASM("NOP");}

}
void i2c_init(void){
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; 
RCC->APB1ENR|=RCC_APB1ENR_I2C1EN; 
GPIOB->MODER|=0xA0000; 
GPIOB->AFR[1]|=0x44;  
GPIOB->OTYPER|=GPIO_OTYPER_OT8|GPIO_OTYPER_OT9; 
I2C1->CR1=I2C_CR1_SWRST;
I2C1->CR1&=~I2C_CR1_SWRST;	
I2C1->CR2|=16;
I2C1->CCR|=0x2|(1<<15)|(1<<14); 
I2C1->TRISE=17; 
I2C1->CR1|=I2C_CR1_PE;
}


int main(void){
	RCC->AHB1ENR=0xF;
	GPIOC->MODER=0X5;
	i2c_init();
	oled_Init();
	InitADC();
	InitUSART();
	InitSPI();
	

	while(1){
		ReadLM35();
		ReadTermo();
		for(int i=0;i<=100000;i++){__ASM("NOP");}
		
		 sprintf(celcius, "%.2f", TCupla); //Toma el dato extraido de la coordenada, y ya que es tipo double, lo convierte a cadena de texto para mostrarlo en la OLED
	celcius=dato_char1; //Lo guarda en una variable usada para mostrarlo en la OLED
	
		 sprintf(kelvin, "%.2f", KCupla); //Lo mismo de arriba
	kelvin=dato_char2;
	
		 sprintf(fahrenheit, "%.2f", FCupla);
	fahrenheit=dato_char3;
		
		SSD1306_GotoXY (5, 5);
	SSD1306_Puts ("Temp (C): ", &Font_7x10, 1);
  SSD1306_GotoXY (5, 25);
	SSD1306_Puts ("Temp (K): ", &Font_7x10, 1);
	SSD1306_GotoXY (5, 45);
	SSD1306_Puts ("Temp (F): ", &Font_7x10, 1);
	SSD1306_UpdateScreen();
		
	SSD1306_GotoXY (75, 5); //Define la sección de la OLED
	SSD1306_Puts (celcius, &Font_7x10, 1); //Ahora, enviará a la oled la cadena de caracteres convertida del angulo que se está tomando
	SSD1306_GotoXY (75, 25); //Se repite
	SSD1306_Puts (kelvin, &Font_7x10, 1);
	SSD1306_GotoXY (75, 45);
	SSD1306_Puts (fahrenheit, &Font_7x10, 1);
	SSD1306_UpdateScreen(); //Actualiza la pantalla OLED	
		
		SendUSART();
	}
}

void InitUSART(void){
	GPIOA->MODER |= 0X280000;// PA(10-9)Alterno
	GPIOA->AFR[1]|=0X0770;//Tx,Rx
	RCC->APB2ENR|=1<<4;//Activar USART1
	USART1->BRR=0X684;//9600b/s
	USART1->CR1=0X212C;//Enable Usart, Tx,Rx, Interrupci?n Rx
	NVIC_EnableIRQ(USART1_IRQn);
}

void SendUSART(void){
	char x[10]={};
	sprintf(x,"%f",TCupla);
	//x[5]='C';
	for(int i=0;i<5;i++){
		USART1->DR=x[i];for(int i=0;i<=10000;i++){__ASM("NOP");}
	}
	USART1->DR=10;for(int i=0;i<=50000;i++){__ASM("NOP");}
	
}

void InitADC(void){
	RCC->APB2ENR |= 0X100; //HABILITAR EL ADC 1
	GPIOA->MODER |= 0X3;// PA(0) Análogo
	ADC1->SQR3 = 0; //CANAL 0 DEL ADC1
	ADC1->CR1 |= (0<<24); // 12 BITS DE RESOLUCIÓN
	ADC1->SMPR2|=7;//480 CICLOS
	ADC1->CR2 |= 1; // ENCENDIDO DEL ADC
}

void InitSPI(void){
  // Configurar los pines del SPI
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Habilitar el clock Puerto A
  GPIOA->MODER|=(2<<8)|(2<<10)|(2<<12)|(2<<14);//ALTERNO PA(4-7)
	GPIOA->AFR[0]|=(5<<16)|(5<<20)|(5<<24)|(5<<28);//ALTERNATE FUNCTION

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Habilitar el reloj de SPI1
	SPI1->CR1 |=1<<3;// Frecuencia de reloj a 2 MHz (baudrate = PCLK/4)
	SPI1->CR1 |= SPI_CR1_CPHA | SPI_CR1_CPOL; // Modo de reloj: fase 1 y polaridad alta
	SPI1->CR1 |= SPI_CR1_MSTR; // Modo maestro
	SPI1->CR2 |= SPI_CR2_SSOE; // Habilitar la salida automática de CS
	SPI1->CR1|=(1<<11);//Comunicación 16 Bits
	SPI1->CR1 |= SPI_CR1_SPE; // Habilitar el SPI 
}

void ReadLM35(void){
	ADC1->SQR3=0;//Canal 0
	ADC1->CR2|=(1<<30);
	if((ADC1->SR&2)==2){__ASM("NOP");}
	for(int i=0;i<=1000;i++){__ASM("NOP");}
	TLM35=(ADC1->DR)*8056/100000;
}

void ReadTermo(void){
	
	uint16_t data;

	GPIOC->ODR=0; // Bajar CS (activo bajo)
	data = SPI1->DR; // Limpiar el registro DR
	while (!(SPI1->SR & SPI_SR_TXE_Msk)); // Esperar a que el registro de transmisión esté vacío
	SPI1->DR = 0x00; // Iniciar Reloj
	while (!(SPI1->SR & SPI_SR_RXNE_Msk)); // Esperar a que se reciba el primer byte
	data = SPI1->DR;// Almacenar el primer byte recibido en los 8 bits más significativos
	GPIOC->ODR=1; // Subir CS
	
	if (data & 0x4) { // Verificar si se ha detectado un error en el MAX6675
			TCupla = 5; // Si hay un error, asignar NAN a la temperatura
	} else {
			data >>= 3; // Descartar los 3 bits menos significativos
			TCupla = data * 0.25; // Calcular la temperatura en grados Celsius
//			KCupla= TCupla + 273.15;
//			FCupla= (TCupla*(9/5))+32;
	}
}
