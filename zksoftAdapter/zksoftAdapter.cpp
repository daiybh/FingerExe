// zksoftAdapter.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "zksoftAdapter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CzksoftAdapterApp

BEGIN_MESSAGE_MAP(CzksoftAdapterApp, CWinApp)
END_MESSAGE_MAP()

#include "Adapter.h"
CAdapter g_Adapter;
// CzksoftAdapterApp ����

CzksoftAdapterApp::CzksoftAdapterApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	printf("CzksoftAdapterApp::CzksoftAdapterApp()\n");	
}

CzksoftAdapterApp::~CzksoftAdapterApp()
{
	g_Adapter.Release();
	CoUninitialize();
}

// Ψһ��һ�� CzksoftAdapterApp ����

CzksoftAdapterApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xBEEF9FFB, 0x9065, 0x4422, { 0x9C, 0x7, 0x20, 0xC1, 0xB9, 0xDC, 0x2E, 0x79 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CzksoftAdapterApp ��ʼ��

BOOL CzksoftAdapterApp::InitInstance()
{
	HRESULT hr = CoInitialize(NULL);
	CWinApp::InitInstance();

	AfxEnableControlContainer();
	
	printf(_T("initinstance()\n"));
	//create();
	// ������ OLE ������(����)ע��Ϊ���С��⽫ʹ
	//  OLE ����Դ�����Ӧ�ó��򴴽�����
	COleObjectFactory::RegisterAll();

	return TRUE;
}


// DllGetClassObject - �����๤��

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - ���� COM ж�� DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
printf("DllRegisterServer\n");
	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
printf("DllUnregisterServer\n");
	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}

