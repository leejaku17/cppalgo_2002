#ifndef _SHAPE_H
#define _SHAPE_H

#include <stdio.h>

class Point
{
private:
	int m_nX;
	int m_nY;
	int m_nColor;
public:
	// constructors
	Point() { m_nX = 0; m_nY = 0; m_nColor = 0; }
	Point(int x, int y, int c) { m_nX = x; m_nY = y; m_nColor = c; }
	// member functions
	void setColor(int c) { m_nColor = c; }
	int  getColor() { return m_nColor; }
	void setXY(int x, int y) { m_nX = x; m_nY = y; }
	int getX() { return m_nX; }
	int getY() { return m_nY; }
	// virtual functions
	virtual void WhoAreYou() { printf("I'm Point\n"); }
};

class Rectangle : public Point
{
private:
	int m_nX2;
	int m_nY2;
public:
	// constructors
	Rectangle() : Point() { m_nX2 = 0; m_nY2 = 0; }
	Rectangle(int x1, int y1, int x2, int y2, int c) : Point(x1, y1, c) { m_nX2 = x2; m_nY2 = y2; }
	// member functions
	void setX2Y2(int x2, int y2) { m_nX2 = x2; m_nY2 = y2; }
	int getX2() { return m_nX2; }
	int getY2() { return m_nY2; }
	// virtual functions
	void WhoAreYou() { printf("I'm Rectangle\n"); }
};

#endif	/* _SHAPE_H */