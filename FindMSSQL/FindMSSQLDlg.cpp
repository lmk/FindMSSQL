
// FindMSSQLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindMSSQL.h"
#include "FindMSSQLDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFindMSSQLDlg dialog



CFindMSSQLDlg::CFindMSSQLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FINDMSSQL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindMSSQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFindMSSQLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFindMSSQLDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFindMSSQLDlg message handlers

BOOL CFindMSSQLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	SetDlgItemText(IDC_IPADDRESS, TEXT("127.0.0.1"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFindMSSQLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFindMSSQLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFindMSSQLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool GetMSSQLInfo(CString &info, int timeout_sec, CString ip = _T(""))
{
	char buf[1024] = { 0, };

	CSocket socket;
	UINT port = 0;
	UINT size = 0;

	socket.Create(0, SOCK_DGRAM);

	// broadcast
	if (ip.IsEmpty())
	{
		int flag = 1, flag_size = sizeof(flag);
		socket.SetSockOpt(SO_BROADCAST, &flag, flag_size);
	}

	buf[0] = 0x02;
	if (ip.IsEmpty())
	{
		// broadcast
		socket.SendTo(buf, sizeof(buf[0]), 1434);
	}
	else
	{
		socket.SendTo(buf, sizeof(buf[0]), 1434, ip);
	}

	struct timeval tm;
	tm.tv_sec = timeout_sec;
	tm.tv_usec = 0;

	while (1)
	{
		fd_set rfs;
		FD_ZERO(&rfs);
		FD_SET(socket.m_hSocket, &rfs);

		int select_ret = select(socket.m_hSocket + 1, &rfs, NULL, NULL, &tm);

		if (select_ret == 0) break;					// timeout
		else if (select_ret <= 0) return false;		// network error

		size = socket.ReceiveFrom(buf, sizeof(buf), ip, port);
		if (size <= 3) return false;

		info.AppendFormat(TEXT("%S"), &buf[3]);
	}

	info.Replace(_T(";;"), _T("\r\n"));

	return true;
}

void CFindMSSQLDlg::OnBnClickedOk()
{
	CButton* pButton = (CButton*)GetDlgItem(IDC_CHECK_BROADCAST);

	CString ip, msg;

	if (pButton->GetCheck() == BST_CHECKED)
	{
		GetMSSQLInfo(msg, 3);
	}
	else
	{
		GetDlgItemText(IDC_IPADDRESS, ip);
		GetMSSQLInfo(msg, 1, ip);
	}

	msg.Append(_T("\r\n"));

	CString result;
	GetDlgItemText(IDC_EDIT_RESULT, result);
	result.AppendFormat(TEXT("%s"), msg);
	SetDlgItemText(IDC_EDIT_RESULT, result);
}
