// uart.c

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "task.h"

//int uart_putchar_1(char ch, FILE *stream);

FILE Mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE Mystdin  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
char uart_busy;

static int echo_mode = 1;

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

int uart_peek() {
	return (qi_peek());
}


ISR(USART0_TX_vect){
	char ch;

	if((ch = qo_delete()) == 0)
		uart_busy = 0;
	else 
		UDR0 = ch;
}

ISR(USART0_RX_vect) {
	struct task task;
	char ch;
	ch = UDR0;
	if (ch == ESC) {
		echo_mode = (echo_mode + 1) & 0x01;
		return ;
	}

	if(ch != EOT) {
		if (ch == '\r')  ch = '\n';
		if (echo_mode)	uart_echo(ch);
	}
	qi_insert(ch);
	if (ch == EOT || ch == '\n') {
		task.fun = task_cmd;
		strcpy(task.arg, "");
		task_insert(&task);
	}
}
