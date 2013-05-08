// charter3.h : main header file for the CHARTER3 application
//

#if !defined(AFX_CHARTER3_H__4B819CCE_B193_45DD_8A40_635B475E35CC__INCLUDED_)
#define AFX_CHARTER3_H__4B819CCE_B193_45DD_8A40_635B475E35CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCharter3App:
// See charter3.cpp for the implementation of this class
//

class CCharter3App : public CWinApp
{
public:
	CCharter3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharter3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCharter3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTER3_H__4B819CCE_B193_45DD_8A40_635B475E35CC__INCLUDED_)
