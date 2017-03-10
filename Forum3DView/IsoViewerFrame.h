// IsoViewerFrame.h : header file
//
// Copyright (C) 2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_ISOVIEWERFRAME_H__1CE64F71_91D1_4778_B88C_05FFFE9E3BA2__INCLUDED_)
#define AFX_ISOVIEWERFRAME_H__1CE64F71_91D1_4778_B88C_05FFFE9E3BA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ScadViewerFrm.h"
#include "ResultsDialogBar.h"
#include "ScalePane.h"
/////////////////////////////////////////////////////////////////////////////
// CIsoViewerFrame frame

class CIsoViewGeometry;

class FORUM3DVIEW_EXPORT CIsoViewerFrame : public CScadViewerFrame
{
	DECLARE_DYNCREATE(CIsoViewerFrame)
protected:
	CIsoViewerFrame();           // protected constructor used by dynamic creation

// Attributes

// Operations
public:
	CIsoViewGeometry* Geom() const;
	void SetCheck(UINT nId, bool bValue) const;
	void OnParamsChanged(void);
	HWND m_hWndParent;
	void OnViewNewResults();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIsoViewerFrame)
	protected:
	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	//}}AFX_VIRTUAL


	// Implementation
protected:
	void SetToolBarNames() override;
	void OnParamsChangedFactor();
	virtual ~CIsoViewerFrame();
	UINT_PTR	m_nTimer;
	CMFCToolBar    m_wndToolBar;
	CDepthDialogBar		m_wndDefScaleDialogBar;
	CResultsDialogBar m_wndResParams;
	CScalePane m_ScaleWnd;
	void UpdateDeformScale() const;
	void FillFactorCombo() const;
	void OnUpdateCombo(CCmdUI* pCmdUI);
	void OnCbnSelchangeComboFactor();
	void OnCbnSelchangeComboLoad();


	// Generated message map functions
	//{{AFX_MSG(CIsoViewerFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateExportToDxf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSliderDefScale(CCmdUI* pCmdUI);
	afx_msg void OnCheckIsolines();
	afx_msg void OnCheckValues();
	afx_msg void OnCheckEggs();
	afx_msg void OnUpdateCheckIsolines(CCmdUI* pCmdUI);
	afx_msg void OnBtnIsolines();
	afx_msg void OnUpdateBtnValues(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnEggs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFactorGroup(CCmdUI* pCmdUI);
	afx_msg void OnFactorDisplacements();
	afx_msg void OnFactorStressfields();
	afx_msg void OnFactorStresscolourmap();
	afx_msg void OnUpdateFactorDisplacements(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFactorStressfields(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFactorStresscolourmap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewResults(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//typedef CIsoViewerFrame CIsoViewerFrameFull;

#endif // !defined(AFX_ISOVIEWERFRAME_H__1CE64F71_91D1_4778_B88C_05FFFE9E3BA2__INCLUDED_)
