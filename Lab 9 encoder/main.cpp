#include "stm32f4xx.h"
#include "Numeros_Nokia.h"



float rpm = 0,velocidad = 0,conver = 0,potenciometro=0,tiempo = 0;
int cont_init = 0,cont_usart=0,conta = 0,siu = 0,vueltas = 0,cen = 0,unid = 0,dec = 0,mil = 0,mil2 = 0,n = 0;
double tiempo_transcurrido;
char modo;
char control_pwm2;
char manual2;


void adc_config(void){
	  RCC -> APB2ENR |= (1UL<<14);
	RCC -> APB2ENR |= 0x100;				//Habilitar el ADC1
	GPIOB -> MODER|= 0XC; //0000 0000 1100
	
	ADC1->CR1|=0;
	ADC1->SQR3=9	;//activa canal 9 osea B1
	ADC1->CR2=0;//desactivar conversion T1
	Delay(100);//esperar
	ADC1->CR2=1;//activa conversion
}
void hall_config(void) {
	RCC->APB1ENR|=RCC_APB1ENR_TIM5EN; // Activa reloj TIM2
  TIM5->CNT=0xFFFFFFFF; // Valor inicial del contador
  TIM5->CR1|=TIM_CR1_CEN; // Encendido del TIM2
  // Periodo de 1 usegundo
  TIM5->ARR=999;//63999; 999
  TIM5->PSC=15;//249;15
  NVIC_EnableIRQ(TIM5_IRQn); // Activa interrupción
  TIM5->DIER|=TIM_DIER_UIE; // Enciende interrupción TIM2
}
void pwm_config(void) {
	 GPIOA->MODER|= 0X80000000; //0X800 Pin PA15 modo alternativo 1000 0000 0000 0000 0000 0000 0000 0000 
	GPIOA->AFR[1]|=0X10000000; // Función alternativa 1 en pin PA15
  RCC->APB1ENR|=(1UL<<0); // Activa reloj TIM2
	TIM2->CNT=0xFFFFFFFF; // Valor inicial del contador
	TIM2->CR1|=(1UL<<0); // Encendido del TIM2
	// Periodo de 1 segundo
	TIM2->ARR=567;
	TIM2->PSC=567;
	TIM2->CCMR1|=(7UL<<TIM_CCMR1_OC1M_Pos); // Modo PWM
	TIM2->CCMR1|=TIM_CCMR1_OC1PE; // Comparador activo
	TIM2->CCER|=(TIM_CCER_CC1P| TIM_CCER_CC1E);
	TIM2->CR1|=TIM_CR1_ARPE; // Recarga activa
	TIM2->CR1|=TIM_CR1_CEN; // Activo modulo compa	rador
	TIM2->BDTR|=TIM_BDTR_MOE; // Outputs activos
}
void config_usart(void) {
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
}
void sendUsart(){
	
		USART2->DR=(int)(rpm/2);
	Delay(100);
	
	}
void sentido_adelante(void){
	GPIOC -> ODR = 0X1; //Girar motores hacia adelante 
	//Delay(time);                    // Esperar por 10 segundos 
}
void sentido_atras(void){
	GPIOC -> ODR = 0x2; //Girar motores hacia atrás
	//Delay(time); 	
}
void giro_derecha(void){
	GPIOC -> ODR |= (1<<3); //| (1<<0);
	//Delay(time);
}

void giro_izquierda(void){
	GPIOC -> ODR |= (1<<1); //| (1<<2);
	//Delay(time);
}

void detener(void){
	GPIOC -> ODR &= ~(1<<0) & ~(1<<1) & ~(1<<2) & ~(1<<3);
	//Delay(time);
}




extern "C"{
 void TIM5_IRQHandler(void){
  TIM5->SR&=(~TIM_SR_UIF); // Apagado de bandera
	 if(cont_init == 1){
   tiempo++;}
 }
 
 	void EXTI0_IRQHandler(void){
		EXTI ->PR |= 0X8007; 
		vueltas++;
		if(cont_init == 0){
			cont_init = 1;
			tiempo = 0; 
			tiempo_transcurrido = 0;
		}else{
			cont_init = 0;
			tiempo_transcurrido = tiempo;
			rpm = (60000.0/(tiempo_transcurrido));
			velocidad = (rpm *(2.0* 3.141592))/60.0;
			if(rpm>9999){rpm=9999;}
			
			 
	mil = rpm/1000;
	n = (int)rpm%1000;
	cen = n/100;
	n= n%100;
	dec = n/10;
	n= n%10;
	unid = n;
 
 Delay(500);
 
 rpm = 0;
		}	
		
	}
	
		void USART2_IRQHandler(void){
		cont_usart++;
		unsigned char Dato;
		Dato=USART2->SR; // Limpiar banderas
		Dato=USART2->DR; // Lee dato
		if(cont_usart==1){
		modo = Dato;}
			
			if(modo == 'V'){
		    control_pwm2=Dato; // Lee dato
				
				if(control_pwm2 == 'V'){modo='V'; cont_usart=1;}
				if(control_pwm2 == 'M'){modo='M'; cont_usart=1;}
				if(control_pwm2 == 'D'){modo='V'; sentido_adelante();}
				if(control_pwm2 == 'I'){modo='V'; sentido_atras();}
				
			}else if(modo == 'M'){
				manual2 = Dato;
				if(manual2 == 'V'){modo='V'; cont_usart=1;}
				if(manual2 == 'M'){modo='M'; cont_usart=1;}
			}
	 }
}

int main(void){
	
	RCC->AHB1ENR|= 0X7; // Activa relojes
	confi_Nokia();

	
	RCC ->APB2ENR |= (1UL<<14);               //Encender el Reloj de las interrupciones
	EXTI -> FTSR |= 0X1;
	EXTI -> IMR |= 0X1;                  //Activar las interrupcion 0
	SYSCFG -> EXTICR[0] |= 0X0001;         //Interrupciones en PB0 0000 0000 0000 0001
	NVIC_EnableIRQ(EXTI0_IRQn);       //Activa Interrupción 0
	adc_config();
	hall_config();
	pwm_config();
	config_usart();
	
 //Puente h
 GPIOC -> MODER |= 0X55; 
 
while(1){

	
	ADC1->CR2|=0X40000000; //inicia conversion en canales regulares
	while((ADC1->SR &0X2)==1){asm("nop");}
	conver = ADC1 -> DR; 
	potenciometro = (conver/4095.0)*100.0;
		
	sendUsart();
	
 send_comand_nokia(Xaddress);
 send_comand_nokia(Yaddress);
 escribir5x7('R');escribir5x7('P');escribir5x7('M'); escribir5x7(':');
 escribir5x7(mil+48);
 escribir5x7(cen+48);
 escribir5x7(dec+48);
 escribir5x7(unid+48);
 escribir5x7(' ');

		
		
	if(modo == 'M'){
		
		
		send_comand_nokia(Yaddress+5);
		send_comand_nokia(Xaddress);
		escribir5x7('M');escribir5x7('o');escribir5x7('d');escribir5x7('o');escribir5x7(':');escribir5x7(' ');
		escribir5x7('M');escribir5x7('A');escribir5x7('N');escribir5x7('U');escribir5x7('A');escribir5x7('L');escribir5x7(' ');
		
		if(potenciometro>=0 && potenciometro<=49){
			sentido_adelante();
			float siu1=0;
			siu1 = (((50.0-potenciometro)/100.0)*2.0);
					if(siu1*100>99){siu1=0.99;}
			TIM2->CCR1=(567*(siu1)); // 
		
			send_comand_nokia(Yaddress+2);
			send_comand_nokia(Xaddress);
			escribir5x7(((siu1*100)/10)+48);
			escribir5x7(((int)(siu1*100)%10)+48);escribir5x7('%');
			escribir5x7(' ');escribir5x7('D');escribir5x7('e');escribir5x7('r');escribir5x7(' ');escribir5x7(' ');escribir5x7(' ');
	}else{
		if(potenciometro>=51 && potenciometro<=100){
			sentido_atras();
			float siu2 = 0;
			siu2 = (((potenciometro-50.0)/100.0)*2.0);
			if(siu2*100>99){siu2=0.99;}
			TIM2->CCR1=(567*(siu2)); //
		  send_comand_nokia(Yaddress+2);
	    send_comand_nokia(Xaddress);
	    escribir5x7(((siu2*100)/10)+48);
			escribir5x7(((int)(siu2*100)%10)+48);escribir5x7('%');
			escribir5x7(' ');escribir5x7('I');escribir5x7('z');escribir5x7('q');escribir5x7(' ');escribir5x7(' ');escribir5x7(' ');
		}else{if(potenciometro==50){detener();}}
	}
	
	}else{
		if(modo=='V'){
		
		send_comand_nokia(Yaddress+5);
		send_comand_nokia(Xaddress);
		escribir5x7('M');escribir5x7('o');escribir5x7('d');escribir5x7('o');escribir5x7(':');escribir5x7(' ');
		escribir5x7('V');escribir5x7('I');escribir5x7('R');escribir5x7('T');escribir5x7('U');escribir5x7('A');escribir5x7('L');
		
		TIM2->CCR1=(567*((control_pwm2-48)*11)/100);
    send_comand_nokia(Yaddress+2);
		send_comand_nokia(Xaddress);
			
		if((control_pwm2-48)>=0 && (control_pwm2-48)<10){
			escribir5x7('V');escribir5x7('i');escribir5x7('r');escribir5x7(':');escribir5x7(' '); escribir5x7(control_pwm2);
		escribir5x7('0');escribir5x7('%');escribir5x7(' ');escribir5x7(' ');escribir5x7(' ');
		}
		}
	
	}
}

return 0; 

}