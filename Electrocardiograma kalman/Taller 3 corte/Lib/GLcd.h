// C�digo Ejemplo 10 8 // 
// Archivo *.h //
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Pines.h>
#include <FontTexto.h>
 
#ifndef _GLCD_H
#define _GLCD_H
 
// Definici�n de mascara de bits
const unsigned int BitsValue[32]={ 
 1UL<<0,1UL<<1,1UL<<2,1UL<<3,1UL<<4,1UL<<5,1UL<<6,1UL<<7,    
 1UL<<8,1UL<<9,1UL<<10,1UL<<11,1UL<<12,1UL<<13,1UL<<14,1UL<<15,
 1UL<<16,1UL<<17,1UL<<18,1UL<<19,1UL<<20,1UL<<21,1UL<<22,1UL<<23,
 1UL<<24,1UL<<25,1UL<<26,1UL<<27,1UL<<28,1UL<<29,1UL<<30,1UL<<31
};
 
// Clase GLcd //
class GLcd{
private:
 int dx,dy,Tdx,Tdy,Cx,Cy,xi,yi,Txe,Tye;
 int fx,fy;
protected:   
 unsigned char clv,chv;
 unsigned int WDis,HDis,WText,HText,BloW,BloH,BloT;
 const unsigned char *Fn;  
public:
 GLcd(); // Constructor
 virtual void IniciarGLCD(void); // M�todo para iniciar por defecto
 virtual void Pixel(int x,int y); // M�todo para imprimir un pixel  
 virtual void LineaX(int x,int y0,int y1); // M�todo para imprimir una l�nea en X
 virtual void LineaY(int x0,int x1,int y); // M�todo para imprimir una l�nea en Y
 virtual void Refrescar(void); // M�todo para refrescar la pantalla
 void SetColor(unsigned int col); // M�todo para definir el color de impresi�n 
 void Mover(int x,int y); // M�todo para mover el l�piz
 void Linea(int x,int y); // M�todo para trazar l�nea
 void Linea(int x0,int y0,int x1,int y1); // M�todo para imprimir l�nea
 // M�todo para imprimir l�nea en patr�n
 void LineaP(int x0,int y0,int x1,int y1,unsigned char p);
 // M�todo para imprimir l�nea X en patr�n
 void LineaXP(int x,int y0,int y1,unsigned char p);
 // M�todo para imprimir l�nea Y en patr�n
 void LineaYP(int x0,int x1,int y,unsigned char p);
 // M�todo para imprimir cuadrante de circulo
 void CirculoCuadrante(int x,int y,int r,unsigned char cua);
 // M�todo para imprimir cuadrante de circulo relleno 
 void CirculoCuadranteRelleno(int x,int y,int r,unsigned char cua); 
 void Circulo(int x,int y,int r); // M�todo para imprimir circulo
 void CirculoRelleno(int x,int y,int r); // M�todo para imprimir circulo relleno
 // M�todo para imprimir rect�ngulo curvo
 void RectanguloCurvo(int x0,int y0,int x1,int y1,int r);
 // M�todo para imprimir rect�ngulo curvo relleno  
 void RectanguloCurvoRelleno(int x0,int y0,int x1,int y1,int r);  
 void Rectangulo(int x0,int y0,int x1,int y1); // M�todo para imprimir rect�ngulo
 // M�todo para imprimir rect�ngulo relleno
 void RectanguloRelleno(int x0,int y0,int x1,int y1);
 void BorrarPantalla(unsigned int col); // M�todo para borrar pantalla con un color
 void BorrarPantalla(void); // M�todo para borrar pantalla 
 // M�todo para definir la fuente de texto
 void FuenteTexto(const unsigned char *font);
 int AnchoChar(char c); // M�todo para definir el ancho en pixeles de un car�cter  
 int AltoChar(void); // M�todo para definir el alto en pixeles de un car�cter 
 int AnchoTexto(char *t); // M�todo para definir el ancho en pixeles de un texto
 // Lee p�xel de un car�cter seg�n la fuente de texto 
 bool GetPixelFont(const unsigned char *font,int x,int y,char c);
 // Lee p�xel de un car�cter seg�n la fuente de texto         
 bool GetPixelFont(int x,int y,char c);         
 int PrintChar(int x,int y,char ch); // Imprime un car�cter
 void PrintTexto(int x,int y,char *t); // Imprime un texto
};
#endif

