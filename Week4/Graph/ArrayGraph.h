#ifndef _ArrayGraph_h
#define _ArrayGraph_h

#include <string.h>
#include "../Search/RBTreeMap.h"
#include "../Stack/ListStack.h"
#include "../Queue/ListQueue.h"
#include "EdgeHeap.h"

namespace cppalgo
{
	typedef long EDGE;
	template <class VERTEX> class ArrayGraph 
	{
	public:
		ArrayGraph(int nSize = 100);
		~ArrayGraph();
		// utilities
		bool AddEdge(const VERTEX& v1, const VERTEX& v2, EDGE w);
		bool AddEdgeDir(const VERTEX& v1, const VERTEX& v2, EDGE w);
		EDGE GetEdge(const VERTEX& v1, const VERTEX& v2);
		bool SetEdge(const VERTEX& v1, const VERTEX& v2, EDGE w);
		// virtual functions
		virtual void Visit(const VERTEX& v) {}
		virtual void VisitEdge(const VERTEX& v1, const VERTEX& v2) {}
		// operations
		void DFS();
		void DFS_nr();
		void BFS();
		long CountComponents();
		void FindAP(SimpleList<VERTEX>& aplist);
		EDGE MCST_Pfs();
		EDGE MCST_Kruskal();
		void ShortestPath_Pfs(const VERTEX& start);
		void ShortestPath_Dijkstra(const VERTEX& start);
	protected:
		long _FindVertex(const VERTEX& v);
		long _AddVertex(const VERTEX& v);
		EDGE _GetEdgeByIndex(long i, long j);
		bool _SetEdgeByIndex(long i, long j, EDGE w);
		void _DFS(long i, bool* visited);
		long _FindAP(long i, long order, SimpleList<VERTEX>& aplist, long *porder, long& son_of_root);
		
		VERTEX* m_pVertices;
		long* m_pEdges;
		long m_nSize;
		long m_nCount;
	};

	template <class VERTEX>
		ArrayGraph<VERTEX>::ArrayGraph(int nSize)
	{
			m_pVertices = new VERTEX[nSize];
			m_pEdges = new EDGE [nSize*nSize];
			memset(m_pEdges, 0, nSize*nSize*sizeof(long));
			m_nSize = nSize;
			m_nCount = 0;
	}

	template <class VERTEX>
		ArrayGraph<VERTEX>::~ArrayGraph()
	{
			delete [] m_pVertices;
			delete [] m_pEdges;
	}

	template <class VERTEX>
		long ArrayGraph<VERTEX>::_FindVertex(const VERTEX& v)
	{
		for (int i = 0; i < m_nCount; i++) 
		{
			if (m_pVertices[i] == v) return i;
		}
		return -1;
	}

	template <class VERTEX>
		long ArrayGraph<VERTEX>::_AddVertex(const VERTEX& v)
	{
		if (m_nCount >= m_nSize)	// 꽉 찼음.
			return -1;
		m_pVertices[m_nCount] = v;
		return m_nCount++;
	}

	template <class VERTEX>
		EDGE ArrayGraph<VERTEX>::_GetEdgeByIndex(long i, long j)
	{
		return m_pEdges[i*m_nSize + j];
	}

	template <class VERTEX>
		bool ArrayGraph<VERTEX>::_SetEdgeByIndex(long i, long j, EDGE w)
	{
		if (i < 0 || i >= m_nCount || j < 0 || j >= m_nCount)
			return false;
		m_pEdges[i*m_nSize + j] = w;
		return true;
	}

	template <class VERTEX>
		bool ArrayGraph<VERTEX>::AddEdge(const VERTEX& v1, const VERTEX& v2, EDGE w)
	{
		long iv1, iv2;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) iv1 = _AddVertex(v1);
		if (iv1 < 0) return false;
		
		iv2 = _FindVertex(v2);
		if (iv2 < 0) iv2 = _AddVertex(v2);
		if (iv2 < 0) return false;

		_SetEdgeByIndex(iv1, iv2, w);
		_SetEdgeByIndex(iv2, iv1, w);
		return true;
	}

	template <class VERTEX>
		bool ArrayGraph<VERTEX>::AddEdgeDir(const VERTEX& v1, const VERTEX& v2, EDGE w)
	{
		long iv1, iv2;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) iv1 = _AddVertex(v1);
		if (iv1 < 0) return false;
		
		iv2 = _FindVertex(v2);
		if (iv2 < 0) iv2 = _AddVertex(v2);
		if (iv2 < 0) return false;

		_SetEdgeByIndex(iv1, iv2, w);

		return true;
	}

	template <class VERTEX>
		EDGE ArrayGraph<VERTEX>::GetEdge(const VERTEX& v1, const VERTEX& v2)
	{
		long iv1, iv2;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) return 0;
		
		iv2 = _FindVertex(v2);
		if (iv2 < 0) return 0;

		return _GetEdgeByIndex(iv1, iv2);
	}

	template <class VERTEX>
		bool ArrayGraph<VERTEX>::SetEdge(const VERTEX& v1, const VERTEX& v2, EDGE w)
	{
		long iv1, iv2;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) return false;
		
		iv2 = _FindVertex(v2);
		if (iv2 < 0) return false;

		return _SetEdgeByIndex(iv1, iv2, w);		
	}

	template <class VERTEX>
		void ArrayGraph<VERTEX>::DFS()
	{
		bool *visited = new bool [m_nCount];
		for (int i = 0; i < m_nCount; i++) visited[i] = false;		
		for (i = 0; i < m_nCount; i++)
			if (!visited[i]) _DFS(i, visited);
		delete [] visited;
	}

	template <class VERTEX>
		void ArrayGraph<VERTEX>::_DFS(long i, bool *visited)
	{
		long j;		
		visited[i] = true;
		Visit(m_pVertices[i]);  // 방문 
		for (j = 0; j < m_nCount; j++)
		{
			if (_GetEdgeByIndex(i, j) != 0 && !visited[j])
				_DFS(j, visited);
		}
	}

	template <class VERTEX>
		void ArrayGraph<VERTEX>::DFS_nr()
	{
		long i, j, k;
		ListStack<long> stack;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;

		for (i = 0; i < m_nCount; i++)
		{
			if (!visited[i])
			{
				stack.Push(i);
				visited[i] = true;				
				while (!stack.IsEmpty())
				{
					k = stack.Pop();
					Visit(m_pVertices[k]);
					for (j = 0; j < m_nCount; j++)
					{
						if (_GetEdgeByIndex(k, j) != 0 && !visited[j]) 
						{
							stack.Push(j);
							visited[j] = true;							
						}
					}
				}
			}
		}
		delete [] visited;
	}

	template <class VERTEX>
		void ArrayGraph<VERTEX>::BFS()
	{
		long i, j, k;
		ListQueue<long> queue;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;
		
		for (i = 0; i < m_nCount; i++)
		{
			if (!visited[i])
			{
				queue.Put(i);
				visited[i] = true;				
				while (!queue.IsEmpty())
				{
					k = queue.Get();
					Visit(m_pVertices[k]);
					for (j = 0; j < m_nCount; j++)
					{
						if (_GetEdgeByIndex(k, j) != 0 && !visited[j]) 
						{
							queue.Put(j);
							visited[j] = true;							
						}
					}
				}
			}
		}
		delete [] visited;
	}

	template <class VERTEX>
		long ArrayGraph<VERTEX>::CountComponents()
	{
		long count = 0;
		long i, j, k;
		ListStack<long> stack;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;
		
		for (i = 0; i < m_nCount; i++)
		{
			if (!visited[i])
			{
				count++;
				stack.Push(i);
				visited[i] = true;				
				while (!stack.IsEmpty())
				{
					k = stack.Pop();
					for (j = 0; j < m_nCount; j++)
					{
						if (_GetEdgeByIndex(k, j) != 0 && !visited[j]) 
						{
							stack.Push(j);
							visited[j] = true;							
						}
					}
				}
			}
		}
		delete [] visited;
		return count;
	}

	template <class VERTEX>
		void ArrayGraph<VERTEX>::FindAP(SimpleList<VERTEX>& aplist)
	{
		long *porder = new long[m_nCount];
		memset(porder, 0, m_nCount*sizeof(long));
		long son_of_root = 0;

		_FindAP(0, 1, aplist, porder, son_of_root);
		delete [] porder;

		if (son_of_root > 1)
			aplist.AddHead(m_pVertices[0]);
	}

	template <class VERTEX>
		long ArrayGraph<VERTEX>::_FindAP(long i, long order, SimpleList<VERTEX>& aplist, long* porder, long& son_of_root)
	{
		long min, m;

		porder[i] = min = ++order;		

		for (int j = 0; j < m_nCount; j++)
		{
			if (_GetEdgeByIndex(i, j) != 0)
			{
				if (porder[j] == 0)  // if Tree Edge
				{
					if (i == 0) son_of_root++;	// root의 자식을 세기. 

					m = _FindAP(j, order, aplist, porder, son_of_root);
					if (m < min) min = m;  // 최소값 업데이트 
					if (m >= porder[i] && i != 0)
					{
						// Articulation Points: 중복될 수 있으므로 체크 
						if (!aplist.Find(m_pVertices[i]))
							aplist.AddHead(m_pVertices[i]);
					}
				}
				else	// Non-Tree Edge
				{
					if (porder[j] < min)
						min = porder[j];
				}
			}
		}
		return min;
	}

	template <class VERTEX>
	EDGE ArrayGraph<VERTEX>::MCST_Pfs()
	{
		long i, j, k;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		EDGE sum = 0;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;

		for (i = 0; i < m_nCount; i++)
		{
			if (!visited[i])
			{
				pq.Insert(m_pVertices[i], m_pVertices[i], 0);
				visited[i] = true;				
				while (!pq.IsEmpty())
				{
					p = pq.Extract();

					if (p.v1 != p.v2) {
						VisitEdge(p.v1, p.v2);
						sum += -p.w;
					}
					k = _FindVertex(p.v2);

					for (j = 0; j < m_nCount; j++)
					{
						if (_GetEdgeByIndex(k, j) != 0)
						{
							if (!visited[j])
							{   // 방문하지 않은 정점들에 대해서 
								pq.Insert(m_pVertices[k], m_pVertices[j], -_GetEdgeByIndex(k, j));
								visited[j] = true;								
							}
							else 
							{	// 방문한 정점들에 대해서. 
								pq.Update(m_pVertices[k], m_pVertices[j], -_GetEdgeByIndex(k, j));
							}
						}
					}
				}
			}
		}
		delete [] visited;
		return sum;
	}

	template <class VERTEX>
	EDGE ArrayGraph<VERTEX>::MCST_Kruskal()
	{
		EdgeHeap<char> pq;
		Set<char> set;
		int i, j;
		EDGE sum = 0;
		int nEdge = 0;

		// insert all edges to heap
		for (i = 0; i < m_nCount; i++) {
			for (j = i+1; j < m_nCount; j++) {
				if (_GetEdgeByIndex(i, j)) {
					pq.Insert(m_pVertices[i], m_pVertices[j], -_GetEdgeByIndex(i, j));
				}
			}
		}

		while (!pq.IsEmpty() && nEdge < m_nCount - 1) {
			// MCST의 간선수는 정점수 - 1
			EdgeHeap<char>::Pair p = pq.Extract();
			int i1 = set.Find(p.v1);
			if (i1 < 0) i1 = set.AddSet(p.v1);
			int i2 = set.Find(p.v2);
			if (i2 < 0) i2 = set.AddSet(p.v2);
			if (i1 >= 0 && i2 >= 0 && i1 != i2) {	// 회로가 아니면 
				VisitEdge(p.v1, p.v2);
				nEdge++;
				sum += -p.w;
				set.UnionByIndex(i1, i2);
			}
		}

		return sum;
	}

	template <class VERTEX>
		void ArrayGraph<VERTEX>::ShortestPath_Pfs(const VERTEX& start)
	{
		long i, j, k;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		EDGE sum = 0;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;
		
		i = _FindVertex(start);
		pq.Insert(m_pVertices[i], m_pVertices[i], 0);
		visited[i] = true;
		while (!pq.IsEmpty())
		{
			p = pq.Extract();
			
			if (p.v1 != p.v2) {
				VisitEdge(p.v1, p.v2);
				sum += -p.w;
			}
			k = _FindVertex(p.v2);
			
			for (j = 0; j < m_nCount; j++)
			{
				if (_GetEdgeByIndex(k, j) != 0)
				{
					if (!visited[j])
					{   // 방문하지 않은 정점들에 대해서 
						pq.Insert(m_pVertices[k], m_pVertices[j], p.w - _GetEdgeByIndex(k, j));
						visited[j] = true;							
					}
					else 
					{	// 방문한 정점들에 대해서. 
						pq.Update(m_pVertices[k], m_pVertices[j], p.w - _GetEdgeByIndex(k, j));
					}
				}
			}
		}
		delete [] visited;
	}

	template <class VERTEX>
		void ArrayGraph<VERTEX>::ShortestPath_Dijkstra(const VERTEX& start)
	{
		int i;
		int count = 0;
		int x, y;
		int s = _FindVertex(start);
		bool *visited = new bool [m_nCount];
		EDGE *distance = new EDGE [m_nCount];
		int *parent = new int [m_nCount];

		for (i = 0; i < m_nCount; i++) {
			visited[i] = false;
			distance[i] = _GetEdgeByIndex(s, i);
			if (i != s) parent[i] = s;
			else parent[i] = -1;
		}

		visited[s] = true;
		count++;

		while (count < m_nCount) {
			x = 0;
			while (visited[x]) x++;
			for (i = x; i < m_nCount; i++) {
				if (!visited[i] && distance[i] > 0 && distance[i] < distance[x]) 
					x = i;
			}

			visited[x] = true;
			count++;

			for (y = 0; y < m_nCount; y++) {
				if (x == y || _GetEdgeByIndex(x, y) == 0 || visited[y]) continue;
				// y는 방문하지 않은 (x,y)간선이 존재하는 정점 
				EDGE d = distance[x] + _GetEdgeByIndex(x, y);
				if (distance[y] == 0 || d < distance[y]) {   // distance[y]가 infinite이거나 d보다 크면 
					distance[y] = d;
					parent[y] = x;
				}
			}
		}

		// visit edge
		for (i = 0; i < m_nCount; i++) {
			if (parent[i] >= 0) VisitEdge(m_pVertices[parent[i]], m_pVertices[i]);
		}

		delete [] visited;
		delete [] distance;
		delete [] parent;
	}
};

#endif