// TestSTC89S52.h : main header file for the TESTSTC89S52 application
//

#if !defined(AFX_TESTSTC89S52_H__ED2EF483_0DB4_4D02_B675_2C653D457BF2__INCLUDED_)
#define AFX_TESTSTC89S52_H__ED2EF483_0DB4_4D02_B675_2C653D457BF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestSTC89S52App:
// See TestSTC89S52.cpp for the implementation of this class
//

class CTestSTC89S52App : public CWinApp
{
public:
	CTestSTC89S52App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSTC89S52App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestSTC89S52App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSTC89S52_H__ED2EF483_0DB4_4D02_B675_2C653D457BF2__INCLUDED_)
