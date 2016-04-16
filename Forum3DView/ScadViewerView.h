// ScadViewerView.h : interface of the CScadViewerView class
//
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_SCADVIEWERVIEW_H__F0ABEA1F_493B_11D5_B1B3_000102C8846A__INCLUDED_)
#define AFX_SCADVIEWERVIEW_H__F0ABEA1F_493B_11D5_B1B3_000102C8846A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "View3DBox.h"

class CScadViewerDoc;
#include "Forum3DView.h"

class FORUM3DVIEW_EXPORT CScadViewerView : public C3DBoxView
{
protected: // create from serialization only
	CScadViewerView();
	DECLARE_DYNCREATE(CScadViewerView)

// Attributes
public:
	CScadViewerDoc* GetDocument() const;

// Operations
public:
	void OnOptionsChanged(const SViewOptions &rNewViewOptions);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScadViewerView)
	public:
	void OnDraw(CDC* pDC) override;  // overridden to draw this view
	void OnInitialUpdate() override;
	protected:
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
	void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) override;
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL SetViewFilePath( const TCHAR * sFilePath, const TCHAR * sTypeExt );
	virtual ~CScadViewerView();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
	void ReloadDoc();

	// Generated message map functions
protected:
	bool IsForumGeometry() const;
	UINT m_nLastViewNo;
	//{{AFX_MSG(CScadViewerView)
	afx_msg void OnUpdateViewZoom(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomIn();
	afx_msg void OnViewZoomOut();
	afx_msg void OnViewZoomAll();
	afx_msg void OnUpdateViewModeZoomWin(CCmdUI* pCmdUI);
	afx_msg void OnViewModeZoomWin();
	afx_msg void OnUpdateViewModePan(CCmdUI* pCmdUI);
	afx_msg void OnViewModePan();
	afx_msg void OnUpdateViewModeRotate(CCmdUI* pCmdUI);
	afx_msg void OnViewModeRotate();
	afx_msg void OnUpdateViewModeLookAround(CCmdUI* pCmdUI);
	afx_msg void OnViewModeLookAround();
	afx_msg void OnViewModeWalk();
	afx_msg void OnUpdateViewModeWalk(CCmdUI* pCmdUI);
	afx_msg void OnViewPerspective();
	afx_msg void OnUpdateViewPerspective(CCmdUI* pCmdUI);
	afx_msg void OnViewModeWireframe();
	afx_msg void OnViewModeSolid();
	afx_msg void OnViewModeElementborders();
	afx_msg void OnViewModeTransparent();
	afx_msg void OnUpdateViewModeWireframe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModeSolid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModeElementborders(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewModeTransparent(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsColumns();
	afx_msg void OnUpdateViewElementsColumns(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsConstraints();
	afx_msg void OnUpdateViewElementsConstraints(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsNodes();
	afx_msg void OnUpdateViewElementsNodes(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsPlates();
	afx_msg void OnUpdateViewElementsPlates(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsRoofs();
	afx_msg void OnUpdateViewElementsRoofs(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsSlabs();
	afx_msg void OnUpdateViewElementsSlabs(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsSolids();
	afx_msg void OnUpdateViewElementsSolids(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsWalls();
	afx_msg void OnUpdateViewElementsWalls(CCmdUI* pCmdUI);
	afx_msg void OnViewElementsBars();
	afx_msg void OnViewElementsBeams();
	afx_msg void OnUpdateViewElementsBars(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewElementsBeams(CCmdUI* pCmdUI);
	afx_msg void OnProjection();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnPlatesHorizontal();
	afx_msg void OnUpdatePlatesHorizontal(CCmdUI* pCmdUI);
	afx_msg void OnPlatesVertical();
	afx_msg void OnUpdatePlatesVertical(CCmdUI* pCmdUI);
	afx_msg void OnPlatesSlanted();
	afx_msg void OnUpdatePlatesSlanted(CCmdUI* pCmdUI);
	afx_msg void OnBarsHorizontal();
	afx_msg void OnUpdateBarsHorizontal(CCmdUI* pCmdUI);
	afx_msg void OnBarsVertical();
	afx_msg void OnUpdateBarsVertical(CCmdUI* pCmdUI);
	afx_msg void OnBarsSlanted();
	afx_msg void OnUpdateBarsSlanted(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnFileEdit();
	afx_msg void OnUpdateFileEdit(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePane(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePane2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSliderFlength(CCmdUI* pCmdUI);
	afx_msg void OnExportToDxf();
	afx_msg void OnExportToBmp();
	afx_msg void OnUpdateExportToBmp(CCmdUI* pCmdUI);
	afx_msg void OnViewModeSelect();
	afx_msg void OnUpdateViewModeSelect(CCmdUI* pCmdUI);
	afx_msg void OnSelectHideElement();
	afx_msg void OnUpdateHideElementPlate(CCmdUI *pCmdUI);
	afx_msg void OnHideElementPlate();
	afx_msg void OnShowElementPlate();
	afx_msg void OnViewElementsAxes();
	afx_msg void OnUpdateViewElementsAxes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnView3dviews(UINT nID);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewShowbarprofile();
	afx_msg void OnViewShowplatethickness();
	afx_msg void OnUpdateViewShowbarprofile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewShowplatethickness(CCmdUI *pCmdUI);
	afx_msg void OnCut();
	afx_msg void OnUpdateCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNoCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInvCut(CCmdUI *pCmdUI);
	afx_msg void OnInvCut();
	afx_msg void OnNoCut();
	afx_msg void OnCutUndo();
	afx_msg void OnUpdateCutUndo(CCmdUI *pCmdUI);
	afx_msg void OnLight();
	afx_msg void OnUpdateLight(CCmdUI *pCmdUI);
	void DrawOptionsChanged();
private:
	CWnd	*m_pOldMainWnd;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in ScadViewerView.cpp
inline CScadViewerDoc* CScadViewerView::GetDocument() const
   { return static_cast<CScadViewerDoc*>(m_pDocument); }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCADVIEWERVIEW_H__F0ABEA1F_493B_11D5_B1B3_000102C8846A__INCLUDED_)
