
// MFCDCProgect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCDCProgectApp: 
// �йش����ʵ�֣������ MFCDCProgect.cpp
//

class CMFCDCProgectApp : public CWinApp
{
public:
	CMFCDCProgectApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCDCProgectApp theApp;