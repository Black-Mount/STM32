#include "stm32f4xx.h"
#include "math.h"
#include "stdio.h"

char clear_Display = 0X01; 
char return_Home = 0x02;
char move_cursor_right = 0x06;
char move_cursor_left = 0X04;
char move_display_right = 0X05;
char move_display_left = 0X7;
char cursor_parpadeo = 0X0F;   //Display ON
char cursor_no_parpadeo = 0XC; //Display ON
char cursor_no_parpadeo_off = 0XE; //Display ON
char set_8bits = 0X38; //8 bits dos lineas
char set_4bits = 0X28; //4 bits dos lineas
char ddram1L = 0X80; //Posición 00 en la primera fila
char ddram2L = 0XC0; //Posición 40 en segunda fila
int correg_dato_izq = 0X10; //Desplaza el cursor a la izquierda sin leer o escribir
int correg_dato_der= 0X14; //Desplaza el cursor a la derecha sin leer o escribir
char envio;
char entrada;
char dato[] = {"Platano:"};
char dato2[] = {"Yo:"};
char dato3[]= {};
int NUM[10]={32,32,32,32,32,32,32,32,32,32};
int u=0;
int c0=0, c1=0, c2=0, c3=0, c4=0, c5=0, c6=0, c7=0, c8=0, c9=0, compara=0;

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


int numerito1 = 8;
int numerito2= 3;
int numerito3=10;

void Delay(int x){
for(int i=0;i<x*500;i++){
      asm("nop");
	}
}
void send_comand(char n1){
	GPIOC ->ODR &= 0XFF00;
	GPIOC ->ODR |= n1;
	GPIOC ->ODR &= ~(1UL<<8);//RS=0
	GPIOC ->ODR |= (1UL<<9); // Enable 1
	Delay(10); 
	GPIOC ->ODR &= ~(1UL<<9); // Enable 0
}

void send_dato(char n1){
	GPIOC ->ODR &=0XFF00;
	GPIOC ->ODR |= n1;	
	GPIOC->ODR |=(1UL<<8);//RS=1
	GPIOC->ODR |=(1UL<<9); // Enable 1
	Delay(10);
	GPIOC->ODR &=~(1UL<<9); // Enable 0
}

void asigNum(int x){		
		Delay(10);

		if (x==1000){
			u++;
			c0=0;c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
		}
		NUM[u]=x;
		if (u==10){u=0;}
}
void configUsart(void){
	RCC->APB1ENR|=1<<17;//Activar USART2
	USART2->BRR|=0X683;//9600b/s
	USART2->CR1|=0X212C;//Enable Usart, Tx,Rx, Interrupci?n Rx
	NVIC_EnableIRQ(USART2_IRQn);
	
}

void display (void){
	
	if (compara==0) {
		
		for (int j=0; j<10;j++){
		send_comand(ddram2L+j);
		send_dato(NUM[j]);
		Delay(50);
	}
	}
	
	else {
		
	}
	
	
}
void entrasale (void) {
	switch (compara) {
		
		case 0: 
			send_comand(clear_Display); //Limpiar el Display
		for(int i = 0; i<0x0+numerito2; i++){ //Envia letras de LCD
		send_dato(dato2[i]);
	  Delay(1);}
		send_comand(ddram1L+numerito2); 
		break;
		
		case 1:
		send_comand(clear_Display); //Limpiar el Display
		for(int i = 0; i<0x0+numerito1; i++){ //Envia letras de LCD
		send_dato(dato[i]);
	  Delay(1);}
		send_comand(ddram1L+numerito1); 
		
		 //Datos usart
		for(int i = 0; i<0x0+numerito3; i++){ //Envia letras de LCD
		send_dato(entrada);
	  Delay(1);}
		send_comand(ddram2L+numerito3); 
		break;
	}
}
extern "C"{
	void EXTI0_IRQHandler(void){
		    Delay(100);	
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&1;
					if(cl==1&&i==6){CONT7();}
					else if(cl==1&&i==7){CONT4();}
					else if(cl==1&&i==8){CONT1();}
					else if(cl==1&&i==9){asigNum(10);}
				}
				Delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;		
	}
	
	void EXTI1_IRQHandler(void){
		    Delay(100);
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&2;
					if(cl==2&&i==6){CONT8();}
					else if(cl==2&&i==7){CONT5();}
					else if(cl==2&&i==8){CONT2();}
					else if(cl==2&&i==9){CONT0();}
				}
				Delay(3000);
				GPIOB->ODR=0x1E0;
				EXTI->PR=0XFFFF;
	}
	
	void EXTI2_IRQHandler(void){
				Delay(100);
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&4;
					if(cl==4&&i==6){CONT9();}
					else if(cl==4&&i==7){CONT6();}
					else if(cl==4&&i==8){CONT3();}
					else if(cl==4&&i==9){asigNum(1000);}
				}
				Delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;
				
	}
	
	void EXTI4_IRQHandler(void){
				Delay(100);
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&0x10;
					if(cl==16&&i==6){asigNum(12);}
					else if(cl==16&&i==7){asigNum(13);}
					else if(cl==16&&i==8){asigNum(14);}
					else if(cl==16&&i==9){asigNum(15);}
				}
				Delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;
	}
	
	void USART2_IRQHandler(void){
	
			entrada=USART2->DR; //Dato que llega de matlab
		
	}
}
void configSysTick(void){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock);
}
void sendUsart(){
	
	USART2->DR='#';
	Delay(100);
	
	USART2->DR=envio; //Dato que sale a matlab
	Delay(100);
	
	USART2->DR='#';
	Delay(100);

}
void control(void){
	
	send_comand(ddram1L+numerito1+1); 
//	send_dato(cen+48);
//	send_dato(dec+48);
//	send_dato(unid+48);	

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
void configuracion(){
		RCC->AHB1ENR=0XF;								//Activar el reloj
		GPIOC -> MODER |= 0X5555555;
	  RCC -> APB2ENR |= (1UL<<14);
	  GPIOA->MODER |= 0XA0;// PA(2-3)Alterno
	  GPIOA->AFR[0]|=0X7700;//Tx,Rx
	GPIOB->MODER|=0x15400;
	GPIOB->PUPDR|=0X22A;
	SYSCFG->EXTICR[0]|=0x0111;
	SYSCFG->EXTICR[1]|=0x0001;
	EXTI -> IMR|=0X17;
	EXTI -> RTSR|=0X17;
	NVIC->ISER[0]=1UL<<6|1UL<<7|1UL<<8|1UL<<10;
	GPIOB->ODR=0X1E0;
	
	  //CONFIGURACION LCD
  send_comand(set_8bits); //Configurar a 8 bits
	send_comand(cursor_no_parpadeo); //Encender el Display con el cursor sin parpadear
	send_comand(move_cursor_right); //Mover el cursor a la derecha
	send_comand(clear_Display); //Limpiar el Display
	Delay(20);
	send_comand(ddram1L); 
	//ESCRIBIR
	entrasale();
}

int main(void) {
	configuracion();
	configUsart();
	configSysTick();
	
	while(1){
	control();
	display();
//	sendUsart();
}
	
}
