#ifndef _DrawRadixTrieMap_h
#define _DrawRadixTrieMap_h

#include "../Search/RadixTrieMap.h"
#include <afxwin.h>

class DrawRadixTrieMap : public cppalgo::RadixTrieMap<char>
{
public:
	DrawRadixTrieMap() : cppalgo::RadixTrieMap<char>() {
		m_nDY = 50;
		m_nXMargin = 10;
		m_nYMargin = 20;
	}
	~DrawRadixTrieMap() {}
	void Draw(CDC *pDC, const RECT& rt, bool bDrawTail = true);
protected:
	int m_nDY;
	int m_nXMargin;
	int m_nYMargin;
	void _DrawNode(CDC *pDC, Node *p, int x1, int x2, int y, bool bDrawTail, int b);
	void _DrawLink(CDC *pDC, Node *p, int x1, int x2, int y, bool bDrawTail);
	CString _MakeBits(int x, int b);
};

#endif