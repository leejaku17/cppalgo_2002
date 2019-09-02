// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__88024287_7478_48F2_A8F7_1D5746173BED__INCLUDED_)
#define AFX_CHILDVIEW_H__88024287_7478_48F2_A8F7_1D5746173BED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawRandomTree(int x, int y, int nOrder, int nLength, double dAngle, CDC *pDC);
	void DrawFixedTree(int x, int y, int nOrder, int nLength, double dAngle, CDC *pDC);
	void DrawColorTree(int x, int y, int nOrder, int nLength, double dAngle, CDC *pDC);

	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnDrawFixedTree();
	afx_msg void OnDrawRandomTree();
	afx_msg void OnDrawColorTree();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__88024287_7478_48F2_A8F7_1D5746173BED__INCLUDED_)
