#include <stm32f4xx.h>
#include <stdint.h>
#include <stdio.h>

float TCupla;

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

int main (void) {
	RCC->AHB1ENR|=0XF;
	GPIOC->MODER|=5;
	InitSPI();
	
	while (1) {
		
		ReadTermo();
		for(int i=0;i<=100000;i++){asm("nop");}
		
	}
	
}