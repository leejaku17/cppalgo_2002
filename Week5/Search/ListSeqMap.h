#ifndef _ListSeqMap_h
#define _ListSeqMap_h

#include "../SList/DList.h"

namespace cppalgo
{
	template <class TYPE> class ListSeqMap
	{
	public:
		struct MapPos
		{
			TYPE key;
			POS pos;
		};
	public:
		ListSeqMap() {}
		~ListSeqMap() {}

		// utility functions
		long GetCount() const { return m_list.GetCount(); }
		bool IsEmpty() const { return m_list.IsEmpty(); }
		void RemoveAll() { m_list.RemoveAll(); }

		// operations
		bool Find(const TYPE& key, TYPE& value);
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);

		bool FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const;
		bool FindNext(TYPE& value, MapPos& pos) const;
		bool RemoveAt(const MapPos& pos);

	protected:
		DoubleList<TYPE> m_list;
		bool _find(MapPos& pos) const;
	};

	template <class TYPE>
		bool ListSeqMap<TYPE>::_find(MapPos& pos) const
	{
		pos.pos = m_list.Find(pos.key, pos.pos);
		if (pos.pos == 0)
			return false;
		else
			return true;
	}

	template <class TYPE>
		bool ListSeqMap<TYPE>::Find(const TYPE& key, TYPE& value)
	{
		// MRU 법칙으로 list 내용을 바꾸므로 const function이 아니다. 
		MapPos pos;
		pos.pos = 0;
		pos.key = key;

		if (!_find(pos))
			return false;
		value = m_list.GetAt(pos.pos);

		/*
		// MRU 법칙으로 찾은 값을 제일 앞으로 올림 
		m_list.DeleteAt(pos.pos);
		m_list.AddHead(value);
		*/

		return true;
	}
	
	template <class TYPE>
		bool ListSeqMap<TYPE>::Insert(const TYPE& value)
	{
		m_list.AddTail(value);
		return true;
	}

	template <class TYPE>
		bool ListSeqMap<TYPE>::Remove(const TYPE& key)
	{
		MapPos pos;
		pos.pos = 0;
		pos.key = key;

		if (!_find(pos))
			return false;
		
		RemoveAt(pos);
		return true;
	}

	template <class TYPE>
		bool ListSeqMap<TYPE>::FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const
	{
		pos.pos = 0;
		pos.key = key;

		if (!_find(pos))
			return false;
		value = m_list.GetAt(pos.pos);
		return true;
	}

	template <class TYPE>
		bool ListSeqMap<TYPE>::FindNext(TYPE& value, MapPos& pos) const
	{
		m_list.GetNext(pos.pos);
		if (pos.pos == 0)
			return false;
		if (!_find(pos))
			return false;
		value = m_list.GetAt(pos.pos);
		return true;
	}

	template <class TYPE>
		bool ListSeqMap<TYPE>::RemoveAt(const MapPos& pos)
	{
		bool result = true;
		try {
			m_list.DeleteAt(pos.pos);
		} catch (DoubleList<TYPE>::Exception) {
			result = false;
		}
		return result;
	}
};



#endif