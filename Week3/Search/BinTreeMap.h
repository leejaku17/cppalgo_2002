#ifndef _BinTreeMap_h
#define _BinTreeMap_h

#include "../Tree/BinaryTree.h"

namespace cppalgo
{
	template <class TYPE> class BinTreeMap : public BinaryTree<TYPE>
	{
	public:
		enum Exception {
			INSUFFICIENT_MEMORY_FOR_SORT
		};
	public:
		BinTreeMap() : BinaryTree<TYPE>() { m_nCount = 0; }
		~BinTreeMap() {}        

		// Utilities
		long GetCount() const { return m_nCount; }
		bool IsEmpty() const { return m_nCount == 0; }
		void RemoveAll() { BinaryTree<TYPE>::RemoveAll(); m_nCount = 0; }

		// Operations
		bool Find(const TYPE& key, TYPE& value) const;
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);

		// FindFirst/FindNext는 구현 힘듦 : 다음 데이타라는 개념이 없음.
		// RemoveAt은 구현 힘듦 : 부모노드를 알지 못함. 
		// 그래서 BinaryTree는 중복키를 다루기 힘들다. 

		// 배열 a는 노드수와 크기가 같아야 한다. 
		void Sort(TYPE a[], int n, Node* p = 0) const;
		void Balance();

	protected:
		long m_nCount;
		
		Node* _balance(TYPE a[], int n, bool start = true);
	};

	template <class TYPE>
		bool BinTreeMap<TYPE>::Find(const TYPE& key, TYPE& value) const
	{
		Node *s;

		s = m_pNodeHead->pLeft;
		while (!(key == s->data) && s != m_pNodeTail)
		{
			if (key > s->data) s = s->pRight;
			else s = s->pLeft;
		}
		if (s == m_pNodeTail)
			return false;

		value = s->data;
		return true;
	}

	template <class TYPE>
		bool BinTreeMap<TYPE>::Insert(const TYPE& value)
	{
		Node *p, *s;
		p = m_pNodeHead;
		s = m_pNodeHead->pLeft;

		while (s != m_pNodeTail)
		{
			p = s;   // 부모를 유지한다.
			if (value > s->data) s = s->pRight;
			else s = s->pLeft;
		}

		s = new Node;
		s->data = value;
		s->pLeft = m_pNodeTail;
		s->pRight = m_pNodeTail;

		if (value > p->data && p != m_pNodeHead) p->pRight = s;
		else p->pLeft = s;

		m_nCount++;
		return true;
	}

	template <class TYPE>
		bool BinTreeMap<TYPE>::Remove(const TYPE& key)
	{
		if (IsEmpty()) return false;
		Node *delp, *del;
		Node *cdd, *cddp;

		// 먼저 삭제할 키가 있는 노드를 찾는다. 
		delp = m_pNodeHead;
		del = m_pNodeHead->pLeft;
		while (!(key == del->data) && del != m_pNodeTail)
		{
			delp = del;
			if (key > del->data) del = del->pRight;
			else del = del->pLeft;
		}
		if (del == m_pNodeTail)	// 삭제하고자 하는 키가 없음 
			return false;

		if (del->pRight == m_pNodeTail)  // 경우 1
		{
			cdd = del->pLeft;
		}
		else if (del->pRight->pLeft == m_pNodeTail) // 경우 2
		{
			cdd = del->pRight;
			cdd->pLeft = del->pLeft;
		}
		else		// 경우 3
		{
			cddp = del;
			cdd = del->pRight;
			while (cdd->pLeft != m_pNodeTail)
			{
				cddp = cdd;
				cdd = cdd->pLeft;			
			}

			cddp->pLeft = cdd->pRight;
			cdd->pLeft = del->pLeft;
			cdd->pRight = del->pRight;
		}

		// delp의 자식으로 cdd를 둠 
		if (key > delp->data && delp != m_pNodeHead) delp->pRight = cdd;
		else delp->pLeft = cdd;

		delete del;
		m_nCount--;
		return true;
	}

	template <class TYPE>
		void BinTreeMap<TYPE>::Sort(TYPE a[], int n, Node* p) const
	{
		static int index = 0;
		if (p == 0)		// 초기조건 
		{
			if (m_nCount != n) throw INSUFFICIENT_MEMORY_FOR_SORT;
			index = 0;
			p = m_pNodeHead->pLeft;
		}
		
		if (p != m_pNodeTail)  // 종료 조건 
		{
			Sort(a, n, p->pLeft);
			a[index++] = p->data;
			Sort(a, n, p->pRight);
		}
	}

	template <class TYPE>
		void BinTreeMap<TYPE>::Balance()
	{
		TYPE *a;
		a = new TYPE [m_nCount];
		Sort(a, m_nCount);

		int nCount = m_nCount;
		RemoveAll();

		m_pNodeHead->pLeft = _balance(a, nCount, true);
		m_nCount = nCount;

		delete [] a;
	}

	template <class TYPE>
		BinTreeMap<TYPE>::Node* BinTreeMap<TYPE>::_balance(TYPE a[], int n, bool start)
	{
		static int index = 0;
		if (start)
			index = 0;
		
		Node *p;
		int nl, nr;
		if (n > 0)
		{
			nl = (n-1) / 2;
			nr = n - nl - 1;
			
			p = new Node;
			p->pLeft = _balance(a, nl, false);
			p->data = a[index++];
			p->pRight = _balance(a, nr, false);

			return p;
		}
		else
			return m_pNodeTail;
	}
};

#endif