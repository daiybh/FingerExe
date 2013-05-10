
// FingerExeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FingerExe.h"
#include "FingerExeDlg.h"
#include "com_yumt_zksoft_ZKTCP_cpp.h"

#pragma comment(lib,"E:\\workspace\\�����˵�\\л����\\ָ���ѻ�������\\FingerExe\\Release\\zksoftAdapter.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFingerExeDlg �Ի���




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


// CFingerExeDlg ��Ϣ�������

BOOL CFingerExeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	OnBnClickedCheck1();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFingerExeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		
		ss.Format(_T("connect_com ûʵ��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
