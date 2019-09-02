#ifndef _SelectionSort_h
#define _SelectionSort_h

namespace cppalgo {

template <class TYPE>
void SelectionSort(TYPE a[], int n)
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
	}
}
};
#endif