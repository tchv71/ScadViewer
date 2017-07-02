// ScadViewer.h : main header file for the SCADVIEWER application
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_SCADVIEWER_H__F0ABEA17_493B_11D5_B1B3_000102C8846A__INCLUDED_)
#define AFX_SCADVIEWER_H__F0ABEA17_493B_11D5_B1B3_000102C8846A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "ForumView_ENG/resource.h"       // main symbols
#include "Forum3DView/SCAD3DMdlSettings.h"
/////////////////////////////////////////////////////////////////////////////
// CScadViewerApp:
// See ScadViewer.cpp for the implementation of this class
//

class CScadViewerApp : public CWinAppEx
{
public:
	CScadViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScadViewerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance(void);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CScadViewerApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CSCAD3DMdlSettings m_Settings;

	//	afx_msg void OnToolsOptions();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCADVIEWER_H__F0ABEA17_493B_11D5_B1B3_000102C8846A__INCLUDED_)
