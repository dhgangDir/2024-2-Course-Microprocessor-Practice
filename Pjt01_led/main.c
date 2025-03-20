// main.c

#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main()
{
   	led_init();
	//d_on(1);
	//PORTL = 0x01;
	_delay_ms(100);		
	PORTL = 0x01;
   	while(1) {
	}
   	
   	return 0;
}
