#include <stdio.h>
#include <math.h>			// sqrt 함수 사용을 위해 필요 

int is_prime(int n)
{
	int i;
	for (i = 2; i < n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int is_prime2(int n)
{
	int i, sqrn;
	sqrn = (int)sqrt(n);
	for (i = 2; i <= sqrn; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

void main(void) 
{
	int n;

	n = 1483;

	// 2 ~ 1482 까지 검사 
	printf("(is_prime) %d is %s prime number\n", n, is_prime(n) ? "" : "not");
	// sqrt(1483) = 38.5  즉 2 ~ 38까지만 검사 
	printf("(is_prime2) %d is %s prime number\n", n, is_prime2(n) ? "" : "not");
	
	n = 529;
	printf("(is_prime) %d is %s prime number\n", n, is_prime(n) ? "" : "not");
	printf("(is_prime2) %d is %s prime number\n", n, is_prime2(n) ? "" : "not");
}	
