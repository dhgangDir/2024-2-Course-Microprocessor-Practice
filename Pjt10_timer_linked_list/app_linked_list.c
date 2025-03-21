// app_linked_list.h
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "uart.h"

void app_list(char *ap) {
	char buf[8], how = 'a';
	struct node *np;

	if (ap) how = *ap;
	while(1) {
		printf("> ");
		if (fgets(buf, 8, stdin) == NULL)
			break;
		np = get_node();
		np->data = atoi(buf);
		switch(how) {
			case 'h' : insert_node_head(np); break;
			case 't' : insert_node_tail(np); break;
			default  : insert_node_ascn(np);
		}
	}
	tour_list();
	free_list();
}
