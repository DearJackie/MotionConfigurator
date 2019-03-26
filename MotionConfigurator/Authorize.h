#pragma once


// CAuthorize dialog
#include "resource.h"

class CAuthorize : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthorize)

public:
	CAuthorize(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAuthorize();

// Dialog Data
	enum { IDD = IDD_DIALOG_AUTHORATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
