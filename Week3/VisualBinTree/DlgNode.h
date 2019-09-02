#if !defined(AFX_DLGNODE_H__AAC83678_AC08_4385_ADF0_9D5E28C27906__INCLUDED_)
#define AFX_DLGNODE_H__AAC83678_AC08_4385_ADF0_9D5E28C27906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNode dialog

class CDlgNode : public CDialog
{
// Construction
public:
	CDlgNode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNode)
	enum { IDD = IDD_NODE };
	CString	m_strValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNode)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNODE_H__AAC83678_AC08_4385_ADF0_9D5E28C27906__INCLUDED_)
