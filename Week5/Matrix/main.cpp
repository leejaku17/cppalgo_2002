#include "DenseMatrix.h"
#include "SparseMatrix.h"

using namespace cppalgo;

void DenseMatrixTest()
{
	DenseMatrix dm33(3, 3);
	DenseMatrix dm33_2(3, 3);
	DenseMatrix dm33_3(3, 3);
	DenseMatrix dm31(3, 1);

	// opertor +
	dm33.A(0, 0) = 1; dm33.A(0, 1) = 2; dm33.A(0, 2) = 4;
	dm33.A(1, 0) = 3; dm33.A(1, 1) = 1; dm33.A(1, 2) = 2;
	dm33.A(2, 0) = 4; dm33.A(2, 1) = 1; dm33.A(2, 2) = 3;

	dm33_2.A(0, 0) = 7; dm33_2.A(0, 1) = 3; dm33_2.A(0, 2) = 1;
	dm33_2.A(1, 0) = 2; dm33_2.A(1, 1) = 3; dm33_2.A(1, 2) = 5;
	dm33_2.A(2, 0) = 8; dm33_2.A(2, 1) = 1; dm33_2.A(2, 2) = 6;

	dm33_3 = dm33 + dm33_2;
	dm33_3.Print();

	dm33_3 = dm33 - dm33_2;
	dm33_3.Print();

	dm33_3 = dm33 * dm33_2;
	dm33_3.Print();

	// Solve_Gauss , Determinant_Gauss
	dm33.A(0, 0) = 2; dm33.A(0, 1) = 1; dm33.A(0, 2) = -3;
	dm33.A(1, 0) = -1; dm33.A(1, 1) = 3; dm33.A(1, 2) = 2;
	dm33.A(2, 0) = 3; dm33.A(2, 1) = 1; dm33.A(2, 2) = -3;
	printf("Determinant = %lg\n", dm33.Determinant());

	dm31.A(0, 0) = -1; dm31.A(1, 0) = 12; dm31.A(2, 0) = 0;

	dm31 = dm33.Solve(dm31);
	dm31.Print();
	// Solve_Gauss with pivotting , Determinant_Gauss
	dm33.A(0, 0) = 0; dm33.A(0, 1) = -1; dm33.A(0, 2) = 2;
	dm33.A(1, 0) = -2; dm33.A(1, 1) = 2; dm33.A(1, 2) = -1;
	dm33.A(2, 0) = -2; dm33.A(2, 1) = 4; dm33.A(2, 2) = 3;
	printf("Determinant = %lg\n", dm33.Determinant());

	dm31.A(0, 0) = 0; dm31.A(1, 0) = 0; dm31.A(2, 0) = 1;

	dm31 = dm33.Solve(dm31);
	dm31.Print();

	// inverse
	dm33.A(0, 0) = 2; dm33.A(0, 1) = 1; dm33.A(0, 2) = -3;
	dm33.A(1, 0) = -1; dm33.A(1, 1) = 3; dm33.A(1, 2) = 2;
	dm33.A(2, 0) = 3; dm33.A(2, 1) = 1; dm33.A(2, 2) = -3;

	dm33_2 = dm33.Inverse();
	dm33_2.Print();

	dm33_3 = dm33 * dm33_2;
	dm33_3.Print();
}

void SparseMatrixTest()
{
	SparseMatrix dm33(3, 3);
	SparseMatrix dm33_2(3, 3);
	SparseMatrix dm33_3(3, 3);
	SparseMatrix dm31(3, 1);

	// opertor +
	dm33.Set(0, 0, 1); dm33.Set(0, 1, 2); dm33.Set(0, 2, 4);
	dm33.Set(1, 0, 3); dm33.Set(1, 1, 1); dm33.Set(1, 2, 2);
	dm33.Set(2, 0, 4); dm33.Set(2, 1, 1); dm33.Set(2, 2 ,3);

	dm33_2.Set(0, 0, 7); dm33_2.Set(0, 1, 3); dm33_2.Set(0, 2, 1);
	dm33_2.Set(1, 0, 2); dm33_2.Set(1, 1, 3); dm33_2.Set(1, 2, 5);
	dm33_2.Set(2, 0, 8); dm33_2.Set(2, 1, 1); dm33_2.Set(2, 2, 6);

	dm33_3 = dm33 + dm33_2;
	dm33_3.Print();

	dm33_3 = dm33 - dm33_2;
	dm33_3.Print();

	dm33_3 = dm33 * dm33_2;
	dm33_3.Print();

	// Solve_Gauss , Determinant_Gauss
	dm33.Set(0, 0, 2); dm33.Set(0, 1, 1); dm33.Set(0, 2, -3);
	dm33.Set(1, 0,-1); dm33.Set(1, 1, 3); dm33.Set(1, 2, 2);
	dm33.Set(2, 0, 3); dm33.Set(2, 1, 1); dm33.Set(2, 2, -3);
	printf("Determinant = %lg\n", dm33.Determinant());

	dm31.Set(0, 0, -1); dm31.Set(1, 0, 12); dm31.Set(2, 0, 0);

	dm31 = dm33.Solve(dm31);
	dm31.Print();
	// Solve_Gauss with pivotting , Determinant_Gauss
	dm33.Set(0, 0, 0); dm33.Set(0, 1, -1); dm33.Set(0, 2, 2);
	dm33.Set(1, 0, -2); dm33.Set(1, 1, 2); dm33.Set(1, 2, -1);
	dm33.Set(2, 0, -2); dm33.Set(2, 1, 4); dm33.Set(2, 2, 3);
	printf("Determinant = %lg\n", dm33.Determinant());

	dm31.Set(0, 0, 0); dm31.Set(1, 0, 0); dm31.Set(2, 0, 1);

	dm31 = dm33.Solve(dm31);
	dm31.Print();

	// inverse
	dm33.Set(0, 0, 2); dm33.Set(0, 1, 1); dm33.Set(0, 2, -3);
	dm33.Set(1, 0, -1); dm33.Set(1, 1, 3); dm33.Set(1, 2, 2);
	dm33.Set(2, 0, 3); dm33.Set(2, 1, 1); dm33.Set(2, 2, -3);

	dm33_2 = dm33.Inverse();
	dm33_2.Print();

	dm33_3 = dm33 * dm33_2;
	dm33_3.Print();

	dm33_3.Set(0, 0, 0); dm33_3.Set(0, 1, 0); dm33_3.Set(0, 2, 0);
	dm33_3.Set(1, 0, 0); dm33_3.Set(1, 1, 0); dm33_3.Set(1, 2, 0);
	dm33_3.Set(2, 0, 0); dm33_3.Set(2, 1, 0); dm33_3.Set(2, 2, 0);
	dm33_3.Print();
}

void main(void)
{
	DenseMatrixTest();
	SparseMatrixTest();
}