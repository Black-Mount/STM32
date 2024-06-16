#include "Init.h"
#include "oled.h"
#include "i2c.h"

char Pal[12]={'|','T','A','L','L','E','R',' ','R','P','M','|'};
char var[12]={'R','P','M','=','>'};




void Interfaz_OLED(){
	OLED_Clear();

	OLED_DrawLine(5, 5, 123, 5, OLED_COLOR_WHITE);
	OLED_DrawLine(5, 5, 5, 60, OLED_COLOR_WHITE);
	OLED_DrawLine(5, 60, 123, 60, OLED_COLOR_WHITE);
	OLED_DrawLine(123, 5, 123, 60, OLED_COLOR_WHITE);
	OLED_GotoXY (25,10);
	OLED_Puts (Pal, &Font_7x10, 1);// titulo
	OLED_GotoXY (15,35);
	OLED_Puts (var, &Font_7x10, 1);
  OLED_UpdateScreen();
}


