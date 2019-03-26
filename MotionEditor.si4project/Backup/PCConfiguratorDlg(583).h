
// PCConfiguratorDlg.h : header file
//

#pragma once

#include "CGalil.h"
#include "Log.h"
#include "afxwin.h"

// Global data
typedef struct strControlParam {
	const char *strParamName; // The parameter name defined in the motion controller application
	UINT uCtrlID;  // The control ID of the parameter
	float fDefaultValue; // Default value after application starts
	float fMinStep;  // Minimum change step for the parameter
	float fMin; // Minimum value
	float fMax; // Max Value
	UINT uMulitiplier; // Mulitiplier of the paramter to apply to real value
	float *pCtrlVar; // The control value variable
}TCTRLPARAM;

#define CONTROL_ID_INVALID     0xFFFFFFFF
typedef struct strGalilCommand {
	UINT uTriggerCtrlID; // The control ID which will trigger the command
	const char *strCmdPrefix; // Prefix of the command
	UINT uCmdOrder; // The order of the current command, the problem is the same trigger can involves several commands, and
	                // they shall follow some order, starting from "0"
	UINT uOption1CtrlID; // Control ID of the input option. Command option1 depends on the inputs in the CEDIT control
	const char *strCmdDescrip; // Debug information
}TGALILCMD;

// CPCConfiguratorDlg dialog
class CPCConfiguratorDlg : public CDialogEx
{
// Construction
public:
	CPCConfiguratorDlg(CWnd* pParent = NULL);	// standard constructor
	~CPCConfiguratorDlg();

// Dialog Data
	enum { IDD = IDD_PCCONFIGURATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	CGalil m_galil;
	CLog m_log;
	BOOL m_bUnlocked;
	BOOL m_bConnected;

	void LoadControlIcons(void);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnGalilConnect();
	// The IP address to set, if empty, it will use the default one
	//CEdit m_setIP;
	// The output window for logging and feedback
	//CStatic m_outLogWindow;
	// The current password which is used by the application
	//CEdit m_strPassword;

	CButton m_btnMinusX;
	CButton m_btnPlusX;
	CButton m_btnMinusY;
	CButton m_btnPlusY;
	CButton m_btnMinusZ;
	CButton m_btnPlusZ;
	CButton m_btnConnect;
	CButton m_btnRoutineStart;
	CButton m_btnRoutineStop;
	CButton m_btnRoutineReset;
//	CStatic m_staticAxisX;
//	CStatic m_staticAxisY;
//	CStatic m_staticAxisZ;
//	CStatic m_staticRoutineDemo;
//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
//	afx_msg void OnUpdateEditParamL();
//	afx_msg void OnKillfocusEditParamL();
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	// Set the specified edit member variables, if no parameter passed, all variables are reset to default values
	TCTRLPARAM GetCtrlParameterInfo(UINT uCtrlID);
	void SetMemberDefaultValues(UINT uCtrlID = 0xFFFFFFFF);
	// Note that one control may trigger several commands, return value is the command number of the trigger
	// Make sure the buffer is enough
	UINT GetTriggerCmdList(UINT uCtrlID, TGALILCMD *pCmds, UINT uBufSize);
	//Send the commands by the trigger one by one
	int SendCommands(UINT uCtrlID);
	int UnlockConfigurator(BOOL bUnlock);
public:
//	float m_fParamL;
//	float m_fParamR;
//	float m_fParamSd;
//	float m_fParamW;
	// Speed
//	float m_fParamRs;
	// Rolling Speed
//	float m_fParamCBs;
//	float m_fParamDx;
//	float m_fParamDy;
//	float m_fParamDz;
	afx_msg void OnClickedBtnConnect();
	afx_msg void OnClickedBtnSaveParam();
	afx_msg void OnClickedBtnAxisXMinus();
	afx_msg void OnClickedBtnAxisXPlus();
	afx_msg void OnClickedBtnAxisYMinus();
	afx_msg void OnClickedBtnAxisYPlus();
	afx_msg void OnClickedBtnAxisZMinus();
	afx_msg void OnClickedBtnAxisZPlus();
	afx_msg void OnClickedBtnConveyorClampJig();
	afx_msg void OnClickedBtnConveyorLooseJig();
	afx_msg void OnClickedBtnConveyorSpeedChange();
	afx_msg void OnClickedBtnConveyorStart();
	afx_msg void OnClickedBtnConveyorStop();
	afx_msg void OnClickedBtnLock();
	afx_msg void OnClickedBtnMotorStart();
	afx_msg void OnClickedBtnMotorStop();
	afx_msg void OnClickedBtnRoutineReset();
	afx_msg void OnClickedBtnRoutineStart();
	afx_msg void OnClickedBtnRoutineStop();
	afx_msg void OnClickedBtnSetStartPoint();
	afx_msg void OnClickedBtnSetUp();
	afx_msg void OnClickedBtnUnlock();
	float m_fParamTw;

	float m_fParamPzm;
	float m_fParamTg1;
	float m_fParamTg2;
	afx_msg void OnClickedBtnParamTesting();
	afx_msg void OnClickedBtnConveyorWaitTimeChange();
//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnStnClickedStaticRoutineDemo();
	float m_fParamL;
	float m_fParamR;
	float m_fParamSd;
	float m_fParamW;
	float m_fParamRs;
	// Rolling Speed
	float m_fParamCBs;
	float m_fParamDx;
	float m_fParamDy;
	float m_fParamDz;
//	afx_msg void OnClickedBtnGo();
	afx_msg void OnClickedBtnGo();
};
