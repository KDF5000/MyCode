// TestSTC89S52Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm1.h"
//}}AFX_INCLUDES

#if !defined(AFX_TESTSTC89S52DLG_H__62227D33_1896_4D72_93C7_15851BB91951__INCLUDED_)
#define AFX_TESTSTC89S52DLG_H__62227D33_1896_4D72_93C7_15851BB91951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestSTC89S52Dlg dialog

class CTestSTC89S52Dlg : public CDialog
{
// Construction
public:
	CTestSTC89S52Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestSTC89S52Dlg)
	enum { IDD = IDD_TESTSTC89S52_DIALOG };
	CString	m_strPXDdata;
	CMSComm	m_ctrlComm;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSTC89S52Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	int status;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestSTC89S52Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnControl();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSTC89S52DLG_H__62227D33_1896_4D72_93C7_15851BB91951__INCLUDED_)
