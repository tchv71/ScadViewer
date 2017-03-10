// ScadViewerFrm.cpp : implementation of the CScadViewerFrame class
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
//#include "ScadViewer.h"

#include "ScadViewerFrm.h"
#include "ScadViewerView.h"
#include "ViewerOptions.h"
#include "..\Forum3DView\resource.h"
#include "OptionsMaterial.h"
#include "OptionsRtf.h"
//#include "mp4view.h"

#define CMp4View CScadViewerView

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScadViewerFrame

IMPLEMENT_DYNCREATE(CScadViewerFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CScadViewerFrame, CFrameWndEx)
	//{{AFX_MSG_MAP(CScadViewerFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_CAMERA_CHANGED, OnCameraChanged)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_INSTRUMENTS, OnUpdateContextInstruments)
	ON_COMMAND(ID_CONTEXT_INSTRUMENTS, OnContextInstruments)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_CUT, OnUpdateContextCut)
	ON_COMMAND(ID_CONTEXT_CUT, OnContextCut)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_CAMERA, OnUpdateContextCamera)
	ON_COMMAND(ID_CONTEXT_CAMERA, OnContextCamera)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_DEPTH, OnUpdateContextDepth)
	ON_COMMAND(ID_CONTEXT_DEPTH, OnContextDepth)
	ON_COMMAND(ID_CONTEXT_FILTERS, OnContextFilters)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_FILTERS, OnUpdateContextFilters)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESULTS, OnUpdateViewResults)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWndEx::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWndEx::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWndEx::OnHelpFinder)
	ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR,OnToolbarReset)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CScadViewerFrame construction/destruction

CScadViewerFrame::CScadViewerFrame() :
	m_pbClosed(nullptr),
	m_wndDepthDialogBar(IDC_SLIDER_DEPTH),
	m_p3DView(nullptr), m_pMp4View(nullptr), m_bFirstActivate(true)
{
	// enable bitmap menu support.
	//EnableBmpMenus();
}

CScadViewerFrame::~CScadViewerFrame()
{
}

//BEGIN_BUTTON_MAP(btnViewerFrameMap)
//	STD_BUTTON(ID_VIEW_ZOOM_IN,  TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ZOOM_OUT, TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ZOOM_ALL, TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_ZOOM_WIN, TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_PAN, TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_ROTATE, TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_WALK, TBBS_CHECKBOX)
//	SCTWOPART_BUTTON( ID_PROJECTION, ID_DROPARROW, 0, 0, IDR_POPUP_MENUS, 0, TPM_LEFTALIGN )
//	STD_BUTTON(ID_FILE_PRINT, TBBS_CHECKBOX)
//	STD_BUTTON(ID_FILE_PRINT_PREVIEW, TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_WIREFRAME ,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_SOLID,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_ELEMENTBORDERS, TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_MODE_TRANSPARENT, TBBS_CHECKBOX)
//	STD_BUTTON(ID_LIGHT,TBBS_CHECKBOX)
//	STD_BUTTON(ID_TOOLS_OPTIONS,TBBS_CHECKBOX)
//END_BUTTON_MAP()

//BEGIN_BUTTON_MAP(btnFiltersMap)
//	STD_BUTTON(ID_VIEW_ELEMENTS_NODES,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ELEMENTS_CONSTRAINTS,TBBS_CHECKBOX)
//	SCTWOPART_BUTTON( ID_VIEW_ELEMENTS_BARS, ID_DROPARROW, 0, 0, IDR_POPUP_MENUS, 2, TPM_LEFTALIGN )
//	SCTWOPART_BUTTON( ID_VIEW_ELEMENTS_PLATES, ID_DROPARROW, 0, 0, IDR_POPUP_MENUS, 3, TPM_LEFTALIGN )
//	STD_BUTTON(ID_VIEW_ELEMENTS_SOLIDS,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ELEMENTS_COLUMNS,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ELEMENTS_BEAMS,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ELEMENTS_WALLS,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ELEMENTS_SLABS,TBBS_CHECKBOX)
//	STD_BUTTON(ID_VIEW_ELEMENTS_ROOFS,TBBS_CHECKBOX)
//END_BUTTON_MAP()

IMPLEMENT_SERIAL(CDropdownButton, CMFCToolBarMenuButton, 1)

int CScadViewerFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	//AddBmpMenuToolBarResource(IDR_MAIN_TOOLBAR);
	//AddBmpMenuToolBarResource(IDR_FILTERS_TOOLBAR);
	//AddBmpMenuToolBarResource(IDR_CUT_TOOLBAR);

	//m_wndToolBar.SetButtonMap(btnViewerFrameMap);
	//m_wndFitersToolBar.SetButtonMap(btnFiltersMap);
	afxGlobalData.EnableRibbonImageScale(FALSE);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Не удалось создать строку меню\n");
		return -1;      // не удалось создать
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY| CBRS_GRIPPER);
	m_wndMenuBar.SetRecentlyUsedMenus(FALSE);

	// предотвращение фокусировки строки меню на активации 
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	DWORD dwStyle =  WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT,dwStyle, CRect(1,1,1,1), IDR_MAIN_TOOLBAR) ||
		!m_wndToolBar.LoadToolBar(IDR_MAIN_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	

	int i;
	i=m_wndToolBar.CommandToIndex(ID_VIEW_3DVIEWS_TOP);
	m_mapCmdToImgIndex[ID_VIEW_3DVIEWS_TOP] = m_wndToolBar.GetButton(i)->GetImage();
	for (; i<m_wndToolBar.GetCount(); )
		m_wndToolBar.RemoveButton(i/*,true*/);

	if (!m_wndFitersToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle, CRect(1,1,1,1), IDR_FILTERS_TOOLBAR) ||
		!m_wndFitersToolBar.LoadToolBar(IDR_FILTERS_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	i=m_wndFitersToolBar.CommandToIndex(ID_VIEW_SHOWBARPROFILE);
	m_mapCmdToImgIndex[ID_BAR_IMG] = m_wndFitersToolBar.GetButton(m_wndFitersToolBar.CommandToIndex(ID_BAR_IMG))->GetImage();
	m_mapCmdToImgIndex[ID_PLATE_IMG] = m_wndFitersToolBar.GetButton(m_wndFitersToolBar.CommandToIndex(ID_PLATE_IMG))->GetImage();
	for (; i<m_wndFitersToolBar.GetCount(); )
		m_wndFitersToolBar.RemoveButton(i/*,true*/);

	if (!m_wndCutToolBar.CreateEx(this,TBSTYLE_FLAT, dwStyle, CRect(1,1,1,1), IDR_CUT_TOOLBAR) ||
		!m_wndCutToolBar.LoadToolBar(IDR_CUT_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) /* ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT))*/)
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneStyle(1, SBPS_NORMAL);

	CDockingManager::SetDockingMode(DT_SMART);
	//CRect rc;
	if (!m_wndDepthDialogBar.Create(IDD_DEPTH, this,  WS_CHILD | WS_VISIBLE | CBRS_RIGHT |CBRS_TOOLTIPS | CBRS_GRIPPER/*| CBRS_FLYBY*/ /*| CBRS_SIZE_FIXED*/, IDD_DEPTH))
		///*CBRS_EX_STDCONTEXTMENU |*/CBRS_EXIDD_DEPTH_COOLBORDERS|CBRS_EX_GRIPPER/* CBRS_EX_FLATSTYLE |CBRS_EX_COOL | CBRS_EX_BORDERSPACE*/))
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      // fail to create
	}
	if (!m_wndCameraDialogBar.Create(IDD_CAMERA, this, WS_CHILD | WS_VISIBLE | CBRS_TOP |CBRS_TOOLTIPS | CBRS_SIZE_FIXED|CBRS_GRIPPER,IDD_CAMERA))
		///*CBRS_EX_STDCONTEXTMENU |*/CBRS_EX_COOLBORDERS|CBRS_EX_GRIPPER | CBRS_EX_UNIDIRECTIONAL, IDD_CAMERA/* CBRS_EX_FLATSTYLE |CBRS_EX_COOL | CBRS_EX_BORDERSPACE*/))
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      // fail to create
	}
	m_wndCameraDialogBar.EnableGripper(TRUE);
	m_wndCameraDialogBar.EnableToolTips();
	//m_wndCameraDialogBar.SetBorders(20,10,10,10);
	//m_wndCutToolBar.SetSizes(CSize(16+7,16+6),CSize(16,16));
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFitersToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCutToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDepthDialogBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	m_wndCameraDialogBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);


	//m_wndDepthDialogBar.SetExBarStyle(m_wndDepthDialogBar.GetExBarStyle() | CBRS_EX_UNIDIRECTIONAL);
	//m_wndCameraDialogBar.SetExBarStyle(m_wndCameraDialogBar.GetExBarStyle() | CBRS_EX_UNIDIRECTIONAL);

	//m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC);
	//m_wndFitersToolBar.SetBarStyle(m_wndFitersToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC);
	//m_wndCutToolBar.SetBarStyle(m_wndCutToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	//SetToolBarNames();
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar, AFX_IDW_DOCKBAR_TOP);
	CRect r;
	DockPane(&m_wndCutToolBar, AFX_IDW_DOCKBAR_RIGHT, &r);

	RecalcLayout();

	DockPaneBottomOf(&m_wndDepthDialogBar, &m_wndCutToolBar);

	//DockPane(&m_wndFitersToolBar, AFX_IDW_DOCKBAR_TOP,&rect);
	DockPaneRightOf(&m_wndFitersToolBar, &m_wndToolBar);
	DockPaneRightOf(&m_wndCameraDialogBar, &m_wndFitersToolBar);
	EnablePaneMenu(TRUE, 0, "",0, TRUE, TRUE);

	SetActiveView( m_p3DView );
	CSliderCtrl *pWnd = static_cast<CSliderCtrl *>(m_wndDepthDialogBar.GetDlgItem(IDC_SLIDER_DEPTH));
	pWnd->SetRange(0, 100);
	pWnd->SetPos(100);
	pWnd->SetTicFreq(10);
	return 0;
}

void CScadViewerFrame::DockPaneRightOf(CPane* pBar, CPane* pRightOf)
{
	CRect rect;
	pRightOf->GetWindowRect(&rect);
	GetDockingManager()->FindDockSiteByPane(pRightOf)->ScreenToClient(&rect);
	rect.OffsetRect(rect.Size().cx,0);
	//CRect rectBar;
	//pRightOf->GetWindowRect(&rectBar);
	//rect.right = rect.left + rectBar.Width();
	pBar->m_recentDockInfo.m_recentSliderInfo.m_rectDockedRect = rect;
	GetDockingManager()->FindDockSiteByPane(pRightOf)->AdjustDockingLayout();
	GetDockingManager()->FindDockSiteByPane(pRightOf)->AdjustLayout();
	DockPane(pBar, AFX_IDW_DOCKBAR_TOP, &rect);
}

void CScadViewerFrame::DockPaneBottomOf(CPane* pBar, CPane* pBottomOf)
{
	CRect rect;
	pBottomOf->GetWindowRect(&rect);
	GetDockingManager()->FindDockSiteByPane(pBottomOf)->ScreenToClient(&rect);
	rect.OffsetRect(0,rect.Size().cy);
	//CRect rectBar;
	//pBottomOf->GetWindowRect(&rectBar);
	//rect.bottom = rect.top + rectBar.Height();
	pBar->m_recentDockInfo.m_recentSliderInfo.m_rectDockedRect = rect;
	DockPane(pBar, AFX_IDW_DOCKBAR_RIGHT, &rect);
}

BOOL CScadViewerFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScadViewerFrame diagnostics

#ifdef _DEBUG
void CScadViewerFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CScadViewerFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScadViewerFrame message handlers

BOOL CScadViewerFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_p3DView = static_cast<CScadViewerView*>(RUNTIME_CLASS( CMp4View )->CreateObject());	
	m_p3DView->UpdateSettings(true, _T("ModelView"));
	m_p3DView->Create( nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0,0,0,0), this, AFX_IDW_PANE_FIRST, pContext );
	
	//return CFrameWndEx::OnCreateClient(lpcs, pContext);
	return TRUE;
}



void CScadViewerFrame::OnClose() 
{
	EndModalLoop(0);
	if (m_pbClosed)
		*m_pbClosed = true;
	
	CFrameWndEx::OnClose();
}



void CScadViewerFrame::SetProjectionButton(UINT nViewNo)
{
	SetButtonImage(IDR_MAIN_TOOLBAR, ID_PROJECTION, ID_VIEW_3DVIEWS_TOP, nViewNo);
}

void CScadViewerFrame::SetButtonImage(UINT nIDToolBar, UINT nIdCommand, UINT nFirstImageCmd, UINT nImageIndex)
{
	//::BmpItem* pItem;
	CMFCToolBar  *pToolBar = nullptr;
	switch (nIDToolBar)
	{
	case IDR_MAIN_TOOLBAR:
		pToolBar = &m_wndToolBar;
		break;
	case IDR_FILTERS_TOOLBAR:
		pToolBar = &m_wndFitersToolBar;
		break;
	}
	ASSERT(pToolBar);

	//pToolBar->GetBmpMgr()->m_mapItem.Lookup(nFirstImageCmd, pItem);	
	//UINT nOffset = pItem->m_nBmpOffset;

	//pToolBar->GetBmpMgr()->m_mapItem.Lookup(nIdCommand, pItem);
	//
	//pItem->m_nBmpOffset  = nOffset+nImageIndex;
	//pToolBar->GetBmpMgr()->m_mapItem.SetAt(nIdCommand, pItem);

	//SECStdBtn *pBtn = pToolBar->GetBtnObject(pToolBar->CommandToIndex(nIdCommand));
	//pBtn->Invalidate();
	pToolBar->SetButtonInfo(pToolBar->CommandToIndex(nIdCommand), nIdCommand, TBBS_BUTTON, m_mapCmdToImgIndex[nFirstImageCmd]+nImageIndex);
}

BOOL CScadViewerFrame::UpdateSettings(bool bLoad)
{
	m_p3DView->UpdateSettings(bLoad, _T("ModelView"));
	return TRUE;
}

void CScadViewerFrame::OnDestroy() 
{
	UpdateSettings(false);
	CFrameWndEx::OnDestroy();
}



void CScadViewerFrame::ActivateFrame(int nCmdShow) 
{
	if (m_bFirstActivate)
	{
		UpdateSettings(true);
		m_bFirstActivate = false;
        //LoadBarState(_T("Toolbars\\"));
        // sets window's position and minimized/maximized status
		if (m_Menu.GetSafeHmenu())
			m_Menu.DestroyMenu();
		m_Menu.LoadMenu(IDR_MAINFRAME);
		m_wndMenuBar.CreateFromMenu(m_Menu.GetSafeHmenu());
		m_hMenuDefault = m_Menu.GetSafeHmenu();  //

	}
	
	CFrameWndEx::ActivateFrame(nCmdShow);
}

void CScadViewerFrame::OnToolsOptions() 
{
	CString strCaption;
	strCaption.LoadString(IDS_OPTIONS_DLG_NAME);
	CViewerOptions OptionsDlg(strCaption);
	extern int nLangID;
	CPersistViewOptions theOpt(m_p3DView->m_ViewOptions);
	COptionsMaterial	PageMaterial(theOpt, true);
	COptionsRtf			PageRtf(m_p3DView->m_DrawOptions);
	// ReSharper disable once CppLocalVariableMightNotBeInitialized
	PageMaterial.m_nLangID = nLangID;

	OptionsDlg.AddPage(&PageMaterial);
	OptionsDlg.AddPage(&PageRtf);
	if (OptionsDlg.DoModal()!=IDOK)
		return;
	// ReSharper disable once CppLocalVariableMightNotBeInitialized
	if (nLangID!=PageMaterial.m_nLangID)
	{
		LoadLanguage(PageMaterial.m_nLangID);
		SetToolBarNames();
	}
	m_p3DView->OnOptionsChanged(PageMaterial.m_ViewOptions);
	
}

void CScadViewerFrame::SetToolBarNames()
{
	CString strCaption;
	strCaption.LoadString(IDS_MAIN_TOOLBAR_CAPTION);
	SetControlBarName(m_wndToolBar, strCaption);
	strCaption.LoadString(IDS_CUT_TOOLBAR_CAPTION);
	SetControlBarName(m_wndCutToolBar,strCaption);
	strCaption.LoadString(IDS_FILTERS_TOOLBAR_CAPTION);
	SetControlBarName(m_wndFitersToolBar,strCaption);
	strCaption.LoadString(IDS_CAMERA_TOOLBAR_CAPTION);
	m_wndCameraDialogBar.SetWindowText(strCaption);
	strCaption.LoadString(IDS_DEPTH_TOOLBAR);
	m_wndDepthDialogBar.SetWindowText(strCaption);
	strCaption.LoadString(IDS_CAMERA_TOOLBAR_MM);
	m_wndCameraDialogBar.GetDlgItem(IDC_STATIC_MM)->SetWindowText(strCaption);
}

//DEL void CScadViewerFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
//DEL {
//DEL 	CSliderCtrl *pSlider = reinterpret_cast<CSliderCtrl*>( pScrollBar );
//DEL 	if (pSlider && pSlider->GetDlgCtrlID() == IDC_SLIDER_DEPTH)
//DEL 	{
//DEL 		m_p3DView->OnDepthChange(pSlider->GetPos()/100.0f);
//DEL 	}
//DEL 	CFrameWndEx::OnVScroll(nSBCode, nPos, pScrollBar);
//DEL }





BOOL CScadViewerFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if (wParam == IDC_SLIDER_DEPTH)
	{
		LPNMHDR pNmhdr = LPNMHDR(lParam);
		if (int(pNmhdr->code) == NM_CUSTOMDRAW)
		{
			CSliderCtrl *pSlider = reinterpret_cast<CSliderCtrl*>(m_wndDepthDialogBar.GetDlgItem(IDC_SLIDER_DEPTH));
			if (pSlider && pSlider->GetDlgCtrlID() == IDC_SLIDER_DEPTH)
			{
				m_p3DView->OnDepthChange(pSlider->GetPos()/100.0f);
			}

		}
	}
	
	return CFrameWndEx::OnNotify(wParam, lParam, pResult);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnCameraChanged() 
{
	m_p3DView->SetCamera(m_wndCameraDialogBar.m_nFocusLength, m_wndCameraDialogBar.m_bChangeDistance);
}

void CScadViewerFrame::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu Popup;
	Popup.LoadMenu(IDR_POPUP_MENUS);
	CMenu* pPopup = Popup.GetSubMenu(4);
	ASSERT(pPopup);

	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,	point.x, point.y, this, nullptr/*&rc*/);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnUpdateContextInstruments(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndToolBar.GetStyle() & WS_VISIBLE ? 1 : 0 );
	
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnContextInstruments() 
{
	//ShowControlBar( &m_wndToolBar, ( m_wndToolBar.GetStyle() & WS_VISIBLE ) == 0 , FALSE );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnUpdateContextCut(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndCutToolBar.GetStyle() & WS_VISIBLE ? 1 : 0 );
	
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnContextCut() 
{
	//ShowControlBar( &m_wndCutToolBar, ( m_wndCutToolBar.GetStyle() & WS_VISIBLE ) == 0 , FALSE );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnUpdateContextCamera(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndCameraDialogBar.GetStyle() & WS_VISIBLE ? 1 : 0 );
}

void CScadViewerFrame::OnContextCamera() 
{
	m_wndCameraDialogBar.ShowWindow(( m_wndCameraDialogBar.GetStyle() & WS_VISIBLE ) == 0 ? SW_SHOW : SW_HIDE);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnUpdateContextDepth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndDepthDialogBar.GetStyle() & WS_VISIBLE ? 1 : 0 );
	
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnContextDepth() 
{
	//ShowControlBar( &m_wndDepthDialogBar, ( m_wndDepthDialogBar.GetStyle() & WS_VISIBLE ) == 0 , FALSE );
}



// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnContextFilters() 
{
	//ShowControlBar( &m_wndFitersToolBar, ( m_wndFitersToolBar.GetStyle() & WS_VISIBLE ) == 0 , FALSE );

}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnUpdateContextFilters(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndFitersToolBar.GetStyle() & WS_VISIBLE ? 1 : 0 );
	
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerFrame::OnUpdateViewResults(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);

}

void CScadViewerFrame::SetControlBarName(CPane &bar, CString str)
{
	bar.SetWindowText(str);
	//if (bar.IsFloating())
	//{
	//	bar.m_pDockBar->SetWindowText(str);
	//	bar.m_pDockBar->GetParent()->SetWindowText(str);
	//}
}

LRESULT CScadViewerFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	UINT uiToolBarId = UINT(wp);

	CMenu mnuPopup;
	mnuPopup.LoadMenu(IDR_POPUP_MENUS);
	switch (uiToolBarId)
	{
	case IDR_MAIN_TOOLBAR:
		{
			CMenu *mnuPopupMenu = mnuPopup.GetSubMenu(0);
			ASSERT(mnuPopupMenu);
			CDropdownButton bn(ID_PROJECTION,mnuPopupMenu->m_hMenu, nullptr);
			m_wndToolBar.ReplaceButton(ID_PROJECTION,bn);
		}
		break;
	case IDR_FILTERS_TOOLBAR:
		{
			CMenu *mnuPopupMenu = mnuPopup.GetSubMenu(2);
			ASSERT(mnuPopupMenu);
			CDropdownButton bn(ID_VIEW_ELEMENTS_BARS,mnuPopupMenu->m_hMenu, nullptr);
			m_wndFitersToolBar.ReplaceButton(ID_VIEW_ELEMENTS_BARS,bn);
			mnuPopupMenu = mnuPopup.GetSubMenu(3);
			ASSERT(mnuPopupMenu);
			CDropdownButton bn1(ID_VIEW_ELEMENTS_PLATES,mnuPopupMenu->m_hMenu, nullptr);
			m_wndFitersToolBar.ReplaceButton(ID_VIEW_ELEMENTS_PLATES,bn1);
		}
		break;
	}

	return 0;
}