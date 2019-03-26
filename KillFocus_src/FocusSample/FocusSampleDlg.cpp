// FocusSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FocusSample.h"
#include "FocusSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusSampleDlg dialog

CFocusSampleDlg::CFocusSampleDlg(CWnd* pParent /*=NULL*/)
	: CMyBaseDialog(CFocusSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFocusSampleDlg)
	m_edName = _T("");
	m_cbCombo = _T("");
	m_lbListBox = _T("");
	m_tpDate = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   MyPerson_.Name       = "Charles";
   MyPerson_.Date       = COleDateTime::GetCurrentTime();
   MyPerson_.Profession = "Plumber";
   MyPerson_.Status     = "married";

}

void CFocusSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyBaseDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFocusSampleDlg)
	DDX_Text(pDX, IDED_NAME, m_edName);
	DDX_CBString(pDX, IDCB_COMBO, m_cbCombo);
	DDX_LBString(pDX, IDLB_LISTBOX, m_lbListBox);
	DDX_DateTimeCtrl(pDX, IDTP_DATE, m_tpDate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFocusSampleDlg, CMyBaseDialog)
	//{{AFX_MSG_MAP(CFocusSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDMyCANCEL, OnMyCANCEL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFocusSampleDlg::UpdateControls()
{
   m_edName     = MyPerson_.Name;
   m_tpDate     = MyPerson_.Date;
   m_lbListBox  = MyPerson_.Profession;
   m_cbCombo    = MyPerson_.Status;
   UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CFocusSampleDlg message handlers

BOOL CFocusSampleDlg::OnInitDialog()
{
	CMyBaseDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
   CComboBox *pCombo = (CComboBox *)GetDlgItem(IDCB_COMBO);
   
   pCombo->AddString("married");
   pCombo->AddString("single");

   CListBox *pListBox = (CListBox *) GetDlgItem(IDLB_LISTBOX);

   pListBox->AddString("plumber");
   pListBox->AddString("Software Developer");
   pListBox->AddString("Postman");
   pListBox->AddString("Doctor");
   pListBox->AddString("Whatever");

   UpdateControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFocusSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CMyBaseDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFocusSampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CMyBaseDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFocusSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/* -------------------------------------------------------------------------
    THE ONE AND ONLY METHOD THAT YOU NEED TO IMPLEMENT...
   ------------------------------------------------------------------------- */
BOOL CFocusSampleDlg::ValAndSubmit(int DlgCtrlID) 
{
   BOOL          bIsOk   = FALSE;
   CString       Error;
   COleDateTime  Aux;//( 1975, 12, 31); //, int nHour, int nMin, int nSec, int nDST = -1 );

   Aux.ParseDateTime("12/31/1975");



   Error.Empty();
   UpdateData(TRUE);         
   switch(DlgCtrlID) {                           
       case IDED_NAME:    // Finish Prob                              
          if((m_edName.GetLength() == 0) || (m_edName[0]!= 'C')) {
            Error = "Hey ! Name must begin with 'C' (upper) !!!";          
          } else {
             MyPerson_.Name = m_edName;
          }
       break;
       case IDLB_LISTBOX:    // Finish Prob                              
          if(m_lbListBox == "Whatever") {

             Error = "Hey ! Whatever is not a valid profession !!!";          
          } else {
             MyPerson_.Profession = m_lbListBox;
          }
       break;
       case IDTP_DATE:
          if(m_tpDate > Aux) {
             MyPerson_.Date = m_tpDate;
          } else {
             Error = "Hey ! Date must be greater than 1975 !!!";          
          }
       break;

       break;      
   }

   UpdateControls();  // If its right nothing happens, if not wrong data is replaced...
                      // just to have always the right data in the right place...

   if(!(Error.IsEmpty())) {
      MessageBox(Error);
   }

         
   return bIsOk;
}


void CFocusSampleDlg::OnOK() 
{
   CString Result;

   Result  = "The output record is:\n";
   Result += "Name: "       + MyPerson_.Name + "\n";
   Result += "Date: "       + MyPerson_.Date.Format() + "\n";
   Result += "Status: "     + MyPerson_.Status + "\n";
   Result += "Profession: " + MyPerson_.Profession + "\n";

   
   MessageBox(Result);
   
	CMyBaseDialog::OnOK();
}

void CFocusSampleDlg::OnMyCANCEL() 
{
   CMyBaseDialog::OnCancel();	
}
