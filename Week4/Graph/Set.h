#ifndef _Set_h
#define _Set_h

namespace cppalgo
{
	template <class TYPE> class Set
	{
	public:
		struct Item {
			TYPE elem;  
			int parent;	// parent index
			int height;
		};
	public:
		Set(int nSize = 100) {
			m_pArray = new Item [nSize];
			m_nArrayLen = nSize;
			m_nCount = 0;
		}
		~Set() { delete [] m_pArray; }

		TYPE& GetItem(int index) const { return m_pArray[index].elem; }
		int GetParent(int index) const { return m_pArray[index].parent; }
		int GetIndex(const TYPE& t) const {
			for (int i = 0; i < m_nCount; i++) 
				if (m_pArray[i].elem == t) return i;
			return -1;
		}
		int AddSet(const TYPE& t) {
			if (m_nCount >= m_nArrayLen) return false;
			m_pArray[m_nCount].elem = t;
			m_pArray[m_nCount].parent = -1;
			m_pArray[m_nCount].height = 1;
			return m_nCount++;
		}

		int Find(const TYPE& t) {
			for (int i = 0; i < m_nCount && m_pArray[i].elem != t; i++);
			if (i >= m_nCount) return -1; 
			while (m_pArray[i].parent >= 0) i = m_pArray[i].parent;
			return i;
		}
		void Union(const TYPE& t1, const TYPE& t2) {
			int i1 = Find(t1);
			int i2 = Find(t2);
			if (i1 < 0 || i2 < 0) return;
			UnionByIndex(i1, i2);
		}
		void UnionByIndex(int i1, int i2) {
			if (m_pArray[i1].height > m_pArray[i2].height) {
				m_pArray[i2].parent = i1;
			} else if (m_pArray[i1].height < m_pArray[i2].height) {
				m_pArray[i1].parent = i2;
			} else { // m_pArray[i1].height == m_pArray[i2].height
				m_pArray[i2].parent = i1;
				m_pArray[i1].height++;
			}
		}

	private:
		Item *m_pArray;
		int m_nArrayLen;
		int m_nCount;
	};
};

#endif