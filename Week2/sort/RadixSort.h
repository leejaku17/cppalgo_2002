#ifndef _RadixSort_h
#define _RadixSort_h

#include "../Stack/ArrayStack.h"

namespace cppalgo 
{

inline unsigned long bits(unsigned long x, unsigned long k, unsigned long j)
{
	return (x >> k) & ~(~0 << j);
}

void RadixExchangeSort(unsigned long a[], int n, int b = 31)
{
	unsigned long t;
	int i, j;
	
	if (n > 1 && b >= 0)  // 종료조건 
	{
		i = 0;		// i는 왼쪽
		j = n - 1;    // j는 오른쪽 
		while (true)
		{
			while (bits(a[i], b, 1) == 0 && i < j) i++;
			while (bits(a[j], b, 1) != 0 && i < j) j--;
			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		if (bits(a[n-1], b, 1) == 0) j++;   // 모두 0인경우 대비 
		RadixExchangeSort(a, j, b-1);
		RadixExchangeSort(a+i, n-j, b-1);
	}
}

void RadixExchangeSort_nr(unsigned long a[], int n)
{
	unsigned long t;
	int i, j;
	int l, r;
	int b;

	ArrayStack<int> stack(32*3+3);

	b = 31;
	l = 0;
	r = n-1;
	stack.Push(b);
	stack.Push(r);
	stack.Push(l);
	while (!stack.IsEmpty())
	{
		l = stack.Pop();
		r = stack.Pop();
		b = stack.Pop();
		if (r > l && b >= 0)
		{
			i = l;
			j = r;
			while (true)
			{
				while (bits(a[i], b, 1) == 0 && i < j) i++;
				while (bits(a[j], b, 1) != 0 && i < j) j--;
				if (i >= j) break;
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			if (bits(a[r], b, 1) == 0) j++;
			stack.Push(b-1);
			stack.Push(r);
			stack.Push(j);
			stack.Push(b-1);
			stack.Push(j-1);
			stack.Push(l);
		}
	}
}

void StraightRadixSort(unsigned long a[], int n)
{
	int i, j;
	unsigned long *b, *count;
	unsigned long w = 32;
	unsigned long m = 8;
	unsigned long mv = (1<<m);

	b = new unsigned long [n];
	count = new unsigned long [mv];
	for (i = 0; i < w/m; i++)
	{
		for (j = 0; j < mv; j++)
			count[j] = 0;
		for (j = 0; j < n; j++)
			count[bits(a[j], i*m, m)]++;
		for (j = 1; j < mv; j++)
			count[j] = count[j] + count[j-1];
		for (j = n-1; j >= 0; j--)
			b[--count[bits(a[j], i*m, m)]] = a[j];
		for (j = 0; j < n; j++)
			a[j] = b[j];
	}
	delete [] b;
	delete [] count;
}

};

#endif