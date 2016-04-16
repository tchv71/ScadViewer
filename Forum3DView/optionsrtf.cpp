// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
// OptionsRtf.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "OptionsRtf.h"
#include "Renderer.h"


// COptionsRtf dialog

IMPLEMENT_DYNAMIC(COptionsRtf, CPropertyPage)
COptionsRtf::COptionsRtf(CDrawOptions	&rDrawOptions) : CPropertyPage(COptionsRtf::IDD),
	m_rDrawOptions(rDrawOptions)
	//m_FontAxesDlg(&(rDrawOptions.arrLogFonts[0]), nullptr, this),
	//m_FontDlg(&(rDrawOptions.arrLogFonts[1]),nullptr, this)
{
	//{{AFX_DATA_INIT(COptionsRtf)
	m_dblDefScale = m_rDrawOptions.dblDefScale;
	//}}AFX_DATA_INIT
}

COptionsRtf::~COptionsRtf()
{
}

void COptionsRtf::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsRtf)
	DDX_Control(pDX, IDC_DEFORM_SCALE_SPIN, m_DefScaleSpin);
	DDX_Text(pDX, IDC_DEFORM_SCALE_EDIT, m_dblDefScale);
	DDV_MinMaxDouble(pDX, m_dblDefScale, 1.e-003, 1000.);
	//}}AFX_DATA_MAP
	if( pDX->m_bSaveAndValidate )
	{
		m_rDrawOptions.dblDefScale = m_dblDefScale;
	}
}


BEGIN_MESSAGE_MAP(COptionsRtf, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsRtf)
	ON_BN_CLICKED(IDC_FONT_RESULTS, OnFontResults)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DEFORM_SCALE_SPIN, OnDeltaposDeformScaleSpin)
	ON_BN_CLICKED(IDC_FONT_AXES, OnFontAxes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// COptionsRtf message handlers

void COptionsRtf::OnFontResults() 
{
	CFontDialog		m_FontDlg(&(m_rDrawOptions.arrLogFonts[1]), CF_EFFECTS | CF_SCREENFONTS, nullptr, this);
	m_FontDlg.DoModal();
}

void COptionsRtf::OnFontAxes() 
{
	CFontDialog		m_FontAxesDlg(&(m_rDrawOptions.arrLogFonts[0]), CF_EFFECTS | CF_SCREENFONTS, nullptr, this);
	m_FontAxesDlg.DoModal();	
}

void COptionsRtf::OnDeltaposDeformScaleSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	NM_UPDOWN* pNMUpDown = reinterpret_cast<NM_UPDOWN*>(pNMHDR);
	// TODO: Add your control notification handler code here
	const double c_dStep = 0.5;
	switch(pNMUpDown->iDelta)
	{
	case -1:
		if (m_dblDefScale> c_dStep)
		{
			m_dblDefScale = int(m_dblDefScale/c_dStep)*c_dStep;
			m_dblDefScale -= c_dStep;
		}
		break;
	case 1:
		if (m_dblDefScale<1000)
		{
			m_dblDefScale = int(m_dblDefScale/c_dStep)*c_dStep;
			m_dblDefScale += c_dStep;
		}
		break;
	}
	UpdateData(FALSE);
	SetModified();
	*pResult = 0;
}
