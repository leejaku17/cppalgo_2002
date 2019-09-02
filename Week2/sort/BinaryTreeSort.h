#ifndef _BinaryTreeSort_h
#define _BinaryTreeSort_h

#include "../Search/BinTreeMap.h"

namespace cppalgo
{
template <class TYPE>
void BinaryTreeSort(TYPE a[], int n)
{
	BinTreeMap<TYPE> bintree;
	
	// 먼저 데이타를 삽입한다. 
	for (int i = 0; i < n; i++)
		bintree.Insert(a[i]);

	// 정렬 
	bintree.Sort(a, n);
}
};

#endif