#include <stm32f4xx.h>

int time,num,pos=16,u=0,d=0,c=0,x;	
float temp=0;
void Delay(void){for(int x=0;x<16000;x++);}

void configurar(int codea,int codeb){
	GPIOC -> ODR = codea;//0011
	GPIOC -> ODR |= (1UL<<4);
//	Delay(100);
	Delay();
	GPIOC -> ODR = codeb;//0011
	GPIOC -> ODR |= (1UL<<4);
//	Delay(100);
	Delay();
}	
void escribir(int codeb,int codea){
	GPIOC -> ODR = codea+0x20;//0011
	GPIOC -> ODR |= (1UL<<4);
//	Delay(1);
	Delay();
	GPIOC -> ODR = codeb+0X20;//0011
	GPIOC -> ODR |= (1UL<<4);
//	Delay(1);
	Delay();
}	
void rellenotecla(void){
	escribir(12,4);//L
	escribir(1,4);//A
	escribir(1,1);//ESPACIO
	escribir(4,5);//T
	escribir(5,4);//E
	escribir(13,4);//M
	escribir(0,5);//P
	escribir(1,1);//ESPACIO
	escribir(5,4);//E
	escribir(3,5);//S
	escribir(1,1);//ESPACIO
}
void datos(int a, int b, int c){
	switch(a){
		//posiciones en base al datasheet
		case 0:escribir(0,3);break;
		case 1:escribir(1,3);break;
		case 2:escribir(2,3);break;
		case 3:escribir(3,3);break;
		case 4:escribir(4,3);break;
		case 5:escribir(5,3);break;
		case 6:escribir(6,3);break;
		case 7:escribir(7,3);break;
		case 8:escribir(8,3);break;
		case 9:escribir(9,3);break;
	}
	switch(b){
		//posiciones en base al datasheet
		case 0:escribir(0,3);break;
		case 1:escribir(1,3);break;
		case 2:escribir(2,3);break;
		case 3:escribir(3,3);break;
		case 4:escribir(4,3);break;
		case 5:escribir(5,3);break;
		case 6:escribir(6,3);break;
		case 7:escribir(7,3);break;
		case 8:escribir(8,3);break;
		case 9:escribir(9,3);break;
	}
	switch(c){
		//posiciones en base al datasheet
		case 0:escribir(0,3);break;
		case 1:escribir(1,3);break;
		case 2:escribir(2,3);break;
		case 3:escribir(3,3);break;
		case 4:escribir(4,3);break;
		case 5:escribir(5,3);break;
		case 6:escribir(6,3);break;
		case 7:escribir(7,3);break;
		case 8:escribir(8,3);break;
		case 9:escribir(9,3);break;
	}
}
void configuracion(){
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN; // Se activa el módulo ADC1
	ADC->CCR=(3UL<<16); // Se hace ADCCLK=PCLK2/8
	ADC1->CR1=0;
	ADC1->CR2=1UL; // Se activa modulo ADC1
	ADC1->SMPR1=0xFFFFFFFF; // Se fija máximo tiempo de muestreo
	ADC1->SMPR2=0xFFFFFFFF; // Se fija máximo tiempo de muestreo
	ADC1->SQR1=0; // Se fijan todas las secuencias en 0
	ADC1->SQR2=0; // Se fijan todas las secuencias en 0
	ADC1->SQR3=0; // Se fijan todas las secuencias en 0

	
//////////////////////////////////////////////////////
	RCC -> AHB1ENR = 0xF;
	GPIOA->MODER|=3UL; // Activa PA0 análogo
	GPIOB->MODER=0x55555555;//TODOS PRUEBA BORRAR
	
	GPIOC -> MODER = 0X55555;				 //Pines display
	
	GPIOC -> ODR = 0X0;//borra todo Display
	configurar(3,2);// 0011 0010 configura 4 bits
	configurar(2,8);// 0010 1000 enciende display 
	configurar(0,12);//0000 1100 cambiar 12 por 15 para que parpadee y tenga linea
	configurar(0,1);// 0000 0001 limpiar display 
}
 
void control(){
	ADC1->CR2|=(1UL<<30); // Se inicia la rutina de conversión
  while(!(ADC1->SR&(1UL<<1))); // Se espera al fin de la conversión
  GPIOB->ODR=(unsigned int)ADC1->DR; // Se guarda el valor convertido en GPIOC		
	temp=(ADC1->DR)*0.0612;
	configurar(0,2);//cursor a home
	rellenotecla();
	c=temp/100;
	d=(temp-100*c)/10;
	u=temp-(100*c)-(10*d);
	datos(c,d,u);
	escribir(15,13);escribir(3,4);
	for(int x=0;x<17;x++){
		configurar(1,8);//desplaza a la izquierdsa
	}
	
}

int main(void){
	configuracion();
	while(1){
		control();
	}
	return 0;
}