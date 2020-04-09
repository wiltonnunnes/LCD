/*
 * LCD.cpp
 *
 * Created: 09/02/2020 17:54:14
 * Author : WillNunnes
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define LCD_PORT PORTD
#define LCD_DDR DDRD
#define RS 2
#define EN 3

void send_cmd(unsigned char cmd) {
	LCD_PORT = (LCD_PORT & 0x0F) | (cmd & 0xF0);
	LCD_PORT &= ~(1 << RS);
	LCD_PORT |= (1 << EN);
	_delay_ms(1);
	LCD_PORT &= ~(1 << EN);	
	_delay_ms(1);
	
	LCD_PORT = (LCD_PORT & 0x0F) | (cmd << 4);
	LCD_PORT |= (1 << EN);
	_delay_ms(1);
	LCD_PORT &= ~(1 << EN);	
	_delay_ms(1);
}

void send_data(unsigned char data) {
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_PORT |= (1 << RS);
	LCD_PORT |= (1 << EN);
	_delay_ms(2);
	LCD_PORT &= ~(1 << EN);	
	_delay_ms(2);
	
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4);
	LCD_PORT |= (1 << EN);
	_delay_us(2);
	LCD_PORT &= ~(1 << EN);
	_delay_us(2);
}

void lcd_init() {
	LCD_DDR |= 0b11111100;
	LCD_PORT |= (LCD_PORT & 0b0000) | 0x20;
	LCD_PORT &= ~(1 << RS);
	LCD_PORT |= (1 << EN);
	_delay_ms(1);
	LCD_PORT &= ~(1 << EN);
	
	send_cmd(0x28);
	_delay_ms(1);
	send_cmd(0x0E);
	_delay_ms(1);
	send_cmd(0x80);
}

void lcd_clear() {
	send_cmd(0x01);
	_delay_ms(5);
}

void set_cursor(unsigned char row, unsigned char col) {
	send_cmd((0x80 | row << 6) + col);
	_delay_us(50);
}

void print(char *str) {
	int i;
	for(i = 0; str[i] != '\0'; i++) {
		send_data(str[i]);
	}
}

int main(void)
{
	char str[] = "Wilton Nunes";
	lcd_init();
	
	send_data(0x39);
	
    while (1);
	return 0;
}