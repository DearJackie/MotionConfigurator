// FocusSampleDlg.h : header file
//

#if !defined(AFX_FOCUSSAMPLEDLG_H__599C8188_F901_4161_8C37_D57E35CEEFA8__INCLUDED_)
#define AFX_FOCUSSAMPLEDLG_H__599C8188_F901_4161_8C37_D57E35CEEFA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include"MyBaseDialog.h"

typedef struct TPerson {  
   CString        Name;
   COleDateTime   Date;
   CString        Status;
   CString        Profession;
} Person;

/////////////////////////////////////////////////////////////////////////////
// CFocusSampleDlg dialog

class CFocusSampleDlg : public CMyBaseDialog
{
public:
   Person  MyPerson_;   // Ok, the final place where the ok data must be...
// Construction
public:
	CFocusSampleDlg(CWnd* pParent = NULL);	// standard constructor

   virtual BOOL ValAndSubmit(int DlgCtrlID); // THE ONE AND ONLY METHOD THAT YOU NEED TO IMPLEMENT...

	//{{AFX_DATA(CFocusSampleDlg)
	enum { IDD = IDD_FOCUSSAMPLE_DIALOG };
	CString	m_edName;
	CString	m_cbCombo;
	CString	m_lbListBox;
	COleDateTime	m_tpDate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFocusSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnMyCANCEL();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   void UpdateControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUSSAMPLEDLG_H__599C8188_F901_4161_8C37_D57E35CEEFA8__INCLUDED_)
