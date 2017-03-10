// OptionsMaterial.cpp : implementation file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "resource.h"
#include "OptionsMaterial.h"


// COptionsMaterial dialog

IMPLEMENT_DYNAMIC(COptionsMaterial, CPropertyPage)
COptionsMaterial::COptionsMaterial(SViewOptions &rViewOptions, bool bShowLanguage)
	: CPropertyPage(COptionsMaterial::IDD), m_nLangID(1049),
	m_ViewOptions(rViewOptions),
	m_bShowLanguage(bShowLanguage)
{
}

COptionsMaterial::~COptionsMaterial()
{
}

void COptionsMaterial::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control( pDX, IDC_LANGUAGES, m_Languages );
	DDX_Control(pDX, IDC_BAR_COLOR_BTN, m_btnClrBars);
	DDX_Control(pDX, IDC_PLATE_COLOR_BTN, m_btnClrPlate);
	DDX_Control(pDX, IDC_BORDER_COLOR_BTN, m_btnClrBorder);
	DDX_Control(pDX, IDC_BACKGROUND_COLOR_BTN, m_btnClrBackground);
	DDX_Control(pDX, IDC_NODE_COLOR_BTN, m_btnClrNodes);
	DDX_Control(pDX, IDC_SOLIDS_COLOR_BTN, m_btnClrSolids);
	DDX_Control(pDX, IDC_DUPES_COLOR_BTN, m_btnClrDupes);
	DDX_Control(pDX, IDC_X_COLOR_BTN, m_btnClrBoundX);
	DDX_Control(pDX, IDC_Y_COLOR_BTN, m_btnClrBoundY);
	DDX_Control(pDX, IDC_Z_COLOR_BTN, m_btnClrBoundZ);
	DDX_Control(pDX, IDC_UX_COLOR_BTN, m_btnClrBoundUX);
	DDX_Control(pDX, IDC_UY_COLOR_BTN, m_btnClrBoundUY);
	DDX_Control(pDX, IDC_UZ_COLOR_BTN, m_btnClrBoundUZ);
	DDX_Control(pDX, IDC_LINE_WIDTH_EDIT, m_edtLineWidth);
	DDX_Control(pDX, IDC_LINE_WIDTH_SPIN, m_btnLineWidthSpin);
	DDX_Control(pDX, IDC_NODE_SIZE_EDIT, m_edtNodeSize);
	DDX_Control(pDX, IDC_NODE_SIZE_SPIN, m_btnNodeSizeSpin);

	DDX_Control(pDX, IDC_WALL_COLOR_BTN, m_btnClrWall);
	DDX_Control(pDX, IDC_SLAB_COLOR_BTN, m_btnClrSlab);
	DDX_Control(pDX, IDC_COLUMN_COLOR_BTN, m_btnClrColumn);
	DDX_Control(pDX, IDC_BEAM_COLOR_BTN, m_btnClrBeam);
	DDX_Control(pDX, IDC_ROOF_COLOR_BTN, m_btnClrRoof);

	if( pDX->m_bSaveAndValidate )
	{
		DDX_ColorButton(pDX, IDC_BAR_COLOR_BTN,			m_ViewOptions.BarColor);
		DDX_ColorButton(pDX, IDC_PLATE_COLOR_BTN,		m_ViewOptions.PlateColor);
		DDX_ColorButton(pDX, IDC_BORDER_COLOR_BTN,		m_ViewOptions.EdgeColor);
		DDX_ColorButton(pDX, IDC_BACKGROUND_COLOR_BTN,	m_ViewOptions.BackgroundColor);
		DDX_ColorButton(pDX, IDC_NODE_COLOR_BTN,		m_ViewOptions.NodeColor);
		DDX_ColorButton(pDX, IDC_SOLIDS_COLOR_BTN,		m_ViewOptions.SolidColor);
		DDX_ColorButton(pDX, IDC_DUPES_COLOR_BTN,		m_ViewOptions.DupeColor);
		DDX_ColorButton(pDX, IDC_X_COLOR_BTN,			m_ViewOptions.BoundsColor[0]);
		DDX_ColorButton(pDX, IDC_Y_COLOR_BTN,			m_ViewOptions.BoundsColor[1]);
		DDX_ColorButton(pDX, IDC_Z_COLOR_BTN,			m_ViewOptions.BoundsColor[2]);
		DDX_ColorButton(pDX, IDC_UX_COLOR_BTN,			m_ViewOptions.BoundsColor[3]);
		DDX_ColorButton(pDX, IDC_UY_COLOR_BTN,			m_ViewOptions.BoundsColor[4]);
		DDX_ColorButton(pDX, IDC_UZ_COLOR_BTN,			m_ViewOptions.BoundsColor[5]);

		DDX_ColorButton(pDX, IDC_WALL_COLOR_BTN,		m_ViewOptions.WallColor);
		DDX_ColorButton(pDX, IDC_SLAB_COLOR_BTN,		m_ViewOptions.SlabColor);
		DDX_ColorButton(pDX, IDC_COLUMN_COLOR_BTN,		m_ViewOptions.ColumnColor);
		DDX_ColorButton(pDX, IDC_BEAM_COLOR_BTN,		m_ViewOptions.BeamColor);
		DDX_ColorButton(pDX, IDC_ROOF_COLOR_BTN,		m_ViewOptions.RoofColor);

		m_ViewOptions.NodeSize	  = m_btnNodeSizeSpin.GetPos();
		m_ViewOptions.LineWidth   = m_btnLineWidthSpin.GetPos();

		m_ViewOptions.OGL10		  = m_btnCheckOGL10.GetCheck() !=0 ;
		m_ViewOptions.SoftOGL	  = m_btnCheckHardwAccel.GetCheck() ==0 ;
		m_ViewOptions.bLineSmooth = m_btnCheckLineSmooth.GetCheck() !=0 ;
		m_ViewOptions.bRemoveDupPlanes = m_btnCheckRemoveDupPlanes.GetCheck() !=0;
		m_ViewOptions.bDrawOptimize = m_btnCheckDrawOptimize.GetCheck() != 0;
		m_ViewOptions.bShowUsedNodes = m_btnShowUsedNodes.GetCheck() != 0;
		if( m_Languages.GetCurSel() >= 0 )
			m_nLangID = int(m_Languages.GetItemData( m_Languages.GetCurSel() ));

	}
	DDX_Control(pDX, IDC_CHECK_OGL10, m_btnCheckOGL10);
	DDX_Control(pDX, IDC_CHECK_HARDWARE_ACC, m_btnCheckHardwAccel);
	DDX_Control(pDX, IDC_CHECK_LINE_SMOOTH, m_btnCheckLineSmooth);
	DDX_Control(pDX, IDC_CHECK_DELETE_INNER_PLATES, m_btnCheckRemoveDupPlanes);
	DDX_Control(pDX, IDC_CHECK_DRAW_OPTIMIZE, m_btnCheckDrawOptimize);
	DDX_Control(pDX, IDC_CHECK_SHOW_USED_NODES, m_btnShowUsedNodes);
}


BEGIN_MESSAGE_MAP(COptionsMaterial, CPropertyPage)
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// COptionsMaterial message handlers


BOOL COptionsMaterial::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_btnLineWidthSpin.SetBuddy( &m_edtLineWidth );
	m_btnLineWidthSpin.SetRange( 1, 10 );
	m_btnLineWidthSpin.SetPos( m_ViewOptions.LineWidth);
	m_btnNodeSizeSpin.SetBuddy( &m_edtNodeSize );
	m_btnNodeSizeSpin.SetRange( 1, 10 );
	m_btnNodeSizeSpin.SetPos( m_ViewOptions.NodeSize);

	m_btnCheckOGL10.SetCheck(m_ViewOptions.OGL10);
	m_btnCheckHardwAccel.SetCheck(!m_ViewOptions.SoftOGL);
	m_btnCheckLineSmooth.SetCheck(m_ViewOptions.bLineSmooth);
	m_btnCheckRemoveDupPlanes.SetCheck(m_ViewOptions.bRemoveDupPlanes);
	m_btnCheckDrawOptimize.SetCheck(m_ViewOptions.bDrawOptimize);
	m_btnShowUsedNodes.SetCheck(m_ViewOptions.bShowUsedNodes);

	m_btnClrBars.Color		= m_ViewOptions.BarColor;
	m_btnClrPlate.Color		= m_ViewOptions.PlateColor;
	m_btnClrBorder.Color	= m_ViewOptions.EdgeColor;
	m_btnClrBackground.Color= m_ViewOptions.BackgroundColor;
	m_btnClrNodes.Color		= m_ViewOptions.NodeColor;
	m_btnClrSolids.Color	= m_ViewOptions.SolidColor;
	m_btnClrDupes.Color		= m_ViewOptions.DupeColor;
	m_btnClrBoundX.Color	= m_ViewOptions.BoundsColor[0];
	m_btnClrBoundY.Color	= m_ViewOptions.BoundsColor[1];
	m_btnClrBoundZ.Color	= m_ViewOptions.BoundsColor[2];
	m_btnClrBoundUX.Color	= m_ViewOptions.BoundsColor[3];
	m_btnClrBoundUY.Color	= m_ViewOptions.BoundsColor[4];
	m_btnClrBoundUZ.Color	= m_ViewOptions.BoundsColor[5];

	m_btnClrWall.Color		= m_ViewOptions.WallColor;
	m_btnClrSlab.Color		= m_ViewOptions.SlabColor;
	m_btnClrColumn.Color	= m_ViewOptions.ColumnColor;
	m_btnClrBeam.Color		= m_ViewOptions.BeamColor;
	m_btnClrRoof.Color		= m_ViewOptions.RoofColor;
	if (!m_bShowLanguage)
	{
		GetDlgItem(IDC_STATIC_LANGUAGE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LANGUAGES)->ShowWindow(SW_HIDE);
	}
	int nItemPos = m_Languages.AddString( _T("English") );
	m_Languages.SetItemData( nItemPos, 1033 );
	if( m_nLangID == 1033 )
		m_Languages.SetCurSel( nItemPos );
	nItemPos = m_Languages.AddString( _T("Русский") );
	m_Languages.SetItemData( nItemPos, 1049 );
	if( m_nLangID == 1049 )
		m_Languages.SetCurSel( nItemPos );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
