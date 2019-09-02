#ifndef _RBTreeMap_h
#define _RBTreeMap_h

#include "BinTreeMap.h"

namespace cppalgo
{
	template <class TYPE> class RBTreeMap
	{
	public:
		RBTreeMap();
		~RBTreeMap();
		
		// Utilities
		long GetCount() const { return m_nCount; }
		bool IsEmpty() const { return m_nCount == 0; }
		void RemoveAll();
		// Operations
		bool Find(const TYPE& key, TYPE& value) const;
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);
		// RBTreeMap에는 중복키 들어갈 수 없음.
		// FindFirst / FindNext / RemoveAt 생략 
	protected:
		struct Node 
		{
			TYPE data;
			Node *pLeft;
			Node *pRight;
			bool Red;
			Node() { pLeft = pRight = 0; Red = false; }
		};
		
		Node* _Rotate(const TYPE& key, Node* pivot);
		bool _IsLeafNode(const Node *p) const;
		bool _Is2Node(const Node *p) const;
		bool _DelLeafNode(const TYPE& key, Node *delp, Node *del);
		bool _RedAsParent(Node *delgp, Node *delp, Node *sib);
		TYPE _SwapKey(Node *del);
		bool _BorrowKey(Node *delgp, Node *delp, Node* del, Node *sib);
		void _BindNode(Node *delp);
		void RemoveSubtree(Node *pNode);

		Node *m_pNodeHead;
		long m_nCount;
	};

	template <class TYPE> RBTreeMap<TYPE>::RBTreeMap()
	{
		m_pNodeHead = new Node;
		
		m_pNodeHead->pLeft = 0;
		m_pNodeHead->pRight = 0;
	}

	template <class TYPE> RBTreeMap<TYPE>::~RBTreeMap()
	{
		RemoveAll();
		if (m_pNodeHead)
			delete m_pNodeHead;
	}

	template <class TYPE> void RBTreeMap<TYPE>::RemoveSubtree(Node *pNode)
	{
		if (pNode != 0)
		{
			RemoveSubtree(pNode->pLeft);
			RemoveSubtree(pNode->pRight);
			delete pNode;
		}
	}

	template <class TYPE> void RBTreeMap<TYPE>::RemoveAll()
	{
		RemoveSubtree(m_pNodeHead->pLeft);
		m_pNodeHead->pLeft = 0;
	}

	template <class TYPE>
		bool RBTreeMap<TYPE>::Find(const TYPE& key, TYPE& value) const
	{
		Node *s;

		s = m_pNodeHead->pLeft;
		while (s && !(key == s->data))
		{
			if (key > s->data) s = s->pRight;
			else s = s->pLeft;
		}
		if (s == 0)
			return false;

		value = s->data;
		return true;
	}

	template <class TYPE>
		bool RBTreeMap<TYPE>::Insert(const TYPE& value)
	{
		Node *t, *p, *gp, *ggp;
		ggp = gp = p = (Node*)m_pNodeHead;
		t = (Node*)m_pNodeHead->pLeft;
		while (t)
		{
			if (value == t->data) return false;	// 중복키 삽입금지 
			if (t->pLeft && t->pRight && t->pLeft->Red && t->pRight->Red)
			{	// Color Promotion
				t->Red = true;
				t->pLeft->Red = t->pRight->Red = false;
				if (p->Red)  // 회전이 필요 
				{
					gp->Red = true;
					if ((value> gp->data) != (value > p->data))  // double rotation
						p = _Rotate(value, gp);
					t = _Rotate(value, ggp);
					t->Red = false;
				}
				m_pNodeHead->pLeft->Red = false;  // 뿌리는 검정으로 
			}
			ggp = gp; gp = p; p = t;
			if (value > t->data) t = t->pRight;
			else t = t->pLeft;
		}
		t = new Node;
		t->data = value;
		t->pLeft = t->pRight = 0;
		t->Red = true;	// 새로삽입되는 노드는 빨강 
		if (value > p->data && p != m_pNodeHead) p->pRight = t;
		else p->pLeft = t;
		m_nCount++;

		if (p->Red)  // 부모가 빨강이면 한번더 회전을 해주어야. 
		{
			gp->Red = true;
			if ((value> gp->data) != (value > p->data))  // double rotation
				p = _Rotate(value, gp);
			t = _Rotate(value, ggp);
			t->Red = false;
		}
		m_pNodeHead->pLeft->Red = false;  // 뿌리는 검정으로 
		return true;
	}

	template <class TYPE>
		bool RBTreeMap<TYPE>::Remove(const TYPE& key)
	{
		Node *delgp, *delp, *del, *sib;
		TYPE value = key;

		delgp = delp = m_pNodeHead;
		del = m_pNodeHead->pLeft;
		sib = 0;
		while (!_IsLeafNode(del)) {
			if (!del->Red) {	// del 이 black이면 Rotation
				if (_RedAsParent(delgp, delp, sib)) {
					// delgp와 sib의 위치가 변했다. 새로 수정 
					delgp = sib;
					if (del->data > delp->data || del->data == delp->data) sib = delp->pLeft;
					else sib = delp->pRight;
				}
			}

			if (del != m_pNodeHead->pLeft && _Is2Node(del)) {
				if (!_BorrowKey(delgp, delp, del, sib))
					_BindNode(delp);
			}

			if (value == del->data)	value = _SwapKey(del);
			
			delgp = delp;
			delp = del;
			if (value > del->data || value == del->data) {
				// swapkey로 인해 같은 값이 나올 수 있음.
				// In-order successor를 사용하기 때문에 오른쪽으로 
				sib = del->pLeft;
				del = del->pRight;				
			}
			else {
				sib = del->pRight;
				del = del->pLeft;
			}
		}

		if (!del->Red) {	// del 이 black이면 Rotation
			if (_RedAsParent(delgp, delp, sib)) {
				// delgp와  sib의 위치가 변했다. 새로 수정 
				delgp = sib;
				if (del->data > delp->data || del->data == delp->data) sib = delp->pLeft;
				else sib = delp->pRight;
			}
		}
		if (del != m_pNodeHead->pLeft && _Is2Node(del)) {
			if (!_BorrowKey(delgp, delp, del, sib))
				_BindNode(delp);
		}

		if (_DelLeafNode(value, delp, del)) {
			m_nCount--;
			return true;
		} else {	
			return false;
		}
	}

	template <class TYPE>
		RBTreeMap<TYPE>::Node* RBTreeMap<TYPE>::_Rotate(const TYPE& key, Node* pivot)
	{
		Node *child, *gchild;
		if ((key > pivot->data || key == pivot->data) && pivot != m_pNodeHead)
			child = (Node*)pivot->pRight;
		else
			child = (Node*)pivot->pLeft;
		if (key > child->data || key == child->data) // Rotate Left
		{
			gchild = (Node*)child->pRight;	
			child->pRight = gchild->pLeft;
			gchild->pLeft = (Node*)child;
		}
		else	// Rotate Right
		{
			gchild = (Node*)child->pLeft;
			child->pLeft = gchild->pRight;
			gchild->pRight = (Node*)child;
		}
		if ((key > pivot->data || key == pivot->data) && pivot != m_pNodeHead)
			pivot->pRight = gchild;
		else
			pivot->pLeft = gchild;
		return gchild;
	}

	template <class TYPE>
		bool RBTreeMap<TYPE>::_IsLeafNode(const Node *p) const 
	{ 
		if (p == 0) return false;
		if ((p->pLeft == 0 || (p->pLeft && p->pLeft->Red && !p->pLeft->pLeft && !p->pLeft->pRight)) 
			&& (p->pRight == 0 || (p->pRight && p->pRight->Red && !p->pRight->pLeft && !p->pRight->pRight))) 
			return true; 
		else 
			return false;
	}

	template <class TYPE>
		bool RBTreeMap<TYPE>::_Is2Node(const Node *p) const 
	{
		if (p == 0) return false;
		if (p->Red == true) return false;
		if ((p->pLeft == 0 && p->pRight == 0) 
			|| (p->pLeft && p->pRight && !p->pLeft->Red && !p->pRight->Red))
			return true;
		else
			return false;
	}
	
	template <class TYPE>
		bool RBTreeMap<TYPE>::_DelLeafNode(const TYPE& key, Node *delp, Node *del) 
	{
		if (key == del->data && !del->pLeft && !del->pRight) { 
			// red leaf나 black leaf 인 경우 
			delete del;
			if ((key > delp->data || key == delp->data) && delp != m_pNodeHead)
				delp->pRight = 0;
			else
				delp->pLeft = 0;
			return true;
		} else if (key == del->data) {	// black node일 경우 
			Node *ret;
			if (del->pLeft) {
				del->pLeft->pRight = del->pRight;
				ret = del->pLeft;
				ret->Red = false;
				delete del;
			} else if (del->pRight) {	// Delete Right Child
				del->pRight->pLeft = del->pLeft;
				ret = del->pRight;
				ret->Red = false;
				delete del;
			} 
			if ((ret->data > delp->data || ret->data == delp->data) && delp != m_pNodeHead)
				delp->pRight = ret;
			else
				delp->pLeft = ret;
			return true;
		} else if (del->pLeft && key == del->pLeft->data) {
			delete del->pLeft;
			del->pLeft = 0;
			return true;
		} else if (del->pRight && key == del->pRight->data) {
			delete del->pRight;
			del->pRight = 0;
			return true;
		} else {
			return false;
		}	
	}

	template <class TYPE>
		bool RBTreeMap<TYPE>::_RedAsParent(Node *delgp, Node *delp, Node *sib) 
	{
		if (sib == 0 || !sib->Red) return false;
		_Rotate(sib->data, delgp);
		sib->Red = false;
		delp->Red = true;
		return true;
	}

	template <class TYPE>
		TYPE RBTreeMap<TYPE>::_SwapKey(Node *del) 
	{
		Node *cdd;
		cdd = del->pRight;
		while (cdd->pLeft) 
			cdd = cdd->pLeft;
		del->data = cdd->data;
		return cdd->data;
	}

	template <class TYPE>
		bool RBTreeMap<TYPE>::_BorrowKey(Node *delgp, Node *delp, Node* del, Node *sib)
	{
		Node *sibrc;
		if (_Is2Node(sib)) return false;
		if (del->data > sib->data) {
			if (sib->pLeft && sib->pLeft->Red) sibrc = sib->pLeft;
			else sibrc = sib->pRight;
		} else {
			if (sib->pRight && sib->pRight->Red) sibrc = sib->pRight;
			else sibrc = sib->pLeft;
		}
		if ((delp->data > sib->data) != (sib->data > sibrc->data)) {
			// double rotation
			_Rotate(sibrc->data, delp);
			_Rotate(sibrc->data, delgp);
			sib->Red = false;
			sibrc->Red = true;
		} else {
			// single rotation
			_Rotate(sib->data, delgp);
			sib->Red = true;
			sibrc->Red = false;
		}
		del->Red = true;
		delp->Red = false;
		
		// Root가 빨강이면 검정으로 바꾼다. 
		if (m_pNodeHead->pLeft->Red)
			m_pNodeHead->pLeft->Red = false;
		return true;
	}

	template <class TYPE>
		void RBTreeMap<TYPE>::_BindNode(Node *delp) 
	{
		delp->Red = false;
		delp->pLeft->Red = true;
		delp->pRight->Red = true;
	}
};

#endif