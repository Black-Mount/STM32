#include "stm32f4xx.h"

char datico;
char envio;
char c1;
//char tec_LCD[4][4]={{c1, c2, c3, c4},
//                      {c5, c6, c7, c8},
//                      {c9, c10, c11, c12}, 
//                      {c13, c14, c15, c16}}; //Matriz para teclado matricial

int subconta1 = 1, subconta2 = 1, subconta3 = 1;
char digitos[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; 
int conta = 0; 
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
char cgram = 0x40; //Graficar
char cgram2 = 0x48;
char cgram3 = 0x50;
char cgram4 = 0x58;
int most=0;
int f;
char numerito;
int banderita;
char siu = ' ';
char vector2[3];
char datos2[16];

int enviar = 0;

int contddram = 0;

char escribir[10];

char dato3[] = {"Lab 6 Micros"};
char dato[] = {"Chat USART"};

void Delay(int x){
	for(volatile int i=0;i<x*700; i++){
		asm("nop"); 
	}
}	


void send_comand(char n1){
	GPIOC ->ODR &= 0XFF00;
	GPIOC ->ODR |= n1;
	GPIOC ->ODR &= ~(1UL<<8);//RS=0
	GPIOC ->ODR |= (1UL<<9); // Enable 1
	Delay(20); 
	GPIOC ->ODR &= ~(1UL<<9); // Enable 1
}

void send_dato(char n1){
	GPIOC ->ODR &=0XFF00;
	GPIOC ->ODR |= n1;	
	GPIOC->ODR |=(1UL<<8);//RS=1
	GPIOC->ODR |=(1UL<<9); // Enable 1
	Delay(20);
	GPIOC->ODR &=~(1UL<<9); // Enable 0
}


void create_draw6(char n1){//n1 es la dirección donde se quiere dirigir primera fila y n2 posición donde se guardó en CGRAM
	GPIOC ->ODR &=0XFF00;
	send_comand(ddram2L + n1);
	send_comand(cgram4); 
	send_dato(0x1F);
	send_dato(0x1E);
	send_dato(0x1C);
	send_dato(0x09);
	send_dato(0x03);
	send_dato(0x17);
	send_dato(0x1F);
	send_dato(0x1F);
	send_comand(ddram2L + n1); 
	Delay(1);
	send_dato(0X3);
}

void clear_1L(int conta){
		send_comand(cursor_no_parpadeo);
	send_comand(ddram1L+conta);
	for(int x = conta; x<16; x++){
		send_dato(' ');
		Delay(20);
	}
}
void clear_2L(){
	send_comand(cursor_no_parpadeo);
	send_comand(ddram2L);
	for(int x = 0; x<16; x++){
		send_dato(' ');
		Delay(20);
	}
}


//Para corregir DATO 
int correg_dato = 0X10; //Desplaza el cursor a la izquierda sin leer o escribir
int conta2ddram = 0;

void enviar_datico(int siu2){
   while(!(USART2->SR&USART_SR_TXE)){};           // Espera puerto disponible 
  	USART2->DR= siu2;	 // Transmite dato
}


extern "C"{

 void USART2_IRQHandler(void){
 send_comand(cursor_no_parpadeo_off);
  unsigned char Dato;
	send_comand(ddram1L+conta2ddram);
  Dato=USART2->SR;                               // Limpiar banderas
  Dato=USART2->DR;                              // Lee dato

  send_dato(Dato);
	Delay(10);
	conta2ddram++;

	if(Dato == '.'){	
		clear_1L(conta2ddram);
		send_comand(ddram1L);
		conta2ddram = 0;
	}
	
  }
 
  void SysTick_Handler(void){	
		if(most<4){                    //Envía pulso al teclado 
			GPIOB -> ODR = ((1UL<<most)<<4);
			f=most;
			most++;
		}else{
		 most = 0;                     //Si most es mayor a 4 vuelve a enviar '1' en las columnas
			}
	}
	
//		void EXTI0_IRQHandler(void){                //Función interrupcion 9_5
//			EXTI->PR |=0XFFFF;                        //Apagado de banderas
//		  Delay(500);                                      
//	  }

//	
//		void EXTI1_IRQHandler(void){                //Función interrupcion 9_5
//			EXTI->PR |=0XFFFF;                        //Apagado de banderas
//			Delay(500);                                      
//    }
//		
//			void EXTI4_IRQHandler(void){               //Función interrupcion 9_5
//			EXTI->PR |=0XFFFF;                         //Apagado de banderas
//		  Delay(500);                                         
//	  }
			
		
			
	void EXTI9_5_IRQHandler(void){               //Función interrupcion 9_5
	send_comand(cursor_no_parpadeo_off);
		if(EXTI->PR & 0X200){                      //Si se activa interrupcion 9
			EXTI->PR |=0XFFFF;                      //Apagado de banderas
      send_comand(ddram2L+contddram);
			
		  if(f== 0 && subconta1 == 1){c1 = '1';}
			else if(f== 0 && subconta1 == 2){c1 = 'A';}
			else if(f== 0 && subconta1 == 3){c1 = 'B';}
			else if(f== 0 && subconta1 == 4){c1 = 'C';}
			
			if(f== 1 && subconta1 == 1){c1 = '4';}
			else if(f== 1 && subconta1 == 2){c1 = 'J';}
			else if(f== 1 && subconta1 == 3){c1 = 'K';}
			else if(f== 1 && subconta1 == 4){c1 = 'L';}
			
			if(f== 2 && subconta1 == 1){c1 = '7';}
			else if(f== 2 && subconta1 == 2){c1 = 'S';}
			else if(f== 2 && subconta1 == 3){c1 = 'T';}
			else if(f== 2 && subconta1 == 4){c1 = 'U';}
			
			if(f== 3 && subconta1 == 1){c1 = 0XEE;}
			else if(f== 3 && subconta1 == 2){c1 = 0X21;}
			else if(f== 3 && subconta1 == 3){c1 = 0XAF;}
			else if(f== 3 && subconta1 == 4){c1 = 0XEF;}
		
			Delay(200);                               //Bandera es 5 
      digitos[conta] = c1;          //Vector guarda en char tecla oprimida
			
			Delay(200);
		  send_dato(c1);
			//send_comand(move_cursor_left);
			subconta1++; 
			subconta2 = 1; subconta3 = 1; 
			if(subconta1 > 4){subconta1 = 1;}
			send_comand(ddram2L+contddram);
		}
	
	}
	void EXTI15_10_IRQHandler(void){  //Función interrupcion 10_15
			send_comand(cursor_no_parpadeo_off);
		
		if(EXTI->PR & 0X400){    //Si se activa interrupcion 10
		  EXTI->PR |=0XFFFF;                       //Apagado de banderas
		  Delay(200);                               //Bandera es 5 
		  send_comand(ddram2L+contddram);
			
      if(f== 0 && subconta2 == 1){c1 = '2';}
			else if(f== 0 && subconta2 == 2){c1 = 'D';}
			else if(f== 0 && subconta2 == 3){c1 = 'E';}
			else if(f== 0 && subconta2 == 4){c1 = 'F';}
			
			if(f== 1 && subconta2 == 1){c1 = '5';}
			else if(f== 1 && subconta2 == 2){c1 = 'M';}
			else if(f== 1 && subconta2 == 3){c1 = 'N';}
			else if(f== 1 && subconta2 == 4){c1 = 'O';}
			
			if(f== 2 && subconta2 == 1){c1 = '8';}
			else if(f== 2 && subconta2 == 2){c1 = 'V';}
			else if(f== 2 && subconta2 == 3){c1 = 'W';}
			else if(f== 2 && subconta2 == 4){c1 = 'X';}
			
			if(f== 3 && subconta2 == 1){c1 = '0';}
			else if(f== 3 && subconta2 == 2){c1 = ',';}
			else if(f== 3 && subconta2 == 3){c1 = '+';}
			else if(f== 3 && subconta2 == 4){c1 = '-';}
		
			Delay(200);                               //Bandera es 5 
      digitos[conta] = c1;           //Vector guarda en char tecla oprimida
			
			Delay(200);
		  send_dato(c1);
			subconta2++; subconta1 = 1; subconta3 = 1; 
			
			if(subconta2 > 4){subconta2 = 1;}
			send_comand(ddram2L+contddram);
		}
		
		if(EXTI->PR & 0X800){    //Si se activa interrupcion 11
			EXTI->PR |=0XFFFF;                       //Apagado de banderas
		  Delay(200);                             //Bandera es 5 
	    send_comand(ddram2L+contddram);
			
      if(f== 0 && subconta3 == 1){c1 = '3';}
			else if(f== 0 && subconta3 == 2){c1 = 'G';}
			else if(f== 0 && subconta3 == 3){c1 = 'H';}
			else if(f== 0 && subconta3 == 4){c1 = 'I';}
			
			if(f== 1 && subconta3 == 1){c1 = '6';}
			else if(f== 1 && subconta3 == 2){c1 = 'P';}
			else if(f== 1 && subconta3 == 3){c1 = 'Q';}
			else if(f== 1 && subconta3 == 4){c1 = 'R';}
			
			if(f== 2 && subconta3 == 1){c1 = '9';}
			else if(f== 2 && subconta3 == 2){c1 = 'Y';}
			else if(f== 2 && subconta3 == 3){c1 = 'Z';}
			else if(f== 2 && subconta3 == 4){c1 = '.';}
			
			if(f== 3){
				clear_2L();
				Delay(10);	
        contddram = 0;		
        for(int x = 0; x<16; x++){
					digitos[x] = ' '; 
				}
				conta = 0;	
				send_comand(cursor_no_parpadeo_off);
			}
		
			Delay(200);                               //Bandera es 5 
      digitos[conta] = c1;         //Vector guarda en char tecla oprimida
			
			Delay(200);
		  send_dato(c1);
			subconta3++; subconta2 = 1; subconta1 = 1; 
			
			if(subconta3 > 4){subconta3 = 1;}
			send_comand(ddram2L+contddram);
		}
		
		if(EXTI->PR & 0X1000){    //Si se activa interrupcion 12
			EXTI->PR |=0XFFFF;                       //Apagado de banderas
		  Delay(200);                           //Bandera es 5 
			
			if(f== 0){
			subconta1 = 1; subconta2 = 1; subconta3 = 1; 
			contddram++;conta++;
			Delay(100);
			send_comand(ddram2L+contddram);				
			Delay(400); 
			//enviar_datico();
			enviar = 1;}
			
			if(f==1){
				subconta1 = 1; subconta2 = 1; subconta3 = 1; 
				send_dato(digitos[conta] = ' ');
				contddram--;conta--;
				Delay(100);
				send_comand(ddram2L+contddram);
				
				Delay(400);
				siu = c1;
				enviar = 1;
			}
			
			if(f==2){
				send_comand(ddram2L); 
				for(int x = 0; x<16; x++){
					enviar_datico(digitos[x]);
				}
				create_draw6(0XF);
			}
			
			if(f==3){
				send_comand(clear_Display);
				Delay(10);
				conta2ddram = 0;		
        contddram = 0;		
        for(int x = 0; x<16; x++){
					digitos[x] = ' '; 
				}
				conta = 0;	
				send_comand(cursor_no_parpadeo_off);
				
			}
		
		}	
	}
 	
}	

//void send(){
//	int i=0;
//	for(i=0; envio!='-';i++){
//		envio = envio1[i]; 
//		while(!(USART2->SR&USART_SR_TXE)); // Espera puerto disponible 
//		USART2 -> DR = envio;
//	}
//	envio = '1';
//}

int main(void){
 RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; // Activa reloj GPIOA
 RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; // Activa reloj GPIOA
 RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN; // Activa reloj GPIOC
 GPIOA->MODER |= 0X500;//0101 0000 0000
 GPIOC->MODER |= 0X55555;//0101 0000 0000
 GPIOA -> MODER |= 0X0; //0000 0000 0000 0000 0000 0000 0000 0000  Entrada
 GPIOB -> MODER = 0X5500;  //0000 0000 0000 0000 0101 0101 0000 0000 Salida teclado
 GPIOB -> PUPDR |= 0XAA00;   //0000 0000 0000 0000 1010 1010 0000 0000
 GPIOA -> PUPDR |= 0X2A80000; //0000 0000 0000 0000 0000 0000 0000 0000 pull-up  -- 0000 0010 1010 1000 0000 0000 0000 0000  pullDown 
 GPIOA->MODER|=(2UL<<GPIO_MODER_MODER2_Pos); // Pin PA2 modo alternativo
 GPIOA->MODER|=(2UL<<GPIO_MODER_MODER3_Pos); // Pin PA3 modo alternativo
 GPIOA->AFR[0]|=(7UL<<GPIO_AFRL_AFSEL2_Pos); // Función alternativa 7 en pin PA2
 GPIOA->AFR[0]|=(7UL<<GPIO_AFRL_AFSEL3_Pos); // Función alternativa 7 en pin PA3
 RCC->APB1ENR|=RCC_APB1ENR_USART2EN; // Activa reloj USART2
 USART2->BRR=(unsigned int)(16000000/9600); // Define 9600 bps    
 USART2->CR1|=(USART_CR1_RE|USART_CR1_TE); // Activa Tx y Rx
 USART2->CR2=0;
 USART2->CR3=0;
 USART2->CR1|=USART_CR1_UE; // Activa Usart
 NVIC_EnableIRQ(USART2_IRQn); // Activa vector interrupción 
 USART2->CR1|=USART_CR1_RXNEIE; // Activa servicio de interrupción
	
  //CONFIGURACION INTERRUPCIONES
	//Configuracion Interrupciones
	RCC ->APB2ENR |= (1UL<<14);        //Activar reloj Interrupciones
	//EXTI->RTSR |= 0X1E13;            //Colocar en flanco de subida
	EXTI->FTSR |= 0X1E13;              //Colocar en flanco de bajada
	EXTI->IMR |= 0X1E13;               //Activar las interrupciones 0,1,9, 10, 11, 12  0001 1110 0001 0011
	SYSCFG->EXTICR[0] |=0X0000;        //Vectores para interrupciones PA0, PA1   0000 0000 0000 0000
	SYSCFG->EXTICR[1] |=0X0000;        //Vectores para interrupciones PA4   0000 0000 0000 0000
	SYSCFG->EXTICR[2] |=0X0000;        //Vectores para interrupciones PA9, PA10 y PA11    0000 0000 0000 0000
	SYSCFG->EXTICR[3] |=0x0000;        //Vectores para interrupciones PA12    0000 0000 0000 0000
	NVIC_EnableIRQ(EXTI0_IRQn);        //Llamado a la interrupcion  0
	NVIC_EnableIRQ(EXTI1_IRQn);        //Llamado a las interrupcion 1
	NVIC_EnableIRQ(EXTI4_IRQn);        //Llamado a la interrupcion  4
	NVIC_EnableIRQ(EXTI15_10_IRQn);    //Llamado a las interrupciones  10, 11 y 12
	NVIC_EnableIRQ(EXTI9_5_IRQn);      //Llamado a la interrupcion 9
	
	
	//Configuracion SysTick
	SystemCoreClockUpdate();
		SysTick_Config(SystemCoreClock*0.001);

	//CONFIGURACION LCD
  send_comand(set_8bits); //Configurar a 8 bits
	send_comand(cursor_no_parpadeo_off); //Encender el Display con el cursor sin parpadear
	send_comand(move_cursor_right); //Mover el cursor a la derecha
	send_comand(clear_Display); //Limpiar el Display
	Delay(20);
	send_comand(ddram1L+2); 
	
		for(int i = 0; i<12; i++){ //Envia letras de LCD
			numerito = dato3[i];
			send_dato(dato3[i]);
			Delay(100);}
		send_comand(ddram2L+3);
		for(int i = 0; i<10; i++){ //Envia letras de LCD
			numerito = dato[i];
			send_dato(dato[i]);
			Delay(100);}
	  	Delay(3000);
			send_comand(clear_Display); 

	while(1){	

	
	} // Bucle infinito
	return 0;
	}