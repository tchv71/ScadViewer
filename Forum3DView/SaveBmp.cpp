// SaveBmp.cpp : implementation file
//

#include "stdafx.h"
#include "forum3dview.h"
#include "SaveBmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveBmp dialog


CSaveBmp::CSaveBmp(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveBmp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveBmp)
	m_nBmpWidth = 0;
	m_nBmpHeight = 0;
	//}}AFX_DATA_INIT
}


void CSaveBmp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveBmp)
	DDX_Text(pDX, IDC_EDIT_BMP_HEIGHT, m_nBmpWidth);
	DDX_Text(pDX, IDC_EDIT_BMP_WIDTH, m_nBmpHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveBmp, CDialog)
	//{{AFX_MSG_MAP(CSaveBmp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveBmp message handlers
