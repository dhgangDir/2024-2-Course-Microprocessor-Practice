// app_linked_list.h
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "uart.h"

void app_list(char *ap) {
	char buf[8], how = 'a', ch;
	int i;
	struct node *np;

	if (ap) how = *ap;
	while(1) {
		printf("> ");
		if (fgets(buf, 8, stdin) == NULL)
			break;
		np = get_node();
		for (i = 0; i < 8; i++) {
			if (buf[i] >= 'a' && buf[i] <= 'z') {
				ch = buf[i];
				break;
			}  else if ( buf[i] >= 'A' && buf[i] <= 'Z' ) {
				ch = buf[i];
				break;
			}
		}
		np->data = ch;
		switch(how) {
			case 'h' : insert_node_head(np); break;
			case 't' : insert_node_tail(np); break;
			case 'd' : insert_node_decn(np); break;
			default  : insert_node_ascn(np);
		}
	}
	tour_list();
	free_list();
}
