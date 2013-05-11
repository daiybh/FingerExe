#include "StdAfx.h"
#include "Adapter.h"

CAdapter::CAdapter(void)
{
	m_bInit=FALSE;
	m_bConnected = FALSE;
	m_bTFTMachine=FALSE;
	m_ZKFPVersion = 9;
}

CAdapter::~CAdapter(void)
{
}

BOOL CAdapter::CheckConnectStatus()
{
	if(!m_bConnected){
		//outPrintf("Error:Had not Connect the devices\n");
		return FALSE;
	}
	return TRUE;
}
int CAdapter::Create()
{
	m_bInit = FALSE;
	try{
		HRESULT hr = m_pIZKEM.CreateInstance(__uuidof(zkemkeeper::CZKEM));
		if(FAILED(hr)){
			CString s;
			s.Format(_T("m_pIZKEM.CreateInstance faild --%d"),GetLastError());
			printf(s);	
		}else{
			m_bInit = TRUE;
		}

	}catch(...){
		CString s;
		s.Format(_T("m_pIZKEM.CreateInstance Exception --%d"),GetLastError());
		printf(s);	
	}
	return m_bInit?m_pIZKEM:NULL;
}

void CAdapter::Release()
{
	if(m_bInit){
		try{
			m_pIZKEM.Release();
			m_bInit=FALSE;
		}catch(_com_error &e){
			printf("m_pIZKEM.Release() _com_error exception nCode=%d  %s\n",e.Error(),e.ErrorMessage());
		}catch(...){
			printf("m_pIZKEM.Release() exception\n");
		}

	}
}

BOOL CAdapter::Connect_Net( LPCTSTR lpnativeAddress,int port )
{
	if(!m_bInit){
		if(Create()==NULL){
			printf("Create ocx obj faild.\n");
			return FALSE;
		}
	}
	
	m_bConnected = FALSE;
	m_bConnected=m_pIZKEM->Connect_Net(lpnativeAddress,port);

	if(m_bConnected){
		m_bTFTMachine = m_pIZKEM->IsTFTMachine(1);
		BSTR bstrZKFPVersion=NULL;
		m_pIZKEM->GetSysOption(1, "~ZKFPVersion", &bstrZKFPVersion);
		CString ss(bstrZKFPVersion);
		if(bstrZKFPVersion!=NULL)
			SysFreeString(bstrZKFPVersion);
		m_ZKFPVersion = (ss==_T("10")) ? 10:9;
		//_tprintf(_T("fpVersion:%d\n"),m_ZKFPVersion);

		//_tprintf(_T("fpVersion:%s\n"),ss);
		//printf("****sysinfo--end********\n");
	}
	return m_bConnected;
}

BOOL CAdapter::ReadAllGLogData( DWORD dwMachineNumber )
{
	if(!CheckConnectStatus())return FALSE;
	return m_pIZKEM->ReadAllGLogData(dwMachineNumber);
}

BOOL CAdapter::GetGeneralLogDataStr( long dwMachineNumber, long * dwEnrollNumber, long * dwVerifyMode, long * dwInOutMode, BSTR * TimeStr )
{
	if(!CheckConnectStatus())return FALSE;
	if(m_bTFTMachine)return FALSE;
	BOOL bRet =  m_pIZKEM->GetGeneralLogDataStr(dwMachineNumber,dwEnrollNumber,dwVerifyMode,dwInOutMode,TimeStr);
	return bRet;

}
BOOL CAdapter::GetGeneralLogData( long dwMachineNumber, long * dwTMachineNumber, long * dwEnrollNumber, long * dwEMachineNumber, long * dwVerifyMode, long * dwInOutMode, long * dwYear, long * dwMonth, long * dwDay, long * dwHour, long * dwMinute ,long *dwSecond )
{
	if(!CheckConnectStatus())return FALSE;	
	VARIANT_BOOL bRet = VARIANT_FALSE;
	if(m_bTFTMachine){
		long dwWorkCode;
		BSTR bstrEnrollNumber=NULL;
		bRet = m_pIZKEM->SSR_GetGeneralLogData(dwMachineNumber,
			&bstrEnrollNumber,dwVerifyMode,dwInOutMode,dwYear,dwMonth,dwDay,dwHour,dwMinute,dwSecond,&dwWorkCode);
		if(bRet){
			CString enroll(bstrEnrollNumber);
			char* lpszText2 = _com_util::ConvertBSTRToString(bstrEnrollNumber);
			
			*dwEnrollNumber = (lpszText2==NULL)?0:atoi(lpszText2);
		}
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
	}else{
		bRet =  m_pIZKEM->GetGeneralLogData(dwMachineNumber,dwTMachineNumber,dwEnrollNumber,
			dwEMachineNumber,dwVerifyMode,dwInOutMode,dwYear,dwMonth,dwDay,dwHour,dwMinute);	

	}
	if(bRet==VARIANT_FALSE)
		return FALSE;
	return bRet;

}
BOOL CAdapter::ClearGLog( long dwMachineNumber )
{
	if(!CheckConnectStatus())return FALSE;
	return m_pIZKEM->ClearGLog(dwMachineNumber);
}

BOOL CAdapter::ReadAllUserID( long dwMachineNumber )
{
	if(!CheckConnectStatus())return FALSE;
	return m_pIZKEM->ReadAllUserID(dwMachineNumber);
}

BOOL CAdapter::GetAllUserInfo( long dwMachineNumber, long * dwEnrollNumber, BSTR * Name, BSTR * Password, long * Privilege, VARIANT_BOOL * Enabled )
{
	if(!CheckConnectStatus())return FALSE;
	if(m_bTFTMachine)
	{
		BSTR bstrEnrollNumber=NULL;
		BOOL bRet =  m_pIZKEM->SSR_GetAllUserInfo(dwMachineNumber,&bstrEnrollNumber,Name,Password,Privilege,Enabled);
		char* lpszText2 = _com_util::ConvertBSTRToString(bstrEnrollNumber);
		*dwEnrollNumber = (lpszText2==NULL)?0:atoi(lpszText2);
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
		return bRet;
	}
	return m_pIZKEM->GetAllUserInfo(dwMachineNumber,dwEnrollNumber,Name,Password,Privilege,Enabled);
}

BOOL CAdapter::GetUserInfo( long dwMachineNumber, long dwEnrollNumber, BSTR * Name, BSTR * Password, long * Privilege, VARIANT_BOOL * Enabled )
{
	if(!CheckConnectStatus())return FALSE;
	if(m_bTFTMachine){
		CString strEnrollNumber;
		strEnrollNumber.Format(_T("%d"),dwEnrollNumber);
		BSTR bstrEnrollNumber=strEnrollNumber.AllocSysString();
		BOOL bRet = m_pIZKEM->SSR_GetUserInfo(dwMachineNumber,bstrEnrollNumber,Name,Password,Privilege,Enabled);
		
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
		return bRet;
	}
	return m_pIZKEM->GetUserInfo(dwMachineNumber,dwEnrollNumber,Name,Password,Privilege,Enabled);
}

BOOL CAdapter::SetUserInfo( long dwMachineNumber, long dwEnrollNumber, _bstr_t Name, _bstr_t Password, long Privilege, VARIANT_BOOL Enabled )
{
	if(!CheckConnectStatus())return FALSE;
	if(m_bTFTMachine){
		CString strEnrollNumber;
		strEnrollNumber.Format(_T("%d"),dwEnrollNumber);
		BSTR bstrEnrollNumber=strEnrollNumber.AllocSysString();
		BOOL bRet =   m_pIZKEM->SSR_SetUserInfo(dwMachineNumber,bstrEnrollNumber,Name,Password,Privilege,Enabled);
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
		return bRet;
	}
	return m_pIZKEM->SetUserInfo(dwMachineNumber,dwEnrollNumber,Name,Password,Privilege,Enabled);
}

BOOL CAdapter::SetUserTmpStr( long dwMachineNumber, long dwEnrollNumber, long dwFingerIndex, _bstr_t TmpData )
{
	if(!CheckConnectStatus())return FALSE;

	if(m_ZKFPVersion==10){
		CString strEnrollNumber;
		strEnrollNumber.Format(_T("%d"),dwEnrollNumber);
		BSTR bstrEnrollNumber=strEnrollNumber.AllocSysString();
		long dwFlag=0;
		BOOL bRet =  m_pIZKEM->SetUserTmpExStr(dwMachineNumber,bstrEnrollNumber,dwFingerIndex,dwFlag,TmpData);
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
		return bRet;
	}
	if(m_bTFTMachine){
		CString strEnrollNumber;
		strEnrollNumber.Format(_T("%d"),dwEnrollNumber);
		BSTR bstrEnrollNumber=strEnrollNumber.AllocSysString();
		BOOL bRet =  m_pIZKEM->SSR_SetUserTmpStr(dwMachineNumber,bstrEnrollNumber,dwFingerIndex,TmpData);
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
		return bRet;
	}
	return m_pIZKEM->SetUserTmpStr(dwMachineNumber,dwEnrollNumber,dwFingerIndex,TmpData);
}

BOOL CAdapter::GetUserTmpStr( long dwMachineNumber, long dwEnrollNumber, long dwFingerIndex, BSTR * TmpData, long * TmpLength )
{
	if(!CheckConnectStatus())return FALSE;

	if(m_ZKFPVersion==10){
		CString strEnrollNumber;
		strEnrollNumber.Format(_T("%d"),dwEnrollNumber);
		BSTR bstrEnrollNumber=strEnrollNumber.AllocSysString();

		long dwFlag=0;
		BOOL bRet =  m_pIZKEM->GetUserTmpExStr(dwMachineNumber,bstrEnrollNumber,dwFingerIndex,&dwFlag,TmpData,TmpLength);
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
		return bRet;
	}
	/**/
	if(m_bTFTMachine){
		CString strEnrollNumber;
		strEnrollNumber.Format(_T("%d"),dwEnrollNumber);
		BSTR bstrEnrollNumber=strEnrollNumber.AllocSysString();
		BOOL bRet =  m_pIZKEM->SSR_GetUserTmpStr(dwMachineNumber,bstrEnrollNumber,dwFingerIndex,TmpData,TmpLength);
		if(bstrEnrollNumber!=NULL)
			::SysFreeString(bstrEnrollNumber);
		return bRet;
	}
	return m_pIZKEM->GetUserTmpStr(dwMachineNumber,dwEnrollNumber,dwFingerIndex,TmpData,TmpLength);
}

void CAdapter::Disconnect()
{
	if(m_bConnected)	m_pIZKEM->Disconnect();
	if(m_bInit)Release();
	m_bConnected = FALSE;
}

void CAdapter::EnableDevice( LONG dwMachineNumber,VARIANT_BOOL Enabled )
{
	if(!CheckConnectStatus())return;
	m_pIZKEM->EnableDevice(dwMachineNumber,Enabled);
}
