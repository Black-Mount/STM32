// Código Ejemplo 10 10 // 
// Archivo *.h //

#ifndef _GLCD12864_H
#define _GLCD12864_H
 
#include <Pines.h>
#include <FontTexto.h>
#include <Delay.h>
#include <GLcd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Clase Glcd12864 //
class GLcd12864 : public GLcd{
protected:
// Campos de memoria y variables
unsigned char Pan[1024];
Pines RS,E,RST,CS1,CS2;
Pines DD0,DD1,DD2,DD3,DD4,DD5,DD6,DD7;
void Bus(unsigned char d);
void Pastilla(bool p1,bool p2);
public:
GLcd12864(); // Constructor
void IniciarGLCD(void); // Inicio por defecto de GLcd
// Inicio por detallado de GLcd
void IniciarGLCD(int rs,int e,int rst,int cs1,int cs2,int d7,
                 int d6,int d5,int d4,int d3,int d2,int d1,int d0);
void BorrarPagina(unsigned char p); // Borrado de pagina
void Refrescar(void); // Refresco de la pantalla visible
void Test(void); // Método para grafica de prueba
void Imagen(unsigned char *img); // Grafica mapa de bits
void BorrarPantalla(void); // Borra pantalla 
void Comando(unsigned char c); // Envía comando
void Dato(unsigned char d); // Envía Dato
void SetColumna(unsigned char c); // Selecciona columna 
void SetPagina(unsigned char p); // Selecciona pagina
void Pixel(int x,int y); // Imprime pixel
void LineaX(int x,int y0,int y1); // Imprime línea X
void LineaY(int x0,int x1,int y); // Imprime línea Y
};
#endif

