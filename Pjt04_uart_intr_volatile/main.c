// Pjt04_uart_intr_volatile
// main.c

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "uart.h"
#include "led.h"

/*
int main() {
	int i;
	led_init();
	uart_init();
	sei();
	//txend = 0;
	for (i = 0; i < 100; i++) {
		uart_putstart("I love you. You love me.\n");
			//while(!txend); txend = 0;
		//uart_putstart("You love me.\n");
			//while(!txend); txend = 0;
		//uart_putstart("He loves her.\n");
			//while(!txend); txend = 0;
	}
	uart_putstart("End !!!\n");
	while(1);
	return(0);
}
*/

int main() {
	int i;
	int r, l;
	char fbuf[64];
	sei();

	led_init();
	uart_init();

	for (i = 0; i < 10000; i++) {
		r = sqrt((double)i);
		l = log((double)i);
		sprintf(fbuf, "%d, %d\n", r, l);
		uart_putstart(fbuf);
	}
	uart_putstart("End !!!\n");
	while(1);
	return(0);
}

