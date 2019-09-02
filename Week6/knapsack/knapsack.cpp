#include <stdio.h>
#include "../sort/ShellSort.h"

struct KnapsackItem {
	char name;
	int w;
	int p;
	bool operator>(const KnapsackItem& item) const { 
		return (double)p/(double)w < (double)item.p/(double)item.w; 
	}
};

int Knapsack_Dynamic(KnapsackItem *Items, int N, int M)
{
	int *cost = new int [M + 1];
	int *best = new int [M + 1];
	int y, j;

	for (y = 0; y <= M; y++) {
		cost[y] = 0;
		best[y] = -1;
	}

	for (j = 0; j < N; j++) {
		for (y = 1; y <= M; y++) {
			if (y >= Items[j].w) {
				if (cost[y] < cost[y - Items[j].w] + Items[j].p) {
					cost[y] = cost[y - Items[j].w] + Items[j].p;
					best[y] = j;
				}
			}
		}
	}

	y = M;
	do {
		printf("%c", Items[best[y]].name);
		y -= Items[best[y]].w;
	} while (y > 0 && best[y] >= 0);
	printf("\n");

	int maxp = cost[M];

	delete [] cost;
	delete [] best;

	return maxp;
}

double Knapsack_Greedy(KnapsackItem *Items, int N, double M)
{
	int i;
	double maxp = 0;

	cppalgo::ShellSort(Items, N);

	for (i = 0; i < N; i++) {
		if (M > Items[i].w) {
			printf("%c : %d\n", Items[i].name, Items[i].w);
			M -= Items[i].w;
			maxp += Items[i].p;
		} else {
			double frac = M / Items[i].w;
			if (frac > 0) {
				printf("%c : %lf\n", Items[i].name, frac * Items[i].w);
				maxp += frac * Items[i].p;				
			}
			break;
		}
	}

	return maxp;
}

bool Knapsack_Simple_Promising(double M, int weight)
{
	if (weight <= M) return true;
	else return false;
}

int count = 0;

void Knapsack_Backtrack_Simple(KnapsackItem *Items, int N, double M, int& maxprofit, int best[], int trial[], int j = -1, int weight = 0, int profit = 0)
{
	count++;	// for test
	if (Knapsack_Simple_Promising(M, weight)) {
		if (j == N - 1) {
			if (profit > maxprofit) {
				maxprofit = profit;
				for (int i = 0; i < N; i++) best[i] = trial[i];
			}
		} else {
			trial[j+1] = 1;
			Knapsack_Backtrack_Simple(Items, N, M, maxprofit, best, trial, j+1, weight + Items[j+1].w, profit + Items[j+1].p);
			trial[j+1] = 0;
			Knapsack_Backtrack_Simple(Items, N, M, maxprofit, best, trial, j+1, weight, profit);
		}
	}	
}

bool Knapsack_Bound_Promising(KnapsackItem *Items, int N, int M, int j, int weight, int profit, int maxprofit)
{
	if (weight > M) return false; // upper bound
	if (j == N - 1) return true;  // 마지막 레벨은 검사할 필요 없음 

	double gprofit = profit;
	int remain = M - weight;
	for (int i = j+1; i < N; i++) {
		if (Items[i].w < remain) {
			gprofit += Items[i].p;
			remain -= Items[i].w;
		} else {
			double frac = (double)remain / (double)Items[i].w;
			if (frac > 0) {
				gprofit += frac * (double)Items[i].p;				
			}
			break;
		}
	}
	if (gprofit > maxprofit) return true;
	else return false;
}

void Knapsack_Backtrack_Bound(KnapsackItem *Items, int N, double M, int& maxprofit, int best[], int trial[], int j = -1, int weight = 0, int profit = 0)
{
	count++;	// for test
	if (Knapsack_Bound_Promising(Items, N, M, j, weight, profit, maxprofit)) {
		if (j == N - 1) {
			if (profit > maxprofit) {
				maxprofit = profit;
				for (int i = 0; i < N; i++) best[i] = trial[i];
			}
		} else {
			trial[j+1] = 1;
			Knapsack_Backtrack_Bound(Items, N, M, maxprofit, best, trial, j+1, weight + Items[j+1].w, profit + Items[j+1].p);
			trial[j+1] = 0;
			Knapsack_Backtrack_Bound(Items, N, M, maxprofit, best, trial, j+1, weight, profit);
		}
	}	
}

void Init(KnapsackItem* pItems)
{
	char name[] = { 'A', 'B', 'C', 'D', 'E' };
	int weight[] = { 3, 4, 7, 8, 9 };
	int profit[] = { 4, 5, 10, 11, 13 };

	for (int i = 0; i < 5; i++) {
		pItems[i].name = name[i];
		pItems[i].w = weight[i];
		pItems[i].p = profit[i];
	}
}

void main(void)
{
	KnapsackItem Items[5];

	int maxp;
	printf("Dynamic Programming\n");

	Init(Items);
	maxp = Knapsack_Dynamic(Items, 5, 17);
	printf("Max profit = %d\n", maxp);

	double maxpd;
	Init(Items);
	printf("Greedy Method\n");
	maxpd = Knapsack_Greedy(Items, 5, 17);
	printf("Max profit = %lf\n", maxpd);

	int best[5];
	int trial[5];

	Init(Items);
	maxp = 0;
	count = 0;
	printf("Backtracking Simple\n");
	Knapsack_Backtrack_Simple(Items, 5, 17, maxp, best, trial);
	printf("Max profit = %d (count = %d)\n", maxp, count);
	for (int i = 0; i < 5; i++) {
		if (best[i]) printf("%c", Items[i].name);
	}
	printf("\n");

	Init(Items);
	count = 0;
	maxp = 0;
	cppalgo::ShellSort(Items, 5);
	printf("Backtracking Bound\n");
	Knapsack_Backtrack_Bound(Items, 5, 17, maxp, best, trial);
	printf("Max profit = %d (count = %d)\n", maxp, count);
	for (i = 0; i < 5; i++) {
		if (best[i]) printf("%c", Items[i].name);
	}
	printf("\n");
}