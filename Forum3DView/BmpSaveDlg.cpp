// BmpSaveDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "scadviewer.h"
#include "resource.h"
#include "BmpSaveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpSaveDlg

IMPLEMENT_DYNAMIC(CBmpSaveDlg, CFileDialog)

CBmpSaveDlg::CBmpSaveDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd),
		m_bLockProp(TRUE)
{
	//{{AFX_DATA_INIT(CSaveBmp)
	m_nBmpWidth = 0;
	m_nBmpHeight = 0;
	//}}AFX_DATA_INIT
	SetTemplate(0,IDD_SAVE_BMP);
}


BEGIN_MESSAGE_MAP(CBmpSaveDlg, CFileDialog)
	//{{AFX_MSG_MAP(CBmpSaveDlg)
	ON_CONTROL(EN_CHANGE,IDC_EDIT_BMP_WIDTH, OnWidthChange)
	ON_CONTROL(EN_CHANGE,IDC_EDIT_BMP_HEIGHT, OnHeightChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CBmpSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CFileDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveBmp)
	DDX_Control(pDX,IDC_EDIT_BMP_WIDTH,m_ctlEditWidth);
	DDX_Control(pDX,IDC_EDIT_BMP_HEIGHT,m_ctlEditHeight);
	DDX_Text(pDX, IDC_EDIT_BMP_WIDTH, m_nBmpWidth);
	DDX_Text(pDX, IDC_EDIT_BMP_HEIGHT, m_nBmpHeight);
	DDX_Check(pDX,IDC_CHECK_LOCK_PROP, m_bLockProp);
	//}}AFX_DATA_MAP
}



BOOL CBmpSaveDlg::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	m_fAspect = float(m_nBmpWidth)/m_nBmpHeight;
	m_ctlEditHeight.SetLimitText(4);
	m_ctlEditWidth.SetLimitText(4);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBmpSaveDlg::OnWidthChange()
{
	UpdateData(true);
	if (m_bLockProp)
	{
		m_nBmpHeight = int(m_nBmpWidth/m_fAspect);
		UpdateData(false);
	}

}


void CBmpSaveDlg::OnHeightChange()
{
	UpdateData(true);
	if (m_bLockProp)
	{
		m_nBmpWidth = int(m_nBmpHeight*m_fAspect);
		UpdateData(false);
	}

}