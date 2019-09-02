#include "Polynomial.h"

using namespace cppalgo;

void main(void)
{
	Polynomial p1, p2;

	p1.InsertTerm(4, 8.0);
	p1.InsertTerm(3, 6.0);
	p1.InsertTerm(2, 5.0);
	p1.InsertTerm(1, -3.0);
	p1.InsertTerm(0, 1.0);

	p2.InsertTerm(3, -3.0);
	p2.InsertTerm(2, 1.0);
	p2.InsertTerm(1, 9.0);
	p2.InsertTerm(0, 3.0);

	Polynomial p3 = p1 + p2;
	p3.Print();

	p3 = p1 - p2;
	p3.Print();

	p3 = p1 * p2;
	p3.Print();

	p1.Differential();
	p1.Print();

	p1.Integral();
	p1.Print();

	printf("%lg\n", p1.Evaluate(2.0));

}