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
	hItem = test.m_bulidingT.InsertItem("����",TVI_ROOT);
	//�ڸ���������Parent1
	hItem = test.m_bulidingT.InsertItem("��ʮ��",TVI_ROOT,hItem);
	hItem = test.m_bulidingT.InsertItem("����",TVI_ROOT,hItem);
	hItem = test.m_bulidingT.InsertItem("��ʮ��",TVI_ROOT,hItem);
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
