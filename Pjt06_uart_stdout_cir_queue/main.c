// main.c
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "app_prime.h"

int main()
{
	uart_init();
   	sei();	

	app_prime(2000);

	while(1);
   	return 0;
}
