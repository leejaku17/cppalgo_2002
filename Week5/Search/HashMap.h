#ifndef _HashMap_h
#define _HashMap_h

#include <assert.h>

namespace cppalgo
{
	template <class TYPE, class HASH> class HashMap
	{
	public:
		struct MapPos {
			TYPE key;
			long index;
		};
		enum NodeStatus {
			EMPTY, DELETED, AVAIL
		};
	protected:
		struct Node {
			TYPE data;
			NodeStatus status;
			Node() { status = EMPTY; }  // 초기화 
		};

	public:
		HashMap(const HASH& hash, int nSize = 100);
		~HashMap() { delete [] m_pArray; }
		//utility function
		long GetCount() const { return m_nCount; }
		bool IsEmpty() const { return m_nCount == 0; }
		void RemoveAll() { for (int i = 0; i < m_nArraySize; i++) m_pArray[i].status = EMPTY; }

		// operations
		bool Find(const TYPE& key, TYPE& value) const;
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);

		bool FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const;
		bool FindNext(TYPE& value, MapPos& pos) const;
		bool RemoveAt(const MapPos& pos);

	protected:
		Node *m_pArray;
		long m_nArraySize;
		long m_nCount;
		HASH m_hash;

		bool _find(MapPos& pos) const;
		int _next(const TYPE& key) const { return 1; }
	};

	template <class TYPE, class HASH>
		HashMap<TYPE, HASH>::HashMap(const HASH& hash, int nSize)
	{
		m_hash = hash;

		m_pArray = new Node [nSize];
		assert(m_pArray);

		m_nArraySize = nSize;
		m_nCount = 0;
	}

	template <class TYPE, class HASH>
		bool HashMap<TYPE, HASH>::Find(const TYPE& key, TYPE& value) const
	{
		MapPos pos;
		pos.key = key;
		pos.index = 0;

		if (!_find(pos))
			return false;

		value = m_pArray[pos.index].data;
		return true;
	}

	template <class TYPE, class HASH>
		bool HashMap<TYPE, HASH>::Insert(const TYPE& value)
	{
		int start, index;
		index = start = m_hash.hash(value) % m_nArraySize;
		while (m_pArray[index].status == AVAIL)
		{
			index = (index + _next(value)) % m_nArraySize;
			if (index == start)		// 꽉 찬 경우 , 꽉차 경우는 이렇게 안해도 알 수 있다. m_nCount과 m_nArraySize를 비교하면 된다
				return false;
		}
		m_pArray[index].status = AVAIL;
		m_pArray[index].data = value;
		m_nCount++;
		return true;
	}

	template <class TYPE, class HASH>
		bool HashMap<TYPE, HASH>::Remove(const TYPE& key)
	{
		MapPos pos;
		pos.key = key;
		pos.index = 0;		// 아무 의미 없다. 그냥 초기화 

		if (!_find(pos))
			return false;

		RemoveAt(pos);

		return true;
	}
	
	template <class TYPE, class HASH>
		bool HashMap<TYPE, HASH>::FindFirst(const TYPE& key, TYPE& value, MapPos& pos) const
	{
		pos.key = key;
		pos.index = 0;

		if (!_find(pos))
			return false;

		value = m_pArray[pos.index].data;
		return true;
	}

	template <class TYPE, class HASH>
		bool HashMap<TYPE, HASH>::FindNext(TYPE& value, MapPos& pos) const
	{
		int start, index;

		index = start = (pos.index + _next(pos.key)) % m_nArraySize;		// 다음 아이템으로 이동...
		while (m_pArray[index].status != EMPTY)		// AVAIL or DELETED
		{
			if (m_pArray[index].data == pos.key)
			{
				pos.index = index;
				value = m_pArray[index].data;
				return true;
			}

			index = (index + _next(pos.key)) % m_nArraySize;
			if (index == start)		// 꽉 찬 경우 , 꽉차 경우는 이렇게 안해도 알 수 있다. m_nCount과 m_nArraySize를 비교하면 된다
				return false;
		}
		return false;	// end of cluster를 만났으나 값은 찾지 못했다. 
	}

	template <class TYPE, class HASH>
		bool HashMap<TYPE, HASH>::RemoveAt(const MapPos& pos)
	{
		// Lazy Deletion
		if (m_nCount <= 0 || pos.index < 0 || pos.index >= m_nArraySize)
			return false;

		if (m_pArray[pos.index].status != AVAIL)		// 지울게 없다. 
			return false;
		m_pArray[pos.index].status = DELETED;
		m_nCount--;

		// Hash에서의 삭제는 약간의 문제성이 있다.  DELETED라고 표시한 것은 검색의 효율에 아무런 도움을 주지 않는다. 
		// 그러므로 삭제와 삽입이 빈번하다보면 결국 모든 chunk들이 연결되어 버리게 된다. 
		return true;
	}
	
	template <class TYPE, class HASH>
		bool HashMap<TYPE, HASH>::_find(MapPos& pos) const
	{
		int start, index;
		index = start = m_hash.hash(pos.key) % m_nArraySize;
		while (m_pArray[index].status != EMPTY)		// AVAIL or DELETED
		{
			if (m_pArray[index].status == AVAIL && m_pArray[index].data == pos.key)
			{
				pos.index = index;
				return true;
			}

			index = (index + _next(pos.key)) % m_nArraySize;
			if (index == start)		// 꽉 찬 경우 , 꽉차 경우는 이렇게 안해도 알 수 있다. m_nCount과 m_nArraySize를 비교하면 된다
				return false;
		}
		return false;	// end of cluster를 만났으나 값은 찾지 못했다. 
	}
};

#endif