#if !defined(AFX_FOLDERLISTCTRL_H__0AB6AE91_1C60_4EBA_879D_2F32045687D0__INCLUDED_)
#define AFX_FOLDERLISTCTRL_H__0AB6AE91_1C60_4EBA_879D_2F32045687D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FolderListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFolderListCtrl window

#include "Forum3DView.h"
#include "DetViewOpts.h"
#include "DirChangeListener.h"
//#include <corecrt_io.h>
#include <tchar.h>


#define	FLC_IMAGE_EMPTY		0


enum FLViewType
{
	flvtThumbnail,
	flvtLargeIcon,
	flvtSmallIcon,
	flvtList,
	flvtDetails,
	flvtSize,
};

#define	FLC_HEADER_ID	128

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/

class FORUM3DVIEW_EXPORT CFolderListCtrl : public CListCtrl
{
	struct CFLCItemData
	{
		CFLCItemData( const TCHAR * sPath, const TCHAR * sExt ): m_nSize(0), m_tModified(0)
		{
			m_sFilePath = sPath;
			m_sExt = sExt;
			m_bProcessed = false;
			m_bFoundOnRefresh = true;
			m_nThumbnailInd = FLC_IMAGE_EMPTY;
			m_nLargeIconInd = FLC_IMAGE_EMPTY;
			m_nSmallIconInd = FLC_IMAGE_EMPTY;
		}

		CSCADString	m_sFilePath;
		CSCADString	m_sExt;
		_fsize_t	m_nSize;
		time_t		m_tModified;
		bool		m_bProcessed;
		bool		m_bFoundOnRefresh;
		int			m_nThumbnailInd;
		int			m_nLargeIconInd;
		int			m_nSmallIconInd;
	};
// Construction
public:
	CFolderListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Refresh();
	void RefreshFileList();
	void DeleteItem(CString &strFileName);
	virtual ~CFolderListCtrl();

	virtual	BOOL				SetCurFolder	( const CSCADString& sFolderPath, bool bForce = false );
	virtual	const CSCADString&	GetCurFolder	() const { return m_sFolderPath;}
	virtual	BOOL				SetViewProp		( const CFLCProperties& property );
	virtual	void				GetViewProp		( CFLCProperties& property ) const { property = m_Properties;}

	virtual	FLViewType	GetViewType		() const;
	virtual	BOOL		SetViewType		( FLViewType vt );
	virtual	BOOL		SetColumnName		();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFolderListCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg	LRESULT	OnSendFileBmp( WPARAM wParam, LPARAM lParam );
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg	LRESULT	OnDirChange( WPARAM wParam, LPARAM lParam );
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	virtual	void		CreateImageList		();
	virtual	BOOL		SetRedrawItemPos	( int nPos, bool bInit = false );
	virtual	void		DeleteAllItemsData	();
	virtual	void		ClearImageList		();
	virtual	BOOL		SetValidItemImage	( int nItem );
	virtual	BOOL		SetSortType			( int nCol, BOOL bAsc );
	virtual	CSCADString	TimeToStr			( time_t ftm ) const;

	static	int CALLBACK	CmpByName		( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
	static	int CALLBACK	CmpBySize		( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );
	static	int CALLBACK	CmpByModified	( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );

protected:
	void UpdateFileCount();
	void AddFileItem(const struct _tfinddata_t &fd,int  nLargeIconInd, int nSmallIconInd, CString &strExt);
	void AddFileTypeIcons(const struct _tfinddata_t &fd, int &nLargeIconInd, int &nSmallIconInd);
	enum flColumnPos
	{
		flcName,
		flcFileSize,
		flcModified,
		flcSize
	};
	struct	FLColumnInfo
	{
		UINT			m_idStr;
		PFNLVCOMPARE	m_fnCmp;
		int				m_nHdrFormat;
	};

	CImageList *	m_pimlThumbnails;
	CImageList		m_imlLargeIcons;
	CImageList		m_imlSmallIcons;
	CImageList		m_imlHeader;
	CSCADString		m_sFolderPath;
	CFLCProperties	m_Properties;
	int				m_nItemCount;
	int				m_nImageBalance;
	int				m_nTopItemForSizeChanging;
	int				m_nSelectedItem;
	FLViewType		m_flvtViewType;
	CSCADString		m_sModifiedFormat;
	int				m_nCurColumn;
	BOOL			m_bSortAscending;

	CDirChangeListener m_DirChangeListener;
	CString			m_strSelectedPath;
	static	DWORD			m_ListStyles[flvtSize];
	static	FLColumnInfo	m_flciColumns[flcSize];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERLISTCTRL_H__0AB6AE91_1C60_4EBA_879D_2F32045687D0__INCLUDED_)
