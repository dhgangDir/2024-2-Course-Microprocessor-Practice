#ifndef __I2C_TCN75_H__
#define __I2C_TCN75_H__
#include <util/delay.h>

#define delay_2nop() asm volatile("nop" ::); asm volatile("nop" ::);
#define delay_us _delay_us
#define SCL 0
#define SDA 1

void tcn75_i2c_init();
inline void i2c_tcn75_trans_start();
inline void i2c_tcn75_trans_stop();
inline uint8_t i2c_tcn75_write_one_byte(uint8_t data);
inline uint8_t i2c_tcn75_read_one_byte(uint8_t data);
void task_tcn75_i2c(void *arg);

#endif

