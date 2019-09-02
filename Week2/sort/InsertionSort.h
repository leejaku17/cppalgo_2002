#ifndef _InsertionSort_h
#define _InsertionSort_h

namespace cppalgo {
template <class TYPE>
void InsertionSort(TYPE a[], int n)
{
	int i, j;
	TYPE t;
	for (i = 1; i < n; i++)
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}
}
};

#endif