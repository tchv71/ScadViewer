//---------------------------------------------------------------------------
#ifndef View3DBoxH
#define View3DBoxH

#include "MouseManipulatorWnd.h"

class CGLRenderer;
//---------------------------------------------------------------------------

class C3DBoxView : public CView, public CSettingManager, public I3DBoxView
{
protected:
	int				ClientWidth;
	int				ClientHeight;
	//IFemRenderer*	m_pRenderer;
	CGLRenderer*	m_pRenderer;
	CCutter			m_Cutter;
	TV3DBState		m_StateBeforeCut;
	FLOAT_TYPE			OldScrScale;
public:
	CDrawOptions	m_DrawOptions;
	CPersistViewOptions	m_ViewOptions;

	void			RebindGL(void);
	BOOL			UpdateSettings(bool bLoad, CString strSubkey);

	SPerspectiveView		m_ViewPos;
	TV3DBState		State;
	CRotator		Rot;


	void			Zoom(FLOAT_TYPE Scale);
	void			ZoomAll(S3DBox *Box, int Border);


	void			ResizeView(int Width, int Height, int Border);
	void			RestoreView(void);
	//void			FullRepaint(void)	{ NeedRefresh = true; Invalidate(); };

protected:
	C3DBoxView(void);		// protected constructor used by dynamic creation
	void Redraw(BOOL bSwap = TRUE) override;
	void EnablePopupMenu(bool bEnable) override
	{
		m_bDisplayPopupMenu = bEnable;
	}
	TV3DBState GetStateBeforeCut() override
	{
		return m_StateBeforeCut;
	}
	DECLARE_DYNCREATE(C3DBoxView)
	CString m_strFps;

// Attributes
public:
// Operations
public:
	void RedoCut() override
	{
		m_Cutter.RedoAll();
	}
	void UpdateToolbar() const;
	void SetCamera(int nFocusLength, bool bChangeDistance);
	void OnDepthChange(FLOAT_TYPE fNewDepth);
	void OnTransparencyChange(FLOAT_TYPE fNewVal);
	void ZoomAll(void) override;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DBoxView)
	public:
	afx_msg BOOL	OnEraseBkgnd(CDC *pDC);
	void	OnInitialUpdate(void) override;
	protected:
	void	OnDraw(CDC *pDC) override;	// overridden to draw this view
	void	OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint) override;
	void OnPrint(CDC* pDC, CPrintInfo* pInfo) override;
	BOOL OnPreparePrinting(CPrintInfo* pInfo) override;
	void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) override;
	//}}AFX_VIRTUAL
// Implementation
protected:
	CMouseManipulatorWnd renderWnd;
	virtual~C3DBoxView(void);
#ifdef _DEBUG
	void	AssertValid(void) const override;
	void	Dump(CDumpContext &dc) const override;
#endif

// Generated message map functions
protected:
	bool Select(CPoint pt) override;
	bool m_bDisplayPopupMenu;
	//{{AFX_MSG(C3DBoxView)
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnDestroy(void);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
#endif
