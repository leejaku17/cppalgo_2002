#ifndef _EdgeHeap_h
#define _EdgeHeap_h

#include "../sort/HeapSort.h"	// for Heap class

namespace cppalgo 
{
	typedef long EDGE;

	template <class VERTEX> class EdgeHeap 
	{
	public:
		struct Pair {
			VERTEX v1;	
			VERTEX v2;
			EDGE w;
			Pair(const VERTEX& vv1, const VERTEX& vv2, EDGE ww) { v1 = vv1; v2 = vv2; w = ww; }
			Pair() { w = 0; }
		};
	public:
		EdgeHeap(int nSize = 100) { 
			m_pArray = new Pair[nSize];
			m_nArrayLen = nSize; 
			m_nHeapLen = 0; 
		}
		~EdgeHeap() { delete [] m_pArray; }
		Pair& a(int k) { return m_pArray[k-1]; }
		bool IsEmpty() { return m_nHeapLen == 0; }

		void UpHeap(int k)
		{
			Pair p;
			p = a(k);
			while (p.w > a(k/2).w && k > 1) {
				a(k) = a(k/2);
				k /= 2;
			}
			a(k) = p;
		}

		void DownHeap(int k)
		{
			int i;
			Pair p;
			p = a(k);
			while (k <= m_nHeapLen/2) {
				i = k*2;
				if (i < m_nHeapLen && a(i+1).w > a(i).w) i++;
				if (p.w > a(i).w || p.w == a(i).w) break;
				a(k) = a(i);
				k = i;
			}
			a(k) = p;
		}

		bool Insert(const VERTEX& p, const VERTEX& v, EDGE w)
		{
			if (m_nHeapLen >= m_nArrayLen - 1) return false;
			a(++m_nHeapLen) = Pair(p, v, w);
			UpHeap(m_nHeapLen);
			return true;
		}

		Pair Extract(void)
		{
			Pair p = a(1);
			a(1) = a(m_nHeapLen--);
			DownHeap(1);
			return p;
		}
		
		bool Update(const VERTEX& p, const VERTEX& v, EDGE w)
		{
			// vertex Ã£±â 
			for (int i = 0; i < m_nHeapLen; i++) {
				if (m_pArray[i].v2 == v && m_pArray[i].w < w) {
					m_pArray[i].w = w;
					m_pArray[i].v1 = p;
					for (int k = m_nHeapLen/2; k >= 1; k--)
						DownHeap(k);
					return true;
				}
			}
			return false;
		}

	private:
		Pair *m_pArray;
		int m_nArrayLen;
		int m_nHeapLen;
	};
};

#endif