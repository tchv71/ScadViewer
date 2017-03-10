// Mp4View.h : interface of the CMp4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP4VIEW_H__EB9E8092_3466_4847_9127_4D007B9C4335__INCLUDED_)
#define AFX_MP4VIEW_H__EB9E8092_3466_4847_9127_4D007B9C4335__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScadViewerView.h"

class FORUM3DVIEW_EXPORT CMp4View : public CScadViewerView
{
protected: // create from serialization only
	CMp4View();
	DECLARE_DYNCREATE(CMp4View)

public:
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMp4View)
	public:
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	protected:
	//virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnInitialUpdate() override; // called first time after construct
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;

	// From I3DBoxView interface
	void ZoomAll() override;
	void Redraw(BOOL) override;
	void EnablePopupMenu(bool bEnable) override;
	TV3DBState GetStateBeforeCut() override;
	bool Select(CPoint pt) override;


	//virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	afx_msg BOOL	OnEraseBkgnd(CDC *pDC);
	afx_msg void OnFileNew();
	afx_msg void OnFilePlay();
	afx_msg void OnFileStop();
	void OnClose();

// Implementation
public:
	virtual ~CMp4View();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

protected:
	//IDSMP4*				m_pDSMP4;
	//I3DView*			m_p3DView;
	bool	m_bShowMp4;

// Generated message map functions
protected:
	//{{AFX_MSG(CMp4View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MP4VIEW_H__EB9E8092_3466_4847_9127_4D007B9C4335__INCLUDED_)
