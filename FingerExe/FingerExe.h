
// FingerExe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFingerExeApp:
// �йش����ʵ�֣������ FingerExe.cpp
//

class CFingerExeApp : public CWinAppEx
{
public:
	CFingerExeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFingerExeApp theApp;