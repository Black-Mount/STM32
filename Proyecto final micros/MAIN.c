#include "stm32f4xx.h"
#include "config.h"
#include "oled.h"
#include "stdio.h"

void Motor1 (int);
void Motor2 (int);
void Mostrar(int,int,int);
void SysTick_Handler(void);
void Ultrasonido(void);
void ConfigUltrasonido(void);
void USART1_Config(void);
void sendUsart(void);
void InitADC(void);
void ReadLM35(void);
void PLL(void);

float TLM35=0;
int recibido=0;
float M1=0, M2=0;
int G1=90, vel=0;
int Tamano=1;
int prueba=27;
int temp=1000, contador, D0, D1;
int x1=0, x2=0, Tam=0;


char T_1[2], T_2[3], V_M[1];


int main (){
PLL();
configP();
GPIOB->MODER|=0X15;		
Interfaz_OLED();
InitADC();
PWM();
USART1_Config();
ConfigUltrasonido();	

	
	while(1){
		Ultrasonido();
		for(int i=0;i<10;i++){'nope';}
		
      if (Tam > 360){G1=90; }
	  	else if (Tam <= 200){G1=40; x1++; GPIOB->ODR|=(1UL<<2); } //Las azules grandes b2
		  else if (Tam > 200 || Tam <360){G1=120; x2++; GPIOB->ODR|=(1UL<<1);} //Las verdes pequeñas b1
	
	// Tam 580 y 420	 
	// Tam 270 		
	ReadLM35();
		Motor1 (G1);  // servomotor
		Motor2 (vel); // Banda
		Mostrar(x1,x2,vel);
		sendUsart();
		if (G1!= 90){
		for(int i=0;i<1000;i++){'nope';}
	}
	}
}

void Motor1 (int G1){//servo canal 1
	M1=10.944*G1 + 585;
	TIM3-> CCR1  = M1;
}

void Motor2 (int Vel){//banda

	if(Vel==1){TIM3-> CCR2  = 4500; GPIOB->ODR|=(1UL<<0);} //5000 o 4500
	else if (Vel==2){TIM3-> CCR2  = 4700; GPIOB->ODR|=(1UL<<0); } //5500 o 4700
	else if (Vel==3){TIM3-> CCR2  = 4900; GPIOB->ODR|=(1UL<<0);} //4900 o 6000
	else if (Vel==0){TIM3-> CCR2  = 0;GPIOB->ODR|=(0UL<<0);}
	
}

void SysTick_Handler(void){
	
	
}

void Mostrar (int x1, int x2, int vel){
	sprintf(V_M, "%d", vel);
	OLED_GotoXY (80,22);
	OLED_Puts (V_M, &Font_7x10, 1);
	
	
	sprintf(T_1, "%d", x1);
	OLED_GotoXY (25,47);
	OLED_Puts (T_1, &Font_7x10, 1);
	
	sprintf(T_2, "%d", x2);
	OLED_GotoXY (89,47);
	OLED_Puts (T_2, &Font_7x10, 1);
	OLED_UpdateScreen();
}

void Ultrasonido(void){
	
	  GPIOC->ODR=2;// Se acciona el triger del ultrasonido
		TIM2->CNT=0;// Se reinicia el conteo del TIM
		while(TIM2 -> CNT < 12){}// Se cuenta 12us
		GPIOC-> ODR= 0;// Se apaga el triger del ultrasonido
		while ((GPIOC -> IDR & 0x1)==0);// Se espera a que la señal ECO se ponga en 1
		TIM2 -> CNT = 0;// Se apaga reinicia el contero del TIM
		while((GPIOC->IDR&1)==1);// Se espera a que la señal de ECO sea 0
		Tam=(TIM2->CNT); // Calculo de distancia
//		x1=Tam;

}

void ConfigUltrasonido(){
	GPIOC->MODER|=0x4;//Pin C1 de salida
	//TIMER ULTRASONIDO
	RCC->APB1ENR|=1;// Se habilita el reloj del TIM2 
	TIM2 -> CR1 = 1;// Contador habilitado
	TIM2 -> PSC = 16; //Base d etiempo de 1 us
	TIM2 -> ARR = 0xFFFFF; // Limite de cuenta  
}
void delay (float ms){ // Es el delay xd
	
	ms=ms*5333;
	for(int z=0;z<ms;z++){__ASM("NOP");}

}

void sendUsart(void){

	USART1->DR=TLM35;
	delay(150);
	}
	

void USART1_Config(void){
	GPIOA->MODER |= 0X280000;// PA(10-9)Alterno
	GPIOA->AFR[1]|=0X0770;//Tx,Rx
	RCC->APB2ENR|=1<<4;//Activar USART1
	USART1->BRR=0X684;//9600b/s 0x28B1 para 100Mhz, y 0x684 normal
	USART1->CR1=0X212C;//Enable Usart, Tx,Rx,
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void)
	{
		recibido=USART1->DR; //Lee dato recibido
		if (recibido==49) { //Recibe un uno en ASCII 
			//Poner algo para que la transportadora inicie
		}
		if (recibido==50) { //Recibe un dos en ASCII
			//Poner algo para que la transportadora pare
			vel=0;
		}
		if (recibido==51) { //Recibe un tres en ASCII
			//Poner algo para la velocidad 1
			vel=1;
		}
		if (recibido==52) { //Recibe un cuatro en ASCII
			//Poner algo para la velocidad 2
			vel=2;
		}
		if (recibido==53) { //Recibe un cinco en ASCII
			//Poner algo para la velocidad 3
			vel=3;
		}
	}
	
	void InitADC(void){
	RCC->APB2ENR |= 0X100; //HABILITAR EL ADC 1
	GPIOA->MODER |= 0X3;// PA(0) Análogo
	ADC1->SQR3 = 0; //CANAL 0 DEL ADC1
	ADC1->CR1 |= (0<<24); // 12 BITS DE RESOLUCIÓN
	ADC1->SMPR2|=7;//480 CICLOS
	ADC1->CR2 |= 1; // ENCENDIDO DEL ADC
}
	
void ReadLM35(void){
	ADC1->SQR3=0;//Canal 0
	ADC1->CR2|=(1<<30);
	if((ADC1->SR&2)==2){__ASM("NOP");}
	for(int i=0;i<=1000;i++){__ASM("NOP");}
	TLM35=(ADC1->DR)*8056/100000;
}


void PLL(void){
	RCC->CR|=0x10000; //Activar el oscilador HSE a 100 MHZ
	while ((RCC->CR & 0x20000)==0); //Esperar que el HSE este estabilizado
	RCC->APB1ENR=0x10000000; //Power interface clock enable
	RCC->CFGR=0x9400; //APB2 (/2) y APB1(/4)
	RCC->PLLCFGR=0x07403210; //HSE reloj de entrada al PLL; PLLM=32; PLLN=200; PLLP=2
	RCC->CR|=0x1000000; //Activar el PLL
	while((RCC->CR & 0x2000000)==0); //Esperar que el PLL este listo
	FLASH->ACR=0x205; //Activar el ART Acelerador y actializa a wait states
	RCC->CFGR|=2; //Seleccionar el PLL como la fuente de reloj del micro
}