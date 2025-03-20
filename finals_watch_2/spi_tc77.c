#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include "spi_tc77.h"
#include "task.h"
#include "timer_linked_list.h"

void spi_init() {
	sbi(DDRB, 0);
	sbi(DDRB, 1);
	sbi(DDRB, 2);
	cbi(DDRB, 3);

	sbi(SPSR, SPI2X);
	SPCR = ((1 << MSTR) | (1 << SPE) | (1 << SPIE));

}

void spi_select() {
	cbi(PORTB, 0);
}

void spi_release() {
	sbi(PORTB, 0);
}

void spi_write(uint8_t data) {
	SPDR = data;
}

void task_tc77(void *arg) {
	static uint8_t state;
	static uint16_t value;

	if (!strcmp(arg, "")) {
		state = TC77_WAIT_HI;
		spi_select();
		spi_write(0x00);
	} else {
		switch(state) {
			case TC77_WAIT_HI:
				value = atoi(arg) << 8;
				state = TC77_WAIT_LO;
				spi_write(0x00);
				break;
			case TC77_WAIT_LO:
				value |= atoi(arg);
				value = (value >> 3) * 0.0625;
				spi_release();
				printf("task_tc77() : crrent_temperatur -> %d degree.\n", value);
				break;
			default:
				spi_release();
				printf("task_tc77() : unecpecetd state task_tc77...\n"); 
		}
	}
}

ISR(SPI_STC_vect) {
	struct task task;
	uint8_t     data;
	data = SPDR;
	task.fun = task_tc77;
	sprintf(task.arg, "%d", data);
	task_insert(&task);
}
