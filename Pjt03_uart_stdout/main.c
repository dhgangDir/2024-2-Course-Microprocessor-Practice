// main.c
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include "uart.h"

int is_prime(int n) {
    int i;
	for(i = 2; i <= n/2; i++){
		if((n % 2) == 0) return(0);
	}
	return(1);
}

int main()
{
	int i = 0;
	uart_init();

   	for(i = 3; i <= 1000; i++) {
		if (is_prime(i)) 
			printf("%d is a prime number !!!\n", i);
		else
		    printf("%d is not a prime number !!!\n", i);
		
	}
	printf("The end\n");

	while(1);
   	return 0;
}
