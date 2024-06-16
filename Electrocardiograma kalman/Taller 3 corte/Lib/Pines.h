// Código Ejemplo 9 1 //
// Archivo *.h //
#ifndef _PINES_H
#define _PINES_H
 
#if defined (STM32F401xE) // Adición de librerías micro F401
 #include "stm32f401xE.h"
#endif
#if defined(STM32F746xx) // Adición de librerías micro F746
 #include "stm32f746xx.h"
#endif
 
#include <stdlib.h> // Estándar de librerías 
#include <stdio.h> // Estándar de entradas y salidas
 
// DEFINICIONES DE PINES //
#define PA0   0x00
#define PA1   0x01
#define PA2   0x02
#define PA3   0x03
#define PA4   0x04
#define PA5   0x05
#define PA6   0x06
#define PA7   0x07
#define PA8   0x08
#define PA9   0x09
#define PA10  0x0A
#define PA11  0x0B
#define PA12  0x0C
#define PA13  0x0D
#define PA14  0x0E
#define PA15  0x0F
#define PB0   0x10
#define PB1   0x11
#define PB2   0x12
#define PB3   0x13
#define PB4   0x14
#define PB5   0x15
#define PB6   0x16
#define PB7   0x17
#define PB8   0x18
#define PB9   0x19
#define PB10  0x1A
#define PB11  0x1B
#define PB12  0x1C
#define PB13  0x1D
#define PB14  0x1E
#define PB15  0x1F
#define PC0   0x20
#define PC1   0x21
#define PC2   0x22
#define PC3   0x23
#define PC4   0x24
#define PC5   0x25
#define PC6   0x26
#define PC7   0x27
#define PC8   0x28
#define PC9   0x29
#define PC10  0x2A
#define PC11  0x2B
#define PC12  0x2C
#define PC13  0x2D
#define PC14  0x2E
#define PC15  0x2F
#define PD0   0x30
#define PD1   0x31
#define PD2   0x32
#define PD3   0x33
#define PD4   0x34
#define PD5   0x35
#define PD6   0x36
#define PD7   0x37
#define PD8   0x38
#define PD9   0x39
#define PD10  0x3A
#define PD11  0x3B
#define PD12  0x3C
#define PD13  0x3D
#define PD14  0x3E
#define PD15  0x3F
#define PE0   0x40
#define PE1   0x41
#define PE2   0x42
#define PE3   0x43
#define PE4   0x44
#define PE5   0x45
#define PE6   0x46
#define PE7   0x47
#define PE8   0x48
#define PE9   0x49
#define PE10  0x4A
#define PE11  0x4B
#define PE12  0x4C
#define PE13  0x4D
#define PE14  0x4E
#define PE15  0x4F
#define PF0   0x50
#define PF1   0x51
#define PF2   0x52
#define PF3   0x53
#define PF4   0x54
#define PF5   0x55
#define PF6   0x56
#define PF7   0x57
#define PF8   0x58
#define PF9   0x59
#define PF10  0x5A
#define PF11  0x5B
#define PF12  0x5C
#define PF13  0x5D
#define PF14  0x5E
#define PF15  0x5F
#define PG0   0x60
#define PG1   0x61
#define PG2   0x62
#define PG3   0x63
#define PG4   0x64
#define PG5   0x65
#define PG6   0x66
#define PG7   0x67
#define PG8   0x68
#define PG9   0x69
#define PG10  0x6A
#define PG11  0x6B
#define PG12  0x6C
#define PG13  0x6D
#define PG14  0x6E
#define PG15  0x6F
    
// Definiciones morfología Arduino Uno F401
#if defined (STM32F401xE)
#define AP0 PA0
#define AP1 PA1
#define AP2 PA4
#define AP3 PB0
#define AP4 PC1
#define AP5 PC0
#define DP0 PA3
#define DP1 PA2
#define DP2 PA10
#define DP3 PB3
#define DP4 PB5
#define DP5 PB4
#define DP6 PB10
#define DP7 PA8
#define DP8 PA9
#define DP9 PC7
#define DP10 PB6
#define DP11 PA7
#define DP12 PA6
#define DP13 PA5
#define DP14 PB9
#define DP15 PB8
#endif
 
// Definiciones morfología Arduino Uno F746
#if defined(STM32F746xx)
#define AP0 PA3
#define AP1 PC0
#define AP2 PC3
#define AP3 PF3
#define AP4 PF5
#define AP5 PF10
#define DP0 PG9
#define DP1 PG14
#define DP2 PF15
#define DP3 PE13
#define DP4 PF14
#define DP5 PE11
#define DP6 PE9
#define DP7 PF13
#define DP8 PF12
#define DP9 PD15
#define DP10 PD14
#define DP11 PA7
#define DP12 PA6
#define DP13 PA5
#define DP14 PB9
#define DP15 PB8
#endif 
 
// Definiciones seriales Arduino
#define SPI_CLK DP13
#define SPI_MISO DP12
#define SPI_MOSI DP11
 
#define I2C_SCL DP15
#define I2C_SDA DP14
 
#define USART_TX DP1
#define USART_RX DP0
 
// Definición de apuntador a función //
typedef void (*FunInt)(void);
typedef void (*FunInt2)(unsigned char d);
 
// Clase Pines //
class Pines{
private: // Declaraciones privadas
public:
 GPIO_TypeDef * port; // Apuntador a GPIO
 unsigned char pin,prt; // variable para guardar pin asociado
 // Variables para guardar las mascara de activación 1 y 0
 unsigned int mask1, mask0; 
 void Pin(unsigned char p); // Método para asignar pin a la clase
 // Método para usar función alternativa
 void FuncionAlternativa(unsigned char p,unsigned char f);
 void DigitalOut(unsigned char p); // Método para hacer pin de salida
 void DigitalOut(void); // Método para hacer pin de salida
 // Método para hacer pin de salida con open drain
 void DigitalOutOpen(unsigned char p);
 void OpenDrain(void);
 void DigitalIn(unsigned char p); // Método para hacer pin de entrada
 void DigitalIn(void); // Método para hacer pin de entrada
 // Método para hacer pin de entrada con resistencia Pull-Up
 void DigitalInUp(unsigned char p);
 void PullUp(void);
 // Método para hacer pin de entrada con resistencia Pull-Down
 void DigitalInDown(unsigned char p);
 void PullDown(void);
 void Analogo(unsigned char p); // Método para función análogo
 bool GetPin(void); // Método para leer el estado lógico del pin
 void SetPin(bool e); // Método para asignar estado lógico al pin
 void Interrupcion(FunInt fun,bool ft,bool rt); // Método para asignar interrupción
 bool operator = (bool e); // Operador para igualar el pin a estado lógico
 operator bool(); // Operador para leer el estado lógico del pin
 bool operator = (Pines p); // Operador para igualar el pin a otro pin
 void operator << (unsigned char p); // Operador para definir pin de entrada
 void operator >> (unsigned char p); // Operador para definir pin de salida
 void operator << (int p); // Operador para definir pin de entrada
 void operator >> (int p); // Operador para definir pin de salida
 bool operator & (bool e); // Operador lógico AND
 bool operator | (bool e); // Operador lógico OR
 bool operator ^ (bool e); // Operador lógico XOR
 bool operator ! (void); // Operador NOT; 
 void operator &= (bool e); // Operador lógico auto AND 
 void operator |= (bool e); // Operador lógico auto OR
 void operator ^= (bool e); // Operador lógico auto XOR
 void operator >> (FunInt fun); // Operador para asignar flanco subida
 void operator << (FunInt fun); // Operador para asignar flanco bajada
};
 
unsigned int HCLK(void); // Función para identificar frecuencia del Core
unsigned int PCLK1(void); // Función para identificar frecuencia APB1
unsigned int PCLK2(void); // Función para identificar frecuencia APB2
#endif
