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
#include "app_linked_list.h"
#include "timer_linked_list.h"

int main()
{
	char cmd[128], *cp, *ap;
	int n;
	uart_init();
   	sei();	
	
	while(1) {
		printf("$ ");
		if(fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		if((cp = strtok(cmd, "\n\r\t ")) == NULL) continue;
		ap = strtok(NULL, "\n\r\t ");
		if      (!strcmp(cp, "prime")) app_prime(ap);
		else if (!strcmp(cp, "list"))  app_list(ap);
		else if (!strcmp(cp, "timer")) app_timer(ap);
		else 					 	   printf("Unknown command...\n");
	}
	printf("logout, good bye!!! \n");
	while(1);
	
   	return 0;
}
