#ifndef _Raster_h
#define _Raster_h

class RasterSpace 
{
public:
	RasterSpace() { m_pArray = 0; }
	RasterSpace(const int* pArray, int w, int h);
	~RasterSpace() { delete [] m_pArray; }
	void SetArray(const int *pArray, int w, int h);

	int GetPixel(int x, int y);
	void PutPixel(int x, int y, int nColor);

	void FloodFill(int x, int y, int nFillColor, int nSelColor = -1);
	void FloodFill_nr(int x, int y, int nFillColor);

	void print();

protected:
	int *m_pArray;
	int m_nWidth;
	int m_nHeight;
};

#endif