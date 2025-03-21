#include <stdio.h>
#include <stdlib.h>
#include "app_sum.h"

void app_sum(char *ap) {
	int t = 100, sum = 0;

	if (ap && *ap) t = atoi(ap);
	sum = ((t + 1) * (t)) / 2;
	printf("sum=%d\n", sum);
}
