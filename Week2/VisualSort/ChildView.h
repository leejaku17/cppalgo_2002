// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__9794904B_D43D_487A_A773_6F80D8AF5DA6__INCLUDED_)
#define AFX_CHILDVIEW_H__9794904B_D43D_487A_A773_6F80D8AF5DA6__INCLUDED_

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
	void CopyArray(int a[], int order);
	void FillRandom(int a[], int n);
	void DrawArray(int a[], int n, int order);
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnBubbleSort();
	afx_msg void OnInsertionSort();
	afx_msg void OnSelectionSort();
	afx_msg void OnQuickSort();
	afx_msg void OnHeapSort();
	afx_msg void OnShellSort();
	afx_msg void OnMergeSort();
	afx_msg void OnStraightRadixSort();
	afx_msg void OnRadixExchangeSort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__9794904B_D43D_487A_A773_6F80D8AF5DA6__INCLUDED_)
