
// FindMSSQL.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFindMSSQLApp:
// See FindMSSQL.cpp for the implementation of this class
//

class CFindMSSQLApp : public CWinApp
{
public:
	CFindMSSQLApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFindMSSQLApp theApp;