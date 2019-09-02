// DlgNode.cpp : implementation file
//

#include "stdafx.h"
#include "VisualBinTree.h"
#include "DlgNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNode dialog


CDlgNode::CDlgNode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNode)
	m_strValue = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNode)
	DDX_Text(pDX, IDC_VALUE, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNode, CDialog)
	//{{AFX_MSG_MAP(CDlgNode)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNode message handlers
