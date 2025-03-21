#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "timer_linked_list.h"
#include "app_prime.h"
#include "task.h"
#include "uart.h"
#include "app_sum.h"

struct task Task_q[MAX_TASK];
volatile int Task_f, Task_r;

struct task_tab Task_tab[] = {
	{"prime", task_prime},
	{"sum", app_sum},
};

int Task_cnt = sizeof(Task_tab) / sizeof(struct task_tab);

void task_init() {
	Task_f = Task_r = 0;
}

int task_insert(struct task *tskp) {
	if ((Task_r + 1) % MAX_TASK == Task_f)
		return (0);
	Task_r = (Task_r + 1) % MAX_TASK;
	Task_q[Task_r] = *tskp;
	return (1);
}

int task_delete(struct task *tskp) {
	if (Task_r == Task_f)
		return(0);
	Task_f = (Task_f + 1) % MAX_TASK;
	*tskp = Task_q[Task_f];
	return (1);
}

struct task_tab *what_task(char *name) {
	int i;
	for (i = 0; i < Task_cnt; i++)
		if(!strcmp(name, Task_tab[i].task_name))
			return (&Task_tab[i]);
	return (NULL);
}

void task_cmd(char *arg) {
	char buf[64], *cp0, *cp1, *cp2, *cp3;
	struct task task;
	struct task_tab *ptt;
	int ms;

	if (!uart_peek()) return ;

	if (gets(buf) == NULL) {
		printf("logout, good bye !!!\n");
		while(1);
	}

	cp0 = strtok(buf, " \t\n\r");
	cp1 = strtok(NULL, " \t\n\r");
	cp2 = strtok(NULL, " \t\n\r");
	cp3 = strtok(NULL, " \t\n\r");

	if (cp0 == NULL) {
		printf("$ "); return ;
	}

	if (!strcmp(cp0, "timer")) {
		if (!cp1 || !cp2) {
			printf("!!!-222\n");
			printf("$ ");
			return ;
		}
		ms = atoi(cp1) / 256;

		if (!(ptt = what_task(cp2))) {
			printf("Unknown command...\n");
			return ;
		}

		task.fun = ptt->task_fun;
		if (cp3) strcpy(task.arg, cp3);
		else 	 strcpy(task.arg, "");
		cli();
		insert_timer(&task,ms);
		sei();
		/*
		if (!strcmp(cp2, "prime")) {
			task.fun = task_prime;
			if (cp3) strcpy(task.arg, cp3);
			else 	 strcpy(task.arg, "");
			cli();
			insert_timer(&task,ms);
			sei();
		} else if (!strcmp(cp2, "sum")) {
			task.fun = app_sum;
			if (cp3) strcpy(task.arg, cp3);
			else 	 strcpy(task.arg, "");
			cli();
			insert_timer(&task,ms);
			sei();
		*/
		} else {
			if (!(ptt = what_task(cp0))) {
				printf("Unknown command...\n");
				return ;
			}

			if (cp2)
				(*ptt->task_fun)(cp1);
			else
				(*ptt->task_fun)("");
		}
	printf("$ ");
}
