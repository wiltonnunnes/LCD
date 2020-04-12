#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define LCD_PORT PORTD
#define LCD_DDR DDRD
#define RS 2
#define EN 3

void lcd_init();
void send_cmd(unsigned char cmd);
void lcd_clear();
void send_data(unsigned char data);
void set_cursor(unsigned char, unsigned char);
void print(char *str);
void write_digit(unsigned char);
void write_int(int);