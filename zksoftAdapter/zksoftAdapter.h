// zksoftAdapter.h : zksoftAdapter DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CzksoftAdapterApp
// �йش���ʵ�ֵ���Ϣ������� zksoftAdapter.cpp
//

class CzksoftAdapterApp : public CWinApp
{
public:
	CzksoftAdapterApp();
	~CzksoftAdapterApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
private:

};
