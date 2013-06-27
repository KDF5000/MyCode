// bulidTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TestTreeCtrl.h"
#include "bulidTreeCtrl.h"
#include "TestTreeCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// bulidTreeCtrl

bulidTreeCtrl::bulidTreeCtrl()
{
}

bulidTreeCtrl::~bulidTreeCtrl()
{
}
void bulidTreeCtrl::initTree()
{
	//CTestTreeCtrlDlg test = new CTestTreeCtrlDlg();
	HTREEITEM hItem;
	hItem = CTestTreeCtrlDlg::m_bulidingT.InsertItem("东九",TVI_ROOT);
	//在根结点上添加Parent1
	hItem = CTestTreeCtrlDlg::m_bulidingT.InsertItem("东十二",TVI_ROOT,hItem);
	hItem = CTestTreeCtrlDlg::m_bulidingT.InsertItem("西五",TVI_ROOT,hItem);
	hItem = CTestTreeCtrlDlg::m_bulidingT.InsertItem("西十二",TVI_ROOT,hItem);
}

BEGIN_MESSAGE_MAP(bulidTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(bulidTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// bulidTreeCtrl message handlers
