#if !defined(AFX_SCADVIEWERSTATBAR_H__2001892B_3864_4E7A_B4C0_5303535950A2__INCLUDED_)
#define AFX_SCADVIEWERSTATBAR_H__2001892B_3864_4E7A_B4C0_5303535950A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SCADViewerStatBar.h : header file
//
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

/////////////////////////////////////////////////////////////////////////////
// CSCADViewerStatBar window

//#include "SCAD3DModelAPIDef.hxx"

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
class  CSCADViewerStatBar : public CMFCStatusBar
{
// Construction
public:
	CSCADViewerStatBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCADViewerStatBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSCADViewerStatBar();

	virtual	void	SetGenInfo		( const TCHAR * sInfoText );
	virtual	void	SetFileCount	( UINT nFiles );	
	virtual	void	IncFilePos		();
	virtual	void	BreakDrawFile	();
	virtual	void	SetFileInfo		( const TCHAR * sFileInfo );

	// Generated message map functions
protected:
	//{{AFX_MSG(CSCADViewerStatBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdatePane (CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	int m_Progress;
	int m_nFiles;
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCADVIEWERSTATBAR_H__2001892B_3864_4E7A_B4C0_5303535950A2__INCLUDED_)
