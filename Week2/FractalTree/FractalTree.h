// FractalTree.h : main header file for the FRACTALTREE application
//

#if !defined(AFX_FRACTALTREE_H__BC676F87_657A_4E90_AB5E_4B8E197964C8__INCLUDED_)
#define AFX_FRACTALTREE_H__BC676F87_657A_4E90_AB5E_4B8E197964C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFractalTreeApp:
// See FractalTree.cpp for the implementation of this class
//

class CFractalTreeApp : public CWinApp
{
public:
	CFractalTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFractalTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CFractalTreeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTALTREE_H__BC676F87_657A_4E90_AB5E_4B8E197964C8__INCLUDED_)
