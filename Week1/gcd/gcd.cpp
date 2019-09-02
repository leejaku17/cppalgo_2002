#include <stdio.h>

int get_gcd(int u, int v) 
{
	int t;
	while (u > 0) {
		if (u < v) {
			t = u; u = v; v = t;
		}
		u = u - v;
	}
	return v;
}

int gcd_modulus(int u, int v)
{
	int t;
	while (v > 0) {
		t = u % v;
		u = v;
		v = t;
	}
	return u;
}

int gcd_recursion(int u, int v)
{
	if (v == 0) {
		return u;
	} else {
		return gcd_recursion(v, u % v);	
	}
}	

void main(void)
{
	int u, v;
	int gcd;

	u = 280;
	v = 30;

	printf("get_gcd result : ");
	gcd = get_gcd(u, v);
	printf("%d\n", gcd);

	printf("gcd_modulus result : ");
	gcd = gcd_modulus(u, v);
	printf("%d\n", gcd);

	printf("gcd_recursion result : ");
	gcd = gcd_recursion(u, v);
	printf("%d\n", gcd);

}