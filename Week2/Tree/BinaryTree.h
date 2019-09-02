#ifndef _BinaryTree_h
#define _BinaryTree_h

namespace cppalgo {
	
	template <class TYPE> class BinaryTree
	{
    public:
		BinaryTree();
		~BinaryTree();
		void RemoveAll();
	
	protected:
		struct Node {
			TYPE data;
			Node* pLeft;
			Node* pRight;
			Node() { pLeft = pRight = 0; }
		};
	
		Node* m_pNodeHead;
		Node* m_pNodeTail;
	
		void RemoveSubtree(Node *pNode);
	};
	
	template <class TYPE> BinaryTree<TYPE>::BinaryTree()
	{
		m_pNodeHead = new Node;
		m_pNodeTail = new Node;
		
		m_pNodeHead->pLeft = m_pNodeTail;
		m_pNodeHead->pRight = m_pNodeTail;
		
		m_pNodeTail->pLeft = m_pNodeTail;
		m_pNodeTail->pRight = m_pNodeTail;
	}
	
	template <class TYPE> BinaryTree<TYPE>::~BinaryTree()
	{
		RemoveAll();
		if (m_pNodeHead)
			delete m_pNodeHead;
		if (m_pNodeTail)
			delete m_pNodeTail;
	}
	
	template <class TYPE> void BinaryTree<TYPE>::RemoveSubtree(Node *pNode)
	{
		if (pNode != m_pNodeTail)
		{
			RemoveSubtree(pNode->pLeft);
			RemoveSubtree(pNode->pRight);
			delete pNode;
		}
	}
	
	template <class TYPE> void BinaryTree<TYPE>::RemoveAll()
	{
		// Post Order traverse를 통해 전체 노드를 삭제한다. 
		RemoveSubtree(m_pNodeHead->pLeft);
		m_pNodeHead->pLeft = m_pNodeTail;
	}
};
#endif
