// Pjt04_uart_intr_volatile
// main.c

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "uart.h"
#include "led.h"

int main() {
	int i;
	led_init();
	uart_init();
	sei();
	//txend = 0;
	for (i = 0; i < 10; i++) {
		uart_putstart("I love you.\n");
			//while(!txend); txend = 0;
		uart_putstart("You love me.\n");
			//while(!txend); txend = 0;
		uart_putstart("He loves her.\n");
			//while(!txend); txend = 0;
	}
	uart_putstart("End !!!\n");
	while(1);
	return(0);
}

