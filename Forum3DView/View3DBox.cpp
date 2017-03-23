//---------------------------------------------------------------------------
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#include "stdafx.h" 
#include "ScadViewerDoc.h"
#include "ScadViewerFrm.h"
#include "resource.h"
#include "View3DBox.h"
#include "Timer.h"


#include "DibGlRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*
static const SViewOptions DefaultViewOptions =
{
	1,          // Line width
    //********* Colors ************
    clRed,      // Bar color
	clNavy,     // Element border color
	clWhite,    // Background color
	clGreen,    // Node color
    clSilver,   // Plate color
    clSilver,   // Solid element color
    //** Constraint colors ***
	clRed,      // X
	clLime,     // Y
	clBlue,     // Z
	clPurple,   // UX
	clYellow,   // UY
	clFuchsia,  // UZ
    //******************************
	4,          // Node size

	//M_FILL_AND_LINES, // Display mode

	false,	    // OGL10
	false,	    // bLineSmooth
	false,	    // SoftOGL
	false,	    // bRemoveDupPlanes
	true,	    // bDrawOptimize
    600,        // nPrintResolution
    false,      // bPerspective
	true,		// bShowUsedNodes
	// Forum objects colors
	clSilver,	// WallColor
	clSilver,	// SlabColor
	clRed,		// ColumnColor
	clRed,		// BeamColor
	clSilver	// RoofColor

};
*/

/////////////////////////////////////////////////////////////////////////////
// C3DBoxView
IMPLEMENT_DYNCREATE(C3DBoxView, CView)
C3DBoxView::C3DBoxView(void) :
	m_pRenderer(nullptr),
	m_StateBeforeCut(ST_ROTATE),
	//m_DrawMode(M_FILL_AND_LINES),
	State(ST_ROTATE),
	//m_ViewOptions(DefaultViewOptions),
	renderWnd(m_ViewPos, State, m_Cutter),
	m_bDisplayPopupMenu(true)
{
	renderWnd.SetOwnerView(this);
	m_ViewPos.FocusLength = 50;

	//Rot=new CRotator;
	m_ViewPos.ScrScale = 1;
	m_ViewPos.Xorg = 0;
	m_ViewPos.Yorg = 0;
	m_ViewPos.bPerspective = false;
	m_ViewPos.Rot = &Rot;
	m_pRenderer = new CGLRenderer(m_ViewPos);
	//EraseBackground = true;
	//NeedRefresh = true;
}

C3DBoxView::~C3DBoxView(void)
{
	delete m_pRenderer;
}

BEGIN_MESSAGE_MAP(C3DBoxView, CView)
//{{AFX_MSG_MAP(C3DBoxView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////

// C3DBoxView drawing
void C3DBoxView::OnDraw(CDC *pDC)
{
	CTimer Timer;
	Timer.Start();
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*Geometry = pDoc ? pDoc->m_pViewGeometry : nullptr;
	if(Geometry == nullptr)
		return;

	Geometry->Render(m_pRenderer,&m_ViewOptions, &m_DrawOptions);

	// Swap buffers
	if (!pDC->IsPrinting())
		m_pRenderer->SwapBuffers();
	m_strFps.Format(_T("  (%.1f fps)"), 1/Timer.Stop());

}

void C3DBoxView::Redraw(BOOL bSwap)
{
	CTimer Timer;
	Timer.Start();
	CDC *pDC=GetDC(); 
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*Geometry = pDoc->m_pViewGeometry;
	if(Geometry == nullptr)
		return;

	Geometry->Render(m_pRenderer,&m_ViewOptions, &m_DrawOptions);

	// Swap buffers
	if (!pDC->IsPrinting() && bSwap)
		m_pRenderer->SwapBuffers();
	ReleaseDC(pDC);
	m_strFps.Format(_T("  (%.1f fps)"), 1/Timer.Stop());
}


/////////////////////////////////////////////////////////////////////////////
// C3DBoxView diagnostics
#ifdef _DEBUG
void C3DBoxView::AssertValid(void) const
{
	CView::AssertValid();
}

void C3DBoxView::Dump(CDumpContext &dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

// C3DBoxView message handlers
int C3DBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	RebindGL();
	//JustCreated = true;

	return 0;
}

void C3DBoxView::OnDestroy(void)
{
	m_pRenderer->ReleaseWindow();
	CView::OnDestroy();
}




void C3DBoxView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	renderWnd.MoveWindow(0,0,cx,cy);
	if(cx<=0 || cy<=0)
		return;

	ClientWidth = cx;
	ClientHeight = cy;
	ResizeView(cx, cy, min(cx, cy) / 10);
}

BOOL C3DBoxView::OnEraseBkgnd(CDC *pDC)
{
	if(GetDocument()&& static_cast<CScadViewerDoc *>(GetDocument())->m_pViewGeometry == nullptr)
		return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

//---------------------------------------------------------------------------
void C3DBoxView::Zoom(FLOAT_TYPE S)
{
	m_ViewPos.ScrScale *= S;

	m_ViewPos.ViewSizeX /= S;
	m_ViewPos.ViewSizeY /= S;
	m_ViewPos.TargetDist /= S;

	//if (FOnRepaint)
	//	FOnRepaint(this);
	Invalidate();
}



#define M_PI_2	(3.1415926f / 2)
static inline FLOAT_TYPE RadToDeg(FLOAT_TYPE x)
{
	return x * 90 / M_PI_2;
}



void C3DBoxView::ZoomAll(S3DBox *Box, int Border)
{
	CRect	clr;
	GetClientRect(&clr);
	//ViewBox = *Box;

	m_ViewPos.GeometryZoomAll(&clr, Border, Box);
	
	m_ViewPos.ViewSizeX = Box->x_max - Box->x_min;
	m_ViewPos.ViewSizeY = Box->y_max - Box->y_min;

	FLOAT_TYPE
		Asp = FLOAT_TYPE(ClientWidth) / ClientHeight,
		t1,
		t2,
		cy =(FLOAT_TYPE(ClientHeight)+Border)/ClientHeight,
		cx =(FLOAT_TYPE(ClientWidth)+Border)/ClientWidth;
	const FLOAT_TYPE c_fltFrameHeight = 24;
	if(Asp > 1)
	{
		t1 = m_ViewPos.FocusLength / c_fltFrameHeight * cy * m_ViewPos.ViewSizeY + (Box->z_max - Box->z_min) / 2;
		t2 = m_ViewPos.FocusLength / (c_fltFrameHeight * Asp) * cx * m_ViewPos.ViewSizeX + (Box->z_max - Box->z_min) / 2;
	}
	else
	{
		t1 = m_ViewPos.FocusLength / (c_fltFrameHeight / Asp) * cy * m_ViewPos.ViewSizeY + (Box->z_max - Box->z_min) / 2;
		t2 = m_ViewPos.FocusLength / c_fltFrameHeight * cx * m_ViewPos.ViewSizeX + (Box->z_max - Box->z_min) / 2;
	}

	m_ViewPos.TargetDist = max(t1, t2);
}



void C3DBoxView::ResizeView(int Width, int Height, int Border)
{
	m_pRenderer->SetViewportSize(Width, Height);

	int clw = Width - Border, clh = Height - Border;
	if((m_ViewPos.ViewSizeX == 0))
		m_ViewPos.ViewSizeX = 1;
	if((m_ViewPos.ViewSizeY == 0))
		m_ViewPos.ViewSizeY = 1;

	FLOAT_TYPE	SclX = clw / m_ViewPos.ViewSizeX, SclY = clh / m_ViewPos.ViewSizeY;
	FLOAT_TYPE	SclF = (SclX < SclY) ? SclX : SclY;
	OldScrScale = m_ViewPos.ScrScale;
	m_ViewPos.ScrScale = SclF;
}

void C3DBoxView::RestoreView(void)
{
	m_pRenderer->SetViewportSize(ClientWidth, ClientHeight);
	m_ViewPos.ScrScale = OldScrScale;
}


void C3DBoxView::RebindGL(void)
{
	if (renderWnd.m_hWnd!=nullptr)
	{
		m_pRenderer->ReleaseWindow();
		renderWnd.DestroyWindow();
	}
	CRect rcClient;
	GetClientRect(&rcClient);
	renderWnd.Create(AfxRegisterWndClass(CS_DBLCLKS),_T(""),WS_CHILD | WS_VISIBLE,rcClient,this,0);
	m_pRenderer->BindWindow(renderWnd.m_hWnd, m_ViewOptions.SoftOGL, m_DrawOptions.arrLogFonts);
}

/*
void C3DBoxView::SetSoftOGL(bool value)
{
	bSoftOGL = value;
}
*/

void C3DBoxView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	m_Cutter.SetGeomAddr(&(pDoc->m_pViewGeometry));
	Invalidate();
}

void C3DBoxView::OnInitialUpdate(void)
{
	CView::OnInitialUpdate();
	extern SCDefProjType ThumbProjection;
	// ReSharper disable once CppLocalVariableMightNotBeInitialized
	Rot.SetPredefinedView(ThumbProjection);
	m_Cutter.FreeCutChain();
	ZoomAll();
}

void C3DBoxView::ZoomAll(void)
{
	S3DBox			Box;
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*Geometry = pDoc? pDoc->m_pViewGeometry : nullptr;

	if(Geometry == nullptr)
		return;
	Geometry->Get3DBox(&Rot, &Box);
	Geometry->Get3DBox(nullptr, &Geometry->m_FragmentBox);
	ZoomAll(&Box, min(ClientWidth, ClientHeight) / 10);
	Invalidate();
}



void C3DBoxView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if (!m_pRenderer)
		return;
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*Geometry = pDoc->m_pViewGeometry;
	if(Geometry == nullptr)
		return;

	FLOAT_TYPE fLineScale = 1;
	CDibGlRenderer rend(Geometry, m_ViewPos);
	rend.OnBeforePrint(pDC, pInfo, this, pDoc->GetPathName(), fLineScale);
	rend.BuildAllFonts(m_DrawOptions.arrLogFonts,fLineScale);
	SViewOptions sPrintViewOptions = SViewOptions(m_ViewOptions);
	sPrintViewOptions.LineWidth = int(sPrintViewOptions.LineWidth*fLineScale+0.5f);
	sPrintViewOptions.NodeSize = int(sPrintViewOptions.NodeSize*fLineScale+0.5f);
	sPrintViewOptions.BackgroundColor = clWhite;
	rend.Render(Geometry,&sPrintViewOptions, &m_DrawOptions);
	rend.OnAfterPrint(pDC);
	m_pRenderer->BuildAllFonts(nullptr);
	GetParentFrame()->EnableWindow();
}

BOOL C3DBoxView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	pInfo->SetMaxPage(1);
	pInfo->m_pPD->m_pd.Flags |= PD_PRINTSETUP;
	return CView::DoPreparePrinting(pInfo);
}

BOOL C3DBoxView::UpdateSettings(bool bLoad, CString strSubkey)
{
	if (!bLoad)
	{
		m_ViewOptions.bPerspective = m_ViewPos.bPerspective;
	}
	BOOL bResult;
	bResult = m_DrawOptions.UpdateSettings(bLoad, strSubkey+_T("\\DrawOptions"));
	if (!bResult)
		return false;

	bResult = m_ViewOptions.UpdateSettings(bLoad, strSubkey+_T("\\ViewOptions"));
	if (!bResult)
		return false;

	CScadViewerDoc *pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	SetKey(strSubkey);
	if (pDoc)
	{
		UpdateBool(bLoad, _T("ShowProfiles"), &pDoc->m_bShowProfiles, false);
		UpdateBool(bLoad, _T("ShowThickness"), &pDoc->m_bShowPlateThickness, false);
		UpdateInt(bLoad, _T("State"), reinterpret_cast<int *>(&State), ST_ROTATE);
		if (bLoad)
		{
			m_ViewPos.bPerspective = m_ViewOptions.bPerspective;
			UpdateToolbar();
		}
	}
	return TRUE;
}

void C3DBoxView::OnDepthChange(FLOAT_TYPE fNewDepth)
{
	m_DrawOptions.fDepth = fNewDepth;
	Invalidate();

}

void C3DBoxView::SetCamera(int nFocusLength, bool bChangeDistance)
{
	if (bChangeDistance)
	{
		m_ViewPos.TargetDist *= nFocusLength/m_ViewPos.FocusLength;
	}
	m_ViewPos.FocusLength = FLOAT_TYPE(nFocusLength);
	Invalidate();
}

void C3DBoxView::UpdateToolbar() const
{
	CScadViewerFrame *pFrm = reinterpret_cast<CScadViewerFrame *>(GetParent());
	CScadViewerDoc *pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	UINT nBarIndex = pDoc->m_bShowProfiles ? 1 : 0;
	UINT nPlateIndex = pDoc->m_bShowPlateThickness ? 1 : 0;
	if (pDoc->m_bViewResults)
	{
		/*nBarIndex = */nPlateIndex = 0;
	}
	pFrm->SetButtonImage(IDR_FILTERS_TOOLBAR, ID_VIEW_ELEMENTS_BARS, ID_BAR_IMG, nBarIndex);
	pFrm->SetButtonImage(IDR_FILTERS_TOOLBAR, ID_VIEW_ELEMENTS_PLATES, ID_PLATE_IMG,  nPlateIndex);

}

BOOL C3DBoxView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	const FLOAT_TYPE c_fScalingFactor = 1.3f;

	FLOAT_TYPE	S = (zDelta > 0) ? c_fScalingFactor : 1 /  c_fScalingFactor;
	CRect	clr;
	GetClientRect(clr);
	ClientToScreen(clr);
	if (!clr.PtInRect(pt))
		return FALSE;
	CPoint ptCenter = clr.CenterPoint();
	m_ViewPos.Xorg -= (ptCenter.x - pt.x)/m_ViewPos.ScrScale;
	m_ViewPos.Yorg += (ptCenter.y - pt.y)/m_ViewPos.ScrScale;

	m_ViewPos.ScrScale *= S;
	m_ViewPos.Xorg += (ptCenter.x - pt.x)/m_ViewPos.ScrScale;
	m_ViewPos.Yorg -= (ptCenter.y - pt.y)/m_ViewPos.ScrScale;
	m_ViewPos.ViewSizeX /= S;
	m_ViewPos.ViewSizeY /= S;
	m_ViewPos.TargetDist /=  S;


	Invalidate();
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

bool C3DBoxView::Select(CPoint pt)
{
	CScadViewerDoc	*pDoc = static_cast<CScadViewerDoc *>(GetDocument());
	CViewGeometry	*pGeometry = pDoc->m_pViewGeometry;
	if (!pGeometry)
		return FALSE;
	pt.y = ClientHeight - pt.y;
	bool bRes = m_pRenderer->Select(pGeometry,pt, m_DrawOptions.fDepth);
	pGeometry->SetupElementColors(&m_ViewOptions, m_DrawOptions.Mode);
	pGeometry->BuildArrays();
	Invalidate();
	return bRes;
}

void C3DBoxView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	m_pRenderer->BuildAllFonts(m_DrawOptions.arrLogFonts);
	
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);
}
