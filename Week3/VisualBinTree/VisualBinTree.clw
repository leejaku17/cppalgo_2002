; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgNode
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VisualBinTree.h"
LastPage=0

ClassCount=5
Class1=CVisualBinTreeApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class2=CChildView
Class5=CDlgNode
Resource3=IDD_NODE

[CLS:CVisualBinTreeApp]
Type=0
HeaderFile=VisualBinTree.h
ImplementationFile=VisualBinTree.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=VisualBinTree.cpp
ImplementationFile=VisualBinTree.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=IDM_BINTREE_INSERT
Command3=IDM_BINTREE_REMOVE
Command4=IDM_BINTREE_BALANCE
Command5=IDM_BINTREE_REMOVEALL
Command6=IDM_HASH_INSERT
Command7=IDM_HASH_REMOVE
Command8=IDM_HASH_REMOVEALL
Command9=IDM_CHAIN_INSERT
Command10=IDM_CHAIN_REMOVE
Command11=IDM_CHAIN_REMOVEALL
Command12=IDM_RADIXTREE_INSERT
Command13=IDM_RADIXTREE_REMOVE
Command14=IDM_RADIXTREE_REMOVEALL
Command15=IDM_RADIXTRIE_INSERT
Command16=IDM_RADIXTRIE_REMOVE
Command17=IDM_RADIXTRIE_REMOVEALL
Command18=IDM_BTREE_INSERT
Command19=IDM_BTREE_REMOVE
Command20=IDM_BTREE_REMOVEALL
Command21=IDM_BTREE_BULKINSERT
Command22=IDM_234_INSERT
Command23=IDM_234_REMOVE
Command24=IDM_234_REMOVEALL
Command25=IDM_234TREE_BULKINSERT
Command26=IDM_RBTREE_INSERT
Command27=IDM_RBTREE_REMOVE
Command28=IDM_RBTREE_REMOVEALL
Command29=IDM_RBTREE_BULKINSERT
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[DLG:IDD_NODE]
Type=1
Class=CDlgNode
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_VALUE,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CDlgNode]
Type=0
HeaderFile=DlgNode.h
ImplementationFile=DlgNode.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgNode

