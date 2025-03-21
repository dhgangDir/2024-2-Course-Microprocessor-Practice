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
#include "task.h"
#include "adc_tc1047.h"

int main()
{
	int tag;	
	struct task task;

	sei();
	uart_init();
	task_init();
	timer_init();
	adc_init();
	printf("$ ");

	while(1) {
		cli();
		tag = task_delete(&task);
		sei();
		if (tag)
			(*(task.fun))(task.arg);
	}

   	return 0;
}
