#include "lcd.h"

int main() {
	lcd_init();

	print("Hello");
	
	while(1);
	return 0;
}