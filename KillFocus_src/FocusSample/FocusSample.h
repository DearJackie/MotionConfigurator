// FocusSample.h : main header file for the FOCUSSAMPLE application
//

#if !defined(AFX_FOCUSSAMPLE_H__2C60542E_A63C_4D55_8AA1_F382D1E7479A__INCLUDED_)
#define AFX_FOCUSSAMPLE_H__2C60542E_A63C_4D55_8AA1_F382D1E7479A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFocusSampleApp:
// See FocusSample.cpp for the implementation of this class
//

class CFocusSampleApp : public CWinApp
{
public:
	CFocusSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFocusSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUSSAMPLE_H__2C60542E_A63C_4D55_8AA1_F382D1E7479A__INCLUDED_)
