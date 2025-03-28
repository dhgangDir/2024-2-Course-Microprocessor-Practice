// uart.c

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "cir_queue.h"

#define BS 0x08
//int uart_putchar_1(char ch, FILE *stream);

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE Mystdin  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
char uart_busy;

void uart_init() {
	stdin = &Mystdin; stdout = &Mystdout;
	uart_busy = 0;
	q_init();
    UBRR0H = 0x00; UBRR0L = 0x07;
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, TXEN0);
	sbi(UCSR0B, TXCIE0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, RXCIE0);
}

int uart_putchar(char ch, FILE *stream){
    if(ch == '\n') 
	    uart_putchar('\r', stream);

	cli();
	
	if(!uart_busy) {
	    UDR0 = ch;
		uart_busy = 1;
	} else {
		while(qo_insert(ch) == 0) {
		    sei();
			_delay_us(100);
			cli();
		}
	}
	sei();
	return (1);
}
/*
void uart_putstr(char *sp){
    for(; *sp; sp++)
	    uart_putchar(*sp);
}
*/
int uart_putchar_1(char ch, FILE *stream) {
    if(ch == '\n')
	    uart_putchar_1('\r', stream);
    //_delay_ms(10);
	while(1) {
	    if((UCSR0A & (1 << UDRE0)) != 0 )
		    break;
	}
	UDR0 = ch;
	return (1);
}

int uart_getchar(FILE *stream) {
	char ch;

	do {
		cli();
		ch = qi_delete();
		sei();
	} while (ch == 0);
	if (ch == EOT) return(-1);
	else 		   return(ch);
}

void uart_echo(char ch) {
	if(ch == '\n') uart_echo('\r');
	if(!uart_busy) {
		UDR0 = ch;
		uart_busy = 1;
	}
	else
		qo_insert(ch);
}

ISR(USART0_TX_vect){
	char ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else if (ch == BS) UDR0 = BS;
	else {
		UDR0 = ch;
	}
}

ISR(USART0_RX_vect) {
	char ch;
	ch = UDR0;
	if(ch != EOT) {
		if(ch == '\r')  ch = '\n';
		uart_echo(ch);
	}
	if (ch == BS) qi_delete();
	qi_insert(ch);
}
