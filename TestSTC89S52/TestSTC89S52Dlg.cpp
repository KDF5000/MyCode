// TestSTC89S52Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestSTC89S52.h"
#include "TestSTC89S52Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSTC89S52Dlg dialog

CTestSTC89S52Dlg::CTestSTC89S52Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSTC89S52Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestSTC89S52Dlg)
	m_strPXDdata = _T("");
	status = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSTC89S52Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSTC89S52Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_strPXDdata);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestSTC89S52Dlg, CDialog)
	//{{AFX_MSG_MAP(CTestSTC89S52Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONTROL, OnControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSTC89S52Dlg message handlers

BOOL CTestSTC89S52Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//*************************************************************************************
	if(m_ctrlComm.GetPortOpen())
		m_ctrlComm.SetPortOpen(false);


	m_ctrlComm.SetCommPort(7);
	m_ctrlComm.SetInBufferSize(1024);
	m_ctrlComm.SetOutBufferSize(1024);
	m_ctrlComm.SetSettings("9600,n,8,1");
	m_ctrlComm.SetInputMode(1);  //1表示以二进制方式获取数据

	m_ctrlComm.SetRThreshold(1);  //1表示当缓冲区中有多于或者等于1个数据时产生一个oncomm
								//事件表示接受数据
	m_ctrlComm.SetInputLen(0);  //设置当前数据区长度为0	

	if(!m_ctrlComm.GetPortOpen())
		m_ctrlComm.SetPortOpen(true);  //打开串口
	else
		//AfxMessageBox("不能打开串口");
		m_ctrlComm.SetOutBufferCount(0);
	m_ctrlComm.GetInput();
//*******************************************************************************************
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestSTC89S52Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestSTC89S52Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestSTC89S52Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CTestSTC89S52Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTestSTC89S52Dlg)
	ON_EVENT(CTestSTC89S52Dlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTestSTC89S52Dlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	m_strPXDdata = _T("");
	VARIANT  varint_inp;
	COleSafeArray safeArray_inp;
	LONG len,k;
	BYTE rxDate[2048];
	CString strTemp;
	if(m_ctrlComm.GetCommEvent()==2)    //等于2表示缓冲区有数据
	{
		varint_inp = m_ctrlComm.GetInput();
		safeArray_inp = varint_inp;
		len  = safeArray_inp.GetOneDimSize();
		for(k = 0;k<len;k++)
			safeArray_inp.GetElement(&k,rxDate+k);
		for(k = 0;k<len;k++)
		{
			BYTE temp = *(char *)(rxDate+k);
			strTemp.Format("%c",temp);
			m_strPXDdata += temp;
		}
	}
	UpdateData(FALSE);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}


void CTestSTC89S52Dlg::OnControl() 
{
	// TODO: Add your control notification handler code here
	int i,Count;
	CString m_SendData;
	m_SendData="C"; 
	Count=m_SendData.GetLength();
	CByteArray m_Array;

	m_Array.RemoveAll();
	m_Array.SetSize(Count);

	for(i=0;i<Count;i++)
		m_Array.SetAt(i,m_SendData[i]);
	m_ctrlComm.SetOutput(COleVariant(m_Array));
}
