
// FingerExeDlg.h : ͷ�ļ�
//

#pragma once
// CFingerExeDlg �Ի���
class CFingerExeDlg : public CDialog
{
// ����
public:
	CFingerExeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FINGEREXE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
