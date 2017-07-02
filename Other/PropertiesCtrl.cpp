// CPropertiesCtrl.cpp : implementation file
//
// Copyright (C) 2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "ForumView_ENG/resource.h"
//#include "SCAD3DMdlSettings.h"
#include "PropertiesCtrl.h"
#include <shlwapi.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesCtrl

CPropertiesCtrl::CPropertiesCtrl()
{
	m_piMalloc = NULL;
}

CPropertiesCtrl::~CPropertiesCtrl()
{
}


BEGIN_MESSAGE_MAP(CPropertiesCtrl, SECTreeCtrl)
	//{{AFX_MSG_MAP(CPropertiesCtrl)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesCtrl message handlers

//DEL BOOL CPropertiesCtrl::SetTopFolder( int idFolder, BOOL bExpand/* = FALSE*/ )
//DEL {
//DEL 	DelItemRecursive( GetRootItem() );
//DEL 
//DEL 	CComPtr<IShellFolder> piDesktop;
//DEL 	CComPtr<IShellFolder> piFolder;
//DEL 	BOOL bRes = FALSE;
//DEL 
//DEL 	SHGetDesktopFolder( &piDesktop );
//DEL 
//DEL 	ITEMIDLIST * pItem = NULL;
//DEL 	HRESULT hr = SHGetSpecialFolderLocation( NULL, idFolder, &pItem );
//DEL 	_STRRET strret;
//DEL 	IExtractIcon * piEI = NULL;
//DEL 	CSCADString sName, sFolderPath;
//DEL 
//DEL 	hr = piDesktop->GetDisplayNameOf( pItem, SHGDN_NORMAL, &strret );
//DEL 	sName = StrRetToStr(pItem, strret, true, m_piMalloc );
//DEL 	hr = piDesktop->GetDisplayNameOf( pItem, SHGDN_NORMAL | SHGDN_FORPARSING, &strret );
//DEL 	sFolderPath = StrRetToStr(pItem, strret, true, m_piMalloc );
//DEL 	hr = piDesktop->GetUIObjectOf( NULL, 1, (LPCITEMIDLIST*)&pItem, IID_IExtractIcon, NULL, (void**)&piEI );
//DEL 	if( idFolder != CSIDL_DESKTOP )
//DEL 		hr = piDesktop->BindToObject( pItem, NULL, IID_IShellFolder, (void**)&piFolder );
//DEL 	else
//DEL 		piFolder = piDesktop;
//DEL 
//DEL 
//DEL 	if( piFolder )
//DEL 		bRes = InsertFolder( pItem, piFolder, piEI, sName, sFolderPath, TVI_ROOT, TVI_LAST, true ) != NULL;
//DEL 
//DEL 	if( piEI )
//DEL 		piEI->Release();
//DEL 
//DEL 	return bRes;
//DEL }

//DEL BOOL CPropertiesCtrl::SetTopFolder( const TCHAR * sPathFolder, BOOL bExpand/* = FALSE*/ )
//DEL {
//DEL 	if( !sPathFolder || !*sPathFolder )
//DEL 		return FALSE;
//DEL 
//DEL 	DelItemRecursive( GetRootItem() );
//DEL 
//DEL 	CSCADString sName;
//DEL 	ITEMIDLIST * pItem = NULL; 
//DEL 	CComPtr<IExtractIcon> piEI;
//DEL 	IShellFolder * piFld = GetFolderByPath( NULL, sPathFolder, &pItem, sName, &piEI );
//DEL 	CComPtr<IShellFolder> piFolder = piFld;
//DEL 	
//DEL 	if( piFolder )
//DEL 	{
//DEL 		piFld->Release();
//DEL 		InsertFolder( pItem, piFolder, piEI, sName, sPathFolder, TVI_ROOT, TVI_LAST, true );
//DEL 	}
//DEL 
//DEL 	return piFolder != NULL;
//DEL }

//DEL BOOL CPropertiesCtrl::SetCurFolder( const TCHAR * sPathFolder, BOOL bExpand/* = FALSE*/ )
//DEL {
//DEL 	if( !sPathFolder || !*sPathFolder )
//DEL 		return FALSE;
//DEL 
//DEL 	HTREEITEM hRoot = GetRootItem();
//DEL 	CFTCItemData * pItemData = (CFTCItemData*)GetItemData( hRoot );
//DEL 
//DEL 	if( !pItemData )
//DEL 		return FALSE;
//DEL 
//DEL 	IShellFolder * piRoot = pItemData->m_piFolder;
//DEL 
//DEL 	if( !piRoot )
//DEL 		return FALSE;
//DEL 
//DEL 	ITEMIDLIST * pCurIDL = GetPIDLByPath( piRoot, sPathFolder );
//DEL 	CSCADString sNormPath;
//DEL 	_STRRET strret;
//DEL 
//DEL 	piRoot->GetDisplayNameOf( pCurIDL, SHGDN_NORMAL | SHGDN_FORPARSING, &strret );
//DEL 	sNormPath = StrRetToStr(pCurIDL, strret, true, m_piMalloc );
//DEL 
//DEL 	HTREEITEM hItem = OpenFolder( hRoot, pCurIDL, sPathFolder );
//DEL 
//DEL 	if( !pCurIDL )
//DEL 		m_piMalloc->Free( pCurIDL );
//DEL 	if( hItem ) 
//DEL 	{
//DEL 		Select( hItem, TVGN_CARET );
//DEL 		if( bExpand && !IsExpanded( hItem ) )
//DEL 			Expand( hItem, TVE_EXPAND );
//DEL 	}
//DEL 	
//DEL 	return hItem ? TRUE : FALSE;
//DEL }

//DEL HTREEITEM CPropertiesCtrl::OpenFolder( HTREEITEM hItem, ITEMIDLIST * pidl, const TCHAR * sPathFolder )
//DEL {
//DEL 	if( !hItem )
//DEL 		return NULL;
//DEL 	if( pidl && !pidl->mkid.cb )
//DEL 		return hItem;
//DEL 
//DEL 	if( !IsExpanded( hItem ) )
//DEL 		Expand( hItem, TVE_EXPAND );
//DEL 
//DEL 	HTREEITEM hChildItem = GetNextItem( hItem, TVGN_CHILD );
//DEL 	CFTCItemData * pItemData;
//DEL 	FTCFolderCmpRes fcrRes;
//DEL 
//DEL 	for( ; hChildItem; hChildItem = GetNextItem( hChildItem, TVGN_NEXT ) )
//DEL 	{
//DEL 		pItemData = (CFTCItemData*)GetItemData( hChildItem );
//DEL 		if( !pItemData )
//DEL 			continue;
//DEL 		if( pidl && EqualRelativePIDLs( pidl, pItemData->m_pIDL ) )
//DEL 			return OpenFolder( hChildItem, (ITEMIDLIST*)( ((BYTE*)pidl ) + pidl->mkid.cb ), sPathFolder );
//DEL 		fcrRes = CmpPath( pItemData->m_sPath, sPathFolder );
//DEL 		if( fcrRes == fcrSubDir )
//DEL 		{
//DEL 			pidl = pidl ? (ITEMIDLIST*)( ((BYTE*)pidl ) + pidl->mkid.cb ) : pidl;
//DEL 
//DEL 			return OpenFolder( hChildItem, pidl, sPathFolder );
//DEL 		}
//DEL 		if( fcrRes == fcrEqual )
//DEL 			return hChildItem;
//DEL 	}
//DEL 
//DEL 	return NULL;
//DEL }

//DEL HTREEITEM CPropertiesCtrl::InsertFolder( ITEMIDLIST * pidl, IShellFolder * piFolder, IExtractIcon * piIcon, const TCHAR * sName, const TCHAR * sPath, HTREEITEM hParent/* = TVI_ROOT*/, HTREEITEM hAfter/* = TVI_LAST*/, bool bExpand/* = false*/ )
//DEL {
//DEL 	HTREEITEM hResTI = NULL;
//DEL 
//DEL 	if( !piFolder )
//DEL 		return hResTI;
//DEL 
//DEL 	int nImgNonSel = 0, nImgSel = 0;
//DEL 
//DEL 	if( piIcon )
//DEL 		GetIconsIndexes( piIcon, nImgNonSel, nImgSel );
//DEL 	else
//DEL 		if( !GetIconsIndexes( sPath, nImgNonSel, nImgSel ) )
//DEL 			GetIconsIndexes( pidl, nImgNonSel, nImgSel );
//DEL 	CFTCItemData * pParentData = (CFTCItemData*)GetItemData( hParent );
//DEL 	ULONG ulAttr = SFGAO_FILESYSANCESTOR | SFGAO_FILESYSTEM;;
//DEL 	if (pParentData)
//DEL 		HRESULT hr = pParentData->m_piFolder->GetAttributesOf(1, (const _ITEMIDLIST **)&pidl, &ulAttr);
//DEL 	if (!ulAttr)
//DEL 		return 0;
//DEL 	hResTI = InsertItem( sName, nImgNonSel, nImgSel, hParent, hAfter );
//DEL 	if( hResTI && ulAttr )
//DEL 	{
//DEL 		CFTCItemData * pItemData = new CFTCItemData( pParentData, piFolder, pidl, sPath );
//DEL 
//DEL 		SetItemData( hResTI, (DWORD)pItemData );
//DEL 		ULONG ulAttr;
//DEL 		ulAttr = SFGAO_HASSUBFOLDER;
//DEL 		if (pParentData)
//DEL 			HRESULT hr = pParentData->m_piFolder->GetAttributesOf(1, (const _ITEMIDLIST **)&pidl, &ulAttr);
//DEL 
//DEL 		if( ulAttr & SFGAO_HASSUBFOLDER )
//DEL 			if( bExpand )
//DEL 			{
//DEL 				InsertItem( _T(""), hResTI, hAfter );
//DEL 				Expand( hResTI, TVE_EXPAND );
//DEL 			}	
//DEL 			else
//DEL 				InsertItem( _T(""), hResTI, hAfter );
//DEL 	}
//DEL 	return hResTI;
//DEL }

BOOL CPropertiesCtrl::IsFolderEmpty( IShellFolder * piFolder ) const
{
	BOOL bRes = TRUE;
	if( !piFolder )
		return bRes;

	CComPtr<IEnumIDList> piIDList;
	ULONG nRes = 0;
	ITEMIDLIST * pItem = NULL;
	HRESULT hr = piFolder->EnumObjects( NULL, SHCONTF_FOLDERS, &piIDList );

	if( hr != NOERROR )
		return bRes;
	hr = piIDList->Next( 1, &pItem, &nRes );
	bRes = !( hr == NOERROR && nRes > 0 );
	if( pItem )
		m_piMalloc->Free( pItem );
	
	return bRes;
}

BOOL CPropertiesCtrl::OnExpanding( HTREEITEM hItem, UINT nCode )
{
	int i, nChild = 0;
	CFTCItemData * pItemData = (CFTCItemData*)GetItemData( hItem );

	switch( nCode )
	{
		case TVE_EXPAND:
			{
				CWaitCursor cur;
				nChild = GetChildCount( hItem );
				for( i = 0; i < nChild; i++ )
				{
					DelItemRecursive( GetNextItem( hItem, TVGN_CHILD ) );
					Invalidate();
				}

				CComPtr<IEnumIDList> piIDList;
				ULONG nRes = 0;
				ITEMIDLIST * pItem = NULL;
				HRESULT hr = pItemData->m_piFolder->EnumObjects( NULL, SHCONTF_FOLDERS, &piIDList );
				_STRRET strret;
				CSCADString sPath, sName;
				IExtractIcon * piEI = NULL;
				IShellFolder * piChildFolder = NULL;

				if( hr != NOERROR )
				{
					Invalidate();
					return FALSE;
				}
				for( hr = piIDList->Next( 1, &pItem, &nRes ); hr == NOERROR && nRes > 0; hr = piIDList->Next( 1, &pItem, &nRes ) )
				{
					hr = pItemData->m_piFolder->GetDisplayNameOf( pItem, SHGDN_INFOLDER, &strret );
					sName = StrRetToStr(pItem, strret, true, m_piMalloc );
					hr = pItemData->m_piFolder->GetDisplayNameOf( pItem, SHGDN_NORMAL | SHGDN_FORPARSING, &strret );
					sPath = StrRetToStr(pItem, strret, true, m_piMalloc );
					hr = pItemData->m_piFolder->GetUIObjectOf( NULL, 1, (LPCITEMIDLIST*)&pItem, IID_IExtractIcon, NULL, (void**)&piEI );
					hr = pItemData->m_piFolder->BindToObject( pItem, NULL, IID_IShellFolder, (void**)&piChildFolder );
					if( piChildFolder )
					{
						if( !piEI )
						{
							//hr = piChildFolder->CreateViewObject( NULL, IID_IExtractIcon, (void**)&piEI );
						}
						//InsertFolder( pItem, piChildFolder, piEI, sName, sPath, hItem );
						piChildFolder->Release();
						piChildFolder = NULL;
					}
					if( piEI )
					{
						piEI->Release();
						piEI = NULL;
					}
				}
			}
			return TRUE;
		default:
			nChild = GetChildCount( hItem );
			for( i = 0; i < nChild; i++ )
				DelItemRecursive( GetNextItem( hItem, TVGN_CHILD ) );
			if( !IsFolderEmpty( pItemData->m_piFolder ) )
				InsertItem( _T(""), hItem, TVI_LAST );
			break;
	}

	return TRUE;
}

BOOL CPropertiesCtrl::DelItemRecursive( HTREEITEM hItem )
{
	if( !hItem )
		return TRUE;

	HTREEITEM hChild = NULL;

	for( hChild = GetNextItem( hItem, TVGN_CHILD ); hChild; hChild = GetNextItem( hItem, TVGN_CHILD ) )
		DelItemRecursive( hChild );
	
	CFTCItemData * pItemData = (CFTCItemData*)GetItemData( hItem );

	if( pItemData )
	{
		m_piMalloc->Free( pItemData->m_pIDL );
		pItemData->m_pIDL = NULL;
	}
	delete pItemData;
	
	DeleteItem( hItem );

	return TRUE;
}

const TCHAR * CPropertiesCtrl::GetCurFolderPath() const
{
	HTREEITEM hItem = GetFirstSelectedItem();

	if( !hItem )
		return NULL;
	
	CFTCItemData * pData = (CFTCItemData*)GetItemData( hItem );

	if( !pData )
		return NULL;
	
	return pData->m_sPath;
}

CSCADString CPropertiesCtrl::StrRetToStr(LPITEMIDLIST pidl, _STRRET& strret, bool bMustFree/* = false*/, IMalloc * piMalloc/* = NULL*/ )
{
	CString str;
	CSCADString sRet;

	switch( strret.uType )
	{
		case STRRET_CSTR:
			sRet = strret.cStr;
			if( bMustFree )
				strret.cStr[0] = 0;
			break;
		case STRRET_WSTR:
			str = strret.pOleStr;
			sRet = str;
			if( bMustFree )
			{
				piMalloc->Free( strret.pOleStr );
				strret.pOleStr = NULL;
			}
			break;
		case STRRET_OFFSET:
			sRet = PSTR(PBYTE(pidl) + strret.uOffset);
			break;

	}

	return sRet;
}

void CPropertiesCtrl::OnDestroy() 
{
	DelItemRecursive( GetRootItem( NULL ) );
	SECTreeCtrl::OnDestroy();
}

BOOL CPropertiesCtrl::GetIconsIndexes( IExtractIcon * piIcon, int& nIcon, int& nIconOpen )
{
	nIcon = nIconOpen = 0;
	if( !piIcon )
		return FALSE;

	HRESULT hr;
	char sIconFile[MAX_PATH];
	int nIconInd = 0;
	HICON hiSmall = NULL, hiLarge = NULL;
	UINT nFlag = 0;

	sIconFile[0] = 0;
	hr = piIcon->GetIconLocation( GIL_FORSHELL, sIconFile, MAX_PATH, &nIconInd, &nFlag );
	if( hr == NOERROR )
	{
		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( sIconFile, nIconInd ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			hr = piIcon->Extract( sIconFile, nIconInd, &hiSmall, &hiLarge, MAKELONG( 16, 16 ) );
			if( hr == NOERROR )
			{
				if( hiSmall )
					nIcon = m_imlNormal.Add( hiSmall );
				else
					if( hiLarge )
						nIcon = m_imlNormal.Add( hiLarge );
				if( nIcon > 0 )
				{
					m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( sIconFile, nIconInd ), nIcon ) );
					::DestroyIcon( hiSmall );
					::DestroyIcon( hiLarge );
					hiSmall = hiLarge = NULL;
				}
			}
			else
				nIcon = 0;
		}
		else
			nIcon = itIcon->second;
	}
	
	nIconInd = 0;
	nFlag = 0;
	sIconFile[0] = 0;

	hr = piIcon->GetIconLocation( GIL_FORSHELL | GIL_OPENICON, sIconFile, MAX_PATH, &nIconInd, &nFlag ); 
	if( hr == NOERROR )
	{
		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( sIconFile, nIconInd ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			hr = piIcon->Extract( sIconFile, nIconInd, &hiSmall, &hiLarge, MAKELONG( 16, 16 ) ); 
			if( hr == NOERROR )
			{
				if( hiSmall )
					nIconOpen = m_imlNormal.Add( hiSmall );
				else
					if( hiLarge )
						nIconOpen = m_imlNormal.Add( hiLarge );
				if( nIconOpen )
				{
					m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( sIconFile, nIconInd ), nIconOpen ) );
					::DestroyIcon( hiSmall );
					::DestroyIcon( hiLarge );
					hiSmall = hiLarge = NULL;
				}
			}
			else
				nIconOpen = 0;
		}
		else
			nIconOpen = itIcon->second;
	}
	if( !nIconOpen )
		nIconOpen = nIcon;

	return ( nIcon && nIconOpen ) ? TRUE : FALSE;
}
/*
BOOL CPropertiesCtrl::GetIconsIndexes( const TCHAR * sPath, int& nIcon, int& nIconOpen )
{
	nIcon = nIconOpen = 0;
	if( !sPath || !*sPath )
		return FALSE;

	SHFILEINFO shFI;

	memset( &shFI, 0, sizeof( shFI ) );

	DWORD dwRes = SHGetFileInfo( sPath, 0, &shFI, sizeof( shFI ), SHGFI_ICON | SHGFI_ICONLOCATION );

	if( dwRes > 0 )
	{
		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			if( shFI.hIcon )
				nIcon = m_imlNormal.Add( shFI.hIcon );
			if( nIcon > 0 )
				m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ), nIcon ) );
		}
		else
			nIcon = itIcon->second;
	}

	if( shFI.hIcon )
		::DestroyIcon( shFI.hIcon );
	memset( &shFI, 0, sizeof( shFI ) );
	dwRes = SHGetFileInfo( sPath, 0, &shFI, sizeof( shFI ), SHGFI_OPENICON | SHGFI_ICONLOCATION );

	if( dwRes > 0 )
	{
		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			if( shFI.hIcon )
				nIconOpen = m_imlNormal.Add( shFI.hIcon );
			if( nIconOpen > 0 )
				m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ), nIconOpen ) );
		}
		else
			nIconOpen = itIcon->second;
	}
	if( shFI.hIcon )
		::DestroyIcon( shFI.hIcon );
	if( !nIconOpen )
		nIconOpen = nIcon;

	return ( nIcon && nIconOpen ) ? TRUE : FALSE;
}
*/
BOOL CPropertiesCtrl::GetIconsIndexes( ITEMIDLIST * pidl, int& nIcon, int& nIconOpen )
{
	nIcon = nIconOpen = 0;
	if( !pidl )
		return FALSE;

	SHFILEINFO shFI;

	memset( &shFI, 0, sizeof( shFI ) );

	DWORD dwRes = SHGetFileInfo( (LPCTSTR)pidl, 0, &shFI, sizeof( shFI ), SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON );

	if( dwRes > 0 )
	{
		_stprintf( shFI.szDisplayName, _T("%d"), dwRes );
		shFI.hIcon = ImageList_ExtractIcon( NULL, (HIMAGELIST)dwRes, shFI.iIcon );

		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			if( shFI.hIcon )
				nIcon = m_imlNormal.Add( shFI.hIcon );
			if( nIcon > 0 )
				m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ), nIcon ) );
		}
		else
			nIcon = itIcon->second;
	}

	if( shFI.hIcon )
		::DestroyIcon( shFI.hIcon );
	memset( &shFI, 0, sizeof( shFI ) );
	dwRes = SHGetFileInfo( (LPCTSTR)pidl, 0, &shFI, sizeof( shFI ), SHGFI_PIDL | SHGFI_SYSICONINDEX );

	if( dwRes > 0 )
	{
		_stprintf( shFI.szDisplayName, _T("%d"), dwRes );
		shFI.hIcon = CImageList::FromHandle( (HIMAGELIST)dwRes )->ExtractIcon( shFI.iIcon );

		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			if( shFI.hIcon )
				nIconOpen = m_imlNormal.Add( shFI.hIcon );
			if( nIconOpen > 0 )
				m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ), nIconOpen ) );
		}
		else
			nIconOpen = itIcon->second;
	}
	if( shFI.hIcon )
		::DestroyIcon( shFI.hIcon );
	if( !nIconOpen )
		nIconOpen = nIcon;

	return ( nIcon && nIconOpen ) ? TRUE : FALSE;
}

BOOL CPropertiesCtrl::GetIconsIndexes( const TCHAR * sPath, int& nIcon, int& nIconOpen )
{
	nIcon = nIconOpen = 0;
	if( !sPath )
		return FALSE;

	SHFILEINFO shFI;

	memset( &shFI, 0, sizeof( shFI ) );

	DWORD dwRes = SHGetFileInfo( sPath, 0, &shFI, sizeof( shFI ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON );
	
	if( dwRes > 0 )
	{
		_stprintf( shFI.szDisplayName, _T("%d"), dwRes );
		shFI.hIcon = ImageList_ExtractIcon( NULL, (HIMAGELIST)dwRes, shFI.iIcon );

		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			if( shFI.hIcon )
				nIcon = m_imlNormal.Add( shFI.hIcon );
			if( nIcon > 0 )
				m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ), nIcon ) );
		}
		else
			nIcon = itIcon->second;
	}

	if( shFI.hIcon )
		::DestroyIcon( shFI.hIcon );
	memset( &shFI, 0, sizeof( shFI ) );
	dwRes = SHGetFileInfo( sPath, 0, &shFI, sizeof( shFI ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_OPENICON );

	if( dwRes > 0 )
	{
		_stprintf( shFI.szDisplayName, _T("%d"), dwRes );
		shFI.hIcon = CImageList::FromHandle( (HIMAGELIST)dwRes )->ExtractIcon( shFI.iIcon );

		CFTCIconMap::iterator itIcon = m_miPresentIcon.find( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ) );

		if( itIcon == m_miPresentIcon.end() )
		{
			if( shFI.hIcon )
				nIconOpen = m_imlNormal.Add( shFI.hIcon );
			if( nIconOpen > 0 )
				m_miPresentIcon.insert( CFTCIconMap::value_type( CFTCIconInfo( shFI.szDisplayName, shFI.iIcon ), nIconOpen ) );
		}
		else
			nIconOpen = itIcon->second;
	}
	if( shFI.hIcon )
		::DestroyIcon( shFI.hIcon );
	if( !nIconOpen )
		nIconOpen = nIcon;

	return ( nIcon && nIconOpen ) ? TRUE : FALSE;
}

BOOL CPropertiesCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	SECTreeCtrl::OnChildNotify(message, wParam, lParam, pLResult);

	if( message == WM_NOTIFY )
	{
		NMHDR * pNMHDR = (NMHDR*)lParam;

		if( pNMHDR && pNMHDR->code == TVN_ITEMEXPANDING )
		{
			NMTREEVIEW * pExpandInfo = (LPNMTREEVIEW)pNMHDR;

			OnExpanding( pExpandInfo->itemNew.hItem, pExpandInfo->action );
			return TRUE;
		}
	}

	return FALSE;
}

int CPropertiesCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (SECTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SHGetDesktopFolder(	&m_piDesktop );
	SHGetMalloc( &m_piMalloc );
	m_imlNormal.Create( 16, 16, ILC_COLORDDB, 8, 8);
	m_imlNormal.SetBkColor( RGB( 255, 255, 255 ) );
	SetImageList( &m_imlNormal, TVSIL_NORMAL );
	
	return 0;
}

IShellFolder * CPropertiesCtrl::GetFolderByPath( IShellFolder * piParent, const TCHAR * sPathFolder, LPITEMIDLIST * ppItem, CSCADString& sName, IExtractIcon ** ppiIcon )
{
	if( !sPathFolder || !*sPathFolder )
		return NULL;

	OLECHAR olePath[MAX_PATH];
	OLECHAR * sPath;
	ULONG chEaten;
	ULONG dwAttributes;
	HRESULT hr;
	_STRRET strret;
	LPSHELLFOLDER piResFolder = NULL;
	bool bMustRelease = false;
	CComPtr<IShellFolder> piFolder;
	CComPtr<IMalloc> piMalloc;

	if( !piParent )
	{
		SHGetDesktopFolder( &piFolder );
		bMustRelease = true;
	}
	else
		piFolder = piParent;

	if( !piFolder )
		return NULL;

#ifndef UNICODE

	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, sPathFolder, -1, olePath, MAX_PATH );
	sPath = (OLECHAR*)olePath;

#else
	
	sPath = sPathFolder;

#endif //UNICODE

	hr = piFolder->ParseDisplayName( NULL, NULL, sPath, &chEaten, ppItem, &dwAttributes );
	   
	if( FAILED( hr ) )
		return NULL;

	hr = piFolder->GetDisplayNameOf( *ppItem, SHGDN_NORMAL, &strret );
	SHGetMalloc( &piMalloc );
	sName = StrRetToStr(*ppItem, strret, true, piMalloc );
	*ppiIcon = NULL;
	hr = piFolder->GetUIObjectOf( NULL, 1, (LPCITEMIDLIST*)ppItem, IID_IExtractIcon, NULL, (void**)ppiIcon );
	hr = piFolder->BindToObject( *ppItem, 0, IID_IShellFolder, (void**)&piResFolder );

	return piResFolder;
}

LPITEMIDLIST CPropertiesCtrl::GetPIDLByPath( IShellFolder * piParent, const TCHAR * sPathFolder )
{
	if( !sPathFolder || !*sPathFolder )
		return NULL;

	OLECHAR olePath[MAX_PATH];
	OLECHAR * sPath;
	ULONG chEaten;
	ULONG dwAttributes;
	HRESULT hr;
	//LPSHELLFOLDER piResFolder = NULL;
	bool bMustRelease = false;
	CComPtr<IShellFolder> piFolder;
	LPITEMIDLIST pItem = NULL;

	if( !piParent )
	{
		SHGetDesktopFolder( &piFolder );
		bMustRelease = true;
	}
	else
		piFolder = piParent;

	if( !piFolder )
		return NULL;

#ifndef UNICODE

	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, sPathFolder, -1, olePath, MAX_PATH );
	sPath = (OLECHAR*)olePath;

#else
	
	sPath = sPathFolder;

#endif //UNICODE

	hr = piFolder->ParseDisplayName( NULL, NULL, sPath, &chEaten, &pItem, &dwAttributes );
	   
	return pItem;
}

BOOL CPropertiesCtrl::EqualRelativePIDLs( ITEMIDLIST * pidl1, ITEMIDLIST * pidl2 )
{
	if( !pidl1 || !pidl2 || !pidl1->mkid.cb || !pidl2->mkid.cb || pidl1->mkid.cb != pidl2->mkid.cb )
		return FALSE;

	return memcmp( pidl1, pidl2, pidl1->mkid.cb ) == 0 ? TRUE : FALSE;
}

LPITEMIDLIST CPropertiesCtrl::GetLastPIDL( ITEMIDLIST * pidl )
{
	if( !pidl )
		return NULL;
	
	for( ; ((LPITEMIDLIST)(((BYTE*)pidl) + pidl->mkid.cb ))->mkid.cb; pidl = (LPITEMIDLIST)(((BYTE*)pidl) + pidl->mkid.cb ) );

	return pidl;
}

UINT CPropertiesCtrl::GetPIDLSize( ITEMIDLIST * pidl )
{
	if( !pidl )
		return 0;

	UINT nSubDir = 0;

	for( ; ((LPITEMIDLIST)((BYTE*)pidl))->mkid.cb; pidl = (LPITEMIDLIST)(((BYTE*)pidl) + pidl->mkid.cb ), nSubDir++ );

	return nSubDir;
}

//DEL FTCFolderCmpRes CPropertiesCtrl::CmpPath( const TCHAR * sParent, const TCHAR * sPath )
//DEL {
//DEL 	if( !sParent || !sPath || !*sParent || !*sPath )
//DEL 		return fcrNotEqual;
//DEL 
//DEL 	unsigned nParentLen = _tcslen( sParent );
//DEL 
//DEL 	if( _tcslen( sPath ) < nParentLen )
//DEL 		return fcrNotEqual;
//DEL 	if( _tcsnicmp( sParent, sPath, nParentLen ) == 0 )
//DEL 	{
//DEL 		if( !*( sPath + nParentLen ) )
//DEL 			return fcrEqual;
//DEL 		if( *( sPath + nParentLen ) == _T('\\') )
//DEL 			return fcrSubDir;
//DEL 	}
//DEL 
//DEL 	return fcrNotEqual;
//DEL }


BOOL CPropertiesCtrl::PathIsUNCPath( const TCHAR * sPathFolder )
{
	if( !sPathFolder || _tcslen( sPathFolder ) < 3 || sPathFolder[0] != _T('\\') || sPathFolder[1] != _T('\\') )
		return FALSE;

	return TRUE;
}

BOOL CPropertiesCtrl::PathIsUNCSvr( const TCHAR * sPathFolder )
{
	if( !sPathFolder || _tcslen( sPathFolder ) < 3 || 
		sPathFolder[0] != _T('\\') || sPathFolder[1] != _T('\\') ||
		_tcschr( sPathFolder + 2, _T('\\') ) 
	  )
		return FALSE;

	return TRUE;
}

BOOL CPropertiesCtrl::PathIsUNCShare( const TCHAR * sPathFolder )
{
	if( !PathIsUNCPath( sPathFolder ) )
		return FALSE;

	const TCHAR * pSlashPos = sPathFolder + 2;
	
	pSlashPos = _tcschr( pSlashPos, _T('\\') );

	if( !pSlashPos )
		return FALSE;

	pSlashPos++;
	pSlashPos = _tcschr( pSlashPos, _T('\\') );

	if( pSlashPos )
		return FALSE;

	return TRUE;
}

void CPropertiesCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu Popup;
	Popup.LoadMenu(IDR_POPUP_MENUS);
	CMenu* pPopup = Popup.GetSubMenu(5);
	ASSERT(pPopup);
	CRect rc;

	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,	point.x, point.y, GetParentFrame(), NULL/*&rc*/);
	
}
