#include "timer_linked_list.h"

#define MAX_TASK 16

struct task_tab {
	char task_name[32];
	void (*task_fun) (char *arg);
};

extern struct task Task_q[MAX_TASK];
extern int Task_cnt;
void task_init();
int task_insert(struct task *tskp);
int task_delete(struct task *tskp);
void task_cmd(char *arg);
struct task_tab *what_task(char *name);
