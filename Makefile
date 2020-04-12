a:
	avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c lcd.c
	avr-ar rcs liblcd.a lcd.o
	rm lcd.o

hex:
	avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c test_lcd.c
	avr-gcc -DF_CPU=16000000 -mmcu=atmega328p -o test_lcd.elf test_lcd.o -L. -llcd
	avr-objcopy -O ihex test_lcd.elf test_lcd.hex
	rm test_lcd.o
	rm test_lcd.elf

flash:
	avrdude -c arduino -p m328p -P /dev/ttyACM0 -U flash:w:test_lcd.hex

clear:
	rm test_lcd.hex
	rm liblcd.a