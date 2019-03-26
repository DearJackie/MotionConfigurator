/* -------------------------------------------------------------------------
   Filename: MyBaseDialog.h 

      ok, here is my base dialog class ( this handle the OnCommand and on 
   Notify), just inherit yiour dialogs from this class, and then implement 
   in your classes the virtual method ValAndSubmit...
   ------------------------------------------------------------------------- */
#ifndef MYBASEDIALOG_H
#define MYBASEDIALOG_H


#include "FocusSample.h"
// Define message to inform the parent when this dialog is closed.



class CMyBaseDialog : public CDialog
{
public:
	// Construction.
	CMyBaseDialog( UINT nDlgID,				// ID for the dialog template resource.				     				     
				     CWnd* pParent = NULL );	// Parent window, if any.   				

   virtual BOOL ValAndSubmit(int DlgCtrlID) = 0; // So you must implement this in your base class !!!   
                                                 // if you don´t want so, just replace the = 0 for a {}
                                          
  	//{{AFX_DATA(CMyBaseDialog)	
	//}}AFX_DATA
		
	//{{AFX_VIRTUAL(CMyBaseDialog)
	public:	
   virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);	
   virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
   virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:	
	//{{AFX_MSG(CMyBaseDialog)					
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //  MYBASEDIALOG