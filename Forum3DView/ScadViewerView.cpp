// ScadViewerView.cpp : implementation of the CScadViewerView class
//
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "resource.h"
//#include "ScadViewer.h"

#include "ScadViewerDoc.h"
#include "ScadViewerFrm.h"
#include "ScadViewerView.h"
#include "BmpSaveDlg.h"
#include <shlwapi.h>
#ifndef SCAD11
#ifdef SCAD21
#include "SCADAPIX.hxx"
#else
#include "schema.h"
#endif
#else
#include "schema.hpp"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DibGlRenderer.h"

/////////////////////////////////////////////////////////////////////////////
// CScadViewerView

IMPLEMENT_DYNCREATE(CScadViewerView, C3DBoxView)

BEGIN_MESSAGE_MAP(CScadViewerView, C3DBoxView)
	//{{AFX_MSG_MAP(CScadViewerView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_IN, OnUpdateViewZoom)
	ON_COMMAND(ID_VIEW_ZOOM_IN, OnViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOM_OUT, OnViewZoomOut)
	ON_COMMAND(ID_VIEW_ZOOM_ALL, OnViewZoomAll)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_ZOOM_WIN, OnUpdateViewModeZoomWin)
	ON_COMMAND(ID_VIEW_MODE_ZOOM_WIN, OnViewModeZoomWin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_PAN, OnUpdateViewModePan)
	ON_COMMAND(ID_VIEW_MODE_PAN, OnViewModePan)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_ROTATE, OnUpdateViewModeRotate)
	ON_COMMAND(ID_VIEW_MODE_ROTATE, OnViewModeRotate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_LOOK_AROUND, OnUpdateViewModeLookAround)
	ON_COMMAND(ID_VIEW_MODE_LOOK_AROUND, OnViewModeLookAround)
	ON_COMMAND(ID_VIEW_MODE_WALK, OnViewModeWalk)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_WALK, OnUpdateViewModeWalk)
	ON_COMMAND(ID_VIEW_PERSPECTIVE, OnViewPerspective)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PERSPECTIVE, OnUpdateViewPerspective)
	ON_COMMAND(ID_VIEW_MODE_WIREFRAME, OnViewModeWireframe)
	ON_COMMAND(ID_VIEW_MODE_SOLID, OnViewModeSolid)
	ON_COMMAND(ID_VIEW_MODE_ELEMENTBORDERS, OnViewModeElementborders)
	ON_COMMAND(ID_VIEW_MODE_TRANSPARENT, OnViewModeTransparent)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_WIREFRAME, OnUpdateViewModeWireframe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_SOLID, OnUpdateViewModeSolid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_ELEMENTBORDERS, OnUpdateViewModeElementborders)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_TRANSPARENT, OnUpdateViewModeTransparent)
	ON_COMMAND(ID_VIEW_ELEMENTS_COLUMNS, OnViewElementsColumns)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_COLUMNS, OnUpdateViewElementsColumns)
	ON_COMMAND(ID_VIEW_ELEMENTS_CONSTRAINTS, OnViewElementsConstraints)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_CONSTRAINTS, OnUpdateViewElementsConstraints)
	ON_COMMAND(ID_VIEW_ELEMENTS_NODES, OnViewElementsNodes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_NODES, OnUpdateViewElementsNodes)
	ON_COMMAND(ID_VIEW_ELEMENTS_PLATES, OnViewElementsPlates)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_PLATES, OnUpdateViewElementsPlates)
	ON_COMMAND(ID_VIEW_ELEMENTS_ROOFS, OnViewElementsRoofs)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_ROOFS, OnUpdateViewElementsRoofs)
	ON_COMMAND(ID_VIEW_ELEMENTS_SLABS, OnViewElementsSlabs)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_SLABS, OnUpdateViewElementsSlabs)
	ON_COMMAND(ID_VIEW_ELEMENTS_SOLIDS, OnViewElementsSolids)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_SOLIDS, OnUpdateViewElementsSolids)
	ON_COMMAND(ID_VIEW_ELEMENTS_WALLS, OnViewElementsWalls)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_WALLS, OnUpdateViewElementsWalls)
	ON_COMMAND(ID_VIEW_ELEMENTS_BARS, OnViewElementsBars)
	ON_COMMAND(ID_VIEW_ELEMENTS_BEAMS, OnViewElementsBeams)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_BARS, OnUpdateViewElementsBars)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_BEAMS, OnUpdateViewElementsBeams)
	ON_COMMAND(ID_PROJECTION, OnProjection)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PLATES_HORIZONTAL, OnPlatesHorizontal)
	ON_UPDATE_COMMAND_UI(ID_PLATES_HORIZONTAL, OnUpdatePlatesHorizontal)
	ON_COMMAND(ID_PLATES_VERTICAL, OnPlatesVertical)
	ON_UPDATE_COMMAND_UI(ID_PLATES_VERTICAL, OnUpdatePlatesVertical)
	ON_COMMAND(ID_PLATES_SLANTED, OnPlatesSlanted)
	ON_UPDATE_COMMAND_UI(ID_PLATES_SLANTED, OnUpdatePlatesSlanted)
	ON_COMMAND(ID_BARS_HORIZONTAL, OnBarsHorizontal)
	ON_UPDATE_COMMAND_UI(ID_BARS_HORIZONTAL, OnUpdateBarsHorizontal)
	ON_COMMAND(ID_BARS_VERTICAL, OnBarsVertical)
	ON_UPDATE_COMMAND_UI(ID_BARS_VERTICAL, OnUpdateBarsVertical)
	ON_COMMAND(ID_BARS_SLANTED, OnBarsSlanted)
	ON_UPDATE_COMMAND_UI(ID_BARS_SLANTED, OnUpdateBarsSlanted)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_EDIT, OnFileEdit)
	ON_UPDATE_COMMAND_UI(ID_FILE_EDIT, OnUpdateFileEdit)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(1025, OnUpdatePane)
	ON_UPDATE_COMMAND_UI(1024, OnUpdatePane2)

	ON_UPDATE_COMMAND_UI(IDC_SLIDER_FLENGTH, OnUpdateSliderFlength)
	ON_COMMAND(ID_EXPORT_TO_DXF, OnExportToDxf)
	ON_COMMAND(ID_EXPORT_TO_BMP, OnExportToBmp)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_TO_DXF, OnUpdateExportToBmp)
	ON_COMMAND(ID_VIEW_MODE_SELECT, OnViewModeSelect)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MODE_SELECT, OnUpdateViewModeSelect)
	ON_COMMAND(ID_SELECT_HIDE_ELEMENT, OnSelectHideElement)
	ON_UPDATE_COMMAND_UI(ID_HIDE_ELEMENT_PLATE, OnUpdateHideElementPlate)
	ON_COMMAND(ID_HIDE_ELEMENT_PLATE, OnHideElementPlate)
	ON_COMMAND(ID_SELECT_SHOW_ELEMENT_PLATE, OnShowElementPlate)
	ON_COMMAND(ID_VIEW_ELEMENTS_AXES, OnViewElementsAxes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS_AXES, OnUpdateViewElementsAxes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_OUT, OnUpdateViewZoom)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_ALL, OnUpdateViewZoom)
	ON_UPDATE_COMMAND_UI(IDC_CHECK_CHANGE_DIST, OnUpdateSliderFlength)
	ON_UPDATE_COMMAND_UI(IDC_STATIC_FLENGTH, OnUpdateSliderFlength)
	ON_UPDATE_COMMAND_UI(IDC_STATIC_MM, OnUpdateSliderFlength)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_TO_BMP, OnUpdateExportToBmp)
	ON_UPDATE_COMMAND_UI(ID_SELECT_SHOW_ELEMENT_PLATE, OnUpdateHideElementPlate)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_VIEW_3DVIEWS_TOP,  ID_VIEW_3DVIEWS_DIMETRY, OnView3dviews)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_3DVIEWS_TOP,  ID_VIEW_3DVIEWS_DIMETRY, OnUpdateView3dviews)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, C3DBoxView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, C3DBoxView::OnFilePrint)
	ON_COMMAND(ID_VIEW_SHOWBARPROFILE, OnViewShowbarprofile)
	ON_COMMAND(ID_VIEW_SHOWPLATETHICKNESS, OnViewShowplatethickness)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWBARPROFILE, OnUpdateViewShowbarprofile)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWPLATETHICKNESS, OnUpdateViewShowplatethickness)
	ON_COMMAND(ID_CUT, OnCut)
	ON_UPDATE_COMMAND_UI(ID_CUT, OnUpdateCut)
	ON_UPDATE_COMMAND_UI(ID_NO_CUT, OnUpdateNoCut)
	ON_UPDATE_COMMAND_UI(ID_INV_CUT, OnUpdateInvCut)
	ON_COMMAND(ID_INV_CUT, OnInvCut)
	ON_COMMAND(ID_NO_CUT, OnNoCut)
	ON_COMMAND(ID_CUT_UNDO, OnCutUndo)
	ON_UPDATE_COMMAND_UI(ID_CUT_UNDO, OnUpdateCutUndo)
	ON_COMMAND(ID_LIGHT, OnLight)
	ON_UPDATE_COMMAND_UI(ID_LIGHT, OnUpdateLight)

	ON_WM_ERASEBKGND()
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScadViewerView construction/destruction

CScadViewerView::CScadViewerView() :
	m_nLastViewNo(0), m_pOldMainWnd(nullptr)
{
//	m_pDocument = (CScadViewerDoc*)RUNTIME_CLASS( CScadViewerDoc )->CreateObject();;
}

CScadViewerView::~CScadViewerView()
{
//	if (m_pDocument)
//	{
//		delete m_pDocument;
//		m_pDocument = nullptr;
//	}
}


/////////////////////////////////////////////////////////////////////////////
// CScadViewerView drawing

void CScadViewerView::OnDraw(CDC* pDC)
{
	C3DBoxView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CScadViewerView diagnostics

#ifdef _DEBUG
void CScadViewerView::AssertValid() const
{
	C3DBoxView::AssertValid();
}

void CScadViewerView::Dump(CDumpContext& dc) const
{
	C3DBoxView::Dump(dc);
}

CScadViewerDoc* CScadViewerView::GetDocument() const
// non-debug version is inline
{
	//ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScadViewerDoc)));
	return static_cast<CScadViewerDoc*>(m_pDocument);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScadViewerView message handlers

void CScadViewerView::OnUpdate(CView * pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	C3DBoxView::OnUpdate(pSender, lHint, pHint);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewZoom(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();	
}


void CScadViewerView::OnViewZoomIn() 
{
	Zoom(1.5f);	
}

void CScadViewerView::OnViewZoomOut() 
{
	Zoom(1/1.5f);
	
}

void CScadViewerView::OnViewZoomAll() 
{
	ZoomAll();	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeZoomWin(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(State == ST_ZOOM ? 1 : 0);	
}

void CScadViewerView::OnViewModeZoomWin() 
{
	State = ST_ZOOM;	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModePan(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(State == ST_PAN ? 1 : 0);	
}

void CScadViewerView::OnViewModePan() 
{
	State = ST_PAN;	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(State == ST_ROTATE ? 1 : 0);	
}

void CScadViewerView::OnViewModeRotate() 
{
	State = ST_ROTATE;	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeLookAround(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ViewPos.bPerspective);
	pCmdUI->SetCheck(State == ST_LOOK_AROUND ? 1 : 0);	
}

void CScadViewerView::OnViewModeLookAround() 
{
	State = ST_LOOK_AROUND;	
}

void CScadViewerView::OnViewModeWalk() 
{
	State = ST_WALK;	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeWalk(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ViewPos.bPerspective);
	pCmdUI->SetCheck(State == ST_WALK ? 1 : 0);	
}

void CScadViewerView::OnViewPerspective() 
{
	m_ViewPos.bPerspective = !m_ViewPos.bPerspective;
	if (!m_ViewPos.bPerspective)
	{
		if (State == ST_LOOK_AROUND)
			State = ST_ROTATE;
		if (State == ST_WALK)
			State = ST_PAN;
	}
	Invalidate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewPerspective(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_ViewPos.bPerspective? 1 : 0);	
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeWireframe(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_DrawOptions.Mode == M_LINES ? 1 : 0);	
}

void CScadViewerView::OnViewModeWireframe() 
{
	m_DrawOptions.Mode = M_LINES;
	Invalidate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeSolid(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_DrawOptions.Mode == M_FILL ? 1 : 0);	
}

void CScadViewerView::OnViewModeSolid() 
{
	m_DrawOptions.Mode = M_FILL;
	Invalidate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeElementborders(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_DrawOptions.Mode == M_FILL_AND_LINES ? 1 : 0);	
	
}

void CScadViewerView::OnViewModeElementborders() 
{
	m_DrawOptions.Mode = M_FILL_AND_LINES;
	Invalidate();
}

#define INVERT(x) x = !x

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeTransparent(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_DrawOptions.Mode == M_FILL_AND_LINES_TRANSP ? 1 : 0);	
}

void CScadViewerView::OnViewModeTransparent() 
{
	m_DrawOptions.Mode = M_FILL_AND_LINES_TRANSP;
	Invalidate();
}

void CScadViewerView::OnViewShowbarprofile()
{
	GetDocument()->m_bShowProfiles = !GetDocument()->m_bShowProfiles;
	ReloadDoc();
	UpdateToolbar();
}

void CScadViewerView::OnViewShowplatethickness()
{
	GetDocument()->m_bShowPlateThickness = !GetDocument()->m_bShowPlateThickness;
	ReloadDoc();
	UpdateToolbar();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewShowbarprofile(CCmdUI *pCmdUI)
{
/*
	if (GetDocument()->m_bViewResults)
	{
		pCmdUI->SetCheck(0);
		pCmdUI->Enable(FALSE);
		return;
	}
*/
	pCmdUI->Enable();
	pCmdUI->SetCheck(GetDocument()->m_bShowProfiles);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewShowplatethickness(CCmdUI *pCmdUI)
{
	if (GetDocument()->m_bViewResults)
	{
		pCmdUI->SetCheck(0);
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->Enable();
	pCmdUI->SetCheck(GetDocument()->m_bShowPlateThickness);
}

/***************** Elements drawing by type *************************/

void CScadViewerView::OnViewElementsNodes() 
{
	INVERT(m_DrawOptions.bNodes);
	Invalidate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsNodes(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_DrawOptions.bNodes);
}

void CScadViewerView::OnViewElementsConstraints() 
{
	INVERT(m_DrawOptions.bBounds);
	Invalidate();
}


// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsConstraints(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bBounds);
}

void CScadViewerView::OnViewElementsAxes() 
{
	INVERT(m_DrawOptions.bAxes);
	Invalidate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsAxes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bAxes);
}

void CScadViewerView::OnViewElementsBars() 
{
	INVERT(m_DrawOptions.bBars);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsBars(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bBars);	
}

void CScadViewerView::OnViewElementsPlates() 
{
	INVERT(m_DrawOptions.bElements);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsPlates(CCmdUI* pCmdUI) 
{

	pCmdUI->SetCheck(m_DrawOptions.bElements);
}

void CScadViewerView::OnViewElementsSolids() 
{
	INVERT(m_DrawOptions.bSolids);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsSolids(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bSolids);
}

void CScadViewerView::OnViewElementsColumns() 
{
	INVERT(m_DrawOptions.bColumns);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsColumns(CCmdUI* pCmdUI) 
{
	if (m_DrawOptions.bBars == false || !IsForumGeometry())
	{
		pCmdUI->Enable(false);
		return;
	}
	pCmdUI->SetCheck(m_DrawOptions.bColumns);
}



void CScadViewerView::OnViewElementsRoofs() 
{
	INVERT(m_DrawOptions.bRoofs);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsRoofs(CCmdUI* pCmdUI) 
{
	if (m_DrawOptions.bElements == false || !IsForumGeometry())
	{
		pCmdUI->Enable(false);
		return;
	}
	pCmdUI->SetCheck(m_DrawOptions.bRoofs);
}

void CScadViewerView::OnViewElementsSlabs() 
{
	INVERT(m_DrawOptions.bSlabs);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsSlabs(CCmdUI* pCmdUI) 
{
	if (m_DrawOptions.bElements == false || !IsForumGeometry())
	{
		pCmdUI->Enable(false);
		return;
	}
	pCmdUI->SetCheck(m_DrawOptions.bSlabs);
}


void CScadViewerView::OnViewElementsWalls() 
{
	INVERT(m_DrawOptions.bWalls);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsWalls(CCmdUI* pCmdUI) 
{
	if (m_DrawOptions.bElements == false  || !IsForumGeometry() )
	{
		pCmdUI->Enable(false);
		return;
	}
	pCmdUI->SetCheck(m_DrawOptions.bWalls);
}


void CScadViewerView::OnViewElementsBeams() 
{
	INVERT(m_DrawOptions.bBeams);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewElementsBeams(CCmdUI* pCmdUI) 
{
	if (m_DrawOptions.bBars == false || !IsForumGeometry())
	{
		pCmdUI->Enable(false);
		return;
	}
	pCmdUI->SetCheck(m_DrawOptions.bBeams);
}

void CScadViewerView::DrawOptionsChanged()
{
	CWaitCursor cur;
	if (GetDocument() && GetDocument()->m_pViewGeometry)
		GetDocument()->m_pViewGeometry->DrawOptionsChanged(&m_DrawOptions, m_ViewOptions.bShowUsedNodes);
	m_DrawOptions.arrLogFonts[SVF_AXES].lfCharSet = RUSSIAN_CHARSET;
	m_pRenderer->BuildFont(SVF_AXES, m_DrawOptions.arrLogFonts+SVF_AXES);
	m_pRenderer->BuildFont(SVF_VALUES, m_DrawOptions.arrLogFonts+SVF_VALUES);

	Invalidate();
}



void CScadViewerView::OnOptionsChanged(const SViewOptions &rNewViewOptions)
{
	CWaitCursor cur;
	
	bool bReinit = (m_ViewOptions.SoftOGL != rNewViewOptions.SoftOGL);
	bool bReload =
		m_ViewOptions.bShowUsedNodes != rNewViewOptions.bShowUsedNodes ||
		m_ViewOptions.bRemoveDupPlanes != rNewViewOptions.bRemoveDupPlanes ||
		m_ViewOptions.bDrawOptimize != rNewViewOptions.bDrawOptimize;
	m_ViewOptions = rNewViewOptions;
	if (bReinit)
	{
		RebindGL();
	}
	if (bReload)
		ReloadDoc();
	else
		DrawOptionsChanged();
}

void CScadViewerView::OnCut()
{
	if(State != ST_INV_CUT)
		m_StateBeforeCut = State;
	State = ST_CUT;
}

void CScadViewerView::OnInvCut()
{
	if(State != ST_CUT)
		m_StateBeforeCut = State;
	State = ST_INV_CUT;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateCut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_ViewPos.bPerspective);
	pCmdUI->SetCheck(State == ST_CUT);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateNoCut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Cutter.CanUndo());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateInvCut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_ViewPos.bPerspective);
	pCmdUI->SetCheck(State == ST_INV_CUT);
}



void CScadViewerView::OnNoCut()
{
	CWaitCursor cur;
	m_Cutter.CancelCut();
	ZoomAll();
}

void CScadViewerView::OnCutUndo()
{
	CWaitCursor cur;
	bool bNeedZoomAll;
	m_Cutter.Undo(bNeedZoomAll);
	if (bNeedZoomAll)
		ZoomAll();
	else
		Invalidate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateCutUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Cutter.CanUndo());
}


void CScadViewerView::OnProjection() 
{
	Rot.SetPredefinedView(m_nLastViewNo);
	ZoomAll();
}


void CScadViewerView::OnView3dviews(UINT nID) 
{
	m_nLastViewNo = nID-ID_VIEW_3DVIEWS_TOP;
	Rot.SetPredefinedView(m_nLastViewNo);
	reinterpret_cast<CScadViewerFrame *>(GetParent())->SetProjectionButton(m_nLastViewNo);
	ZoomAll();
}

void CScadViewerView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (!m_bDisplayPopupMenu)
		return;
	CMenu Popup;
	Popup.LoadMenu(IDR_POPUP_MENUS);
	CViewGeometry* pGeometry = GetDocument()->m_pViewGeometry;
	NUM_ELEM_TYPE nSelestedEl = pGeometry ? pGeometry->ElementArray.GetSelectedElement() : 0;
	CMenu* pPopup = Popup.GetSubMenu(nSelestedEl == 0 ? 1: 6);
	ASSERT(pPopup);
	//CRect rc;
	dynamic_cast<CWinAppEx*>(AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pPopup->m_hMenu, point.x,point.y,this,TRUE);
	//pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,	point.x, point.y, GetParent(), nullptr/*&rc*/);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CFrameWnd* pwndFrame = GetParentFrame();
	if(nullptr != pwndFrame)
		pwndFrame->SendMessage(WM_INITMENUPOPUP,WPARAM(pPopupMenu->m_hMenu), MAKELPARAM(nIndex,bSysMenu));
}

void CScadViewerView::OnPlatesHorizontal() 
{
	INVERT(m_DrawOptions.bElHorizontal);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdatePlatesHorizontal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bElHorizontal);
}

void CScadViewerView::OnPlatesVertical() 
{
	INVERT(m_DrawOptions.bElVertical);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdatePlatesVertical(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bElVertical);
}

void CScadViewerView::OnPlatesSlanted() 
{
	INVERT(m_DrawOptions.bElOther);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdatePlatesSlanted(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bElOther);
}

void CScadViewerView::OnBarsHorizontal() 
{
	INVERT(m_DrawOptions.bBarHorizontal);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateBarsHorizontal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bBarHorizontal);
}

void CScadViewerView::OnBarsVertical() 
{
	INVERT(m_DrawOptions.bBarVertical);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateBarsVertical(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bBarVertical);
}

void CScadViewerView::OnBarsSlanted() 
{
	INVERT(m_DrawOptions.bBarOther);
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateBarsSlanted(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_DrawOptions.bBarOther);
}



void CScadViewerView::OnFilePrintPreview() 
{
	m_pOldMainWnd = AfxGetThread()->m_pMainWnd;
	AfxGetThread()->m_pMainWnd = GetParentFrame();
	C3DBoxView::OnFilePrintPreview();
}

void CScadViewerView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	C3DBoxView::OnEndPrintPreview(pDC, pInfo, point, pView);
	if (m_pOldMainWnd)
		AfxGetThread()->m_pMainWnd = m_pOldMainWnd;
	else
		AfxGetThread()->m_pMainWnd = GetParentFrame();
}

void CScadViewerView::OnInitialUpdate() 
{
	DrawOptionsChanged();
	C3DBoxView::OnInitialUpdate();
}

void CScadViewerView::ReloadDoc()
{
	CViewGeometry *pViewGeometry = GetDocument()->m_pViewGeometry;
	if (pViewGeometry == nullptr)
		return;
	NUM_ELEM_TYPE nSelectedElement = pViewGeometry->ElementArray.GetSelectedElement();
	GetDocument()->Load();
	GetDocument()->m_pViewGeometry->ElementArray.SelectElement(nSelectedElement);
	m_Cutter.RedoAll();
	DrawOptionsChanged();
}

// ReSharper disable once CppMemberFunctionMayBeConst
BOOL CScadViewerView::SetViewFilePath( const TCHAR * sFilePath, const TCHAR * sTypeExt )
{
	GetDocument()->GetDocTemplate()->OpenDocumentFile(sFilePath);
	return TRUE;
}




// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnFileEdit() 
{
	CString strFileName = GetDocument()->m_strFileName;
	if (strFileName.IsEmpty())
		return;
	::ShellExecute
		(
			m_hWnd,
			_T("open"),
			strFileName,
			nullptr,
			nullptr,//FolderTreeForm->FPath.c_str(),
			SW_SHOWNORMAL
		);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateFileEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetDocument()->GetPathName().IsEmpty());
	
}

void CScadViewerView::OnEditCopy() 
{
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*Geometry = pDoc->m_pViewGeometry;
	if(Geometry == nullptr)
		return;

	if ( !OpenClipboard() )
	{
	  AfxMessageBox( _T("Cannot open the Clipboard" ));
	  return;
	}
	// Remove the current Clipboard contents  
	if( !EmptyClipboard() )
	{
	  AfxMessageBox( _T("Cannot empty the Clipboard") );
	  return;  
	}
	CDibGlRenderer rend(Geometry, m_ViewPos);
	rend.BindDib(m_hWnd, CSize(ClientWidth, ClientHeight),  min(ClientWidth, ClientHeight) / 10);

	rend.Render(Geometry,&m_ViewOptions, &m_DrawOptions);

	rend.SetClipboardData();
	CloseClipboard();
	rend.ReleaseDib();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*Geometry = pDoc->m_pViewGeometry;
	pCmdUI->Enable(Geometry!=nullptr && (!pDoc->m_strFileName.IsEmpty() || pDoc->m_pSchem));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdatePane(CCmdUI* pCmdUI) 
{
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	if (!pDoc->m_pViewGeometry)
		return;
	CString strText;
	strText.Format(IDS_FILE_INFO_FORMAT,
		pDoc->m_pViewGeometry->m_ModelInfo.m_nNodeCount,
		pDoc->m_pViewGeometry->m_ModelInfo.m_nElementCount
		);
	pCmdUI->SetText(strText+m_strFps+_T(" ")+m_pRenderer->GetRenderString());
	pCmdUI->Enable();
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppMemberFunctionMayBeStatic
void CScadViewerView::OnUpdatePane2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateSliderFlength(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ViewPos.bPerspective);	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnExportToDxf() 
{
	CString strFileName = GetDocument()->GetPathName();
	CViewGeometry *pGeometry = GetDocument()->m_pViewGeometry;
	if (strFileName.IsEmpty())
#ifdef SCAD21
		strFileName = ApiGetProjectNameFile(GetDocument()->m_pSchem);
#else
		strFileName = GetDocument()->m_pSchem->FileName;
#endif
	if (strFileName.IsEmpty() || pGeometry == nullptr )
		return;
	CFileDialog dlgFile(false);
	CString title;
	VERIFY(title.LoadString(IDS_EXPORT_DXF_TITLE));

	dlgFile.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

	CString strFilter;
	LPTSTR szExt = PathFindExtension(strFileName.GetBuffer(_MAX_PATH));
	_tcscpy_s(szExt, 5, _T(".dxf"));
	strFileName.ReleaseBuffer();
	strFilter += _T("Autocad DXF (*.dxf)");
	strFilter += TCHAR('\0');   // next string please
	strFilter += _T("*.dxf");
	strFilter += TCHAR('\0');   // last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = strFileName.GetBuffer(_MAX_PATH);

	
	INT_PTR nResult = dlgFile.DoModal();
	strFileName.ReleaseBuffer();
	if (nResult==IDOK)
		pGeometry->ExportToDxf(strFileName);
}

void CScadViewerView::OnExportToBmp() 
{
	CString strFileName = GetDocument()->GetPathName();
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*Geometry = pDoc->m_pViewGeometry;
	if(Geometry == nullptr)
		return;
	//CFileDialog dlgFile(false);
	CBmpSaveDlg dlgFile;
	CString title;
	VERIFY(title.LoadString(IDS_EXPORT_BMP_TITLE));

	dlgFile.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

	CString strFilter;
	LPTSTR szExt = PathFindExtension(strFileName.GetBuffer(_MAX_PATH));
	_tcscpy_s(szExt, 5, _T(".bmp"));
	strFileName.ReleaseBuffer();
	strFilter += _T("Windows bitmap (*.bmp)");
	strFilter += TCHAR('\0');   // next string please
	strFilter += _T("*.bmp");
	strFilter += TCHAR('\0');   // last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = strFileName.GetBuffer(_MAX_PATH);

	
	dlgFile.m_nBmpWidth = ClientWidth; dlgFile.m_nBmpHeight = ClientHeight;
	INT_PTR nResult = dlgFile.DoModal();
	strFileName.ReleaseBuffer();
	if (nResult!=IDOK)
		return;
	int nWidth = dlgFile.m_nBmpWidth;
	int nHeight = dlgFile.m_nBmpHeight;
	if (nWidth ==0 || nHeight==0)
	{
		AfxMessageBox(IDS_BMP_SIZE_ERR, MB_ICONERROR | MB_OK);
		return;
	}
	CWaitCursor crWait;
	CDibGlRenderer rend(Geometry, m_ViewPos);
	rend.BindDib(m_hWnd, CSize(nWidth, nHeight),  min(nWidth, nHeight) / 10);

	rend.Render(Geometry,&m_ViewOptions, &m_DrawOptions);
/*
	CBitmap bmp;
	SECDib dib;
	m_pRenderer->SetToBitmap(bmp, dib);
	m_pRenderer->ReleaseDib();
	dib.SaveImage(strFileName);
*/
	rend.SaveImage(strFileName);	
	rend.ReleaseDib();
}

void CScadViewerView::OnUpdateExportToBmp(CCmdUI* pCmdUI) 
{
	OnUpdateEditCopy(pCmdUI);
}


void CScadViewerView::OnViewModeSelect() 
{
	State = ST_SELECT;
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateViewModeSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(State == ST_SELECT ? 1 : 0);	
}

void CScadViewerView::OnSelectHideElement() 
{
	NUM_ELEM_TYPE nNumElem = GetDocument()->m_pViewGeometry->ElementArray.GetSelectedElement();
	m_Cutter.DoCut(HIDE_ELEMENT, m_ViewPos.Rot, 0, 0,0,0,nNumElem);
	Invalidate();
}

bool CScadViewerView::IsForumGeometry() const
{
	if (!GetDocument()->m_pViewGeometry)
		return false;
	return GetDocument()->m_pViewGeometry->IsForumGeometry();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateHideElementPlate(CCmdUI *pCmdUI)
{
	bool bEnable = false;
	CViewGeometry *pGeometry = GetDocument()->m_pViewGeometry;
	TOrgElemType elOrgType = pGeometry ? pGeometry->ElementArray.GetSelElemOrgType() : EL_BAR;
	switch (elOrgType)
	{
	case EL_PLATE:
	case EL_SLAB:
	case EL_WALL:
	case EL_ROOF:
	case EL_ISO:
		bEnable = true;
		break;
	case EL_BAR: break;
	case EL_SOLID: break;
	case EL_COLUMN: break;
	case EL_BEAM: break;
	default: break;
	}

	pCmdUI->Enable(bEnable);
}

void CScadViewerView::OnHideElementPlate() 
{
	NUM_ELEM_TYPE nNumElem = GetDocument()->m_pViewGeometry->ElementArray.GetSelectedElement();
	m_Cutter.DoCut(HIDE_ELEMENT_PLATE, m_ViewPos.Rot, 0, 0,0,0,nNumElem);
	Invalidate();
}

void CScadViewerView::OnShowElementPlate() 
{
	NUM_ELEM_TYPE nNumElem = GetDocument()->m_pViewGeometry->ElementArray.GetSelectedElement();
	m_Cutter.DoCut(SHOW_ELEMENT_PLATE, m_ViewPos.Rot, 0, 0,0,0,nNumElem);
	ZoomAll();
}


void CScadViewerView::OnLight()
{
	INVERT(m_DrawOptions.bLighting);
	Invalidate();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerView::OnUpdateLight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_DrawOptions.bLighting);
}


BOOL CScadViewerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return C3DBoxView::OnEraseBkgnd(pDC);
}
