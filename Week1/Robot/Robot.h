// Robot.h : main header file for the ROBOT application
//

#if !defined(AFX_ROBOT_H__FA370409_ED16_4696_B2ED_90523BF0E622__INCLUDED_)
#define AFX_ROBOT_H__FA370409_ED16_4696_B2ED_90523BF0E622__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRobotApp:
// See Robot.cpp for the implementation of this class
//

class CRobotApp : public CWinApp
{
public:
	CRobotApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobotApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CRobotApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOT_H__FA370409_ED16_4696_B2ED_90523BF0E622__INCLUDED_)
