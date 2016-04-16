#include "stdafx.h"
#include "ResultsDialogBar.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CResultsDialogBar
IMPLEMENT_DYNAMIC(CResultsDialogBar, CDepthDialogBar)


CResultsDialogBar::CResultsDialogBar(void) :
	CDepthDialogBar(100)	
{
}


CResultsDialogBar::~CResultsDialogBar(void)
{
}

CSize CResultsDialogBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	if (!bHorz)
		return CSize(0,0);
	m_dwStyle =  m_dwStyle | CBRS_FLYBY;
	CRect rcSlider;
	GetDlgItem(IDC_COMBO_LOAD)->GetWindowRect(rcSlider);
	ScreenToClient(rcSlider);
	return  CSize(rcSlider.right+8, 26);
}
BEGIN_MESSAGE_MAP(CResultsDialogBar, CDepthDialogBar)
	ON_CBN_SELCHANGE(IDC_COMBO_FACTOR, &CResultsDialogBar::OnCbnSelchangeComboFactor)
END_MESSAGE_MAP()


// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CResultsDialogBar::OnCbnSelchangeComboFactor()
{
}
