// OptionsGeneral.cpp : implementation file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "SCADDefProj.h"
#include "OptionsGeneral.h"
#include <algorithm>
#include "SCAD3DMdlSettings.h"


// COptionsGeneral dialog

IMPLEMENT_DYNAMIC(COptionsGeneral, CPropertyPage)
COptionsGeneral::COptionsGeneral(SViewerOptions	&rViewerOptions)
	: CPropertyPage(COptionsGeneral::IDD),
	m_rViewerOptions(rViewerOptions), m_fAspect(0),
	m_bManualThumbChange(true)	
{
	m_bSyncChangeThumbSize = FALSE;
	m_LockBmp.LoadBitmap( IDB_THUMB_SIZE_SYNC );
	m_nLangID = m_rViewerOptions.nLangID;
	m_nThumbnailWidth = m_rViewerOptions.m_ViewProp.m_nItemCX;
	m_nThumbnailHeight = m_rViewerOptions.m_ViewProp.m_nItemCY;
	m_WhiteBrush.CreateSolidBrush(RGB(255,255,255));
}

COptionsGeneral::~COptionsGeneral()
{
}

void COptionsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsGeneral)
		DDX_Control( pDX, IDC_LANGUAGES, m_Languages );
		DDX_Control( pDX, IDC_FILE_TYPES_LIST, m_FileTypeList );
		DDX_Control( pDX, IDC_DEF_PROJ_LIST, m_DefProjList );
		DDX_Control( pDX, IDC_WIDTH_SLIDER, m_ThumbWidthSlider );
		DDX_Control( pDX, IDC_HEIGHT_SLIDER, m_ThumbHeightSlider );
		DDX_Text( pDX, IDC_WIDTH_EDIT, m_nThumbnailWidth );
		DDV_MinMaxLong( pDX, m_nThumbnailWidth, 0, 400 );
		DDX_Text( pDX, IDC_HEIGHT_EDIT, m_nThumbnailHeight );
		DDV_MinMaxLong( pDX, m_nThumbnailHeight, 0, 400 );
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	if( pDX->m_bSaveAndValidate )
	{
/*
		int nSelCount = m_FileTypeList.GetSelCount();
		
		m_ViewProperty.m_vsExt.clear();
		if( nSelCount )
		{
			int * pSel = (int*)_alloca( sizeof( int ) * nSelCount );
			const FPTExtFuncInfo * pEFI;
			int nDefProj;

			m_FileTypeList.GetSelItems( nSelCount, pSel );
			for( int i = 0; i < nSelCount; i++ )
			{
				pEFI = (FPTExtFuncInfo*)m_FileTypeList.GetItemData( pSel[i] );
				if( pEFI )
					m_ViewProperty.m_vsExt.push_back( pEFI->m_sExt );
			}
			nDefProj = m_DefProjList.GetCurSel();
			if( nDefProj >= 0 && nDefProj < DPT_Size )
				nDefProj = (int)m_DefProjList.GetItemData( nDefProj );
			else
				nDefProj = DPT_SouthWest;
			m_ViewProperty.m_DefProj = (SCDefProjType)nDefProj;
		}
*/

		if( m_Languages.GetCurSel() >= 0 )
			m_nLangID = int(m_Languages.GetItemData( m_Languages.GetCurSel()));
	}
}


BEGIN_MESSAGE_MAP(COptionsGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsGeneral)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND( IDC_SIZE_PROP, OnSizeProp )
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// COptionsGeneral message handlers
BOOL COptionsGeneral::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateThumbnail();
	size_t nDFI = CSCAD3DMdlSettings::Get3DS() ? CSCAD3DMdlSettings::Get3DS()->GetEFISize() : 0;
	int nItemPos;
	const FPTExtFuncInfo * pEFI;
	UINT i;
	CRect r;

	m_ViewProperty = m_rViewerOptions.m_ViewProp;
	for( i = 0; i < nDFI; i++ )
	{
		pEFI = CSCAD3DMdlSettings::Get3DS()->GetEFIAt( i );
		nItemPos = m_FileTypeList.AddString( pEFI->m_sDescript );
		m_FileTypeList.SetItemData( nItemPos, DWORD_PTR(pEFI) );
		if( std::find( m_ViewProperty.m_vsExt.begin(), m_ViewProperty.m_vsExt.end(), pEFI->m_sExt ) != m_ViewProperty.m_vsExt.end() )
			m_FileTypeList.SetSel( nItemPos, TRUE );
	}

	for( i = 0; i < SCADDefProj::GetDefProjSize(); i++ )
	{
		nItemPos = m_DefProjList.AddString( SCADDefProj::GetDesc( SCDefProjType(i) ) );
		m_DefProjList.SetItemData( nItemPos, DWORD(i) );
		if( m_ViewProperty.m_DefProj == int(i) )
			m_DefProjList.SetCurSel( nItemPos );
	}
	//m_ViewProperty.m_DefProj = m_rViewerOptions.nDefaultView;
	m_ThumbWidthSlider.GetClientRect( &r );
	m_ThumbWidthSlider.SetRange( 10, r.Width() );
	m_ThumbWidthSlider.SetTicFreq( 10 );
	m_ThumbWidthSlider.SetPos( m_ViewProperty.m_nItemCX);
	m_ThumbHeightSlider.GetClientRect( &r );
	m_ThumbHeightSlider.SetRange( 10, r.Height() );
	m_ThumbHeightSlider.SetTicFreq( 10 );
	m_ThumbHeightSlider.SetPos( m_ViewProperty.m_nItemCY);

	static_cast<CButton*>(GetDlgItem( IDC_SIZE_PROP ))->SetBitmap( m_LockBmp );
	static_cast<CButton*>(GetDlgItem( IDC_SIZE_PROP ))->SetCheck( m_bSyncChangeThumbSize ? BST_CHECKED : BST_UNCHECKED );

	nItemPos = m_Languages.AddString( _T("English") );
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

void COptionsGeneral::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if( !pScrollBar || !m_bManualThumbChange)
		return;
	
	CSliderCtrl * pSlider = reinterpret_cast<CSliderCtrl*>( pScrollBar );
	
	if( pSlider && pSlider->GetDlgCtrlID() == IDC_WIDTH_SLIDER )
	{
		int pos = pSlider->GetPos();

		if( m_nThumbnailWidth != pos )
		{
			if( m_bSyncChangeThumbSize )
			{
				int nNewHeight = int(pos/m_fAspect);
				int nMaxHeight, nMinHeight;
				
				m_ThumbHeightSlider.GetRange( nMinHeight, nMaxHeight );
				if( nNewHeight < nMinHeight || nNewHeight > nMaxHeight )
				{
					MessageBeep( MB_ICONEXCLAMATION );
					pSlider->SetPos( m_nThumbnailWidth);
				}
				else
				{
					CSCADString str;

					m_nThumbnailWidth = pos;
					m_nThumbnailHeight = nNewHeight;
					m_bManualThumbChange = false;
					m_ThumbHeightSlider.SetPos( m_nThumbnailHeight);
					m_bManualThumbChange = true;
					str.Format( _T("%d"), m_nThumbnailWidth );
					GetDlgItem( IDC_WIDTH_EDIT )->SetWindowText( str );
					str.Format( _T("%d"), m_nThumbnailHeight );
					GetDlgItem( IDC_HEIGHT_EDIT )->SetWindowText( str );
				}
			}
			else
			{
				CSCADString str;

				str.Format( _T("%d"), pos );
				GetDlgItem( IDC_WIDTH_EDIT )->SetWindowText( str );
				m_nThumbnailWidth = pos;
			}
			UpdateThumbnail();

		}
	}
}

void COptionsGeneral::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);

	if( !pScrollBar || !m_bManualThumbChange)
		return;
	
	CSliderCtrl * pSlider = reinterpret_cast<CSliderCtrl*>( pScrollBar );
	
	if( pSlider && pSlider->GetDlgCtrlID() == IDC_HEIGHT_SLIDER )
	{
		int n_pos = pSlider->GetPos();
		CSCADString str;
		if( m_nThumbnailWidth != n_pos )
		{
			if( m_bSyncChangeThumbSize )
			{
				int nNewWidth = int(n_pos * m_fAspect);
				int nMaxWidth, nMinWidth;
				
				m_ThumbWidthSlider.GetRange( nMinWidth, nMaxWidth);
				if( nNewWidth < nMinWidth || nNewWidth > nMaxWidth )
				{
					MessageBeep( MB_ICONEXCLAMATION );
					pSlider->SetPos( m_nThumbnailHeight);
				}
				else
				{
					CSCADString str1;

					m_nThumbnailHeight = n_pos;
					m_nThumbnailWidth = nNewWidth;
					m_bManualThumbChange = false;
					m_ThumbWidthSlider.SetPos( m_nThumbnailWidth);
					m_bManualThumbChange = true;
					str1.Format( _T("%d"), m_nThumbnailWidth );
					GetDlgItem( IDC_WIDTH_EDIT )->SetWindowText( str1 );
					str1.Format( _T("%d"), m_nThumbnailHeight );
					GetDlgItem( IDC_HEIGHT_EDIT )->SetWindowText( str1 );
				}
			}
			else
			{
				m_nThumbnailHeight = n_pos;
				str.Format( _T("%d"), n_pos );
				GetDlgItem( IDC_HEIGHT_EDIT )->SetWindowText( str );
			}
			UpdateThumbnail();
		}
	}
}

void COptionsGeneral::OnSizeProp()
{
	m_bSyncChangeThumbSize = static_cast<CButton*>(GetDlgItem( IDC_SIZE_PROP ))->GetCheck() == BST_CHECKED;
	if (m_bSyncChangeThumbSize)
		m_fAspect = float(m_nThumbnailWidth)/m_nThumbnailHeight;
}

HBRUSH COptionsGeneral::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_THUMBNAIL)
	{
		hbr = m_WhiteBrush;
	}
	return hbr;
}




void COptionsGeneral::UpdateThumbnail() const
{
	CRect r;
	GetDlgItem(IDC_THUMBNAIL_VIEW)->GetWindowRect(&r);
	ScreenToClient(&r);
	CPoint ptCenter = r.CenterPoint();
	r.left = ptCenter.x - m_nThumbnailWidth/2;
	r.right = r.left + m_nThumbnailWidth;
	r.top = ptCenter.y - m_nThumbnailHeight/2;
	r.bottom = r.top + m_nThumbnailHeight;
	GetDlgItem(IDC_THUMBNAIL)->MoveWindow(&r);
}

void COptionsGeneral::OnOK()
{
	m_ViewProperty.m_nItemCX = m_nThumbnailWidth;
	m_ViewProperty.m_nItemCY = m_nThumbnailHeight;
	m_ViewProperty.m_DefProj = SCDefProjType(m_DefProjList.GetCurSel());
	int nSelected = m_FileTypeList.GetSelCount();
	std::vector<int> parrSelected(nSelected);
	m_FileTypeList.GetSelItems(nSelected, &parrSelected[0]);
	m_ViewProperty.m_vsExt.clear();
	for (int i=0; i<nSelected; i++)
		m_ViewProperty.m_vsExt.push_back( CSCAD3DMdlSettings::Get3DS()->GetEFIAt(parrSelected[i])->m_sExt);
	m_rViewerOptions.m_ViewProp = m_ViewProperty;
	m_rViewerOptions.nLangID = m_nLangID;

}
