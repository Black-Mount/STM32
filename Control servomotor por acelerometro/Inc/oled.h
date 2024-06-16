#include "stm32f4xx.h"  
#include "fonts.h"

#define I2C_ADDR  0x3C
#define SSD1306_WIDTH            128
#define SSD1306_HEIGHT           64

typedef enum {
	SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
	SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;

uint8_t SSD1306_Init(void);

void SSD1306_UpdateScreen(void);

void SSD1306_Fill(SSD1306_COLOR_t Color);

void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);

void SSD1306_GotoXY(uint16_t x, uint16_t y);

char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);

char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);

void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, char* data, uint16_t count);

void SSD1306_Clear (void);

void oled_Init(void);

