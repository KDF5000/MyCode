// charter3View.h : interface of the CCharter3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARTER3VIEW_H__0A70AD38_13EB_48C4_B6DE_500ECCB74058__INCLUDED_)
#define AFX_CHARTER3VIEW_H__0A70AD38_13EB_48C4_B6DE_500ECCB74058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCharter3View : public CView
{
protected: // create from serialization only
	CCharter3View();
	DECLARE_DYNCREATE(CCharter3View)

// Attributes
public:
	CCharter3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCharter3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCharter3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCharter3View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in charter3View.cpp
inline CCharter3Doc* CCharter3View::GetDocument()
   { return (CCharter3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTER3VIEW_H__0A70AD38_13EB_48C4_B6DE_500ECCB74058__INCLUDED_)
