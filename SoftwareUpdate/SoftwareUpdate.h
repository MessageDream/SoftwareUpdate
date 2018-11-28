
// SoftwareUpdate.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "ZClassLib.h"

// CSoftwareUpdateApp:
// 有关此类的实现，请参阅 SoftwareUpdate.cpp
//

class CSoftwareUpdateApp : public CWinApp
{
public:
	CSoftwareUpdateApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CSoftwareUpdateApp theApp;
extern CString g_sz_strParameter[3];

#define WM_MSGRECVPRO WM_USER+1

enum MSGUSER
{
	MSGUSER_UPDATERESULT=0
};