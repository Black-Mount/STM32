// Código Ejemplo 9 2 //
// Archivo *.cpp //
#include "Pines.h"
 
// Definición de funciones apuntadoras a interrupción EXTI //
FunInt FunExti0=0,FunExti1=0,FunExti2=0,FunExti3=0,
FunExti4=0,FunExti5=0,FunExti6=0,FunExti7=0,FunExti8=0,
FunExti9=0,FunExti10=0,FunExti11=0,FunExti12=0,
FunExti13=0,FunExti14=0,FunExti15=0; 
 
//// Vectores de Interrupciones //
//extern "C"{
// // Vector interrupción EXTI0 y limpieza de bandera
// void EXTI0_IRQHandler(void){if(FunExti0!=0)FunExti0();EXTI->PR|=(1UL<<0);}
// // Vector interrupción EXTI1 y limpieza de bandera
// void EXTI1_IRQHandler(void){if(FunExti1!=0)FunExti1();EXTI->PR|=(1UL<<1);}
// // Vector interrupción EXTI2 y limpieza de bandera
// void EXTI2_IRQHandler(void){if(FunExti2!=0)FunExti2();EXTI->PR|=(1UL<<2);}
// // Vector interrupción EXTI3 y limpieza de bandera
// void EXTI3_IRQHandler(void){if(FunExti3!=0)FunExti3();EXTI->PR|=(1UL<<3);}
// // Vector interrupción EXTI4 y limpieza de bandera
// void EXTI4_IRQHandler(void){if(FunExti4!=0)FunExti4();EXTI->PR|=(1UL<<4);}
// // Vector interrupción EXTI 5 al 9 y limpieza de bandera
// void EXTI9_5_IRQHandler(void){
//  // Se evalúa bandera activa, ejecuta rutina y limpia banderas
//  if(EXTI->PR&(1UL<<5)){if(FunExti5!=0)FunExti5();EXTI->PR|=(1UL<<5);}
//  if(EXTI->PR&(1UL<<6)){if(FunExti6!=0)FunExti6();EXTI->PR|=(1UL<<6);}
//  if(EXTI->PR&(1UL<<7)){if(FunExti7!=0)FunExti7();EXTI->PR|=(1UL<<7);}
//  if(EXTI->PR&(1UL<<8)){if(FunExti8!=0)FunExti8();EXTI->PR|=(1UL<<8);}
//  if(EXTI->PR&(1UL<<9)){if(FunExti9!=0)FunExti9();EXTI->PR|=(1UL<<9);}
// }
// 
// // Vector interrupción EXTI 10 al 15 y limpieza de bandera
// void EXTI15_10_IRQHandler(void){
//  // Se evalúa bandera activa, ejecuta rutina y limpia banderas
//  if(EXTI->PR&(1UL<<10)){if(FunExti10!=0)FunExti10();EXTI->PR|=(1UL<<10);}
//  if(EXTI->PR&(1UL<<11)){if(FunExti11!=0)FunExti11();EXTI->PR|=(1UL<<11);}
//  if(EXTI->PR&(1UL<<12)){if(FunExti12!=0)FunExti12();EXTI->PR|=(1UL<<12);}
//  if(EXTI->PR&(1UL<<13)){if(FunExti13!=0)FunExti13();EXTI->PR|=(1UL<<13);}
//  if(EXTI->PR&(1UL<<14)){if(FunExti14!=0)FunExti14();EXTI->PR|=(1UL<<14);}
//  if(EXTI->PR&(1UL<<15)){if(FunExti15!=0)FunExti15();EXTI->PR|=(1UL<<15);}
// }
//}
 
// Método para usar función alternativa
void Pines::FuncionAlternativa(unsigned char p,unsigned char f){
 Pin(p); // Se asigna pin
 port->MODER|=(2UL<<pin*2); // Se define alternativo el pin
 if(pin<=7){ // Se evalúa la parte alta y baja de la AFR
  port->AFR[0]&=~(15UL<<pin*4); // Se borra la función
  port->AFR[0]|=((f&15UL)<<pin*4); // Se asigna la función
 }
 else{
  port->AFR[1]&=~(15UL<<(pin-8)*4); // Se borra la función
  port->AFR[1]|=((f&15UL)<<(pin-8)*4); // Se asigna la función
 }
}
 
void Pines::Pin(unsigned char p){ // Método para asignar pin a la clase
 // Evaluación del nibble superior que codifica el puerto
 // Esta estructura SW asigna al apuntador port el GPIO según el caso
 switch(p&0xF0){
  case 0x00:port=GPIOA;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;break;
  case 0x10:port=GPIOB;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;break;
  case 0x20:port=GPIOC;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;break;
  case 0x30:port=GPIOD;RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;break;
  case 0x40:port=GPIOE;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;break;
#if defined(STM32F746xx) 
  case 0x50:port=GPIOF;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;break;
  case 0x60:port=GPIOG;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;break;
#endif
 }
 // Evaluación del nibble inferior que codifica el pin
 pin=p&0x0F; // Numero de pin
 prt=(p>>4)&0x0F; // Numero de puerto
 mask1=(1UL<<pin); // Asignación de la máscara 1
 mask0=(1UL<<(pin+16)); // Asignación de la máscara 0
 // Las siguientes 5 líneas de código
 // configuran el pin como entrada digital
 port->MODER&=~(3UL<<pin*2);
 port->OTYPER&=~mask1;
 port->OSPEEDR&=~(3UL<<pin*2);
 port->OSPEEDR|=(3UL<<pin*2);
 port->PUPDR&=~(3UL<<pin*2);
}
 
void Pines::DigitalOut(unsigned char p){ // Método para hacer pin de salida
 Pin(p); // Método para asignar pin a la clase 
 port->MODER|=(1UL<<pin*2); // Se define de salida el pin
 SetPin(false); // Inicia en 0    
}

void Pines::DigitalOut(void){ // Método para hacer pin de salida
 DigitalOut((prt<<4)|pin);
}
 
// Método para hacer pin de salida con Open Drain 
void Pines::DigitalOutOpen(unsigned char p){
 DigitalOut(p); // Método para hacer pin de salida
 OpenDrain(); // Activa Open-Drain 
}
 
void Pines::OpenDrain(void){
 port->OTYPER|=mask1; // Activa Open-Drain 
}
 
void Pines::DigitalIn(unsigned char p){ // Método para hacer pin de entrada
 Pin(p); // Método para asignar pin a la clase
}
 
void Pines::DigitalIn(void){ // Método para hacer pin de entrada
 DigitalIn((prt<<4)|pin);
}
 
// Método para hacer pin de entrada con resistencia Pull-Up
void Pines::DigitalInUp(unsigned char p){
 Pin(p); // Método para asignar pin a la clase
 PullUp(); // Activa Pull-UP
}

void Pines::PullUp(void){
 port->PUPDR|=(1UL<<pin*2); // Activa Pull-UP
}
 
// Método para hacer pin de entrada con resistencia Pull-Down
void Pines::DigitalInDown(unsigned char p){
 Pin(p); // Método para asignar pin a la clase
 PullDown(); // Activa Pull-Down
}
 
void Pines::PullDown(void){
 port->PUPDR|=(2UL<<pin*2); // Activa Pull-Down
}
 
void Pines::Analogo(unsigned char p){ // Método para función análogo
 Pin(p); // Método para asignar pin a la clase
 port->MODER|=(3UL<<pin*2); // Se define pin análogo  
}
 
bool Pines::GetPin(void){ // Método para leer el estado lógico del pin
 // Se evalúa estado lógico del pin y se retorna 1 o 0
 if(port->IDR&mask1)return true;
 return false;
}
 
void Pines::SetPin(bool e){ // Método para asignar estado lógico al pin
 // Se asigna estado lógico en el pin 
 if(e)port->BSRR|=mask1;
 else port->BSRR|=mask0;
}
 
// Método para asignar interrupción
void Pines::Interrupcion(FunInt fun,bool ft,bool rt){
 // Activa reloj SYSCFG  
 RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN;
 EXTI->RTSR&=~mask1; // Apaga flanco de subida
 EXTI->FTSR&=~mask1; // Apaga flanco de bajada
 EXTI->IMR&=~mask1; // apaga interrupción
 if(!ft && !rt)return; // Retorna si no hay activación
 EXTI->IMR|=mask1; // Activa mascara interrupción
 if(rt)EXTI->RTSR|=mask1; // Activa flanco de subida
 if(ft)EXTI->FTSR|=mask1; // Activa flanco de bajada
 switch(pin&=0x0F){ // Evalúa pin fuente
  case 0x00:SYSCFG->EXTICR[0]&=0xFFF0; // Borra puerto
   SYSCFG->EXTICR[0]|=(prt<<0); // Asigna puerto 
   FunExti0=fun; // Asigna vector de interrupción 
   NVIC_EnableIRQ(EXTI0_IRQn); // Activa interrupción
   break;
  case 0x01:SYSCFG->EXTICR[0]&=0xFF0F; // Borra puerto
   SYSCFG->EXTICR[0]|=(prt<<4); // Asigna puerto 
   FunExti1=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI1_IRQn); // Activa interrupción
   break;
  case 0x02:SYSCFG->EXTICR[0]&=0xF0FF; // Borra puerto
   SYSCFG->EXTICR[0]|=(prt<<8); // Asigna puerto
   FunExti2=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI2_IRQn); // Activa interrupción
   break;
  case 0x03:SYSCFG->EXTICR[0]&=0x0FFF; // Borra puerto
   SYSCFG->EXTICR[0]|=(prt<<12); // Asigna puerto
   FunExti3=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI3_IRQn); // Activa interrupción
   break;
  case 0x04:SYSCFG->EXTICR[1]&=0xFFF0; // Borra puerto
   SYSCFG->EXTICR[1]|=(prt<<0); // Asigna puerto
   FunExti4=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI4_IRQn); // Activa interrupción
   break;
  case 0x05:SYSCFG->EXTICR[1]&=0xFF0F; // Borra puerto
   SYSCFG->EXTICR[1]|=(prt<<4); // Asigna puerto
   FunExti5=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI9_5_IRQn); // Activa interrupción
   break;
  case 0x06:SYSCFG->EXTICR[1]&=0xF0FF; // Borra puerto
   SYSCFG->EXTICR[1]|=(prt<<8); // Asigna puerto
   FunExti6=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI9_5_IRQn); // Activa interrupción
   break;
  case 0x07:SYSCFG->EXTICR[1]&=0x0FFF; // Borra puerto
   SYSCFG->EXTICR[1]|=(prt<<12); // Asigna puerto
   FunExti7=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI9_5_IRQn); // Activa interrupción
   break;
  case 0x08:SYSCFG->EXTICR[2]&=0xFFF0; // Borra puerto
   SYSCFG->EXTICR[2]|=(prt<<0); // Asigna puerto
   FunExti8=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI9_5_IRQn); // Activa interrupción
   break;
  case 0x09:SYSCFG->EXTICR[2]&=0xFF0F; // Borra puerto
   SYSCFG->EXTICR[2]|=(prt<<4); // Asigna puerto
   FunExti9=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI9_5_IRQn); // Activa interrupción
   break;
  case 0x0A:SYSCFG->EXTICR[2]&=0xF0FF; // Borra puerto
   SYSCFG->EXTICR[2]|=(prt<<8); // Asigna puerto
   FunExti10=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI15_10_IRQn); // Activa interrupción
   break;
  case 0x0B:SYSCFG->EXTICR[2]&=0x0FFF; // Borra puerto
   SYSCFG->EXTICR[2]|=(prt<<12); // Asigna puerto
   FunExti11=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI15_10_IRQn); // Activa interrupción
   break;
  case 0x0C:SYSCFG->EXTICR[3]&=0xFFF0; // Borra puerto
   SYSCFG->EXTICR[3]|=(prt<<0); // Asigna puerto
   FunExti12=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI15_10_IRQn); // Activa interrupción
   break;
  case 0x0D:SYSCFG->EXTICR[3]&=0xFF0F; // Borra puerto
   SYSCFG->EXTICR[3]|=(prt<<4); // Asigna puerto 
   FunExti13=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI15_10_IRQn); // Activa interrupción  
   break;
  case 0x0E:SYSCFG->EXTICR[3]&=0xF0FF; // Borra puerto
   SYSCFG->EXTICR[3]|=(prt<<8); // Asigna puerto 
   FunExti14=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI15_10_IRQn); // Activa interrupción
   break;
  case 0x0F:SYSCFG->EXTICR[3]&=0x0FFF; // Borra puerto
   SYSCFG->EXTICR[3]|=(prt<<12); // Asigna puerto
   FunExti15=fun; // Asigna vector de interrupción
   NVIC_EnableIRQ(EXTI15_10_IRQn); // Activa interrupción
   break; 
 }
}
 
bool Pines::operator = (bool e){ // Operador para igualar el pin a estado lógico
 SetPin(e); // Método para asignar estado lógico al pin
 return e; // retorno del estado lógico
}

Pines::operator bool(){ // Operador para leer el estado lógico del pin
 // Método para leer el estado lógico del pin
 // y retorno del valor lógico
 return GetPin();
}
 
bool Pines::operator = (Pines p){ // Operador para igualar el pin a otro pin
 // Método para leer el estado lógico del pin
 // y método para asignar estado lógico al pin
 SetPin( p.GetPin() );
 // retorno del valor configurado
 return GetPin();
}
 
void Pines::operator << (unsigned char p){ // Operador para definir pin de entrada
 DigitalIn(p); // Método para hacer pin de entrada
}
 
void Pines::operator >> (unsigned char p){ // Operador para definir pin de salida
 DigitalOut(p); // Método para hacer pin de salida
}
 
void Pines::operator << (int p){ // Operador para definir pin de entrada
 DigitalIn(p); // Método para hacer pin de entrada
}
 
void Pines::operator >> (int p){ // Operador para definir pin de salida
 DigitalOut(p); // Método para hacer pin de salida
}
 
bool Pines::operator & (bool e){ // Operador lógico AND
 return GetPin()&e;
}
 
bool Pines::operator | (bool e){ // Operador lógico OR
 return GetPin()|e;
}
 
bool Pines::operator ^ (bool e){ // Operador lógico XOR
 return GetPin()^e;
}
 
bool Pines::operator ! (void){ // Operador NOT;
 return !GetPin();
}
 
void Pines::operator &= (bool e){ // Operador lógico auto AND
 SetPin(GetPin()&e);
}
 
void Pines::operator |= (bool e){ // Operador lógico auto OR
 SetPin(GetPin()|e);
}
 
void Pines::operator ^= (bool e){ // Operador lógico auto XOR
 SetPin(GetPin()^e);
}
 
void Pines::operator >> (FunInt fun){ // Operador para asignar flanco subida
 Interrupcion(fun,0,1);
}
 
void Pines::operator << (FunInt fun){ // Operador para asignar flanco bajada
 Interrupcion(fun,1,0);
}
 
unsigned int HCLK(void){ // Función para identificar frecuencia del Core
 SystemCoreClockUpdate();
 return (unsigned int)SystemCoreClock;
}
 
unsigned int PCLK1(void){ // Función para identificar frecuencia APB1
 unsigned int PC;
 PC=HCLK(); // Leer frecuencia del Core
 // Evalúa pre-escala del PCLK1
 switch((RCC->CFGR>>RCC_CFGR_PPRE1_Pos)&7){
  case 4: PC/=2.0;break;
  case 5: PC/=4.0;break;
  case 6: PC/=8.0;break;
  case 7: PC/=16.0;break;
  default:break;
 }
 return PC; // Retorna PCLK1
}
 
unsigned int PCLK2(void){ // Función para identificar frecuencia APB2
 unsigned int PC;
 PC=HCLK(); // Leer frecuencia del Core
 // Evalúa pre-escala del PCLK2
 switch((RCC->CFGR>>RCC_CFGR_PPRE2_Pos)&7){
  case 4: PC/=2.0;break;
  case 5: PC/=4.0;break;
  case 6: PC/=8.0;break;
  case 7: PC/=16.0;break;
  default:break;
 }
 return PC; // Retorna PCLK2
}
