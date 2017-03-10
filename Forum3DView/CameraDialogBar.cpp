// CameraDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "CameraDialogBar.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraDialogBar
IMPLEMENT_DYNAMIC(CCameraDialogBar, CDepthDialogBar)


CCameraDialogBar::CCameraDialogBar() :
	CDepthDialogBar(100),
	m_nFocusLength(50),
	m_bChangeDistance(false)
{
}

CCameraDialogBar::~CCameraDialogBar()
{
}


BEGIN_MESSAGE_MAP(CCameraDialogBar, CDepthDialogBar)
	//{{AFX_MSG_MAP(CCameraDialogBar)
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCameraDialogBar message handlers


BOOL CCameraDialogBar::Create(UINT nIDTemplate, CWnd* pParentWnd, UINT nStyle, UINT nID)
{
	if (!CDepthDialogBar::Create(nIDTemplate, pParentWnd,  nStyle,nID))
		return FALSE;
	SetBorders(1,1,1,1);

	CSliderCtrl *pSlider = static_cast<CSliderCtrl *>(GetDlgItem(IDC_SLIDER_FLENGTH));
	ASSERT(pSlider);
	pSlider->SetRange(13,130);
	pSlider->SetTicFreq(10);
	pSlider->SetPos(m_nFocusLength);
	CString str;
	str.Format(_T("%d"), m_nFocusLength);
	GetDlgItem(IDC_STATIC_FLENGTH)->SetWindowText(str);
	return TRUE;
}



void CCameraDialogBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl *pSlider = reinterpret_cast<CSliderCtrl *>(pScrollBar);
	ASSERT(pSlider);
	if (pSlider->GetDlgCtrlID()==IDC_SLIDER_FLENGTH)
	{
		m_nFocusLength = pSlider->GetPos();
		CString str;
		str.Format(_T("%d"), m_nFocusLength);
		GetDlgItem(IDC_STATIC_FLENGTH)->SetWindowText(str);
		m_bChangeDistance = static_cast<CButton *>(GetDlgItem(IDC_CHECK_CHANGE_DIST))->GetCheck() == BST_CHECKED;
		GetOwner()->SendMessage(WM_COMMAND, ID_CAMERA_CHANGED);
	}
	CDepthDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

CSize CCameraDialogBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	if (!bHorz)
		return CSize(0,0);
	m_dwStyle =  m_dwStyle | CBRS_FLYBY;
	CRect rcSlider;
	GetDlgItem(IDC_STATIC_MM)->GetWindowRect(rcSlider);
	ScreenToClient(rcSlider);
	return  CSize(rcSlider.right+8, 26);
}




INT_PTR CCameraDialogBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	INT_PTR nRes = CWnd::OnToolHitTest(point, pTI);
	if (nRes!= 0 && pTI)
		pTI->uFlags &= ~(TTF_NOTBUTTON|TTF_CENTERTIP);
	return nRes;
}

void CCameraDialogBar::OnSize(UINT nType, int cx, int cy) 
{
	CDepthDialogBar::OnSize(nType, cx, cy);
	
	CenterHeight(IDC_CHECK_CHANGE_DIST,cy);
	CenterHeight(IDC_SLIDER_FLENGTH,cy);
	CenterHeight(IDC_STATIC_FLENGTH,cy);
	CenterHeight(IDC_STATIC_MM,cy);
}

void CCameraDialogBar::CenterHeight(UINT nID, int cy) const
{
	CWnd *pWnd = GetDlgItem(nID);
	if (!pWnd)
		return;
	CRect rc;
	pWnd->GetWindowRect(&rc);
	ScreenToClient(&rc);
	pWnd->SetWindowPos(nullptr,rc.left, (cy-rc.Height())/2, 0,0, SWP_NOSIZE);

}
