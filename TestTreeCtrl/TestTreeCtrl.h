// TestTreeCtrl.h : main header file for the TESTTREECTRL application
//

#if !defined(AFX_TESTTREECTRL_H__0569228A_7920_4EDB_B736_F75A8759E89A__INCLUDED_)
#define AFX_TESTTREECTRL_H__0569228A_7920_4EDB_B736_F75A8759E89A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestTreeCtrlApp:
// See TestTreeCtrl.cpp for the implementation of this class
//

class CTestTreeCtrlApp : public CWinApp
{
public:
	CTestTreeCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTreeCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestTreeCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTREECTRL_H__0569228A_7920_4EDB_B736_F75A8759E89A__INCLUDED_)
