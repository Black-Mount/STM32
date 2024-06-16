void lcd_send_cmd (char cmd);
void IniciarLCdConI2C(void);
void lcd_put_cur(int row, int col);
void lcd_send_data (char data);
void lcd_send_string (char *str);
void EnviarString(char Cadena[], int x, int y);