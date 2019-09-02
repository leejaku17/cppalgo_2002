#include "../Search/ArraySeqMap.h"
#include "../Search/ListSeqMap.h"
#include "../Search/BinMap.h"
#include "../Search/ItpMap.h"
#include "../Search/HashMap.h"
#include "../Search/ChainMap.h"
#include "../Search/RadixTreeMap.h"
#include "../Search/RadixTrieMap.h"
#include "../Search/BTreeMap.h"
#include "../Search/RBTreeMap.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>

using namespace cppalgo;

#define FINDTESTNUM  1000
#define FAST_TEST	10000

void TimeForArraySeqMap(int n)
{
	ArraySeqMap<int> map(n);
	DWORD dwTime;
	int v;
	int i;

	printf("Test for ArraySeqMap (%d items)\n", n);

	// Insert Test
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (map.Find(n, v))
			printf("Error in find\n");
	}
	printf("\tFind %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (!map.Remove(i))
			printf("Error in remove\n");
	}
	printf("\tRemove %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);
}

void TimeForListSeqMap(int n)
{
	ListSeqMap<int> map;
	DWORD dwTime;
	int v;
	int i;

	printf("Test for ListSeqMap (%d items)\n", n);

	// Insert Test
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (map.Find(n, v))
			printf("Error in find\n");
	}
	printf("\tFind %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (!map.Remove(i))
			printf("Error in remove\n");
	}
	printf("\tRemove %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);
}

void TimeForBinMap(int n)
{
	BinMap<int> map(n);
	DWORD dwTime;
	int v;
	int i;

	printf("Test for BinMap (%d items)\n", n);

	// Insert Test  : 역순으로 집어넣음 최악...
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(n-i-1))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();
	
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (map.Find(n, v))
			printf("Error in find\n");
	}
	/*
	for (i = 0; i < n; i++)
	{
		if (!map.Find(i, v))
			printf("Error in find (%d)\n", i);
	}*/

	printf("\tFind %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (!map.Remove(i))
			printf("Error in remove\n");
	}
	printf("\tRemove %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);
}

void TimeForItpMap(int n)
{
	ItpMap<int> map(n);
	DWORD dwTime;
	int v;
	int i;

	printf("Test for ItpMap (%d items)\n", n);

	// Insert Test  : 역순으로 집어넣음 최악...
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(n-i-1))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	
	dwTime = GetTickCount();
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (map.Find(n, v))
			printf("Error in find\n");
	}
	/*
	for (i = 0; i < n; i++)
	{
		if (!map.Find(i, v))
			printf("Error in find (%d)\n", i);
	}*/
	printf("\tFind %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FINDTESTNUM; i++)
	{
		if (!map.Remove(i))
			printf("Error in remove\n");
	}
	printf("\tRemove %d items in %dmsec\n", FINDTESTNUM, GetTickCount() - dwTime);
}

struct IntHash {
	int hash(int i) const { return i; }
};

void TimeForHashMap(int n)
{
	HashMap<int, IntHash> map(IntHash(), n*2);   // N*2의 해쉬크기를 잡음 .
	DWORD dwTime;
	int v;
	int i;

	printf("Test for HashMap (%d items)\n", n);

	// Insert Test 
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();
	
	for (i = 0; i < FAST_TEST; i++)
	{	
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		if (!map.Find(t, v))
			printf("Error in find (%d)\n", t);
	}
	
	printf("\tFind %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		map.Remove(t);			
	}
	printf("\tRemove %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);
}

void TimeForChainMap(int n)
{
	ChainMap<int, IntHash> map(IntHash(), n/2);   // N/2의 해쉬크기를 잡음 .
	DWORD dwTime;
	int v;
	int i;

	printf("Test for ChainMap (%d items)\n", n);

	// Insert Test  : 역순으로 집어넣음 최악...
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();
	
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		if (!map.Find(t, v))
			printf("Error in find\n");
	}
	
	printf("\tFind %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		map.Remove(t);			
	}
	printf("\tRemove %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);
}

void TimeForRadixTreeMap(int n)
{
	RadixTreeMap<int> map;
	DWORD dwTime;
	int v;
	int i;

	printf("Test for RadixTreeMap (%d items)\n", n);

	// Insert Test  : 역순으로 집어넣음 최악...
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();

	for (i = 0; i < n; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		if (!map.Find(t, v))
			printf("Error in find (%d)\n", i);
	}

	printf("\tFind %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		map.Remove(t);			
	}
	printf("\tRemove %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);
}

void TimeForRadixTrieMap(int n)
{
	RadixTrieMap<int> map;
	DWORD dwTime;
	int v;
	int i;

	printf("Test for RadixTrieMap (%d items)\n", n);

	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);
	
	dwTime = GetTickCount();

	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		if (!map.Find(t, v))
			printf("Error in find\n");
	}
	printf("\tFind %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	dwTime = GetTickCount();
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		map.Remove(t);			
	}
	printf("\tRemove %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);
}

void TimeForBTreeMap(int n)
{
	BTreeMap<int> map(5);
	DWORD dwTime;
	int v;
	int i;

	printf("Test for BTreeMap (%d items)\n", n);

	// Insert Test  : 역순으로 집어넣음 최악...
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();
	
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		if (!map.Find(t, v))
			printf("Error in find\n");
	}
	
	printf("\tFind %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	
	dwTime = GetTickCount();
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		map.Remove(t);			
	}
	printf("\tRemove %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);
	
}

void TimeForRBTreeMap(int n)
{
	RBTreeMap<int> map;
	DWORD dwTime;
	int v;
	int i;

	printf("Test for RBTreeMap (%d items)\n", n);

	// Insert Test  : 역순으로 집어넣음 최악...
	dwTime = GetTickCount();
	for (i = 0; i < n; i++)
	{
		if (!map.Insert(i))
			printf("Error in insert\n");
	}
	printf("\tInsert %d items in %dmsec\n", n, GetTickCount() - dwTime);

	// Find Test  (없는 값 찾기 : 최악의 경우)
	dwTime = GetTickCount();

	for (i = 0; i < n; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		if (!map.Find(t, v))
			printf("Error in find (%d)\n", i);
	}

	printf("\tFind %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);

	// Remove Test  (제일 앞의 값 삭제하기, find는 최소화하고 Remove가 힘들게)
	
	dwTime = GetTickCount();
	for (i = 0; i < FAST_TEST; i++)
	{
		int t = int((double)rand() / (double)RAND_MAX * (n-1));
		map.Remove(t);
	}
	printf("\tRemove %d items in %dmsec\n", FAST_TEST, GetTickCount() - dwTime);
}

void main(void)
{
	bool DoArraySeqMap = false;
	bool DoListSeqMap = false;
	bool DoBinMap = false;
	bool DoItpMap = false;
	bool DoHashMap = true;
	bool DoRadixMap = true;
	bool DoBalancedTree = true;
	srand( (unsigned)time( NULL ) );

	if (DoArraySeqMap)
	{
		TimeForArraySeqMap(10000);
		TimeForArraySeqMap(20000);
		TimeForArraySeqMap(30000);
		TimeForArraySeqMap(40000);
		TimeForArraySeqMap(50000);
		TimeForArraySeqMap(60000);
		TimeForArraySeqMap(70000);
		TimeForArraySeqMap(80000);
		TimeForArraySeqMap(90000);
		TimeForArraySeqMap(100000);
	}

	if (DoListSeqMap)
	{
		TimeForListSeqMap(10000);
		TimeForListSeqMap(20000);
		TimeForListSeqMap(30000);
		TimeForListSeqMap(40000);
		TimeForListSeqMap(50000);
		TimeForListSeqMap(60000);
		TimeForListSeqMap(70000);
		TimeForListSeqMap(80000);
		TimeForListSeqMap(90000);
		TimeForListSeqMap(100000);
	}

	if (DoBinMap)
	{
		TimeForBinMap(10000);
		TimeForBinMap(20000);
		TimeForBinMap(30000);
		TimeForBinMap(40000);
		TimeForBinMap(50000);
		TimeForBinMap(60000);
		TimeForBinMap(70000);
		TimeForBinMap(80000);
		TimeForBinMap(90000);
		TimeForBinMap(100000);
	}

	if (DoItpMap)
	{
		TimeForItpMap(10000);
		TimeForItpMap(20000);
		TimeForItpMap(30000);
		TimeForItpMap(40000);
		TimeForItpMap(50000);
		TimeForItpMap(60000);
		TimeForItpMap(70000);
		TimeForItpMap(80000);
		TimeForItpMap(90000);
		TimeForItpMap(100000);
	}

	if (DoHashMap)
	{
		TimeForHashMap(10000);
		TimeForHashMap(20000);
		TimeForHashMap(30000);
		TimeForHashMap(40000);
		TimeForHashMap(50000);
		TimeForHashMap(60000);
		TimeForHashMap(70000);
		TimeForHashMap(80000);
		TimeForHashMap(90000);
		TimeForHashMap(100000);

		TimeForChainMap(10000);
		TimeForChainMap(20000);
		TimeForChainMap(30000);
		TimeForChainMap(40000);
		TimeForChainMap(50000);
		TimeForChainMap(60000);
		TimeForChainMap(70000);
		TimeForChainMap(80000);
		TimeForChainMap(90000);
		TimeForChainMap(100000);
	}
	if (DoRadixMap)
	{
		TimeForRadixTreeMap(10000);
		TimeForRadixTreeMap(20000);
		TimeForRadixTreeMap(30000);
		TimeForRadixTreeMap(40000);
		TimeForRadixTreeMap(50000);
		TimeForRadixTreeMap(60000);
		TimeForRadixTreeMap(70000);
		TimeForRadixTreeMap(80000);
		TimeForRadixTreeMap(90000);
		TimeForRadixTreeMap(100000);

		TimeForRadixTrieMap(10000);
		TimeForRadixTrieMap(20000);
		TimeForRadixTrieMap(30000);
		TimeForRadixTrieMap(40000);
		TimeForRadixTrieMap(50000);
		TimeForRadixTrieMap(60000);
		TimeForRadixTrieMap(70000);
		TimeForRadixTrieMap(80000);
		TimeForRadixTrieMap(90000);
		TimeForRadixTrieMap(100000);
	}

	if (DoBalancedTree)
	{
		TimeForBTreeMap(10000);
		TimeForBTreeMap(20000);
		TimeForBTreeMap(30000);
		TimeForBTreeMap(40000);
		TimeForBTreeMap(50000);
		TimeForBTreeMap(60000);
		TimeForBTreeMap(70000);
		TimeForBTreeMap(80000);
		TimeForBTreeMap(90000);
		TimeForBTreeMap(100000);
		
	
		TimeForRBTreeMap(10000);
		TimeForRBTreeMap(20000);
		TimeForRBTreeMap(30000);
		TimeForRBTreeMap(40000);
		TimeForRBTreeMap(50000);
		TimeForRBTreeMap(60000);
		TimeForRBTreeMap(70000);
		TimeForRBTreeMap(80000);
		TimeForRBTreeMap(90000);
		TimeForRBTreeMap(100000);
	}
}
