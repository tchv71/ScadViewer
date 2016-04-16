#ifndef __FOLDERTREEDOCKINGWND_H__
#define __FOLDERTREEDOCKINGWND_H__

// Stingray Objective Toolkit
// Component Gallery generated file
// FolderTreeDockingWnd.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CFolderTreeDockingWnd window
// TODO: define a resource id
#define IDC_EMBEDDED_CONTROL 200
class CShellTreeCtrl : public CMFCShellTreeCtrl
{
public:
	CString GetCurFolderPath() const
	{ CString strFolder; GetItemPath(strFolder); return strFolder; }
	void SetCurFolder(LPCTSTR sFolderPath ) { SelectPath(sFolderPath); }
};


class CFolderTreeDockingWnd : public CDockablePane
{
// Construction
public:
	CFolderTreeDockingWnd();
// Attributes
public:
	CShellTreeCtrl m_childWnd;
	//virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler) {};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderTreeDockingWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFolderTreeDockingWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFolderTreeDockingWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __FOLDERTREEDOCKINGWND_H__
