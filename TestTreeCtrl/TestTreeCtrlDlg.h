// TestTreeCtrlDlg.h : header file
//

#if !defined(AFX_TESTTREECTRLDLG_H__ECD86660_6B16_440F_91CD_CE636FA5D0DE__INCLUDED_)
#define AFX_TESTTREECTRLDLG_H__ECD86660_6B16_440F_91CD_CE636FA5D0DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestTreeCtrlDlg dialog

class CTestTreeCtrlDlg : public CDialog
{
// Construction
public:
	CTestTreeCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestTreeCtrlDlg)
	enum { IDD = IDD_TESTTREECTRL_DIALOG };
	CTreeCtrl	m_bulidingT;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTreeCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestTreeCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTREECTRLDLG_H__ECD86660_6B16_440F_91CD_CE636FA5D0DE__INCLUDED_)
