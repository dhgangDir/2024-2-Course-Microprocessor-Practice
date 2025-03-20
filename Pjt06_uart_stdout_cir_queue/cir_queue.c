// cir_queue.h
#include "cir_queue.h"

char q[Q_SIZE];
int f, r;
void q_init(void) {
	f = r = 0;
}
int q_insert(char ch) {
	if((r + 1) % Q_SIZE == f)
		return (0);
	r = (r + 1) % Q_SIZE;
	q[r] = ch;
	return(1);
}
int q_delete(void) {
	if( r == f)
		return(0);
    f = (f+1) % Q_SIZE;
	return(q[f]);
}
