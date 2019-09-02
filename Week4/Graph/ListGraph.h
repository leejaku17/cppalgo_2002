#ifndef _ListGraph_h
#define _ListGraph_h

#include <string.h>
#include "../Search/RBTreeMap.h"
#include "../Stack/ListStack.h"
#include "../Queue/ListQueue.h"
#include "EdgeHeap.h"

namespace cppalgo
{
	typedef long EDGE;
	template <class VERTEX> class ListGraph
	{
	public:
		ListGraph(int nSize = 100);
		~ListGraph();
		//utilities
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

		void Reach_Dfs(const VERTEX& start);
		void StrongConnect();
		void TopologicalSort();
		void RevTopologicalSort();
		void CriticalActivity();
	protected:
		struct Adj {
			VERTEX vertex;
			EDGE weight;
			bool operator==(const Adj& n) const { return vertex == n.vertex; }
			Adj(const VERTEX& v, EDGE w = 1) { vertex = v; weight = w; }
			Adj() { }
		};
		struct Item {
			VERTEX vertex;
			SimpleList<Adj> list;
		};

		long _FindVertex(const VERTEX& v);
		long _AddVertex(const VERTEX& v);
		void _DFS(long i, bool *visited);
		long _FindAP(long i, long order, SimpleList<VERTEX>& aplist, long *porder, long& son_of_root);
		int _StrongConnect(long i, long order, long* porder, ListStack<long>& stack);
		void _CriticalActivity_forward(int *earliest);
		void _CriticalActivity_backward(int *latest, int initial);
		
		Item *m_pVertices;
		long m_nSize;
		long m_nCount;
	};

	template <class VERTEX>
		ListGraph<VERTEX>::ListGraph(int nSize)
	{
		m_pVertices = new Item [nSize];
		m_nSize = nSize;
		m_nCount = 0;
	}

	template <class VERTEX>
		ListGraph<VERTEX>::~ListGraph()
	{
		delete [] m_pVertices;
	}

	template <class VERTEX>
		long ListGraph<VERTEX>::_FindVertex(const VERTEX& v)
	{
		for (long i = 0; i < m_nCount; i++)
		{
			if (m_pVertices[i].vertex == v) return i;
		}
		return -1;
	}

	template <class VERTEX>
		long ListGraph<VERTEX>::_AddVertex(const VERTEX& v)
	{
		if (m_nCount >= m_nSize)
			return -1;
		m_pVertices[m_nCount].vertex = v;
		return m_nCount++;
	}

	template <class VERTEX>
		bool ListGraph<VERTEX>::AddEdge(const VERTEX& v1, const VERTEX& v2, EDGE w)
	{
		long iv1, iv2;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) iv1 = _AddVertex(v1);
		if (iv1 < 0) return false;

		iv2 = _FindVertex(v2);
		if (iv2 < 0) iv2 = _AddVertex(v2);
		if (iv2 < 0) return false;

		m_pVertices[iv1].list.AddHead(Adj(v2, w));
		m_pVertices[iv2].list.AddHead(Adj(v1, w));

		return true;
	}

	template <class VERTEX>
		bool ListGraph<VERTEX>::AddEdgeDir(const VERTEX& v1, const VERTEX& v2, EDGE w)
	{
		long iv1, iv2;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) iv1 = _AddVertex(v1);
		if (iv1 < 0) return false;

		iv2 = _FindVertex(v2);
		if (iv2 < 0) iv2 = _AddVertex(v2);
		if (iv2 < 0) return false;

		m_pVertices[iv1].list.AddHead(Adj(v2, w));
		return true;
	}

	template <class VERTEX>
		EDGE ListGraph<VERTEX>::GetEdge(const VERTEX& v1, const VERTEX& v2)
	{
		long iv1;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) return 0;
		
		POS pos = m_pVertices[iv1].list.Find(Adj(v2, 0));
		if (pos) {
			return m_pVertices[iv1].list.GetAt(pos).weight;
		} else {
			return 0;
		}
	}

	template <class VERTEX>
		bool ListGraph<VERTEX>::SetEdge(const VERTEX& v1, const VERTEX& v2, EDGE w)
	{
		long iv1;
		iv1 = _FindVertex(v1);
		if (iv1 < 0) return false;
		
		POS pos = m_pVertices[iv1].list.Find(Adj(v2, 0));
		if (pos) {
			m_pVertices[iv1].list.GetAt(pos).weight = w;
			return true;
		} else {
			return false;
		}		
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::DFS()
	{
		bool *visited = new bool [m_nCount];
		for (long i = 0; i < m_nCount; i++) visited[i] = false;
		for (i = 0; i < m_nCount; i++)
			if (!visited[i]) _DFS(i, visited);
		delete [] visited;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::_DFS(long i, bool* visited)
	{
		visited[i] = true;		
		Visit(m_pVertices[i].vertex);

		POS pos = m_pVertices[i].list.GetHeadPosition();
		while (pos) 
		{
			Adj adj = m_pVertices[i].list.GetNext(pos);
			int k = _FindVertex(adj.vertex);
			if (!visited[k]) {
				_DFS(k, visited);
			}
		}
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::DFS_nr()
	{
		long i, j;
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
					j = stack.Pop();
					Visit(m_pVertices[j].vertex);

					POS pos = m_pVertices[j].list.GetHeadPosition();
					while (pos) 
					{
						Adj adj = m_pVertices[j].list.GetNext(pos);
						int k = _FindVertex(adj.vertex);
						if (!visited[k])
						{
							stack.Push(k);
							visited[k] = true;							
						}
					}
				}
			}
		}
		delete [] visited;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::BFS()
	{
		long i, j;
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
					j = queue.Get();
					Visit(m_pVertices[j].vertex);

					POS pos = m_pVertices[j].list.GetHeadPosition();
					while (pos) 
					{
						Adj adj = m_pVertices[j].list.GetNext(pos);
						int k = _FindVertex(adj.vertex);
						if (!visited[k])
						{
							queue.Put(k);
							visited[k] = true;							
						}
					}
				}
			}
		}
		delete [] visited;
	}

	template <class VERTEX>
		long ListGraph<VERTEX>::CountComponents()
	{
		long count = 0;
		long i, j;
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
					j = stack.Pop();
					POS pos = m_pVertices[j].list.GetHeadPosition();
					while (pos) 
					{
						Adj adj = m_pVertices[j].list.GetNext(pos);
						int k = _FindVertex(adj.vertex);
						if (!visited[k])
						{
							stack.Push(k);
							visited[k] = true;
						}
					}
				}
			}
		}
		delete [] visited;

		return count;		
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::FindAP(SimpleList<VERTEX>& aplist)
	{
		// porder는 방문표시겸, 방문순서를 나타낸다. 
		// 방문순서는 1부터 시작하므로, 0이면 방문하지 않은 정점이다. 
		long *porder = new long[m_nCount];
		memset(porder, 0, m_nCount*sizeof(long));
		long son_of_root = 0;

		_FindAP(0, 1, aplist, porder, son_of_root);
		delete [] porder;

		if (son_of_root > 1)
			aplist.AddHead(m_pVertices[0].vertex);		
	}

	template <class VERTEX>
		long ListGraph<VERTEX>::_FindAP(long i, long order, SimpleList<VERTEX>& aplist, long *porder, long& son_of_root)
	{
		long min, m;

		porder[i] = min = ++order;
		
		POS pos = m_pVertices[i].list.GetHeadPosition();
		while (pos)
		{
			Adj adj = m_pVertices[i].list.GetNext(pos);
			int k = _FindVertex(adj.vertex);
			if (porder[k] == 0)  // if Tree Edge
			{
				if (i == 0) son_of_root++;	// root의 자식을 세기. 
				
				m = _FindAP(k, order, aplist, porder, son_of_root);
				if (m < min) min = m;  // 최소값 업데이트 
				if (m >= porder[i] && i != 0)
				{
					// Articulation Points: 중복될 수 있으므로 체크 
					if (!aplist.Find(m_pVertices[i].vertex))
						aplist.AddHead(m_pVertices[i].vertex);
				}
			}
			else	// Non-Tree Edge
			{
				if (porder[k] < min)
					min = porder[k];
			}
		}
		return min;
	}

	template <class VERTEX>
		EDGE ListGraph<VERTEX>::MCST_Pfs()
	{
		long i, j;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		EDGE sum = 0;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;

		for (i = 0; i < m_nCount; i++)
		{
			if (!visited[i])
			{
				pq.Insert(m_pVertices[i].vertex, m_pVertices[i].vertex, 0);
				visited[i] = true;				
				while (!pq.IsEmpty())
				{
					p = pq.Extract();

					if (p.v1 != p.v2) {
						VisitEdge(p.v1, p.v2);
						sum += -p.w;
					}
					j = _FindVertex(p.v2);

					POS pos = m_pVertices[j].list.GetHeadPosition();
					while (pos) 
					{
						Adj adj = m_pVertices[j].list.GetNext(pos);
						int k = _FindVertex(adj.vertex);
						if (!visited[k])
						{   // 방문하지 않은 정점들에 대해서 
							pq.Insert(m_pVertices[j].vertex, adj.vertex, -adj.weight);
							visited[k] = true;
						}
						else 
						{	// 방문한 정점들에 대해서. 
							pq.Update(m_pVertices[j].vertex, adj.vertex, -adj.weight);
						}
					}
				}
			}
		}
		delete [] visited;
		return sum;
	}

	template <class VERTEX>
	EDGE ListGraph<VERTEX>::MCST_Kruskal()
	{
		EdgeHeap<char> pq;
		Set<char> set;
		int i;
		EDGE sum = 0;
		int nEdge = 0;

		// insert all edges to heap
		for (i = 0; i < m_nCount; i++) {
			POS pos = m_pVertices[i].list.GetHeadPosition();
			while (pos) {
				Adj adj = m_pVertices[i].list.GetNext(pos);
				if (_FindVertex(adj.vertex) > i)	// 간선의 중복을 피하기 위해 
					pq.Insert(m_pVertices[i].vertex, adj.vertex, -adj.weight);
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
		void ListGraph<VERTEX>::ShortestPath_Pfs(const VERTEX& start)
	{
		long i, j;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;

		i = _FindVertex(start);
		if (i < 0) return;
		
		// Shortest Path는 연결된 요소에서만 가능하다. 그래서 최상위루프는 빠진다. 
		pq.Insert(m_pVertices[i].vertex, m_pVertices[i].vertex, 0);
		visited[i] = true;			
		while (!pq.IsEmpty())
		{
			p = pq.Extract();
			
			if (p.v1 != p.v2) {
				VisitEdge(p.v1, p.v2);
			}
			j = _FindVertex(p.v2);
			
			POS pos = m_pVertices[j].list.GetHeadPosition();
			while (pos) 
			{
				Adj adj = m_pVertices[j].list.GetNext(pos);
				int k = _FindVertex(adj.vertex);
				if (!visited[k])
				{   // 방문하지 않은 정점들에 대해서 
					pq.Insert(m_pVertices[j].vertex, adj.vertex, p.w - adj.weight);
					visited[k] = true;						
				}
				else 
				{	// 방문한 정점들에 대해서. 
					pq.Update(m_pVertices[j].vertex, adj.vertex, p.w - adj.weight);
				}
			}

		}
		delete [] visited;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::ShortestPath_Dijkstra(const VERTEX& start)
	{
		long i;
		long x, y;
		long count = 0;
		long s = _FindVertex(start);
		EDGE *distance = new EDGE [m_nCount]; // start로부터의 거리를 저장 
		bool *visited = new bool [m_nCount];
		int *parent = new int [m_nCount];

		for (i = 0; i < m_nCount; i++) {
			visited[i] = false;
			distance[i] = 0;		// 0 means Infinite
			if (i != s) parent[i] = s;
			else parent[i] = -1;
		}

		// fill distance array
		POS pos = m_pVertices[s].list.GetHeadPosition();
		while (pos) {
			Adj adj = m_pVertices[s].list.GetNext(pos);
			distance[_FindVertex(adj.vertex)] = adj.weight;
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

			pos = m_pVertices[x].list.GetHeadPosition();
			while (pos) {
				Adj adj = m_pVertices[x].list.GetNext(pos);
				y = _FindVertex(adj.vertex);
				if (visited[y]) continue;
				EDGE d = distance[x] + adj.weight;	// 우회경로 
				if (distance[y] == 0 || d < distance[y]) {
					distance[y] = d;
					parent[y] = x;
				}
			}
		}

		// visit edge
		for (i = 0; i < m_nCount; i++) {
			if (parent[i] >= 0) VisitEdge(m_pVertices[parent[i]].vertex, m_pVertices[i].vertex);
		}

		delete [] distance;
		delete [] visited;
		delete [] parent;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::Reach_Dfs(const VERTEX& start)
	{
		long i, j;
		ListStack<long> stack;
		bool *visited = new bool [m_nCount];
		for (i = 0; i < m_nCount; i++) visited[i] = false;

		i = _FindVertex(start);
		if (i < 0) return;

		stack.Push(i);
		visited[i] = true;				
		while (!stack.IsEmpty())
		{
			j = stack.Pop();
			Visit(m_pVertices[j].vertex);
			
			POS pos = m_pVertices[j].list.GetHeadPosition();
			while (pos) 
			{
				Adj adj = m_pVertices[j].list.GetNext(pos);
				int k = _FindVertex(adj.vertex);
				if (!visited[k])
				{
					stack.Push(k);
					visited[k] = true;							
				}
			}
		}
		delete [] visited;		
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::StrongConnect()
	{
		int i;
		ListStack<long> stack;
		long *porder = new long [m_nCount];

		for (i = 0; i < m_nCount; i++) {
			porder[i] = 0;
		}
		for (i = 0; i < m_nCount; i++) {
			if (porder[i] == 0)	_StrongConnect(i, 0, porder, stack);
		}

		delete [] porder;
	}

	template <class VERTEX>
		int ListGraph<VERTEX>::_StrongConnect(long i, long order, long* porder, ListStack<long>& stack)
	{
		int m, min;
		int k;
		bool cycle;

		porder[i] = min = ++order;
		stack.Push(i);

		POS pos = m_pVertices[i].list.GetHeadPosition();
		while (pos) {
			Adj adj = m_pVertices[i].list.GetNext(pos);
			k = _FindVertex(adj.vertex);
			if (porder[k] == 0)	// 방문하지 않은 정점이면
				m = _StrongConnect(k, order, porder, stack);
			else
				m = porder[k];
			if (m < min) min = m;
		}
		if (min == porder[i])	// 자기자신을 가리키면 
		{
			cycle = false;
			while ((k = stack.Pop()) != i) {
				Visit(m_pVertices[k].vertex);
				porder[k] = m_nCount + 1;	// 다시는 출력되지 않도록 체크 
				cycle = true;
			}
			if (cycle) Visit(m_pVertices[k].vertex);
			// 여기까지가 한묶음 
		}
		return min;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::TopologicalSort()
	{
		int i;
		ListQueue<int> queue;
		// indegree 배열 설정
		
		int *indegree = new int [m_nCount];
		for (i = 0; i < m_nCount; i++) indegree[i] = 0;

		for (i = 0; i < m_nCount; i++) {
			POS pos = m_pVertices[i].list.GetHeadPosition();
			while (pos) {
				Adj adj = m_pVertices[i].list.GetNext(pos);
				int k = _FindVertex(adj.vertex);
				indegree[k]++;
			}
		}

		for (i = 0; i < m_nCount; i++) {
			if (indegree[i] == 0) queue.Put(i);
		}

		for (i = 0; i < m_nCount && !queue.IsEmpty(); i++) {
			// queue가  비면 DAG가 아니다. (순환이 있음)
			int j = queue.Get();
			Visit(m_pVertices[j].vertex);
			POS pos = m_pVertices[j].list.GetHeadPosition();
			while (pos) {
				Adj adj = m_pVertices[j].list.GetNext(pos);
				int k = _FindVertex(adj.vertex);
				indegree[k]--;
				if (indegree[k] == 0) queue.Put(k);
			}
		}
		delete [] indegree;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::RevTopologicalSort()
	{
		int i;
		ListQueue<int> queue;
		// indegree 배열 설정
		
		int *outdegree = new int [m_nCount];
		for (i = 0; i < m_nCount; i++) outdegree[i] = 0;

		for (i = 0; i < m_nCount; i++) {
			outdegree[i] = m_pVertices[i].list.GetCount();
		}

		for (i = 0; i < m_nCount; i++) {
			if (outdegree[i] == 0) queue.Put(i);
		}

		for (i = 0; i < m_nCount && !queue.IsEmpty(); i++) {
			// queue가  비면 DAG가 아니다. (순환이 있음)
			int j = queue.Get();
			Visit(m_pVertices[j].vertex);

			for (int k = 0; k < m_nCount; k++) {
				POS pos = m_pVertices[k].list.GetHeadPosition();
				while (pos) {
					Adj adj = m_pVertices[k].list.GetNext(pos);
					if (adj.vertex == m_pVertices[j].vertex) {
						outdegree[k]--;
						if (outdegree[k] == 0) queue.Put(k);
					}
				}
			}
		}
		delete [] outdegree;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::CriticalActivity()
	{
		int *earliest = new int [m_nCount];
		int *latest = new int [m_nCount];

		_CriticalActivity_forward(earliest);
		int initial = 0;
		for (int i = 0; i < m_nCount; i++) {
			if (initial < earliest[i]) initial = earliest[i];
		}

		_CriticalActivity_backward(latest, initial);
/*
		for (i = 0; i < m_nCount; i++) {
			printf("%c %2d %2d\n", m_pVertices[i].vertex, earliest[i], latest[i]);
		}*/

		for (i = 0; i < m_nCount; i++) {
			POS pos = m_pVertices[i].list.GetHeadPosition();
			while (pos) {
				Adj adj = m_pVertices[i].list.GetNext(pos);
				int e = earliest[i];
				int l = latest[_FindVertex(adj.vertex)] - adj.weight;
				if (l == e && adj.weight > 0) 
					VisitEdge(m_pVertices[i].vertex, adj.vertex);
			}
		}

		delete [] earliest;
		delete [] latest;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::_CriticalActivity_forward(int *earliest)
	{
		int i;
		ListQueue<int> queue;
		// indegree 배열 설정
		
		int *indegree = new int [m_nCount];
		for (i = 0; i < m_nCount; i++) {
			indegree[i] = 0;
			earliest[i] = 0;
		}

		for (i = 0; i < m_nCount; i++) {
			POS pos = m_pVertices[i].list.GetHeadPosition();
			while (pos) {
				Adj adj = m_pVertices[i].list.GetNext(pos);
				int k = _FindVertex(adj.vertex);
				indegree[k]++;
			}
		}

		for (i = 0; i < m_nCount; i++) {
			if (indegree[i] == 0) queue.Put(i);
		}

		for (i = 0; i < m_nCount && !queue.IsEmpty(); i++) {
			// queue가  비면 DAG가 아니다. (순환이 있음)
			int j = queue.Get();
//			Visit(m_pVertices[j].vertex);
			POS pos = m_pVertices[j].list.GetHeadPosition();
			while (pos) {
				Adj adj = m_pVertices[j].list.GetNext(pos);
				int k = _FindVertex(adj.vertex);
				indegree[k]--;
				if (indegree[k] == 0) queue.Put(k);
				if (earliest[k] < earliest[j] + adj.weight)
					earliest[k] = earliest[j] + adj.weight;
			}
		}
		delete [] indegree;
	}

	template <class VERTEX>
		void ListGraph<VERTEX>::_CriticalActivity_backward(int *latest, int initial)
	{
		int i;
		ListQueue<int> queue;
		// indegree 배열 설정
		
		int *outdegree = new int [m_nCount];
		for (i = 0; i < m_nCount; i++) {
			outdegree[i] = 0;
			latest[i] = initial;
		}

		for (i = 0; i < m_nCount; i++) {
			outdegree[i] = m_pVertices[i].list.GetCount();
		}

		for (i = 0; i < m_nCount; i++) {
			if (outdegree[i] == 0) queue.Put(i);
		}

		for (i = 0; i < m_nCount && !queue.IsEmpty(); i++) {
			// queue가  비면 DAG가 아니다. (순환이 있음)
			int j = queue.Get();
//			Visit(m_pVertices[j].vertex);

			for (int k = 0; k < m_nCount; k++) {
				POS pos = m_pVertices[k].list.GetHeadPosition();
				while (pos) {
					Adj adj = m_pVertices[k].list.GetNext(pos);
					if (adj.vertex == m_pVertices[j].vertex) {
						outdegree[k]--;
						if (outdegree[k] == 0) queue.Put(k);
						if (latest[k] > latest[j] - adj.weight)
							latest[k] = latest[j] - adj.weight;
					}
				}
			}
		}
		delete [] outdegree;
	}

};

#endif