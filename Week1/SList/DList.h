#ifndef _DList_h
#define _DList_h

namespace cppalgo {
	typedef void* POS;
	template <class TYPE> 	class DoubleList
	{
	public:
		enum Exception {
			INVALID_POS,
			EMPTY_LIST
		};
	public:
		DoubleList() { _init(); }
		~DoubleList() { _clear(); }

		int GetCount() const { return m_nCount; }
		bool IsEmpty() const { return m_nCount == 0; }
		
		TYPE& GetHead(); 
		TYPE GetHead() const; 
		TYPE& GetTail();
		TYPE GetTail() const;

		bool IsValid(POS pos) const { return (pos != (POS)m_pNodeHead && pos != (POS)m_pNodeTail && pos != 0); }

		TYPE DeleteAt(POS pos);
		POS InsertBefore(POS pos, const TYPE& newElem);
		POS InsertNext(POS pos, const TYPE& newElem);

		TYPE RemoveHead() { return DeleteAt(m_pNodeHead->pNext); }
		TYPE RemoveTail() { return DeleteAt(m_pNodeTail->pPrev); }
		
		POS AddHead(const TYPE& newElem) { return InsertNext(m_pNodeHead, newElem); }
		POS AddTail(const TYPE& newElem) { return InsertBefore(m_pNodeTail, newElem); }
		
		void RemoveAll();
		
		POS GetHeadPosition() const { return (m_nCount > 0) ? m_pNodeHead->pNext : 0; }
		TYPE& GetNext(POS& pos);
		TYPE GetNext(POS& pos) const;

		POS GetTailPosition() const { return (m_nCount > 0) ? m_pNodeTail->pPrev : 0; }
		TYPE& GetPrev(POS& pos);
		TYPE GetPrev(POS& pos) const;
		
		TYPE& GetAt(POS pos);
		TYPE GetAt(POS pos) const;
		void SetAt(POS pos, const TYPE& newElem);
		
		POS Find(const TYPE& searchValue, POS startAfter = 0) const;
		POS FindReverse(const TYPE& searchValue, POS startFrom = 0) const;
		POS FindIndex(int nIndex) const;
		
	protected:
		struct Node
		{
			TYPE data;
			Node* pNext;
			Node* pPrev;
			Node() { pNext = pPrev = 0; }
		};
		
		Node *m_pNodeHead;
		Node *m_pNodeTail;
		int m_nCount;
		
		void _init();
		void _clear();
		
	};

	template <class TYPE> TYPE& DoubleList<TYPE>::GetHead()
	{
		if (m_nCount > 0)
			return m_pNodeHead->pNext->data;
		else
			throw EMPTY_LIST;
	}

	template <class TYPE> TYPE DoubleList<TYPE>::GetHead() const
	{
		if (m_nCount > 0)
			return m_pNodeHead->pNext->data;
		else
			throw EMPTY_LIST;
	}

	template <class TYPE> TYPE& DoubleList<TYPE>::GetTail()
	{
		if (m_nCount > 0)
			return m_pNodeTail->pPrev->data;
		else
			throw EMPTY_LIST;
	}

	template <class TYPE> TYPE DoubleList<TYPE>::GetTail() const
	{
		if (m_nCount > 0)
			return m_pNodeTail->pPrev->data;
		else
			throw EMPTY_LIST;
	}

	template <class TYPE> TYPE DoubleList<TYPE>::DeleteAt(POS pos)
	{
		if (!IsValid(pos))
			throw INVALID_POS;

		Node *pNode = (Node*)pos;
		pNode->pPrev->pNext = pNode->pNext;
		pNode->pNext->pPrev = pNode->pPrev;

		TYPE data = pNode->data;
		delete pNode;

		m_nCount--;
		return data;
	}

	template <class TYPE> POS DoubleList<TYPE>::InsertBefore(POS pos, const TYPE& newElem)
	{
		if (pos == (POS)m_pNodeHead || pos == 0)
			return 0;

		Node *pNode = (Node*)pos;
		Node *pNewNode = new Node;

		pNewNode->data = newElem;
		pNode->pPrev->pNext = pNewNode;
		pNewNode->pPrev = pNode->pPrev;
		pNode->pPrev = pNewNode;
		pNewNode->pNext = pNode;

		m_nCount ++;

		return pNewNode;
	}

	template <class TYPE> POS DoubleList<TYPE>::InsertNext(POS pos, const TYPE& newElem)
	{
		if (pos == (POS)m_pNodeTail || pos == 0)
			return 0;

		Node *pNode = (Node*)pos;
		Node *pNewNode = new Node;

		pNewNode->data = newElem;
		pNode->pNext->pPrev = pNewNode;
		pNewNode->pNext = pNode->pNext;
		pNode->pNext = pNewNode;
		pNewNode->pPrev = pNode;

		m_nCount ++;

		return pNewNode;
	}

	template <class TYPE> void DoubleList<TYPE>::RemoveAll()
	{
		int n = GetCount();
		for (int i = 0; i < n; i++)
			RemoveHead();
	}

	template <class TYPE> TYPE& DoubleList<TYPE>::GetNext(POS& pos)
	{
		if (!IsValid(pos))
			throw INVALID_POS;

		Node *pNode = (Node*)pos;

		if (!IsValid(pNode->pNext))
			pos = 0;
		else
			pos = pNode->pNext;

		return pNode->data;
	}

	template <class TYPE> TYPE DoubleList<TYPE>::GetNext(POS& pos) const
	{
		if (!IsValid(pos))
			throw INVALID_POS;

		Node *pNode = (Node*)pos;

		if (!IsValid(pNode->pNext))
			pos = 0;
		else
			pos = pNode->pNext;

		return pNode->data;
	}

	template <class TYPE> TYPE& DoubleList<TYPE>::GetPrev(POS& pos)
	{
		if (!IsValid(pos))
			throw INVALID_POS;

		Node *pNode = (Node*)pos;

		if (!IsValid(pNode->pPrev))
			pos = 0;
		else
			pos = pNode->pPrev;

		return pNode->data;
	}

	template <class TYPE> TYPE DoubleList<TYPE>::GetPrev(POS& pos) const
	{
		if (!IsValid(pos))
			throw INVALID_POS;

		Node *pNode = (Node*)pos;

		if (!IsValid(pNode->pPrev))
			pos = 0;
		else
			pos = pNode->pPrev;

		return pNode->data;
	}

	template <class TYPE> TYPE& DoubleList<TYPE>::GetAt(POS pos) 
	{ 
		if (IsValid(pos))
			return ((Node*)pos)->data;
		else
			throw INVALID_POS;
	}

	template <class TYPE> TYPE DoubleList<TYPE>::GetAt(POS pos) const 
	{ 
		if (IsValid(pos))
			return ((Node*)pos)->data;
		else
			throw INVALID_POS;
	}

	template <class TYPE> void DoubleList<TYPE>::SetAt(POS pos, const TYPE& newElem) 
	{ 
		if (IsValid(pos))
			((Node*)pos)->data = newElem;
	}

	template <class TYPE> POS DoubleList<TYPE>::Find(const TYPE& searchValue, POS startAfter) const
	{
		POS pos;
		if (!IsValid(startAfter))
			pos = GetHeadPosition();
		else
			pos = startAfter;

		while (pos)
		{
			TYPE d = GetAt(pos);
			if (searchValue == d)
				break;
			GetNext(pos);
		}
		return pos;
	}

	template <class TYPE> POS DoubleList<TYPE>::FindReverse(const TYPE& searchValue, POS startFrom) const
	{
		POS pos;
		if (!IsValid(startFrom))
			pos = GetTailPosition();
		else
			pos = startFrom;

		while (pos)
		{
			TYPE d = GetAt(pos);
			if (searchValue == d)
				break;
			GetPrev(pos);
		}
		return pos;
	}

	template <class TYPE> POS DoubleList<TYPE>::FindIndex(int nIndex) const
	{
		if (nIndex >= GetCount())
			return 0;
		int nCount = 0;

		POS pos = GetHeadPosition();
		for (int i = 0; i < nIndex; i++)
			GetNext(pos);
		return pos;
	}

	template <class TYPE> void DoubleList<TYPE>::_init()
	{
		m_pNodeHead = new Node;
		m_pNodeTail = new Node;

		m_pNodeHead->pNext = m_pNodeTail;
		m_pNodeHead->pPrev = m_pNodeHead;
		m_pNodeTail->pNext = m_pNodeTail;
		m_pNodeTail->pPrev = m_pNodeHead;

		m_nCount = 0;
	}

	template <class TYPE> void DoubleList<TYPE>::_clear()
	{
		RemoveAll();
		if (m_pNodeHead)
			delete m_pNodeHead;
		if (m_pNodeTail)
			delete m_pNodeTail;

		m_pNodeHead = 0;
		m_pNodeTail = 0;
		m_nCount = 0;
	}
};

#endif