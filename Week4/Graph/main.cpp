#include "ArrayGraph.h"
#include "ListGraph.h"
#include "Set.h"
#include <stdio.h>

using namespace cppalgo;

template ArrayGraph<char>;
template ListGraph<char>;
template EdgeHeap<char>;
template Set<char>;

class ACharGraph : public ArrayGraph<char>
{
public:
	ACharGraph(int nSize = 100) : ArrayGraph<char>(nSize) {}
	void Visit(const char& v) { printf("%c", v); }
	void VisitEdge(const char& v1, const char& v2) { printf("%c%c ", v1, v2); }
};

class LCharGraph : public ListGraph<char>
{
public:
	LCharGraph(int nSize = 100) : ListGraph<char>(nSize) {}
	void Visit(const char& v) { printf("%c", v); }
	void VisitEdge(const char& v1, const char& v2) { printf("%c%c ", v1, v2); }
};

void AG_Search()
{
	printf("ArrayGraph Test\n");
	ACharGraph ag;
	ag.AddEdge('A', 'B', 1);
	ag.AddEdge('A', 'C', 1);
	ag.AddEdge('A', 'D', 1);
	ag.AddEdge('B', 'E', 1);
	ag.AddEdge('C', 'F', 1);
	ag.AddEdge('D', 'H', 1);
	ag.AddEdge('E', 'F', 1);
	ag.AddEdge('F', 'H', 1);
	ag.AddEdge('E', 'G', 1);
	ag.AddEdge('G', 'I', 1);
	ag.AddEdge('H', 'I', 1);
	ag.AddEdge('J', 'K', 1);
	ag.AddEdge('J', 'L', 1);
	ag.AddEdge('M', 'N', 1);
	ag.AddEdge('M', 'O', 1);
	ag.AddEdge('N', 'P', 1);
	ag.AddEdge('N', 'Q', 1);
	ag.AddEdge('O', 'Q', 1);

	printf("Depth First Search = ");
	ag.DFS();
	printf("\n");

	printf("Depth First Search (nr) = ");
	ag.DFS_nr();
	printf("\n");

	printf("Breadth First Search = ");
	ag.BFS();
	printf("\n");

	printf("Count of Connected Components = %d\n", ag.CountComponents());

	ag.AddEdge('D', 'J', 1);
	ag.AddEdge('J', 'M', 1);
	printf("Articulation Point is ");
	SimpleList<char> aplist;
	ag.FindAP(aplist);
	
	POS pos = aplist.GetHeadPosition();
	while (pos) 
		printf("%c", aplist.GetNext(pos));
	printf("\n");
}

void LG_Search()
{
	printf("ListGraph Test\n");
	LCharGraph lg;
	lg.AddEdge('A', 'B', 1);
	lg.AddEdge('A', 'C', 1);
	lg.AddEdge('A', 'D', 1);
	lg.AddEdge('B', 'E', 1);
	lg.AddEdge('C', 'F', 1);
	lg.AddEdge('D', 'H', 1);
	lg.AddEdge('E', 'F', 1);
	lg.AddEdge('F', 'H', 1);
	lg.AddEdge('E', 'G', 1);
	lg.AddEdge('G', 'I', 1);
	lg.AddEdge('H', 'I', 1);
	lg.AddEdge('J', 'K', 1);
	lg.AddEdge('J', 'L', 1);
	lg.AddEdge('M', 'N', 1);
	lg.AddEdge('M', 'O', 1);
	lg.AddEdge('N', 'P', 1);
	lg.AddEdge('N', 'Q', 1);
	lg.AddEdge('O', 'Q', 1);

	printf("Depth First Search = ");
	lg.DFS();
	printf("\n");

	printf("Depth First Search (nr) = ");
	lg.DFS_nr();
	printf("\n");

	printf("Breadth First Search = ");
	lg.BFS();
	printf("\n");

	printf("Count of Connected Components = %d\n", lg.CountComponents());

	lg.AddEdge('D', 'J', 1);
	lg.AddEdge('J', 'M', 1);
	printf("Articulation Point is ");
	SimpleList<char> aplist;
	lg.FindAP(aplist);
	
	POS pos = aplist.GetHeadPosition();
	while (pos) 
		printf("%c", aplist.GetNext(pos));
	printf("\n");
}

void LG_Weighted()
{
	printf("Weighted ListGraph\n");
	LCharGraph lg;
	lg.AddEdge('A', 'B', 4);
	lg.AddEdge('A', 'C', 1);
	lg.AddEdge('A', 'D', 2);
	lg.AddEdge('A', 'E', 3);
	lg.AddEdge('B', 'F', 4);
	lg.AddEdge('C', 'D', 2);
	lg.AddEdge('D', 'F', 4);
	lg.AddEdge('D', 'G', 4);
	lg.AddEdge('E', 'F', 4);
	lg.AddEdge('F', 'J', 2);
	lg.AddEdge('F', 'K', 4);
	lg.AddEdge('G', 'H', 3);
	lg.AddEdge('G', 'I', 3);
	lg.AddEdge('G', 'J', 4);
	lg.AddEdge('H', 'I', 2);
	lg.AddEdge('I', 'J', 2);
	lg.AddEdge('J', 'K', 1);

	printf("MCST: Priority First Search = ");
	EDGE w = lg.MCST_Pfs();
	printf("  (%d)\n", w);

	printf("MCST: Kruskal Algorithm = ");
	w = lg.MCST_Kruskal();
	printf("  (%d)\n", w);

	printf("Shortest Path: Priority First Search = ");
	lg.ShortestPath_Pfs('A');
	printf("\n");

	printf("Shortest Path: Dijkstra = ");
	lg.ShortestPath_Dijkstra('A');
	printf("\n");

}

void AG_Weighted()
{
	printf("Weighted ArrayGraph\n");
	ACharGraph ag;
	ag.AddEdge('A', 'B', 4);
	ag.AddEdge('A', 'C', 1);
	ag.AddEdge('A', 'D', 2);
	ag.AddEdge('A', 'E', 3);
	ag.AddEdge('B', 'F', 4);
	ag.AddEdge('C', 'D', 2);
	ag.AddEdge('D', 'F', 4);
	ag.AddEdge('D', 'G', 4);
	ag.AddEdge('E', 'F', 4);
	ag.AddEdge('F', 'J', 2);
	ag.AddEdge('F', 'K', 4);
	ag.AddEdge('G', 'H', 3);
	ag.AddEdge('G', 'I', 3);
	ag.AddEdge('G', 'J', 4);
	ag.AddEdge('H', 'I', 2);
	ag.AddEdge('I', 'J', 2);
	ag.AddEdge('J', 'K', 1);

	printf("Priority First Search = ");
	EDGE w = ag.MCST_Pfs();
	printf("  (%d)\n", w);

	printf("Kruskal Algorithm = ");
	w = ag.MCST_Kruskal();
	printf("  (%d)\n", w);

	printf("Shortest Path: Priority First Search = ");
	ag.ShortestPath_Pfs('A');
	printf("\n");

	printf("Shortest Path: Dijkstra = ");
	ag.ShortestPath_Dijkstra('A');
	printf("\n");
}

void LG_Directed()
{
	printf("Directed ListGraph\n");
	LCharGraph lg;
	lg.AddEdgeDir('A', 'B', 1);
	lg.AddEdgeDir('A', 'C', 1);
	lg.AddEdgeDir('A', 'D', 1);
	lg.AddEdgeDir('D', 'C', 1);
	lg.AddEdgeDir('D', 'F', 1);
	lg.AddEdgeDir('E', 'A', 1);
	lg.AddEdgeDir('F', 'B', 1);
	lg.AddEdgeDir('F', 'D', 1);
	lg.AddEdgeDir('F', 'E', 1);
	lg.AddEdgeDir('G', 'D', 1);
	lg.AddEdgeDir('G', 'J', 1);
	lg.AddEdgeDir('H', 'G', 1);
	lg.AddEdgeDir('H', 'I', 1);
	lg.AddEdgeDir('I', 'G', 1);
	lg.AddEdgeDir('J', 'I', 1);
	lg.AddEdgeDir('J', 'F', 1);
	lg.AddEdgeDir('J', 'K', 1);
	lg.AddEdgeDir('K', 'F', 1);

	printf("Reachability by DFS: \n");

	for (char i = 'A'; i <= 'K'; i++) {
		printf("\t%c = ", i);
		lg.Reach_Dfs(i);
		printf("\n");
	}

	printf("Strong Connected : ");
	lg.StrongConnect();
	printf("\n");

	LCharGraph lg2;
	lg2.AddEdgeDir('A', 'B', 1);
	lg2.AddEdgeDir('B', 'C', 1);
	lg2.AddEdgeDir('C', 'D', 1);
	lg2.AddEdgeDir('C', 'E', 1);
	lg2.AddEdgeDir('C', 'F', 1);
	lg2.AddEdgeDir('C', 'G', 1);
	lg2.AddEdgeDir('E', 'K', 1);
	lg2.AddEdgeDir('F', 'H', 1);
	lg2.AddEdgeDir('F', 'I', 1);
	lg2.AddEdgeDir('F', 'J', 1);
	lg2.AddEdgeDir('H', 'K', 1);
	lg2.AddEdgeDir('I', 'K', 1);
	lg2.AddEdgeDir('J', 'K', 1);
	lg2.AddEdgeDir('K', 'L', 1);

	printf("Topological Sort : ");
	lg2.TopologicalSort();
	printf("\n");

	printf("Reverse Topological Sort : ");
	lg2.RevTopologicalSort();
	printf("\n");
	
	LCharGraph lg3;
	lg3.AddEdgeDir('A', 'B', 10);
	lg3.AddEdgeDir('B', 'C', 3);
	lg3.AddEdgeDir('C', 'D', 12);
	lg3.AddEdgeDir('D', 'E', 6);
	lg3.AddEdgeDir('D', 'F', 0);
	lg3.AddEdgeDir('D', 'J', 0);
	lg3.AddEdgeDir('D', 'K', 2);
	lg3.AddEdgeDir('F', 'M', 3);
	lg3.AddEdgeDir('K', 'L', 7);
	lg3.AddEdgeDir('L', 'M', 2);
	lg3.AddEdgeDir('E', 'G', 2);
	lg3.AddEdgeDir('E', 'H', 0);
	lg3.AddEdgeDir('E', 'I', 0);
	lg3.AddEdgeDir('J', 'M', 7);
	lg3.AddEdgeDir('G', 'K', 4);
	lg3.AddEdgeDir('H', 'K', 5);
	lg3.AddEdgeDir('I', 'K', 8);

	printf("Critical Activity : ");
	lg3.CriticalActivity();
	printf("\n");
}

void AG_Directed()
{

}

void main(void)
{
	AG_Search();
	LG_Search();
	LG_Weighted();
	AG_Weighted();

	LG_Directed();
	AG_Directed();
}