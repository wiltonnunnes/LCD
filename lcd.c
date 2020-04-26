#include "lcd.h"

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

void write_digit(unsigned char value) {
	send_data(value + 0x30);
}

void write_number(int x) {
	if(x < 0) {
		send_data('-');
		x = abs(x);
	}

	if(x > 9999) {
		write_digit(x / 10000);

		int r = x % 10000;
		if(r < 1000)
			write_digit(0);
		if(r < 100)
			write_digit(0);
		write_number(r);
	}

	if(x > 999 && x <= 9999) {
		write_digit(x / 1000);

		int r = x % 1000;
		if(r < 100)
			write_digit(0);

		write_number(r);
	}

	if(x > 99 && x <= 999) {
		write_digit(x / 100);
		write_number(x % 100);
	}
	
	if(x <= 99){
		write_digit(x / 10);
		write_digit(x % 10);
	}
}

