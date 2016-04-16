// MainScadViewerFrame.cpp : implementation file
//
// Copyright (C) 2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "MainScadViewerFrame.h"
#include "ScadViewerView.h"
#include "ScadViewerDoc.h"
#include "ViewerOptions.h"
#include "OptionsGeneral.h"
#include "OptionsMaterial.h"
#include "OptionsRtf.h"
#include "SettingManager.h"
#include "shlwapi.h"
#include <tchar.h>
#include <io.h>
#include "ResultsDlg.h"
#include "IsoViewerFrame.h"
#include "SCAD3DMdlSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainScadViewerFrame

IMPLEMENT_DYNCREATE(CMainScadViewerFrame, CIsoViewerFrame)

CMainScadViewerFrame::CMainScadViewerFrame()
{
	CSettingManager sm;
	int nLangID;
	sm.SetKey(_T(""));
	sm.UpdateInt(true, _T("LangId"), &nLangID, 1049);
	LoadLanguage(nLangID);
}

CMainScadViewerFrame::~CMainScadViewerFrame()
{
}


BEGIN_MESSAGE_MAP(CMainScadViewerFrame, CIsoViewerFrame)
	//{{AFX_MSG_MAP(CMainScadViewerFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_THUMBNAIL, OnViewThumbnail )
	ON_UPDATE_COMMAND_UI(ID_VIEW_THUMBNAIL, OnUpdateViewThumbnail )
	ON_COMMAND(ID_VIEW_LARGE_ICON, OnViewLargeIcon )
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGE_ICON, OnUpdateViewLargeIcon )
	ON_COMMAND(ID_VIEW_SMALL_ICON, OnViewSmallIcon )
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALL_ICON, OnUpdateViewSmallIcon )
	ON_COMMAND(ID_VIEW_LIST, OnViewList )
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList )
	ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails )
	ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, OnUpdateViewDetails )
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_SCAD_VIEW_DBLCLICK, OnScadViewDblclick)
	ON_COMMAND(ID_VIEW_FOLDER_TREE, OnViewFolderTree)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FOLDER_TREE, OnUpdateViewFolderTree)
	ON_COMMAND(ID_VIEW_FOLDER_VIEW, OnViewFolderView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FOLDER_VIEW, OnUpdateViewFolderView)
	ON_COMMAND(ID_FILE_DELETE, OnFileDelete)
	ON_COMMAND(ID_TREE_EXPLORER, OnTreeExplorer)
	ON_UPDATE_COMMAND_UI(ID_FILE_CALCRES_DELETE, OnUpdateFileCalcresDelete)
	ON_COMMAND(ID_FILE_CALCRES_DELETE, OnFileCalcresDelete)
	ON_COMMAND(ID_FILE_CALCRES_SEL_DELETE, OnFileCalcresSelDelete)
	ON_COMMAND(ID_MENU_VIEW_REFRESH, OnMenuViewRefresh)
	ON_UPDATE_COMMAND_UI(ID_FILE_CALCRES_SEL_DELETE, OnUpdateFileCalcresDelete)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESULTS, OnUpdateViewResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainScadViewerFrame message handlers

int CMainScadViewerFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CIsoViewerFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CScadViewerView * p3DView = m_p3DView;//(CScadViewerView*)GetWindow( GW_CHILD );

	if (!CSCAD3DMdlSettings::Get3DS())
		return 0;
	CSCAD3DMdlSettings::Get3DS()->SetFileView( p3DView );
	
	// Objective Toolkit component gallery block: Dockable window
	{
		//DWORD dwStyle = WS_CHILD|WS_VISIBLE|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC;
		//DWORD dwStyleEx = CBRS_EX_COOL|CBRS_EX_BORDERSPACE;
		UINT nID = 100;
		CString strCaption;
		strCaption.LoadString(IDS_FOLDER_TREE_CAPTION);
		//CRect rc;
		if (!m_FolderTreeDockingWnd.Create(strCaption, this, CSize(200,200), TRUE, nID))
		{
			TRACE(_T("Failed to create docking window"));
			return -1;
		}
		m_FolderTreeDockingWnd.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_TOP|CBRS_ALIGN_RIGHT|CBRS_ALIGN_BOTTOM);

		DockPane(&m_FolderTreeDockingWnd, AFX_IDW_DOCKBAR_LEFT);
		//m_FolderTreeDockingWnd.m_childWnd.SetCurFolder("C:\\", TRUE);
		
	} // end block
	{
		//DWORD dwStyle = WS_CHILD|WS_VISIBLE| WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC;
		//DWORD dwStyleEx = CBRS_EX_COOL | CBRS_EX_BORDERSPACE;
		UINT nID = 101;
		CString strCaption;
		strCaption.LoadString(IDS_FOLDER_CAPTION);
		//CRect rc;
		if (!m_FolderWnd.Create( strCaption, this, CSize(200,200), TRUE, nID))
		{
			TRACE(_T("Failed to create docking window"));
			return -1;
		}
		m_FolderWnd.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_TOP|CBRS_ALIGN_RIGHT|CBRS_ALIGN_BOTTOM);

		DockPane(&m_FolderWnd, AFX_IDW_DOCKBAR_BOTTOM);
		
	} // end block
	CString strPath;
	LPTSTR pszPath = strPath.GetBuffer(_MAX_PATH);
	::GetModuleFileName(AfxGetApp()->m_hInstance, pszPath, _MAX_PATH);
	_tcsrchr(pszPath, _T('\\'))[1]=0;
	strPath.ReleaseBuffer();

	::GetPrivateProfileString(
		_T("DIRECTORIES"),
		_T("Output"),
		_T("C:\\SWORK\\"),
		m_strWorkDir.GetBuffer(_MAX_PATH),
		_MAX_PATH,
		strPath+_T("Scad.ini")
	);
	m_strWorkDir.ReleaseBuffer();
	SetToolBarNames();

	return 0;
}

BOOL CMainScadViewerFrame::SetCurViewFolder( const TCHAR * sFolderPath )
{
	if( _tcscmp( m_FolderTreeDockingWnd.m_childWnd.GetCurFolderPath(), sFolderPath ) != 0 )
		m_FolderTreeDockingWnd.m_childWnd.SetCurFolder( sFolderPath );
	m_FolderWnd.m_childWnd.SetCurFolder( sFolderPath );

	return TRUE;
}


void CMainScadViewerFrame::OnViewThumbnail()
{
	m_FolderWnd.m_childWnd.SetViewType( flvtThumbnail );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnUpdateViewThumbnail(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio( m_FolderWnd.m_childWnd.GetViewType() == flvtThumbnail );
}

void CMainScadViewerFrame::OnViewLargeIcon()
{
	m_FolderWnd.m_childWnd.SetViewType( flvtLargeIcon );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnUpdateViewLargeIcon(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio( m_FolderWnd.m_childWnd.GetViewType() == flvtLargeIcon );
}

void CMainScadViewerFrame::OnViewSmallIcon()
{
	m_FolderWnd.m_childWnd.SetViewType( flvtSmallIcon );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnUpdateViewSmallIcon(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio( m_FolderWnd.m_childWnd.GetViewType() == flvtSmallIcon );
}

void CMainScadViewerFrame::OnViewList()
{
	m_FolderWnd.m_childWnd.SetViewType( flvtList );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnUpdateViewList(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio( m_FolderWnd.m_childWnd.GetViewType() == flvtList );
}

void CMainScadViewerFrame::OnViewDetails()
{
	m_FolderWnd.m_childWnd.SetViewType( flvtDetails );
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnUpdateViewDetails(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio( m_FolderWnd.m_childWnd.GetViewType() == flvtDetails );
}

void CMainScadViewerFrame::OnToolsOptions() 
{
	CString strCaption;
	strCaption.LoadString(IDS_OPTIONS_DLG_NAME);
	CViewerOptions OptionsDlg(strCaption);
	COptionsGeneral		PageGeneral(m_ViewerOptions);
	CPersistViewOptions theOpt(m_p3DView->m_ViewOptions);
	COptionsMaterial	PageMaterial(theOpt);
	COptionsRtf			PageRtf(m_p3DView->m_DrawOptions);
	
	OptionsDlg.AddPage(&PageGeneral);
	OptionsDlg.AddPage(&PageMaterial);
	OptionsDlg.SetActivePage(1);
	OptionsDlg.AddPage(&PageRtf);


	if (OptionsDlg.DoModal()!=IDOK)
		return;
	extern int nLangID;
	// ReSharper disable once CppLocalVariableMightNotBeInitialized
	if (nLangID != m_ViewerOptions.nLangID)
	{
		LoadLanguage(m_ViewerOptions.nLangID);
		if (m_Menu.GetSafeHmenu())
			m_Menu.DestroyMenu();
		m_Menu.LoadMenu(IDR_MAINFRAME);
		m_wndMenuBar.CreateFromMenu(m_Menu.GetSafeHmenu());
		
		// Remove and destroy the old menu
		//SetMenu(nullptr);
		//::DestroyMenu(m_hMenuDefault);

		//// Add the new menu
		//SetMenu(&m_Menu);

		// Assign default menu
		m_hMenuDefault = m_Menu.GetSafeHmenu();  // or m_NewMenu.m_hMenu;
		SetToolBarNames();
		m_FolderWnd.m_childWnd.SetColumnName();
	}
	//RecalcLayout();
	//m_pMenuBar->ResetMenus();
	m_p3DView->OnOptionsChanged(PageMaterial.m_ViewOptions);
	if (m_FolderWnd.m_childWnd.GetSafeHwnd())
		m_FolderWnd.m_childWnd.SetViewProp(m_ViewerOptions.m_ViewProp);
	
}


BOOL CMainScadViewerFrame::UpdateSettings(bool bLoad)
{
	CIsoViewerFrame::UpdateSettings(bLoad);
	
	if (!CSCAD3DMdlSettings::Get3DS())
		return TRUE;

	m_ViewerOptions.UpdateSettings(bLoad, _T(""));
	if (bLoad)
	{
		m_FolderWnd.m_childWnd.SetViewProp(m_ViewerOptions.m_ViewProp);
	}
	m_FolderWnd.UpdateSettings(bLoad);
	return TRUE;
}


void CMainScadViewerFrame::ActivateFrame(int nCmdShow)
{
	bool bFirstActivate = m_bFirstActivate;
	CIsoViewerFrame::ActivateFrame(nCmdShow);
	if (!CSCAD3DMdlSettings::Get3DS())
		return;
	if (bFirstActivate)
	{
		if ( !((m_FolderWnd.GetStyle() | m_FolderTreeDockingWnd.GetStyle()) & WS_VISIBLE))
		{
			// Show tree & folder
			m_FolderTreeDockingWnd.ShowWindow(SW_SHOW);
			m_FolderWnd.ShowWindow(SW_SHOW);
		}
	}
};



void CMainScadViewerFrame::OnViewInFolder(LPCTSTR pszPath)
{
	m_FolderWnd.AddRecentDir(pszPath);
}

void CMainScadViewerFrame::OnScadViewDblclick()
{
	if (!m_FolderWnd.GetSafeHwnd() || !m_FolderTreeDockingWnd.GetSafeHwnd())
		return;
	if ( (m_FolderWnd.GetStyle() | m_FolderTreeDockingWnd.GetStyle()) & WS_VISIBLE)
	{
		// Hide tree & folder
		ShowPane(&m_FolderTreeDockingWnd, FALSE, FALSE, FALSE);
		ShowPane(&m_FolderWnd, FALSE, FALSE, FALSE);
	}
	else
	{
		// Show tree & folder
		ShowPane(&m_FolderTreeDockingWnd, TRUE, FALSE, FALSE);
		ShowPane(&m_FolderWnd, TRUE, FALSE, FALSE);
	}

}

void CMainScadViewerFrame::OnViewFolderTree() 
{
	m_FolderTreeDockingWnd.ShowWindow(( m_FolderTreeDockingWnd.GetStyle() & WS_VISIBLE ) == 0 ? SW_SHOW : SW_HIDE);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnUpdateViewFolderTree(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_FolderTreeDockingWnd.GetStyle() & WS_VISIBLE ? 1 : 0 );
}

void CMainScadViewerFrame::OnViewFolderView() 
{
	m_FolderWnd.ShowWindow(( m_FolderWnd.GetStyle() & WS_VISIBLE ) == 0 ? SW_SHOW : SW_HIDE);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnUpdateViewFolderView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_FolderWnd.GetStyle() & WS_VISIBLE ? 1 : 0 );
}

void CMainScadViewerFrame::SetToolBarNames()
{
	CIsoViewerFrame::SetToolBarNames();
	CString strCaption;
	strCaption.LoadString(IDS_FOLDER_TREE_CAPTION);
	m_FolderTreeDockingWnd.SetWindowText(strCaption);
	strCaption.LoadString(IDS_FOLDER_CAPTION);
	m_FolderWnd.SetWindowText(strCaption);
}

BOOL CMainScadViewerFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	
	return CIsoViewerFrame::OnNotify(wParam, lParam, pResult);
}

void CMainScadViewerFrame::OnFileDelete() 
{
	ASSERT(m_p3DView);
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	if (pDoc)
	{
		CString strFileName = pDoc->GetPathName();
		if (!strFileName.IsEmpty())
		{
			SHFILEOPSTRUCT sfos;
			ZeroMemory(&sfos, sizeof(sfos));
			sfos.hwnd = GetSafeHwnd();
			LPTSTR szFileName = strFileName.GetBuffer(strFileName.GetLength()+2);
			szFileName[strFileName.GetLength()+1]=0;
			sfos.pFrom = szFileName;
			sfos.wFunc = FO_DELETE;
			int nResult =::SHFileOperation(&sfos);
			strFileName.ReleaseBuffer();
			if (nResult == 0 && !sfos.fAnyOperationsAborted)
			{
				m_FolderWnd.m_childWnd.DeleteItem(strFileName);
			}
		}
	}

	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMainScadViewerFrame::OnTreeExplorer() 
{
	::ShellExecute
		(
			m_hWnd,
			_T("explore"),
			m_FolderTreeDockingWnd.m_childWnd.GetCurFolderPath(),
			nullptr,
			nullptr,//FolderTreeForm->FPath.c_str(),
			SW_SHOWNORMAL
		);
	
}

void CMainScadViewerFrame::OnUpdateFileCalcresDelete(CCmdUI* pCmdUI) 
{
	CString strMask = GetSelWorkFileMask();
	struct _tfinddata_t fd;
	long hFindHandle = _tfindfirst( strMask, &fd );
	pCmdUI->Enable(hFindHandle!=-1);
	_findclose(hFindHandle);
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
CString CMainScadViewerFrame::GetSelWorkFileMask()
{
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	CString strFileName = pDoc->GetPathName();
	if (strFileName.IsEmpty())
		return strFileName;
	strFileName = PathFindFileName(strFileName);

	PathRemoveExtension(strFileName.GetBuffer(_MAX_PATH));
	strFileName.ReleaseBuffer();
	strFileName+=_T(".*");
	return m_strWorkDir+strFileName;
}

void CMainScadViewerFrame::OnFileCalcresDelete() 
{
	CString strMask = GetSelWorkFileMask();
	struct _tfinddata_t fd;
	long hFindHandle = _tfindfirst( strMask, &fd );
	if (hFindHandle==-1)
		return;
	do
	{
		::DeleteFile(m_strWorkDir+fd.name);
	} while (_tfindnext(hFindHandle, &fd) != -1);
	_findclose(hFindHandle);
}

void CMainScadViewerFrame::OnFileCalcresSelDelete() 
{
	CResultsDlg dlg(GetSelWorkFileMask());
	dlg.DoModal();
}

void CMainScadViewerFrame::OnMenuViewRefresh() 
{
	m_FolderWnd.m_childWnd.Refresh();
}


void CMainScadViewerFrame::OnUpdateViewResults(CCmdUI* pCmdUI) 
{
	CString strMask = GetSelWorkFileMask();
	struct _tfinddata_t fd;
	long hFindHandle = _tfindfirst( strMask, &fd );
	pCmdUI->Enable(hFindHandle!=-1);
	_findclose(hFindHandle);
	CScadViewerDoc *pDoc = m_p3DView->GetDocument();
	pCmdUI->SetCheck(pDoc->m_bViewResults);
	
}

