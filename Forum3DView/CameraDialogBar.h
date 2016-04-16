#if !defined(AFX_CAMERADIALOGBAR_H__C8A375BB_D844_4754_8166_B263263299E2__INCLUDED_)
#define AFX_CAMERADIALOGBAR_H__C8A375BB_D844_4754_8166_B263263299E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraDialogBar.h : header file
//
#include "DepthDialogBar.h"
/////////////////////////////////////////////////////////////////////////////
// CCameraDialogBar window

class CCameraDialogBar : public CDepthDialogBar
{
	DECLARE_DYNAMIC(CCameraDialogBar)
// Construction
public:
	CCameraDialogBar();

// Attributes
public:
	int m_nFocusLength;
	bool m_bChangeDistance;
// Operations
public:
	BOOL Create(UINT nIDTemplate, CWnd* pParentWnd, UINT nStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, UINT nID=0);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraDialogBar)
	public:
	CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz) override;
	int OnToolHitTest(CPoint point, TOOLINFO* pTI) const override;
	//}}AFX_VIRTUAL

// Implementation
public:
	void CenterHeight(UINT nID, int cy) const;
	virtual ~CCameraDialogBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCameraDialogBar)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERADIALOGBAR_H__C8A375BB_D844_4754_8166_B263263299E2__INCLUDED_)
