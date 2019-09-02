#ifndef _ShellSort_h
#define _ShellSort_h

namespace cppalgo {
template <class TYPE>
void ShellSort(TYPE a[], int n)
{
	int i, j, k, h;
	TYPE v;
	for (h = n/2; h > 0; h /= 2)	
	{
		for (i = 0; i < h; i++)  // 변이 
		{
			for (j = i+h; j < n; j += h)   // j는 삽입정렬할 요소를 지정
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v) // 삽입할 곳을 찾음 
				{
					a[k] = a[k-h];  // 이동 
					k -= h;
				}
				a[k] = v;		// 삽입 
			}
		}
	}
}

template <class TYPE>
void ShellSort_3h(TYPE a[], int n)
{
	// h = 3*h + 1 수열 사용
	int i, j, k, h;
	TYPE v;
	for (h = 1; h < n; h = 3*h+1);   // n보다 작은 최대의 h를 찾는다.
	for (h /= 3; h > 0; h /= 3)
	{
		for (i = 0; i < h; i++)
		{
			for (j = i+h; j < n; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
}
};
#endif