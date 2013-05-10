// zksoftAdapter.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "zksoftAdapter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CzksoftAdapterApp

BEGIN_MESSAGE_MAP(CzksoftAdapterApp, CWinApp)
END_MESSAGE_MAP()

#include "Adapter.h"
CAdapter g_Adapter;
// CzksoftAdapterApp 构造

CzksoftAdapterApp::CzksoftAdapterApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	printf("CzksoftAdapterApp::CzksoftAdapterApp()\n");	
}

CzksoftAdapterApp::~CzksoftAdapterApp()
{
	g_Adapter.Release();
	CoUninitialize();
}

// 唯一的一个 CzksoftAdapterApp 对象

CzksoftAdapterApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xBEEF9FFB, 0x9065, 0x4422, { 0x9C, 0x7, 0x20, 0xC1, 0xB9, 0xDC, 0x2E, 0x79 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CzksoftAdapterApp 初始化

BOOL CzksoftAdapterApp::InitInstance()
{
	HRESULT hr = CoInitialize(NULL);
	CWinApp::InitInstance();

	AfxEnableControlContainer();
	
	printf(_T("initinstance()\n"));
	//create();
	// 将所有 OLE 服务器(工厂)注册为运行。这将使
	//  OLE 库得以从其他应用程序创建对象。
	COleObjectFactory::RegisterAll();

	return TRUE;
}


// DllGetClassObject - 返回类工厂

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - 允许 COM 卸载 DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - 将项添加到系统注册表

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


// DllUnregisterServer - 将项从系统注册表中移除

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

