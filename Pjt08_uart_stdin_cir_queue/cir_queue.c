// cir_queue.h
#include "cir_queue.h"

char qi[QI_SIZE], qo[QO_SIZE];
int fi, ri, fo, ro;
void q_init(void) {
	fi = ri = fo = ro = 0;
}
int qi_insert(char ch) {
	if((ri + 1) % QI_SIZE == fi)
		return (0);
	ri = (ri + 1) % QI_SIZE;
	qi[ri] = ch;
	return(1);
}
int qi_delete(void) {
	if( ri == fi)
		return(0);
    fi = (fi+1) % QI_SIZE;
	return(qi[fi]);
}
int qo_insert(char ch) {
	if((ro + 1) % QO_SIZE == fo)
		return (0);
	ro = (ro + 1) % QO_SIZE;
	qo[ro] = ch;
	return(1);
}
int qo_delete(void) {
	if( ro == fo)
		return(0);
    fo = (fo+1) % QO_SIZE;
	return(qo[fo]);
}
