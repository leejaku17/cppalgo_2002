#include "DrawChainMap.h"

void DrawChainMap::Draw(CDC *pDC)
{
	for (int i = 0; i < m_nArraySize; i++)
	{
		CRect rt(m_nXMargin, m_nYMargin + i*m_nHeight, m_nXMargin + m_nWidth, m_nYMargin + (i+1)*m_nHeight +1);
		pDC->Rectangle(&rt);

		CString strText;
		strText.Format("%2d", i);

		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strText, &rt, DT_VCENTER | DT_CENTER);

		// Draw Link

		CRect rtText;
		int offset = 0;
		cppalgo::POS pos = m_pArray[i].GetHeadPosition();
		while (pos) 
		{
			cppalgo::String str = m_pArray[i].GetNext(pos);
			CSize sz = pDC->GetOutputTextExtent((const char*)str);
			
			pDC->MoveTo(rt.right + offset, (rt.top + rt.bottom)/2);
			pDC->LineTo(rt.right + offset + m_nLinkLen, (rt.top + rt.bottom)/2);

			rtText = CRect(rt.right + offset + m_nLinkLen, rt.top, rt.right + offset + sz.cx + 4 + m_nLinkLen, rt.bottom);
			pDC->Ellipse(&rtText);
			pDC->DrawText((const char*)str, &rtText, DT_VCENTER | DT_CENTER);

			offset += m_nLinkLen + sz.cx + 4;
		}
	}
}