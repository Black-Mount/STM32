#include <stm32f4xx.h>
#include <stdio.h>
#include "LCD.h"
LCD LCD1;


float TLM35=0;
float TCupla=0;

void InitADC();
void InitUSART();
void SendUSART();
void InitSPI();
void ReadLM35();
void ReadTermo();
void StartLCD();
void ShowLCD();



int main(void){
	RCC->AHB1ENR=0xF;
	GPIOC->MODER=0X5;
	LCD1.Config();
	LCD1.Clear();
	InitADC();
	InitUSART();
	InitSPI();
	StartLCD();
	while(1){
		ReadLM35();
		ReadTermo();
		for(int i=0;i<=100000;i++){asm("nop");}
		ShowLCD();
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
		USART1->DR=x[i];for(int i=0;i<=10000;i++){asm("nop");}
	}
	USART1->DR=10;for(int i=0;i<=50000;i++){asm("nop");}
	
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
	if((ADC1->SR&2)==2){asm("nop");}
	for(int i=0;i<=1000;i++){asm("nop");}
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
	}
}

void StartLCD(void){
	char LM[]={'L','M','3','5',':'};
	char Termo[]={'T','C','U',':','L'};
	LCD1.Set(LCD1.SetL1);
	LCD1.WriteWord(LM,0,5);
	LCD1.Set(LCD1.SetL1+10);
	LCD1.WriteWord(Termo,0,4);
}

void ShowLCD(void){
	char xd[10]={0};
	sprintf(xd,"%f",TLM35);
	LCD1.Set(LCD1.SetL2);
	LCD1.WriteWord(xd,0,4);
	LCD1.WriteLetter('C');
	sprintf(xd,"%f",TCupla);
	LCD1.Set(LCD1.SetL2+10);
	LCD1.WriteWord(xd,0,5);
	LCD1.WriteLetter('C');
}

