// MScomm.cpp : implementation file
//

#include "stdafx.h"
#include "TestSTC89S52.h"
#include "MScomm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMScomm

CMScomm::CMScomm()
{
	EnableAutomation();
}

CMScomm::~CMScomm()
{
}

void CMScomm::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CMScomm, CWnd)
	//{{AFX_MSG_MAP(CMScomm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CMScomm, CWnd)
	//{{AFX_DISPATCH_MAP(CMScomm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMScomm to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {29A131D1-00EF-4AFA-9E8A-E8DA63ACF3DF}
static const IID IID_IMScomm =
{ 0x29a131d1, 0xef, 0x4afa, { 0x9e, 0x8a, 0xe8, 0xda, 0x63, 0xac, 0xf3, 0xdf } };

BEGIN_INTERFACE_MAP(CMScomm, CWnd)
	INTERFACE_PART(CMScomm, IID_IMScomm, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMScomm message handlers

BEGIN_EVENTSINK_MAP(CMScomm, CWnd)
    //{{AFX_EVENTSINK_MAP(CMScomm)
	ON_EVENT(CMScomm, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMScomm::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	
}
