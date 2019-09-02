// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "VisualSort.h"
#include "ChildView.h"
#include "../sort/QuickSort.h"
#include "../sort/HeapSort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int arraySort[6][100];

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(IDM_BUBBLE_SORT, OnBubbleSort)
	ON_COMMAND(IDM_INSERTION_SORT, OnInsertionSort)
	ON_COMMAND(IDM_SELECTION_SORT, OnSelectionSort)
	ON_COMMAND(IDM_QUICK_SORT, OnQuickSort)
	ON_COMMAND(IDM_HEAP_SORT, OnHeapSort)
	ON_COMMAND(IDM_SHELL_SORT, OnShellSort)
	ON_COMMAND(IDM_MERGE_SORT, OnMergeSort)
	ON_COMMAND(IDM_STRAIGHT_RADIX_SORT, OnStraightRadixSort)
	ON_COMMAND(IDM_RADIX_EXCHANGE_SORT, OnRadixExchangeSort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	for (int i = 0; i < 6; i++)
		DrawArray(arraySort[i], 100, i);
}


void CChildView::OnBubbleSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);

	int i, j;
	int t;
	for (i = 0; i < n - 1; i++)
	{
		if (i % 20 == 0 && i > 0) {
			CopyArray(a, i/20);
		}

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
	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

void CChildView::OnInsertionSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);

	int i, j;
	int t;
	for (i = 1; i < n; i++)
	{
		if (i % 20 == 0 && i > 0) {
			CopyArray(a, i/20);
		}

		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}	
	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

void CChildView::OnSelectionSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);

	//--------------
	int min;		// 최소값 저장
	int minindex;   // 최소값 인덱스 저장 
	int i, j;

	for (i = 0; i < n - 1; i++)
	{
		if (i % 20 == 0 && i > 0) {
			CopyArray(a, i/20);
		}

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

	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

void CChildView::DrawArray(int a[], int n, int order)
{
	int x, y;
	x = (order % 3) * n * 2 + ((order % 3) + 1) * 10;
	y = (order / 3) * n * 2 + ((order / 3) + 1) * 10;

	// draw frame
	CDC *pdc = GetDC();
	pdc->Rectangle(x, y, x + n*2 + 2, y + n*2 + 2);

	for (int i = 0; i < n; i++) 
	{
		pdc->SetPixel(x + i*2, y + (n - a[i])*2, RGB(0, 0, 0));
		pdc->SetPixel(x + i*2 + 1, y + (n - a[i])*2, RGB(0, 0, 0));
		pdc->SetPixel(x + i*2, y + (n - a[i])*2 - 1, RGB(0, 0, 0));
		pdc->SetPixel(x + i*2 + 1, y + (n - a[i])*2 - 1, RGB(0, 0, 0));
	}

	ReleaseDC(pdc);
}

void CChildView::FillRandom(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}

	// shuffle
	for (i = 0; i < 300; i++) 
	{
		int j = int(((double)rand() / (double)RAND_MAX) * n);
		int k = int(((double)rand() / (double)RAND_MAX) * n);
		int t;
		t = a[j];
		a[j] = a[k];
		a[k] = t;
	}
}

void CChildView::CopyArray(int a[], int order)
{
	for (int i = 0;i < 100; i++) 
	{
		arraySort[order][i] = a[i];
	}
}

void CChildView::OnQuickSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);

	//--------------

	int v, t;
	int i, j;
	int l, r;  // 스택에 저장할 구간의 정보 
	
	int count = 0;

	cppalgo::ListStack<int> stack;
	l = 0;
	r = n-1;
	stack.Push(r);
	stack.Push(l);
	while (!stack.IsEmpty())
	{
		l = stack.Pop();
		r = stack.Pop();
		if ((r-l+1 > 12 && r-l+1 < 20)) CopyArray(a, (++count) > 5 ? 5 : count);

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
	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

void CChildView::OnHeapSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);
	//-------------
	int i;
	cppalgo::Heap<int> heap(a, n);
	for (i = 1; i <= n; i++) {
		heap.Insert(heap.a(i));
		if (i == n/2) CopyArray(a, 1);
	}
	CopyArray(a, 2);
	while (n > 1) {
		heap.a(n--) = heap.Extract();
		if (n == 66)
			CopyArray(a, 3);
		if (n == 33)
			CopyArray(a, 4);
	}

	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

void CChildView::OnShellSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);
	//-------------
	int i, j, k, h;
	int count = 1;
	int v;
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

		CopyArray(a, count++);
	}
	
	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

void CChildView::OnMergeSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);
	//-------------
	int i, j, k, first, second, size;
	int *b;
	// 병합할 메모리공간 할당 
	b = new int [n];
	assert(b != 0);

	for (size = 1; size < n; size *= 2)
	{
		first = 0;
		second = size;
		while (second < n)
		{
			i = first;
			j = second;
			k = first;
			while (i < first + size || (j < second + size && j < n))
			{
				if (a[i] > a[j])
				{
					if (j < second + size && j < n)
						b[k++] = a[j++];
					else
						b[k++] = a[i++];
				} 
				else 
				{
					if (i < first + size)
						b[k++] = a[i++];
					else
						b[k++] = a[j++];
				}
			}
			first += 2*size;
			second += 2*size;
		}
		for (i = 0; i < n; i++)
			a[i] = b[i];    // 복사 

		if (size == 4)
			CopyArray(a, 1);
		if (size == 8)
			CopyArray(a, 2);
		if (size == 16)
			CopyArray(a, 3);
		if (size == 32)
			CopyArray(a, 4);
	}
	delete [] b;

	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

inline unsigned long bits(unsigned long x, unsigned long k, unsigned long j)
{
	return (x >> k) & ~(~0 << j);
}


void CChildView::OnStraightRadixSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);
	//-------------
	int i, j;
	unsigned long *b, *count;
	unsigned long w = 8;
	unsigned long m = 1;
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

		if (i == 2)
			CopyArray(a, 1);
		if (i == 3)
			CopyArray(a, 2);
		if (i == 4)
			CopyArray(a, 3);
		if (i == 5)
			CopyArray(a, 4);
	}
	delete [] b;
	delete [] count;
	// Terminate
	CopyArray(a, 5);
	Invalidate();
}

void CChildView::OnRadixExchangeSort() 
{
	int a[100];
	int n = 100;
	FillRandom(a, n);
	CopyArray(a, 0);
	//-------------
	unsigned long t;
	int i, j;
	int l, r;
	int b;

	int oo = 1;

	cppalgo::ListStack<int> stack;

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

			if (3 < b && b < 6) CopyArray(a, oo++);
/*
			if (b == 3)
				CopyArray(a, 4);
			if (b == 4)
				CopyArray(a, 3);
			if (b == 5)
				CopyArray(a, 2);
			if (b == 6)
				CopyArray(a, 1);
				*/

		}
	}
	// Terminate
	CopyArray(a, 5);
	Invalidate();
}
