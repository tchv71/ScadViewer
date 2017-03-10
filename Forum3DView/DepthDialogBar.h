// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV

// All Rights Reserved

// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#if !defined(AFX_DEPTHDIALOGBAR_H__1EE1C81B_1744_47BE_BA51_B1A945715CD0__INCLUDED_)
#define AFX_DEPTHDIALOGBAR_H__1EE1C81B_1744_47BE_BA51_B1A945715CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DepthDialogBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDepthDialogBar window

class CDepthDialogBar : public CMFCToolBar
{
	DECLARE_DYNAMIC(CDepthDialogBar)
// Construction
public:
	CDepthDialogBar(UINT nId);

	AFX_DOCK_TYPE GetDockingMode() const override
	{ return DT_IMMEDIATE; }
	virtual BOOL Create(UINT IDD, CWnd* pParentWnd, DWORD dwStyle = AFX_DEFAULT_TOOLBAR_STYLE, UINT nID = AFX_IDW_TOOLBAR);

//	BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, BOOL bHasGripper, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID,
//		DWORD dwTabbedStyle = AFX_CBRS_REGULAR_TABS, DWORD dwControlBarStyle = AFX_DEFAULT_DOCKING_PANE_STYLE)
//	{
//		m_lpszBarTemplateName = (LPTSTR)lpszTemplateName;
//		CRect rc;
//		return CMFCToolBar::Create(afxGlobalData.RegisterWindowClass(_T("Afx:ToolBar")),nStyle,rc, pParentWnd,nID);
//	}
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDepthDialogBar)
	CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz) override;
	INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const override;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDepthDialogBar();
protected:
	UINT m_nId;
	// Generated message map functions
protected:
	//{{AFX_MSG(CDepthDialogBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//	afx_msg void OnNcPaint();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEPTHDIALOGBAR_H__1EE1C81B_1744_47BE_BA51_B1A945715CD0__INCLUDED_)
