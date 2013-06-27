// charter3Doc.h : interface of the CCharter3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARTER3DOC_H__61D4745D_2EF3_407D_917C_2CBFC1D21328__INCLUDED_)
#define AFX_CHARTER3DOC_H__61D4745D_2EF3_407D_917C_2CBFC1D21328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCharter3Doc : public CDocument
{
protected: // create from serialization only
	CCharter3Doc();
	DECLARE_DYNCREATE(CCharter3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharter3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCharter3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCharter3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTER3DOC_H__61D4745D_2EF3_407D_917C_2CBFC1D21328__INCLUDED_)
