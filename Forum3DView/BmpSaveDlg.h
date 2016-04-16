// BmpSaveDlg.h : header file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV

// All Rights Reserved

// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_BMPSAVEDLG_H__5751430D_8150_4DD7_AC62_554D6716F7EB__INCLUDED_)
#define AFX_BMPSAVEDLG_H__5751430D_8150_4DD7_AC62_554D6716F7EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NumEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CBmpSaveDlg dialog
class CBmpSaveDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CBmpSaveDlg)

public:
	int m_nBmpHeight;
	int m_nBmpWidth;
	BOOL m_bLockProp;
	CBmpSaveDlg(BOOL bOpenFileDialog=FALSE, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = nullptr,
		LPCTSTR lpszFileName = nullptr,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = nullptr,
		CWnd* pParentWnd = nullptr);

protected:
	CNumEdit m_ctlEditWidth;
	CNumEdit m_ctlEditHeight;
	float	 m_fAspect;
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	//{{AFX_MSG(CBmpSaveDlg)
	BOOL OnInitDialog() override;
	afx_msg void OnWidthChange();
	afx_msg void OnHeightChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSAVEDLG_H__5751430D_8150_4DD7_AC62_554D6716F7EB__INCLUDED_)
