/* -------------------------------------------------------------------------
   Filename: MyBaseDialog.h 

      ok, here is my base dialog class ( this handle the OnCommand and on 
   Notify), just inherit yiour dialogs from this class, and then implement 
   in your classes the virtual method ValAndSubmit...
   ------------------------------------------------------------------------- */

#include "stdafx.h"
#include "MyBaseDialog.h "

//-----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CMyBaseDialog, CDialog)
	//{{AFX_MSG_MAP(CMyBaseDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------

CMyBaseDialog::CMyBaseDialog( UINT  nDlgID,							      							      
							      CWnd* pParent )
: CDialog( nDlgID, pParent )
{
	//{{AFX_DATA_INIT(CPinnableDialog)
	//}}AFX_DATA_INIT
}

/* -------------------------------------------------------------------------
      Ok, for some new controls..., Like the PretranslateMessage thing...
   ------------------------------------------------------------------------- */

BOOL CMyBaseDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
   NMHDR* pNMHDR = (NMHDR *)lParam;

   if(pNMHDR && pNMHDR->code == NM_KILLFOCUS) {      
      CWnd *pFocus = CWnd::GetFocus(); // call to a static function
      if(pFocus && (pFocus->GetParent() == this)) {
         if(pFocus->GetDlgCtrlID() != IDCANCEL) {  // Ok, if the focus is not in the cancel button...            
            if(pNMHDR->idFrom) {
               ValAndSubmit(pNMHDR->idFrom);
            }
         }
      }       
   }

	return CDialog::OnNotify(wParam, lParam, pResult);
}


/* -------------------------------------------------------------------------
      Like the PretranslateMessage thing...
   ------------------------------------------------------------------------- */

BOOL CMyBaseDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
   UINT notificationCode = (UINT) HIWORD(wParam);

   
   if((notificationCode == EN_KILLFOCUS)        ||   // For List control I handle it in another way....
            (notificationCode == LBN_KILLFOCUS) ||
            (notificationCode == CBN_KILLFOCUS) ||
            (notificationCode == NM_KILLFOCUS)  ||
            (notificationCode == WM_KILLFOCUS)) {
         CWnd *pFocus = CWnd::GetFocus(); // call to a static function

         // If we are changing the focus to another control of the same window...
         if(pFocus && (pFocus->GetParent() == this)) {
            if(pFocus->GetDlgCtrlID() != IDCANCEL) {  // Ok, if the focus is not in the cancel button...
               ValAndSubmit(LOWORD(wParam));
            }
         }       
   }

   
	return CDialog::OnCommand(wParam, lParam);
}

/* -------------------------------------------------------------------------
      Just to capture the ENTER key...
   ------------------------------------------------------------------------- */

BOOL CMyBaseDialog::PreTranslateMessage(MSG* pMsg)
{
   
   if (pMsg->message != WM_KEYDOWN) // Only deal with KEYDOWN messages.  Defer everything else to base class   
      return CDialog::PreTranslateMessage(pMsg);
   
   if(pMsg->wParam == VK_RETURN && this->GetSafeHwnd()) { // <Enter> key
      CWnd *pCurr = GetFocus();
      if(pCurr) {
         ValAndSubmit(pCurr->GetDlgCtrlID());      
      }

      return FALSE;  // Dirty trick, take care if you want to handle enter in your dialog
                     // for other purposed ( easy to fix... ;-) )
   } 
   
	return CDialog::PreTranslateMessage(pMsg);
}