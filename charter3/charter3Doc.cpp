// charter3Doc.cpp : implementation of the CCharter3Doc class
//

#include "stdafx.h"
#include "charter3.h"

#include "charter3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCharter3Doc

IMPLEMENT_DYNCREATE(CCharter3Doc, CDocument)

BEGIN_MESSAGE_MAP(CCharter3Doc, CDocument)
	//{{AFX_MSG_MAP(CCharter3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharter3Doc construction/destruction

CCharter3Doc::CCharter3Doc()
{
	// TODO: add one-time construction code here

}

CCharter3Doc::~CCharter3Doc()
{
}

BOOL CCharter3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCharter3Doc serialization

void CCharter3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCharter3Doc diagnostics

#ifdef _DEBUG
void CCharter3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCharter3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCharter3Doc commands
