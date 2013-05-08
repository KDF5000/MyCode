#if !defined(AFX_BULIDTREECTRL_H__843280CE_EDF9_4EFB_8F35_E3B0F2FCFF16__INCLUDED_)
#define AFX_BULIDTREECTRL_H__843280CE_EDF9_4EFB_8F35_E3B0F2FCFF16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// bulidTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// bulidTreeCtrl window

class bulidTreeCtrl : public CTreeCtrl
{
// Construction
public:
	bulidTreeCtrl();

// Attributes
public:

// Operations
public:
	void initTree();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(bulidTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~bulidTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(bulidTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BULIDTREECTRL_H__843280CE_EDF9_4EFB_8F35_E3B0F2FCFF16__INCLUDED_)
