//LCD

#include "stm32f4xx.h"

int unidad;
int decena;
int centena;
int decimal1;
int temp = 0;		
float conver = 0;
float unid = 0, dec=0;
int cen=0;
int n =0;
										 
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
char cgram = 0X40; //Graficar
char cgram2 = 0X48; //Graficar
char cgram3 = 0X50; //Graficar
char cgram4 = 0X58; //Graficar
int correg_dato_izq = 0X10; //Desplaza el cursor a la izquierda sin leer o escribir
int correg_dato_der= 0X14; //Desplaza el cursor a la derecha sin leer o escribir

char dato[] = {"Humedad:"};
int numerito = 8;

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

extern "C"{
void SysTick_Handler (void){
	GPIOB -> ODR ^= 1;
}
}



void configuracion(){
		RCC->AHB1ENR=0X7;								//Activar el reloj
		GPIOC -> MODER |= 0X5555555;
	  RCC -> APB2ENR |= (1UL<<14);
		RCC -> APB2ENR |= 0x100;				//Habilitar el ADC1
		GPIOB -> MODER |= 0X5005;				//0000 0000 0000 0000 0101 0000 0000 0101 
		GPIOA -> MODER |= 0X3;					//0000 0000 0000 0000 0000 0000 0000 0011
  	GPIOA -> MODER |= 0X0;					//0000 0000 0000 0000 0000 0000 0000 0000
		SysTick -> LOAD = 75; //49 para 20k , 99 para 10k 75 para 15k
		SysTick -> VAL = 0;
		SysTick -> CTRL = 3;
	
	//CONFIGURACION ADC
		ADC1->CR1|=0;
		ADC1->SQR3=0;//activa canal 0 osea A0
		ADC1->CR2=0;//desactivar conversion T1
		for(int dl=0;dl<5000;dl++);//esperar
		ADC1->CR2=1;//activa conversion
	
	//CONFIGURACION LCD
  send_comand(set_8bits); //Configurar a 8 bits
	send_comand(cursor_no_parpadeo); //Encender el Display con el cursor sin parpadear
	send_comand(move_cursor_right); //Mover el cursor a la derecha
	send_comand(clear_Display); //Limpiar el Display
	Delay(20);
	send_comand(ddram1L); 
	//ESCRIBIR
	for(int i = 0; i<0x0+numerito; i++){ //Envia letras de LCD
		send_dato(dato[i]);
	  Delay(1);}
		send_comand(ddram1L+numerito); 
}
void control(void){
	ADC1->CR2|=0X40000000; //inicia conversion en canales regulares
	while((ADC1->SR &0X2)==1){asm("nop");};;
	conver = ADC1 -> DR; 
	temp = (((conver* 8056)/407500)+10)*10-7;	

			cen = temp/100;
			n=temp%100;
	    dec = n/10;
		  unid = temp%10;
	
	send_comand(ddram1L+numerito+1); 
	send_dato(cen+48);
	send_dato(dec+48);
	//send_dato('.');
	//send_dato(unid+48);	

}

int main(void){
	configuracion();
	
while(1){
	control();
}
}