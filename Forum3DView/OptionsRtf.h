// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#pragma once


class CDrawOptions;

// COptionsRtf dialog

class COptionsRtf : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionsRtf)

public:
	COptionsRtf(CDrawOptions	&rDrawOptions);
	virtual ~COptionsRtf();

// Dialog Data
	//{{AFX_DATA(COptionsRtf)
	enum { IDD = IDD_TAB_RTF };
	CSpinButtonCtrl	m_DefScaleSpin;
	double	m_dblDefScale;
	//}}AFX_DATA

protected:
	// Generated message map functions
	//{{AFX_MSG(COptionsRtf)
	afx_msg void OnFontResults();
	afx_msg void OnDeltaposDeformScaleSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFontAxes();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	CDrawOptions	&m_rDrawOptions;

};
