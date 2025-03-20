// main.c

#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include "uart.h"

int main()
{
	char c = 0;
	int i = 0;
	uart_init();

   	for(i = 0; i < 20; i++) {
		for( c = 'A'; c <= 'Z'; c++){
		    uart_putchar(c);
		}
        uart_putchar('\n');
	}
	uart_putstr("The end");
   	
   	return 0;
}
