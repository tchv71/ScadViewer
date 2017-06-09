// DelimDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DelimDialog.h"
#include "afxdialogex.h"
#include "..\OglIso\OglIso.h"
#include "..\ForumView_RUS\resource.h"


// CDelimDialog dialog

IMPLEMENT_DYNAMIC(CDelimDialog, CDialogEx)

CDelimDialog::CDelimDialog(CWnd* pParent /*=NULL*/, double val, const struct DefMapInfo* pDMI)
	: CDialogEx(CDelimDialog::IDD, pParent), m_dblValue(val), m_pDMI(pDMI)
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
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelimDialog::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CDelimDialog message handlers


BOOL CDelimDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	for (int i = 0; i < m_pDMI->Scale_count; i++)
	{
		const double val =  m_pDMI->binter[i];
		CString strVal;
		strVal.Format(_T("%.2f"), val);
		m_editValue.AddString(strVal);
	}

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDelimDialog::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CDelimDialog::OnOK()
{
	CDataExchange dx(this, true);
	DDX_Text(&dx, IDC_EDIT_VALUE, m_dblValue);
	const double val = m_dblValue;
	const double fMin = m_pDMI->binter[0] - 0.01f;
	const double fMax = m_pDMI->einter[m_pDMI->Scale_count - 1]+0.01f;
	if (val< fMin || val> fMax)
	{
		CString strMsg;
		strMsg.Format(IDS_DELIM_OUT_OF_RANGE, fMin, fMax);
		AfxMessageBox(strMsg);
		return;
	}


	CDialogEx::OnOK();
}
