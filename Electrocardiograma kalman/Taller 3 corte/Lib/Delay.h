// Código Ejemplo 5 42//
// Archivo *.h //
#ifndef _DELAY_H
#define _DELAY_H
#if defined (STM32F401xE) // Adición de librerías micro F401
 #include "stm32f401xE.h"
#endif
#if defined(STM32F746xx) // Adición de librerías micro F746
 #include "stm32f746xx.h"
#endif
// Función para iniciar servicios de los retardos
void IniciarDelay(void);
void Delay_us(unsigned int t); // Retardo en microsegundos
void Delay_ms(unsigned int t); // Retardo en milisegundos
void delay(unsigned int t); // Retardo en milisegundos
void delayMicroseconds(unsigned int t); // Retardo en microsegundos
#endif

