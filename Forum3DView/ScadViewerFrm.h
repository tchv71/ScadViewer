// ScadViewerFrm.h : interface of the CScadViewerFrame class
//
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_MAINFRM_H__F0ABEA1B_493B_11D5_B1B3_000102C8846A__INCLUDED_)
#define AFX_MAINFRM_H__F0ABEA1B_493B_11D5_B1B3_000102C8846A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScadViewerView;
#include "..\Forum3DView\Forum3DView.h"
#include "DepthDialogBar.h"
#include "CameraDialogBar.h"
#include "SCADViewerStatBar.h"
#include <map>
class CMp4View;

class FORUM3DVIEW_EXPORT CScadViewerFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CScadViewerFrame();
	DECLARE_DYNCREATE(CScadViewerFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScadViewerFrame)
	public:
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	protected:
	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) override;
	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	//}}AFX_VIRTUAL

// Implementation
public:
	void ActivateFrame(int nCmdShow = -1) override;
	void SetProjectionButton(UINT nViewNo);
	void SetButtonImage(UINT nIDToolBar, UINT nID, UINT nFirstImageCmd, UINT nImageIndex);
	virtual ~CScadViewerFrame();
	bool *m_pbClosed;
	void SetCloseFlag(bool *pbClosed)
	{
		m_pbClosed = pbClosed;
	}
	CSCADViewerStatBar &GetStatusBar() {return m_wndStatusBar; }
	void DockPaneRightOf(CPane* pBar, CPane* pRightOf);
	void DockPaneBottomOf(CPane* pBar, CPane* pBottomOf);

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

protected:  // control bar embedded members
	CSCADViewerStatBar  m_wndStatusBar;
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar    m_wndToolBar;
	CMFCToolBar	m_wndFitersToolBar;
	CMFCToolBar	m_wndCutToolBar;
	CDepthDialogBar		m_wndDepthDialogBar;
	CCameraDialogBar	m_wndCameraDialogBar;
	CScadViewerView		*m_p3DView;
	CMp4View			*m_pMp4View;
	bool m_bFirstActivate;
	std::map<int,int> m_mapCmdToImgIndex;
// Generated message map functions
protected:
	static void SetControlBarName(CPane &bar, CString str);
	virtual void SetToolBarNames();
	CMenu	m_Menu;
	virtual BOOL UpdateSettings(bool bLoad);
	//{{AFX_MSG(CScadViewerFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnToolsOptions();
	afx_msg void OnCameraChanged();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateContextInstruments(CCmdUI* pCmdUI);
	afx_msg void OnContextInstruments();
	afx_msg void OnUpdateContextCut(CCmdUI* pCmdUI);
	afx_msg void OnContextCut();
	afx_msg void OnUpdateContextCamera(CCmdUI* pCmdUI);
	afx_msg void OnContextCamera();
	afx_msg void OnUpdateContextDepth(CCmdUI* pCmdUI);
	afx_msg void OnContextDepth();
	afx_msg void OnContextFilters();
	afx_msg void OnUpdateContextFilters(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewResults(CCmdUI* pCmdUI);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CDropdownButton : public CMFCToolBarMenuButton
{
	DECLARE_SERIAL(CDropdownButton)

public:
	CDropdownButton()
	{
	}

	CDropdownButton(UINT uiCmdID, HMENU h, LPCTSTR lpszText) : CMFCToolBarMenuButton(uiCmdID, h, GetCmdMgr()->GetCmdImage(uiCmdID, FALSE), lpszText)
	{
	}



protected:

	BOOL IsEmptyMenuAllowed() const override
	{
		return TRUE;
	}

	void OnChangeParentWnd(CWnd* pWndParent) override
	{
		CMFCToolBarMenuButton::OnChangeParentWnd(pWndParent);
		m_bDrawDownArrow = TRUE;
	}

	BOOL IsExclusive() const override
	{
		return FALSE;
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F0ABEA1B_493B_11D5_B1B3_000102C8846A__INCLUDED_)
