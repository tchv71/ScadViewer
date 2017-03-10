// DepthDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "DepthDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDepthDialogBar, CMFCToolBar)
/////////////////////////////////////////////////////////////////////////////
// CDepthDialogBar

CDepthDialogBar::CDepthDialogBar(UINT nId) :
	m_nId(nId)
{
}

CDepthDialogBar::~CDepthDialogBar()
{
}


BEGIN_MESSAGE_MAP(CDepthDialogBar, CMFCToolBar)
	//{{AFX_MSG_MAP(CDepthDialogBar)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
//	ON_WM_NCPAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDepthDialogBar message handlers
BOOL CDepthDialogBar::Create(UINT IDD, CWnd* pParentWnd, DWORD dwStyle , UINT nID)
{
	m_lpszBarTemplateName = MAKEINTRESOURCE(IDD);
	BOOL bRes = CMFCToolBar::Create(pParentWnd, dwStyle, nID);
	EnableToolTips();
	return bRes;
}

CSize CDepthDialogBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CRect rcSlider;
	m_dwStyle =  m_dwStyle | CBRS_FLYBY;
	GetDlgItem(m_nId)->GetWindowRect(rcSlider);
	ScreenToClient(rcSlider);
	return CSize(26/*rcSlider.right+5*/, rcSlider.bottom+15);
}


INT_PTR CDepthDialogBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	INT_PTR nRes = CWnd::OnToolHitTest(point, pTI);
	if (nRes!= 0 && pTI)
		pTI->uFlags &= ~(TTF_NOTBUTTON|TTF_CENTERTIP);
	return nRes;

}

void CDepthDialogBar::OnSize(UINT nType, int cx, int cy) 
{
	CMFCToolBar::OnSize(nType, cx, cy);
	
	CWnd *pWnd = GetDlgItem(m_nId);
	if (!pWnd)
		return;
	CRect rc;
	pWnd->GetWindowRect(&rc);
	ScreenToClient(&rc);
	pWnd->SetWindowPos(nullptr,(cx-rc.Width())/2, rc.top, 0,0, SWP_NOSIZE);
	
}


//void CDepthDialogBar::OnNcPaint()
//{
//	m_Impl.DrawNcArea();
//}
