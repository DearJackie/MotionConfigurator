// Authorize.cpp : implementation file
//

#include "stdafx.h"
#include "Authorize.h"
#include "afxdialogex.h"


// CAuthorize dialog

IMPLEMENT_DYNAMIC(CAuthorize, CDialogEx)

CAuthorize::CAuthorize(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuthorize::IDD, pParent)
{

}

CAuthorize::~CAuthorize()
{
}

void CAuthorize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAuthorize, CDialogEx)
END_MESSAGE_MAP()


// CAuthorize message handlers
