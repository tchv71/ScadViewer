#pragma once
#include "depthdialogbar.h"

class CResultsDialogBar :	public CDepthDialogBar
{
	DECLARE_DYNAMIC(CResultsDialogBar)
// Construction
public:
	CResultsDialogBar(void);
	virtual ~CResultsDialogBar(void);
// Attributes
public:
// Operations
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraDialogBar)
	public:
	CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz) override;
	//}}AFX_VIRTUAL

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeComboFactor();
};

