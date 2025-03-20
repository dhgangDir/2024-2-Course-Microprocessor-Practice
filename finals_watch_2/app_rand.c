#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "task.h"
#include "timer_linked_list.h"
#include "app_rand.h"

void task_rand(char *ap) {
	struct task task;
	// struct task rnd;

	if (Thead) {
		printf("%d\n", rand());
		task_rand("");
	} else {
		task.fun = task_cmd;
		strcpy(task.arg, "");
		cli();
		insert_timer(&task, (10000/256));
		sei();
		task_rand("");
	}
}
