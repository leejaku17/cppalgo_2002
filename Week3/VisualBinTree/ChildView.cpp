// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "VisualBinTree.h"
#include "ChildView.h"
#include "DlgNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView


CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(IDM_BINTREE_BALANCE, OnBintreeBalance)
	ON_COMMAND(IDM_BINTREE_INSERT, OnBintreeInsert)
	ON_COMMAND(IDM_BINTREE_REMOVE, OnBintreeRemove)
	ON_COMMAND(IDM_BINTREE_REMOVEALL, OnBintreeRemoveall)
	ON_COMMAND(IDM_HASH_INSERT, OnHashInsert)
	ON_COMMAND(IDM_HASH_REMOVE, OnHashRemove)
	ON_COMMAND(IDM_HASH_REMOVEALL, OnHashRemoveall)
	ON_COMMAND(IDM_CHAIN_INSERT, OnChainInsert)
	ON_COMMAND(IDM_CHAIN_REMOVE, OnChainRemove)
	ON_COMMAND(IDM_CHAIN_REMOVEALL, OnChainRemoveall)
	ON_COMMAND(IDM_RADIXTREE_INSERT, OnRadixtreeInsert)
	ON_COMMAND(IDM_RADIXTREE_REMOVE, OnRadixtreeRemove)
	ON_COMMAND(IDM_RADIXTREE_REMOVEALL, OnRadixtreeRemoveall)
	ON_COMMAND(IDM_RADIXTRIE_INSERT, OnRadixtrieInsert)
	ON_COMMAND(IDM_RADIXTRIE_REMOVE, OnRadixtrieRemove)
	ON_COMMAND(IDM_RADIXTRIE_REMOVEALL, OnRadixtrieRemoveall)
	ON_COMMAND(IDM_BTREE_INSERT, OnBtreeInsert)
	ON_COMMAND(IDM_BTREE_REMOVE, OnBtreeRemove)
	ON_COMMAND(IDM_BTREE_REMOVEALL, OnBtreeRemoveall)
	ON_COMMAND(IDM_BTREE_BULKINSERT, OnBtreeBulkinsert)
	ON_COMMAND(IDM_RBTREE_INSERT, OnRbtreeInsert)
	ON_COMMAND(IDM_RBTREE_REMOVE, OnRbtreeRemove)
	ON_COMMAND(IDM_RBTREE_REMOVEALL, OnRbtreeRemoveall)
	ON_COMMAND(IDM_234_INSERT, On234Insert)
	ON_COMMAND(IDM_234_REMOVE, On234Remove)
	ON_COMMAND(IDM_234_REMOVEALL, On234Removeall)
	ON_COMMAND(IDM_RBTREE_BULKINSERT, OnRbtreeBulkinsert)
	ON_COMMAND(IDM_234TREE_BULKINSERT, On234treeBulkinsert)
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

	CRect rt;
	GetClientRect(&rt);

	if (m_strWhich == "DrawBinTree")
		m_bintree.Draw(&dc, rt, true);
	else if (m_strWhich == "DrawHashMap")
		m_hash.Draw(&dc);
	else if (m_strWhich == "DrawChainMap")
		m_chain.Draw(&dc);
	else if (m_strWhich == "DrawRadixTreeMap")
		m_radixtree.Draw(&dc, rt, true);
	else if (m_strWhich == "DrawRadixTrieMap")
		m_radixtrie.Draw(&dc, rt, true);
	else if (m_strWhich == "DrawBTreeMap")
		m_btree.Draw(&dc, rt);
	else if (m_strWhich == "Draw234Tree")
		m_234tree.Draw(&dc, rt);
	else if (m_strWhich == "DrawRBTreeMap")
		m_rbtree.Draw(&dc, rt);
}


void CChildView::OnBintreeBalance() 
{
	m_strWhich = "DrawBinTree";
	m_bintree.Balance();
	Invalidate();	
}

void CChildView::OnBintreeInsert() 
{
	m_strWhich = "DrawBinTree";
	CDlgNode dlg;
	
	if (IDOK == dlg.DoModal())
	{
		m_bintree.Insert((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnBintreeRemove() 
{
	m_strWhich = "DrawBinTree";
	CDlgNode dlg;
	
	if (IDOK == dlg.DoModal())
	{
		m_bintree.Remove((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnBintreeRemoveall() 
{
	m_strWhich = "DrawBinTree";
	m_bintree.RemoveAll();
	Invalidate();
}

void CChildView::OnHashInsert() 
{
	m_strWhich = "DrawHashMap";

	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_hash.Insert((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnHashRemove() 
{
	m_strWhich = "DrawHashMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_hash.Remove((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnHashRemoveall() 
{
	m_strWhich = "DrawHashMap";
	m_hash.RemoveAll();
	Invalidate();
}

void CChildView::OnChainInsert() 
{
	m_strWhich = "DrawChainMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_chain.Insert((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnChainRemove() 
{
	m_strWhich = "DrawChainMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_chain.Remove((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnChainRemoveall() 
{
	m_strWhich = "DrawChainMap";
	m_chain.RemoveAll();
	Invalidate();
}

void CChildView::OnRadixtreeInsert() 
{
	m_strWhich = "DrawRadixTreeMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_radixtree.Insert(dlg.m_strValue[0]);
	}
	Invalidate();
}

void CChildView::OnRadixtreeRemove() 
{
	m_strWhich = "DrawRadixTreeMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_radixtree.Remove(dlg.m_strValue[0]);
	}
	Invalidate();
}

void CChildView::OnRadixtreeRemoveall() 
{
	m_strWhich = "DrawRadixTreeMap";
	m_radixtree.RemoveAll();
	Invalidate();
}

void CChildView::OnRadixtrieInsert() 
{
	m_strWhich = "DrawRadixTrieMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_radixtrie.Insert(dlg.m_strValue[0]);
	}
	Invalidate();
}

void CChildView::OnRadixtrieRemove() 
{
	m_strWhich = "DrawRadixTrieMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_radixtrie.Remove(dlg.m_strValue[0]);
	}
	Invalidate();
}

void CChildView::OnRadixtrieRemoveall() 
{
	m_strWhich = "DrawRadixTrieMap";
	m_radixtrie.RemoveAll();
	Invalidate();
}

void CChildView::OnBtreeInsert() 
{
	m_strWhich = "DrawBTreeMap";

	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_btree.Insert((const char*)dlg.m_strValue);
	}

	Invalidate();
}

void CChildView::OnBtreeRemove() 
{
	m_strWhich = "DrawBTreeMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_btree.Remove((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnBtreeRemoveall() 
{
	m_strWhich = "DrawBTreeMap";
	m_btree.RemoveAll();
	Invalidate();
}

void CChildView::OnBtreeBulkinsert() 
{
	m_strWhich = "DrawBTreeMap";
	for (int i = 'A'; i <= 'Z'; i++)
		m_btree.Insert((char)i);
	Invalidate();	
}

void CChildView::OnRbtreeInsert() 
{
	m_strWhich = "DrawRBTreeMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_rbtree.Insert((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnRbtreeRemove() 
{
	m_strWhich = "DrawRBTreeMap";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_rbtree.Remove((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::OnRbtreeRemoveall() 
{
	m_strWhich = "DrawRBTreeMap";
	m_rbtree.RemoveAll();
	
	Invalidate();
}

void CChildView::On234Insert() 
{
	m_strWhich = "Draw234Tree";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_234tree.Insert((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::On234Remove() 
{
	m_strWhich = "Draw234Tree";
	CDlgNode dlg;
	if (IDOK == dlg.DoModal())
	{
		m_234tree.Remove((const char*)dlg.m_strValue);
	}
	Invalidate();
}

void CChildView::On234Removeall() 
{
	m_strWhich = "Draw234Tree";
	m_234tree.RemoveAll();
	Invalidate();
}

void CChildView::OnRbtreeBulkinsert() 
{
	m_strWhich = "DrawRBTreeMap";
	for (int i = 'A'; i <= 'Z'; i++)
		m_rbtree.Insert((char)i);
	Invalidate();	
}

void CChildView::On234treeBulkinsert() 
{
	m_strWhich = "Draw234Tree";
	for (int i = 'A'; i <= 'Z'; i++)
		m_234tree.Insert((char)i);
	Invalidate();	
}
