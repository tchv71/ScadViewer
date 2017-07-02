// SCADFolderTreeCtrl.cxx : implementation file
//

#include "stdafx.h"
#include "../ForumView_ENG/resource.h"
//#include "SCAD3DMdlSettings.h"
#include "SCADFolderTreeCtrl.hxx"
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSCADFolderTreeCtrl

CSCADFolderTreeCtrl::CSCADFolderTreeCtrl()
{
	m_piMalloc = nullptr;
}

CSCADFolderTreeCtrl::~CSCADFolderTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CSCADFolderTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CSCADFolderTreeCtrl)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCADFolderTreeCtrl message handlers

BOOL CSCADFolderTreeCtrl::SetTopFolder( int idFolder, BOOL bExpand/* = FALSE*/ )
{
	DelItemRecursive( GetRootItem() );

	CComPtr<IShellFolder> piDesktop;
	CComPtr<IShellFolder> piFolder;
	BOOL bRes = FALSE;

	SHGetDesktopFolder( &piDesktop );

	ITEMIDLIST * pItem = nullptr;
	HRESULT hr = SHGetSpecialFolderLocation( nullptr, idFolder, &pItem );
	if (FAILED(hr))
		return FALSE;

	_STRRET strret;
	IExtractIcon * piEI = nullptr;
	CSCADString sName;
	CSCADString sFolderPath;

	hr = piDesktop->GetDisplayNameOf( pItem, SHGDN_NORMAL, &strret );
	if (FAILED(hr))
		return FALSE;
	sName = StrRetToStr(pItem, strret, true, m_piMalloc );
	hr = piDesktop->GetDisplayNameOf( pItem, SHGDN_NORMAL | SHGDN_FORPARSING, &strret );
	if (FAILED(hr))
		return FALSE;
	sFolderPath = StrRetToStr(pItem, strret, true, m_piMalloc );
	hr = piDesktop->GetUIObjectOf( nullptr, 1, const_cast<LPCITEMIDLIST*>(&pItem), IID_IExtractIcon, nullptr, reinterpret_cast<void**>(&piEI) );
	if (FAILED(hr))
		return FALSE;
	if( idFolder != CSIDL_DESKTOP )
		hr = piDesktop->BindToObject( pItem, nullptr, IID_IShellFolder, reinterpret_cast<void**>(&piFolder) );
	else
		piFolder = piDesktop;
	if (FAILED(hr))
		return FALSE;


	if( piFolder )
		bRes = InsertFolder( pItem, piFolder, piEI, sName, sFolderPath, TVI_ROOT, TVI_LAST, true ) != nullptr;

	if( piEI )
		piEI->Release();

	return bRes;
}

BOOL CSCADFolderTreeCtrl::SetTopFolder( const TCHAR * sPathFolder, BOOL bExpand/* = FALSE*/ )
{
	if( !sPathFolder || !*sPathFolder )
		return FALSE;

	DelItemRecursive( GetRootItem() );

	CSCADString sName;
	ITEMIDLIST * pItem = nullptr; 
	CComPtr<IExtractIcon> piEI;
	IShellFolder * piFld = GetFolderByPath( nullptr, sPathFolder, &pItem, sName, &piEI );
	CComPtr<IShellFolder> piFolder = piFld;
	
	if( piFolder )
	{
		piFld->Release();
		InsertFolder( pItem, piFolder, piEI, sName, sPathFolder, TVI_ROOT, TVI_LAST, true );
	}

	return piFolder != nullptr;
}

BOOL CSCADFolderTreeCtrl::SetCurFolder( const TCHAR * sPathFolder, BOOL bExpand/* = FALSE*/ )
{
	if( !sPathFolder || !*sPathFolder )
		return FALSE;

	HTREEITEM hRoot = GetRootItem();
	CFTCItemData * pItemData = reinterpret_cast<CFTCItemData*>(GetItemData( hRoot ));

	if( !pItemData )
		return FALSE;

	IShellFolder * piRoot = pItemData->m_piFolder;

	if( !piRoot )
		return FALSE;

	LPITEMIDLIST pCurIDL = GetPIDLByPath( piRoot, sPathFolder );
	_STRRET strret;

	piRoot->GetDisplayNameOf( pCurIDL, SHGDN_NORMAL | SHGDN_FORPARSING, &strret );
	CSCADString sNormPath = StrRetToStr(pCurIDL, strret, true, m_piMalloc );

	HTREEITEM hItem = OpenFolder( hRoot, pCurIDL, sPathFolder );

	if( !pCurIDL )
		m_piMalloc->Free( pCurIDL );
	if( hItem ) 
	{
		Select( hItem, TVGN_CARET );
		if( bExpand && !IsExpanded( hItem ) )
			Expand( hItem, TVE_EXPAND );
	}
	
	return hItem ? TRUE : FALSE;
}

HTREEITEM CSCADFolderTreeCtrl::OpenFolder( HTREEITEM hItem, LPITEMIDLIST pidl, const TCHAR * sPathFolder )
{
	if( !hItem )
		return nullptr;
	if( pidl && !pidl->mkid.cb )
		return hItem;

	if( !IsExpanded( hItem ) )
		Expand( hItem, TVE_EXPAND );

	HTREEITEM hChildItem = GetNextItem( hItem, TVGN_CHILD );
	CFTCItemData * pItemData;
	FTCFolderCmpRes fcrRes;

	for( ; hChildItem; hChildItem = GetNextItem( hChildItem, TVGN_NEXT ) )
	{
		pItemData = reinterpret_cast<CFTCItemData*>(GetItemData( hChildItem ));
		if( !pItemData )
			continue;
		if( pidl && EqualRelativePIDLs( pidl, pItemData->m_pIDL) )
			return OpenFolder( hChildItem, reinterpret_cast<ITEMIDLIST*>(reinterpret_cast<BYTE*>(pidl) + pidl->mkid.cb), sPathFolder );
		fcrRes = CmpPath( pItemData->m_sPath, sPathFolder );
		if( fcrRes == fcrSubDir )
		{
			pidl = pidl ? reinterpret_cast<ITEMIDLIST*>(reinterpret_cast<BYTE*>(pidl) + pidl->mkid.cb) : pidl;

			return OpenFolder( hChildItem, pidl, sPathFolder );
		}
		if( fcrRes == fcrEqual )
			return hChildItem;
	}

	return nullptr;
}

HTREEITEM CSCADFolderTreeCtrl::InsertFolder( ITEMIDLIST * pidl, IShellFolder * piFolder, IExtractIcon * piIcon, const TCHAR * sName, const TCHAR * sPath, HTREEITEM hParent/* = TVI_ROOT*/, HTREEITEM hAfter/* = TVI_LAST*/, bool bExpand/* = false*/ )
{
	HTREEITEM hResTI = nullptr;

	if( !piFolder )
		return hResTI;

	int nImgNonSel = 0, nImgSel = 0;

	if( piIcon )
		GetIconsIndexes( piIcon, nImgNonSel, nImgSel );
	else
		if( !GetIconsIndexes( sPath, nImgNonSel, nImgSel ) )
			GetIconsIndexes( pidl, nImgNonSel, nImgSel );
	CFTCItemData * pParentData = reinterpret_cast<CFTCItemData*>(GetItemData( hParent ));
	ULONG ulAttr = SFGAO_FILESYSANCESTOR | SFGAO_FILESYSTEM;;
	if (pParentData)
	{
		HRESULT hr = pParentData->m_piFolder->GetAttributesOf(1, const_cast<const _ITEMIDLIST **>(&pidl), &ulAttr);
		if (FAILED(hr))
			return nullptr;
	}
	if (!ulAttr)
		return nullptr;
	hResTI = InsertItem( sName, nImgNonSel, nImgSel, hParent, hAfter );
	if( hResTI && ulAttr )
	{
		CFTCItemData * pItemData = new CFTCItemData( pParentData, piFolder, pidl, sPath );

		SetItemData( hResTI, DWORD_PTR(pItemData) );
		ULONG attr;
		attr = SFGAO_HASSUBFOLDER;
		if (pParentData)
		{
			HRESULT hr = pParentData->m_piFolder->GetAttributesOf(1, const_cast<const _ITEMIDLIST **>(&pidl), &attr);
			if (FAILED(hr))
				return nullptr;
		}

		if( attr & SFGAO_HASSUBFOLDER )
			if( bExpand )	
			{
				InsertItem( _T(""), hResTI, hAfter );
				Expand( hResTI, TVE_EXPAND );
			}	
			else
				InsertItem( _T(""), hResTI, hAfter );
	}
	return hResTI;
}

BOOL CSCADFolderTreeCtrl::IsFolderEmpty( IShellFolder * piFolder ) const
{
	BOOL bRes = TRUE;
	if( !piFolder )
		return bRes;

	CComPtr<IEnumIDList> piIDList;
	ULONG nRes = 0;
	ITEMIDLIST * pItem = nullptr;
	HRESULT hr = piFolder->EnumObjects( nullptr, SHCONTF_FOLDERS, &piIDList );

	if( hr != NOERROR )
		return bRes;
	hr = piIDList->Next( 1, &pItem, &nRes );
	bRes = !( hr == NOERROR && nRes > 0 );
	if( pItem )
		m_piMalloc->Free( pItem );
	
	return bRes;
}

BOOL CSCADFolderTreeCtrl::OnExpanding( HTREEITEM hItem, UINT nCode )
{
	//int nChild = 0;
	CFTCItemData * pItemData = reinterpret_cast<CFTCItemData*>(GetItemData( hItem ));

	switch( nCode )
	{
		case TVE_EXPAND:
			{
				CWaitCursor cur;
				//nChild = GetChildCount( hItem );
				for( HTREEITEM i = GetChildItem(hItem); i ;  )
				{
					DelItemRecursive(i);
					i=GetNextSiblingItem(i);
					Invalidate();
				}

				CComPtr<IEnumIDList> piIDList;
				ULONG nRes = 0;
				ITEMIDLIST * pItem = nullptr;
				HRESULT hr = pItemData->m_piFolder->EnumObjects( nullptr, SHCONTF_FOLDERS, &piIDList );
				_STRRET strret;
				CSCADString sPath, sName;
				IExtractIcon * piEI = nullptr;
				IShellFolder * piChildFolder = nullptr;

				if( hr != NOERROR )
				{
					Invalidate();
					return FALSE;
				}
				for( hr = piIDList->Next( 1, &pItem, &nRes ); hr == NOERROR && nRes > 0; hr = piIDList->Next( 1, &pItem, &nRes ) )
				{
					hr = pItemData->m_piFolder->GetDisplayNameOf( pItem, SHGDN_INFOLDER, &strret );
					if (FAILED(hr))
						return FALSE;
					sName = StrRetToStr(pItem, strret, true, m_piMalloc );
					hr = pItemData->m_piFolder->GetDisplayNameOf( pItem, SHGDN_NORMAL | SHGDN_FORPARSING, &strret );
					if (FAILED(hr))
						return FALSE;
					sPath = StrRetToStr(pItem, strret, true, m_piMalloc );
					hr = pItemData->m_piFolder->GetUIObjectOf( nullptr, 1, const_cast<LPCITEMIDLIST*>(&pItem), IID_IExtractIcon, nullptr, reinterpret_cast<void**>(&piEI) );
					if (FAILED(hr))
						return FALSE;
					hr = pItemData->m_piFolder->BindToObject( pItem, nullptr, IID_IShellFolder, reinterpret_cast<void**>(&piChildFolder) );
					if (FAILED(hr))
						return FALSE;
					if( piChildFolder )
					{
						if( !piEI )
						{
							//hr = piChildFolder->CreateViewObject( nullptr, IID_IExtractIcon, (void**)&piEI );
						}
						InsertFolder( pItem, piChildFolder, piEI, sName, sPath, hItem );
						piChildFolder->Release();
						piChildFolder = nullptr;
					}
					if( piEI )
					{
						piEI->Release();
						piEI = nullptr;
					}
				}
			}
			return TRUE;
		default:
			//nChild = GetChildCount( hItem );
			for(HTREEITEM i = GetChildItem(hItem); i; )
			{
				DelItemRecursive(i);
				i=GetNextSiblingItem(i);
			}
			if( !IsFolderEmpty( pItemData->m_piFolder ) )
				InsertItem( _T(""), hItem, TVI_LAST );
			break;
	}

	return TRUE;
}

BOOL CSCADFolderTreeCtrl::DelItemRecursive( HTREEITEM hItem )
{
	if( !hItem )
		return TRUE;

	HTREEITEM hChild = nullptr;

	for( hChild = GetNextItem( hItem, TVGN_CHILD ); hChild; hChild = GetNextItem( hItem, TVGN_CHILD ) )
		DelItemRecursive( hChild );
	
	CFTCItemData * pItemData = reinterpret_cast<CFTCItemData*>(GetItemData( hItem ));

	if( pItemData )
	{
		m_piMalloc->Free( pItemData->m_pIDL );
		pItemData->m_pIDL = nullptr;
	}
	delete pItemData;
	
	DeleteItem( hItem );

	return TRUE;
}

const TCHAR * CSCADFolderTreeCtrl::GetCurFolderPath() const
{
	HTREEITEM hItem = GetSelectedItem();

	if( !hItem )
		return nullptr;
	
	CFTCItemData * pData = reinterpret_cast<CFTCItemData*>(GetItemData( hItem ));

	if( !pData )
		return nullptr;
	
	return pData->m_sPath;
}

CSCADString CSCADFolderTreeCtrl::StrRetToStr(LPITEMIDLIST pidl, _STRRET& strret, bool bMustFree/* = false*/, IMalloc * piMalloc/* = nullptr*/ )
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
				strret.pOleStr = nullptr;
			}
			break;
		case STRRET_OFFSET:
			sRet = PSTR(PBYTE(pidl) + strret.uOffset);
			break;

	}

	return sRet;
}

void CSCADFolderTreeCtrl::OnDestroy() 
{
	DelItemRecursive( GetRootItem( ) );
	CTreeCtrl::OnDestroy();
}

BOOL CSCADFolderTreeCtrl::GetIconsIndexes( IExtractIcon * piIcon, int& nIcon, int& nIconOpen )
{
	nIcon = nIconOpen = 0;
	if( !piIcon )
		return FALSE;

	HRESULT hr;
	TCHAR sIconFile[MAX_PATH];
	int nIconInd = 0;
	HICON hiSmall = nullptr, hiLarge = nullptr;
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
					hiSmall = hiLarge = nullptr;
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
					hiSmall = hiLarge = nullptr;
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
BOOL CSCADFolderTreeCtrl::GetIconsIndexes( const TCHAR * sPath, int& nIcon, int& nIconOpen )
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
BOOL CSCADFolderTreeCtrl::GetIconsIndexes( ITEMIDLIST * pidl, int& nIcon, int& nIconOpen )
{
	nIcon = nIconOpen = 0;
	if( !pidl )
		return FALSE;

	SHFILEINFO shFI;

	memset( &shFI, 0, sizeof( shFI ) );

	DWORD_PTR dwRes = SHGetFileInfo( LPCTSTR(pidl), 0, &shFI, sizeof( shFI ), SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON );

	if( dwRes > 0 )
	{
#ifdef _AMD64_
		_stprintf_s(shFI.szDisplayName, _T("%lld"), dwRes);
#else
		_stprintf_s( shFI.szDisplayName, _T("%d"), dwRes );
#endif
		shFI.hIcon = ImageList_ExtractIcon( nullptr, HIMAGELIST(dwRes), shFI.iIcon );

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
	dwRes = SHGetFileInfo( LPCTSTR(pidl), 0, &shFI, sizeof( shFI ), SHGFI_PIDL | SHGFI_SYSICONINDEX );

	if( dwRes > 0 )
	{
#ifdef _AMD64_
		_stprintf_s(shFI.szDisplayName, _T("%lld"), dwRes);
#else
		_stprintf_s(shFI.szDisplayName, _T("%d"), dwRes);
#endif
		shFI.hIcon = CImageList::FromHandle( HIMAGELIST(dwRes) )->ExtractIcon( shFI.iIcon );

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

BOOL CSCADFolderTreeCtrl::GetIconsIndexes( const TCHAR * sPath, int& nIcon, int& nIconOpen )
{
	nIcon = nIconOpen = 0;
	if( !sPath )
		return FALSE;

	SHFILEINFO shFI;

	memset( &shFI, 0, sizeof( shFI ) );

	DWORD_PTR dwRes = SHGetFileInfo( sPath, 0, &shFI, sizeof( shFI ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON );
	
	if( dwRes > 0 )
	{
#ifdef _AMD64_
		_stprintf_s(shFI.szDisplayName, _T("%lld"), dwRes);
#else
		_stprintf_s( shFI.szDisplayName, _T("%d"), dwRes );
#endif // _AMD64_

		shFI.hIcon = ImageList_ExtractIcon( nullptr, HIMAGELIST(dwRes), shFI.iIcon );

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
#ifdef _AMD64_
		_stprintf_s(shFI.szDisplayName, _T("%lld"), dwRes);
#else
		_stprintf_s(shFI.szDisplayName, _T("%d"), dwRes);
#endif // _AMD64_

		shFI.hIcon = CImageList::FromHandle( HIMAGELIST(dwRes) )->ExtractIcon( shFI.iIcon );

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

BOOL CSCADFolderTreeCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	CTreeCtrl::OnChildNotify(message, wParam, lParam, pLResult);

	if( message == WM_NOTIFY )
	{
		NMHDR * pNMHDR = reinterpret_cast<NMHDR*>(lParam);

		if( pNMHDR && pNMHDR->code == TVN_ITEMEXPANDING )
		{
			NMTREEVIEW * pExpandInfo = LPNMTREEVIEW(pNMHDR);

			OnExpanding( pExpandInfo->itemNew.hItem, pExpandInfo->action );
			return TRUE;
		}
	}

	return FALSE;
}

int CSCADFolderTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SHGetDesktopFolder(	&m_piDesktop );
	SHGetMalloc( &m_piMalloc );
	m_imlNormal.Create( 16, 16, ILC_COLORDDB, 8, 8);
	m_imlNormal.SetBkColor( RGB( 255, 255, 255 ) );
	SetImageList( &m_imlNormal, TVSIL_NORMAL );
	
	return 0;
}

IShellFolder * CSCADFolderTreeCtrl::GetFolderByPath( IShellFolder * piParent, const TCHAR * sPathFolder, LPITEMIDLIST * ppItem, CSCADString& sName, IExtractIcon ** ppiIcon )
{
	if( !sPathFolder || !*sPathFolder )
		return nullptr;

#ifndef UNICODE
	OLECHAR olePath[MAX_PATH];
#endif // !UNICODE

	OLECHAR * sPath;
	ULONG chEaten;
	ULONG dwAttributes;
	HRESULT hr;
	_STRRET strret;
	LPSHELLFOLDER piResFolder = nullptr;
	CComPtr<IShellFolder> piFolder;
	CComPtr<IMalloc> piMalloc;

	if( !piParent )
	{
		SHGetDesktopFolder( &piFolder );
	}
	else
		piFolder = piParent;

	if( !piFolder )
		return nullptr;

#ifndef UNICODE

	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, sPathFolder, -1, olePath, MAX_PATH );
	sPath = (OLECHAR*)olePath;

#else
	
	sPath = LPWSTR(sPathFolder);

#endif //UNICODE

	hr = piFolder->ParseDisplayName( nullptr, nullptr, sPath, &chEaten, ppItem, &dwAttributes );
	   
	if( FAILED( hr ) )
		return nullptr;

	hr = piFolder->GetDisplayNameOf( *ppItem, SHGDN_NORMAL, &strret );
	if( FAILED( hr ) )
		return nullptr;
	SHGetMalloc( &piMalloc );
	sName = StrRetToStr(*ppItem, strret, true, piMalloc );
	*ppiIcon = nullptr;
	hr = piFolder->GetUIObjectOf( nullptr, 1, const_cast<LPCITEMIDLIST*>(ppItem), IID_IExtractIcon, nullptr, reinterpret_cast<void**>(ppiIcon) );
	if( FAILED( hr ) )
		return nullptr;
	hr = piFolder->BindToObject( *ppItem, nullptr, IID_IShellFolder, reinterpret_cast<void**>(&piResFolder) );
	if( FAILED( hr ) )
		return nullptr;

	return piResFolder;
}

LPITEMIDLIST CSCADFolderTreeCtrl::GetPIDLByPath( IShellFolder * piParent, const TCHAR * sPathFolder )
{
	if( !sPathFolder || !*sPathFolder )
		return nullptr;
#ifndef UNICODE
	OLECHAR olePath[MAX_PATH];
#endif // !UNICODE

	OLECHAR * sPath;
	ULONG chEaten;
	ULONG dwAttributes;
	HRESULT hr;
	//LPSHELLFOLDER piResFolder = nullptr;
	CComPtr<IShellFolder> piFolder;
	LPITEMIDLIST pItem = nullptr;

	if( !piParent )
	{
		SHGetDesktopFolder( &piFolder );
	}
	else
		piFolder = piParent;

	if( !piFolder )
		return nullptr;

#ifndef UNICODE

	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, sPathFolder, -1, olePath, MAX_PATH );
	sPath = (OLECHAR*)olePath;

#else
	
	sPath = LPWSTR(sPathFolder);

#endif //UNICODE

	hr = piFolder->ParseDisplayName( nullptr, nullptr, sPath, &chEaten, &pItem, &dwAttributes );
	if (FAILED(hr))
		return nullptr;
	   
	return pItem;
}

BOOL CSCADFolderTreeCtrl::EqualRelativePIDLs( LPITEMIDLIST pidl1, LPITEMIDLIST pidl2 )
{
	if( !pidl1 || !pidl2 || !pidl1->mkid.cb || !pidl2->mkid.cb || pidl1->mkid.cb != pidl2->mkid.cb )
		return FALSE;

	return memcmp( pidl1, pidl2, pidl1->mkid.cb ) == 0 ? TRUE : FALSE;
}

LPITEMIDLIST CSCADFolderTreeCtrl::GetLastPIDL(LPITEMIDLIST  pidl )
{
	if( !pidl )
		return nullptr;
	
	for( ; LPITEMIDLIST(reinterpret_cast<BYTE*>(pidl) + pidl->mkid.cb)->mkid.cb;
	       // ReSharper disable once CppPossiblyErroneousEmptyStatements
		pidl = LPITEMIDLIST(reinterpret_cast<BYTE*>(pidl) + pidl->mkid.cb) );

	return pidl;
}

UINT CSCADFolderTreeCtrl::GetPIDLSize( LPITEMIDLIST pidl )
{
	if( !pidl )
		return 0;

	UINT nSubDir = 0;

	// ReSharper disable once CppPossiblyErroneousEmptyStatements
	for( ; LPITEMIDLIST(reinterpret_cast<BYTE*>(pidl))->mkid.cb; pidl = LPITEMIDLIST(reinterpret_cast<BYTE*>(pidl) + pidl->mkid.cb), nSubDir++ );

	return nSubDir;
}

FTCFolderCmpRes CSCADFolderTreeCtrl::CmpPath( const TCHAR * sParent, const TCHAR * sPath )
{
	if( !sParent || !sPath || !*sParent || !*sPath )
		return fcrNotEqual;

	size_t nParentLen = _tcslen( sParent );

	if( _tcslen( sPath ) < nParentLen )
		return fcrNotEqual;
	if( _tcsnicmp( sParent, sPath, nParentLen ) == 0 )
	{
		if( !*( sPath + nParentLen ) )
			return fcrEqual;
		if( *( sPath + nParentLen ) == _T('\\') )
			return fcrSubDir;
	}

	return fcrNotEqual;
}


BOOL CSCADFolderTreeCtrl::PathIsUNCPath( const TCHAR * sPathFolder )
{
	if( !sPathFolder || _tcslen( sPathFolder ) < 3 || sPathFolder[0] != _T('\\') || sPathFolder[1] != _T('\\') )
		return FALSE;

	return TRUE;
}

BOOL CSCADFolderTreeCtrl::PathIsUNCSvr( const TCHAR * sPathFolder )
{
	if( !sPathFolder || _tcslen( sPathFolder ) < 3 || 
		sPathFolder[0] != _T('\\') || sPathFolder[1] != _T('\\') ||
		_tcschr( sPathFolder + 2, _T('\\') ) 
	  )
		return FALSE;

	return TRUE;
}

BOOL CSCADFolderTreeCtrl::PathIsUNCShare( const TCHAR * sPathFolder )
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

// ReSharper disable once CppMemberFunctionMayBeConst
void CSCADFolderTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu Popup;
	Popup.LoadMenu(IDR_POPUP_MENUS);
	CMenu* pPopup = Popup.GetSubMenu(5);
	ASSERT(pPopup);
	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,	point.x, point.y, GetParentFrame(), nullptr/*&rc*/);
	
}
