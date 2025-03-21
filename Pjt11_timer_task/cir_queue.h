// cir_queue.h

#define QI_SIZE 64
#define QO_SIZE 64

extern char qi[QI_SIZE], qo[QO_SIZE];
extern int fi, ri, fo, ro;

void q_init(void);
int qi_insert(char);
int qi_delete(void);
int qo_insert(char);
int qo_delete(void);
int qi_peek();
