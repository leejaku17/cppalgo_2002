#include "Selection.h"
#include <stdlib.h>

void main(void)
{
	int a[1000];
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
		a[i] = rand();

	int a2 = cppalgo::Select_Partition(a, sizeof(a)/sizeof(int), 15);
	int a1 = cppalgo::Select_Linear(a, sizeof(a)/sizeof(int), 15);
	
}