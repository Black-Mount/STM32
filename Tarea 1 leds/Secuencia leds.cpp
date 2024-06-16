#include "stm32f4xx.h"

int i,x; //Son las variables a utilizar para mover los datos
int pasado=0; //Es el estado inicial de la variable que cuenta la cantidad de veces que se presiona el botón
int leds[]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x100,0x200,0x400,0x800}; //Vector con las posiciones de los leds
int ledsalto[]={0x1,0x40,0x2,0x80,0x4,0x100,0x8,0x200,0x10,0x400,0x20,0x800};
int v1(void){for(x=0; x<500000;x++);return 0;}// delay de velocidad 1
int v2(void){for(x=0; x<300000;x++);return 0;}// delay de velocidad 2 
int v3(void){for(x=0; x<100000;x++);return 0;}// delay de velocidad 3


int configuracion (void) {
RCC->AHB1ENR=0x4; //Habilita el puerto c
GPIOC->MODER=0x555555; //Configura los pines C0 al C11 en salida, y el C13 en entrada
return 0;
}

int control (void) {
	if(!(GPIOC->IDR &(1UL<<13))) //Se evalua si el pulsador esta activo en bajo
	{
		pasado++;
		if(pasado==4){
		pasado=0;
		}
	}
if(pasado==1){
	
	
			for(i=0;i<12;i++){ // Es un ciclo para que ascienda en las posiciones de los vectores de led, y así generar el movimiento
			GPIOC->ODR=leds[i];
			v1();
			}	
			for (i=12;i>=0; i--) {	
			GPIOC->ODR=leds[i];
			v1();
			}			
			for(i=0;i<12;i++){
			GPIOC->ODR=ledsalto[i];
			v1();
			}	
			for (i=12;i>=0; i--) {	
			GPIOC->ODR=ledsalto[i];
			v1();
			}			
	}
if(pasado==2){
	
	
			for(i=0;i<12;i++){
			GPIOC->ODR=leds[i];
			v2();
			}	
			for (i=12;i>=0; i--) {	
			GPIOC->ODR=leds[i];
			v2();
			}			
			for(i=0;i<12;i++){
			GPIOC->ODR=ledsalto[i];
			v2();
			}	
			for (i=12;i>=0; i--) {	
			GPIOC->ODR=ledsalto[i];
			v2();
			}			
	}
if(pasado==3){
	
	
			for(i=0;i<12;i++){
			GPIOC->ODR=leds[i];
			v3();
			}	
			for (i=12;i>=0; i--) {	
			GPIOC->ODR=leds[i];
			v3();
			}			
			for(i=0;i<12;i++){
			GPIOC->ODR=ledsalto[i];
			v3();
			}	
			for (i=12;i>=0; i--) {	
			GPIOC->ODR=ledsalto[i];
			v3();
			}			
	}
	return 0;
}

int main(void)
{
	configuracion();
	while(1)
	{control();}
}
