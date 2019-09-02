#ifndef _DrawChainMap_h
#define _DrawChainMap_h

#include "../Search/ChainMap.h"
#include "../String/AString.h"
#include "DrawHashMap.h"		// for StringHash

#include <afxwin.h>
#pragma comment(lib, "../cppalgo/ReleaseMT/cppalgo.lib")

class DrawChainMap : public cppalgo::ChainMap<cppalgo::String, StringHash>
{
public:
	DrawChainMap(const StringHash& hash, int nSize) : cppalgo::ChainMap<cppalgo::String, StringHash>(hash, nSize) {
		m_nXMargin = 50;
		m_nYMargin = 10;
		m_nWidth = 50;
		m_nHeight = 20;
		m_nLinkLen = 20;
	}
	~DrawChainMap() {} 
	void Draw(CDC *pDC);

protected:
	int m_nXMargin;
	int m_nYMargin;
	int m_nWidth;
	int m_nHeight;
	int m_nLinkLen;
};

#endif