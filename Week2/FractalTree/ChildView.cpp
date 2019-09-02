// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "FractalTree.h"
#include "ChildView.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(IDM_DRAW_FIXED_TREE, OnDrawFixedTree)
	ON_COMMAND(IDM_DRAW_RANDOM_TREE, OnDrawRandomTree)
	ON_COMMAND(IDM_DRAW_COLOR_TREE, OnDrawColorTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::DrawFixedTree(int x, int y, int nOrder, int nLength, double dAngle, CDC *pDC)
{
	int dx, dy;
	dx = int(nLength * sin(dAngle));
	dy = int(nLength * cos(dAngle));

	pDC->MoveTo(x, y);
	pDC->LineTo(x - dx, y - dy);
	
	if (nOrder > 0)
	{
		DrawFixedTree(x - dx, y - dy, nOrder - 1, int(nLength * 0.8), dAngle + 0.5, pDC);
		DrawFixedTree(x - dx, y - dy, nOrder - 1, int(nLength * 0.8), dAngle - 0.5, pDC);
	}
}

void CChildView::OnDrawFixedTree() 
{
	CDC *pDC = GetDC();

	DrawFixedTree(300, 400, 15, 70, 0.0, pDC);
	
	ReleaseDC(pDC);
}

void CChildView::DrawRandomTree(int x, int y, int nOrder, int nLength, double dAngle, CDC *pDC)
{
	int dx, dy;
	dx = int(nLength * sin(dAngle));
	dy = int(nLength * cos(dAngle));

	pDC->MoveTo(x, y);
	pDC->LineTo(x - dx, y - dy);

	double turn1, turn2, scale;
	turn1 = (double)rand() / (double)RAND_MAX;		// 0.0 ~ 1.0
	turn2 = (double)rand() / (double)RAND_MAX;		// 0.0 ~ 1.0
	scale = (double)rand() / (double)RAND_MAX / 5.0 + 0.7;   // 0.7 ~ 0.9
	
	if (nOrder > 0)
	{
		DrawRandomTree(x - dx, y - dy, nOrder - 1, int(nLength * scale), dAngle + turn1, pDC);
		DrawRandomTree(x - dx, y - dy, nOrder - 1, int(nLength * scale), dAngle - turn2, pDC);
	}
}

void CChildView::DrawColorTree(int x, int y, int nOrder, int nLength, double dAngle, CDC *pDC)
{
	int dx, dy;
	dx = int(nLength * sin(dAngle));
	dy = int(nLength * cos(dAngle));

	// Select Pen
	COLORREF nColor;
	
	int nPenWidth;
	if (nOrder == 0) {
		nPenWidth = 4;
		nLength = 12;
		nColor = RGB(5, 165, 73);
	} else {
		nPenWidth = (nOrder)/4+1;
		nColor = RGB(128, 87, 8);
	}

	CPen *pOldPen;
	CPen pen(PS_SOLID, nPenWidth, nColor);

	pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(x, y);
	pDC->LineTo(x - dx, y - dy);

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	double turn1, turn2, scale;
	turn1 = (double)rand() / (double)RAND_MAX;		// 0.0 ~ 1.0
	turn2 = (double)rand() / (double)RAND_MAX;		// 0.0 ~ 1.0
	scale = (double)rand() / (double)RAND_MAX / 5.0 + 0.7;   // 0.7 ~ 0.9

	if (nOrder > 0)
	{
		DrawColorTree(x - dx, y - dy, nOrder - 1, int(nLength * scale), dAngle + turn1, pDC);
		DrawColorTree(x - dx, y - dy, nOrder - 1, int(nLength * scale), dAngle - turn2, pDC);
	}
}

void CChildView::OnDrawRandomTree() 
{
	CDC *pDC = GetDC();

	DrawRandomTree(300, 400, 15, 70, 0.0, pDC);
	
	ReleaseDC(pDC);
}

void CChildView::OnDrawColorTree() 
{
	CDC *pDC = GetDC();

	DrawColorTree(300, 400, 15, 70, 0.0, pDC);
	
	ReleaseDC(pDC);
}
