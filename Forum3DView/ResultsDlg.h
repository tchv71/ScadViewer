// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#if !defined(AFX_RESULTSDLG_H__4EB5C2BE_98F9_4BEB_9D73_969049130B55__INCLUDED_)
#define AFX_RESULTSDLG_H__4EB5C2BE_98F9_4BEB_9D73_969049130B55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ForumView_ENG/resource.h"
// ResultsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultsDlg dialog

class CResultsDlg : public CDialog
{
// Construction
public:
	CResultsDlg(CString strResultsMask, CWnd* pParent = nullptr);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResultsDlg)
	enum { IDD = IDD_RESULTS };
	CListCtrl	m_ListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultsDlg)
	protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ReloadFileList();
	CString m_strResultsMask;
	// Generated message map functions
	//{{AFX_MSG(CResultsDlg)
	BOOL OnInitDialog() override;
	afx_msg void OnSelectAll();
	afx_msg void OnDelete();
	afx_msg void OnCreateZip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTSDLG_H__4EB5C2BE_98F9_4BEB_9D73_969049130B55__INCLUDED_)
