#ifndef _HeapSort_h
#define _HeapSort_h

namespace cppalgo {
template <class TYPE> class Heap
{
public:
	Heap() { m_pArray = 0; m_nArrayLen = 0; m_nHeapLen = 0; }
	Heap(TYPE a[], int n) { m_pArray = a; m_nArrayLen = n; m_nHeapLen = 0;}
	void SetArray(TYPE a[], int n) { m_pArray = a; m_nArrayLen = n; m_nHeapLen = 0; }

	TYPE& a(int k) { return m_pArray[k-1]; } // 첨자조작 
	int GetHeapLen() { return m_nHeapLen; }
	void SetHeapLen(int n) { m_nHeapLen = n; }

	void UpHeap(int k)
	{
		TYPE v;
		v = a(k);
		while (v > a(k/2) && k > 1)
		{
			a(k) = a(k/2);
			k /= 2;
		}
		a(k) = v;
	}

	void DownHeap(int k)
	{
		int i;
		TYPE v;
		v = a(k);
		while (k <= m_nHeapLen/2)  // 내부노드에 대해서만 
		{
			i = k*2;  // Left-Child
			if (i < m_nHeapLen && a(i+1) > a(i))
				i++;
			if (v > a(i) || v == a(i))
				break;
			a(k) = a(i);
			k = i;
		}
		a(k) = v;
	}

	void Insert(TYPE v)
	{
		a(++m_nHeapLen) = v;
		UpHeap(m_nHeapLen);
	}

	TYPE Extract(void)
	{
		TYPE v = a(1);   
		a(1) = a(m_nHeapLen--);
		DownHeap(1);
		return v;
	}

private:
	TYPE *m_pArray;
	int m_nArrayLen;
	int m_nHeapLen;
};

template <class TYPE>
void HeapSort(TYPE a[], int n)
{
	int i;
	Heap<TYPE> heap(a, n);
	for (i = 1; i <= n; i++)
		heap.Insert(heap.a(i));
	while (n > 1)
		heap.a(n--) = heap.Extract();
}

template <class TYPE>
void HeapSort_up(TYPE a[], int n)
{
	int k;
	Heap<TYPE> heap(a, n);
	heap.SetHeapLen(n);
	for (k = n/2; k >= 1; k--)
		heap.DownHeap(k);
	while (n > 1)
		heap.a(n--) = heap.Extract();
}

};

#endif