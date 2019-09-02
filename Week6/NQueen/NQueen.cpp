#include <stdio.h>
#include <stdlib.h>

void PrintQueens(int q[], int N)
{
	int r, c;
	for (r = 0; r < N; r++) {
		for (c = 0; c < N; c++) {
			if (q[r] == c) printf("Q");
			else printf(".");
		}
		printf("\n");
	}
	printf("\n");
}

bool NQueen_Promising(int q[], int N, int row)
{
	if (row < 1) return true;		// 하나 놓인 것은 상관 없다. 

	for (int i = 0; i < row; i++) {
		if (q[row] == q[i] || row - i == abs(q[row] - q[i]))
			return false;
	}
	return true;
}

void NQueen(int q[], int N, int row = -1)
{
	if (NQueen_Promising(q, N, row)) {
		if (row == N - 1) {
			PrintQueens(q, N);
		} else {
			for (int i = 0; i < N; i++) {
				q[row + 1] = i;
				NQueen(q, N, row + 1);
			}
		}
	}
}

void NQueen2(int q[], int N, int row = 0)
{
	for (int i = 0; i < N; i++) {
		q[row] = i;
		if (NQueen_Promising(q, N, row)) {
			if (row == N - 1) {
				PrintQueens(q, N);
			} else {
				NQueen2(q, N, row + 1);
			}
		}
	}
}

void main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage : NQueen [N]\n");
		return;
	}

	int N = atoi(argv[1]);

	int *q = new int [N];

	NQueen2(q, N);

	delete [] q;
}