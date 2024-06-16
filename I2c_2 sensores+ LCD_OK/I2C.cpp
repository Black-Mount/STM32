#include "stm32f4xx.h"                  // Device header
#include "I2C.h"												//Devoce by david :D
char I2CRead(char address,char registry ){
	//while(!(I2C1->SR2 & I2C_SR2_BUSY));		// Wait for BUSY line
	I2C1->CR1 |= I2C_CR1_START;				// Generate START condition

	while (!(I2C1->SR1 & I2C_SR1_SB)){}; 		// Wait for EV5
	I2C1->DR = address;					// Write device address (W)

	while (!(I2C1->SR1 & I2C_SR1_ADDR)){};	// Wait for EV6
  (void)I2C1->SR2;						// Read SR2

	while (!(I2C1->SR1 & I2C_SR1_TXE));		// Wait for EV8_1
	I2C1->DR = registry;

	I2C1->CR1 |= I2C_CR1_STOP;				// Generate STOP condition


	I2C1->CR1 |= I2C_CR1_START;				// Generate START condition

	while (!(I2C1->SR1 & I2C_SR1_SB)); 		// Wait for EV5
	I2C1->DR = (address  ) | 1;			// Write device address (R)

	while (!(I2C1->SR1 & I2C_SR1_ADDR)){};	// Wait for EV6
    I2C1->CR1 &= ~I2C_CR1_ACK;              // No ACK
    (void)I2C1->SR2;						// Read SR2

	while (!(I2C1->SR1 & I2C_SR1_RXNE)){};	// Wait for EV7_1
    char value = (char)I2C1->DR;      // Read value
		I2C1->CR1 |=I2C_CR1_ACK;
    I2C1->CR1 |= I2C_CR1_STOP;			    // Generate STOP condition

	return value;
}

void I2CWriteOneBuff(char address, uint8_t registry ){
	I2C1->CR1 |= I2C_CR1_START;				// Generate START condition
	while (!(I2C1->SR1 & I2C_SR1_SB)); 		// Wait for EV5
	I2C1->DR = address;					// Write device address (W)

	while (!(I2C1->SR1 & I2C_SR1_ADDR)){};	// Wait for EV6
    (void)I2C1->SR2;						// Read SR2

	while (!(I2C1->SR1 & I2C_SR1_TXE));		// Wait for EV8_1
	I2C1->DR = registry;					// Write registry address

	while (!(I2C1->SR1 & I2C_SR1_BTF));	    // Wait for BTF
	//I2C1->DR = registry;
	I2C1->CR1 &= ~I2C_CR1_ACK;              // No ACK
	I2C1->CR1 |= I2C_CR1_STOP;			    // Generate STOP condition
}
void I2CWrite  (char address, char registry, char data){
	I2C1->CR1 |= I2C_CR1_START;				// Generate START condition

	while (!(I2C1->SR1 & I2C_SR1_SB)); 		// Wait for EV5
	I2C1->DR = address;					// Write device address (W)

	while (!(I2C1->SR1 & I2C_SR1_ADDR)){};	// Wait for EV6
    (void)I2C1->SR2;						// Read SR2

	while (!(I2C1->SR1 & I2C_SR1_TXE));		// Wait for EV8_1
	I2C1->DR = registry;					// Write registry address

	while (!(I2C1->SR1 & I2C_SR1_BTF));	    // Wait for BTF
	I2C1->DR = data;

	I2C1->CR1 |= I2C_CR1_STOP;			    // Generate STOP condition
}




void IniciarI2C(void){
	RCC->APB1ENR |= (1Ul << 21); //Clk I2C1 EN
	I2C1->CCR &= ~I2C_CCR_CCR;
	I2C1->CR2 &= ~(I2C_CR2_FREQ);
	I2C1->CR2 |= 0b000010;
	I2C1->CCR |= 80;
	I2C1->TRISE |= 3;
	I2C1->CR1 |= 0x0001;
	GPIOB->MODER |= 0xA000; // Funciones especiales P7 y P6
	GPIOB->AFR[0] |= 0x44000000; // canales F4 para P6 y P7
	GPIOB->PUPDR |= 0xA000; //para I2C
	GPIOB->OSPEEDR |= 0;;
	GPIOB->OTYPER |= 0xC0;//para I2C
}
