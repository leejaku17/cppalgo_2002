#include "DrawBinTree.h"

void DrawBinTree::Draw(CDC *pDC, const RECT& rt, bool bDrawTail)
{
	pDC->MoveTo((rt.right + rt.left) / 2, m_nYMargin);
	_DrawLink(pDC, m_pNodeHead->pLeft, m_nXMargin, rt.right - m_nXMargin, m_nYMargin, bDrawTail);
	_DrawNode(pDC, m_pNodeHead->pLeft, m_nXMargin, rt.right - m_nXMargin, m_nYMargin, bDrawTail);
}

void DrawBinTree::_DrawNode(CDC *pDC, Node *p, int x1, int x2, int y, bool bDrawTail)
{
	if (p != m_pNodeTail)
	{
		_DrawNode(pDC, p->pLeft, x1, (x1+x2)/2, y + m_nDY, bDrawTail);
		
		// 노드를 그림 
		CSize size = pDC->GetOutputTextExtent(CString((const char*)p->data));
		CRect rt((x1+x2)/2 - size.cx/2, y - size.cy/2, (x1+x2)/2 + size.cx/2, y + size.cy/2);

		CRect rt2 = rt;
		rt2.InflateRect(4, 2);
		pDC->Ellipse(&rt2);

		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(CString((const char*)p->data), &rt, DT_CENTER | DT_VCENTER);

		_DrawNode(pDC, p->pRight, (x1+x2)/2, x2, y + m_nDY, bDrawTail);
	} 
	else if (bDrawTail)
	{
		pDC->Rectangle((x1+x2)/2 - 2, y - 2, (x1+x2)/2 + 2, y + 2);
	}
}

void DrawBinTree::_DrawLink(CDC *pDC, Node *p, int x1, int x2, int y, bool bDrawTail)
{
	if (p != m_pNodeTail)
	{
		// parent로부터 현재 위치로 선을 그린다. 
		pDC->LineTo((x1+x2)/2, y);
		_DrawLink(pDC, p->pLeft, x1, (x1+x2)/2, y + m_nDY, bDrawTail);

		// 다음을 위해 원위치 한다. 
		pDC->MoveTo((x1+x2)/2, y);
		_DrawLink(pDC, p->pRight, (x1+x2)/2, x2, y + m_nDY, bDrawTail);
	} 
	else if (bDrawTail)
	{
		pDC->LineTo((x1+x2)/2, y);
	}
}