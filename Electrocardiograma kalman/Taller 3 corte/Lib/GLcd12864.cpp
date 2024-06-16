// Código Ejemplo 10 11 // 
// Archivo *.cpp //
#include <GLcd12864.h>

GLcd12864::GLcd12864(){}

void GLcd12864::IniciarGLCD(void){
 WDis=128;HDis=64;
 clv=0;chv=0;
 IniciarGLCD(DP9,DP8,AP1,AP0,DP12,DP11,DP10,DP2,DP3,DP4,DP5,DP6,DP7);
}

void GLcd12864::Pastilla(bool p1,bool p2){CS1=!p1;CS2=!p2;}

void GLcd12864::IniciarGLCD(int rs,int e,int rst,int cs1,int cs2,
	                          int d7,int d6,int d5,int d4,int d3,int d2,int d1,int d0){
  RS>>rs;RS=0;
  E>>e;E=0;
  RST>>rst;RST=0;
  CS1>>cs1;CS1=0;
  CS2>>cs2;CS2=0;
  DD0>>d0;
  DD1>>d1;
  DD2>>d2;
  DD3>>d3;
  DD4>>d4;
  DD5>>d5;
  DD6>>d6;
  DD7>>d7;
	IniciarDelay();
	delay(100);
  RST=0;delay(20);
  RST=1;delay(20);
  Pastilla(1,0);Comando(0x3F);
  Pastilla(0,1);Comando(0x3F);
  BorrarPantalla();
  Refrescar();
  SetColor(1);
}

void GLcd12864::Test(void){
  BorrarPantalla();
  SetColor(1);
  FuenteTexto(System14x14);
  RectanguloCurvo(0,0,127,63,5);
  RectanguloCurvo(2,2,125,61,3);
  PrintTexto(6,6,"Test Pantalla");
  PrintTexto(6,20,"GLcd 128x64");
  PrintTexto(6,34,"KS0108");
  Refrescar();
}

void GLcd12864::Bus(unsigned char d){
  DD0 = (bool)(d&1);
  DD1 = (bool)(d&2);
  DD2 = (bool)(d&4);
  DD3 = (bool)(d&8);
  DD4 = (bool)(d&16);
  DD5 = (bool)(d&32);
  DD6 = (bool)(d&64);
  DD7 = (bool)(d&128);
}

void GLcd12864::Refrescar(void){    
    for(unsigned char p=0;p<8;p++){
     Pastilla(1,0);
     SetPagina(p);
     SetColumna(0);
     RS=1;
     for(unsigned char x=0;x<64;x++){
       Bus( Pan[p*128+x] );delayMicroseconds(5);E=1;delayMicroseconds(5);E=0;
     }
     Pastilla(0,1);
     SetPagina(p);
     SetColumna(0);
     RS=1;
     for(unsigned char x=64;x<128;x++){
       Bus( Pan[p*128+x] );delayMicroseconds(5);E=1;delayMicroseconds(5);E=0;
     }
    }
}

void GLcd12864::BorrarPagina(unsigned char p){ 
  for(unsigned char n=0;n<128;n++)Pan[p*128+n]=0;
}

void GLcd12864::BorrarPantalla(void){
  for(int n=0;n<1024;n++)Pan[n]=0;
}

void GLcd12864::Imagen(unsigned char *img){
  for(int n=0;n<1024;n++)Pan[n]=img[n];
}

void GLcd12864::Comando(unsigned char c){
  RS=0;
  Bus(c);delayMicroseconds(5);
  E=1;delayMicroseconds(5);
  E=0;
}

void GLcd12864::Dato(unsigned char d){
  RS=1;
  Bus(d);delayMicroseconds(5);
  E=1;delayMicroseconds(5);
  E=0;
}

void GLcd12864::SetColumna(unsigned char c)
{Comando(0x40|(c&0x3F));}

void GLcd12864::SetPagina(unsigned char p)
{Comando(0xB8|(p&0x07));}

void GLcd12864::Pixel(int x,int y){
  unsigned char p,pi;
  p=y/8;
  pi=y-p*8;
 if( clv==1 ){
    switch(pi){ 
      case 0: Pan[p*128+x] |= 0x01; break; 
      case 1: Pan[p*128+x] |= 0x02; break; 
      case 2: Pan[p*128+x] |= 0x04; break; 
      case 3: Pan[p*128+x] |= 0x08; break; 
      case 4: Pan[p*128+x] |= 0x10; break; 
      case 5: Pan[p*128+x] |= 0x20; break;    
      case 6: Pan[p*128+x] |= 0x40; break; 
      case 7: Pan[p*128+x] |= 0x80; break;
      default:break;
    }
 }
 else{
   switch(pi){ 
      case 0: Pan[p*128+x] &= ~0x01; break; 
      case 1: Pan[p*128+x] &= ~0x02; break; 
      case 2: Pan[p*128+x] &= ~0x04; break; 
      case 3: Pan[p*128+x] &= ~0x08; break; 
      case 4: Pan[p*128+x] &= ~0x10; break; 
      case 5: Pan[p*128+x] &= ~0x20; break;    
      case 6: Pan[p*128+x] &= ~0x40; break; 
      case 7: Pan[p*128+x] &= ~0x80; break;
      default:break;
    }
 }
} 

void GLcd12864::LineaX(int x,int y0,int y1){for(int y=y0;y<=y1;y++)Pixel(x,y);}
void GLcd12864::LineaY(int x0,int x1,int y){for(int x=x0;x<=x1;x++)Pixel(x,y);}

