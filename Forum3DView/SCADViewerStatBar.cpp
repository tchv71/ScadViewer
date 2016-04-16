// SCADViewerStatBar.cpp : implementation file
//
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "SCADViewerStatBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_IND_FILE_COUNT	1024
#define ID_IND_FILE_INFO	1025

/*
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
*/

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_IND_FILE_COUNT,
	ID_IND_FILE_INFO,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL
};

/////////////////////////////////////////////////////////////////////////////
// CSCADViewerStatBar

CSCADViewerStatBar::CSCADViewerStatBar(): m_Progress(0), m_nFiles(0)
{
}

CSCADViewerStatBar::~CSCADViewerStatBar()
{
}


BEGIN_MESSAGE_MAP(CSCADViewerStatBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CSCADViewerStatBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI ( ID_IND_FILE_COUNT, OnUpdatePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCADViewerStatBar message handlers

int CSCADViewerStatBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMFCStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetIndicators( indicators, sizeof(indicators)/sizeof(UINT) );
	SetPaneWidth( 0, 200 );
	SetPaneWidth( 1, 100 );
	SetPaneWidth( 2, 100 );
	
	//CRect r( 0, 0, 100, 20 );
	
	
	return 0;
}

void CSCADViewerStatBar::OnSize(UINT nType, int cx, int cy) 
{
	CMFCStatusBar::OnSize(nType, cx, cy);

	int nPane0Width = cx/3;
	int nPane1Width = cx/8;
	SetPaneWidth( 0, nPane0Width);
	SetPaneWidth( 1, nPane1Width );
	SetPaneWidth( 2, cx-nPane0Width-nPane1Width-200);
	
	//CRect r= GetPaneRect( 1, &r );
	//m_Progress.SetWindowPos( NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER );
}

void CSCADViewerStatBar::SetGenInfo( const TCHAR * sInfoText )
{
	SetPaneText( 1, sInfoText );
}

void CSCADViewerStatBar::SetFileCount( UINT nFiles )
{
	if( nFiles )
	{
		//m_Progress.ShowWindow( SW_SHOW );
		EnablePaneProgressBar(1, nFiles, TRUE);
		SetPaneProgress(1, 0);
		m_Progress=0;
		m_nFiles = nFiles;
	}
	else
	{
		EnablePaneProgressBar(1, -1);
		//SetPaneText( 1, "" );
	}
}

void CSCADViewerStatBar::IncFilePos()
{
	UINT dwPos = m_Progress++;
	//int nLow, nUp;
	
	if (dwPos<UINT(m_nFiles))
		SetPaneProgress(1, dwPos);
	if( dwPos >= UINT(m_nFiles)-1)
		EnablePaneProgressBar(1, -1);
	//{
	//	TCHAR sBuf[128];

	//	//m_Progress.ShowWindow( SW_HIDE );
	//	sprintf( sBuf, "%d", nUp );

	//	//SetPaneText( 1, sBuf );
	//}
}

void CSCADViewerStatBar::BreakDrawFile()
{
	//int nLow, nUp;
	//TCHAR sBuf[128];

	SetPaneProgress(1, -1);
	//sprintf( sBuf, "%d", nUp );

	//SetPaneText( 1, sBuf );
}

void CSCADViewerStatBar::SetFileInfo( const TCHAR * sFileInfo )
{
	SetPaneText( 2, sFileInfo );
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CSCADViewerStatBar::OnUpdatePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();

}
