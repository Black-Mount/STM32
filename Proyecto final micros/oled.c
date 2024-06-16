#include "oled.h"
#include "i2c.h"
#define OLED_NORMALDISPLAY       0xA6
#define OLED_INVERTDISPLAY       0xA7
static char OLED_Buffer[OLED_WIDTH * OLED_HEIGHT / 8];



typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} OLED_t;


static OLED_t OLED;

void OLED_Init(void) {
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xAE); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x20); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x10); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xB0); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xC8);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x00); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x10); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x40);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x81); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xFF);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xA1); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xA6);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xA8);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x3F);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xA4); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xD3); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x00); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xD5); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xF0); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xD9);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x22); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xDA); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x12);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xDB); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x20);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x8D);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x14); 
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xAF);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x2E); 
	OLED_Fill(OLED_COLOR_BLACK);
	OLED_UpdateScreen();
}

void OLED_UpdateScreen(void) {
	uint8_t m;
	
	for (m = 0; m < 8; m++) {
		I2C_writeByte(OLED_I2C_ADDR, 0x00,0xB0 + m);
		I2C_writeByte(OLED_I2C_ADDR, 0x00,0x00);
		I2C_writeByte(OLED_I2C_ADDR, 0x00,0x10);
		OLED_I2C_WriteMulti(OLED_I2C_ADDR, 0x40, &OLED_Buffer[OLED_WIDTH * m], OLED_WIDTH);
	}
}

void OLED_Fill(OLED_COLOR_t color) {
	memset(OLED_Buffer, (color == OLED_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(OLED_Buffer));
}

void OLED_GotoXY(uint16_t x, uint16_t y) {
	OLED.CurrentX = x;
	OLED.CurrentY = y;
}

void OLED_DrawPixel(uint16_t x, uint16_t y, OLED_COLOR_t color) {
	if (
		x >= OLED_WIDTH ||
		y >= OLED_HEIGHT
	) {
		return;
	}

	if (OLED.Inverted) {
		color = (OLED_COLOR_t)!color;
	}

	if (color == OLED_COLOR_WHITE) {
		OLED_Buffer[x + (y / 8) * OLED_WIDTH] |= 1 << (y % 8);
	} else {
		OLED_Buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
	}
}

void OLED_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, OLED_COLOR_t color) {
		int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        OLED_DrawPixel(x0, y0, color);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


char OLED_Putc(char ch, FontDef_t* Font, OLED_COLOR_t color) {
	uint32_t i, b, j;

	if (
		OLED_WIDTH <= (OLED.CurrentX + Font->FontWidth) ||
		OLED_HEIGHT <= (OLED.CurrentY + Font->FontHeight)
	) {
		return 0;
	}
	for (i = 0; i < Font->FontHeight; i++) {
		b = Font->data[(ch - 32) * Font->FontHeight + i];
		for (j = 0; j < Font->FontWidth; j++) {
			if ((b << j) & 0x8000) {
				OLED_DrawPixel(OLED.CurrentX + j, (OLED.CurrentY + i), (OLED_COLOR_t) color);
			} else {
				OLED_DrawPixel(OLED.CurrentX + j, (OLED.CurrentY + i), (OLED_COLOR_t)!color);
			}
		}
	}
	OLED.CurrentX += Font->FontWidth;
	return ch;
}

char OLED_Puts(char* str, FontDef_t* Font, OLED_COLOR_t color) {
	while (*str) {
		if (OLED_Putc(*str, Font, color) != *str) {
			return *str;
		}
		str++;
	}
	return *str;
}

void OLED_Clear (void){
	OLED_Fill (0);
    OLED_UpdateScreen();
}
void OLED_ON(void) {
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x8D);  
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x14);  
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xAF);  
}
void OLED_OFF(void) {
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x8D);  
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0x10);
	I2C_writeByte(OLED_I2C_ADDR, 0x00,0xAE);  
}
void OLED_I2C_WriteMulti(uint8_t address, uint8_t reg, char* data, uint16_t count) {
uint8_t dt[256];
uint8_t i;
for(i = 0; i < count; i++)
dt[i] = data[i];
I2C_WriteMulti(address,reg,data,count);
}


void OLED_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
	I2C_writeByte(address,reg,data);
}
