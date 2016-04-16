// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#ifndef __DockFolderWnd_h__
#define __DockFolderWnd_h__

// Stingray Objective Toolkit
// AppWizard generated file
// DockFolderWnd.h : header file
//

//#include "SCAD3DModelAPIDef.hxx"
#include "Forum3DView.h"
#include "SettingManager.h"

/////////////////////////////////////////////////////////////////////////////
// CDockFolderWnd window

#define IDC_EMBEDDED_VIEW 200

//#include "FolderView.h"
#include "FolderListCtrl.h"

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
class FORUM3DVIEW_EXPORT CDockFolderWnd : public CDockablePane, public CSettingManager
{
// Construction
public:
	CDockFolderWnd();

// Attributes
public:
	CFolderListCtrl	m_childWnd;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockFolderWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler) override;
	BOOL UpdateSettings(bool bLoad);
	virtual ~CDockFolderWnd();
	void AddRecentDir(const CString &sDir);
protected:
	std::vector<CString> m_VecRecentDirs;
	CComboBox m_RecentComboWnd;

	// Generated message map functions
protected:
	void OnSelectRecentDir();
	void FillCombo();
	int m_nCbHeight;
	//{{AFX_MSG(CDockFolderWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __DockFolderWnd_h__
