#include "DrawRBTreeMap.h"

void DrawRBTreeMap::Draw(CDC *pDC, const RECT& rt)
{
	pDC->MoveTo((rt.right + rt.left) / 2, m_nYMargin);
	_DrawLink(pDC, m_pNodeHead->pLeft, m_nXMargin, rt.right - m_nXMargin, m_nYMargin);
	_DrawNode(pDC, m_pNodeHead->pLeft, m_nXMargin, rt.right - m_nXMargin, m_nYMargin);
}

void DrawRBTreeMap::_DrawNode(CDC *pDC, Node *p, int x1, int x2, int y)
{
	if (p != 0)
	{
		_DrawNode(pDC, p->pLeft, x1, (x1+x2)/2, y + m_nDY);
		
		// 노드를 그림 
		CSize size = pDC->GetOutputTextExtent(CString((const char*)p->data));
		CRect rt((x1+x2)/2 - size.cx/2, y - size.cy/2, (x1+x2)/2 + size.cx/2, y + size.cy/2);

		CPen pen, *oldpen;
		if (p->Red) {
			pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			pDC->SetTextColor(RGB(255, 0, 0));
		} else {
			pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		oldpen = pDC->SelectObject(&pen);

		CRect rt2 = rt;
		rt2.InflateRect(4, 2);
		pDC->Ellipse(&rt2);

		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(CString((const char*)p->data), &rt, DT_CENTER | DT_VCENTER);

		pDC->SelectObject(oldpen);
		pen.DeleteObject();

		_DrawNode(pDC, p->pRight, (x1+x2)/2, x2, y + m_nDY);
	} 
}

void DrawRBTreeMap::_DrawLink(CDC *pDC, Node *p, int x1, int x2, int y)
{
	if (p != 0)
	{
		// parent로부터 현재 위치로 선을 그린다. 
		pDC->LineTo((x1+x2)/2, y);
		_DrawLink(pDC, p->pLeft, x1, (x1+x2)/2, y + m_nDY);

		// 다음을 위해 원위치 한다. 
		pDC->MoveTo((x1+x2)/2, y);
		_DrawLink(pDC, p->pRight, (x1+x2)/2, x2, y + m_nDY);
	} 
}