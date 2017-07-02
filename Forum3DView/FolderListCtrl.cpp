// FolderListCtrl.cpp : implementation file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "../ForumView_ENG/resource.h"
#include "FileProc.h"
#include "FolderListCtrl.h"
#include <algorithm>
#include "SCAD3DMdlSettings.h"
#include "ScadViewerFrm.h"
#include <tchar.h>
#include <io.h>
#include "Timer.h"

CTimer Timer;
//#define SHOW_FILL_TIME

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFLCProperties

int	CFLCProperties::operator==( const CFLCProperties& prop ) const
{
	if( m_nItemCX != prop.m_nItemCX )
		return 0;
	if( m_nItemCY != prop.m_nItemCY )
		return 0;
	if( m_DefProj != prop.m_DefProj )
		return 0;
	if( m_vsExt.size() != prop.m_vsExt.size() )
		return 0;

	SCStringVector::const_iterator it = m_vsExt.begin();
	SCStringVector::const_iterator itprop = prop.m_vsExt.begin();

	for( ; it != m_vsExt.end(); ++it, ++itprop )
		if( std::find( prop.m_vsExt.begin(), prop.m_vsExt.end(), *it ) == prop.m_vsExt.end() )
			return 0;

	return 1;
}

CFLCProperties CFLCProperties::operator=( const CFLCProperties& prop )
{
	m_nItemCX = prop.m_nItemCX;
	m_nItemCY = prop.m_nItemCY;
	m_DefProj = prop.m_DefProj;
	m_vsExt.clear();
	m_vsExt.insert( m_vsExt.begin(), prop.m_vsExt.begin(), prop.m_vsExt.end() );

	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// CFolderListCtrl

DWORD CFolderListCtrl::m_ListStyles[flvtSize] = 
{
	LVS_ICON,		//flvtThumbnail
	LVS_ICON,		//flvtLargeIcon
	LVS_SMALLICON,	//flvtSmallIcon
	LVS_LIST,		//flvtList,
	LVS_REPORT		//flvtDetails,
};

CFolderListCtrl::FLColumnInfo CFolderListCtrl::m_flciColumns[CFolderListCtrl::flcSize] =
{
	{ IDS_FL_COLUMN_NAME, CFolderListCtrl::CmpByName, HDF_LEFT | HDF_BITMAP_ON_RIGHT },
	{ IDS_FL_COLUMN_SIZE, CFolderListCtrl::CmpBySize, HDF_RIGHT | HDF_BITMAP_ON_RIGHT },
	{ IDS_FL_COLUMN_TIME, CFolderListCtrl::CmpByModified, HDF_RIGHT | HDF_BITMAP_ON_RIGHT },
};

CFolderListCtrl::CFolderListCtrl()
{
	m_pimlThumbnails = nullptr;
	m_Properties.m_nItemCX = 70;
	m_Properties.m_nItemCY = 80;
	m_Properties.m_DefProj = DPT_SouthWest;
	m_Properties.m_vsExt.push_back( "*.tns" );
	m_Properties.m_vsExt.push_back( "*.cns" );
	m_Properties.m_vsExt.push_back( "*.sec" );
	m_Properties.m_vsExt.push_back( "*.spr" );
	m_Properties.m_vsExt.push_back( "*.opr" );

	m_nItemCount = 0;
	m_nImageBalance = 0;
	m_nTopItemForSizeChanging = -1;
	m_nSelectedItem = -1;
	m_flvtViewType = flvtLargeIcon;
	m_nCurColumn = flcName;
	m_bSortAscending = FALSE;
}

CFolderListCtrl::~CFolderListCtrl()
{
	delete m_pimlThumbnails;
}


BEGIN_MESSAGE_MAP(CFolderListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CFolderListCtrl)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_MESSAGE( FPTM_SEND_FILE_BMP, OnSendFileBmp )
	ON_WM_WINDOWPOSCHANGING()
	ON_NOTIFY( HDN_ITEMCLICKW, FLC_HEADER_ID, OnItemclick)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnSelChanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_MESSAGE( WM_DIRCHANGE, OnDirChange)
	ON_NOTIFY( HDN_ITEMCLICKA, FLC_HEADER_ID, OnItemclick)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFolderListCtrl message handlers

void CFolderListCtrl::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	if( m_nImageBalance > 0 )
	{
		LVFINDINFO lvfi;

		lvfi.flags = LVFI_NEARESTXY;
		lvfi.pt.x = 0;
		lvfi.pt.y = 0;
		lvfi.vkDirection = VK_NEXT; 
		m_nTopItemForSizeChanging = FindItem( &lvfi );
	}

	CListCtrl::OnWindowPosChanging(lpwndpos);
}

void CFolderListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	if( m_nImageBalance > 0 && m_nTopItemForSizeChanging >= 0 )
	{
		LVFINDINFO lvfi;

		CListCtrl::OnSize(nType, cx, cy);

		lvfi.flags = LVFI_NEARESTXY;
		lvfi.pt.x = 0;
		lvfi.pt.y = 0;
		lvfi.vkDirection = VK_NEXT; 
		int nTopPosNew = FindItem( &lvfi );
		if( nTopPosNew != m_nTopItemForSizeChanging )
			SetRedrawItemPos( nTopPosNew );
	}
	else
		CListCtrl::OnSize(nType, cx, cy);
}

void CFolderListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( m_nImageBalance > 0 )
	{
		LVFINDINFO lvfi;

		lvfi.flags = LVFI_NEARESTXY;
		lvfi.pt.x = 0;
		lvfi.pt.y = 0;
		lvfi.vkDirection = VK_NEXT; 
		int nTopPosOld = FindItem( &lvfi );

		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

		lvfi.pt.x = 0;
		lvfi.pt.y = 0;
		int nTopPosNew = FindItem( &lvfi );
		if( nTopPosNew != nTopPosOld )
			SetRedrawItemPos( nTopPosNew );
	}
	else
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

int CFolderListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_imlLargeIcons.Create( 32, 32, ILC_COLOR, 8, 8 );
	m_imlSmallIcons.Create( 16, 16, ILC_COLOR, 8, 8 );
	m_imlHeader.Create( 16, 16, ILC_MASK, 2, 2 );

	SetImageList( &m_imlLargeIcons, LVSIL_NORMAL );
	SetImageList( &m_imlSmallIcons, LVSIL_SMALL );

	InsertColumn( 0, _T(""), LVCFMT_LEFT, 100, 0 );
	InsertColumn( 1, _T(""), LVCFMT_RIGHT, 100, 1 );
	InsertColumn( 2, _T(""), LVCFMT_RIGHT, 100, 2 );
	SetColumnName();
	SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );
	ModifyStyle(0, LVS_SHOWSELALWAYS);
	SetViewType( flvtThumbnail );

	CBitmap bmpUPArrow;
	CBitmap bmpDNArrow;

	bmpUPArrow.LoadBitmap( IDB_UPARROW );
	bmpDNArrow.LoadBitmap( IDB_DNARROW );

	m_imlHeader.Add( &bmpDNArrow, RGB( 0, 0, 0 ) );
	m_imlHeader.Add( &bmpUPArrow, RGB( 0, 0, 0 ) );

	GetHeaderCtrl()->SetDlgCtrlID( FLC_HEADER_ID );
	GetHeaderCtrl()->SetImageList( &m_imlHeader );
	SetSortType( m_nCurColumn, TRUE );

	
	return 0;
}

void CFolderListCtrl::OnDestroy() 
{
	DeleteAllItemsData();
	CListCtrl::OnDestroy();
}

void CFolderListCtrl::CreateImageList()
{
	CImageList * pImgList = new CImageList;

	pImgList->Create( m_Properties.m_nItemCX, m_Properties.m_nItemCY, ILC_COLOR, 32, 32 );

	CDC * pdcThis = GetDC();
	CDC dcBmp; 
	CBitmap bmpRes;

	dcBmp.CreateCompatibleDC( pdcThis );
	bmpRes.CreateCompatibleBitmap( pdcThis, m_Properties.m_nItemCX, m_Properties.m_nItemCY );

	CBitmap * pbmpOld = static_cast<CBitmap*>(dcBmp.SelectObject( &bmpRes ));
	CRect r( 0, 0, m_Properties.m_nItemCX, m_Properties.m_nItemCY );
	LOGBRUSH lbBackground;

	ReleaseDC( pdcThis );
	lbBackground.lbColor = RGB( 255, 255, 255 );
	lbBackground.lbHatch = 0;
	lbBackground.lbStyle = BS_SOLID;
	
	CBrush brBackground;
	
	brBackground.CreateBrushIndirect( &lbBackground );

	dcBmp.FillRect( r, &brBackground );
	dcBmp.Rectangle( r );
	dcBmp.MoveTo( 0, 0 );
	dcBmp.LineTo( m_Properties.m_nItemCX, m_Properties.m_nItemCY );
	dcBmp.MoveTo( m_Properties.m_nItemCX, 0 );
	dcBmp.LineTo( 0, m_Properties.m_nItemCY );
	dcBmp.SelectObject( pbmpOld );
	dcBmp.DeleteDC();

	if( m_pimlThumbnails )
	{
		for( int i = m_pimlThumbnails->GetImageCount() - 1; i >= 0; i-- )
			m_pimlThumbnails->Remove( i );
		delete m_pimlThumbnails;
	}
	pImgList->Add( &bmpRes, RGB( 0, 0, 0 ) );
	m_pimlThumbnails = pImgList;
	if( m_flvtViewType == flvtThumbnail )
		SetImageList( pImgList, LVSIL_NORMAL );
}

LRESULT CFolderListCtrl::OnSendFileBmp( WPARAM wParam, LPARAM lParam )
{
	FPTFileBmp * pImgInfo = reinterpret_cast<FPTFileBmp*>(lParam);
	LVFINDINFO lvFI;
	int nItem;

	if( !pImgInfo )
		return 0;

	lvFI.flags = LVFI_PARAM;
	lvFI.lParam = pImgInfo->m_nItemID;
	nItem = FindItem( &lvFI );

	if( nItem != -1 )
	{
		CFLCItemData * pData = reinterpret_cast<CFLCItemData*>(GetItemData( nItem ));

		if( !pData->m_bProcessed && pData->m_sFilePath == pImgInfo->m_sFilePath )
		{
			if( pImgInfo->m_nRetCode == FDE_OK && m_pimlThumbnails )
			{
				CBitmap bmp;

				bmp.Attach( pImgInfo->m_hBmp );

				int nPos = m_pimlThumbnails->Add( &bmp, RGB( 0, 0, 0 ) );

				bmp.Detach();
				
				if( nPos >= 0 )
				{
					pData->m_bProcessed = true;
					pData->m_nThumbnailInd = nPos;
					if( m_flvtViewType == flvtThumbnail )
						SetValidItemImage( nItem );
				}
			}
			pData->m_bProcessed = true;
			m_nImageBalance--;

			if( AfxGetMainWnd() )
				static_cast<CScadViewerFrame*>(AfxGetMainWnd())->GetStatusBar().IncFilePos();
		}
	}

	if( pImgInfo->m_hBmp )
		::DeleteObject( pImgInfo->m_hBmp );
	delete pImgInfo;
#ifdef SHOW_FILL_TIME
	if (m_nImageBalance==0)
	{
		CSCADViewerStatBar &theStatusBar = ((CScadViewerFrame*)AfxGetMainWnd())->GetStatusBar();
		theStatusBar.SetGenInfo(Timer.StopStr());

	}
#endif
	return 1;
}



BOOL CFolderListCtrl::SetCurFolder( const CSCADString& sFolderPath, bool bForce)
{
	if( !bForce && !m_sFolderPath.CompareNoCase( sFolderPath ) )
		return TRUE;
	Timer.Start();
	m_DirChangeListener.SetDir(sFolderPath, m_hWnd);
/*
	SCDefProjInfo proj_info;

	SCADDefProj::GetInfo( m_Properties.m_DefProj, proj_info );
	SCMdl3DSetCameraPos( proj_info.m_ptViewDir, proj_info.m_ptUpOrient );
*/
	// ReSharper disable once CppEntityAssignedButNoRead
	extern SCDefProjType ThumbProjection;
	ThumbProjection = m_Properties.m_DefProj;
	if(CSCAD3DMdlSettings::Get3DS())
	{
		CSCAD3DMdlSettings::Get3DS()->CancelDraw();
		CSCAD3DMdlSettings::Get3DS()->SetStartDrawPos( 0 );
	}

	CreateImageList();
	DeleteAllItemsData();
	DeleteAllItems();
	m_sFolderPath = sFolderPath;
	m_nItemCount = 0;
	m_nImageBalance = 0;
	m_nSelectedItem = -1;
	SetSelectionMark( 0 );
	
	int i;

	for( i = m_imlLargeIcons.GetImageCount() - 1; i >= 0; i-- )
		m_imlLargeIcons.Remove( i );
	for( i = m_imlSmallIcons.GetImageCount() - 1; i >= 0; i-- )
		m_imlSmallIcons.Remove( i );

	if( _taccess( sFolderPath, 0 ) == -1 )
		return TRUE;

	SCStringVector::iterator itExt = m_Properties.m_vsExt.begin();
	CSCADString sPath;

	struct _tfinddata_t fd;

	int nLargeIconInd = 0;
	int nSmallIconInd = 0;

	for( ; itExt != m_Properties.m_vsExt.end(); ++itExt )
	{
		sPath = m_sFolderPath + _T("\\") + *itExt;

		intptr_t hFindHandle = _tfindfirst( sPath, &fd );

		if( hFindHandle == -1 )
			continue;

		AddFileTypeIcons(fd, nLargeIconInd, nSmallIconInd);

		do
		{
			AddFileItem(fd, nLargeIconInd, nSmallIconInd, *itExt);
		} while( _tfindnext( hFindHandle, &fd ) != -1 );
		_findclose( hFindHandle );
	}
	SortItems( m_flciColumns[m_nCurColumn].m_fnCmp, m_bSortAscending );
	m_nImageBalance = m_nItemCount;
	SetRedrawItemPos( 0, true );
	if( AfxGetMainWnd() )
	{
		CSCADViewerStatBar &theStatusBar = static_cast<CScadViewerFrame*>(AfxGetMainWnd())->GetStatusBar();
		theStatusBar.SetFileCount( m_nItemCount );
	}
	UpdateFileCount();		

	return TRUE;
}

BOOL CFolderListCtrl::SetViewProp( const CFLCProperties& prop )
{
	if( prop == m_Properties )
		return TRUE;

	CSCADString sPath = m_sFolderPath;

	m_Properties = prop;
	m_sFolderPath.Empty();
	SetIconSpacing(m_Properties.m_nItemCX + 10, m_Properties.m_nItemCY+40);

	return SetCurFolder( sPath );
}

BOOL CFolderListCtrl::SetRedrawItemPos( int nPos, bool bInit/* = false*/ )
{
	if (CSCAD3DMdlSettings::Get3DS())
		CSCAD3DMdlSettings::Get3DS()->SetStartDrawPos( nPos );


	if( !bInit )
		return TRUE;

	CFLCItemData * pData;
	FPTDrawFileInfo * pDFI;
	const FPTExtFuncInfo * pFuncInfo=nullptr;
	int i;

	for( i = nPos; i < m_nItemCount; i++ )
	{
		pData = reinterpret_cast<CFLCItemData*>(GetItemData( i ));
		if( pData && !pData->m_bProcessed )
		{
			if (CSCAD3DMdlSettings::Get3DS())
					pFuncInfo = CSCAD3DMdlSettings::Get3DS()->GetExtFuncInfo( pData->m_sExt );
			if( pFuncInfo )
			{
				pDFI = new FPTDrawFileInfo;
				pDFI->m_pProcInfo = pFuncInfo;
				pDFI->m_hwndReciever = m_hWnd;
				pDFI->m_nItemID = intptr_t(pData);
				pDFI->m_sFilePath = pData->m_sFilePath;
				pDFI->m_nBmpCX = m_Properties.m_nItemCX;
				pDFI->m_nBmpCY = m_Properties.m_nItemCY;
				CSCAD3DMdlSettings::Get3DS()->DrawFile( i, pDFI );
			}
		}
	}
	for( i = nPos - 1; i >= 0; i-- )
	{
		pData = reinterpret_cast<CFLCItemData*>(GetItemData( i ));
		if( pData && !pData->m_bProcessed )
		{
			if (CSCAD3DMdlSettings::Get3DS())
				pFuncInfo = CSCAD3DMdlSettings::Get3DS()->GetExtFuncInfo( pData->m_sExt );
			if( pFuncInfo )
			{
				pDFI = new FPTDrawFileInfo;
				pDFI->m_pProcInfo = pFuncInfo;
				pDFI->m_hwndReciever = m_hWnd;
				pDFI->m_nItemID = intptr_t(pData);
				pDFI->m_sFilePath = pData->m_sFilePath;
				pDFI->m_nBmpCX = m_Properties.m_nItemCX;
				pDFI->m_nBmpCY = m_Properties.m_nItemCY;
				CSCAD3DMdlSettings::Get3DS()->DrawFile( i, pDFI );
			}
		}
	}

	return TRUE;
}

void CFolderListCtrl::DeleteAllItemsData()
{
	CFLCItemData * pData;

	for( int i = 0; i < m_nItemCount; i++ )
	{
		pData = reinterpret_cast<CFLCItemData*>(GetItemData( i ));
		delete pData;
		SetItemData( i, 0 );
	}
}

void CFolderListCtrl::ClearImageList()
{
	CImageList * pImgList = GetImageList( LVSIL_NORMAL );

	if( pImgList )
		for( int i = pImgList->GetImageCount() - 1; i > 0; i-- )
			pImgList->Remove( i );
}

FLViewType CFolderListCtrl::GetViewType() const
{
	return m_flvtViewType;
}

BOOL CFolderListCtrl::SetViewType( FLViewType vt )
{
	if( vt == m_flvtViewType )
		return TRUE;

	if( m_ListStyles[m_flvtViewType] != m_ListStyles[vt] )
		if( !ModifyStyle( m_ListStyles[m_flvtViewType], m_ListStyles[vt], SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER ) )
			return FALSE;
	switch( vt )
	{
		case flvtThumbnail:
			SetImageList( m_pimlThumbnails, LVSIL_NORMAL );
			break;
		case flvtLargeIcon:
			SetImageList( &m_imlLargeIcons, LVSIL_NORMAL );
			break;
	case flvtSmallIcon: break;
	case flvtList: break;
	case flvtDetails: break;
	case flvtSize: break;
	default: break;
	}
	m_flvtViewType = vt;

	for( int i = GetItemCount() - 1; i >= 0; i-- )
		SetValidItemImage( i );
	SortItems( m_flciColumns[m_nCurColumn].m_fnCmp, m_bSortAscending );
	Arrange( LVA_DEFAULT );

	return TRUE;
}

BOOL CFolderListCtrl::SetValidItemImage( int nItem )
{
	CFLCItemData * pData = reinterpret_cast<CFLCItemData*>(GetItemData( nItem ));
	LVITEM lvi;

	if( !pData )
		return FALSE;

	lvi.mask = LVIF_IMAGE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	switch( m_flvtViewType )
	{
		case flvtThumbnail:
			lvi.iImage = pData->m_nThumbnailInd;
			break;
		case flvtLargeIcon:
			lvi.iImage = pData->m_nLargeIconInd;
			break;
		default:
			lvi.iImage = pData->m_nSmallIconInd;
			break;
	}
	SetItem( &lvi );

	return TRUE;
}

BOOL CFolderListCtrl::SetColumnName()
{
	LVCOLUMN lvc;
	CSCADString	sColHeader;

	lvc.mask = LVCF_TEXT;

	for( int i = flcName; i < flcSize; i++ )
	{
		sColHeader.LoadString( m_flciColumns[i].m_idStr );
		lvc.pszText = sColHeader.GetBuffer( 0 );
		SetColumn( i, &lvc );
	}

	m_sModifiedFormat.LoadString( IDS_FL_MODIFIED_FORMAT );
	UpdateFileCount();
	return TRUE;
}

CString	SizeToStr( _fsize_t fsz )
{
	CSCADString sRes;
	CSCADString sNum;
	_fsize_t prec = fsz % 1024;

	if( prec )
	{
		prec = int(fsz % 1024 * 1000. / 1024.);
		if( prec < 10 )
			sRes = _T(",01 KB");
		else
			sRes.Format( _T(",%02d KB"), prec / 10 );

	}
	else
		sRes = _T(" KB");

	fsz = fsz / 1024;
	sNum.Format( _T("%d"), fsz );
	for( int i = sNum.GetLength() - 1, j = 0; i >= 0; i--, j++ )
	{
		if( j && !( j % 3 ) )
			sRes = _T(" ") + sRes;
		sRes = sNum[i] + sRes;
	}

	return sRes;
}

CSCADString CFolderListCtrl::TimeToStr( time_t ftm ) const
{
	CTime ctm( ftm );

	return ctm.Format( m_sModifiedFormat );
}

int CALLBACK CFolderListCtrl::CmpByName( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
	CFLCItemData * pData1 = reinterpret_cast<CFLCItemData*>(lParam1);
	CFLCItemData * pData2 = reinterpret_cast<CFLCItemData*>(lParam2);
	CSCADString	str1( pData1 ? pData1->m_sFilePath : _T("") );
	CSCADString	str2( pData2 ? pData2->m_sFilePath : _T("") );
	
	return lParamSort ? str1.CompareNoCase( str2 ) : str2.CompareNoCase( str1 );
}

int CALLBACK CFolderListCtrl::CmpBySize( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
	CFLCItemData * pData1 = reinterpret_cast<CFLCItemData*>(lParam1);
	CFLCItemData * pData2 = reinterpret_cast<CFLCItemData*>(lParam2);
	_fsize_t sz1 = pData1 ? pData1->m_nSize : 0;
	_fsize_t sz2 = pData2 ? pData2->m_nSize : 0;
	int nRes = sz1 == sz2 ? 0 : ( sz1 < sz2 ? -1 : 1 );

	return lParamSort ? nRes : ( nRes * -1 );
}

int CALLBACK CFolderListCtrl::CmpByModified( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
	CFLCItemData * pData1 = reinterpret_cast<CFLCItemData*>(lParam1);
	CFLCItemData * pData2 = reinterpret_cast<CFLCItemData*>(lParam2);
	time_t tm1 = pData1 ? pData1->m_tModified : 0;
	time_t tm2 = pData2 ? pData2->m_tModified : 0;
	int nRes = tm1 == tm2 ? 0 : ( tm1 < tm2 ? -1 : 1 );

	return lParamSort ? nRes : ( nRes * -1 );
}

void CFolderListCtrl::OnItemclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = reinterpret_cast<HD_NOTIFY *>(pNMHDR);

	if( phdn->iItem >= flcName && phdn->iItem < flcSize )
		SetSortType( phdn->iItem, ( phdn->iItem == m_nCurColumn ? !m_bSortAscending : TRUE ) );	

	*pResult = 0;
}

BOOL CFolderListCtrl::SetSortType( int nCol, BOOL bAsc )
{
	if( nCol < flcName || nCol >= flcSize )
		return FALSE;

	HDITEM curItem;
	curItem.mask = 0;
	CHeaderCtrl* pHdrCtrl= GetHeaderCtrl();

	if( nCol != m_nCurColumn )
	{
		pHdrCtrl->GetItem( m_nCurColumn, &curItem );
		curItem.mask= HDI_FORMAT;
		curItem.fmt= m_flciColumns[m_nCurColumn].m_nHdrFormat | HDF_STRING;
		pHdrCtrl->SetItem( m_nCurColumn, &curItem);
		m_nCurColumn = nCol;
	}
	m_bSortAscending = bAsc;
	pHdrCtrl->GetItem( m_nCurColumn, &curItem );
	curItem.mask= HDI_IMAGE | HDI_FORMAT;
	curItem.iImage = bAsc ? 1 : 0;
	curItem.fmt= m_flciColumns[m_nCurColumn].m_nHdrFormat | HDF_IMAGE | HDF_STRING;
	pHdrCtrl->SetItem( m_nCurColumn, &curItem);
	SortItems( m_flciColumns[m_nCurColumn].m_fnCmp, m_bSortAscending );

	return TRUE;
}

void CFolderListCtrl::OnRButtonUp(UINT nFlags, CPoint point ) 
{
	CListCtrl::OnRButtonUp(nFlags, point);
	CMenu m_ListPopup;
	m_ListPopup.LoadMenu( IDR_FOLDER_LIST );

	CMenu * pListMenu = m_ListPopup.GetSubMenu( 0 )->GetSubMenu( 0 );
	pListMenu->SetDefaultItem(ID_FILE_EDIT);
	ClientToScreen( &point );
	pListMenu->TrackPopupMenu( TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd() );
}

void CFolderListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CListCtrl::OnRButtonDown(nFlags, point);

	POSITION selPos = GetFirstSelectedItemPosition();
	int nItemPos = -1;

	if( selPos )
		nItemPos = GetNextSelectedItem( selPos );
	if( nItemPos >= 0 )
	{
		SetSelectionMark( nItemPos );

		CMenu m_ListPopup;
		m_ListPopup.LoadMenu( IDR_FOLDER_LIST );
		CMenu * pListMenu = m_ListPopup.GetSubMenu( 0 );
		pListMenu->SetDefaultItem(ID_FILE_EDIT);
		ClientToScreen( &point );
		pListMenu->TrackPopupMenu( TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd() );
	}
}

void CFolderListCtrl::OnSelChanged( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLISTVIEW * pNM = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	if( pNM && ( pNM->uNewState & LVIS_SELECTED ) && pNM->iItem != -1 && pNM->iItem != m_nSelectedItem )
	{
		CFLCItemData * pData = reinterpret_cast<CFLCItemData*>(GetItemData( pNM->iItem ));
		if (!pData)
			return;
		m_strSelectedPath = pData->m_sFilePath;
		CSCAD3DMdlSettings::Get3DS()->SetViewFilePath( pData->m_sFilePath, pData->m_sExt );
		m_nSelectedItem = pNM->iItem;
	}
	else if ((pNM->uNewState & LVIS_SELECTED )==0)
	{
		m_nSelectedItem = -1;
	}
}



// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CFolderListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	AfxGetMainWnd()->SendMessage(WM_COMMAND,ID_FILE_EDIT);
	
	*pResult = 0;
}



void CFolderListCtrl::DeleteItem(CString &strFileName)
{
	CFLCItemData * pData;

	for( int i = 0; i < m_nItemCount; i++ )
	{
		pData = reinterpret_cast<CFLCItemData*>(GetItemData( i ));
		if (pData->m_sFilePath == strFileName)
		{
			delete pData;
			CListCtrl::DeleteItem(i);
			m_nItemCount--;
			break;
		}
	}

}

LRESULT CFolderListCtrl::OnDirChange( WPARAM wParam, LPARAM lParam )
{
	RefreshFileList();
	return 0;
}

void CFolderListCtrl::AddFileTypeIcons(const struct _tfinddata_t &fd, int &nLargeIconInd, int &nSmallIconInd)
{
	CSCADString sFileName;
	
	if( m_sFolderPath.GetLength() && 
		( m_sFolderPath[m_sFolderPath.GetLength()-1] == _T('\\') ||
		m_sFolderPath[m_sFolderPath.GetLength()-1] == _T('/') ) )
		sFileName = m_sFolderPath+ fd.name;
	else
		sFileName = m_sFolderPath + (  _T("\\") ) + fd.name;
	SHFILEINFO shFI;
	if( SHGetFileInfo( sFileName, 0, &shFI, sizeof( shFI ), SHGFI_ICON | SHGFI_LARGEICON | SHGFI_LINKOVERLAY ) != 0 )
	{
		nLargeIconInd = m_imlLargeIcons.Add( shFI.hIcon );
		::DestroyIcon( shFI.hIcon );
	}
	if( SHGetFileInfo( sFileName, 0, &shFI, sizeof( shFI ), SHGFI_ICON | SHGFI_SMALLICON | SHGFI_LINKOVERLAY ) != 0 )
	{
		nSmallIconInd = m_imlSmallIcons.Add( shFI.hIcon );
		::DestroyIcon( shFI.hIcon );
	}
	

}

void CFolderListCtrl::AddFileItem(const _tfinddata_t &fd, int nLargeIconInd, int nSmallIconInd, CString &strExt)
{
	CString sFileName;
	int nItemPos;
	if( m_sFolderPath.GetLength() && 
		( m_sFolderPath[m_sFolderPath.GetLength()-1] == _T('\\') ||
		  m_sFolderPath[m_sFolderPath.GetLength()-1] == _T('/') ) )
		sFileName = m_sFolderPath+ fd.name;
	else
		sFileName = m_sFolderPath + (  _T("\\") ) + fd.name;
	
	CFLCItemData * pData;
	pData = new CFLCItemData( sFileName, strExt );
	pData->m_nSize = fd.size;
	pData->m_tModified = fd.time_write;
	pData->m_nLargeIconInd = nLargeIconInd;
	pData->m_nSmallIconInd = nSmallIconInd;

	nItemPos = InsertItem( m_nItemCount, fd.name, FLC_IMAGE_EMPTY );
	SetItemData( nItemPos, DWORD_PTR(pData) );
	SetItemText( nItemPos, 1, SizeToStr( pData->m_nSize ) );
	SetItemText( nItemPos, 2, TimeToStr( pData->m_tModified ) );
	SetValidItemImage( nItemPos );
	m_nItemCount++;
	if (m_strSelectedPath.CompareNoCase(sFileName)==0)
	{
		SetItemState(nItemPos, LVIS_SELECTED, LVIS_SELECTED);
	}
}

void CFolderListCtrl::RefreshFileList()
{
	std::vector<CFLCItemData *>arrListCache(m_nItemCount);
	int i;
	for (i=0;i<m_nItemCount;i++)
	{
		arrListCache[i] = reinterpret_cast<CFLCItemData *>(GetItemData(i));
		arrListCache[i]->m_bFoundOnRefresh = false;
	}

	SCStringVector::iterator itExt = m_Properties.m_vsExt.begin();
	CSCADString sPath;

	struct _tfinddata_t fd;

	int nLargeIconInd = 0;
	int nSmallIconInd = 0;
	int nItemCount = m_nItemCount;

	for( ; itExt != m_Properties.m_vsExt.end(); ++itExt )
	{
		sPath = m_sFolderPath + _T("\\") + *itExt;

		intptr_t hFindHandle = _tfindfirst( sPath, &fd );

		if( hFindHandle == -1 )
			continue;
		AddFileTypeIcons(fd, nLargeIconInd, nSmallIconInd);
		do
		{
			bool bFileFound = false;
			CSCADString sFileName;
			
			if( m_sFolderPath.GetLength() && 
				( m_sFolderPath[m_sFolderPath.GetLength()-1] == _T('\\') ||
				m_sFolderPath[m_sFolderPath.GetLength()-1] == _T('/') ) )
				sFileName = m_sFolderPath+ fd.name;
			else
				sFileName = m_sFolderPath + (  _T("\\") ) + fd.name;
			for (int k=0; k<nItemCount;k++)
			{
				if (arrListCache[k]->m_sFilePath == sFileName)
				{
					bFileFound = true;
					arrListCache[k]->m_bFoundOnRefresh = true;
					if (fd.time_write != arrListCache[k]->m_tModified)
					{
						arrListCache[k]->m_bProcessed = false;
						if (m_strSelectedPath.CompareNoCase(arrListCache[k]->m_sFilePath)==0)
						{
							CSCAD3DMdlSettings::Get3DS()->SetViewFilePath( arrListCache[k]->m_sFilePath, arrListCache[k]->m_sExt );
						}
						break;
					}
				}
			}
			if (!bFileFound)
			{
				AddFileItem(fd, nLargeIconInd, nSmallIconInd,*itExt);
			}
		} while( _tfindnext( hFindHandle, &fd ) != -1 );
		_findclose( hFindHandle );
	}
	m_nImageBalance = 0;
	for (i=0;i<m_nItemCount;i++)
	{
		CFLCItemData *pData = reinterpret_cast<CFLCItemData *>(GetItemData(i));
		if (!pData->m_bFoundOnRefresh)
		{
			delete pData;
			CListCtrl::DeleteItem(i);
			m_nItemCount--;
		}
		else
		{
			if (!pData->m_bProcessed)
				m_nImageBalance++;
		}

	}

	SortItems( m_flciColumns[m_nCurColumn].m_fnCmp, m_bSortAscending );

	ASSERT(m_nItemCount == GetItemCount());
	UpdateFileCount();
	SetRedrawItemPos( 0, true );

}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CFolderListCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CFolderListCtrl::UpdateFileCount()
{
	if( AfxGetMainWnd() )
	{
		CSCADViewerStatBar &theStatusBar = static_cast<CScadViewerFrame*>(AfxGetMainWnd())->GetStatusBar();
		CString strFileCount;
		strFileCount.Format(IDS_FILE_COUNT_FORMAT,m_nItemCount);
		theStatusBar.SetGenInfo(strFileCount);
	}

}

#include "ThumbCashe.h"


void CFolderListCtrl::Refresh()
{
	CThumbCashe cashe(m_sFolderPath);
	cashe.Delete();
	SetCurFolder(m_sFolderPath, TRUE);
}
