// IsoViewerFrame.cpp : implementation file
//
// Copyright (C) 2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "IsoViewerFrame.h"
#include "resource.h"
#include "IsoViewGeometry.h"
#include "ScadViewerView.h"
#include "ScadViewerDoc.h"
#include "3dIso.hpp"
#include "ForumView_ENG/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIsoViewerFrame

IMPLEMENT_DYNCREATE(CIsoViewerFrame, CScadViewerFrame)


BEGIN_MESSAGE_MAP(CIsoViewerFrame, CScadViewerFrame)
	//{{AFX_MSG_MAP(CIsoViewerFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_EXPORT_TO_DXF, OnUpdateExportToDxf)
	ON_UPDATE_COMMAND_UI(IDC_SLIDER_DEFORM_SCALE, OnUpdateSliderDefScale)
	ON_BN_CLICKED(IDC_CHECK_ISOLINES, OnCheckIsolines)
	ON_BN_CLICKED(IDC_CHECK_VALUES, OnCheckValues)
	ON_BN_CLICKED(IDC_CHECK_EGGS, OnCheckEggs)
	ON_UPDATE_COMMAND_UI(IDC_BTN_ISOLINES, OnUpdateCheckIsolines)
	ON_COMMAND(IDC_BTN_ISOLINES, OnBtnIsolines)
	ON_UPDATE_COMMAND_UI(IDC_BTN_VALUES, OnUpdateBtnValues)
	ON_UPDATE_COMMAND_UI(IDC_BTN_EGGS, OnUpdateBtnEggs)
	ON_UPDATE_COMMAND_UI(ID_FACTOR_GROUP, OnUpdateFactorGroup)
	ON_COMMAND(ID_FACTOR_DISPLACEMENTS, OnFactorDisplacements)
	ON_COMMAND(ID_FACTOR_STRESSFIELDS, OnFactorStressfields)
	ON_COMMAND(ID_FACTOR_STRESSCOLOURMAP, OnFactorStresscolourmap)
	ON_UPDATE_COMMAND_UI(ID_FACTOR_DISPLACEMENTS, OnUpdateFactorDisplacements)
	ON_UPDATE_COMMAND_UI(ID_FACTOR_STRESSFIELDS, OnUpdateFactorStressfields)
	ON_UPDATE_COMMAND_UI(ID_FACTOR_STRESSCOLOURMAP, OnUpdateFactorStresscolourmap)
	ON_UPDATE_COMMAND_UI(IDC_COMBO_FACTOR, OnUpdateCombo)
	ON_UPDATE_COMMAND_UI(IDC_COMBO_LOAD, OnUpdateCombo)
	ON_COMMAND(IDC_BTN_VALUES, OnCheckValues)
	ON_COMMAND(IDC_BTN_EGGS, OnCheckEggs)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESULTS, OnUpdateViewResults)
	ON_CBN_SELCHANGE(IDC_COMBO_FACTOR, OnCbnSelchangeComboFactor)
	ON_CBN_SELCHANGE(IDC_COMBO_LOAD, OnCbnSelchangeComboLoad)
	ON_COMMAND(ID_PARAMS_CHANGED, OnParamsChanged)
	//}}AFX_MSG_MAP
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CIsoViewerFrame message handlers

CIsoViewerFrame::CIsoViewerFrame() :
	m_hWndParent(nullptr),
	m_nTimer(0),
	m_wndDefScaleDialogBar(IDC_SLIDER_DEFORM_SCALE),
	m_wndResParams()
{
}

CIsoViewerFrame::~CIsoViewerFrame()
{
}

//BEGIN_BUTTON_MAP(btnResultsMap)
//	SCTWOPART_BUTTON( ID_FACTOR_GROUP, ID_DROPARROW, 0, 0, IDR_POPUP_MENUS, 7, TPM_LEFTALIGN )
//END_BUTTON_MAP()

int CIsoViewerFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScadViewerFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//m_wndToolBar.SetButtonMap(btnResultsMap);


	if (!m_wndToolBar.Create(this,WS_VISIBLE | WS_CHILD | CBRS_TOP ,IDR_RESULTS_TOOLBAR) ||
		!m_wndToolBar.LoadToolBar(IDR_RESULTS_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	//m_wndToolBar.RemoveButton(m_wndToolBar.GetCount()-1);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//CMenu mnuPopup;
	//mnuPopup.LoadMenu(IDR_POPUP_MENUS);
	//CMenu *mnuPopupMenu = mnuPopup.GetSubMenu(7);
	//ASSERT(mnuPopupMenu);
	//CDropdownButton bn(ID_FACTOR_GROUP,mnuPopupMenu->m_hMenu, nullptr);
	//m_wndToolBar.ReplaceButton(ID_FACTOR_GROUP,bn);

	if (!m_wndDefScaleDialogBar.Create(IDD_DEFORM_SCALE, this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT |CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED, IDD_DEFORM_SCALE ))
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      // fail to create
	}

	if (!m_wndResParams.Create(IDD_RES_PARAMS, this, WS_CHILD | WS_VISIBLE | CBRS_RIGHT |CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED, IDD_RES_PARAMS))
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      // fail to create
	}

	UINT nID = 110;
	CString strCaption;
	strCaption.LoadString(IDS_SCALE_CAPTION);
	//strCaption.LoadString(IDS_FOLDER_TREE_CAPTION);
	if (!m_ScaleWnd.Create(IDD_SCALE, strCaption, this, CSize(200,200), TRUE, nID))
	{
		TRACE(_T("Failed to create docking window"));
		return -1;
	}
	m_ScaleWnd.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_TOP|CBRS_ALIGN_RIGHT|CBRS_ALIGN_BOTTOM);

	DockPane(&m_ScaleWnd, AFX_IDW_DOCKBAR_RIGHT);

	m_nTimer = SetTimer(1, 100, nullptr);

	m_wndDefScaleDialogBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	m_wndResParams.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	//m_wndDefScaleDialogBar.SetExBarStyle(m_wndDefScaleDialogBar.GetExBarStyle() | CBRS_EX_UNIDIRECTIONAL);
	//m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC);

	DockPaneRightOf(&m_wndToolBar, &m_wndCameraDialogBar);
	DockPaneRightOf(&m_wndResParams, &m_wndToolBar);
	DockPaneBottomOf(&m_wndDefScaleDialogBar, &m_wndDepthDialogBar);
	CSliderCtrl *pWnd = static_cast<CSliderCtrl *>(m_wndDefScaleDialogBar.GetDlgItem(IDC_SLIDER_DEFORM_SCALE));
	pWnd->SetRange(0, 100);
	pWnd->SetPos(0);
	pWnd->SetTicFreq(10);
	return 0;
}

void CIsoViewerFrame::OnTimer(UINT_PTR nIDEvent) 
{
	AfxGetApp()->OnIdle(-1);
	
	CScadViewerFrame::OnTimer(nIDEvent);
}

void CIsoViewerFrame::OnDestroy() 
{
	if (m_nTimer)
		KillTimer(m_nTimer);
	CWnd *pTmp = AfxGetApp()->m_pMainWnd;
	AfxGetApp()->m_pMainWnd = nullptr;
	CScadViewerFrame::OnDestroy();
	AfxGetApp()->m_pMainWnd = pTmp;
	//::SetActiveWindow(::GetParent(m_hWndParent));
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateExportToDxf(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateSliderDefScale(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);	
}

//BOOL CIsoViewerFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
//{
//	if (wParam == IDC_SLIDER_DEFORM_SCALE && m_p3DView->GetDocument()->m_bViewResults)
//	{
//		LPNMHDR pNmhdr = LPNMHDR(lParam);
//		if (int(pNmhdr->code) == NM_CUSTOMDRAW)
//		{
//			UpdateDeformScale();
//		}
//	}
//	
//	return CScadViewerFrame::OnNotify(wParam, lParam, pResult);
//}

void CIsoViewerFrame::UpdateDeformScale(void) const
{
	CSliderCtrl *pSlider = reinterpret_cast<CSliderCtrl*>(m_wndDefScaleDialogBar.GetDlgItem(IDC_SLIDER_DEFORM_SCALE));
	if (pSlider && pSlider->GetDlgCtrlID() == IDC_SLIDER_DEFORM_SCALE)
	{
#if defined(SCAD11) || defined(SCAD21)
		CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_p3DView->GetDocument()->m_pViewGeometry);
		if (pGeom)
		{
			pGeom->SetDefScale(pSlider->GetPos());
			pGeom->BuildArrays();
			m_p3DView->Invalidate();
		}
#endif
	}
}


// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnCheckIsolines() 
{
#if defined(SCAD11) || defined(SCAD21)
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_p3DView->GetDocument()->m_pViewGeometry);
	if (pGeom)
	{
		CWaitCursor crWait;
		pGeom->m_Params.bDrawIsoLines = !pGeom->m_Params.bDrawIsoLines;
		pGeom->OnParamsChanged();
		m_p3DView->RedoCut();
		m_p3DView->Invalidate();
	}
#endif
}

void CIsoViewerFrame::OnCbnSelchangeComboFactor() 
{
#if defined(SCAD11) || defined(SCAD21)
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_p3DView->GetDocument()->m_pViewGeometry);
	if (pGeom)
	{
		CWaitCursor crWait;
		pGeom->m_Params.nTypeFactor = static_cast<CComboBox *>(m_wndResParams.GetDlgItem(IDC_COMBO_FACTOR))->GetCurSel();
		pGeom->SetDefMapInfo(const_cast<DefMapInfo *>(pGeom->m_Params.pDMI), &pGeom->m_Params);
		m_ScaleWnd.SetDmi(pGeom->m_Params.pDMI);
		pGeom->OnParamsChanged();
		m_p3DView->RedoCut();
		m_p3DView->Invalidate();
	}
#endif
}

void CIsoViewerFrame::OnCbnSelchangeComboLoad() 
{
#if defined(SCAD11) || defined(SCAD21)
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_p3DView->GetDocument()->m_pViewGeometry);
	if (pGeom)
	{
		CWaitCursor crWait;
		pGeom->m_Params.NPr = static_cast<CComboBox *>(m_wndResParams.GetDlgItem(IDC_COMBO_LOAD))->GetCurSel();
		CString str;
		m_wndResParams.GetDlgItem(IDC_COMBO_LOAD)->GetWindowText(str);
		_tcscpy_s(pGeom->m_Params.strCurLoad, str);
		pGeom->SetDefMapInfo(const_cast<DefMapInfo *>(pGeom->m_Params.pDMI), &pGeom->m_Params); 
		m_ScaleWnd.SetDmi(pGeom->m_Params.pDMI);
		pGeom->OnParamsChanged();
		m_p3DView->RedoCut();
		m_p3DView->Invalidate();
	}
#endif
}
// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnCheckValues() 
{
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_p3DView->GetDocument()->m_pViewGeometry);
	if (pGeom)
	{
		CWaitCursor crWait;
		pGeom->m_Params.pTypeInfo->NumFactor = !pGeom->m_Params.pTypeInfo->NumFactor;
		pGeom->OnParamsChanged();
		m_p3DView->RedoCut();
		m_p3DView->Invalidate();
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnCheckEggs() 
{
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_p3DView->GetDocument()->m_pViewGeometry);
	if (pGeom)
	{
		CWaitCursor crWait;
		pGeom->m_Params.bDrawEggs = !pGeom->m_Params.bDrawEggs;
		pGeom->OnParamsChanged();
		m_p3DView->RedoCut();
		m_p3DView->Invalidate();
	}
	
}

void CIsoViewerFrame::SetCheck(UINT nId, bool bValue) const
{
	CButton* pWnd = static_cast<CButton*>(m_wndDefScaleDialogBar.GetDlgItem(nId));
	if (pWnd)
		pWnd->SetCheck(bValue);
}

//DEL void CIsoViewerFrame::UpdateButtons()
//DEL {
//DEL 	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
//DEL 	if (!pDoc)
//DEL 		return;
//DEL 	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(pDoc->m_pViewGeometry);
//DEL 	if (pGeom)
//DEL 	{
//DEL 		SOglIsoParam &params = pGeom->m_Params;
//DEL 		SetCheck(IDC_CHECK_ISOLINES, params.bDrawIsoLines);
//DEL 		if (params.pTypeInfo)
//DEL 			SetCheck(IDC_CHECK_VALUES, params.pTypeInfo->NumFactor!=0);
//DEL 		SetCheck(IDC_CHECK_EGGS, params.bDrawEggs);
//DEL 
//DEL 	}
//DEL }

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateCheckIsolines(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (!pDoc || !pDoc->m_bViewResults)
		return;
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(pDoc->m_pViewGeometry);
	if (pGeom)
	{
		pCmdUI->Enable(TRUE);
		SOglIsoParam &params = pGeom->m_Params;
		pCmdUI->SetCheck(params.bDrawIsoLines);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnBtnIsolines() 
{
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_p3DView->GetDocument()->m_pViewGeometry);
	if (pGeom)
	{
		CWaitCursor crWait;
		pGeom->m_Params.bDrawIsoLines = !pGeom->m_Params.bDrawIsoLines;
		pGeom->OnParamsChanged();
		m_p3DView->RedoCut();
		m_p3DView->Invalidate();
	}
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateBtnValues(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (!pDoc || !pDoc->m_bViewResults)
		return;
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(pDoc->m_pViewGeometry);
	if (pGeom)
	{
		pCmdUI->Enable(TRUE);
		SOglIsoParam &params = pGeom->m_Params;
		if (params.pTypeInfo)
			pCmdUI->SetCheck(params.pTypeInfo->NumFactor!=0);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateCombo(CCmdUI* pCmdUI) 
{
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (!pDoc || !pDoc->m_bViewResults)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->Enable(TRUE);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateBtnEggs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (!pDoc || !pDoc->m_bViewResults)
		return;
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(pDoc->m_pViewGeometry);
	if (pGeom)
	{
		pCmdUI->Enable(TRUE);
		SOglIsoParam &params = pGeom->m_Params;
		pCmdUI->SetCheck(params.bDrawEggs);
	}
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateFactorGroup(CCmdUI* pCmdUI) 
{
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (pDoc  && pDoc->m_bViewResults)
		pCmdUI->Enable();	
}

void CIsoViewerFrame::OnFactorDisplacements() 
{
	CIsoViewGeometry *pGeom = Geom();
	pGeom->m_Params.SetTypeData(Iso_Disp);
	OnParamsChangedFactor();
}

void CIsoViewerFrame::OnFactorStressfields() 
{
	CIsoViewGeometry *pGeom = Geom();
	pGeom->m_Params.SetTypeData(Iso_Nap);
	OnParamsChangedFactor();
}



CIsoViewGeometry* CIsoViewerFrame::Geom() const
{
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (!pDoc || !pDoc->m_bViewResults)
		return nullptr;
	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(pDoc->m_pViewGeometry);
	return pGeom;
}

void CIsoViewerFrame::OnFactorStresscolourmap() 
{
	CIsoViewGeometry *pGeom = Geom();
	pGeom->m_Params.SetTypeData(Iso_Nap_Flat);	
	OnParamsChangedFactor();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateFactorDisplacements(CCmdUI* pCmdUI) 
{
	CIsoViewGeometry *pGeom = Geom();
	pCmdUI->Enable(pGeom != nullptr);
	pCmdUI->SetCheck(pGeom && pGeom->m_Params.nTypeData == Iso_Disp);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateFactorStressfields(CCmdUI* pCmdUI) 
{
	CIsoViewGeometry *pGeom = Geom();
	pCmdUI->Enable(pGeom!=nullptr);
	pCmdUI->SetCheck(pGeom && pGeom->m_Params.nTypeData == Iso_Nap);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateFactorStresscolourmap(CCmdUI* pCmdUI) 
{
	CIsoViewGeometry *pGeom = Geom();
	pCmdUI->Enable(pGeom != nullptr);
	pCmdUI->SetCheck(pGeom && pGeom->m_Params.nTypeData == Iso_Nap_Flat);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnParamsChanged()
{
	CIsoViewGeometry *pGeom = Geom();
	CScadViewerDoc* pDoc = (CScadViewerDoc*)GetActiveDocument();
	DefMapInfo *pDMI = const_cast<DefMapInfo *>(pDoc->m_IsoParams.pDMI);
	pDoc->m_IsoParams = pGeom->m_Params;
	pDoc->m_IsoParams.pDMI = pDMI;
	*pDMI = pGeom->m_DMI;
	//pGeom->SetDefMapInfo(pGeom->m_Params.pDMI, &pGeom->m_Params);
	pGeom->DrawOptionsChanged(&m_p3DView->m_DrawOptions, m_p3DView->m_ViewOptions.bShowUsedNodes);
	pGeom->LoadIso(m_p3DView->GetDocument()->m_bShowProfiles, m_p3DView->m_ViewOptions.bDrawOptimize);
	m_p3DView->RedoCut();
	UpdateDeformScale();
	pGeom->BuildArrays();
	m_p3DView->Invalidate();
}

void CIsoViewerFrame::OnViewNewResults()
{
	CIsoViewGeometry *pGeom = Geom();
	CComboBox *pCombo = static_cast<CComboBox*>(m_wndResParams.GetDlgItem(IDC_COMBO_LOAD));
	m_ScaleWnd.SetDmi(pGeom->m_Params.pDMI);
	pCombo->ResetContent();
#ifdef SCAD21
	for (UINT i=0;i<ApiGetQuantityLoad(pGeom->m_Params.hAPI); i++)
	{
		CString str = ApiGetLoadName(pGeom->m_Params.hAPI,i+1);
		CString str1;
		str1.Format(_T("L%d - \"%s\""), i+1, str);
		if (i==0)
			_tcscpy_s(pGeom->m_Params.strCurLoad,str1);

		pCombo->AddString(str1);
	}
#else
	RESULT *pRes = pGeom->m_Params.Res;
	for (int i=0;i<pRes->QuantityLoad; i++)
	{
		pCombo->AddString(CString(pRes->TableLoad[i].Name));
	}
#endif
	pCombo->SetCurSel(0);
	
	FillFactorCombo();
	UpdateDeformScale();
}

void CIsoViewerFrame::FillFactorCombo() const
{
	CIsoViewGeometry *pGeom = Geom();
	CComboBox *pCombo = static_cast<CComboBox *>(m_wndResParams.GetDlgItem(IDC_COMBO_FACTOR));
	pCombo->ResetContent();
	if (pGeom->m_Params.nTypeData == Iso_Disp) 
	{
		pCombo->AddString(_T("X"));
		pCombo->AddString(_T("Y"));
		pCombo->AddString(_T("Z"));
		pCombo->AddString(_T("UX"));
		pCombo->AddString(_T("UY"));
		pCombo->AddString(_T("UZ"));
		pCombo->AddString(_T("Суммарные"));
	}
	else
	{
		pCombo->AddString(_T("NX"));
		pCombo->AddString(_T("NY"));
		pCombo->AddString(_T("TXY"));
		pCombo->AddString(_T("MX"));
		pCombo->AddString(_T("MY"));
		pCombo->AddString(_T("MXY"));
		pCombo->AddString(_T("QX"));
		pCombo->AddString(_T("QY"));
		pCombo->AddString(_T("Sx верх"));
		pCombo->AddString(_T("Sx низ"));
		pCombo->AddString(_T("Sy верх"));
		pCombo->AddString(_T("Sy низ"));
	}

	pCombo->SetCurSel(pGeom->m_Params.nTypeFactor);

}
// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewerFrame::OnUpdateViewResults(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CIsoViewerFrame::OnParamsChangedFactor()
{
	CIsoViewGeometry *pGeom = Geom();
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (pDoc->m_pSchem == nullptr)
		pGeom->SetDefMapInfo(const_cast<struct DefMapInfo *>(pGeom->m_Params.pDMI), &pGeom->m_Params);
	m_ScaleWnd.SetDmi(pGeom->m_Params.pDMI);

	OnParamsChanged();
	FillFactorCombo();
}

void CIsoViewerFrame::SetToolBarNames()
{
	CScadViewerFrame::SetToolBarNames();
	CString strName;
	strName.LoadString(IDS_RESULTS_TOOLBAR);
	m_wndToolBar.SetWindowText(strName);
	strName.LoadString(IDS_DEFORM_TOOLBAR);
	m_wndDefScaleDialogBar.SetWindowText(strName);
	strName.LoadString(IDS_RESULT_TOOLBAR);
	m_wndResParams.SetWindowText(strName);
	strName.LoadString(IDS_SCALE_CAPTION);
	m_ScaleWnd.SetWindowText(strName);

}



void CIsoViewerFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar && pScrollBar->GetDlgCtrlID() == IDC_SLIDER_DEFORM_SCALE)
	{
		UpdateDeformScale();
	}
	CScadViewerFrame::OnVScroll(nSBCode, nPos, pScrollBar);
}
