#ifndef _ChainMap_h
#define _ChainMap_h

#include "../SList/DList.h"

#include <assert.h>

namespace cppalgo
{
	template <class TYPE, class HASH> class ChainMap
	{
	public:
		struct MapPos {
			TYPE key;
			long index;
			POS pos;
		};
	public:
		ChainMap(const HASH& hash, int nSize = 100);
		~ChainMap() { delete [] m_pArray; }
		// utility functions
		long GetCount() const { return m_nCount; }
		bool IsEmpty() const { return m_nCount == 0; }
		void RemoveAll() { for (int i = 0; i < m_nArraySize; i++) m_pArray[i].RemoveAll(); }
		// operations
		bool Find(const TYPE& key, TYPE& value) const;
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);

		bool FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const;
		bool FindNext(TYPE& value, MapPos& pos) const;
		bool RemoveAt(const MapPos& pos);
	protected:
		DoubleList<TYPE> *m_pArray;
		long m_nCount;
		long m_nArraySize;
		HASH m_hash;

		bool _find(MapPos& pos) const;
	};
	
	template <class TYPE, class HASH>
		ChainMap<TYPE, HASH>::ChainMap(const HASH& hash, int nSize)
	{
		m_hash = hash;
		m_pArray = new DoubleList<TYPE> [nSize];
		assert(m_pArray);
		m_nArraySize = nSize;
		m_nCount = 0;
	}

	template <class TYPE, class HASH>
		bool ChainMap<TYPE, HASH>::Find(const TYPE& key, TYPE& value) const
	{
		MapPos pos;
		pos.key = key;
		pos.pos = 0;
		pos.index = 0;

		if (!_find(pos)) return false;
		
		value = m_pArray[pos.index].GetAt(pos.pos);
		return true;
	}

	template <class TYPE, class HASH>
		bool ChainMap<TYPE, HASH>::Insert(const TYPE& value)
	{
		int index = m_hash.hash(value) % m_nArraySize;
		if (m_pArray[index].AddHead(value) == 0)
			return false;
		else
			return true;
	}

	template <class TYPE, class HASH>
		bool ChainMap<TYPE, HASH>::Remove(const TYPE& key)
	{
		MapPos pos;
		pos.key = key;
		pos.index = 0;
		pos.pos = 0;

		if (!_find(pos)) return false;
		RemoveAt(pos);
		return true;
	}	
	
	template <class TYPE, class HASH>
		bool ChainMap<TYPE, HASH>::FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const
	{
		pos.key = key;
		pos.index = 0;
		pos.pos = 0;
		
		if (!_find(pos)) return false;
		value = m_pArray[pos.index].GetAt(pos.pos);
		return true;
	}

	template <class TYPE, class HASH>
		bool ChainMap<TYPE, HASH>::FindNext(TYPE& value, MapPos& pos) const
	{
		m_pArray[pos.index].GetNext(pos.pos);
		if (pos.pos == 0) return false;
		if (!_find(pos)) return false;
		value = m_pArray[pos.index].GetAt(pos.pos);
		return true;
	}

	template <class TYPE, class HASH>
		bool ChainMap<TYPE, HASH>::RemoveAt(const MapPos& pos)
	{
		int index = m_hash.hash(pos.key) % m_nArraySize;
		bool result = true;
		try {
			m_pArray[index].DeleteAt(pos.pos);
		} catch (DoubleList<TYPE>::Exception) {
			result = false;
		}
		return result;
	}

	template <class TYPE, class HASH>
		bool ChainMap<TYPE, HASH>::_find(MapPos& pos) const
	{
		pos.index = m_hash.hash(pos.key) % m_nArraySize;
		pos.pos = m_pArray[pos.index].Find(pos.key, pos.pos);
		if (pos.pos == 0)
			return false;
		else
			return true;
	}
};

#endif