#ifndef _DrawBinTree_h
#define _DrawBinTree_h

#include "../Search/BinTreeMap.h"
#include "../String/AString.h"

#include <afxwin.h>

// MFC어플리케이션에서 사용할 때는 Release Multithreaded 버전을 사용해야 한다. 
#pragma comment(lib, "../cppalgo/ReleaseMT/cppalgo.lib")

class DrawBinTree : public cppalgo::BinTreeMap<cppalgo::String>
{
public:
	DrawBinTree() : cppalgo::BinTreeMap<cppalgo::String>() { m_nDY = 50; m_nXMargin = 10; m_nYMargin = 20; }
	~DrawBinTree() {}
	
	void SetDY(int nDY) { m_nDY = nDY; }
	
	void Draw(CDC *pDC, const RECT& rt, bool bDrawTail = true);
	
protected:
	int m_nDY;
	int m_nXMargin;
	int m_nYMargin;
	
	void _DrawNode(CDC *pDC, Node *p, int x1, int x2, int y, bool bDrawTail);
	void _DrawLink(CDC *pDC, Node *p, int x1, int x2, int y, bool bDrawTail);
};


#endif