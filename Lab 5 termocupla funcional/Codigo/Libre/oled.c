#include "oled.h"
#define SSD1306_NORMALDISPLAY       0xA6
#define SSD1306_INVERTDISPLAY       0xA7
static char SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;


void i2c_writeByte(char saddr,char maddr,char data){

while(I2C1->SR2&I2C_SR2_BUSY){;}         
I2C1->CR1|=I2C_CR1_START;                
while(!(I2C1->SR1&I2C_SR1_SB)){;}        
I2C1->DR = saddr<< 1;                
while(!(I2C1->SR1&I2C_SR1_ADDR)){;}  
int Tempo = I2C1->SR2; 	
while(!(I2C1->SR1&I2C_SR1_TXE)){;}      
I2C1->DR = maddr;                        
while(!(I2C1->SR1&I2C_SR1_TXE)){;}     
I2C1->DR = data; 	
while (!(I2C1->SR1 & I2C_SR1_BTF));     
I2C1->CR1 |=I2C_CR1_STOP;								
	
}


void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length){
volatile int Tempo;
while (I2C1->SR2 & I2C_SR2_BUSY);           
I2C1->CR1 |= I2C_CR1_START;                   
while (!(I2C1->SR1 & I2C_SR1_SB)){;}				
														
I2C1->DR = saddr<< 1;                 	 			
while (!(I2C1->SR1 & I2C_SR1_ADDR)){;}       
Tempo = I2C1->SR2; 						                 
while (!(I2C1->SR1 & I2C_SR1_TXE));          
I2C1->DR = maddr;                      			
while (!(I2C1->SR1 & I2C_SR1_TXE));         
for (uint8_t i=0;i<length;i++) { 
 I2C1->DR=buffer[i]; 												
	while (!(I2C1->SR1 & I2C_SR1_BTF));
 }	
                            
I2C1->CR1 |= I2C_CR1_STOP;										
}
static SSD1306_t SSD1306;
void oled_Init(void) {
	i2c_writeByte(I2C_ADDR, 0x00,0xAE); 
	i2c_writeByte(I2C_ADDR, 0x00,0x20); 
	i2c_writeByte(I2C_ADDR, 0x00,0x10); 
	i2c_writeByte(I2C_ADDR, 0x00,0xB0); 
	i2c_writeByte(I2C_ADDR, 0x00,0xC8);
	i2c_writeByte(I2C_ADDR, 0x00,0x00); 
	i2c_writeByte(I2C_ADDR, 0x00,0x10); 
	i2c_writeByte(I2C_ADDR, 0x00,0x40);
	i2c_writeByte(I2C_ADDR, 0x00,0x81); 
	i2c_writeByte(I2C_ADDR, 0x00,0xFF);
	i2c_writeByte(I2C_ADDR, 0x00,0xA1); 
	i2c_writeByte(I2C_ADDR, 0x00,0xA6);
	i2c_writeByte(I2C_ADDR, 0x00,0xA8);
	i2c_writeByte(I2C_ADDR, 0x00,0x3F);
	i2c_writeByte(I2C_ADDR, 0x00,0xA4); 
	i2c_writeByte(I2C_ADDR, 0x00,0xD3); 
	i2c_writeByte(I2C_ADDR, 0x00,0x00); 
	i2c_writeByte(I2C_ADDR, 0x00,0xD5); 
	i2c_writeByte(I2C_ADDR, 0x00,0xF0); 
	i2c_writeByte(I2C_ADDR, 0x00,0xD9);
	i2c_writeByte(I2C_ADDR, 0x00,0x22); 
	i2c_writeByte(I2C_ADDR, 0x00,0xDA); 
	i2c_writeByte(I2C_ADDR, 0x00,0x12);
	i2c_writeByte(I2C_ADDR, 0x00,0xDB); 
	i2c_writeByte(I2C_ADDR, 0x00,0x20);
	i2c_writeByte(I2C_ADDR, 0x00,0x8D);
	i2c_writeByte(I2C_ADDR, 0x00,0x14); 
	i2c_writeByte(I2C_ADDR, 0x00,0xAF);
	i2c_writeByte(I2C_ADDR, 0x00,0x2E); 
	SSD1306_Fill(SSD1306_COLOR_BLACK);
	SSD1306_UpdateScreen();
}

void SSD1306_UpdateScreen(void) {
	uint8_t m;
	
	for (m = 0; m < 8; m++) {
		i2c_writeByte(I2C_ADDR, 0x00,0xB0 + m);
		i2c_writeByte(I2C_ADDR, 0x00,0x00);
		i2c_writeByte(I2C_ADDR, 0x00,0x10);
		ssd1306_I2C_WriteMulti(I2C_ADDR, 0x40, &SSD1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH);
	}
}

void SSD1306_Fill(SSD1306_COLOR_t color) {
	memset(SSD1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}

void SSD1306_GotoXY(uint16_t x, uint16_t y) {
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}

void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color) {
	if (
		x >= SSD1306_WIDTH ||
		y >= SSD1306_HEIGHT
	) {
		return;
	}

	if (SSD1306.Inverted) {
		color = (SSD1306_COLOR_t)!color;
	}

	if (color == SSD1306_COLOR_WHITE) {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	} else {
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
}

char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color) {
	uint32_t i, b, j;

	if (
		SSD1306_WIDTH <= (SSD1306.CurrentX + Font->FontWidth) ||
		SSD1306_HEIGHT <= (SSD1306.CurrentY + Font->FontHeight)
	) {
		return 0;
	}
	for (i = 0; i < Font->FontHeight; i++) {
		b = Font->data[(ch - 32) * Font->FontHeight + i];
		for (j = 0; j < Font->FontWidth; j++) {
			if ((b << j) & 0x8000) {
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t) color);
			} else {
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t)!color);
			}
		}
	}
	SSD1306.CurrentX += Font->FontWidth;
	return ch;
}

char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color) {
	while (*str) {
		if (SSD1306_Putc(*str, Font, color) != *str) {
			return *str;
		}
		str++;
	}
	return *str;
}

void SSD1306_Clear (void){
	SSD1306_Fill (0);
    SSD1306_UpdateScreen();
}
void SSD1306_ON(void) {
	i2c_writeByte(I2C_ADDR, 0x00,0x8D);  
	i2c_writeByte(I2C_ADDR, 0x00,0x14);  
	i2c_writeByte(I2C_ADDR, 0x00,0xAF);  
}
void SSD1306_OFF(void) {
	i2c_writeByte(I2C_ADDR, 0x00,0x8D);  
	i2c_writeByte(I2C_ADDR, 0x00,0x10);
	i2c_writeByte(I2C_ADDR, 0x00,0xAE);  
}
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, char* data, uint16_t count) {
uint8_t dt[256];
uint8_t i;
for(i = 0; i < count; i++)
dt[i] = data[i];
i2c_WriteMulti(address,reg,data,count);
}


void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
	i2c_writeByte(address,reg,data);
}
