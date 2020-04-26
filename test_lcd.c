#include "lcd.h"

int main() {
	lcd_init();

	write_number(10200);
	
	while(1);
	return 0;
}