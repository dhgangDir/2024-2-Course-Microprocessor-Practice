#ifndef __SPI_TC77_H__
#define __SPI_TC77_H__

#define TC77_WAIT_HI 1
#define TC77_WAIT_LO 2

void spi_init();
void spi_select();
void spi_release();
void spi_write(uint8_t data);
void task_tc77(void *arg);

#endif
