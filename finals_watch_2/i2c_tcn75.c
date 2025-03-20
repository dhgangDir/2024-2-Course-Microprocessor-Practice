#include <stdio.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include "i2c_tcn75.h"

void tcn75_i2c_init() {
	sbi(DDRD, SDA);	sbi(PORTD, SDA);
	sbi(DDRD, SCL); sbi(PORTD, SCL);
}

inline void i2c_tcn75_trans_start() {
	cbi(PORTD, SCL);
	sbi(PORTD, SDA); delay_2nop();
	sbi(PORTD, SCL); delay_2nop();
	cbi(PORTD, SDA); delay_us(1);
}

inline void i2c_tcn75_trans_stop() {
	cbi(PORTD, SCL);
	cbi(PORTD, SDA); delay_2nop();
	sbi(PORTD, SCL); delay_2nop();
	sbi(PORTD, SDA); delay_us(1);
}

inline uint8_t i2c_tcn75_write_one_byte(uint8_t data) {
	uint8_t mask, ack;
	sbi(DDRD, SDA);

	for (mask = 0x80; mask; mask = mask >> 1) {
		cbi(PORTD, SCL); delay_2nop();
		if (mask & data) sbi(PORTD, SDA);
		else 			 cbi(PORTD, SDA);
		delay_us(1);
		sbi(PORTD, SCL); delay_us(1);
	}
	cbi(DDRD, SDA);
	cbi(PORTD, SCL); delay_us(1);
	sbi(PORTD, SCL); delay_us(1);
	ack = PIND & (1 << SDA);
	
	return (ack);
}

inline uint8_t i2c_tcn75_read_one_byte(uint8_t ack) {
	uint8_t i, data = 0;
	cbi(DDRD, SDA);
	for (i = 0; i < 8; i++) {
		cbi(PORTD, SCL); delay_us(1);
		sbi(PORTD, SCL); delay_us(1);
		data = (data << 1);
		if (PIND & (1 << SDA)) data = data | 0x01;
	}	
	
	sbi(DDRD, SDA);
	cbi(PORTD, SCL); delay_2nop();

	if (ack) sbi(PORTD, SDA);
	else	 cbi(PORTD, SDA);
	delay_us(1);
	sbi(PORTD, SCL); delay_us(1);

	return(data);
}

void task_tcn75_i2c(void *arg) {
	uint16_t value;
	i2c_tcn75_trans_start();
	if (i2c_tcn75_write_one_byte(0x90) != 0) {
		i2c_tcn75_trans_stop();
		printf("task_tcn75_i2c() : SLA+W write fail...\n");
		return ;
	}

	if (i2c_tcn75_write_one_byte(0x00) != 0) {
		i2c_tcn75_trans_stop(); 
		printf("task_tcn75_i2c() : pointer write fail...\n");
		return ;
	}
	
	i2c_tcn75_trans_start();
	if (i2c_tcn75_write_one_byte(0x91) != 0) {
		i2c_tcn75_trans_stop(); 
		printf("task_tcn75_i2c() : SLA+R write fail...\n");
		return ;
	}

	value = ((i2c_tcn75_read_one_byte(0) << 8) | i2c_tcn75_read_one_byte(1)) >> 7;
	i2c_tcn75_trans_stop(); 
	value = value >> 1;
	printf("task_tcn75_i2c() : current_temperature -> %d degree. \n", value);
}
