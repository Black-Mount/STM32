#include "stm32f4xx.h"  
#include "fonts.h"
#include "stdlib.h"
#include "string.h"

#define OLED_I2C_ADDR         0x3C
//#define OLED_I2C_ADDR       0x7A
#define OLED_WIDTH            128
#define OLED_HEIGHT           64

typedef enum {
	OLED_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	OLED_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} OLED_COLOR_t;

//uint8_t OLED_Init(void);

void OLED_UpdateScreen(void);
void OLED_Fill(OLED_COLOR_t Color);
void OLED_DrawPixel(uint16_t x, uint16_t y, OLED_COLOR_t color);
void OLED_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, OLED_COLOR_t color);
void OLED_GotoXY(uint16_t x, uint16_t y);
char OLED_Putc(char ch, FontDef_t* Font, OLED_COLOR_t color);
char OLED_Puts(char* str, FontDef_t* Font, OLED_COLOR_t color);
void OLED_I2C_WriteMulti(uint8_t address, uint8_t reg, char* data, uint16_t count);
void OLED_Clear (void);
void OLED_Init(void);
