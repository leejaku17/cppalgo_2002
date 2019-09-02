#ifndef _BubbleSort_h
#define _BubbleSort_h

namespace cppalgo {
template <class TYPE>
void BubbleSort(TYPE a[], int n)
{
	int i, j;
	TYPE t;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 1; j < n - i; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}
}

template <class TYPE> 
void BubbleSort2(TYPE a[], int n)
{
	int i, j;
	TYPE t;
	bool sorted;
	for (i = 0; i < n - 1; i++)
	{
		sorted = true;
		for (j = 1; j < n - i; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
				sorted = false;
			}
		}
		if (sorted) break;
	}
}
};

#endif