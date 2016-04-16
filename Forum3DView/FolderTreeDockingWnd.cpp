// Stingray Objective Toolkit
// Component Gallery generated file
// FolderTreeDockingWnd.cpp : implementation file
//

#include "stdafx.h"
#include "FolderTreeDockingWnd.h"
//#include "MainScadViewerFrame.h"
#include "SCAD3DMdlSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFolderTreeDockingWnd

CFolderTreeDockingWnd::CFolderTreeDockingWnd()
{
}

CFolderTreeDockingWnd::~CFolderTreeDockingWnd()
{
}


BEGIN_MESSAGE_MAP(CFolderTreeDockingWnd, CDockablePane)
	//{{AFX_MSG_MAP(CFolderTreeDockingWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_EMBEDDED_CONTROL, OnSelChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFolderTreeDockingWnd message handlers

int CFolderTreeDockingWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a tree control
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	//DWORD dwStyleEx = //TVXS_MULTISEL |
	//				  TVXS_FLYBYTOOLTIPS |
	//				  LVXS_HILIGHTSUBITEMS;

	BOOL bCreated = m_childWnd.Create( dwViewStyle, //dwStyleEx, 
						rectDummy, 
						this,
						IDC_EMBEDDED_CONTROL);

	ASSERT(bCreated);
	// add a client edge
	m_childWnd.ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	

	//m_childWnd.SetTopFolder( CSIDL_DESKTOP, TRUE );
	//m_childWnd.SetCurFolder("c:\\", FALSE);

	return 0;
}

void CFolderTreeDockingWnd::OnSize(UINT nType, int cx, int cy) 
{
	CDockablePane::OnSize(nType, cx, cy);
	
	if( m_childWnd.GetSafeHwnd() != nullptr )
	{
		CRect r;
		GetClientRect(&r);

		m_childWnd.SetWindowPos(nullptr, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER|SWP_NOACTIVATE );
	}
}






// ReSharper disable once CppMemberFunctionMayBeConst
void CFolderTreeDockingWnd::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//LPNMTREEVIEW pNMTV = LPNMTREEVIEW(pNMHDR);
		
//	TRACE(_T("Tree selection changed to hti: %0x\n"), pNMTV->itemNew.hItem);
	CString strFolder;
	m_childWnd.GetItemPath(strFolder); 
	TRACE(_T("Path: %s\n"), strFolder);
//	reinterpret_cast<CMainScadViewerFrame *>(AfxGetApp()->m_pMainWnd)->SetCurViewFolder( m_childWnd.GetCurFolderPath() );
	CSCAD3DMdlSettings::Get3DS()->SetCurViewFolder( strFolder );
	*pResult = 0;
}



