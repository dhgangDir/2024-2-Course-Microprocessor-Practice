// Pjt04_uart_intr_volatile
// uart.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"

char buf[64];
int volatile bufi, txend = 1;

void uart_init(void) {
	UBRR0H = 0x00; UBRR0L = 0x07; 
	UCSR0A |= (1 << U2X0);
	UCSR0B |= (1 << TXEN0);
	UCSR0B |= (1 << TXCIE0);
}
void uart_putstart(char str[]) {
	char ch;
	if (buf[0] && (64 - strlen(buf) > strlen(str))) {
		strcat(buf, str);
		return ;
	}
	while(!txend); txend = 0;
	strcpy(buf, str); bufi = 0;
	ch = buf[bufi++];
	UDR0 = ch;	
}

ISR(USART0_TX_vect) {
	char ch = buf[bufi];
	if(!ch) {
		txend = 1; 
		buf[0] = 0;
		return ;
	}
	if(ch == '\n') buf[bufi] = '\r';
	else		   bufi++;

	UDR0 = ch;
}
