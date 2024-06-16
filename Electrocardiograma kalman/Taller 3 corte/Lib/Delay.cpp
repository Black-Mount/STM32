// Código Ejemplo 5 43//
// Archivo *.cpp //
#include "Delay.h"

// Función para iniciar servicios de los retardos
void IniciarDelay(void){
 SystemCoreClockUpdate(); // Actualiza valor de reloj
#if defined (__CORE_CM7_H_GENERIC)
 DWT->LAR=0xC5ACCE55; // Se activa acceso en Core 7
#endif
 // Se activan funciones del Debug
 CoreDebug->DEMCR|=CoreDebug_DEMCR_TRCENA_Msk;
 // Se activa contador de ciclos de reloj
 DWT->CTRL|=DWT_CTRL_CYCCNTENA_Msk;
}
 
void Delay_us(unsigned int t){ // Retardo en microsegundos
 // Se calcula la cuenta de ciclos en microsegundos
 unsigned int N=t*(SystemCoreClock/1000000.0);
 DWT->CYCCNT=0; // Se reinicia el contador
 while(DWT->CYCCNT<N); // Se cuentan ciclos
}
 
void delayMicroseconds(unsigned int t){ // Retardo en microsegundos
 // Se calcula la cuenta de ciclos en microsegundos
 unsigned int N=t*(SystemCoreClock/1000000.0);
 DWT->CYCCNT=0; // Se reinicia el contador
 while(DWT->CYCCNT<N); // Se cuentan ciclos
}
 
void Delay_ms(unsigned int t){ // Retardo en milisegundos
 // Se calcula la cuenta de ciclos en milisegundos
 unsigned int N=t*(SystemCoreClock/1000.0);
 DWT->CYCCNT=0; // Se reinicia el contador
 while(DWT->CYCCNT<N); // Se cuentan ciclos
}
 
void delay(unsigned int t){ // Retardo en milisegundos
 // Se calcula la cuenta de ciclos en milisegundos
 unsigned int N=t*(SystemCoreClock/1000.0);
 DWT->CYCCNT=0; // Se reinicia el contador
 while(DWT->CYCCNT<N); // Se cuentan ciclos
}
