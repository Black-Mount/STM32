#include "STM32F4xx.h"
#include <cmath>
#include <stdio.h>

char disp_on = 0x3F;
char disp_off = 0x3E;
char starL = 0xC0;
char setX = 0xB8;
char setY = 0x40;
int NUM[5]={0,0,0,0,0};
int u=0;
int c0=0, c1=0, c2=0, c3=0, c4=0, c5=0, c6=0, c7=0, c8=0, c9=0;

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

char CAR[37][8]={{0x0,0x7E,0x81,0x81,0x81,0x7E,0x0,0x0},			//Numero 0	CAR[0]
{0x0,0x0,0x82,0x82,0xFF,0x80,0x0,0x0},												//Numero 1	CAR[1]
{0x0,0x82,0xC1,0xA1,0x91,0x8E,0x0,0x0},												//Numero 2	CAR[2]
{0x0,0x0,0x42,0x81,0x89,0x89,0x76,0x0},												//Numero 3	CAR[3]
{0x0,0x30,0x28,0x24,0x22,0xFF,0x20,0x0},											//Numero 4	CAR[4]
{0x0,0x4F,0x89,0x89,0x89,0x71,0x0,0x0},												//Numero 5	CAR[5]
{0x0,0x7E,0x89,0x89,0x89,0x89,0x70,0x0},											//Numero 6	CAR[6]
{0x0,0x0,0xC1,0x21,0x11,0x9,0x7,0x0},													//Numero 7	CAR[7]
{0x0,0x76,0x89,0x89,0x89,0x89,0x76,0x0},											//Numero 8	CAR[8]
{0x0,0xE,0x91,0x91,0x91,0x7E,0x0,0x0},												//Numero 9	CAR[9]
{0x0,0xFC,0x12,0x11,0x11,0x12,0xFC,0x0}, 											//Letra A		CAR[10]
{0x0,0xFF,0x89,0x89,0x89,0x89,0x76,0x0}, 											//Letra B		CAR[11]
{0x0,0x7E,0x81,0x81,0x81,0x81,0x81,0x0}, 											//Letra C		CAR[12]
{0x0,0xFF,0x81,0x81,0x81,0x42,0x3C,0x0}, 										 	//Letra D		CAR[13]
{0x0,0xFF,0x89,0x89,0x89,0x0,0x0,0x0}, 												//Letra E		CAR[14]
{0x0,0xFF,0x9,0x9,0x9,0x0,0x0,0x0}, 													//Letra F		CAR[15]
{0x0,0x7E,0x81,0x89,0x89,0x89,0xF9,0x0}, 											//Letra G		CAR[16]
{0x0,0xFF,0x8,0x8,0x8,0xFF,0x0,0x0}, 													//Letra H		CAR[17]
{0x0,0x81,0x81,0xFF,0x81,0x81,0x0,0x0}, 											//Letra I		CAR[18]
{0x0,0x0,0xF1,0x81,0x81,0xFF,0x1,0x1}, 												//Letra J		CAR[19]
{0x0,0xFF,0x8,0x8,0x14,0xE3,0x0,0x0}, 												//Letra K		CAR[20]
{0x0,0x81,0xFF,0x81,0x80,0xC0,0x0,0x0}, 											//Letra L		CAR[21]
{0x0,0xFF,0x2,0x4,0x8,0x4,0x2,0xFF}, 													//Letra M		CAR[22]
{0x0,0xFF,0x3,0xC,0x30,0xC0,0xFF,0x0}, 												//Letra N		CAR[23]
{0x0,0x3C,0x42,0x81,0x81,0x81,0x42,0x3C}, 										//Letra O		CAR[24]
{0x0,0xFF,0x9,0x9,0x9,0x6,0x0,0x0}, 													//Letra P		CAR[25]
{0x0,0x3C,0x42,0x81,0x81,0xA1,0x42,0xBC}, 										//Letra Q		CAR[26]
{0x0,0xFF,0x11,0x11,0x29,0xC6,0x0,0x0}, 											//Letra R		CAR[27]
{0x0,0x0,0x86,0x89,0x89,0x89,0x71,0x0}, 											//Letra S		CAR[28]
{0x0,0x1,0x1,0x1,0xFF,0x1,0x1,0x1}, 													//Letra T		CAR[29]
{0x0,0x7F,0x80,0x80,0x80,0x80,0x7F,0x0}, 											//Letra U		CAR[30]
{0x0,0x7,0x38,0xC0,0xC0,0x38,0x7,0x0}, 												//Letra V		CAR[31]
{0x7,0x38,0xC0,0x30,0x30,0xC0,0x38,0x7}, 											//Letra W		CAR[32]
{0x0,0xC1,0x36,0x8,0x8,0x36,0xC1,0x0}, 												//Letra X		CAR[33]
{0x0,0x1,0x6,0x8,0xF8,0x8,0x6,0x1},													  //Letra Y		CAR[34]
{0x0,0xC1,0xE1,0xB9,0x9D,0x87,0x83,0x0}, 											//Letra Z		CAR[35]
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}															//Espacio		CAR[36]
};

void delay(int x){
	for(int i=0;i<x*500;i++){
      asm("nop");
  }
}

void send_comando (int cs, char a){
	GPIOC -> ODR = 0;													//RS
	if(cs==1){GPIOC->ODR|=(1UL<<8);}					//Enable CS1
	else if (cs==2){GPIOC->ODR|=(1UL<<9);}		//Enable CS2
	GPIOC->ODR|=a;
	GPIOC->ODR|=(1UL<<11);										//Enable 1
	delay(50);
	GPIOC->ODR &=~ (1UL<<11); 								//Enable 0
	GPIOC -> ODR = 0;													//CS 0
}

void send_dato (int cs, char b){
	GPIOC -> ODR |= (1UL<<10);								//RS
	if(cs==1){GPIOC->ODR|=(1UL<<8);}					//Enable CS1
	else if (cs==2){GPIOC->ODR|=(1UL<<9);}		//Enable CS2
	GPIOC->ODR |= b;
	GPIOC->ODR|=(1UL<<11);										//Enable 1
	delay(50);
	GPIOC->ODR &=~ (1UL<<11); 								//Enable 0
	GPIOC -> ODR = 0;													//CS 0
}

void display (void){
	for (int j=0; j<8;j++){
			send_dato(1, ~CAR[NUM[0]][j]);
			send_dato(2, ~CAR[36][j]);
		}
	for (int j=0; j<8;j++){
			send_dato(1, ~CAR[NUM[1]][j]);
			send_dato(2, ~CAR[36][j]);
		}
	for (int j=0; j<8;j++){
			send_dato(1, ~CAR[NUM[2]][j]);
			send_dato(2, ~CAR[36][j]);
		}
	for (int j=0; j<8;j++){
			send_dato(1, ~CAR[NUM[3]][j]);
			send_dato(2, ~CAR[36][j]);
		}
	for (int j=0; j<8;j++){
			send_dato(1, ~CAR[NUM[4]][j]);
			send_dato(2, ~CAR[36][j]);
		}
}



void asigNum(int x){		
		delay(10);

		if (x==100){
			u++;
			c0=0;c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
		}
		NUM[u]=x;
		if (u==5){u=0;}
}

extern "C"{
	void EXTI0_IRQHandler(void){
		    delay(100);	
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&1;
					if(cl==1&&i==6){CONT7();}
					else if(cl==1&&i==7){CONT4();}
					else if(cl==1&&i==8){CONT1();}
					else if(cl==1&&i==9){asigNum(10);}
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
					else if(cl==2&&i==7){CONT5();}
					else if(cl==2&&i==8){CONT2();}
					else if(cl==2&&i==9){CONT0();}
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
					else if(cl==4&&i==7){CONT6();}
					else if(cl==4&&i==8){CONT3();}
					else if(cl==4&&i==9){asigNum(100);}
				}
				delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;
				
	}
	
	void EXTI4_IRQHandler(void){
				delay(100);
				int cl=0;
				for(int i=6;i<10;i++){
					GPIOB->ODR=1<<(i-1);
					cl=GPIOB->IDR&0x10;
					if(cl==16&&i==6){asigNum(12);}
					else if(cl==16&&i==7){asigNum(13);}
					else if(cl==16&&i==8){asigNum(14);}
					else if(cl==16&&i==9){asigNum(15);}
				}
				delay(3000);
				GPIOB->ODR=0X1E0;
				EXTI->PR=0XFFFF;
	}
}




int main (void){
	
	RCC -> AHB1ENR= 0xF;
	RCC -> APB2ENR|=(1<<14);
	GPIOC -> MODER = 0x55555555;
	GPIOB->MODER=0x15400;
	GPIOB->PUPDR=0X22A;
	
	SYSCFG->EXTICR[0]|=0x0111;
	SYSCFG->EXTICR[1]|=0x0001;
	EXTI -> IMR|=0X17;
	EXTI -> RTSR|=0X17;
	NVIC->ISER[0]=1UL<<6|1UL<<7|1UL<<8|1UL<<10;
	
	GPIOB->ODR=0X1E0;
	
	
	send_comando(1, disp_on);
	send_comando(2, disp_on);
	send_comando(1, 0xC0);
	send_comando(2, 0xC0);
	
		
	
	
	while (true){		
		send_comando(1, setY);
		send_comando(2, setY);
		send_comando(1, setX);
		send_comando(2, setX);
		
		display();
		
		
	}
}

void CONT0 (void){
	c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c0++;
	switch (c0){
		case 1:
			asigNum(0);
			break;
		case 2:
			asigNum(36);
			break;
	}
	
		if (c0==2){c0=0;}
	
}
void CONT1 (void){

	c0=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c1++;
	switch (c1){
		case 1:
			asigNum(1);
			break;
		case 2:
			asigNum(10);
			break;
		case 3:
			asigNum(11);
			break;
		case 4:
			asigNum(12);
			break;
	}
	
		if (c1==4){c1=0;}
	
}

void CONT2 (void){
	c0=0; c1=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c2++;
	switch (c2){
		case 1:
			asigNum(2);
			break;
		case 2:
			asigNum(13);
			break;
		case 3:
			asigNum(14);
			break;
		case 4:
			asigNum(15);
			break;
	}
	
		if (c2==4){c2=0;}
	
}

void CONT3 (void){
	c0=0; c1=0; c2=0; c4=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c3++;
	switch (c3){
		case 1:
			asigNum(3);
			break;
		case 2:
			asigNum(16);
			break;
		case 3:
			asigNum(17);
			break;
		case 4:
			asigNum(18);
			break;
	}
	
		if (c3==4){c3=0;}
	
}

void CONT4 (void){
	c0=0; c1=0; c2=0; c3=0; c5=0; c6=0; c7=0; c8=0; c9=0;
	c4++;
	switch (c4){
		case 1:
			asigNum(4);
			break;
		case 2:
			asigNum(19);
			break;
		case 3:
			asigNum(20);
			break;
		case 4:
			asigNum(21);
			break;
	}
	
		if (c4==4){c4=0;}
	
}

void CONT5 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c6=0; c7=0; c8=0; c9=0;
	c5++;
	switch (c5){
		case 1:
			asigNum(5);
			break;
		case 2:
			asigNum(22);
			break;
		case 3:
			asigNum(23);
			break;
		case 4:
			asigNum(24);
			break;
	}
	
		if (c5==4){c5=0;}
	
}

void CONT6 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c7=0; c8=0; c9=0;
	c6++;
	switch (c6){
		case 1:
			asigNum(6);
			break;
		case 2:
			asigNum(25);
			break;
		case 3:
			asigNum(26);
			break;
		case 4:
			asigNum(27);
			break;
	}
	
		if (c6==4){c6=0;}
	
}

void CONT7 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c8=0; c9=0;
	c7++;
	switch (c7){
		case 1:
			asigNum(7);
			break;
		case 2:
			asigNum(28);
			break;
		case 3:
			asigNum(29);
			break;
		case 4:
			asigNum(30);
			break;
	}
	
		if (c7==4){c7=0;}
	
}

void CONT8 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c9=0;
	c8++;
	switch (c8){
		case 1:
			asigNum(8);
			break;
		case 2:
			asigNum(31);
			break;
		case 3:
			asigNum(32);
			break;
		case 4:
			asigNum(33);
			break;
	}
	
		if (c8==4){c8=0;}
	
}

void CONT9 (void){
	c0=0; c1=0; c2=0; c3=0; c4=0; c5=0; c6=0; c7=0; c8=0;
	c9++;
	switch (c9){
		case 1:
			asigNum(9);
			break;
		case 2:
			asigNum(34);
			break;
		case 3:
			asigNum(35);
			break;
	}
	
		if (c9==3){c9=0;}
	
}