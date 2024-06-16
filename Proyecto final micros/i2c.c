#include "i2c.h"


void I2C_init(void){
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; 
	RCC->APB1ENR|=RCC_APB1ENR_I2C1EN; 
	GPIOB->MODER|=0xA0000; 
	GPIOB->AFR[1]|=0x44;  
	GPIOB->OTYPER|=GPIO_OTYPER_OT8|GPIO_OTYPER_OT9; 
	I2C1->CR1=I2C_CR1_SWRST;
	I2C1->CR1&=~I2C_CR1_SWRST;	
	I2C1->CR2|=42;
	I2C1->CCR|=0x2|(1<<15)|(1<<14); 
	I2C1->TRISE=20; //output max rise 
	I2C1->CR1|=I2C_CR1_PE;
}

void I2C_writeByte(char saddr,char maddr,char data){
	volatile int Tempo;
	while(I2C1->SR2&I2C_SR2_BUSY){;}         
	I2C1->CR1|=I2C_CR1_START;                
	while(!(I2C1->SR1&I2C_SR1_SB)){;}        
	I2C1->DR = saddr<< 1;                
	while(!(I2C1->SR1&I2C_SR1_ADDR)){;}    
	Tempo = I2C1->SR2; 											
	while(!(I2C1->SR1&I2C_SR1_TXE)){;}      
	I2C1->DR = maddr;                        
	while(!(I2C1->SR1&I2C_SR1_TXE)){;}     
	I2C1->DR = data; 	
	while (!(I2C1->SR1 & I2C_SR1_BTF));     
	I2C1->CR1 |=I2C_CR1_STOP;								
}

void I2C_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length){
	volatile int Tempo;
	while (I2C1->SR2 & I2C_SR2_BUSY);           
	I2C1->CR1 |= I2C_CR1_START;                   
	while (!(I2C1->SR1 & I2C_SR1_SB)){;}				
															
	I2C1->DR = saddr<< 1;                 	 			
	while (!(I2C1->SR1 & I2C_SR1_ADDR)){;}       
	Tempo = I2C1->SR2; 						                 
	while (!(I2C1->SR1 & I2C_SR1_TXE));          
	I2C1->DR = maddr;                      			
	while (!(I2C1->SR1 & I2C_SR1_TXE));         
	for (uint8_t i=0;i<length;i++) { 
	I2C1->DR=buffer[i]; 												
	while (!(I2C1->SR1 & I2C_SR1_BTF));
	}														
	I2C1->CR1 |= I2C_CR1_STOP;										
}

