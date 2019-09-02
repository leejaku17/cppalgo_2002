#include "DrawHashMap.h"

void DrawHashMap::Draw(CDC *pDC)
{
	for (int i = 0; i < m_nArraySize; i++)
	{
		CRect rt(m_nXMargin, m_nYMargin + i*m_nHeight, m_nXMargin + m_nWidth, m_nYMargin + (i+1)*m_nHeight +1);
		pDC->Rectangle(&rt);

		CString strContent;
		if (m_pArray[i].status == AVAIL)
			strContent = m_pArray[i].data;
		else if (m_pArray[i].status == EMPTY)
			strContent = "<EMPTY>";
		else if (m_pArray[i].status == DELETED)
			strContent = "<DELETED>";

		CString strText;
		if (m_pArray[i].status == AVAIL)
			strText.Format("%2d : %s = %d", i, (const char*)strContent, m_hash.hash(m_pArray[i].data) % m_nArraySize);
		else
			strText.Format("%2d : %s", i, (const char*)strContent);

		rt.left += 10;
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strText, &rt, DT_VCENTER);
	}
}