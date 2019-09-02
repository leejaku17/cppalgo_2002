#ifndef _BinMap_h
#define _BinMap_h

#include "ArraySeqMap.h"

#include <assert.h>

namespace cppalgo
{
	template <class TYPE> class BinMap : public ArraySeqMap<TYPE>
	{
	public:
		BinMap(int nSize = 100) : ArraySeqMap<TYPE>(nSize) {} 
		~BinMap() { }  // m_pArray는 ~ArraySeqMap에서 지워준다. 
		
		// utility functions
		// implemented in ArraySeqMap

		// operations
		bool Insert(const TYPE& value);
		bool FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const;
		bool FindNext(TYPE& value, MapPos& pos) const;

	protected:
		 bool _find(MapPos& pos) const;
	};

	template <class TYPE>
		bool BinMap<TYPE>::_find(MapPos& pos) const
	{
		int mid;
		int left = 0;
		int right = m_nLen - 1;

		while (right >= left)
		{
			mid = (right + left) / 2;
			if (pos.key == m_pArray[mid])
			{
				pos.index = mid;
				return true;
			}
			if (pos.key > m_pArray[mid])
				left = mid + 1;
			else
				right = mid - 1;
		}
		// 못찾은 경우 
		return false;
	}

	template <class TYPE>
		bool BinMap<TYPE>::Insert(const TYPE& value)
	{
		if (!ArraySeqMap<TYPE>::Insert(value))
			return false;

		// Insertion Sort
		for (int j = m_nLen - 1; j > 0; j--)
		{
			if (m_pArray[j-1] > value)
				m_pArray[j] = m_pArray[j-1];
			else
				break;
		}
		m_pArray[j] = value;
		return true;
	}

	template <class TYPE>
		bool BinMap<TYPE>::FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const
	{
		if (!ArraySeqMap<TYPE>::FindFirst(key, value, pos))
			return false;

		// 동일키 블럭의 중간에 떨어질 수 있음. 앞으로 이동 
		for (int j = pos.index; j > 0; j--)
		{
			if (!(m_pArray[j-1] == value))
				break;
		}
		pos.index = j;
		value = m_pArray[pos.index];
		return true;
	}

	template <class TYPE>
		bool BinMap<TYPE>::FindNext(TYPE& value, MapPos& pos) const
	{
		if (pos.index + 1 >= m_nLen)
			return false;
		
		if (m_pArray[pos.index + 1] == pos.key)
		{
			pos.index++;
			value = m_pArray[pos.index];
			return true;
		} 
		else 
		{
			return false;
		}
	}
};

#endif