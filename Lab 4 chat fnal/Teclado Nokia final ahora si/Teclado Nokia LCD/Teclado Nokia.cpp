#include "STM32F4xx.h"
#include <cmath>
#include <stdio.h>

char disp_on = 0x3F;
char disp_off = 0x3E;
char starL = 0xC0;
char setX = 0xB8;
char setY = 0x40;
int NUM[10]={32,32,32,32,32,32,32,32,32,32};
int u=0;
int c0=0, c1=0, c2=0, c3=0, c4=0, c5=0, c6=0, c7=0, c8=0, c9=0, compara=0, pulso=0;
char dato[] = {"Platano:"};
char dato2[] = {"Yo:"};
char recibido[]= {' ',' ',' ',' ',' ',' ',' ', ' ', ' ', ' '};
int numerito1 = 8;
int numerito2= 3;
char entrada;
char entrada2;
char entrada3;
char entrada4;
char entrada5;
int posmem = 0,habililec=0;

void CONT0 (void);
void CONT1 (void);
void CONT2 (void);
void CONT3 (void);
void CONT4 (void);
void CONT5 (void);
void CONT6 (void);
void CONT7 (void);
void CONT8 (void);
void CONT9 (void);

void configUsart(void){
	RCC->APB1ENR|=1<<17;//Activar USART2
	USART2->BRR=0X683;//9600b/s 
	GPIOA->AFR[0]|=0x7700;// Se configura el pin A3 para el af7=USART2, tx, rx
	USART2->CR1|=0X212C;//Enable Usart, Tx,Rx, Interrupci?n Rx
	USART2->CR1|=0x2D; //Interrupcion habiliatado Se habilita el tx, el rx y la interrupción del usart
	USART2->CR1|=0x2000;  //Activa el usart
	NVIC_EnableIRQ(USART2_IRQn);
	 USART2->CR1|=USART_CR1_RXNEIE; // Activa servicio de interrupción
}

void delay(int x){
	for(int i=0;i<x*500;i++){
      asm("nop");
  }
}

void send_comando(char a){
	GPIOC -> ODR = a|1UL<<9;
	for (int j=0;j<10000;j++){asm("nop");}
	GPIOC ->ODR &=~ (1UL<<9);
}

void send_dato(char b){
	GPIOC -> ODR = b|1UL<<8|1UL<<9;
	for (int j=0;j<10000;j++){asm("nop");}
	GPIOC ->ODR &=~ (1UL<<9);
}

void display (void){
	
	for (int j=0; j<10;j++){
		send_comando(0xC0+j); //80 primera linea, C0 segunda
		send_dato(NUM[j]);
		delay(50);
	
	}
	
}



void entrasale (void) {
	switch (compara) {
		
		case 0: 
			send_comando(0x01); //Limpiar el Display
		for(int i = 0; i<0x0+numerito2; i++){ //Envia letras de LCD
		send_dato(dato2[i]);
	  delay(1);}
		send_comando(0x80+numerito2); 
		break;

	}
}

void sendUsart(){
	
	if (pulso==1) {
		
		for (int i=0; i<10; i++) {
		USART2->DR=NUM[i]; ///Revisar
	delay(3000);
		
	}
	}
	
}
void asigNum(int x){		
		delay(30);
		NUM[u]=x;
		if (u==9){u=0;
		if (pulso==0) {
				pulso=1;
			}
		}
		display();
}

extern "C"{
	void EXTI0_IRQHandler(void){
		    delay(100);	
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&1;
					if(cl==1&&i==6){CONT7();}
					if(cl==1&&i==7){CONT4();}
					if(cl==1&&i==8){CONT1();}
					if(cl==1&&i==9){__NOP();}
				}
				delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;		
	}
	
	void EXTI1_IRQHandler(void){
		    delay(100);
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&2;
					if(cl==2&&i==6){CONT8();}
					if(cl==2&&i==7){CONT5();}
					if(cl==2&&i==8){CONT2();}
					if(cl==2&&i==9){CONT0();}
				}
				delay(3000);
				GPIOB->ODR=0x1E0;
				EXTI->PR=0XFFFF;
	}
	
	void EXTI2_IRQHandler(void){
				delay(100);
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&4;
					if(cl==4&&i==6){CONT9();}
					if(cl==4&&i==7){CONT6();}
					if(cl==4&&i==8){CONT3();}
					if(cl==4&&i==9){
					u++;
					c0=0;c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;}
				}
				delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;
				
	}
	
	void EXTI4_IRQHandler(void){
		if (compara==1) {
			
			}
				delay(100);
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&0x10;
					if(cl==16&&i==6){__NOP();}
					if(cl==16&&i==7){__NOP();}
					if(cl==16&&i==8){__NOP();}
					if(cl==16&&i==9){__NOP();}
				}
				delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;
	}
	void USART2_IRQHandler(void) /// Revisar
	{
		send_comando(0x01); //Limpiar el Display
		compara=1;
		send_comando(0x01); //Limpiar el Display
		if('%'== USART2->DR){
			posmem=0;
			habililec=1;
		}
		if(habililec == 1){
			recibido[posmem]=USART2->DR;
			posmem++;
		}
		if('#'== USART2->DR){
			habililec=0;
		
		for(int i = 0; i<0x0+numerito1; i++){ //Envia letras de LCD
		send_dato(dato[i]);
	  delay(1);}
		send_comando(0x80+numerito1); 	
			
		for (int j=1; j<10;j++){
		send_comando(0xC0+j); //80 primera linea, C0 segunda
		send_dato(recibido[j]);
		delay(50);
		
//	}
		
}
//    SystemCoreClockUpdate();
//			SysTick_Config(SystemCoreClock);
		
	}
}
}




int main (void){
	
	RCC -> AHB1ENR= 0xF;
	RCC -> APB2ENR|=(1<<14);
	GPIOC -> MODER = 0x55555555;
	GPIOB->MODER=0x15400;
	GPIOB->PUPDR=0X22A;
	GPIOA->MODER |= 0XA0;// PA(2-3)Alterno
	GPIOA->AFR[0]|=0X7700;//Tx,Rx
	
	SYSCFG->EXTICR[0]|=0x0111;
	SYSCFG->EXTICR[1]|=0x0001;
	EXTI -> IMR|=0X17;
	EXTI -> RTSR|=0X17;
	NVIC->ISER[0]=1UL<<6|1UL<<7|1UL<<8|1UL<<10;
	
	GPIOB->ODR=0X1E0;
	
	
	send_comando(0x38);		//2 lineas, 8 bits, 5x8
	send_comando(0x06);		//desplazamiento derecha
	send_comando(0xC);		//display prendido, cursor apagado, parpadeo apagado
	
			entrasale();	
	
	configUsart();
	
	
	while (true){		
		sendUsart();
		
	}
}


void CONT0 (void){
	c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c0++;
	switch (c0){
		case 1:
			asigNum(48);
			break;
		case 2:
			asigNum(32);
			break;
	}
	
		if (c0==2){c0=0;}
	
}
void CONT1 (void){

	c0=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c1++;
	switch (c1){
		case 1:
			asigNum(49);
			break;
		case 2:
			asigNum(97);
			break;
		case 3:
			asigNum(98);
			break;
		case 4:
			asigNum(99);
			break;
	}
	
		if (c1==4){c1=0;}
	
}

void CONT2 (void){
	c0=0; c1=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c2++;
	switch (c2){
		case 1:
			asigNum(50);
			break;
		case 2:
			asigNum(100);
			break;
		case 3:
			asigNum(101);
			break;
		case 4:
			asigNum(102);
			break;
	}
	
		if (c2==4){c2=0;}
	
}

void CONT3 (void){
	c0=0; c1=0; c2=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c3++;
	switch (c3){
		case 1:
			asigNum(51);
			break;
		case 2:
			asigNum(103);
			break;
		case 3:
			asigNum(104);
			break;
		case 4:
			asigNum(105);
			break;
	}
	
		if (c3==4){c3=0;}
	
}

void CONT4 (void){
	c0=0; c1=0; c2=0; c3=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c4++;
	switch (c4){
		case 1:
			asigNum(52);
			break;
		case 2:
			asigNum(106);
			break;
		case 3:
			asigNum(107);
			break;
		case 4:
			asigNum(108);
			break;
	}
	
		if (c4==4){c4=0;}
	
}

void CONT5 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c6=0; c7=0; c8=0; c9=0;
	c5++;
	switch (c5){
		case 1:
			asigNum(53);
			break;
		case 2:
			asigNum(109);
			break;
		case 3:
			asigNum(110);
			break;
		case 4:
			asigNum(111);
			break;
	}
	
		if (c5==4){c5=0;}
	
}

void CONT6 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c7=0; c8=0; c9=0;
	c6++;
	switch (c6){
		case 1:
			asigNum(54);
			break;
		case 2:
			asigNum(112);
			break;
		case 3:
			asigNum(113);
			break;
		case 4:
			asigNum(114);
			break;
	}
	
		if (c6==4){c6=0;}
	
}

void CONT7 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c8=0; c9=0;
	c7++;
	switch (c7){
		case 1:
			asigNum(55);
			break;
		case 2:
			asigNum(115);
			break;
		case 3:
			asigNum(116);
			break;
		case 4:
			asigNum(117);
			break;
	}
	
		if (c7==4){c7=0;}
	
}

void CONT8 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c9=0;
	c8++;
	switch (c8){
		case 1:
			asigNum(56);
			break;
		case 2:
			asigNum(118);
			break;
		case 3:
			asigNum(119);
			break;
		case 4:
			asigNum(120);
			break;
	}
	
		if (c8==4){c8=0;}
	
}

void CONT9 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0;
	c9++;
	switch (c9){
		case 1:
			asigNum(57);
			break;
		case 2:
			asigNum(121);
			break;
		case 3:
			asigNum(122);
			break;
	}
	
		if (c9==3){c9=0;}
	
}