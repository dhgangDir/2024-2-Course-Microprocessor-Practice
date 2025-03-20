// main.c
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "app_prime.h"
#include "cir_queue.h"
#include "app_led.h"
#include "led.h"

#define BS 0x08
char st[64];
int main()
{
	char cmd[128], *cp, *ap;
	int i, j, k;
	uart_init();
	led_init();
   	sei();	
	
	while(1) {
		printf("$ ");
		if(fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;

		printf("%s\n", cmd);

		if((cp = strtok(cmd, "\n\r\t ")) == NULL) continue;
		ap = strtok(NULL, "\n\r\t ");		

		if(!strcmp(cp, "prime")) app_prime(2000);
		//if (!strcmp(cp, "led"))  app_led(ap);
		else 					 printf("Unknown command...\n");
	}
	printf("logout, good bye!!! \n");
	while(1);
	
   	return 0;
}
