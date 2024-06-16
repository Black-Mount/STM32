#include <stm32f4xx.h>

int i,x,dip;
int pasado=0,actual;
int numeros[]={0x3f0,0x060,0x5b0,0x4f0,0x660,0x6d0,0x7d0,0x070,0x7f0,0x6f0,0x770,0x7c0,0x390,0x5e0,0x790,0x710};
int leds[]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};


int delay(void){for(x=0; x<300000;x++);return 0;}//no modificar 

int configura(void){
	//definir el puerto a habilitar
	RCC->AHB1ENR=0xF ;   //ENABLE CLK PORT A,B,C
	//definir modo entrada o salida
	GPIOA->MODER=0000;
	GPIOB->MODER=0X155500; //Configuración pines B4 al B10 00,01, 01,01, 01,01, 01,01, 00,00, 00,00
	GPIOC->MODER=0X0005555;     //00,00 00,00 00,00 01,01 01,01 01,01 01,01 
	return 0;
}

int control(void){
	
	dip=GPIOA->IDR & 0X3;
	if(!(GPIOC->IDR &(1UL<<13))) //Se evalua si el pulsador esta activo en bajo
	{
		pasado++;
		if(pasado==4){
		pasado=0;
		}
	}
	
	if (pasado==0) {
		switch(dip) 
		{
			case 1:
				for(i=0;i<10;i++){
		GPIOB->ODR=numeros[i];
		delay(); }
				break;
			case 2:
					for(i=0;i<16;i++){
		GPIOB->ODR=numeros[i];
		delay(); }
				break;
			case 3:
					for(i=0;i<8;i++){
		GPIOB->ODR=numeros[i];
		delay(); }
		}}
		if (pasado==1){
		switch(dip) 
		{
		case 3:
				for(i=7;i>=0;i--){
		GPIOB->ODR=numeros[i];
		delay();}
				break;
		case 1:
				for(i=9;i>=0;i--){
		GPIOB->ODR=numeros[i];
		delay();}
				break;
			case 2:
					for(i=15;i>=0;i--){
		GPIOB->ODR=numeros[i];
		delay();}
				break;
			}
	}
		if(pasado==2){
			for(i=0;i<8;i++){
			GPIOC->ODR=leds[i];
			delay();
		}			
		}
		if(pasado==3){
			for(i=7;i>=0;i--){
			GPIOC->ODR=leds[i];
			delay();
		}	
		
		}
		
	/*
	for(i=0;i<11;i++){
		GPIOD->ODR=numeros[i];
		delay();
	}*/
	return 0;
}

//no modificar	
int main(void)
{
	configura();
	while(1)
	{control();}
}