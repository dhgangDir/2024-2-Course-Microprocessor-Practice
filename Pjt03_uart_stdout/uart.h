// uart.h

void uart_init(void);
void uart_putchar(char ch);
void uart_putstr(char *sp);
int uart_putchar_1(char ch, FILE *stream);
