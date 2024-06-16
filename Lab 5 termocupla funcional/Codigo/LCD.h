#include <stm32f4xx.h>
#define delayLCD for(int i=0;i<10000;i++){asm("nop");}
#define GPIOX GPIOB->ODR

class LCD{
	public:
		char Symbol[8]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7};//Vector que almacena los caracteres especiales
		char SetL1=0x80;//Dirección Linea 1
		char SetL2=0xC0;//Dirección Linea 2
		char CGram=0x40;//Dirección Memoria SpecialCharts
		char Mode=0x06;//Modo de cursor
		void Config();//Configura la LCD con lo básico
		void Set(char);//Recibe un número HEX para enviar datos a la LCD
		void WriteWord(char[],int,int);//Recibe un Arreglo de Char, su inicio y su fin para escribir palabras en la LCD
		void WriteLetter(char);//Recibe un caracter para escribir en la LCD
		void SetSpecialChart(char[]);//Recibe un arreglo el cuál contiene el caracter especial a guardar
		void SaveSpecialCharts();//Guarda los Caracteres personalizados
		void Clear();//Limpia la pantalla
};