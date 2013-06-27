#if !defined(AFX_MSCOMM_H__BB6077E5_38F3_4BC4_8859_783E27DEBFC8__INCLUDED_)
#define AFX_MSCOMM_H__BB6077E5_38F3_4BC4_8859_783E27DEBFC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MScomm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMScomm window

class CMScomm : public CWnd
{
// Construction
public:
	CMScomm();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMScomm)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMScomm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMScomm)
	afx_msg void OnOnCommMscomm1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMScomm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSCOMM_H__BB6077E5_38F3_4BC4_8859_783E27DEBFC8__INCLUDED_)
