// ScaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Forum3DView.h"
#include "ScaleDlg.h"
#include "afxdialogex.h"


// CScaleDlg dialog

IMPLEMENT_DYNAMIC(CScaleDlg, CDialogEx)

CScaleDlg::CScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScaleDlg::IDD, pParent)
{

}

CScaleDlg::~CScaleDlg()
{
}

void CScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScaleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_HOT, &CScaleDlg::OnBnClickedButtonHot)
END_MESSAGE_MAP()


// CScaleDlg message handlers


void CScaleDlg::OnBnClickedButtonHot()
{
	// TODO: Add your control notification handler code here
}
