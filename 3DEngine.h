// 3D Engine.h : main header file for the 3D ENGINE application
//

#if !defined(AFX_3DENGINE_H__7039CD64_DB84_11D5_8358_00A024E92462__INCLUDED_)
#define AFX_3DENGINE_H__7039CD64_DB84_11D5_8358_00A024E92462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CMy3DEngineApp:
// See 3D Engine.cpp for the implementation of this class
//

class CMy3DEngineApp : public CWinApp
{
public:
	CMy3DEngineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DEngineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy3DEngineApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DENGINE_H__7039CD64_DB84_11D5_8358_00A024E92462__INCLUDED_)
