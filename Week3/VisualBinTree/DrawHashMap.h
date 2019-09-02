#ifndef _DrawHashMap_h
#define _DrawHashMap_h

#include "../Search/HashMap.h"
#include "../String/AString.h"

#include <afxwin.h>

// MFC어플리케이션에서 사용할 때는 Release Multithreaded 버전을 사용해야 한다. 
#pragma comment(lib, "../cppalgo/ReleaseMT/cppalgo.lib")

struct StringHash
{
	unsigned long hash(const cppalgo::String& key) const {
		unsigned long nHash = 0;
		for (int i = 0; i < key.GetLength(); i++)
			nHash = (nHash << 5) + nHash + key[i];
		return nHash;
	}
};

class DrawHashMap : public cppalgo::HashMap<cppalgo::String, StringHash>
{
public:
	DrawHashMap(const StringHash& hash, int nSize) : cppalgo::HashMap<cppalgo::String, StringHash>(hash, nSize) {
		m_nXMargin = 50;
		m_nYMargin = 10;
		m_nWidth = 200;
		m_nHeight = 20;
	}
	~DrawHashMap() {}

	void Draw(CDC *pDC);

protected:
	int m_nXMargin;
	int m_nYMargin;
	int m_nWidth;
	int m_nHeight;
};

#endif