#ifndef _ArraySeqMap_h
#define _ArraySeqMap_h

#include <assert.h>

namespace cppalgo
{
	template <class TYPE> class ArraySeqMap
	{
	public:
		struct MapPos
		{
			TYPE key;
			long index;
		};
	public:
		ArraySeqMap(int nSize = 100);
		~ArraySeqMap() { delete [] m_pArray; }

		// utility function
		long GetCount() const { return m_nLen; }
		bool IsEmpty() const { return m_nLen == 0; }
		void RemoveAll() { m_nLen = 0; }

		// operations
		bool Find(const TYPE& key, TYPE& value) const;
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);

		// 중복이 가능한 경우에만 사용되는 operations
		bool FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const;
		bool FindNext(TYPE& value, MapPos& pos) const;
		bool RemoveAt(const MapPos& pos);

	protected:
		TYPE* m_pArray;
		long m_nArraySize;
		long m_nLen;

		virtual bool _find(MapPos& pos) const;
	};

	template <class TYPE>
		ArraySeqMap<TYPE>::ArraySeqMap(int nSize)
	{
		// allocate array
		m_pArray = new TYPE [nSize];
		assert(m_pArray);

		m_nArraySize = nSize;
		m_nLen = 0;
	}
	
	template <class TYPE>
		bool ArraySeqMap<TYPE>::Find(const TYPE& key, TYPE& value) const
	{
		MapPos pos;
		pos.index = 0;
		pos.key = key;

		if (!_find(pos))
			return false;

		value = m_pArray[pos.index];
		return true;
	}
	
	template <class TYPE>
		bool ArraySeqMap<TYPE>::Insert(const TYPE& value)
	{
		// check for too many items
		if (m_nLen + 1 > m_nArraySize)
			return false;			// array full!

		// add new item to end
		m_pArray[m_nLen++] = value;
		return true;
	}
	
	template <class TYPE>
		bool ArraySeqMap<TYPE>::Remove(const TYPE& key)
	{
		MapPos pos;
		pos.index = 0;
		pos.key = key;

		if (!_find(pos))
			return false;

		RemoveAt(pos);
		return true;
	}
	
	template <class TYPE>
		bool ArraySeqMap<TYPE>::FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const
	{
		pos.index = 0;
		pos.key = key;

		if (!_find(pos))
			return false;

		value = m_pArray[pos.index];
		return true;
	}
	
	template <class TYPE>
		bool ArraySeqMap<TYPE>::FindNext(TYPE& value, MapPos& pos) const
	{
		// pos를 하나 증가시키고 find
		pos.index++;
		if (!_find(pos))
			return false;

		value = m_pArray[pos.index];
		return true;
	}
	
	template <class TYPE>
		bool ArraySeqMap<TYPE>::RemoveAt(const MapPos& pos)
	{
		// 뒤놈 당기기 
		for (int i = pos.index + 1; i < m_nLen; i++)
			m_pArray[i-1] = m_pArray[i];

		m_nLen--;

		return true;
	}

	template <class TYPE>
		bool ArraySeqMap<TYPE>::_find(MapPos& pos) const
	{
		if (pos.index >= m_nLen)   // 범위를 벗어나면 
			return false;

		bool found = false;

		for (int i = pos.index; i < m_nLen; i++)
		{
			if (m_pArray[i] == pos.key)		// comparison
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			pos.index = i;
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif