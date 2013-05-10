#pragma once

#import "..\\FingerSDK\\zkemkeeper.dll"

class CAdapter
{
public:
	CAdapter(void);
	~CAdapter(void);
	int Create();
	void Release();

	BOOL Connect_Net(LPCTSTR lpnativeAddress,int port);
	BOOL ReadAllGLogData(DWORD dwMachineNumber);
	BOOL GetGeneralLogDataStr ( long dwMachineNumber, long * dwEnrollNumber, long * dwVerifyMode, long * dwInOutMode, BSTR * TimeStr ) ;
	BOOL ClearGLog ( long dwMachineNumber );
	BOOL ReadAllUserID ( long dwMachineNumber );
	BOOL GetAllUserInfo ( long dwMachineNumber, long * dwEnrollNumber, BSTR * Name, BSTR * Password, long * Privilege, VARIANT_BOOL * Enabled ) ;
	BOOL GetUserInfo ( long dwMachineNumber, long dwEnrollNumber, BSTR * Name, BSTR * Password, long * Privilege, VARIANT_BOOL * Enabled ) ;
	BOOL SetUserInfo ( long dwMachineNumber, long dwEnrollNumber, _bstr_t Name, _bstr_t Password, long Privilege, VARIANT_BOOL Enabled ) ;
	BOOL SetUserTmpStr ( long dwMachineNumber, long dwEnrollNumber, long dwFingerIndex, _bstr_t TmpData ) ;
	BOOL GetUserTmpStr ( long dwMachineNumber, long dwEnrollNumber, long dwFingerIndex, BSTR * TmpData, long * TmpLength ) ;
	void Disconnect();
	BOOL CheckConnectStatus();

	void EnableDevice(LONG dwMachineNumber,VARIANT_BOOL Enabled);
	BOOL GetGeneralLogData ( long dwMachineNumber, long * dwTMachineNumber, long * dwEnrollNumber, long * dwEMachineNumber, long * dwVerifyMode, long * dwInOutMode, long * dwYear, long * dwMonth, long * dwDay, long * dwHour, long * dwMinute ,long *dwSecond) ;	

private:
	
	BOOL m_bInit;
	BOOL m_bConnected;
	BOOL m_bTFTMachine;
	int  m_ZKFPVersion;
	zkemkeeper::IZKEMPtr m_pIZKEM;
};
