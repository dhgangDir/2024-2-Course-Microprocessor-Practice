// uart.h

#include "cir_queue.h"

#define EOT	0x04
#define ESC 0x1B

extern char uart_busy;

void uart_init(void);
int uart_putchar(char ch, FILE *stream);
void uart_putstr(char *sp);
int uart_putchar_1(char ch, FILE *stream);
void uart_echo(char);
int uart_getchar(FILE *);
int uart_peek();
