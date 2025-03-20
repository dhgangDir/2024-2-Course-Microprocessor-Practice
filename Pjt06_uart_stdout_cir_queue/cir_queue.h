// cir_queue.h

#define Q_SIZE 64

extern char q[Q_SIZE];
extern int f, r;

void q_init(void);
int q_insert(char);
int q_delete(void);
