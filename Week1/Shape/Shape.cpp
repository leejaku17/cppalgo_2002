#include "Shape.h"

void main(void)
{
	Point p;
	Rectangle r;

	Point **ppPoints = new Point* [2];

	ppPoints[0] = &p;
	ppPoints[1] = &r; // base클래스로 derived클래스의 포인터를 대입가능

	for (int i = 0; i < 2; i++) {
		ppPoints[i]->WhoAreYou();
	}

}