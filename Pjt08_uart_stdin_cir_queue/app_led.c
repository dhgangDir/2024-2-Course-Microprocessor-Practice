#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "led.h"
#include "app_led.h"

void app_led(char *ap) {
	char  *cp, *tp;
	int i, s;
	
	
	if (!ap) {
		s = get_led();
		printf("%d\n", s);
		return;
	}
	(cp = strtok(ap, "\n\r\t "));
	tp = strtok(NULL, "\n\r\t ");
	//printf("%s\n", cp);
	if (!strcmp(tp, "on")) {
		if (!strcmp(cp, "all")) {
			led_on_all();
		} else {
			i = atoi(cp);
			led_on(i);
		}
	} else {
		if (!strcmp(tp, "all")) {
			led_off_all();
		} else {
			i = atoi(tp);
			led_off(i);
		}
	}
}
