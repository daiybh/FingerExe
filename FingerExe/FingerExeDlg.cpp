
// FingerExeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FingerExe.h"
#include "FingerExeDlg.h"
#include "com_yumt_zksoft_ZKTCP_cpp.h"

#pragma comment(lib,"E:\\workspace\\其他人的\\谢松云\\指纹脱机开发包\\FingerExe\\Release\\zksoftAdapter.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFingerExeDlg 对话框




CFingerExeDlg::CFingerExeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFingerExeDlg::IDD, pParent)
	, m_nComPort(0)
	, m_nDeviceID(0)
	, m_nBaudRate(0)
	, m_strIP(_T("192.168.1.201"))
	, m_nIPPort(4370)
	, m_bUseCom(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFingerExeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nComPort);
	DDX_Text(pDX, IDC_EDIT2, m_nDeviceID);
	DDX_Text(pDX, IDC_EDIT3, m_nBaudRate);
	DDX_Text(pDX, IDC_EDIT4, m_strIP);
	DDX_Text(pDX, IDC_EDIT5, m_nIPPort);
	DDX_Check(pDX, IDC_CHECK1, m_bUseCom);
}

BEGIN_MESSAGE_MAP(CFingerExeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CFingerExeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CFingerExeDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CFingerExeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFingerExeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CFingerExeDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CFingerExeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFingerExeDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_GetUserTmpStr, &CFingerExeDlg::OnBnClickedButtonGetusertmpstr)
END_MESSAGE_MAP()


// CFingerExeDlg 消息处理程序

BOOL CFingerExeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	OnBnClickedCheck1();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFingerExeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFingerExeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFingerExeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFingerExeDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	//	m_zkem.Connect_Net();
	CString ss;
	if(m_bUseCom){
		
		ss.Format(_T("connect_com 没实现"));
		OutPutDebug(ss);
	}
	else
	{
		
		BOOL bRet = ZKTCP::Connect_Net(m_strIP,m_nIPPort);
//		Java_com_yumt_zksoft_ZKTCP_disConnect(NULL,NULL);
		ss.Format(_T("Connect_Net=%d"),bRet);
		OutPutDebug(ss);
	}
}

void CFingerExeDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CWnd *pStac2 = GetDlgItem(IDC_STATIC_2);
	pStac2->ShowWindow(m_bUseCom);
	CWnd *pStac3 = GetDlgItem(IDC_STATIC_3);
	pStac3->ShowWindow(!m_bUseCom);
}

void CFingerExeDlg::OnBnClickedButton4()
{
	DWORD dwMachineNumber = 1;
	/*
	ZKTCP::EnableDevice(dwMachineNumber,FALSE);
	if(!ZKTCP::ReadAllGLogData(dwMachineNumber)){
		OutPutDebug(_T("m_zkem.ReadAllGLogData faild"));

		ZKTCP::EnableDevice(dwMachineNumber,TRUE);
		return;
	}
	long dwEnrollNumber=0;
	long dwVerifyMode=0;
	long dwInOutMode=0;
	BSTR pTimeStr=NULL;
	BOOL bRet =FALSE;
	int i=110;
	int iRetCount = 0;
	do{
		dwEnrollNumber=0;
		dwVerifyMode=0;
		dwInOutMode=0;
		pTimeStr=NULL;
		long dwMachineNumber,  dwTMachineNumber,  dwEnrollNumber,  dwEMachineNumber,  dwVerifyMode, dwInOutMode,
			dwYear,  dwMonth,  dwDay, dwHour,  dwMinute ;
		bRet = ZKTCP::GetGeneralLogData(dwMachineNumber,  
			&dwTMachineNumber,  &dwEnrollNumber,  &dwEMachineNumber,  &dwVerifyMode, &dwInOutMode,
			&dwYear,  &dwMonth,  &dwDay, &dwHour,  &dwMinute);
		if(bRet){
			iRetCount++;
			CString strLog;
			strLog.Format(_T("GetGeneralLogData %d-%d,%d,%d,%d-%d-%d %d:%d\n"),
				dwMachineNumber,dwEnrollNumber,dwVerifyMode,dwInOutMode,
				dwYear,dwMonth,dwDay,dwHour,dwMinute);
			//printf(strLog);
			if(OutPutDebug(strLog)==IDNO)break;
		}
	}while(bRet);
	ZKTCP::EnableDevice(dwMachineNumber,TRUE);
	/**/
	LPCTSTR lpJson = ZKTCP::GetALLGeneralLogData_withJson(dwMachineNumber);
	OutPutDebug(lpJson);
}

void CFingerExeDlg::OnBnClickedButton1()
{
	DWORD dwMachineNumber = 1;
	ZKTCP::EnableDevice(dwMachineNumber,FALSE);
	if(!ZKTCP::ReadAllGLogData(dwMachineNumber)){
		OutPutDebug(_T("m_zkem.ReadAllGLogData faild"));

		ZKTCP::EnableDevice(dwMachineNumber,TRUE);
		return;
	}
	long dwEnrollNumber=0;
	long dwVerifyMode=0;
	long dwInOutMode=0;
	BSTR pTimeStr=NULL;
	BOOL bRet =FALSE;
	//pTimeStr = ::SysAllocString(OLESTR("Test"));
	int i=110;
	int iRetCount = 0;
	do{
		dwEnrollNumber=0;
		dwVerifyMode=0;
		dwInOutMode=0;
		pTimeStr=NULL;
		bRet = ZKTCP::GetGeneralLogDataStr(dwMachineNumber,&(dwEnrollNumber),&dwVerifyMode,&dwInOutMode,&pTimeStr);
		if(bRet){
			iRetCount++;
			CString strLog;
			CString sTimeStr(pTimeStr);
			strLog.Format(_T("retCount=%d dwMachineNumber=%d,&(dwEnrollNumber=%d),&dwVerifyMode=%d,&dwInOutMode=%d,&pTimeStr=%s"),
				iRetCount,dwMachineNumber,(dwEnrollNumber),dwVerifyMode,dwInOutMode,sTimeStr);
			if(OutPutDebug(strLog)==IDNO)break;
		}
	}while(bRet);
	ZKTCP::EnableDevice(dwMachineNumber,TRUE);
}

void CFingerExeDlg::OnBnClickedButton2()
{
	ZKTCP::Disconnect();
}

int CFingerExeDlg::OutPutDebug( LPCTSTR lpmsg )
{
	_tprintf(_T("%s\n"),lpmsg);
	return AfxMessageBox(lpmsg,MB_YESNO);
}

void CFingerExeDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ZKTCP::Disconnect();
	OnCancel();
}

void CFingerExeDlg::OnBnClickedButton3()
{
// 	BOOL bRet = ZKTCP::ReadAllUserID(1);
// 	if(!bRet){
// 		OutPutDebug("ReadAllUserID faild");
// 		return;
// 	}
// 	long  dwEnrollNumber;
// 	BSTR  Name=NULL; BSTR  Password=NULL; long  Privilege; VARIANT_BOOL  Enabled ;
// 	long nRet= 0;
// 	while(ZKTCP::GetAllUserInfo(1, &dwEnrollNumber, &Name, &Password, &Privilege, &Enabled )){
// 		CString ss;
// 		CString ssName(Name);
// 		CString ssPassword(Password);
// 		ss.Format(_T("GetalluserInfo[%d] dwEnrollNumber=%d Privilege=%d Enabled=%d  %x[%s] %x[%s]"),
// 			nRet++,dwEnrollNumber,Privilege, Enabled ,Name,ssName,Password,ssPassword);
// 		OutPutDebug(ss);
// 		SysFreeString(Name);
// 		SysFreeString(Password);
// 	}
// 	
	LPCTSTR lpRet = ZKTCP::GetAllUserInfo_WithJson(1);
	OutPutDebug(lpRet);
}

void CFingerExeDlg::OnBnClickedButtonGetusertmpstr()
{

	BSTR tempData=0;
	long tempDataLen=0;
	for(int i=0;i<10;i++)
	{
		BOOL bRet = ZKTCP::GetUserTmpStr(1,999,i,&tempData,&tempDataLen);
		if(bRet){
			CString strTempData(tempData);
			CString ss;
			ss.Format(_T("%d__%s"),tempDataLen,strTempData);
			OutPutDebug(ss);
		}
	}
}
