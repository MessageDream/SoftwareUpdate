
// SoftwareUpdate.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "MyFuncLib.h"
#include "MyClassLib.h"

// CSoftwareUpdateApp:
// �йش����ʵ�֣������ SoftwareUpdate.cpp
//

class CSoftwareUpdateApp : public CWinApp
{
public:
	CSoftwareUpdateApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSoftwareUpdateApp theApp;
extern CString g_sz_strParameter[3];

#define WM_MSGRECVPRO WM_USER+1

enum MSGUSER
{
	MSGUSER_UPDATERESULT=0
};