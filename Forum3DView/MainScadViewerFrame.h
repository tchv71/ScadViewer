// MainScadViewerFrame.h : header file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#if !defined(AFX_MAINSCADVIEWERFRAME_H__34ECD6F6_6515_40D3_B8C8_1E85135F4B95__INCLUDED_)
#define AFX_MAINSCADVIEWERFRAME_H__34ECD6F6_6515_40D3_B8C8_1E85135F4B95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainScadViewerFrame frame
#include "ScadViewerFrm.h"
#include "FolderTreeDockingWnd.h"
#include "DockFolderWnd.h"
#include "DetViewOpts.h"
#include "IsoViewerFrame.h"


class FORUM3DVIEW_EXPORT CMainScadViewerFrame : public CIsoViewerFrame
{
	DECLARE_DYNCREATE(CMainScadViewerFrame)
protected:
	CMainScadViewerFrame();           // protected constructor used by dynamic creation

// Attributes

	// Operations
public:
	void OnViewInFolder(LPCTSTR pszPath);
	BOOL SetCurViewFolder( const TCHAR * sFolderPath );
	void ActivateFrame(int nCmdShow = -1) override;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainScadViewerFrame)
	protected:
	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString GetSelWorkFileMask();
	CString m_strWorkDir;
	void SetToolBarNames() override;
	BOOL UpdateSettings(bool bLoad) override;
	SViewerOptions m_ViewerOptions;
	CFolderTreeDockingWnd m_FolderTreeDockingWnd;
	CDockFolderWnd		  m_FolderWnd;
	virtual ~CMainScadViewerFrame();

	// Generated message map functions
	//{{AFX_MSG(CMainScadViewerFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewThumbnail();
	afx_msg void OnUpdateViewThumbnail(CCmdUI* pCmdUI);
	afx_msg void OnViewLargeIcon();
	afx_msg void OnUpdateViewLargeIcon(CCmdUI* pCmdUI);
	afx_msg void OnViewSmallIcon();
	afx_msg void OnUpdateViewSmallIcon(CCmdUI* pCmdUI);
	afx_msg void OnViewList();
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnToolsOptions();
	afx_msg void OnScadViewDblclick();
	afx_msg void OnViewFolderTree();
	afx_msg void OnUpdateViewFolderTree(CCmdUI* pCmdUI);
	afx_msg void OnViewFolderView();
	afx_msg void OnUpdateViewFolderView(CCmdUI* pCmdUI);
	afx_msg void OnFileDelete();
	afx_msg void OnTreeExplorer();
	afx_msg void OnUpdateFileCalcresDelete(CCmdUI* pCmdUI);
	afx_msg void OnFileCalcresDelete();
	afx_msg void OnFileCalcresSelDelete();
	afx_msg void OnMenuViewRefresh();
	afx_msg void OnUpdateViewResults(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSCADVIEWERFRAME_H__34ECD6F6_6515_40D3_B8C8_1E85135F4B95__INCLUDED_)
