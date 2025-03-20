// uart.h

extern char uart_busy;

void uart_init(void);
int uart_putchar(char ch, FILE *stream);
void uart_putstr(char *sp);
int uart_putchar_1(char ch, FILE *stream);
