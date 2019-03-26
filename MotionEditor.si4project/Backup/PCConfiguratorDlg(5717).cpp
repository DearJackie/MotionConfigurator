
// PCConfiguratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCConfigurator.h"
#include "PCConfiguratorDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include  "Authorize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#define  _CONNECTION_DEBUG
#endif

#define APP_VERION  L"2.3.1"

static UINT guCtrlIDs[] = {
	IDC_EDIT_PARAM_L,
	IDC_EDIT_PARAM_W,
	IDC_EDIT_PARAM_R,
	IDC_EDIT_PARAM_SD,
	IDC_EDIT_PARAM_SPEED,
	IDC_EDIT_CONV_ROLLING_SPEED,
	IDC_EDIT_SETUP_DX,
	IDC_EDIT_SETUP_DY,
	IDC_EDIT_SETUP_DZ,
	IDC_EDIT_PARAM_PZM,
	IDC_EDIT_PARAM_TG1,
	IDC_EDIT_PARAM_TG2,
	IDC_EDIT_CONV_WAITING_TIME
};
#define CTRLID_LIST_SIZE (sizeof(guCtrlIDs)/sizeof(UINT))

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnBtnConnect();
//	afx_msg void OnBtnSaveParam();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)

//	ON_COMMAND(IDC_BTN_CONNECT, &CAboutDlg::OnBtnConnect)
//	ON_COMMAND(IDC_BTN_SAVE_PARAM, &CAboutDlg::OnBtnSaveParam)
END_MESSAGE_MAP()

// CPCConfiguratorDlg dialog

CPCConfiguratorDlg::CPCConfiguratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCConfiguratorDlg::IDD, pParent),
	m_bUnlocked(FALSE), 
	m_bConnected(FALSE)
	, m_fParamTw(0)
	, m_fParamPzm(0)
	, m_fParamTg1(0)
	, m_fParamTg2(0)
	, m_fParamL(0)
	, m_fParamR(0)
	, m_fParamSd(0)
	, m_fParamW(0)
	, m_fParamRs(0)
	, m_fParamCBs(0)
	, m_fParamDx(0)
	, m_fParamDy(0)
	, m_fParamDz(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	SetMemberDefaultValues();

	m_log.LogStart();
}

CPCConfiguratorDlg::~CPCConfiguratorDlg()
{
	m_log.LogStop();
}

void CPCConfiguratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_AXIS_X_MINUS, m_btnMinusX);
	DDX_Control(pDX, IDC_BTN_AXIS_X_PLUS, m_btnPlusX);
	DDX_Control(pDX, IDC_BTN_AXIS_Y_MINUS, m_btnMinusY);
	DDX_Control(pDX, IDC_BTN_AXIS_Y_PLUS, m_btnPlusY);
	DDX_Control(pDX, IDC_BTN_AXIS_Z_MINUS, m_btnMinusZ);
	DDX_Control(pDX, IDC_BTN_AXIS_Z_PLUS, m_btnPlusZ);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_BTN_ROUTINE_START, m_btnRoutineStart);
	DDX_Control(pDX, IDC_BTN_ROUTINE_STOP, m_btnRoutineStop);
	DDX_Control(pDX, IDC_BTN_ROUTINE_RESET, m_btnRoutineReset);
	DDX_Control(pDX, IDC_AXIS_X, m_staticAxisX);
	DDX_Control(pDX, IDC_AXIS_Y, m_staticAxisY);
	DDX_Control(pDX, IDC_AXIS_Z, m_staticAxisZ);
	DDX_Control(pDX, IDC_STATIC_ROUTINE_DEMO, m_staticRoutineDemo);
	//  DDX_Text(pDX, IDC_EDIT_PARAM_L, m_fParamL);
	//  DDV_MinMaxFloat(pDX, m_fParamL, 0.005f, 160.0f);
	//  DDX_Text(pDX, IDC_EDIT_PARAM_R, m_fParamR);
	//  DDV_MinMaxFloat(pDX, m_fParamR, 0.005f, 80.0f);
	//  DDX_Text(pDX, IDC_EDIT_PARAM_SD, m_fParamSd);
	//  DDV_MinMaxFloat(pDX, m_fParamSd, 0.005f, 60.0f);
	//  DDX_Text(pDX, IDC_EDIT_PARAM_W, m_fParamW);
	//  DDV_MinMaxFloat(pDX, m_fParamW, 0.005f, 60.0f);
	//  DDX_Text(pDX, IDC_EDIT_PARAM_SPEED, m_fParamRs);
	//  DDV_MinMaxFloat(pDX, m_fParamRs, 20.0f, 600.0f); // speed
	//  DDX_Text(pDX, IDC_EDIT_CONV_ROLLING_SPEED, m_fParamCBs);
	//  DDV_MinMaxFloat(pDX, m_fParamCBs, 0.5f, 5.0f);// Rolling Speed
	//  DDX_Text(pDX, IDC_EDIT_SETUP_DX, m_fParamDx);
	//  DDV_MinMaxFloat(pDX, m_fParamDx, 0.005f, 50.0f);
	//  DDX_Text(pDX, IDC_EDIT_SETUP_DY, m_fParamDy);
	//  DDV_MinMaxFloat(pDX, m_fParamDy, 0.005f, 50.0f);
	//  DDX_Text(pDX, IDC_EDIT_SETUP_DZ, m_fParamDz);
	//  DDV_MinMaxFloat(pDX, m_fParamDz, 0.005f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_CONV_WAITING_TIME, m_fParamTw);
	DDV_MinMaxFloat(pDX, m_fParamTw, 1.0f, 65535.0f);
	DDX_Text(pDX, IDC_EDIT_PARAM_PZM, m_fParamPzm);
	DDV_MinMaxFloat(pDX, m_fParamPzm, 0.005f, 50.0f);
	DDX_Text(pDX, IDC_EDIT_PARAM_TG1, m_fParamTg1);
	DDV_MinMaxFloat(pDX, m_fParamTg1, 1.0f, 65535.0f);
	DDX_Text(pDX, IDC_EDIT_PARAM_TG2, m_fParamTg2);
	DDV_MinMaxFloat(pDX, m_fParamTg2, 1.0f, 65535.0f);
	DDX_Text(pDX, IDC_EDIT_PARAM_L, m_fParamL);
	DDV_MinMaxFloat(pDX, m_fParamL, 0.005, 160.0);
	DDX_Text(pDX, IDC_EDIT_PARAM_R, m_fParamR);
	DDV_MinMaxFloat(pDX, m_fParamR, 0.005, 80);
	DDX_Text(pDX, IDC_EDIT_PARAM_SD, m_fParamSd);
	DDV_MinMaxFloat(pDX, m_fParamSd, 0.005, 60.0);
	DDX_Text(pDX, IDC_EDIT_PARAM_W, m_fParamW);
	DDV_MinMaxFloat(pDX, m_fParamW, 0.005, 60);
	DDX_Text(pDX, IDC_EDIT_PARAM_SPEED, m_fParamRs);
	DDV_MinMaxFloat(pDX, m_fParamRs, 20, 600);
	DDX_Text(pDX, IDC_EDIT_CONV_ROLLING_SPEED, m_fParamCBs);
	DDV_MinMaxFloat(pDX, m_fParamCBs, 0.5, 5);
	DDX_Text(pDX, IDC_EDIT_SETUP_DX, m_fParamDx);
	DDV_MinMaxFloat(pDX, m_fParamDx, 0.005, 50);
	DDX_Text(pDX, IDC_EDIT_SETUP_DY, m_fParamDy);
	DDV_MinMaxFloat(pDX, m_fParamDy, 0.005, 50);
	DDX_Text(pDX, IDC_EDIT_SETUP_DZ, m_fParamDz);
	DDV_MinMaxFloat(pDX, m_fParamDz, 0.005, 10);
}

BEGIN_MESSAGE_MAP(CPCConfiguratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_MOUSEHOVER()
//	ON_WM_SETCURSOR()
	//ON_EN_UPDATE(IDC_EDIT_PARAM_L, &CPCConfiguratorDlg::OnUpdateEditParamL)
//	ON_EN_KILLFOCUS(IDC_EDIT_PARAM_L, &CPCConfiguratorDlg::OnKillfocusEditParamL)
//	ON_WM_KEYDOWN()
ON_BN_CLICKED(IDC_BTN_CONNECT, &CPCConfiguratorDlg::OnClickedBtnConnect)
ON_BN_CLICKED(IDC_BTN_SAVE_PARAM, &CPCConfiguratorDlg::OnClickedBtnSaveParam)
ON_BN_CLICKED(IDC_BTN_AXIS_X_MINUS, &CPCConfiguratorDlg::OnClickedBtnAxisXMinus)
ON_BN_CLICKED(IDC_BTN_AXIS_X_PLUS, &CPCConfiguratorDlg::OnClickedBtnAxisXPlus)
ON_BN_CLICKED(IDC_BTN_AXIS_Y_MINUS, &CPCConfiguratorDlg::OnClickedBtnAxisYMinus)
ON_BN_CLICKED(IDC_BTN_AXIS_Y_PLUS, &CPCConfiguratorDlg::OnClickedBtnAxisYPlus)
ON_BN_CLICKED(IDC_BTN_AXIS_Z_MINUS, &CPCConfiguratorDlg::OnClickedBtnAxisZMinus)
ON_BN_CLICKED(IDC_BTN_AXIS_Z_PLUS, &CPCConfiguratorDlg::OnClickedBtnAxisZPlus)
ON_BN_CLICKED(IDC_BTN_CONVEYOR_CLAMP_JIG, &CPCConfiguratorDlg::OnClickedBtnConveyorClampJig)
ON_BN_CLICKED(IDC_BTN_CONVEYOR_LOOSE_JIG, &CPCConfiguratorDlg::OnClickedBtnConveyorLooseJig)
ON_BN_CLICKED(IDC_BTN_CONVEYOR_SPEED_CHANGE, &CPCConfiguratorDlg::OnClickedBtnConveyorSpeedChange)
ON_BN_CLICKED(IDC_BTN_CONVEYOR_START, &CPCConfiguratorDlg::OnClickedBtnConveyorStart)
ON_BN_CLICKED(IDC_BTN_CONVEYOR_STOP, &CPCConfiguratorDlg::OnClickedBtnConveyorStop)
ON_BN_CLICKED(IDC_BTN_LOCK, &CPCConfiguratorDlg::OnClickedBtnLock)
ON_BN_CLICKED(IDC_BTN_MOTOR_START, &CPCConfiguratorDlg::OnClickedBtnMotorStart)
ON_BN_CLICKED(IDC_BTN_MOTOR_STOP, &CPCConfiguratorDlg::OnClickedBtnMotorStop)
ON_BN_CLICKED(IDC_BTN_ROUTINE_RESET, &CPCConfiguratorDlg::OnClickedBtnRoutineReset)
ON_BN_CLICKED(IDC_BTN_ROUTINE_START, &CPCConfiguratorDlg::OnClickedBtnRoutineStart)
ON_BN_CLICKED(IDC_BTN_ROUTINE_STOP, &CPCConfiguratorDlg::OnClickedBtnRoutineStop)
ON_BN_CLICKED(IDC_BTN_SET_START_POINT, &CPCConfiguratorDlg::OnClickedBtnSetStartPoint)
ON_BN_CLICKED(IDC_BTN_SET_UP, &CPCConfiguratorDlg::OnClickedBtnSetUp)
ON_BN_CLICKED(IDC_BTN_UNLOCK, &CPCConfiguratorDlg::OnClickedBtnUnlock)
ON_BN_CLICKED(IDC_BTN_PARAM_TESTING, &CPCConfiguratorDlg::OnClickedBtnParamTesting)
ON_BN_CLICKED(IDC_BTN_CONVEYOR_WAIT_TIME_CHANGE, &CPCConfiguratorDlg::OnClickedBtnConveyorWaitTimeChange)
ON_STN_CLICKED(IDC_STATIC_ROUTINE_DEMO, &CPCConfiguratorDlg::OnStnClickedStaticRoutineDemo)
END_MESSAGE_MAP()


// CPCConfiguratorDlg message handlers

BOOL CPCConfiguratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	CTime tm = CTime::GetCurrentTime();//Get system time
	CString strBuf;
	strBuf.Format(_T("Application Verions %s\nLog start: %4d/%2d/%2d %2d:%2d:%2d\n"), 
	    APP_VERION,
		tm.GetYear(),
		tm.GetMonth(),
		tm.GetDay(),
		tm.GetHour(),
		tm.GetMinute(),
		tm.GetSecond());
	m_log.LogWrite(strBuf);

	LoadControlIcons();

	UnlockConfigurator(m_bUnlocked);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPCConfiguratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPCConfiguratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPCConfiguratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Load the icons for the buttons, all the "Icon" attribute of buttons shall be set to "TRUE"
void CPCConfiguratorDlg::LoadControlIcons(void)
{
	//m_btnMinusX.ModifyStyle(0, BS_BITMAP);
	//if (m_btnLeft.GetBitmap() == NULL)
	//{
	//	m_btnLeft.SetBitmap(::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)));
	//}

	if (m_btnConnect.GetIcon() == NULL)
	{
		m_btnConnect.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_CONNECT)));
	}

	if (m_btnMinusX.GetIcon() == NULL)
	{
		m_btnMinusX.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_X_MINUS)));

	}
	if (m_btnPlusX.GetIcon() == NULL)
	{
		m_btnPlusX.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_X_PLUS)));
	}

	if (m_btnMinusY.GetIcon() == NULL)
	{
		m_btnMinusY.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Y_MINUS)));
	}
	if (m_btnPlusY.GetIcon() == NULL)
	{
		m_btnPlusY.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Y_PLUS)));
	}
	
	if (m_btnMinusZ.GetIcon() == NULL)
	{
		m_btnMinusZ.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Z_MINUS)));
	}
	if (m_btnPlusZ.GetIcon() == NULL)
	{
		m_btnPlusZ.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Z_PLUS)));
	}

	if (m_btnRoutineStart.GetIcon() == NULL)
	{
		m_btnRoutineStart.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_ROUTINE_START)));
	}
	if (m_btnRoutineStop.GetIcon() == NULL)
	{
		m_btnRoutineStop.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_ROUTINE_STOP)));
	}
	if (m_btnRoutineReset.GetIcon() == NULL)
	{
		m_btnRoutineReset.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_ROUTINE_RESET)));
	}

	//if (m_staticAxisX.GetIcon() == NULL)
	//{
	//	m_staticAxisX.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_X_MINUS)));
	//}ph
	//if (m_staticAxisY.GetIcon() == NULL)
	//{
	//	m_staticAxisY.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Y_MINUS)));
	//}
	//if (m_staticAxisZ.GetIcon() == NULL)
	//{
	//	m_staticAxisZ.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_Z_MINUS)));
	//}

	//if (m_staticRoutineDemo.GetIcon() == NULL)
	//{
	//	m_staticRoutineDemo.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_ROUTINE_DEMO)));
	//}
}


//void CPCConfiguratorDlg::OnMouseHover(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CDialogEx::OnMouseHover(nFlags, point);
//}


//BOOL CPCConfiguratorDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
//}


//void CPCConfiguratorDlg::OnUpdateEditParamL()
//{
//	// TODO:  If this is a RICHEDIT control, the control will not
//	// send this notification unless you override the CDialogEx::OnInitDialog()
//	// function to send the EM_SETEVENTMASK message to the control
//	// with the ENM_UPDATE flag ORed into the lParam mask.
//
//	// TODO:  Add your control notification handler code here
//	CString strTemp = _T("");
//	CEdit* pEditCtrl = ((CEdit*)(GetDlgItem(IDC_EDIT_PARAM_L)));
//	pEditCtrl->GetWindowText(strTemp);
//	//int editCtrlVal = (int)(atof((const char *)strTemp.GetString())*2000);
//	//if (editCtrlVal % ((int)(0.005*2000)) != 0 )
//	//{
//	//	MessageBox(_T("Invalid Input!"));
//	//	pEditCtrl->SetWindowText(_T("0.005"));
//	//}
//
//	//int len = strTemp.GetLength();
//	//strTemp.GetString();
//	//for (int i = 0; i < len; i++)
//	//{
//	//	if (strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
//	//	{
//
//	//		strTemp = strTemp.Left(i);
//
//	//		editHelp->SetWindowText(strTemp);
//
//	//		editHelp->SetSel(i, i, TRUE);
//
//	//		return;
//
//	//	}
//	//}
//}


//void CPCConfiguratorDlg::OnKillfocusEditParamL()
//{
//	// TODO: Add your control notification handler code here
//	//CString strTemp = _T("");
//	//CEdit* pEditCtrl = ((CEdit*)(GetDlgItem(IDC_EDIT_PARAM_L)));
//	//pEditCtrl->GetWindowText(strTemp);
//	//double editCtrlValDouble = atof((const char *)strTemp.GetBuffer(0));// .GetString());
//	//int editCtrlVal = (int)(editCtrlValDouble * 2000);
//	////if (editCtrlVal % ((int)(0.005 * 2000)) != 0)
//	////{
//	////	MessageBox(_T("Invalid Input!"));
//	////	pEditCtrl->SetWindowText(_T("0.005"));
//	////}
//
//	//if (!UpdateData(TRUE))
//	//{
//	//	// Reset to default value
//	//	pEditCtrl->SetWindowText(_T("0.005"));
//	//}
//}

//BOOL CPCConfiguratorDlg::PreTranslateMessage(MSG* pMsg)
//{
//	// Check the focus of the current control
//	// When ENTER key pressed or lost focus
//	if ( (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam) ||
//		 (WM_KILLFOCUS == pMsg->message)) // TODO: not working: PreTranslateMessage only sees messages that come from the message queue. The WM_KILLFOCUS messages are sent to the window as a result of processing the mouse message that causes the focus change, so you can add the code there, but it would do nothing.
//	{
//		CWnd *pFocusedWnd = GetFocus();
//
//		// Each time, only 1 focus
//		for (UINT i = 0; i < CTRLID_LIST_SIZE; i++)
//		{
//			UINT uCtrlId = guCtrlIDs[i];
//			if (pFocusedWnd == GetDlgItem(uCtrlId))
//			{
//				if (!UpdateData(TRUE))
//				{
//					// Reset to default value
//					TCTRLPARAM sCtrlParamInfo = GetCtrlParameterInfo(uCtrlId);
//					float fDefaultValue = sCtrlParamInfo.fDefaultValue;
//					char buf[32];
//					memset(buf, 0, sizeof(buf));
//					sprintf_s(buf, "%1.3f", fDefaultValue);
//                    CString str = CString(buf);
//					pFocusedWnd->SetWindowText(str);
//				
//					// Must return 0.
//					return 0;
//				}
//			}
//		}
//	}
//
//	return CDialog::PreTranslateMessage(pMsg);
//}

UINT CPCConfiguratorDlg::GetTriggerCmdList(UINT uCtrlID, TGALILCMD *pCmds, UINT uBufSize)
{
	TGALILCMD sCmdList[] = {
		// Trigger ID,                      CMD Prefix,         CmdOrder, uOption1CtrlID, strCmdDescrip
		//{IDC_BTN_CONNECT, "192.168.1.8 --subscribe ALL", 0, CONTROL_ID_INVALID }, // Different command
		{ IDC_BTN_ROUTINE_START,            "XQ#MLS",           0, CONTROL_ID_INVALID, "Routine Start" }, // Routine
		{ IDC_BTN_ROUTINE_STOP,             "ST",               0, CONTROL_ID_INVALID, "Routine Stop" },
		{ IDC_BTN_ROUTINE_STOP,             "HX0",               1, CONTROL_ID_INVALID, "Routine Stop" },
		{ IDC_BTN_ROUTINE_RESET,            "XQ#Reset",         0, CONTROL_ID_INVALID, "Routine Rest" },
//		{ IDC_BTN_ROUTINE_RESET,            "JP #Reset",        1, CONTROL_ID_INVALID,"Routine Rest" },
//		{ IDC_BTN_CHECK_POSITION,           "TP ABC",           0, CONTROL_ID_INVALID, "Check Position" }, // Check position
//		{ IDC_BTN_MOTOR_START,              "a=1", 0, CONTROL_ID_INVALID, "Motor start" },     // Motor
		{ IDC_BTN_MOTOR_STOP,               "MOABCD",           0, CONTROL_ID_INVALID, "Motor stop" },
		{ IDC_BTN_SAVE_PARAM,               "L=",               0, IDC_EDIT_PARAM_L, "Save parameter" },  // Parameters
		{ IDC_BTN_SAVE_PARAM,               "W=",               1, IDC_EDIT_PARAM_W, "Save parameter" },
		{ IDC_BTN_SAVE_PARAM,               "Sd=",              2, IDC_EDIT_PARAM_SD, "Save parameter" },
		{ IDC_BTN_SAVE_PARAM,               "R=",               3, IDC_EDIT_PARAM_R, "Save parameter" },		
		{ IDC_BTN_SAVE_PARAM,               "Tg1=",             4, IDC_EDIT_PARAM_TG1, "Save parameter" },
		{ IDC_BTN_SAVE_PARAM,               "Tg2=",             5, IDC_EDIT_PARAM_TG2, "Save parameter" },
		{ IDC_BTN_SAVE_PARAM,               "Spd=",             6, IDC_EDIT_PARAM_SPEED, "Save parameter" },
		{ IDC_BTN_SAVE_PARAM,               "Pzm=",             7, IDC_EDIT_PARAM_PZM, "Save parameter" },		
		{ IDC_BTN_SAVE_PARAM,               "BV",               8, CONTROL_ID_INVALID, "Save parameter" },
		{ IDC_BTN_SET_UP,                   "Dx=",              0, IDC_EDIT_SETUP_DX, "Set up" }, // Set up
		{ IDC_BTN_SET_UP,                   "Dy=",              1, IDC_EDIT_SETUP_DY, "Set up" },
		{ IDC_BTN_SET_UP,                   "Dz=",              2, IDC_EDIT_SETUP_DZ, "Set up" },
//		{ IDC_BTN_SET_UP,                   "BV", 3, CONTROL_ID_INVALID, "Set up" },
		{ IDC_BTN_GO,                       "XQ#SP",            0, CONTROL_ID_INVALID, "Go" },
		{ IDC_BTN_AXIS_X_MINUS,             "XQ#Amove2",        0, CONTROL_ID_INVALID, "Axis X-" },   // Move in Axis
		{ IDC_BTN_AXIS_X_PLUS,              "XQ#Amove1",        0, CONTROL_ID_INVALID, "Axis X+" },
		{ IDC_BTN_AXIS_Y_MINUS,             "XQ#Bmove1",        0, CONTROL_ID_INVALID, "Axis Y-" }, // Y forward
		{ IDC_BTN_AXIS_Y_PLUS,              "XQ#Bmove2",        0, CONTROL_ID_INVALID, "Axis Y+" }, // Y backward
		{ IDC_BTN_AXIS_Z_MINUS,             "XQ#Cmove1",        0, CONTROL_ID_INVALID, "Axis Z-" },
		{ IDC_BTN_AXIS_Z_PLUS,              "XQ#Cmove2",        0, CONTROL_ID_INVALID, "Axis Z+" },
		{ IDC_BTN_SET_START_POINT,          "Px=_TPA",          0, CONTROL_ID_INVALID, "Set start point" }, // Set Start Point
		{ IDC_BTN_SET_START_POINT,          "Py=_TPB",          1, CONTROL_ID_INVALID, "Set start point" },
		{ IDC_BTN_SET_START_POINT,          "Pz=_TPC",          2, CONTROL_ID_INVALID, "Set start point" },
		{ IDC_BTN_SET_START_POINT,          "BV",               3, CONTROL_ID_INVALID, "Set start point" },
		{ IDC_BTN_CONVEYOR_SPEED_CHANGE,    "Rspd=",            0, IDC_EDIT_CONV_ROLLING_SPEED, "Conveyor change speed" }, // Conveyor Debug
		{ IDC_BTN_CONVEYOR_SPEED_CHANGE,    "BV",               1, CONTROL_ID_INVALID, "Conveyor change speed" },
		{ IDC_BTN_CONVEYOR_START,           "XQ#Dtest",         0, CONTROL_ID_INVALID, "Conveyor start" },
		{ IDC_BTN_CONVEYOR_STOP,            "STD",              0, CONTROL_ID_INVALID, "Conveyor stop" },
		{ IDC_BTN_CONVEYOR_STOP,            "HX0",              1, CONTROL_ID_INVALID, "Conveyor stop" },
		{ IDC_BTN_CONVEYOR_CLAMP_JIG,       "SB1",              0, CONTROL_ID_INVALID, "Conveyor clamp jig" },
		{ IDC_BTN_CONVEYOR_LOOSE_JIG,       "CB1",              0, CONTROL_ID_INVALID, "Conveyor loose jig" },
		{ IDC_BTN_PARAM_TESTING,            "XQ#Tmove",         0, CONTROL_ID_INVALID, "Testing" },
		{ IDC_BTN_CONVEYOR_WAIT_TIME_CHANGE, "Tw=",             0, IDC_EDIT_CONV_WAITING_TIME, "Change waiting time" },
		{ IDC_BTN_CONVEYOR_WAIT_TIME_CHANGE,"BV",               1, CONTROL_ID_INVALID, "Change waiting time" }				
	};
	#define CMDLIST_SIZE (sizeof(sCmdList)/sizeof(TGALILCMD))

	UINT uCmdSize = 0;
	if (pCmds != NULL && uBufSize > 0)
	{
		for (UINT i = 0; i < CMDLIST_SIZE; i++)
		{
			if (sCmdList[i].uTriggerCtrlID == uCtrlID)
			{
				// Put all the command with the same trigger into the list
				pCmds[uCmdSize] = sCmdList[i];
				uCmdSize++;
				if (uCmdSize > uBufSize)
				{
					// Error
					uCmdSize = 0xFFFFFFFF;
					break;
				}
			}
		}
	}
	return uCmdSize;
}

TCTRLPARAM CPCConfiguratorDlg::GetCtrlParameterInfo(UINT uCtrlID)
{
	TCTRLPARAM sParamList[] = {
		//											default, step,   min(na),    max(na), multiple, pCtrlVar
		{ "L", IDC_EDIT_PARAM_L, 0.005f, 0.005f, 0.005f, 160.0f, 2000, NULL},//&m_fParamL },
		{ "W",     IDC_EDIT_PARAM_W,              	0.005f, 0.005f, 0.005f, 60.0f,      2000, &m_fParamW },
		{ "Sd",    IDC_EDIT_PARAM_SD, 				0.005f, 0.005f, 0.005f, 60.0f, 	    2000, &m_fParamSd }, // (W+Sd) * 4 <= 260
		{ "R", IDC_EDIT_PARAM_R, 0.005f, 0.005f, 0.005f, 80.0f, 2000, NULL },//&m_fParamR },  // 2R < L
		{ "Tg1",   IDC_EDIT_PARAM_TG1, 				1.0f,   1.0f,   1.0f,   65535.0f, 	1,    &m_fParamTg1 },
		{ "Tg2",   IDC_EDIT_PARAM_TG2, 				1.0f,   1.0f,   1.0f,   65535.0f, 	1,    &m_fParamTg2 },
		{ "Spd",   IDC_EDIT_PARAM_SPEED,         	20.0f,  5.0f,   20.0f,  600.0f,     2000, &m_fParamRs },  // Speed
		{ "Rspd",  IDC_EDIT_CONV_ROLLING_SPEED, 	0.5f,   0.5f,   0.5f,   5.0f,       8000, &m_fParamCBs }, // Rolling Speed
		{ "Tw",    IDC_EDIT_CONV_WAITING_TIME, 		1.0f,   1.0f,   1.0f,   65535.0f,   1,    &m_fParamTw }, // Waiting time
		{ "Pzm",   IDC_EDIT_PARAM_PZM, 				0.005f, 0.005f, 0.005f, 50.0f,      2000, &m_fParamPzm },
		{ "Dx",    IDC_EDIT_SETUP_DX,            	0.005f, 0.005f, 0.005f, 50.0f,      2000, &m_fParamDx },
		{ "Dy",    IDC_EDIT_SETUP_DY,            	0.005f, 0.005f, 0.005f, 50.0f,      2000, &m_fParamDy },
		{ "Dz",    IDC_EDIT_SETUP_DZ,            	0.005f, 0.005f, 0.005f, 10.0f,      2000, &m_fParamDz }
	};
	#define PARAMLIST_SIZE (sizeof(sParamList)/sizeof(TCTRLPARAM))

	TCTRLPARAM sParamInfo;
	memset((void *)&sParamInfo, 0, sizeof(sParamInfo));
	for (UINT i = 0; i < PARAMLIST_SIZE; i++)
	{
		if (sParamList[i].uCtrlID == uCtrlID)
		{
			sParamInfo = sParamList[i];
			break;
		}
	}

	return sParamInfo;
}

// Set the specified edit member variables, if no parameter passed, all variables are reset to default values
void CPCConfiguratorDlg::SetMemberDefaultValues(UINT uCtrlID /*= 0xFFFFFFFF*/)
{
	TCTRLPARAM sCtrlParamInfo;

	if (uCtrlID == 0xFFFFFFFF)
	{
		for (UINT i = 0; i < CTRLID_LIST_SIZE; i++)
		{
			sCtrlParamInfo = GetCtrlParameterInfo(guCtrlIDs[i]);
			if (sCtrlParamInfo.pCtrlVar != NULL)
			{
				*sCtrlParamInfo.pCtrlVar = sCtrlParamInfo.fDefaultValue;
			}
		}
	}
	else
	{
		sCtrlParamInfo = GetCtrlParameterInfo(uCtrlID);
		if (sCtrlParamInfo.pCtrlVar != NULL)
		{
			*sCtrlParamInfo.pCtrlVar = sCtrlParamInfo.fDefaultValue;
		}
	}
}

int CPCConfiguratorDlg::SendCommands(UINT uCtrlID)
{
	UINT uCmdNum = 0;
	TGALILCMD sCmdList[10];

	memset((void *)&sCmdList, 0, sizeof(sCmdList));
	uCmdNum = GetTriggerCmdList(uCtrlID, sCmdList, 10);

	// Buffer error
	if (uCmdNum == 0xFFFFFFFF)
	{
		// TODO:
	}
	else
	{
		TGALILCMD sCmdTmp;

		// Sort the commands in order
		for (UINT j = 0; j < uCmdNum - 1; j++)
		{
			for (UINT k = j + 1; k < uCmdNum; k++)
			{
				if (sCmdList[j].uCmdOrder > sCmdList[k].uCmdOrder)
				{
					sCmdTmp = sCmdList[j];
					sCmdList[j] = sCmdList[k];
					sCmdList[k] = sCmdTmp;
				}
			}
		}

		// Compose and execute the commands one by one
		char buf[128];
		CString strBuf;
		for (UINT i = 0; i < uCmdNum; i++)
		{
			// Command is composed of prefix and options
			UINT optionsValue = 0xFFFFFFFF;
			if (sCmdList[i].uOption1CtrlID != CONTROL_ID_INVALID)
			{
				TCTRLPARAM sCtrlParamInfo;
				sCtrlParamInfo = GetCtrlParameterInfo(sCmdList[i].uOption1CtrlID);
				optionsValue = (UINT)((*sCtrlParamInfo.pCtrlVar) * sCtrlParamInfo.uMulitiplier);
				//optionsValue = optionsValue
			}
			strBuf.Empty();
            memset(buf, 0, sizeof(buf));
            if ( optionsValue == 0xFFFFFFFF )
            {
    			sprintf_s(buf, "%s", sCmdList[i].strCmdPrefix, optionsValue);
            }
            else
            {
                sprintf_s(buf, "%s%d", sCmdList[i].strCmdPrefix, optionsValue);
            }
			int cmdRet = m_galil.Command(buf);
			CString tempBuf = L"Gaili sends command:";
            strBuf = CString(buf);
			tempBuf += strBuf;
            tempBuf += "\n";
            m_log.LogWrite(tempBuf);

			memset(buf, 0, sizeof(buf));
			strBuf.Empty();
			sprintf_s(buf, "Command description:%s, prefix: %s, optionValue:%d, ret:%d\n", sCmdList[i].strCmdDescrip, sCmdList[i].strCmdPrefix, optionsValue, cmdRet);
	        strBuf = CString(buf);
			m_log.LogWrite(strBuf);
		}
	}

	return 0;
}

void CPCConfiguratorDlg::OnClickedBtnConnect()
{
	if (m_bConnected)
	{
		m_log.LogWrite(_T("Disconnect.\n"));
        int ret = m_galil.DisConnect();
#ifndef _CONNECTION_DEBUG
        if ( ret == G_NO_ERROR )
#endif            
        {
    		m_bConnected = FALSE;
		    m_btnConnect.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_CONNECT)));
        }
	}
	else
	{
		m_log.LogWrite(_T("Connect...\n"));
		int ret = m_galil.Connect();
#ifndef _CONNECTION_DEBUG
		if ( ret == G_NO_ERROR )
#endif            
		{
			m_bConnected = TRUE;
			m_btnConnect.SetIcon(::LoadIcon(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_DISCONNECT)));
		}

        CString strBuf;
        strBuf.Format(_T("Connection status: %d\n"), ret);
		m_log.LogWrite(strBuf);
	}
}

void CPCConfiguratorDlg::OnClickedBtnSaveParam()
{
	SendCommands(IDC_BTN_SAVE_PARAM);
}

void CPCConfiguratorDlg::OnClickedBtnAxisXMinus()
{
	SendCommands(IDC_BTN_AXIS_X_MINUS);
}


void CPCConfiguratorDlg::OnClickedBtnAxisXPlus()
{
	SendCommands(IDC_BTN_AXIS_X_PLUS);
}


void CPCConfiguratorDlg::OnClickedBtnAxisYMinus()
{
	SendCommands(IDC_BTN_AXIS_Y_MINUS);
}


void CPCConfiguratorDlg::OnClickedBtnAxisYPlus()
{
	SendCommands(IDC_BTN_AXIS_Y_PLUS);
}


void CPCConfiguratorDlg::OnClickedBtnAxisZMinus()
{
	SendCommands(IDC_BTN_AXIS_Z_MINUS);
}


void CPCConfiguratorDlg::OnClickedBtnAxisZPlus()
{
	SendCommands(IDC_BTN_AXIS_Z_PLUS);
}


void CPCConfiguratorDlg::OnClickedBtnConveyorClampJig()
{
	SendCommands(IDC_BTN_CONVEYOR_CLAMP_JIG);
}


void CPCConfiguratorDlg::OnClickedBtnConveyorLooseJig()
{
	SendCommands(IDC_BTN_CONVEYOR_LOOSE_JIG);
}


void CPCConfiguratorDlg::OnClickedBtnConveyorSpeedChange()
{
	SendCommands(IDC_BTN_CONVEYOR_SPEED_CHANGE);
}


void CPCConfiguratorDlg::OnClickedBtnConveyorStart()
{
	SendCommands(IDC_BTN_CONVEYOR_START);
}


void CPCConfiguratorDlg::OnClickedBtnConveyorStop()
{
	SendCommands(IDC_BTN_CONVEYOR_STOP);
}

void CPCConfiguratorDlg::OnClickedBtnMotorStart()
{
	SendCommands(IDC_BTN_MOTOR_START);
}


void CPCConfiguratorDlg::OnClickedBtnMotorStop()
{
	SendCommands(IDC_BTN_MOTOR_STOP);
}


void CPCConfiguratorDlg::OnClickedBtnRoutineReset()
{
	SendCommands(IDC_BTN_ROUTINE_RESET);
}


void CPCConfiguratorDlg::OnClickedBtnRoutineStart()
{
	SendCommands(IDC_BTN_ROUTINE_START);
}


void CPCConfiguratorDlg::OnClickedBtnRoutineStop()
{
	SendCommands(IDC_BTN_ROUTINE_STOP);
}


void CPCConfiguratorDlg::OnClickedBtnSetStartPoint()
{
	SendCommands(IDC_BTN_SET_START_POINT);
}


void CPCConfiguratorDlg::OnClickedBtnSetUp()
{
	SendCommands(IDC_BTN_SET_UP);
}

void CPCConfiguratorDlg::OnClickedBtnLock()
{
	m_bUnlocked = FALSE;
	UnlockConfigurator(m_bUnlocked);
}

void CPCConfiguratorDlg::OnClickedBtnUnlock()
{
	CAuthorize dlg;
	//m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		m_bUnlocked = TRUE;
		UnlockConfigurator(m_bUnlocked);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		//TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
	}
}

int CPCConfiguratorDlg::UnlockConfigurator(BOOL bUnlock)
{
	UINT uCtrlIDs[] = {
		IDC_EDIT_PARAM_L,
		IDC_EDIT_PARAM_W,
		IDC_EDIT_PARAM_R,
		IDC_EDIT_PARAM_SD,
		IDC_EDIT_PARAM_SPEED,
		IDC_EDIT_CONV_ROLLING_SPEED,
		IDC_EDIT_SETUP_DX,
		IDC_EDIT_SETUP_DY,
		IDC_EDIT_SETUP_DZ,
        IDC_EDIT_PARAM_PZM,
        IDC_EDIT_PARAM_TG1,
        IDC_EDIT_PARAM_TG2,
        IDC_EDIT_CONV_WAITING_TIME,

		IDC_BTN_SAVE_PARAM,
		IDC_BTN_SET_UP,
		IDC_BTN_SET_START_POINT,
		IDC_BTN_CONVEYOR_SPEED_CHANGE,
		IDC_BTN_CONVEYOR_START,
		IDC_BTN_CONVEYOR_STOP,
		IDC_BTN_CONVEYOR_CLAMP_JIG,
		IDC_BTN_CONVEYOR_LOOSE_JIG,
		IDC_BTN_AXIS_X_MINUS,
		IDC_BTN_AXIS_X_PLUS,
		IDC_BTN_AXIS_Y_MINUS,
		IDC_BTN_AXIS_Y_PLUS,
		IDC_BTN_AXIS_Z_MINUS,
		IDC_BTN_AXIS_Z_PLUS,
		IDC_BTN_PARAM_TESTING,
		IDC_BTN_CONVEYOR_WAIT_TIME_CHANGE
	};
#define SIZE (sizeof(uCtrlIDs)/sizeof(UINT))

	for (UINT i = 0; i < SIZE; i++)
	{
		GetDlgItem(uCtrlIDs[i])->EnableWindow(bUnlock);
	}

	return 0;
}

void CPCConfiguratorDlg::OnClickedBtnParamTesting()
{
	SendCommands(IDC_BTN_PARAM_TESTING);
}


void CPCConfiguratorDlg::OnClickedBtnConveyorWaitTimeChange()
{
	SendCommands(IDC_BTN_CONVEYOR_WAIT_TIME_CHANGE);
}


//BOOL CPCConfiguratorDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
//{
//    NMHDR* pNMHDR =  (NMHDR *)lParam; 
//    if(pNMHDR &&pNMHDR->code == NM_KILLFOCUS) 
//    {
//       CWnd *pFocus =  CWnd::GetFocus(); // call to a static function 
//       if(pFocus &&(pFocus->GetParent() ==  this))
//       {
//          //if(pFocus->GetDlgCtrlID() != IDCANCEL) 
//          { 
//			  int uCtrlId = pNMHDR->idFrom;
//              // Ok, if the focus is not in the cancelbutton... 
//              if(pNMHDR->idFrom)
//              {
//                 //ValAndSubmit(pNMHDR->idFrom);
//                 if (!UpdateData(TRUE))
//                 {
//                     // Reset to default value
//                     TCTRLPARAM sCtrlParamInfo = GetCtrlParameterInfo(uCtrlId);
//                     float fDefaultValue = sCtrlParamInfo.fDefaultValue;
//                     char buf[32];
//                     memset(buf, 0, sizeof(buf));
//                     sprintf_s(buf, "%1.3f", fDefaultValue);
//                     CString str = CString(buf);
//                     pFocus->SetWindowText(str);                 
//                 }
//              }
//          }
//       }       
//    }
//
//	return CDialogEx::OnNotify(wParam, lParam, pResult);
//}


BOOL CPCConfiguratorDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	UINT notificationCode = (UINT)HIWORD(wParam);

	// For List control I handle it in another way....
	if (0)//(notificationCode == EN_KILLFOCUS) ||
		//(notificationCode == LBN_KILLFOCUS) ||
		//(notificationCode == CBN_KILLFOCUS) ||
		//(notificationCode == NM_KILLFOCUS) ||
		//(notificationCode == WM_KILLFOCUS)) 
	{

		CWnd *pFocus = CWnd::GetFocus(); // call to a static function 
		if (pFocus && (pFocus->GetParent() == this))
		{
			int uCtrlId = pFocus->GetDlgCtrlID();
			if (uCtrlId != IDCANCEL)
			{
				// Ok, if the focus is not in the cancelbutton... 
				if (!UpdateData(TRUE))
				{
					// Reset to default value
					TCTRLPARAM sCtrlParamInfo = GetCtrlParameterInfo(uCtrlId);
					float fDefaultValue = sCtrlParamInfo.fDefaultValue;
					char buf[32];
					memset(buf, 0, sizeof(buf));
					sprintf_s(buf, "%1.3f", fDefaultValue);
					CString str = CString(buf);
					pFocus->SetWindowText(str);
				}
			}
		}
	}

	return CDialogEx::OnCommand(wParam, lParam);
}


void CPCConfiguratorDlg::OnStnClickedStaticRoutineDemo()
{
	// TODO: Add your control notification handler code here
}
