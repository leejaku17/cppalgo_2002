#include "Calc.h"
#include <stdio.h>

using namespace cppalgo;

void main(void)
{
	Calculator calc;
	String strInfix1 = "(12+(34*56))";
	String strInfix2 = "(2*(3+6/2)+2)/4+3";

	String strReturn = calc.ToPostfix1(strInfix1);
	printf("%s\n", (const char*)strReturn);

	strReturn = calc.ToPostfix2(strInfix2);
	printf("%s\n", (const char*)strReturn);

	long n = calc.CalcPostfix(strReturn);
	printf("%d\n", n);

	n = calc.CalcInfix(strInfix2);
	printf("%d\n", n);
}