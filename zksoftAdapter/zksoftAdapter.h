// zksoftAdapter.h : zksoftAdapter DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CzksoftAdapterApp
// 有关此类实现的信息，请参阅 zksoftAdapter.cpp
//

class CzksoftAdapterApp : public CWinApp
{
public:
	CzksoftAdapterApp();
	~CzksoftAdapterApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
private:

};
