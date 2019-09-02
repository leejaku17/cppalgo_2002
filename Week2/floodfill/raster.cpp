#include <stdio.h>
#include "raster.h"
#include "../Stack/ListStack.h"

RasterSpace::RasterSpace(const int *pArray, int w, int h)
{
	m_pArray = new int [w*h];

	for (int i = 0; i < w*h; i++)
		m_pArray[i] = pArray[i];

	m_nWidth = w;
	m_nHeight = h;
}

void RasterSpace::SetArray(const int *pArray, int w, int h)
{
	if (m_pArray)
		delete [] m_pArray;
	m_pArray = new int [w*h];

	for (int i = 0; i < w*h; i++)
		m_pArray[i] = pArray[i];

	m_nWidth = w;
	m_nHeight = h;
}

int RasterSpace::GetPixel(int x, int y)
{
	if (x < 0 || x >= m_nWidth || y < 0 || y >= m_nHeight)
		return -1;
	else
		return m_pArray[y*m_nWidth + x];
}

void RasterSpace::PutPixel(int x, int y, int nColor)
{
	if (x < 0 || x >= m_nWidth || y < 0 || y >= m_nHeight)
		return;
	else
		m_pArray[y*m_nWidth + x] = nColor;
}

void RasterSpace::FloodFill(int x, int y, int nFillColor, int nSelColor)
{
	if (nSelColor < 0)			// 최초 콜이다. 
		nSelColor = GetPixel(x, y);
	
	if (GetPixel(x, y) != nSelColor)	// 다른 색이면
		return;
	else
	{
		PutPixel(x, y, nFillColor);
		FloodFill(x - 1, y, nFillColor, nSelColor);
		FloodFill(x + 1, y, nFillColor, nSelColor);
		FloodFill(x, y - 1, nFillColor, nSelColor);
		FloodFill(x, y + 1, nFillColor, nSelColor);
	}
}

void RasterSpace::FloodFill_nr(int x, int y, int nFillColor)
{
	cppalgo::ListStack<int> stack;

	int nSelColor = GetPixel(x, y);

	stack.Push(y);
	stack.Push(x);

	while (!stack.IsEmpty())
	{
		x = stack.Pop();
		y = stack.Pop();
		if (GetPixel(x, y) != nSelColor)
			continue;
		PutPixel(x, y, nFillColor);
		stack.Push(y + 1);
		stack.Push(x);
		stack.Push(y - 1);
		stack.Push(x);
		stack.Push(y);
		stack.Push(x + 1);
		stack.Push(y);
		stack.Push(x - 1);
	}
}

void RasterSpace::print()
{
	int h, w;
	for (h = 0; h < m_nHeight; h++) {
		for (w = 0; w < m_nWidth; w++) {
			printf("%d", m_pArray[h*m_nHeight + w]);
		}
		printf("\n");
	}
}