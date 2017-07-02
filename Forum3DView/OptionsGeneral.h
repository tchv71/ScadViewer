// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#pragma once

#include "DetViewOpts.h"
#include "resource.h"
// COptionsGeneral dialog

class COptionsGeneral : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionsGeneral)

public:
	void OnOK() override;
	COptionsGeneral(SViewerOptions	&rViewerOptions);
	virtual ~COptionsGeneral();

// Dialog Data
	//{{AFX_DATA(COptionsGeneral)
	enum { IDD = IDD_TAB_GENERAL };
	CComboBox	m_Languages;
	CListBox	m_FileTypeList;
	CListBox	m_DefProjList;
	CSliderCtrl	m_ThumbWidthSlider;
	CSliderCtrl	m_ThumbHeightSlider;
	int			m_nThumbnailWidth;
	int			m_nThumbnailHeight;
	int			m_nLangID;
	//}}AFX_DATA

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsGeneral)
	BOOL OnInitDialog() override;
	afx_msg void OnSizeProp();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH  OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	void UpdateThumbnail() const;
	CBrush m_WhiteBrush;
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	CFLCProperties	m_ViewProperty;
	bool			m_bSyncChangeThumbSize;
	CBitmap			m_LockBmp;
	SViewerOptions	&m_rViewerOptions;
private:
	float m_fAspect;
	bool m_bManualThumbChange;
};
