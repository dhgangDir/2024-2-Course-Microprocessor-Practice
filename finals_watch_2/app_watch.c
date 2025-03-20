#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "app_watch.h"
#include "task.h"
#include "timer_linked_list.h"
#include "app_prime.h"

void task_watch(char *ap) {
	int cnt = 0;
	struct task watch;
	char cnt_ch[2];

	if (ap && *ap) cnt = atoi(ap);
	printf("%d\n", cnt++);
	
	if (cnt < 10) {
		cnt_ch[0] = '0' + cnt;
		cnt_ch[1] = '\0';
		watch.fun = task_watch;
		strcpy(watch.arg, cnt_ch);
		cli();
		insert_timer(&watch, (2000/256));
		sei();
	}
}
