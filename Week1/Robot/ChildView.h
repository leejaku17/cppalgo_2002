// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__25555AA6_F999_4255_8B02_B72C59567B7C__INCLUDED_)
#define AFX_CHILDVIEW_H__25555AA6_F999_4255_8B02_B72C59567B7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window
#include "Maze.h"

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	// 미로 객체를 포함. 
	CMaze	m_maze;

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
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnProbeMaze();
	afx_msg void OnShortestPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__25555AA6_F999_4255_8B02_B72C59567B7C__INCLUDED_)
