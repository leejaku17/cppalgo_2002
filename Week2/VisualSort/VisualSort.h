// VisualSort.h : main header file for the VISUALSORT application
//

#if !defined(AFX_VISUALSORT_H__2EC9B9FB_DC22_423C_BE30_B55F6FFBF63F__INCLUDED_)
#define AFX_VISUALSORT_H__2EC9B9FB_DC22_423C_BE30_B55F6FFBF63F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVisualSortApp:
// See VisualSort.cpp for the implementation of this class
//

class CVisualSortApp : public CWinApp
{
public:
	CVisualSortApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualSortApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CVisualSortApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALSORT_H__2EC9B9FB_DC22_423C_BE30_B55F6FFBF63F__INCLUDED_)
