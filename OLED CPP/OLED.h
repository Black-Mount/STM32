#include "stm32f4xx.h"  
#include "stdint.h"
#include "string.h"

#define SSD1306_WIDTH           128
#define SSD1306_HEIGHT           64
#define SSD1306_COLOR_BLACK    0x00
#define SSD1306_COLOR_WHITE    0x01

typedef struct {
	uint8_t FontWidth;  
	uint8_t FontHeight;   
	const uint16_t *data; 
} FontDef_t;

extern FontDef_t Font_16x26;

void SSD1306_UpdateScreen(void);

void SSD1306_Fill(int Color);

void SSD1306_GotoXY(uint16_t x, uint16_t y);

char SSD1306_Putc(char ch, FontDef_t* Font, int color);

char SSD1306_Puts(char* str, FontDef_t* Font, int color);

void SSD1306_Clear (void);

void oled_Init(void);