//Codigo ejemplo Hola mundo//

#include "stm32f401xe.h"
int main(void)
{
//Configuracion de pines
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN; //Reloj activo para el puerto C.
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; //Reloj activo para el puerto A.
GPIOA->MODER|= (1UL<<10); //Modo salida Pin PA5
while(1) //Bucle infinito
{
if(!(GPIOC->IDR &(1UL<<13))) //Se evalua si el pulsador esta activo en bajo
GPIOA->ODR=32;
else
GPIOA->ODR=0;
}
return 0;
}