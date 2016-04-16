// DelimDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DelimDialog.h"
#include "afxdialogex.h"


// CDelimDialog dialog

IMPLEMENT_DYNAMIC(CDelimDialog, CDialogEx)

CDelimDialog::CDelimDialog(CWnd* pParent /*=NULL*/, double val)
	: CDialogEx(CDelimDialog::IDD, pParent), m_dblValue(val)
{

}

CDelimDialog::~CDelimDialog()
{
}

void CDelimDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_editValue);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_dblValue);
}


BEGIN_MESSAGE_MAP(CDelimDialog, CDialogEx)
END_MESSAGE_MAP()


// CDelimDialog message handlers


BOOL CDelimDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
