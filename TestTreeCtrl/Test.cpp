// Test.cpp : implementation file
//

#include "stdafx.h"
#include "TestTreeCtrl.h"
#include "Test.h"
#include "TestTreeCtrlDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Test

Test::Test()
{
	
	CTestTreeCtrlDlg test = new CTestTreeCtrlDlg();
	HTREEITEM hItem;
	hItem = test.m_bulidingT.InsertItem("东九",TVI_ROOT);
	//在根结点上添加Parent1
	hItem = test.m_bulidingT.InsertItem("东十二",TVI_ROOT,hItem);
	hItem = test.m_bulidingT.InsertItem("西五",TVI_ROOT,hItem);
	hItem = test.m_bulidingT.InsertItem("西十二",TVI_ROOT,hItem);
}

Test::~Test()
{
}


BEGIN_MESSAGE_MAP(Test, CTreeCtrl)
	//{{AFX_MSG_MAP(Test)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Test message handlers
