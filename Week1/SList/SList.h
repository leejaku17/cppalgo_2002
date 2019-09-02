#ifndef _SList_h
#define _SList_h

namespace cppalgo {
	
	typedef void* POS;

	template <class TYPE> class SimpleList
	{
	public:
		enum Exception {
			INVALID_POS,
			EMPTY_LIST
		};
	public:
		// constructor / destructor
		SimpleList() { _init(); }
		~SimpleList() { _clear(); }

		// basic operation
		TYPE DeleteNext(POS  pos);
		POS InsertNext(POS pos, const TYPE& newElem);
		void RemoveAll();
		bool IsEmpty() const { return m_nCount == 0; }
		int GetCount() const { return m_nCount; }
		bool IsValid(POS pos) const { return (pos != (POS)m_pNodeHead && pos != (POS)m_pNodeTail && pos != 0); }

		// head operation
		POS AddHead(const TYPE& newElem) { return InsertNext(m_pNodeHead, newElem); }
		TYPE RemoveHead() { return DeleteNext(m_pNodeHead); }
		TYPE& GetHead();
		TYPE GetHead() const;

		// traverse
		POS GetHeadPosition() const { return (m_nCount > 0) ? m_pNodeHead->pNext : 0; }
		TYPE& GetNext(POS& pos);
		TYPE GetNext(POS& pos) const;

		// Get/Set
		TYPE& GetAt(POS pos);
		TYPE GetAt(POS pos) const;
		void SetAt(POS pos, const TYPE& newElem);

		// Find
		POS Find(const TYPE& searchVal, POS startAfter = 0) const;
		POS FindIndex(int nIndex) const;

	protected:
		struct Node 
		{
			TYPE data;
			Node *pNext;
			Node() { pNext = 0; }
		};
		
		Node *m_pNodeHead;
		Node *m_pNodeTail;
		int m_nCount;
		
		void _init();
		void _clear();
	};

	template <class TYPE> void SimpleList<TYPE>::_init() 
	{
		m_pNodeHead = new Node;
		m_pNodeTail = new Node;

		m_pNodeHead->pNext = m_pNodeTail;
		m_pNodeTail->pNext = m_pNodeTail;

		m_nCount = 0;
	}

	template <class TYPE> void SimpleList<TYPE>::_clear()
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

	template <class TYPE> TYPE SimpleList<TYPE>::DeleteNext(POS pos)
	{
		Node *pNode = (Node*)pos;

		if (pNode == 0)
			throw INVALID_POS;
		if (pNode->pNext == m_pNodeTail)
			throw INVALID_POS;

		Node *pNodeDel = pNode->pNext;

		pNode->pNext = pNode->pNext->pNext;
		
		TYPE rt = pNodeDel->data;
		delete pNodeDel;
		m_nCount --;

		return rt;
	}

	template <class TYPE> POS SimpleList<TYPE>::InsertNext(POS pos, const TYPE& newElem)
	{
		Node *pNode = (Node*)pos;
		if (pNode == 0) 
			return 0;
		if (pNode == m_pNodeTail)
			return 0;

		Node *pNewNode = new Node;
		pNewNode->data = newElem;

		pNewNode->pNext = pNode->pNext;
		pNode->pNext = pNewNode;

		m_nCount++;

		return pNewNode;
	}

	template <class TYPE> TYPE& SimpleList<TYPE>::GetHead()
	{
		if (m_nCount > 0) 
			return m_pNodeHead->pNext->data;
		else
			throw EMPTY_LIST;
	}

	template <class TYPE> TYPE SimpleList<TYPE>::GetHead() const
	{
		if (m_nCount > 0)
			return m_pNodeHead->pNext->data;
		else
			throw EMPTY_LIST;
	}

	template <class TYPE> TYPE& SimpleList<TYPE>::GetNext(POS& pos)
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

	template <class TYPE> TYPE SimpleList<TYPE>::GetNext(POS& pos) const
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

	template <class TYPE> void SimpleList<TYPE>::RemoveAll()
	{
		int n = GetCount();
		for (int i = 0; i < n; i++)
			RemoveHead();
	}

	template <class TYPE> TYPE& SimpleList<TYPE>::GetAt(POS pos)
	{
		if (IsValid(pos))
			return ((Node*)pos)->data;
		else
			throw INVALID_POS;
	}

	template <class TYPE> TYPE SimpleList<TYPE>::GetAt(POS pos) const
	{
		if (IsValid(pos))
			return ((Node*)pos)->data;
		else
			throw INVALID_POS;
	}

	template <class TYPE> void SimpleList<TYPE>::SetAt(POS pos, const TYPE& newElem)
	{
		if (IsValid(pos))
			((Node*)pos)->data = newElem;
		else
			throw INVALID_POS;
	}

	template <class TYPE> POS SimpleList<TYPE>::Find(const TYPE& searchVal, POS startAfter) const
	{
		POS pos;
		if (!IsValid(startAfter))
			pos = GetHeadPosition();
		else
			pos = startAfter;

		while (pos) 
		{
			TYPE d = GetAt(pos);
			if (searchVal == d) 
				break;
			GetNext(pos);
		}

		return pos;
	}

	template <class TYPE> POS SimpleList<TYPE>::FindIndex(int nIndex) const
	{
		if (nIndex >= GetCount())
			return 0;
		int nCount = 0;

		POS pos = GetHeadPosition();
		for (int i = 0; i < nIndex; i++) 
		{
			GetNext(pos);
		}
		return pos;
	}
};
	
#endif