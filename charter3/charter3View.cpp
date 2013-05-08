// charter3View.cpp : implementation of the CCharter3View class
//

#include "stdafx.h"
#include "charter3.h"

#include "charter3Doc.h"
#include "charter3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharter3View

IMPLEMENT_DYNCREATE(CCharter3View, CView)

BEGIN_MESSAGE_MAP(CCharter3View, CView)
	//{{AFX_MSG_MAP(CCharter3View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharter3View construction/destruction

CCharter3View::CCharter3View()
{
	// TODO: add construction code here

}

CCharter3View::~CCharter3View()
{
}

BOOL CCharter3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCharter3View drawing

void CCharter3View::OnDraw(CDC* pDC)
{
	CCharter3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCharter3View printing

BOOL CCharter3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCharter3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCharter3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCharter3View diagnostics

#ifdef _DEBUG
void CCharter3View::AssertValid() const
{
	CView::AssertValid();
}

void CCharter3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCharter3Doc* CCharter3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCharter3Doc)));
	return (CCharter3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCharter3View message handlers
