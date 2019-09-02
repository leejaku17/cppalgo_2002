#ifndef _RadixTreeMap_h
#define _RadixTreeMap_h

#include "../Tree/BinaryTree.h"

// 기수 검색은 중복키가 들어갈 수 없다. 

namespace cppalgo
{
	// RadixTreeMap의 TYPE에는 비트를 다룰 수 있는 타입만 가능하다. 
	// 음수도 검색이 가능하다. 
	// 기타타입도 bits 함수에 대응하는 것만 있다면 가능하다.  
	// 아니면 ...    unsigned long TYPE::operator >> (unsigned long) 이 정의되면 된다. 
	template <class TYPE> class RadixTreeMap : public BinaryTree<TYPE>
	{
	public:
		RadixTreeMap() : BinaryTree<TYPE>() { m_nCount = 0; }
		~RadixTreeMap() {}

		// utilities
		long GetCount() const { return m_nCount; }
		long IsEmpty() const { return m_nCount == 0; }
		void RemoveAll() { BinaryTree<TYPE>::RemoveAll(); m_nCount = 0; }

		// Operations
		bool Find(const TYPE& key, TYPE& value) const;
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);

		// RadixTree는 중복키가 들어갈 수 없다.  중복키가 들어가면 tree의 높이가 비트수보다 커져서 검색이 제대로 안된다. 
		// 만약 중복키를 넣으려면 Tree + List 개념으로 가야한다. 
	protected:
		unsigned long bits(const TYPE& x, unsigned long k, unsigned long j) const
		{
			return (x >> k) & ~(~0 << j);
		}
		long m_nCount;
	};

	template <class TYPE>
		bool RadixTreeMap<TYPE>::Find(const TYPE& key, TYPE& value) const
	{
		Node *t;
		unsigned b = 0;
		t = m_pNodeHead->pLeft;
		while (t != m_pNodeTail && !(key == t->data))
			t = bits(key, b++, 1) ? t->pRight : t->pLeft;

		if (t == m_pNodeTail)	// 못찾았음
			return false;

		value = t->data;
		return true;
	}

	template <class TYPE>
		bool RadixTreeMap<TYPE>::Insert(const TYPE& value)
	{
		Node *p, *t;
		unsigned b = 0;

		p = m_pNodeHead;
		t = m_pNodeHead->pLeft;
		while (t != m_pNodeTail)
		{
			if (value == t->data)		// 동일한 키는 넣을 수 없다!!!!
				return false;	

			p = t;
			t = bits(value, b++, 1) ? t->pRight : t->pLeft;
		}
		
		t = new Node;
		t->data = value;
		t->pLeft = m_pNodeTail;
		t->pRight = m_pNodeTail;
		
		if (bits(value, b-1, 1) && p != m_pNodeHead) p->pRight = t;
		else p->pLeft = t;
		
		m_nCount++;
		
		return true;
	}

	template <class TYPE>
		bool RadixTreeMap<TYPE>::Remove(const TYPE& key)
	{
		if (IsEmpty()) return false;
		Node *del, *delp, *cdd, *cddp;
		unsigned b = 0;

		// 삭제할 노드를 찾는다. 
		delp = m_pNodeHead;
		del = m_pNodeHead->pLeft;
		while (del != m_pNodeTail && !(key == del->data))
		{
			delp = del;
			del = bits(key, b++, 1) ? del->pRight : del->pLeft;
		}
		if (del == m_pNodeTail) return false;		// 못찾았음. 
		if (del->pRight == m_pNodeTail)  // 경우 1
		{
			cdd = del->pLeft;
		}
		else if (del->pRight->pLeft == m_pNodeTail)  // 경우 2
		{
			cdd = del->pRight;
			cdd->pLeft = del->pLeft;
		}
		else	// 경우 3
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
		if (bits(key, b-1, 1) && delp != m_pNodeHead) 
			delp->pRight = cdd;
		else
			delp->pLeft = cdd;

		delete del;
		m_nCount--;
		return true;
	}
};

#endif