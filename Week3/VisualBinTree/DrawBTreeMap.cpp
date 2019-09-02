#include "DrawBTreeMap.h"

void DrawBTreeMap::Draw(CDC *pDC, const RECT& rt)
{
	pDC->MoveTo((rt.right + rt.left) / 2, m_nYMargin);
	_DrawLink(pDC, m_pNodeHead->Left(0), m_nXMargin, rt.right - m_nXMargin, m_nYMargin);
	_DrawNode(pDC, m_pNodeHead->Left(0), m_nXMargin, rt.right - m_nXMargin, m_nYMargin);
}

void DrawBTreeMap::_DrawNode(CDC *pDC, Node *p, int x1, int x2, int y)
{
	int i;
	if (p != 0)
	{
		CString strNode;
		if (p->Size() > 0) {
			strNode += p->Key(0);
			for (i = 1; i < p->Size(); i++) {
				strNode += " ";
				strNode += p->Key(i);
			}
		}
		CSize size = pDC->GetOutputTextExtent(strNode);
		CRect rt((x1+x2)/2 - size.cx/2, y - size.cy/2, (x1+x2)/2 + size.cx/2, y + size.cy/2);
		CRect rt2 = rt;
		rt2.InflateRect(4, 2);
		pDC->Ellipse(&rt2);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strNode, &rt, DT_CENTER | DT_VCENTER);

		int nUnit = (x2 - x1) / (p->Size() + 1);

		for (i = 0; i <= p->Size(); i++) {
			_DrawNode(pDC, p->Left(i), i*nUnit + x1, (i+1)*nUnit + x1, y + m_nDY);
		}
	}
}

void DrawBTreeMap::_DrawLink(CDC * pDC, Node *p, int x1, int x2, int y)
{
	if (p != 0)
	{
		pDC->LineTo((x1 + x2) / 2, y);

		int nUnit = (x2 - x1) / (p->Size() + 1);
		for (int i = 0; i <= p->Size(); i++) {
			_DrawLink(pDC, p->Left(i), i*nUnit + x1, (i+1)*nUnit + x1, y + m_nDY);
			pDC->MoveTo((x1 + x2) / 2, y);
		}
	}
}