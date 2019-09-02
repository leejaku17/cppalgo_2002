#include <stdio.h>

int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return n * factorial(n-1);
}

int factorial_nr(int n)
{
	int f = 1;
	while (n > 0)
		f = f * n--;
	return f;
}

int fibonacci(int n)
{
	if (n == 1 || n == 2)
		return 1;
	else
		return fibonacci(n-1) + fibonacci(n-2);
}

int fibonacci_nr(int n)
{
	int r = 0;
	int a = 1;
	int b = 1;

	if (n == 1 || n == 2)
		return 1;

	while (n-- > 2)
	{
		r = a + b;
		a = b;
		b = r;
	}
	return r;
}

int fibonacci_dynamic(int n, int *solved)
{
	if (solved[n] > 0) {
		return solved[n];
	} else if (n == 1 || n == 2) {
		solved[n] = 1;
		return 1;
	} else {
		solved[n] = fibonacci_dynamic(n-2, solved) + fibonacci_dynamic(n-1, solved);
		return solved[n];		
	}
}

void main(void)
{
	printf("factorial(10) = %d\n", factorial(10));
	printf("factorial_nr(10) = %d\n", factorial_nr(10));

	printf("fibonacci(10) = %d\n", fibonacci(10));
	printf("fibonacci_nr(10) = %d\n", fibonacci_nr(10));

	for (int i = 1; i <= 20; i++)
		printf("%d ", fibonacci(i));
	printf("\n"); 

	int solved[21];
	for (i = 0; i < sizeof(solved) / sizeof(int); i++) solved[i] = -1;
	printf("fibonacci_dynamic(20) = %d\n", fibonacci_dynamic(20, solved));

}