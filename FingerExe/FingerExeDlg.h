
// FingerExeDlg.h : 头文件
//

#pragma once
// CFingerExeDlg 对话框
class CFingerExeDlg : public CDialog
{
// 构造
public:
	CFingerExeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FINGEREXE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	//CZKEM m_zkem;
	//IZKEM *m_pIZkem;
public:
	int OutPutDebug(LPCTSTR lpmsg);
	int m_nComPort;
	int m_nDeviceID;
	afx_msg void OnBnClickedOk();
	int m_nBaudRate;
	CString m_strIP;
	int m_nIPPort;
	afx_msg void OnBnClickedCheck1();
	BOOL m_bUseCom;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
