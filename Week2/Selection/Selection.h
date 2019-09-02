#ifndef _Selection_h
#define _Selection_h

namespace cppalgo 
{
template <class TYPE>
TYPE Select_Linear(TYPE a[], int n, int k)
{
	TYPE min;		// 최소값 저장
	int minindex;   // 최소값 인덱스 저장 
	int i, j;

	for (i = 0; i < n - 1; i++)
	{
		minindex = i;	// 최소값의 초기설정 
		min = a[i];
		for (j = i + 1; j < n; j++)  // i이후의 최소값을 찾음 
		{
			if (min > a[j])  // 더 작은 값이면 바꿈
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];  // i항과 min항을 교환 
		a[i] = min;

		if (i == k)
			return min;
	}
	throw "Invalid k";
}

template <class TYPE>
TYPE Select_Partition(TYPE a[], int n, int k)
{
	TYPE v, t;
	int i, j, l, r;
	l = 1;
	r = n;
	while (r > l)
	{
		v = a[r];
		i = l-1;
		j = r;
		while (true)
		{
			while (a[++i] < v);
			while (a[--j] > v);
			if (i >= j) break;
			t = a[i]; a[i] = a[j]; a[j] = t;
		}
		t = a[i]; a[i] = a[r]; a[r] = t;

		if (i >= k) r = i - 1;
		if (i <= k) l = i + 1;
	}

	return a[k];
}
};

#endif