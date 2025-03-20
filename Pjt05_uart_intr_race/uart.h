// Pjt04_uart_intr_volatile
// uart.h

void uart_init(void);
void uart_putstart(char str[]);

extern char buf[64];
extern volatile int bufi, txend;
