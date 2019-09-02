#include "power.h"
#include <stdio.h>

using namespace cppalgo;

void main(void)
{
	double x = 2.0;
	int n = 11;

	printf("Calculate 2 ^ 11\n");
	printf("power_simple = %lg\n", power_simple(x, n));
	printf("power_recur = %lg\n", power_recur(x, n));
	printf("power_dnq = %lg\n", power_dnq(x, n));
	printf("power_dynamic = %lg\n", power_dynamic(x, n));
}