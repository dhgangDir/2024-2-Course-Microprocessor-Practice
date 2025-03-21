#ifndef __TIMER_LINKED_LIST_H__
#define __TIMER_LINKED_LIST_H__

struct task {
	void (*fun) (char *);
	char arg[8];
};

struct timer {
	int time;
	struct task task;
	struct timer * link;
};

extern struct timer *Thead;

void timer_init();

void timer_expire(void);

struct timer *get_timer();

void insert_timer(struct task *tskp, int ms);
void tour_timer(),
	 free_timer();

void app_timer(char *ap);

#endif
