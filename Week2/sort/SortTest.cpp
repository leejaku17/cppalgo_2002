#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "ShellSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "RadixSort.h"
#include "BinaryTreeSort.h"

int arrayRandom[32000];
int arraySorted[32000];
int arrayReverse[32000];
int arrayCopy[32000];

#define MODE_RANDOM  0
#define MODE_SORTED    1
#define MODE_REVERSE   2

#define LOOP	30

void GenerateArray()
{
	//RAND_MAX = 32767
	srand((unsigned)time(0));
	for (int i = 0; i < sizeof(arrayRandom)/sizeof(int); i++)
		arrayRandom[i] = rand();
	for (i = 0; i < sizeof(arraySorted)/sizeof(int); i++)
		arraySorted[i] = i;
	for (i = 0; i < sizeof(arrayReverse)/sizeof(int); i++)
		arrayReverse[i] = sizeof(arrayReverse)/sizeof(int) - i;
}

void CopyArray(int d[], int s[], int n)
{
	memcpy(d, s, n*sizeof(int));
}

bool IsValid(int a[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i+1])
			return false;
	}
	return true;
}

void TimeForSelectionSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	// 1000, 2000, 4000, 8000, 16000, 32000
	CopyArray(arrayCopy, a, n);

	unsigned dwStart = GetTickCount();
	cppalgo::SelectionSort(arrayCopy, n);
	unsigned dwTime = GetTickCount() - dwStart;

	printf("SelectionSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForInsertionSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	// 1000, 2000, 4000, 8000, 16000, 32000
	CopyArray(arrayCopy, a, n);

	unsigned dwStart = GetTickCount();
	cppalgo::InsertionSort(arrayCopy, n);
	unsigned dwTime = GetTickCount() - dwStart;

	printf("InsertionSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForBubbleSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	// 1000, 2000, 4000, 8000, 16000, 32000
	CopyArray(arrayCopy, a, n);

	unsigned dwStart = GetTickCount();
	cppalgo::BubbleSort(arrayCopy, n);
	unsigned dwTime = GetTickCount() - dwStart;

	printf("BubbleSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForShellSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++)
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		unsigned dwStart = GetTickCount();
		cppalgo::ShellSort(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("ShellSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForShellSort_3h(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++)
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		unsigned dwStart = GetTickCount();
		cppalgo::ShellSort_3h(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("ShellSort_3h(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForQuickSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::QuickSort(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("QuickSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForQuickSortNR(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::QuickSort_nr(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("QuickSortNR(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForQuickSortNR2(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::QuickSort_nr2(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("QuickSortNR2(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForQuickSortRandom(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::QuickSort_random(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("QuickSortRandom(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForQuickSortMedian(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::QuickSort_median(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("QuickSortMedian(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForQuickSortSub(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::QuickSort_sub(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("QuickSortSub(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

int intcmp(const void* a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

void TimeForQsort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		qsort(arrayCopy, n, sizeof(int), intcmp);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("Qsort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForHeapSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::HeapSort(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("HeapSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForHeapSort_up(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::HeapSort_up(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("HeapSort_up(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForMergeSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::MergeSort(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("MergeSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForMergeSort_ex(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::MergeSort_ex(arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("MergeSort_ex(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForRadixExchangeSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::RadixExchangeSort((unsigned long*)arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("RadixExchangeSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForRadixExchangeSort_nr(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::RadixExchangeSort_nr((unsigned long*)arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("RadixExchangeSort_nr(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForStraightRadixSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::StraightRadixSort((unsigned long*)arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("StraightRadixSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void TimeForBinaryTreeSort(int n, int mode)
{
	int *a;
	char szName[16];
	if (mode == MODE_RANDOM) {
		a = arrayRandom;
		strcpy(szName, "Random");
	} else if (mode == MODE_SORTED) {
		a = arraySorted;
		strcpy(szName, "Sorted");
	} else if (mode == MODE_REVERSE) {
		a = arrayReverse;
		strcpy(szName, "Reverse");
	}

	unsigned dwTime = 0;

	for (int i = 0; i < LOOP; i++) 
	{
		// 1000, 2000, 4000, 8000, 16000, 32000
		CopyArray(arrayCopy, a, n);
		
		unsigned dwStart = GetTickCount();
		cppalgo::BinaryTreeSort((unsigned long*)arrayCopy, n);
		dwTime += GetTickCount() - dwStart;
	}

	dwTime /= LOOP;

	printf("BinaryTreeSort(%s %d) : %dmsec %s\n", szName, n, dwTime, IsValid(arrayCopy, n) ? "" : "Error");
}

void main(void)
{
	bool DoElementarySort = false;
	bool DoQuickSort = false;
	bool DoHeapSort = false;
	bool DoShellSort = false;
	bool DoMergeSort = false;
	bool DoRadixSort = false;
	bool DoBinaryTreeSort = true;
	
	GenerateArray();
	
	if (DoElementarySort) {
		TimeForSelectionSort(1000, MODE_RANDOM);
		TimeForSelectionSort(2000, MODE_RANDOM);
		TimeForSelectionSort(4000, MODE_RANDOM);
		TimeForSelectionSort(8000, MODE_RANDOM);
		TimeForSelectionSort(16000, MODE_RANDOM);
		TimeForSelectionSort(32000, MODE_RANDOM);
		
		TimeForSelectionSort(1000, MODE_SORTED);
		TimeForSelectionSort(2000, MODE_SORTED);
		TimeForSelectionSort(4000, MODE_SORTED);
		TimeForSelectionSort(8000, MODE_SORTED);
		TimeForSelectionSort(16000, MODE_SORTED);
		TimeForSelectionSort(32000, MODE_SORTED);
		
		TimeForSelectionSort(1000, MODE_REVERSE);
		TimeForSelectionSort(2000, MODE_REVERSE);
		TimeForSelectionSort(4000, MODE_REVERSE);
		TimeForSelectionSort(8000, MODE_REVERSE);
		TimeForSelectionSort(16000, MODE_REVERSE);
		TimeForSelectionSort(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForInsertionSort(1000, MODE_RANDOM);
		TimeForInsertionSort(2000, MODE_RANDOM);
		TimeForInsertionSort(4000, MODE_RANDOM);
		TimeForInsertionSort(8000, MODE_RANDOM);
		TimeForInsertionSort(16000, MODE_RANDOM);
		TimeForInsertionSort(32000, MODE_RANDOM);
		
		TimeForInsertionSort(1000, MODE_SORTED);
		TimeForInsertionSort(2000, MODE_SORTED);
		TimeForInsertionSort(4000, MODE_SORTED);
		TimeForInsertionSort(8000, MODE_SORTED);
		TimeForInsertionSort(16000, MODE_SORTED);
		TimeForInsertionSort(32000, MODE_SORTED);
		
		TimeForInsertionSort(1000, MODE_REVERSE);
		TimeForInsertionSort(2000, MODE_REVERSE);
		TimeForInsertionSort(4000, MODE_REVERSE);
		TimeForInsertionSort(8000, MODE_REVERSE);
		TimeForInsertionSort(16000, MODE_REVERSE);
		TimeForInsertionSort(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForBubbleSort(1000, MODE_RANDOM);
		TimeForBubbleSort(2000, MODE_RANDOM);
		TimeForBubbleSort(4000, MODE_RANDOM);
		TimeForBubbleSort(8000, MODE_RANDOM);
		TimeForBubbleSort(16000, MODE_RANDOM);
		TimeForBubbleSort(32000, MODE_RANDOM);
		
		TimeForBubbleSort(1000, MODE_SORTED);
		TimeForBubbleSort(2000, MODE_SORTED);
		TimeForBubbleSort(4000, MODE_SORTED);
		TimeForBubbleSort(8000, MODE_SORTED);
		TimeForBubbleSort(16000, MODE_SORTED);
		TimeForBubbleSort(32000, MODE_SORTED);
		
		TimeForBubbleSort(1000, MODE_REVERSE);
		TimeForBubbleSort(2000, MODE_REVERSE);
		TimeForBubbleSort(4000, MODE_REVERSE);
		TimeForBubbleSort(8000, MODE_REVERSE);
		TimeForBubbleSort(16000, MODE_REVERSE);
		TimeForBubbleSort(32000, MODE_REVERSE);
		printf("\n");
	}
	
	if (DoQuickSort) {
		TimeForQuickSort(1000, MODE_RANDOM);
		TimeForQuickSort(2000, MODE_RANDOM);
		TimeForQuickSort(4000, MODE_RANDOM);
		TimeForQuickSort(8000, MODE_RANDOM);
		TimeForQuickSort(16000, MODE_RANDOM);
		TimeForQuickSort(32000, MODE_RANDOM);
		
		TimeForQuickSort(1000, MODE_SORTED);
		TimeForQuickSort(2000, MODE_SORTED);
		TimeForQuickSort(4000, MODE_SORTED);
		TimeForQuickSort(8000, MODE_SORTED);
		//	TimeForQuickSort(16000, MODE_SORTED);
		//	TimeForQuickSort(32000, MODE_SORTED);
		
		TimeForQuickSort(1000, MODE_REVERSE);
		TimeForQuickSort(2000, MODE_REVERSE);
		TimeForQuickSort(4000, MODE_REVERSE);
		TimeForQuickSort(8000, MODE_REVERSE);
		//	TimeForQuickSort(16000, MODE_REVERSE);
		//	TimeForQuickSort(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForQuickSortNR(1000, MODE_RANDOM);
		TimeForQuickSortNR(2000, MODE_RANDOM);
		TimeForQuickSortNR(4000, MODE_RANDOM);
		TimeForQuickSortNR(8000, MODE_RANDOM);
		TimeForQuickSortNR(16000, MODE_RANDOM);
		TimeForQuickSortNR(32000, MODE_RANDOM);
		
		TimeForQuickSortNR(1000, MODE_SORTED);
		TimeForQuickSortNR(2000, MODE_SORTED);
		TimeForQuickSortNR(4000, MODE_SORTED);
		TimeForQuickSortNR(8000, MODE_SORTED);
		TimeForQuickSortNR(16000, MODE_SORTED);
		TimeForQuickSortNR(32000, MODE_SORTED);
		
		TimeForQuickSortNR(1000, MODE_REVERSE);
		TimeForQuickSortNR(2000, MODE_REVERSE);
		TimeForQuickSortNR(4000, MODE_REVERSE);
		TimeForQuickSortNR(8000, MODE_REVERSE);
		TimeForQuickSortNR(16000, MODE_REVERSE);
		TimeForQuickSortNR(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForQuickSortNR2(1000, MODE_RANDOM);
		TimeForQuickSortNR2(2000, MODE_RANDOM);
		TimeForQuickSortNR2(4000, MODE_RANDOM);
		TimeForQuickSortNR2(8000, MODE_RANDOM);
		TimeForQuickSortNR2(16000, MODE_RANDOM);
		TimeForQuickSortNR2(32000, MODE_RANDOM);
		
		TimeForQuickSortNR2(1000, MODE_SORTED);
		TimeForQuickSortNR2(2000, MODE_SORTED);
		TimeForQuickSortNR2(4000, MODE_SORTED);
		TimeForQuickSortNR2(8000, MODE_SORTED);
		TimeForQuickSortNR2(16000, MODE_SORTED);
		TimeForQuickSortNR2(32000, MODE_SORTED);
		
		TimeForQuickSortNR2(1000, MODE_REVERSE);
		TimeForQuickSortNR2(2000, MODE_REVERSE);
		TimeForQuickSortNR2(4000, MODE_REVERSE);
		TimeForQuickSortNR2(8000, MODE_REVERSE);
		TimeForQuickSortNR2(16000, MODE_REVERSE);
		TimeForQuickSortNR2(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForQuickSortRandom(1000, MODE_RANDOM);
		TimeForQuickSortRandom(2000, MODE_RANDOM);
		TimeForQuickSortRandom(4000, MODE_RANDOM);
		TimeForQuickSortRandom(8000, MODE_RANDOM);
		TimeForQuickSortRandom(16000, MODE_RANDOM);
		TimeForQuickSortRandom(32000, MODE_RANDOM);
		
		TimeForQuickSortRandom(1000, MODE_SORTED);
		TimeForQuickSortRandom(2000, MODE_SORTED);
		TimeForQuickSortRandom(4000, MODE_SORTED);
		TimeForQuickSortRandom(8000, MODE_SORTED);
		TimeForQuickSortRandom(16000, MODE_SORTED);
		TimeForQuickSortRandom(32000, MODE_SORTED);
		
		TimeForQuickSortRandom(1000, MODE_REVERSE);
		TimeForQuickSortRandom(2000, MODE_REVERSE);
		TimeForQuickSortRandom(4000, MODE_REVERSE);
		TimeForQuickSortRandom(8000, MODE_REVERSE);
		TimeForQuickSortRandom(16000, MODE_REVERSE);
		TimeForQuickSortRandom(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForQuickSortMedian(1000, MODE_RANDOM);
		TimeForQuickSortMedian(2000, MODE_RANDOM);
		TimeForQuickSortMedian(4000, MODE_RANDOM);
		TimeForQuickSortMedian(8000, MODE_RANDOM);
		TimeForQuickSortMedian(16000, MODE_RANDOM);
		TimeForQuickSortMedian(32000, MODE_RANDOM);
		
		TimeForQuickSortMedian(1000, MODE_SORTED);
		TimeForQuickSortMedian(2000, MODE_SORTED);
		TimeForQuickSortMedian(4000, MODE_SORTED);
		TimeForQuickSortMedian(8000, MODE_SORTED);
		TimeForQuickSortMedian(16000, MODE_SORTED);
		TimeForQuickSortMedian(32000, MODE_SORTED);
		
		TimeForQuickSortMedian(1000, MODE_REVERSE);
		TimeForQuickSortMedian(2000, MODE_REVERSE);
		TimeForQuickSortMedian(4000, MODE_REVERSE);
		TimeForQuickSortMedian(8000, MODE_REVERSE);
		TimeForQuickSortMedian(16000, MODE_REVERSE);
		TimeForQuickSortMedian(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForQuickSortSub(1000, MODE_RANDOM);
		TimeForQuickSortSub(2000, MODE_RANDOM);
		TimeForQuickSortSub(4000, MODE_RANDOM);
		TimeForQuickSortSub(8000, MODE_RANDOM);
		TimeForQuickSortSub(16000, MODE_RANDOM);
		TimeForQuickSortSub(32000, MODE_RANDOM);
		
		TimeForQuickSortSub(1000, MODE_SORTED);
		TimeForQuickSortSub(2000, MODE_SORTED);
		TimeForQuickSortSub(4000, MODE_SORTED);
		TimeForQuickSortSub(8000, MODE_SORTED);
		TimeForQuickSortSub(16000, MODE_SORTED);
		TimeForQuickSortSub(32000, MODE_SORTED);
		
		TimeForQuickSortSub(1000, MODE_REVERSE);
		TimeForQuickSortSub(2000, MODE_REVERSE);
		TimeForQuickSortSub(4000, MODE_REVERSE);
		TimeForQuickSortSub(8000, MODE_REVERSE);
		TimeForQuickSortSub(16000, MODE_REVERSE);
		TimeForQuickSortSub(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForQsort(1000, MODE_RANDOM);
		TimeForQsort(2000, MODE_RANDOM);
		TimeForQsort(4000, MODE_RANDOM);
		TimeForQsort(8000, MODE_RANDOM);
		TimeForQsort(16000, MODE_RANDOM);
		TimeForQsort(32000, MODE_RANDOM);
		
		TimeForQsort(1000, MODE_SORTED);
		TimeForQsort(2000, MODE_SORTED);
		TimeForQsort(4000, MODE_SORTED);
		TimeForQsort(8000, MODE_SORTED);
		TimeForQsort(16000, MODE_SORTED);
		TimeForQsort(32000, MODE_SORTED);
		
		TimeForQsort(1000, MODE_REVERSE);
		TimeForQsort(2000, MODE_REVERSE);
		TimeForQsort(4000, MODE_REVERSE);
		TimeForQsort(8000, MODE_REVERSE);
		TimeForQsort(16000, MODE_REVERSE);
		TimeForQsort(32000, MODE_REVERSE);
		printf("\n");
	}
	
	if (DoHeapSort) {
		TimeForHeapSort(1000, MODE_RANDOM);
		TimeForHeapSort(2000, MODE_RANDOM);
		TimeForHeapSort(4000, MODE_RANDOM);
		TimeForHeapSort(8000, MODE_RANDOM);
		TimeForHeapSort(16000, MODE_RANDOM);
		TimeForHeapSort(32000, MODE_RANDOM);
		
		TimeForHeapSort(1000, MODE_SORTED);
		TimeForHeapSort(2000, MODE_SORTED);
		TimeForHeapSort(4000, MODE_SORTED);
		TimeForHeapSort(8000, MODE_SORTED);
		TimeForHeapSort(16000, MODE_SORTED);
		TimeForHeapSort(32000, MODE_SORTED);
		
		TimeForHeapSort(1000, MODE_REVERSE);
		TimeForHeapSort(2000, MODE_REVERSE);
		TimeForHeapSort(4000, MODE_REVERSE);
		TimeForHeapSort(8000, MODE_REVERSE);
		TimeForHeapSort(16000, MODE_REVERSE);
		TimeForHeapSort(32000, MODE_REVERSE);
		printf("\n");
		
		TimeForHeapSort_up(1000, MODE_RANDOM);
		TimeForHeapSort_up(2000, MODE_RANDOM);
		TimeForHeapSort_up(4000, MODE_RANDOM);
		TimeForHeapSort_up(8000, MODE_RANDOM);
		TimeForHeapSort_up(16000, MODE_RANDOM);
		TimeForHeapSort_up(32000, MODE_RANDOM);
		
		TimeForHeapSort_up(1000, MODE_SORTED);
		TimeForHeapSort_up(2000, MODE_SORTED);
		TimeForHeapSort_up(4000, MODE_SORTED);
		TimeForHeapSort_up(8000, MODE_SORTED);
		TimeForHeapSort_up(16000, MODE_SORTED);
		TimeForHeapSort_up(32000, MODE_SORTED);
		
		TimeForHeapSort_up(1000, MODE_REVERSE);
		TimeForHeapSort_up(2000, MODE_REVERSE);
		TimeForHeapSort_up(4000, MODE_REVERSE);
		TimeForHeapSort_up(8000, MODE_REVERSE);
		TimeForHeapSort_up(16000, MODE_REVERSE);
		TimeForHeapSort_up(32000, MODE_REVERSE);
		printf("\n");
	}
	
	if (DoShellSort) {
		TimeForShellSort(1000, MODE_RANDOM);
		TimeForShellSort(2000, MODE_RANDOM);
		TimeForShellSort(4000, MODE_RANDOM);
		TimeForShellSort(8000, MODE_RANDOM);
		TimeForShellSort(16000, MODE_RANDOM);
		TimeForShellSort(32000, MODE_RANDOM);
		
		TimeForShellSort(1000, MODE_SORTED);
		TimeForShellSort(2000, MODE_SORTED);
		TimeForShellSort(4000, MODE_SORTED);
		TimeForShellSort(8000, MODE_SORTED);
		TimeForShellSort(16000, MODE_SORTED);
		TimeForShellSort(32000, MODE_SORTED);
		
		TimeForShellSort(1000, MODE_REVERSE);
		TimeForShellSort(2000, MODE_REVERSE);
		TimeForShellSort(4000, MODE_REVERSE);
		TimeForShellSort(8000, MODE_REVERSE);
		TimeForShellSort(16000, MODE_REVERSE);
		TimeForShellSort(32000, MODE_REVERSE);
		printf("\n");

		TimeForShellSort_3h(1000, MODE_RANDOM);
		TimeForShellSort_3h(2000, MODE_RANDOM);
		TimeForShellSort_3h(4000, MODE_RANDOM);
		TimeForShellSort_3h(8000, MODE_RANDOM);
		TimeForShellSort_3h(16000, MODE_RANDOM);
		TimeForShellSort_3h(32000, MODE_RANDOM);
		
		TimeForShellSort_3h(1000, MODE_SORTED);
		TimeForShellSort_3h(2000, MODE_SORTED);
		TimeForShellSort_3h(4000, MODE_SORTED);
		TimeForShellSort_3h(8000, MODE_SORTED);
		TimeForShellSort_3h(16000, MODE_SORTED);
		TimeForShellSort_3h(32000, MODE_SORTED);
		
		TimeForShellSort_3h(1000, MODE_REVERSE);
		TimeForShellSort_3h(2000, MODE_REVERSE);
		TimeForShellSort_3h(4000, MODE_REVERSE);
		TimeForShellSort_3h(8000, MODE_REVERSE);
		TimeForShellSort_3h(16000, MODE_REVERSE);
		TimeForShellSort_3h(32000, MODE_REVERSE);
		printf("\n");
	}
	if (DoMergeSort)
	{
		TimeForMergeSort(1000, MODE_RANDOM);
		TimeForMergeSort(2000, MODE_RANDOM);
		TimeForMergeSort(4000, MODE_RANDOM);
		TimeForMergeSort(8000, MODE_RANDOM);
		TimeForMergeSort(16000, MODE_RANDOM);
		TimeForMergeSort(32000, MODE_RANDOM);
		
		TimeForMergeSort(1000, MODE_SORTED);
		TimeForMergeSort(2000, MODE_SORTED);
		TimeForMergeSort(4000, MODE_SORTED);
		TimeForMergeSort(8000, MODE_SORTED);
		TimeForMergeSort(16000, MODE_SORTED);
		TimeForMergeSort(32000, MODE_SORTED);
		
		TimeForMergeSort(1000, MODE_REVERSE);
		TimeForMergeSort(2000, MODE_REVERSE);
		TimeForMergeSort(4000, MODE_REVERSE);
		TimeForMergeSort(8000, MODE_REVERSE);
		TimeForMergeSort(16000, MODE_REVERSE);
		TimeForMergeSort(32000, MODE_REVERSE);
		printf("\n");

		TimeForMergeSort_ex(1000, MODE_RANDOM);
		TimeForMergeSort_ex(2000, MODE_RANDOM);
		TimeForMergeSort_ex(4000, MODE_RANDOM);
		TimeForMergeSort_ex(8000, MODE_RANDOM);
		TimeForMergeSort_ex(16000, MODE_RANDOM);
		TimeForMergeSort_ex(32000, MODE_RANDOM);
		
		TimeForMergeSort_ex(1000, MODE_SORTED);
		TimeForMergeSort_ex(2000, MODE_SORTED);
		TimeForMergeSort_ex(4000, MODE_SORTED);
		TimeForMergeSort_ex(8000, MODE_SORTED);
		TimeForMergeSort_ex(16000, MODE_SORTED);
		TimeForMergeSort_ex(32000, MODE_SORTED);
		
		TimeForMergeSort_ex(1000, MODE_REVERSE);
		TimeForMergeSort_ex(2000, MODE_REVERSE);
		TimeForMergeSort_ex(4000, MODE_REVERSE);
		TimeForMergeSort_ex(8000, MODE_REVERSE);
		TimeForMergeSort_ex(16000, MODE_REVERSE);
		TimeForMergeSort_ex(32000, MODE_REVERSE);
		printf("\n");
	}

	if (DoRadixSort)
	{
		TimeForRadixExchangeSort(1000, MODE_RANDOM);
		TimeForRadixExchangeSort(2000, MODE_RANDOM);
		TimeForRadixExchangeSort(4000, MODE_RANDOM);
		TimeForRadixExchangeSort(8000, MODE_RANDOM);
		TimeForRadixExchangeSort(16000, MODE_RANDOM);
		TimeForRadixExchangeSort(32000, MODE_RANDOM);
		
		TimeForRadixExchangeSort(1000, MODE_SORTED);
		TimeForRadixExchangeSort(2000, MODE_SORTED);
		TimeForRadixExchangeSort(4000, MODE_SORTED);
		TimeForRadixExchangeSort(8000, MODE_SORTED);
		TimeForRadixExchangeSort(16000, MODE_SORTED);
		TimeForRadixExchangeSort(32000, MODE_SORTED);
		
		TimeForRadixExchangeSort(1000, MODE_REVERSE);
		TimeForRadixExchangeSort(2000, MODE_REVERSE);
		TimeForRadixExchangeSort(4000, MODE_REVERSE);
		TimeForRadixExchangeSort(8000, MODE_REVERSE);
		TimeForRadixExchangeSort(16000, MODE_REVERSE);
		TimeForRadixExchangeSort(32000, MODE_REVERSE);
		printf("\n");

		TimeForRadixExchangeSort_nr(1000, MODE_RANDOM);
		TimeForRadixExchangeSort_nr(2000, MODE_RANDOM);
		TimeForRadixExchangeSort_nr(4000, MODE_RANDOM);
		TimeForRadixExchangeSort_nr(8000, MODE_RANDOM);
		TimeForRadixExchangeSort_nr(16000, MODE_RANDOM);
		TimeForRadixExchangeSort_nr(32000, MODE_RANDOM);
		
		TimeForRadixExchangeSort_nr(1000, MODE_SORTED);
		TimeForRadixExchangeSort_nr(2000, MODE_SORTED);
		TimeForRadixExchangeSort_nr(4000, MODE_SORTED);
		TimeForRadixExchangeSort_nr(8000, MODE_SORTED);
		TimeForRadixExchangeSort_nr(16000, MODE_SORTED);
		TimeForRadixExchangeSort_nr(32000, MODE_SORTED);
		
		TimeForRadixExchangeSort_nr(1000, MODE_REVERSE);
		TimeForRadixExchangeSort_nr(2000, MODE_REVERSE);
		TimeForRadixExchangeSort_nr(4000, MODE_REVERSE);
		TimeForRadixExchangeSort_nr(8000, MODE_REVERSE);
		TimeForRadixExchangeSort_nr(16000, MODE_REVERSE);
		TimeForRadixExchangeSort_nr(32000, MODE_REVERSE);
		printf("\n");

		TimeForStraightRadixSort(1000, MODE_RANDOM);
		TimeForStraightRadixSort(2000, MODE_RANDOM);
		TimeForStraightRadixSort(4000, MODE_RANDOM);
		TimeForStraightRadixSort(8000, MODE_RANDOM);
		TimeForStraightRadixSort(16000, MODE_RANDOM);
		TimeForStraightRadixSort(32000, MODE_RANDOM);
		
		TimeForStraightRadixSort(1000, MODE_SORTED);
		TimeForStraightRadixSort(2000, MODE_SORTED);
		TimeForStraightRadixSort(4000, MODE_SORTED);
		TimeForStraightRadixSort(8000, MODE_SORTED);
		TimeForStraightRadixSort(16000, MODE_SORTED);
		TimeForStraightRadixSort(32000, MODE_SORTED);
		
		TimeForStraightRadixSort(1000, MODE_REVERSE);
		TimeForStraightRadixSort(2000, MODE_REVERSE);
		TimeForStraightRadixSort(4000, MODE_REVERSE);
		TimeForStraightRadixSort(8000, MODE_REVERSE);
		TimeForStraightRadixSort(16000, MODE_REVERSE);
		TimeForStraightRadixSort(32000, MODE_REVERSE);
		printf("\n");
	}

	if (DoBinaryTreeSort)
	{
		TimeForBinaryTreeSort(1000, MODE_RANDOM);
		TimeForBinaryTreeSort(2000, MODE_RANDOM);
		TimeForBinaryTreeSort(4000, MODE_RANDOM);
		TimeForBinaryTreeSort(8000, MODE_RANDOM);
		TimeForBinaryTreeSort(16000, MODE_RANDOM);
		TimeForBinaryTreeSort(32000, MODE_RANDOM);
		
		TimeForBinaryTreeSort(1000, MODE_SORTED);
		TimeForBinaryTreeSort(2000, MODE_SORTED);
		TimeForBinaryTreeSort(4000, MODE_SORTED);
		TimeForBinaryTreeSort(8000, MODE_SORTED);
		TimeForBinaryTreeSort(16000, MODE_SORTED);
		TimeForBinaryTreeSort(32000, MODE_SORTED);
		
		TimeForBinaryTreeSort(1000, MODE_REVERSE);
		TimeForBinaryTreeSort(2000, MODE_REVERSE);
		TimeForBinaryTreeSort(4000, MODE_REVERSE);
		TimeForBinaryTreeSort(8000, MODE_REVERSE);
		TimeForBinaryTreeSort(16000, MODE_REVERSE);
		TimeForBinaryTreeSort(32000, MODE_REVERSE);
		printf("\n");
	}
}
