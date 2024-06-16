// Código Ejemplo 10 8 // 
// Archivo *.h //
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Pines.h>
#include <FontTexto.h>
 
#ifndef _GLCD_H
#define _GLCD_H
 
// Definición de mascara de bits
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
 virtual void IniciarGLCD(void); // Método para iniciar por defecto
 virtual void Pixel(int x,int y); // Método para imprimir un pixel  
 virtual void LineaX(int x,int y0,int y1); // Método para imprimir una línea en X
 virtual void LineaY(int x0,int x1,int y); // Método para imprimir una línea en Y
 virtual void Refrescar(void); // Método para refrescar la pantalla
 void SetColor(unsigned int col); // Método para definir el color de impresión 
 void Mover(int x,int y); // Método para mover el lápiz
 void Linea(int x,int y); // Método para trazar línea
 void Linea(int x0,int y0,int x1,int y1); // Método para imprimir línea
 // Método para imprimir línea en patrón
 void LineaP(int x0,int y0,int x1,int y1,unsigned char p);
 // Método para imprimir línea X en patrón
 void LineaXP(int x,int y0,int y1,unsigned char p);
 // Método para imprimir línea Y en patrón
 void LineaYP(int x0,int x1,int y,unsigned char p);
 // Método para imprimir cuadrante de circulo
 void CirculoCuadrante(int x,int y,int r,unsigned char cua);
 // Método para imprimir cuadrante de circulo relleno 
 void CirculoCuadranteRelleno(int x,int y,int r,unsigned char cua); 
 void Circulo(int x,int y,int r); // Método para imprimir circulo
 void CirculoRelleno(int x,int y,int r); // Método para imprimir circulo relleno
 // Método para imprimir rectángulo curvo
 void RectanguloCurvo(int x0,int y0,int x1,int y1,int r);
 // Método para imprimir rectángulo curvo relleno  
 void RectanguloCurvoRelleno(int x0,int y0,int x1,int y1,int r);  
 void Rectangulo(int x0,int y0,int x1,int y1); // Método para imprimir rectángulo
 // Método para imprimir rectángulo relleno
 void RectanguloRelleno(int x0,int y0,int x1,int y1);
 void BorrarPantalla(unsigned int col); // Método para borrar pantalla con un color
 void BorrarPantalla(void); // Método para borrar pantalla 
 // Método para definir la fuente de texto
 void FuenteTexto(const unsigned char *font);
 int AnchoChar(char c); // Método para definir el ancho en pixeles de un carácter  
 int AltoChar(void); // Método para definir el alto en pixeles de un carácter 
 int AnchoTexto(char *t); // Método para definir el ancho en pixeles de un texto
 // Lee píxel de un carácter según la fuente de texto 
 bool GetPixelFont(const unsigned char *font,int x,int y,char c);
 // Lee píxel de un carácter según la fuente de texto         
 bool GetPixelFont(int x,int y,char c);         
 int PrintChar(int x,int y,char ch); // Imprime un carácter
 void PrintTexto(int x,int y,char *t); // Imprime un texto
};
#endif

