// Código Ejemplo 10 9 // 
// Archivo *.cpp //
#include <GLcd.h>

GLcd::GLcd() // Constructor
{
 fx=0;fy=0;
 WDis=0;HDis=0;
 clv=0;chv=0;
 FuenteTexto(Lcd5x7);
}

void GLcd::IniciarGLCD(void){} // Método para iniciar por defecto
	
void GLcd::Pixel(int x,int y){} // Método para imprimir un pixel
	
void GLcd::LineaX(int x,int y0,int y1){} // Método para imprimir una línea en X
	
void GLcd::LineaY(int x0,int x1,int y){} // Método para imprimir una línea en Y
	
void GLcd::Refrescar(void){} // Método para refrescar la pantalla

// Método para definir el color de impresión 
void GLcd::SetColor(unsigned int col){clv=col&255;chv=(col>>8)&255;}

void GLcd::Mover(int x,int y){fx=x;fy=y;}// Método para mover el lápiz

// Método para trazar línea
void GLcd::Linea(int x,int y){Linea(fx,fy,x,y);Mover(x,y);}

// Método para imprimir línea
void GLcd::Linea(int x0,int y0,int x1,int y1)
{
 if(x0==x1){LineaX(x0,y0,y1);return;}
 if(y0==y1){LineaY(x0,x1,y0);return;}
 dx=(x1-x0);dy=(y1-y0);
 Tdx=2*dx;Tdy=2*dy;Cx=x0;Cy=y0;xi=1;yi=1;
 if(dx<0){xi=-1;dx=-dx;Tdx=-Tdx;}
 if(dy<0){yi=-1;dy=-dy;Tdy=-Tdy;}	
 Pixel(x0,y0);Pixel(x1,y1);
 if (dy<=dx)
 {Txe=0;do{Cx+=xi;Txe+=Tdy;if(Txe>dx){Cy+=yi;Txe-=Tdx;}Pixel(Cx,Cy);}while(Cx!=x1);}
 else
 {Tye=0;do{Cy+=yi;Tye+=Tdx;if(Tye>dy){Cx+=xi;Tye-=Tdy;}Pixel(Cx,Cy);}while(Cy!=y1);}
}

// Método para imprimir línea en patrón
void GLcd::LineaP(int x0,int y0,int x1,int y1,unsigned char p)
{
 unsigned char pa=0; 
 if(x0==x1){LineaX(x0,y0,y1);return;}
 if(y0==y1){LineaY(x0,x1,y0);return;}
 dx=(x1-x0);dy=(y1-y0);
 Tdx=2*dx;Tdy=2*dy;Cx=x0;Cy=y0;xi=1;yi=1;
 if(dx<0){xi=-1;dx=-dx;Tdx=-Tdx;}
 if(dy<0){yi=-1;dy=-dy;Tdy=-Tdy;}	
 Pixel(x0,y0);Pixel(x1,y1);
 if (dy<=dx)
 {Txe=0;do{Cx+=xi;Txe+=Tdy;if(Txe>dx){Cy+=yi;Txe-=Tdx;} 
 if(BitsValue[pa]&p)Pixel(Cx,Cy);pa++;if(pa==8)pa=0; }while(Cx!=x1);}
 else
 {Tye=0;do{Cy+=yi;Tye+=Tdx;if(Tye>dy){Cx+=xi;Tye-=Tdy;} 
 if(BitsValue[pa]&p)Pixel(Cx,Cy);pa++;if(pa==8)pa=0; }while(Cy!=y1);}
}

// Método para imprimir línea X en patrón
void GLcd::LineaXP(int x,int y0,int y1,unsigned char p)
{
 unsigned char pa=0;  
 for(int y=y0;y<=y1;y++){if(BitsValue[pa]&p)Pixel(x,y);pa++;if(pa==8)pa=0;}
}

// Método para imprimir línea Y en patrón
void GLcd::LineaYP(int x0,int x1,int y,unsigned char p)
{
  unsigned char pa=0;
 for(int x=x0;x<=x1;x++){if(BitsValue[pa]&p)Pixel(x,y);pa++;if(pa==8)pa=0;}
}

// Método para imprimir cuadrante de circulo
void GLcd::CirculoCuadrante(int x,int y,int r,unsigned char cua)
{
 int _x,_y,xc,yc,re;
 _x=r;_y=0;xc=1-2*r;yc=1;re=0;
 while(_x>=_y)
 {			
  if(cua&1){Pixel(x+_x, y-_y);Pixel(x+_y, y-_x);}	
  if(cua&2){Pixel(x-_x, y-_y);Pixel(x-_y, y-_x);}
  if(cua&4){Pixel(x-_x, y+_y);Pixel(x-_y, y+_x);}
  if(cua&8){Pixel(x+_x, y+_y);Pixel(x+_y, y+_x);}
  _y++;re+=yc;yc+=2;
  if(2*re+xc>0){_x--;re+=xc;xc+=2;}
 }		
}

// Método para imprimir circulo
void GLcd::Circulo(int x,int y,int r){CirculoCuadrante(x,y,r,15);}

// Método para imprimir circulo relleno
void GLcd::CirculoRelleno(int x,int y,int r)
{
  int _x,_y,xc,yc,re;
  _x=r;_y=0; 
	xc=1-2*r;
	yc=1;re=0;
	while(_x>=_y)
  {
		LineaY(x-_x,x+_x,y-_y);	
		LineaY(x-_y,x+_y,y-_x); 
		LineaY(x-_x,x+_x,y+_y);	
		LineaY(x-_y,x+_y,y+_x);   				
    _y++;re+=yc;yc+=2;
    if(2*re+xc>0){_x--;re+=xc;xc+=2;}
  }
}

// Método para imprimir rectángulo curvo
void GLcd::RectanguloCurvo(int x0,int y0,int x1,int y1,int r)
{
	if(r<=0)
  {
    LineaX(x0,y0,y1);LineaX(x1,y0,y1);
	  LineaY(x0,x1,y0);LineaY(x0,x1,y1);
    return;
  }
	int x00,y00,x11,y11,ree=r;
	if(x1>x0){x11=x1;x00=x0;} else {x11=x0;x00=x1;}
	if(y1>y0){y11=y1;y00=y0;} else {y11=y0;y00=y1;}
	if(2*ree>(x11-x00))ree=(x11-x00)/2;
	if(2*ree>(y11-y00))ree=(y11-y00)/2;
	LineaX(x00,y00+ree,y11-ree);LineaX(x11,y00+ree,y11-ree);
	LineaY(x00+ree,x11-ree,y00);LineaY(x00+ree,x11-ree,y11);
	CirculoCuadrante(x11-ree,y00+ree,ree,1);
  CirculoCuadrante(x00+ree,y00+ree,ree,2);
	CirculoCuadrante(x00+ree,y11-ree,ree,4);
	CirculoCuadrante(x11-ree,y11-ree,ree,8);
}

// Método para imprimir rectángulo curvo relleno
void GLcd::RectanguloCurvoRelleno(int x0,int y0,int x1,int y1,int r)
{
  int ree,x00,y00,x11,y11;
	if(r<=0){RectanguloRelleno(x0,y0,x1,y1);return;}
		ree=r;
		if(x1>x0){x11=x1;x00=x0;} else {x11=x0;x00=x1;}
		if(y1>y0){y11=y1;y00=y0;} else {y11=y0;y00=y1;}
		if(2*ree>(x11-x00))ree=(x11-x00)/2;
		if(2*ree>(y11-y00))ree=(y11-y00)/2;
		RectanguloRelleno(x00+ree,y00,x11-ree,y00+ree);
		RectanguloRelleno(x00+ree,y11-ree,x11-ree,y11);
		RectanguloRelleno(x00+ree,y00+ree,x11-ree,y11-ree);
		RectanguloRelleno(x00,y00+ree,x00+ree,y11-ree);
		RectanguloRelleno(x11-ree,y00+ree,x11,y11-ree);
		CirculoCuadranteRelleno(x11-ree,y00+ree,ree,1);
    CirculoCuadranteRelleno(x00+ree,y00+ree,ree,2);
		CirculoCuadranteRelleno(x00+ree,y11-ree-1,ree,4);
		CirculoCuadranteRelleno(x11-ree,y11-ree-1,ree,8);	
}

// Método para imprimir rectángulo
void GLcd::Rectangulo(int x0,int y0,int x1,int y1){RectanguloCurvo(x0,y0,x1,y1,0);}

// Método para imprimir rectángulo relleno
void GLcd::RectanguloRelleno(int x0,int y0,int x1,int y1){for(int y=y0;y<=y1;y++)LineaY(x0,x1,y);}

// Método para imprimir cuadrante de circulo relleno 
void GLcd::CirculoCuadranteRelleno(int x,int y,int r,unsigned char cua)
{
  int _x,_y,xc,yc,re;
	_x=r;_y=0; 
	xc=1-2*r;
	yc=1;re=0;
	while(_x>=_y)
  {
		if(cua&1){LineaY(x,x+_x,y-_y);LineaY(x,x+_y,y-_x);}
		if(cua&2){LineaY(x-_x,x,y-_y);LineaY(x-_y,x,y-_x);}
		if(cua&4){LineaY(x-_x,x,y+_y);LineaY(x-_y,x,y+_x);}
		if(cua&8){LineaY(x,x+_x,y+_y);LineaY(x,x+_y,y+_x);}	
    _y++;re+=yc;yc+=2;
    if(2*re+xc>0){_x--;re+=xc;xc+=2;}
  }
}

// Método para borrar pantalla con un color
void GLcd::BorrarPantalla(unsigned int col){SetColor(col);BorrarPantalla();}

// Método para borrar pantalla
void GLcd::BorrarPantalla(void){RectanguloRelleno(0,0,WDis,HDis);}

// Método para definir la fuente de texto
void GLcd::FuenteTexto(const unsigned char *font)
{
  	WText=font[0];
	  HText=font[1]; 
	  for(int n=8;n>=1;n--)if(HText<=(n*8))BloH=n;
		BloW=WText;BloT=(BloH*BloW+1);
	  Fn=font;
}

// Método para definir el ancho en pixeles de un carácter 
int GLcd::AnchoChar(char c)
{
  int Ini = (c-32)*BloT;
	return (int)Fn[Ini+2];
}

// Método para definir el alto en pixeles de un carácter
int GLcd::AltoChar(void){return HText;}

// Método para definir el ancho en pixeles de un texto
int GLcd::AnchoTexto(char *t){int anc=0,n=0;while(t[n]!=0)anc+=(AnchoChar(t[n++])+1);return anc;}

// Lee píxel de un carácter según la fuente de texto 
bool GLcd::GetPixelFont(const unsigned char *font,int x,int y,char c)
{
  	int Ini,dy,bit,pos;
    Ini=(c-32)*BloT;
		dy = y/8;
		bit = y-dy*8;
		pos = 1+BloH*x + dy + Ini;
		if( font[pos+2]&BitsValue[bit] )return true;
		return false;
}

// Lee píxel de un carácter según la fuente de texto 
bool GLcd::GetPixelFont(int x,int y,char c){return GetPixelFont(Fn,x,y,c);}

// Imprime un carácter
int GLcd::PrintChar(int x,int y,char ch)
{
  	int w;
	  w=AnchoChar(ch);
		for( int xx=0;xx<w;xx++ )
		 for(int yy=0;yy<HText;yy++)
			if(GetPixelFont(xx,yy,ch))Pixel(xx+x,yy+y);
		return w+1;
}

// Imprime un texto
void GLcd::PrintTexto(int x,int y,char *t)
{
  	int n=0,px=x;if(t[0]==0)return; 	
		while(t[n]!=0)px+=PrintChar(px,y,t[n++]);
}
