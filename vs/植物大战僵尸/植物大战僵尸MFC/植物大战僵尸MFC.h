
// 植物大战僵尸MFC.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// C植物大战僵尸MFCApp: 
// 有关此类的实现，请参阅 植物大战僵尸MFC.cpp
//

class C植物大战僵尸MFCApp : public CWinApp
{
public:
	C植物大战僵尸MFCApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern C植物大战僵尸MFCApp theApp;