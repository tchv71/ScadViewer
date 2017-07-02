// Stingray Objective Toolkit
// dockwnd.cpp : implementation file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "DockFolderWnd.h"
#include "SCAD3DMdlSettings.h"
#include "../ForumView_ENG/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockFolderWnd

FORUM3DVIEW_EXPORT CDockFolderWnd::CDockFolderWnd(): m_nCbHeight(0)
{
}

FORUM3DVIEW_EXPORT CDockFolderWnd::~CDockFolderWnd()
{
}


BEGIN_MESSAGE_MAP(CDockFolderWnd, CDockablePane)
	//{{AFX_MSG_MAP(CDockFolderWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_CBN_SELENDOK(IDC_RECENT_COMBO, OnSelectRecentDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockFolderWnd message handlers

FORUM3DVIEW_EXPORT int CDockFolderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD dwStyle = LVS_ICON |
					LVS_AUTOARRANGE |
					LVS_SINGLESEL |
					WS_CHILD | WS_VISIBLE;

	BOOL bCreated = m_childWnd.Create( dwStyle, 
						CRect(0, 0, 0, 0), 
						this,
						IDC_EMBEDDED_VIEW);
	
	ASSERT(bCreated);
	m_RecentComboWnd.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, CRect(0,0,CW_USEDEFAULT,0), this, IDC_RECENT_COMBO);
	m_RecentComboWnd.SetFont(CFont::FromHandle(HFONT(::GetStockObject(DEFAULT_GUI_FONT))));

	CRect rcCombo;
	m_RecentComboWnd.GetClientRect(&rcCombo);
	m_nCbHeight = rcCombo.Height();
	
	// add a client edge
	m_childWnd.ModifyStyleEx( 0, WS_EX_CLIENTEDGE , SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		
	return 0;
}

void CDockFolderWnd::OnSize(UINT nType, int cx, int cy) 
{
	CDockablePane::OnSize(nType, cx, cy);
	
	if( m_childWnd.GetSafeHwnd() != nullptr )
	{
		CRect r;
		GetClientRect(&r);
		m_RecentComboWnd.SetWindowPos(nullptr, r.left, r.top, r.Width(),200, SWP_NOZORDER);
		m_childWnd.SetWindowPos(nullptr, r.left, r.top+m_nCbHeight+5, r.Width(), r.Height() - m_nCbHeight - 5, SWP_NOZORDER|SWP_NOACTIVATE );
	}
}



BOOL CDockFolderWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect rcClient;
	GetClientRect(rcClient);
	CBrush backBrush(GetSysColor(COLOR_BTNFACE));
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);

	pDC->PatBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	
	return CDockablePane::OnEraseBkgnd(pDC);
}

void CDockFolderWnd::FillCombo()
{
	m_RecentComboWnd.ResetContent();
	for (UINT i=0; i<m_VecRecentDirs.size(); i++)
	{
		m_RecentComboWnd.AddString(m_VecRecentDirs[i]);
	}
	m_RecentComboWnd.SetCurSel(0);
}


void CDockFolderWnd::AddRecentDir(const CString &sDir)
{
	const int c_nRecentDirSize = 10;
	if (m_VecRecentDirs.size() !=0 && _tcsicmp(sDir, m_VecRecentDirs[0])==0)
		return;
	for (UINT i=1; i<m_VecRecentDirs.size(); i++)
		if (_tcsicmp(sDir, m_VecRecentDirs[i])==0)
		{
			m_VecRecentDirs.erase(m_VecRecentDirs.begin()+i);
			break;
		}
	m_VecRecentDirs.insert(m_VecRecentDirs.begin(), sDir);
	if (m_VecRecentDirs.size() > c_nRecentDirSize)
		m_VecRecentDirs.resize(c_nRecentDirSize);
	FillCombo();
}


void CDockFolderWnd::OnSelectRecentDir()
{
	CString strDir = m_VecRecentDirs[m_RecentComboWnd.GetCurSel()];
	AddRecentDir(strDir);
	if (CSCAD3DMdlSettings::Get3DS())
		CSCAD3DMdlSettings::Get3DS()->SetCurViewFolder(strDir);
}

void CDockFolderWnd::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{}

BOOL CDockFolderWnd::UpdateSettings(bool bLoad)
{
	SetKey(_T(""));
	UpdateStringVector(bLoad, _T("RecentDirs"), &m_VecRecentDirs, _T(""));
	FillCombo();
	if (m_VecRecentDirs.size()>0 && CSCAD3DMdlSettings::Get3DS())
		CSCAD3DMdlSettings::Get3DS()->SetCurViewFolder(m_VecRecentDirs[0]);
	return TRUE;
}
