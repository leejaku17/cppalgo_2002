#ifndef _BTreeMap_h
#define _BTreeMap_h

namespace cppalgo
{
	template <class TYPE> class BTreeMap
	{
	public:
		enum Exception {
			INVALID_DIMENSION,		// BTree의 차수는 3이상의 홀수여야 한다. 
		};
	public:
		BTreeMap(int dim = 5);
		~BTreeMap();
		// utilites
		long GetCount() const { return m_nCount; }
		bool IsEmpty() const { return m_nCount == 0; }
		void RemoveAll();
		// operations
		bool Find(const TYPE& key, TYPE& value) const;
		bool Insert(const TYPE& value);
		bool Remove(const TYPE& key);
		// BTree도 역시 중복키에 대한 처리가 힘들다. 
	protected:
		struct Node;
		typedef Node* PNODE;
		struct Node {
			TYPE *m_pKeys;
			Node **m_pChildren;
			int m_nKeys;

			Node(int dim) { 
				m_pKeys = new TYPE [dim];
				m_pChildren = new Node* [dim+ 1];
				for (int i = 0; i <= dim; i++) m_pChildren[i] = 0;
				m_nKeys = 0;
			}
			~Node() {
				delete [] m_pKeys;
				delete [] m_pChildren;
			}
			PNODE& Left(int n) { return m_pChildren[n]; }
			PNODE& Right(int n) { return m_pChildren[n+1]; }
			TYPE& Key(int n) { return m_pKeys[n]; }
			int& Size() { return m_nKeys; }
			void AddValue(const TYPE& value, Node* left, Node* right)
			{
				int i;
				i = m_nKeys;  // 삽입정렬 
				while (i > 0 && Key(i-1) > value)
				{
					Key(i) = Key(i-1);
					Left(i+1) = Left(i);
					i--;
				}
				m_nKeys++;
				Key(i) = value;
				Left(i) = left;
				Right(i) = right;
			}
			void DelValue(int index)
			{
				if (index < Size() - 1) {
					for (int i = index+1; i < Size(); i++)
					{
						Key(i-1) = Key(i);
						Left(i-1) = Left(i);
					}
					Left(i-1) = Left(i);
				}
				m_nKeys--;
			}
			int FindKey(const TYPE& key)
			{
				for (int i = 0; i < m_nKeys; i++)
					if (key == Key(i)) return i;
				return -1;
			}
			void Clear(int dim)
			{	
				m_nKeys = 0;
				for (int i = 0; i <= dim; i++)
					m_pChildren[i] = 0;
			}
		};
		Node* m_pNodeHead;
		void _RemoveSubtree(Node *pNode);
		Node* _Split(const TYPE& key, Node* pivot);
		bool _BorrowKey(Node *p, int index);
		Node* _BindNode(Node* p, int index);
		TYPE _SwapKey(Node *del, int index);

		long m_nCount;
		long m_nDim;
	};
	
	template <class TYPE>
		BTreeMap<TYPE>::BTreeMap(int dim)
	{
		if (dim < 3 || dim % 2 == 0)
			throw INVALID_DIMENSION;
			
		m_pNodeHead = new Node(dim);
		m_nDim = dim;
	}

	template <class TYPE>
		BTreeMap<TYPE>::~BTreeMap()
	{
		RemoveAll();
		delete m_pNodeHead;
	}

	template <class TYPE>
		void BTreeMap<TYPE>::_RemoveSubtree(Node *pNode)
	{
		if (pNode != 0)
		{
			for (int i = 0; i <= pNode->Size(); i++)
				_RemoveSubtree(pNode->Left(i));
			delete pNode;
		}
	}

	template <class TYPE>
		void BTreeMap<TYPE>::RemoveAll()
	{
		_RemoveSubtree(m_pNodeHead->Left(0));
		m_pNodeHead->Left(0) = 0;
	}

	template <class TYPE>
		bool BTreeMap<TYPE>::Find(const TYPE& key, TYPE& value) const
	{
		Node *t;
		int index;
		t = m_pNodeHead->Left(0);
		while (t != 0 && (index = t->FindKey(key)) < 0)
		{
			for (int i = 0; i < t->Size() && key > t->Key(i); i++);
			t = t->Left(i);
		}

		if (t == 0) return false;
		
		value = t->Key(index);
		return true;
	}

	template <class TYPE>
		BTreeMap<TYPE>::Node* BTreeMap<TYPE>::_Split(const TYPE& key, Node* pivot)
	{
		Node *left, *right;
		Node *split;   // 리턴할 노드 
		int i, j;
		
		right = new Node(m_nDim);

		// 경우 1 : 분할할 노드가 Root 인 경우 
		if (pivot == m_pNodeHead)
		{
			split= pivot->Left(0);		// child == root

			// left child 생성 
			left = new Node(m_nDim);
			for (i = 0; i < m_nDim/2; i++)
			{
				left->Key(i) = split->Key(i);
				left->Left(i) = split->Left(i);
			}
			left->Left(i) = split->Left(i);
			left->Size() = m_nDim/2;

			// right child 생성 
			for (i = m_nDim/2+1, j = 0; i < m_nDim; i++, j++)
			{
				right->Key(j) = split->Key(i);
				right->Left(j) = split->Left(i);
			}
			right->Left(j) = split->Left(i);
			right->Size() = m_nDim/2;

			// 부모노드 정리 
			TYPE temp = split->Key(m_nDim/2);
			split->Clear(m_nDim);
			split->AddValue(temp, left, right);
		} 
		// 경우 2 : 분할할 노드가 Root가 아닌 경우 
		else
		{
			// 분할할 노드를 찾기 
			for (i = 0; i < pivot->Size() && key > pivot->Key(i); i++);

			// 왼쪽 노드는 이미 있는 노드이므로 갯수만 조정 
			left = pivot->Left(i);
			left->Size() = m_nDim/2;

			// 오른쪽 노드 생성 
			for (i = m_nDim/2+1, j = 0; i < m_nDim; i++, j++)
			{
				right->Key(j) = left->Key(i);
				right->Left(j) = left->Left(i);
			}
			right->Left(j) = left->Left(i);
			right->Size() = m_nDim / 2;

			// 중간키를 부모에 삽입 
			pivot->AddValue(left->Key(m_nDim/2), left, right);
			split = pivot;
		}
		return split;
	}

	template <class TYPE>
		bool BTreeMap<TYPE>::Insert(const TYPE& value)
	{
		Node *t, *p;
		int i;
		p = m_pNodeHead;
		t = m_pNodeHead->Left(0);
		if (t == 0)  // 뿌리노드가 없다면 특별히 생성해주어야 한다. 
		{
			t = new Node(m_nDim);
			m_pNodeHead->Left(0) = t;
		}
		while (t != 0)
		{
			if (t->FindKey(value) >= 0)		// 중복키 삽입금지 
				return false;
			if (t->Size() == m_nDim)	// 꽉찬 노드이면 분할한다. 
				t = _Split(value, p);
			p = t;
			for (i = 0; i < t->Size() && value > t->Key(i); i++);
			t = t->Left(i);
		}
		p->AddValue(value, 0, 0);   // 외부노드로 삽입 
		m_nCount++;
		return true;
	}

	template <class TYPE>
		bool BTreeMap<TYPE>::_BorrowKey(Node *p, int index)
	{
		int from, to;
		Node *p1, *p2;
		to = index;
		if (index == p->Size())	// 가장 오른쪽인 경우 왼쪽형제에게 빌림 
			from = index - 1;
		else  // 아니면 오른쪽 형제에게서 빌림 
			from = index + 1;
		p1 = p->Left(from);   // p1 = 빌려주는 노드 
		p2 = p->Left(to);       // p2 = 빌리는 노드 
		if (p1->Size() <= m_nDim/2)   // 빌려줄 키가 없을 때 실패를 리턴 
			return false;
		if (from > to)   // 오른쪽 형제에게서 빌림 
		{
			p2->AddValue(p->Key(to), p2->Left(p2->Size()), p1->Left(0));
			p->Key(to) = p1->Key(0);
			p1->DelValue(0);
		}
		else   // 왼쪽 형제에게서 빌림 
		{
			p2->AddValue(p->Key(from), p1->Left(p1->Size()), p2->Left(0));
			p->Key(from) = p1->Key(p1->Size() - 1);
			p1->DelValue(p1->Size() - 1);
		}
		return true;
	}

	template <class TYPE>
		BTreeMap<TYPE>::Node* BTreeMap<TYPE>::_BindNode(Node* p, int index)
	{
		Node *left, *right;
		int i;
		if (index == p->Size()) index--;	// 가장 오른쪽이면 index 감소 
		left = p->Left(index);
		right = p->Right(index);
		left->Key(left->Size()++) = p->Key(index);   // 왼쪽노드에 부모키를 복사 
		for (i = 0; i < right->Size(); i++)  // 왼쪽노드에 오른쪽 노드를 복사 
		{
			left->Key(left->Size()) = right->Key(i);
			left->Left(left->Size()++) = right->Left(i);
		}
		left->Left(left->Size()) = right->Left(i);
		p->DelValue(index);   // 부모노드에서 결합한 키를 삭제 
		p->Left(index) = left;  // 포인터 조절 
		delete right;
		if (p->Size() == 0)   // 뿌리노드일 수 밖에 없음 이경우....
		{
			delete p;
			m_pNodeHead->Left(0) = left;
		}
		return left;  // 결합된 노드를 리턴 
	}

	template <class TYPE>
		TYPE BTreeMap<TYPE>::_SwapKey(Node *del, int index)
	{
		Node *cdd, *cddp;    // cdd는 대체노드, cddp는 대체노드의 부모 
		cddp = del;
		cdd = cddp->Right(index);   // 삭제키의 오른쪽 자식 
		while (cdd->Left(0) != 0)
		{
			cddp = cdd;
			cdd = cdd->Left(0);
		}
		del->Key(index) = cdd->Key(0);   // 키 대체 
		return cdd->Key(0);
	}

	template <class TYPE>
		bool BTreeMap<TYPE>::Remove(const TYPE& key)
	{
		Node *t, *p;
		int pi = 0;   // 부모의 index
		int ti = 0;   // 현재노드의 index
		TYPE value = key;
		
		p = m_pNodeHead;
		t = m_pNodeHead->Left(0);
		while (t != 0)
		{
			if (t->Size() <= m_nDim/2 && p != m_pNodeHead) // 확장할 필요가 있으면 확장 
			{
				if (!_BorrowKey(p, pi))		// 형제에게서 빌려보고 실패하면 형제와 결합 
					t = _BindNode(p, pi);
			}

			if ((ti = t->FindKey(value)) >= 0)  // 삭제키가 이 노드에 있으면 
			{
				if (t->Left(0) == 0) break;  // 외부노드이면 break;
				else value = _SwapKey(t, ti);   // 내부노드이면 바꿈. 이제 새로운 value를 아래로 내려야 한다. 
			}
			p = t;
			for (pi = 0; pi < t->Size() && (value > t->Key(pi) || value == t->Key(pi)); pi++);
			t = t->Left(pi);
		}
		if (t == 0) return false;   // 찾을 수 없음. 
		if (t->Size() <= m_nDim/2 && p != m_pNodeHead)  // 외부노드인데 키수가 너무 적으면 
			if (!_BorrowKey(p, pi)) t = _BindNode(p, pi);
		t->DelValue(t->FindKey(value));  // 노드의 키를 삭제 
		m_nCount--;
		return true;
	}
};

#endif