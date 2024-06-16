#include <stdio.h>
#include "STM32F7xx.h"
#include <math.h>

// Ángela Hurtado			Javier Duarte
// 			  1803168						1803410

// Variable ingresada del teclado
int teclado=100;
// Ubicacion del numero ingresado para ser guardado
double dato=0; 
int decenas=100; 
int unidades=100; 
// Vector de los 2 número ingresados
double datos[2];
// Contadores de algoritmos
int contador=0;
// Bandera para procesos logicos
int aux=0; int bandera=0;
//Resultados de las operaciones aritmeticas
double suma=0;double resta=0;double mult=0; double div=0;
double seno=0;double coseno=0;
//Constante PI
double PI=3.141584;
//Variable con referencia a los numeros a mostrar
int d1=0;int d2=0;int d3=0;int d4=0;
// variables para el manejo de las operaciones
bool OperacionSeccion     = 0;
int  OperacionSeleccion   = 99;
bool BanderaGuardarNumero = 0;
bool BanderaResultado     = 0;
//Variable para el movimiento del cursor
bool Cursor = 0;
// Estado operacion LCD
int BanderaCheckVector = 0; 
int CaseOperacion = 0;
int EstadoLCD = 0;

int operaciones[4]={0x2B,0x2D,0x2A,0x2F}; // + - * /

// -------------------------------------------------------------------------
// -------------------------------- LCD ------------------------------------

//POSICIONES DE LA LCD (DIGITOS)
char pos[2][16]={0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF};

//NUMEROS DE LA LCD 
char NumLCD[12]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x2D,0X2E};
//                0     1    2    3   4    5    6    7    8    9     -   .
//Vector numero a mostar en el display
char DisplayRespuesta[4];

//Contador LCD mostrar
int ContLCD =0;

//variable Funciones Comando y dato LCD
int Cont=0;
int time1=1000;
int fila=0;
int columna=0;

// Bandera Tipo cara
bool Cara = 0;
	
char set = 0x38;
char disp_on= 0x0E;


// -- Comando LCD

char ComClear  = 0X01; // Limpiar LCD
char ComHome   = 0X02; // Seleccion a Home
char ComSet    = 0X3C; // 8 bits, 2 lineas de display, 5x10 font
char ComDisOn  = 0X0C; // Prender LCD
char ComDisOff = 0X08; // Apagar LCD
char ComMode1  = 0X06; // Incrementa cursor, modo normal
char ComMode2  = 0X04; // Incrementa cursor, desplaza al ingresar dato
char ComDisLef = 0X18; // Movimiento display izquierda
char ComDisRig = 0X1C; //	Movimiento display derecha
char ComCurLef = 0X10; // Movimiento cursor izquierda
char ComCurRig = 0X14; // Movimiento cursor derecha
char ComCurOff = 0X0C; // Apagar cursor
char ComPosLcd = 0x0;  // Posicion mostrar LCD
char ComEnCGRam = 0x40; // Habilitar memoria CGRAM
char ComEsLine1 = (0X80+ ComPosLcd);	// Posicion 0 LCD linea 1
char ComEsLine2 = (0XC0 + ComPosLcd); // Posicion 0 LCD linea 2

// -------------------------------------------------------------------------

//Lectura y guardado del numero segun sea el caso (un ó dec)
void validacion()
{

		switch (teclado){
				//Numero 0
				case 0: if     ((aux==0) && (bandera==1)){decenas=0; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=0;       teclado=100; bandera=0;}
				break;
				//Numero 1
				case 1: if     ((aux==0) && (bandera==1)){decenas=1; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=1;       teclado=100; bandera=0;}
			  break;
				//Numero 2
				case 2: if     ((aux==0) && (bandera==1)){decenas=2; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=2;       teclado=100; bandera=0;}
			  break;
				//Numero 3
				case 3: if     ((aux==0) && (bandera==1)){decenas=3; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=3;       teclado=100; bandera=0;}
			  break;
				//Numero 4
				case 4: if     ((aux==0) && (bandera==1)){decenas=4; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=4;       teclado=100; bandera=0;}
			  break;
				//Numero 5
				case 5: if     ((aux==0) && (bandera==1)){decenas=5; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=5;       teclado=100; bandera=0;}
				//Numero 6
				case 6: if     ((aux==0) && (bandera==1)){decenas=6; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=6;       teclado=100; bandera=0;}
				//Numero 7
				case 7: if     ((aux==0) && (bandera==1)){decenas=7; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=7;       teclado=100; bandera=0;}
				//Numero 8
				case 8: if     ((aux==0) && (bandera==1)){decenas=8; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=8;       teclado=100; bandera=0;}
			  break;
				//Numero 9
				case 9: if     ((aux==0) && (bandera==1)){decenas=9; aux=1; teclado=100; bandera=0;} 
								else if((aux==1) && (bandera==1)){unidades=9;       teclado=100; bandera=0;}
			  break;
			}		
}

void Suma()
{
		suma=datos[0]+datos[1];
		
		//Cuando la suma es de 3 digitos
		if(suma>99)
		{
			d1=0;
			d2=suma/100;
			d3=(suma-(d2*100))/10;
			d4=((suma-(d2*100))-(d3*10))/1;
		}
		//Cuando la suma es de 2 digitos
		else
		{
			d1=0;
			d2=0;
			d3=suma/10;
			d4=(suma-(d3*10))/1;
		}
	
		//Variables a mostrar en la LCD
		DisplayRespuesta[0] = NumLCD[d1];
		DisplayRespuesta[1] = NumLCD[d2];
		DisplayRespuesta[2] = NumLCD[d3];
		DisplayRespuesta[3] = NumLCD[d4];
		
		
}

void Resta()
{
		resta=datos[0]-datos[1];
		
		//Resultado Positivo
		if(resta>=0)
		{
			//Resultado de 2 digitos
			if(resta > 9)
			{
				d1=0;
				d2=0;
				d3=resta/10;
				d4=(resta-(d3*10))/1;
			}
			//Resultado de 1 digito
			else
			{
				d1=0;
				d2=0;
				d3=0;
				d4=resta;
			}
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[d1];
			DisplayRespuesta[1] = NumLCD[d2];
			DisplayRespuesta[2] = NumLCD[d3];
			DisplayRespuesta[3] = NumLCD[d4];
			
		}
		
		// Resultado Negativo
		else
		{
			//Pasamos el número a positivo
			resta=resta*(-1);
			
			//Resultado de 2 digitos
			if(resta > 9)
			{
				d1=0;
				d2=0;
				d3=resta/10;
				d4=(resta-(d3*10))/1;
			}
			
			//Resultado de 1 digito
			else
			{
				d1=0;
				d2=0;
				d3=0;
				d4=resta;
			}
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[10]; // Manda el signo negativo - 
			DisplayRespuesta[1] = NumLCD[d2];
			DisplayRespuesta[2] = NumLCD[d3];
			DisplayRespuesta[3] = NumLCD[d4];

		}
		
}

void Producto()
{
		mult=datos[0]*datos[1];

		//Resultado de 4 digitos
		if(mult > 999)
		{
			d1=mult/1000;
			d2=(mult-(d1*1000))/100;
			d3=(mult-(d2*100)-(d1*1000))/10;
			d4=(mult-(d3*10)-(d2*100)-(d1*1000))/1;
		}
		//Resultado de 3 digitos
		if((mult<=999) && (mult>99))
		{ 
			d1=0;
			d2=mult/100;
			d3=(mult-(d2*100))/10;
			d4=(mult-(d3*10)-(d2*100))/1;
		}
		//Resultado de 2 digitos
		if((mult<=99) && (mult>9))
		{
			d1=0;
			d2=0;
			d3=mult/10;
			d4=(mult-(d3*10))/1;
		}
		//Resultado de 1 digito
		if(mult<=9)
		{
			d1=0;
			d2=0;
			d3=0;
			d4=mult;
		}
		
		//Variables a mostrar en la LCD
		DisplayRespuesta[0] = NumLCD[d1];
		DisplayRespuesta[1] = NumLCD[d2];
		DisplayRespuesta[2] = NumLCD[d3];
		DisplayRespuesta[3] = NumLCD[d4];
}

void Division()
 {
	if(datos[1] != 0 )
	{
			div = datos [0] / datos[1];
		
			//Resultado en punto decimal inferior a 1
			if((div<1)&&(div>=0))
			{
					//Division como resultado 0.000 algo 

					div = (div * 100);
					
					//Resultado de 2 digitos
					if(div > 9)
					{
						d1=0;
						d2=0;
						d3 = div/10;
						d4 = (div-(d3*10));
					}
					//Resultado de 1 digito
					else
					{
						d1=0;
						d2=0;
						d3=0;
						d4=div;
					}
					
					//Variables a mostrar en la LCD
					DisplayRespuesta[0] = NumLCD[d1]; 
					DisplayRespuesta[1] = NumLCD[11]; // Enviamos un punto .
					DisplayRespuesta[2] = NumLCD[d3]; 
					DisplayRespuesta[3] = NumLCD[d4]; 
			}
			
			//Resultado mayor a decimal inferior a 1
			else
			{
					//Resultado de 2 digitos
					if(div > 9)
					{
						d1=0;
						d2=0;
						d3=div/10;
						d4=(div-(d3*10));
					}
					//Resultado de 1 digito
					else
					{
						d1=0;
						d2=0;
						d3=0;
						d4=div;
					}
				
					//Variables a mostrar en la LCD
					DisplayRespuesta[0] = NumLCD[d1]; 
					DisplayRespuesta[1] = NumLCD[d2]; 
					DisplayRespuesta[2] = NumLCD[d3]; 
					DisplayRespuesta[3] = NumLCD[d4]; 
				
			}
					
	}
	
	//Caso en el que Numero 2 es igual a 0
	// División indeterminada
	
	else
	{	
		d1 = 99;
		d2 = 99;
		d3 = 99;
		d4 = 99; 
		
		//Division sobre 0
		//Variables a mostrar en la LCD
		DisplayRespuesta[0] = NumLCD[10]; // Manda el --
		DisplayRespuesta[1] = NumLCD[10]; // Manda el --
		DisplayRespuesta[2] = NumLCD[10]; // Manda el --
		DisplayRespuesta[3] = NumLCD[10]; // Manda el --
	}

}

void Seno()
{
		//Realizamos la operacion
		seno=sin((datos[1]*PI)/180);

		// Resultado Positivo
		if( (seno>=0) && (seno<1) )
		{
			//Multiplicamos el seno para manejar unidades y decenas
			seno = seno*100;
			
			//Resultado de 2 digitos
			if(seno > 9)
			{
				d1=0;
				d2=0;
				d3=seno/10;
				d4=(seno-(d3*10))/1;
			}
			//Resultado de 1 digito
			else
			{
				d1=0;
				d2=0;
				d3=0;
				d4=seno;
			}
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[d1]; 
			DisplayRespuesta[1] = NumLCD[11]; // Enviamos un punto .
			DisplayRespuesta[2] = NumLCD[d3]; 
			DisplayRespuesta[3] = NumLCD[d4]; 
		}
		
		// Resultado Negativo
		if((seno<0) && (seno>-1))
		{
			//Multiplicamos el seno para manejar unidades y decenas (positivamente)
			seno = seno * (-100);
			
			//Resultado de 2 digitos
			if(seno > 9)
			{
				d1=0;
				d2=0;
				d3=seno/10;
				d4=(seno-(d3*10))/1;
			}
			//Resultado de 1 digito
			else
			{
				d1=0;
				d2=0;
				d3=0;
				d4=seno;
			}
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[10]; // Manda el signo negativo -  
			DisplayRespuesta[2] = NumLCD[d2]; 
			DisplayRespuesta[1] = NumLCD[11]; // Enviamos un punto .
			DisplayRespuesta[3] = NumLCD[d4]; 
			
		}
		
		// Resultado igual a 1
		if(seno == 1)
		{
				d1=0;
				d2=seno;
				d3=0;
				d4=0;
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[d1]; 
			DisplayRespuesta[2] = NumLCD[d2]; 
			DisplayRespuesta[1] = NumLCD[11]; // Enviamos un punto .
			DisplayRespuesta[3] = NumLCD[d4]; 	
			
		}
		
}

void Coseno()
{
		//Realizamos la operacion
		coseno= cos( ( datos[1]*PI ) /180 );

		//Resultado Positivo
		if( (coseno>=0) && (coseno<1) )
		{
			//Multiplicamos el coseno para manejar unidades y decenas
			coseno = coseno*100;
			
			//Resultado de 2 digitos
			if(coseno > 9)
			{
				d1=0;
				d2=0;
				d3=coseno/10;
				d4=(coseno-(d3*10))/1;
			}
			//Resultado de 1 digito
			else
			{
				d1=0;
				d2=0;
				d3=0;
				d4=coseno;
			}
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[d1]; 
			DisplayRespuesta[1] = NumLCD[11]; // Enviamos un punto .
			DisplayRespuesta[2] = NumLCD[d3]; 
			DisplayRespuesta[3] = NumLCD[d4]; 
		}
		
		// Resultado Negativo
		if(coseno<0 && coseno>-1)
		{
			//Multiplicamos el coseno para manejar unidades y decenas (positivamente)
			coseno = coseno * (-100);
		
			//Resultado de 2 digitos
			if(coseno > 9)
			{
				d1=0;
				d2=0;
				d3=coseno/10;
				d4=(coseno-(d3*10))/1;
			}
			//Resultado de 1 digito
			else
			{
				d1=0;
				d2=0;
				d3=0;
				d4=coseno;
			}
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[10]; // Manda el signo negativo -  
			DisplayRespuesta[2] = NumLCD[d2]; 
			DisplayRespuesta[1] = NumLCD[11]; // Enviamos un punto .
			DisplayRespuesta[3] = NumLCD[d4]; 
			
		}
		
		// Resultado igual a 1
		if(coseno == 1)
		{
			d1=0;
			d2=coseno;
			d3=0;
			d4=0;
			
			//Variables a mostrar en la LCD
			DisplayRespuesta[0] = NumLCD[d1]; 
			DisplayRespuesta[2] = NumLCD[d2]; 
			DisplayRespuesta[1] = NumLCD[11]; // Enviamos un punto .
			DisplayRespuesta[3] = NumLCD[d4]; 
			
			
		}
		
}


// FUNCIONES LCD --------------------------------------------------------------------

//Funcion para configuracion de la LCD
void FunEnvioComando(char a)
{
	GPIOB ->ODR &=0XFF00;			 			//Limpiamos (D7 a D0)
	GPIOB ->ODR |= a;   						// Enviamos el comando
	GPIOB ->ODR &=~(1UL<<8);				//RS=0 (Comando)
	GPIOB->ODR |=(1UL<<9); 					// Enable 1
	for(Cont=0;Cont<time1;Cont++);	//Delay
	GPIOB->ODR &=~(1UL<<9); 				// Enable 0
}

//Funcion para mostrar caracter en la LCD
void FunEnvioDato(char b)
{	
	GPIOB ->ODR &=0XFF00;             //Limpiamos (D7 a D0)
	GPIOB ->ODR |= b;									// Enviamos el dato
	GPIOB->ODR |=(1UL<<8);						//RS=1 (Dato)
	GPIOB->ODR |=(1UL<<9); 						// Enable 1
	for(Cont=0;Cont<time1;Cont++);		//Delay
	GPIOB->ODR &=~(1UL<<9); 					// Enable 0
}

//Mostrar LCD
void LCDMostrar()
{
			// Mostramos el numero 1
			if(BanderaCheckVector == 0)
			{
				//Mostrar el numero en que va
				FunEnvioComando(pos[0][0]);
				FunEnvioDato('(');
				
				FunEnvioDato(')');
			}

			// Mostramos la operacion seleccionada
			if(BanderaCheckVector == 1)
			{
				//Mostrar el numero en que va
				FunEnvioComando(pos[0][5]);

				if(OperacionSeccion==0)
				{
					switch (CaseOperacion)
					{
						case 0: // Suma 
						{
							FunEnvioDato(' ');
							FunEnvioDato(' ');

						}break;
						
						case 1: // Resta 
						{
							FunEnvioDato(' ');
							FunEnvioDato(' ');
						}break;
						 
						case 2: // Multiplcación
						{
							FunEnvioDato(' ');
							FunEnvioDato(' ');
						}break;
					}
						
				}
				
				else // 	
				{
						switch (CaseOperacion)
						{
							case 0: // Division 
							{
								FunEnvioDato(' ');
								FunEnvioDato(' ');
							}break;
							
							case 1: // Seno 
							{
								FunEnvioDato('S');
								FunEnvioDato('e');
								FunEnvioDato('n');
							}break;
							 
							case 2: // Coseno
							{
								FunEnvioDato('C');
								FunEnvioDato('o');
								FunEnvioDato('s');
							}break;
						}
					
				}
			
			}//FIN mostrar cuando el vector esta lleno
			
			//Mostrar número 2 ingresado
			if(BanderaCheckVector == 2)
			{
				FunEnvioComando(pos[0][9]);
				//Mostrar el numero en que va
				FunEnvioDato('(');
				// Número Vector [4]
				FunEnvioDato(')');
			}
			
			//Mostrar la respuesta tras el enter
			if(BanderaCheckVector == 3)
			{
				FunEnvioComando(pos[1][7]);
				//Mostrar el numero en que va
				FunEnvioDato('R');
				FunEnvioDato('t');
				FunEnvioDato(':');
			}
	
}

//Funcion Enter, guardar el numero ingresado, ya sea numero 1 ó numero 2
void FuncionEnter()
{
	//Creamos el numero ingresado
	dato = (decenas*10) + unidades;
	
	//Guardamos el numero en el vector
	datos[contador]=dato;
	
	//Reiniciar las variables provisionales
	decenas=100;
	unidades=100;
	
	//Reiniciar Contador numero de posicion (Decenas y unidades)
	aux=0;

}

//Funcion Aritmetica
void FuncionOperacion()
{
	if(OperacionSeccion == 0)
	{
		switch (OperacionSeleccion)
		{
			//Suma
			case 1:
			{
				//Ejecutamos funcion según operación
				Suma();
			}break;
			//Resta
			case 2:
			{
				//Ejecutamos funcion según operación
				Resta();				
			}break;
			//Multiplicacion
			case 3:
			{
				//Ejecutamos funcion según operación
				Producto();				
			}break;
		}
		
	}// Fin Operacion seccion 0
	
	
	if(OperacionSeccion == 1)
	{
		switch (OperacionSeleccion)
		{
			//Division
			case 1:
			{
				//Ejecutamos funcion según operación
				Division();
			}break;
			//Seno
			case 2:
			{
				//Ejecutamos funcion según operación
				Seno();
			}break;
			//Coseno
			case 3:
			{
				//Ejecutamos funcion según operación
				Coseno();		 		
			}break;
		}
		
	}// Fin Operacion seccion 1	
	
} //Fin funcion operacion

	
//Funcion Principal
int main(void)
{
	
	//Clocks
	RCC->AHB1ENR |= (1ul << 1); // Clock ON P-B
	RCC->AHB1ENR |= (1ul << 2); // Clock ON P-C
	RCC->AHB1ENR |= (1ul << 3); // Clock ON P-D
	RCC->APB2ENR |= 0x4000;//activación del reloj del EXTI 
	// Puerto LEDS
	GPIOD -> MODER   = 0x55555555;	//Out
	GPIOD -> OTYPER  = 0x0;         //Push Pull
	GPIOD -> OSPEEDR = 0X55555555;	// Mediumn Vel
	GPIOD -> PUPDR   = 0x55555555;  // Pull Up, Resistencia antes de la salida
	// Puerto LCD
	GPIOB -> MODER   = 0x55555555;	// Out
	GPIOB -> OTYPER  = 0x0;					// Push Pull
	GPIOB -> OSPEEDR = 0X55555555;	// Medium Vel
	GPIOB -> PUPDR   = 0x55555555; 	// Pull Up
	//Puerto C -- Implemetación del teclado Teclado
	GPIOC->MODER = 0x5500;//Filas Teclado pines 4-7 "Salidas" 
												//Columnas Teclado pines 0-3 ""Entrada"
	GPIOC->OSPEEDR = 0x5500; //Velocidad del pin, Vel intermedia, "00" bajo,"10" alto
	GPIOC->PUPDR = 0xAAAA; 
	GPIOC->OTYPER = 0; 
	//Interrupciones para el teclado
	SYSCFG->EXTICR[0]=0x2222;//interrupciones pines 0-3 puerto C
	SYSCFG->EXTICR[3]=0x0020;//interrupciones pines 15-10 puerto C pin 13
	EXTI->IMR |= 0x200F;
	EXTI->RTSR|= 0x200F;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
		
	//Config LCD
	
	FunEnvioComando(ComDisOn); // Prender la LCD
	FunEnvioComando(ComMode1); // // Incrementa cursor, modo normal 
	FunEnvioComando(ComSet);
	FunEnvioComando(ComClear);
	FunEnvioComando(ComHome);

	
	while(true)
	{
		
		// Envia un uno a todas las filas del teclado 
		// en espera de una interrupcion de las columnas
		GPIOC->ODR = 0xf0;
		//Funcion validacion de la lectura del teclado
		validacion();
		
				
		//Condicion del cursor
		if(Cursor == 0) // Posicion digito Decena 02
		{
			//Pasamos el numero a las posicion 1
			contador =0;
		}
		else            // Posicion digito Unidad 01
		{
			//Pasamos el numero a las posicion 2, la siguiente
			contador =1;
		}
		
		//Guardar numero
		if( BanderaGuardarNumero==1)
		{
			BanderaGuardarNumero = 0;
			
			//Se realiza el guardado del numero segun su posicion (contador=0) ó (contador=1)
			FuncionEnter();	
			
			//Cambianos de estado a mostrar -- LCD ---
			EstadoLCD = 1;
		}
		
		//Funcion Resultado -- Al presionar la tecla A
		if( BanderaResultado==1)
		{
			BanderaResultado = 0;
			
			//Pasamos el numero a las posicion 2, la siguiente
			contador =1;
			
			//Se realiza el guardado del numero segun su posicion (contador=0) ó (contador=1)
			FuncionEnter();
			
			//Llamamos la operacion segun la seleccion
			FuncionOperacion();	
			
			//Reiniciamos el tipo de operacion
			OperacionSeleccion=0;
			
			//Cambianos de estado a mostrar -- LCD ---
			EstadoLCD = 3;
			
		}
		
		//LCD
		if(EstadoLCD == 0)
		{
				//Mostrar el numero en que va
				FunEnvioComando(pos[0][0]);
				FunEnvioDato('(');
				FunEnvioDato(NumLCD[decenas]);
				FunEnvioDato(NumLCD[unidades]);
				FunEnvioDato(')');
		}
		if(EstadoLCD == 1)
		{
			//Mostrar el numero en que va
			FunEnvioComando(pos[0][5]);

			//  OperacionSeccion = 0
			if(OperacionSeccion==0)
			{
				switch (OperacionSeleccion)
				{
					case 1: // Suma 
					{
						FunEnvioDato(' ');
						FunEnvioDato(operaciones[0]);
						FunEnvioDato(' ');

					}break;
					
					case 2: // Resta 
					{
						FunEnvioDato(' ');
						FunEnvioDato(operaciones[1]);
						FunEnvioDato(' ');
					}break;
					 
					case 3: // Multiplcación
					{
						FunEnvioDato(' ');
						FunEnvioDato(operaciones[2]);
						FunEnvioDato(' ');
					}break;
				}
					
			}
			
			//  OperacionSeccion = 1
			else  	
			{
					switch (OperacionSeleccion)
					{
						case 1: // Division 
						{
							FunEnvioDato(' ');
							FunEnvioDato(operaciones[3]);	
							FunEnvioDato(' ');
						}break;
						
						case 2: // Seno 
						{
							FunEnvioDato('S');
							FunEnvioDato('e');
							FunEnvioDato('n');
						}break;
						 
						case 3: // Coseno
						{
							FunEnvioDato('C');
							FunEnvioDato('o');
							FunEnvioDato('s');
						}break;
					}
				
			}

			//
			// Mostramos el numero 2 del momento
	
			FunEnvioComando(pos[0][9]);
			//Mostrar el numero en que va
			FunEnvioDato('(');
			FunEnvioDato(NumLCD[decenas]);
			FunEnvioDato(NumLCD[unidades]);
			FunEnvioDato(')');
			
		}
		
		
		if(EstadoLCD == 3)
		{
			FunEnvioComando(pos[1][7]);
			
			//Mostrar el numero en que va
			FunEnvioDato('R');
			FunEnvioDato('t');
			FunEnvioDato(':');
			
			// Mostramos el vector resultado
			FunEnvioDato( DisplayRespuesta[0]);
			FunEnvioDato( DisplayRespuesta[1]);
			FunEnvioDato( DisplayRespuesta[2]);
			FunEnvioDato( DisplayRespuesta[3]);		
		}
		
		
		// Definir el estado del Led indicando la seccion de operación
		if( OperacionSeccion == 1 )
		{
			GPIOD->ODR |= (1UL<<7); //Prendemos el LED indicador
		}
		else
		{
			GPIOD->ODR &= ~(1UL<<7); //Apagamos el LED indicador
		}
	
		
	}//FinWhile
	
}//Fin main


extern "C"
{
	//Declaracin funcion Exti ------
	
	//INTERRUPCIONES POR COLUMNAS
	//COLUMNA 1 (A,B,C,D)
	void EXTI0_IRQHandler(void)
	{
		
		EXTI->PR = 0x1;
		
		//Reiniciar salida filas
		GPIOC->ODR=0;
		
		//tecla D - Multiplicacion ó Coseno
		//teclado=13;
		GPIOC->ODR = 0x10;
		if((GPIOC->IDR & 0x1)==0x1)
		{
			//Seleccionamos la operacion a trabajar
			OperacionSeleccion = 3;
			
			//Activamos la bandera para guardar el numero
			BanderaGuardarNumero = 1;

		}

		
		//tecla C --- Resta ó Seno
		//teclado=12;
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x1)==0x1)
		{
			//Seleccionamos la operacion a trabajar
			OperacionSeleccion = 2;
			
			//Activamos la bandera para guardar el numero
			BanderaGuardarNumero = 1;
			

		}
	
		
		//tecla B --- Suma ó Division
		//teclado=11;
		GPIOC->ODR=0x40;
		if((GPIOC->IDR & 0x1)==0x1)
		{
			
			//Seleccionamos la operacion a trabajar
			OperacionSeleccion = 1;
			
			//Activamos la bandera para guardar el numero
			BanderaGuardarNumero = 1;
			

		}
	
		
		//tecla A --- Enter
		//teclado=10;
		GPIOC->ODR=0x80; 
		if((GPIOC->IDR & 0x1)==0x1)
		{
			BanderaResultado=1;
			
		}//Fin if proceso
		
	}	// Fin EXTI 0
	
	
	//COLUMNA 2 (3,6,9,#)
	void EXTI1_IRQHandler(void)
	{
		EXTI->PR=0x2;
		
		//Reiniciar salida filas
		GPIOC->ODR=0;
		
		//tecla #
		GPIOC->ODR=0x10; 
		if((GPIOC->IDR & 0x2)==0x2)
		{
			//Posiciona el cursor a las posicion 2
			aux = 1;
		}
		
		//tecla 9
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x2)==0x2)
		{
			//Guardamos numero pulsado
			teclado=9;
			//Bandera  Recibe numero
			bandera=1;
		}
		
		//tecla 6
		GPIOC->ODR=0x40; 
		if((GPIOC->IDR & 0x2)==0x2)
		{
			//Guardamos numero pulsado
			teclado=6;
			//Bandera  Recibe numero
			bandera=1;
		}
		
		//tecla 3
		GPIOC->ODR=0x80; 
		if((GPIOC->IDR & 0x2)==0x2)
		{//tecla 3
			//Guardamos numero pulsado
			teclado=3;
			//Bandera  Recibe numero
			bandera=1; 
		}
	}
	
	
	//COLUMNA 3 (2,5,8,0)
	void EXTI2_IRQHandler(void)
	{
		EXTI->PR=0x4;
		
		//Reiniciar salida filas
		GPIOC->ODR=0;	
		
		//tecla 0
		GPIOC->ODR=0x10; 
		if((GPIOC->IDR & 0x4)==0x4)
		{
			//Guardamos numero pulsado
			teclado=0;
			//Bandera  Recibe numero
			bandera=1;
		}
		
		//tecla 8
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x4)==0x4)
		{
			//Guardamos numero pulsado
			teclado=8;
			//Bandera  Recibe numero
			bandera=1;
		}
		
		//tecla 5
		GPIOC->ODR=0x40; 
		if((GPIOC->IDR & 0x4)==0x4)
		{
			//Guardamos numero pulsado
			teclado=5;
			//Bandera  Recibe numero
			bandera=1;
		}
		
		//tecla 2
		GPIOC->ODR=0x80;
		if((GPIOC->IDR & 0x4)==0x4)
		{
			//Guardamos numero pulsado
			teclado=2;
			//Bandera  Recibe numero
			bandera=1;
		}
		
	}// Fin EXTI2
	
	
	//COLUMNA 4 (1,4,7,*)
	void EXTI3_IRQHandler(void)
	{
		EXTI->PR=0x8;
		
		//Reiniciar salida filas
		GPIOC->ODR=0;
			
		//tecla * --- Tipo de operación
		GPIOC->ODR=0x10; 
		if((GPIOC->IDR & 0x8)==0x8)
		{
			//Posiciona el cursor a las posicion 2
			aux = 0;
		}
		
		//tecla 7
		GPIOC->ODR=0x20; 
		if((GPIOC->IDR & 0x8)==0x8)
		{
			//Guardamos numero pulsado
			teclado=7;
			//Bandera  Recibe numero
			bandera=1;
		}
		
		//tecla 4
		GPIOC->ODR=0x40; 
		if((GPIOC->IDR & 0x8)==0x8)
		{
			//Guardamos numero pulsado
			teclado=4;
			//Bandera  Recibe numero
			bandera=1;
		}
		
		//tecla 1
		GPIOC->ODR=0x80; 
		if((GPIOC->IDR & 0x8)==0x8)
		{
			//Guardamos numero pulsado
			teclado=1;
			//Bandera  Recibe numero
			bandera=1;
		}
		
	}//Fin EXTI03
	
	//PIN 13 PUERTO C
	void EXTI15_10_IRQHandler(void)
	{
		EXTI->PR |=0x2000;
		
		OperacionSeccion = !OperacionSeccion;
	}	// Fin EXTI0 PC13
	
	
	// Final Extern C
}

