// VisualBinTree.h : main header file for the VISUALBINTREE application
//

#if !defined(AFX_VISUALBINTREE_H__63AE80E4_2842_458D_895B_72A7BEDB7FEF__INCLUDED_)
#define AFX_VISUALBINTREE_H__63AE80E4_2842_458D_895B_72A7BEDB7FEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVisualBinTreeApp:
// See VisualBinTree.cpp for the implementation of this class
//

class CVisualBinTreeApp : public CWinApp
{
public:
	CVisualBinTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualBinTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CVisualBinTreeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALBINTREE_H__63AE80E4_2842_458D_895B_72A7BEDB7FEF__INCLUDED_)
