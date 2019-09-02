#ifndef _QuickSort_h
#define _QuickSort_h

#include <assert.h>
#include "../Stack/ListStack.h"
#include "../Stack/ArrayStack.h"
#include "InsertionSort.h"

namespace cppalgo {
template <class TYPE>
void QuickSort(TYPE a[], int n)
{
	TYPE v, t;
	int i, j;

	if (n > 1)	// 재귀호출의 종료조건 
	{
		v = a[n-1];  // v는 pivot value
		i = -1;		// i는 왼쪽부터 검색할 위치 
		j = n-1;    // j는 오른쪽부터 검색할 위치 
		while (true)
		{
			while (a[++i] < v);  // 축값보다 큰 값이 있나 검사
			while (a[--j] > v);
			if (i >= j) break;
			t = a[i];		// 두 값을 교환 
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];   // 축값과 축값의 위치에 있는 값을 바꿈 
		a[i] = a[n-1];
		a[n-1] = t;
		QuickSort(a, i);  // 왼쪽 구간 
		QuickSort(a+i+1, n-i-1);  // 오른쪽 구간 
	}
}

template <class TYPE>
void QuickSort_nr(TYPE a[], int n)
{
	TYPE v, t;
	int i, j;
	int l, r;  // 스택에 저장할 구간의 정보 
	ListStack<int> stack;
	l = 0;
	r = n-1;
	stack.Push(r);
	stack.Push(l);
	while (!stack.IsEmpty())
	{
		l = stack.Pop();
		r = stack.Pop();
		if (r-l+1 > 1)   // 종료조건 r-l+1은 구간의 길이 
		{
			v = a[r];	// pivot value
			i = l - 1;
			j = r;
			while (true)
			{
				while (a[++i] < v);
				while (a[--j] > v);
				if (i >= j) break;
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			t = a[i];
			a[i] = a[r];
			a[r] = t;
			stack.Push(r);
			stack.Push(i+1);
			stack.Push(i-1);
			stack.Push(l);
		}
	}
}

template <class TYPE>
void QuickSort_nr2(TYPE a[], int n)
{
	TYPE v, t;
	int i, j;
	int l, r;  // 스택에 저장할 구간의 정보 
	ArrayStack<int> stack(n*2+2);
	l = 0;
	r = n-1;
	stack.Push(r);
	stack.Push(l);
	while (!stack.IsEmpty())
	{
		l = stack.Pop();
		r = stack.Pop();
		if (r-l+1 > 1)   // 종료조건 r-l+1은 구간의 길이 
		{
			v = a[r];	// pivot value
			i = l - 1;
			j = r;
			while (true)
			{
				while (a[++i] < v);
				while (a[--j] > v);
				if (i >= j) break;
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			t = a[i];
			a[i] = a[r];
			a[r] = t;
			stack.Push(r);
			stack.Push(i+1);
			stack.Push(i-1);
			stack.Push(l);
		}
	}
}

template <class TYPE>
void QuickSort_random(TYPE a[], int n)
{
	TYPE v, t;
	int i, j;
	int l, r;  // 스택에 저장할 구간의 정보 
	ArrayStack<int> stack(n*2+2);
	l = 0;
	r = n-1;
	stack.Push(r);
	stack.Push(l);
	while (!stack.IsEmpty())
	{
		l = stack.Pop();
		r = stack.Pop();
		if (r-l+1 > 1)   // 종료조건 r-l+1은 구간의 길이 
		{
			// 난수로 pivot value를 선택 
			int pivot = int(((double)rand()/(double)RAND_MAX)*(double)(r-l)) + l;

			v = a[pivot];	// pivot value와 교환 
			a[pivot] = a[r];
			a[r] = v;

			i = l - 1;
			j = r;
			while (true)
			{
				while (a[++i] < v);
				while (a[--j] > v);
				if (i >= j) break;
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			t = a[i];
			a[i] = a[r];
			a[r] = t;
			stack.Push(r);
			stack.Push(i+1);
			stack.Push(i-1);
			stack.Push(l);
		}
	}
}

template <class TYPE>
void QuickSort_median(TYPE a[], int n)
{
	TYPE v, t;
	int i, j;
	int l, r;  // 스택에 저장할 구간의 정보 
	ArrayStack<int> stack(n*2+2);
	l = 0;
	r = n-1;
	stack.Push(r);
	stack.Push(l);
	while (!stack.IsEmpty())
	{
		l = stack.Pop();
		r = stack.Pop();
		if (r-l+1 > 3)   // 종료조건 r-l+1은 구간의 길이 
		{
			// 가운데 값 선택
			int pivot = (r + l) / 2;
			// a[l], a[pivot], a[r] 세 값 정렬 (Bubble Sort)
			if (a[l] > a[pivot])
			{
				v = a[l]; a[l] = a[pivot]; a[pivot] = v;
			}
			if (a[pivot] > a[r])
			{
				v = a[pivot]; a[pivot] = a[r]; a[r] = v;
			}
			if (a[l] > a[pivot])
			{
				v = a[l]; a[l] = a[pivot]; a[pivot] = v;
			}	
			v = a[pivot];   // 중앙값을 a[r-1]과 교환 
			a[pivot] = a[r-1];
			a[r-1] = v;

			i = l;    // 분할구간은 l+1 ~ r-2 
			j = r - 1;
			while (true)
			{
				while (a[++i] < v);
				while (a[--j] > v);
				if (i >= j) break;
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			t = a[i];
			a[i] = a[r-1];  // 주의 
			a[r-1] = t;      //
			stack.Push(r);
			stack.Push(i+1);
			stack.Push(i-1);
			stack.Push(l);
		} else {	// 구간크기가 3보다 작다면 
			// 가운데 값 선택
			int pivot = (r + l) / 2;
			// a[l], a[pivot], a[r] 세 값 정렬 
			if (a[l] > a[pivot])
			{
				v = a[l]; a[l] = a[pivot]; a[pivot] = v;
			}
			if (a[pivot] > a[r])
			{
				v = a[pivot]; a[pivot] = a[r]; a[r] = v;
			}
			if (a[l] > a[pivot])
			{
				v = a[l]; a[l] = a[pivot]; a[pivot] = v;
			}	
		}
	}
}

template <class TYPE>
void QuickSort_sub(TYPE a[], int n)
{
	TYPE v, t;
	int i, j;
	int l, r;  // 스택에 저장할 구간의 정보 
	ArrayStack<int> stack(n*2+2);
	l = 0;
	r = n-1;
	stack.Push(r);
	stack.Push(l);
	while (!stack.IsEmpty())
	{
		l = stack.Pop();
		r = stack.Pop();
		if (r-l+1 > 200)   // 종료조건 r-l+1이 200보다 클때만 
		{
			// 가운데 값 선택
			int pivot = (r + l) / 2;
			// a[l], a[pivot], a[r] 세 값 정렬 
			if (a[l] > a[pivot])
			{
				v = a[l]; a[l] = a[pivot]; a[pivot] = v;
			}
			if (a[pivot] > a[r])
			{
				v = a[pivot]; a[pivot] = a[r]; a[r] = v;
			}
			if (a[l] > a[pivot])
			{
				v = a[l]; a[l] = a[pivot]; a[pivot] = v;
			}	

			v = a[pivot];   // 중앙값을 a[r-1]과 교환 
			a[pivot] = a[r-1];
			a[r-1] = v;

			i = l;    // 분할구간은 l+1 ~ r-2 
			j = r - 1;
			while (true)
			{
				while (a[++i] < v);
				while (a[--j] > v);
				if (i >= j) break;
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
			t = a[i];
			a[i] = a[r-1];  // 주의 
			a[r-1] = t;      //
			stack.Push(r);
			stack.Push(i+1);
			stack.Push(i-1);
			stack.Push(l);
		} else {	// 구간크기가 200보다 작다면 
			InsertionSort(a + l, r - l + 1);
		}
	}
}

};

#endif