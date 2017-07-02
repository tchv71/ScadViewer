// PropertiesCtrl.h : header file
//
// Copyright (C) 2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#if !defined(AFX_SCADFOLDERTREECTRL_HXX__BE66CF46_248D_4A43_B134_1D6E24B064E9__INCLUDED_)
#define AFX_SCADFOLDERTREECTRL_HXX__BE66CF46_248D_4A43_B134_1D6E24B064E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPropertiesCtrl window

#pragma warning( disable : 4284 )

//#include "SCAD3DModelAPIDef.hxx"
//#include "SCADString.hxx"
#include <map>
using namespace std;
#include "Forum3DView/Forum3DView.h"

#include <atlbase.h>

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
enum FTCFolderCmpRes
{
	fcrNotEqual,
	fcrEqual,
	fcrSubDir
};

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
#define	FTC_ICON_DEFAULT_IND	0

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/


class FORUM3DVIEW_EXPORT CPropertiesCtrl : public SECTreeCtrl
{
// Construction
public:
	CPropertiesCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesCtrl)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertiesCtrl();

	//idFolder is one from CSIDL_ values

	virtual	const TCHAR *	GetCurFolderPath() const;
	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesCtrl)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	virtual	BOOL		OnExpanding		( HTREEITEM hItem, UINT nCode );
	virtual	BOOL		IsFolderEmpty	( IShellFolder * piFolder ) const;
	virtual	BOOL		DelItemRecursive( HTREEITEM hItem );
	virtual	BOOL		GetIconsIndexes	( IExtractIcon * piIcon, int& nIcon, int& nIconOpen );
	virtual	BOOL		GetIconsIndexes	( const TCHAR * sPath, int& nIcon, int& nIconOpen );
	virtual	BOOL		GetIconsIndexes	( ITEMIDLIST * pidl, int& nIcon, int& nIconOpen );

	static	CSCADString		StrRetToStr			( LPITEMIDLIST pidl, _STRRET& strret, bool bMustFree = false, IMalloc * piMalloc = NULL );
	static	IShellFolder *	GetFolderByPath		( IShellFolder * piParent, const TCHAR * sPathFolder, /*out*/LPITEMIDLIST * ppItem, /*out*/CSCADString& sName, /*out*/IExtractIcon ** ppiIcon );
	static	LPITEMIDLIST	GetPIDLByPath		( IShellFolder * piParent, const TCHAR * sPathFolder );
	static	BOOL			EqualRelativePIDLs	( ITEMIDLIST * pidl1, ITEMIDLIST * pidl2 );
	static	LPITEMIDLIST	GetLastPIDL			( ITEMIDLIST * pidl );
	static	UINT			GetPIDLSize			( ITEMIDLIST * pidl );

	static	BOOL			PathIsUNCPath		( const TCHAR * sPathFolder );
	static	BOOL			PathIsUNCSvr		( const TCHAR * sPathFolder );
	static	BOOL			PathIsUNCShare		( const TCHAR * sPathFolder );

protected:
	struct	CFTCItemData
	{
		CFTCItemData( CFTCItemData * pParent, IShellFolder * piFolder, ITEMIDLIST * pidl, const TCHAR * sPath )
		{
			m_pParent = pParent;
			m_piFolder = piFolder;
			m_pIDL = pidl;
			m_sPath = sPath;
		}

		CFTCItemData *			m_pParent;
		CComPtr<IShellFolder>	m_piFolder;
		LPITEMIDLIST			m_pIDL;
		CString					m_sPath;
	};
	struct	CFTCIconInfo
	{
		CFTCIconInfo( const TCHAR * sIFN, int nIPos )
		{
			m_sIconFileName = sIFN;
			m_nIconPos = nIPos;
		}

		bool operator<( const CFTCIconInfo& ii ) const
		{
			if( m_sIconFileName > ii.m_sIconFileName )
				return false;
			if( m_sIconFileName == ii.m_sIconFileName )
				return m_nIconPos < ii.m_nIconPos ? true : false;
			return true;
		}
		CString	m_sIconFileName;
		int		m_nIconPos;
	};

	typedef map< CFTCIconInfo, int>	CFTCIconMap;

	CComPtr<IShellFolder>	m_piDesktop;
	CComPtr<IMalloc>		m_piMalloc;
	CImageList				m_imlNormal;
	map< CFTCIconInfo, int>	m_miPresentIcon;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCADFOLDERTREECTRL_HXX__BE66CF46_248D_4A43_B134_1D6E24B064E9__INCLUDED_)
