// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__C6187D55_02B3_47B0_875F_3624720427B5__INCLUDED_)
#define AFX_CHILDVIEW_H__C6187D55_02B3_47B0_875F_3624720427B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBinTree.h"
#include "DrawHashMap.h"
#include "DrawChainMap.h"
#include "DrawRadixTreeMap.h"
#include "DrawRadixTrieMap.h"
#include "DrawBTreeMap.h"
#include "DrawRBTreeMap.h"

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView() : m_hash(StringHash(), 23), m_chain(StringHash(), 23), m_btree(5), m_234tree(3) { m_strWhich = "DrawBinTree"; }

// Attributes
public:
	CString m_strWhich;
	DrawBinTree m_bintree;
	DrawHashMap m_hash;
	DrawChainMap m_chain;
	DrawRadixTreeMap m_radixtree;
	DrawRadixTrieMap m_radixtrie;
	DrawBTreeMap m_btree;
	DrawBTreeMap m_234tree;
	DrawRBTreeMap m_rbtree;

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
	afx_msg void OnBintreeBalance();
	afx_msg void OnBintreeInsert();
	afx_msg void OnBintreeRemove();
	afx_msg void OnBintreeRemoveall();
	afx_msg void OnHashInsert();
	afx_msg void OnHashRemove();
	afx_msg void OnHashRemoveall();
	afx_msg void OnChainInsert();
	afx_msg void OnChainRemove();
	afx_msg void OnChainRemoveall();
	afx_msg void OnRadixtreeInsert();
	afx_msg void OnRadixtreeRemove();
	afx_msg void OnRadixtreeRemoveall();
	afx_msg void OnRadixtrieInsert();
	afx_msg void OnRadixtrieRemove();
	afx_msg void OnRadixtrieRemoveall();
	afx_msg void OnBtreeInsert();
	afx_msg void OnBtreeRemove();
	afx_msg void OnBtreeRemoveall();
	afx_msg void OnBtreeBulkinsert();
	afx_msg void OnRbtreeInsert();
	afx_msg void OnRbtreeRemove();
	afx_msg void OnRbtreeRemoveall();
	afx_msg void On234Insert();
	afx_msg void On234Remove();
	afx_msg void On234Removeall();
	afx_msg void OnRbtreeBulkinsert();
	afx_msg void On234treeBulkinsert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__C6187D55_02B3_47B0_875F_3624720427B5__INCLUDED_)
