// Mp4View.cpp : implementation of the CMp4View class
//

#include "stdafx.h"
//#include "Mp4PlayerMFC.h"
#include "Mp4View.h"
#include "ScadViewerDoc.h"
#include <shlwapi.h>
#include "DibGlRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMp4View

IMPLEMENT_DYNCREATE(CMp4View, CScadViewerView)

BEGIN_MESSAGE_MAP(CMp4View, CScadViewerView)
	//{{AFX_MSG_MAP(CMp4View)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	//ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	//ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//ON_COMMAND(ID_FILE_PLAY, OnFilePlay)
	//ON_COMMAND(ID_FILE_STOP, OnFileStop)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMp4View construction/destruction

CMp4View::CMp4View() :
	CScadViewerView(),
	m_pDSMP4(nullptr),
	m_p3DView(nullptr),
	m_bShowMp4(false)
{
	//{{AFX_DATA_INIT(CMp4View)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMp4View::~CMp4View()
{
	if (m_pDSMP4)
		m_pDSMP4->Release();
	m_pDSMP4 = nullptr;
}

void CMp4View::OnFileNew()
{
	OnFileStop();

	m_pDSMP4->Close();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMp4View::OnFilePlay()
{
	m_pDSMP4->Play();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CMp4View::OnFileStop()
{
	m_pDSMP4->Stop();
}

void CMp4View::OnClose()
{
	OnFileNew();
}

/*
void CMp4View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMp4View)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
*/
BOOL CMp4View::PreCreateWindow(CREATESTRUCT& cs)
{
	//m_pMainWnd = pFrame;
	//HRESULT hr;

	return CScadViewerView::PreCreateWindow(cs);
}

void CMp4View::OnInitialUpdate()
{
	CScadViewerView::OnInitialUpdate();
	//GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();

	//GetDlgItem(IDC_STATIC_COMPOSITOR, theApp.CompositorWindow());
	//*theApp.CompositorWindow() = m_hWnd;
}

void CMp4View::OnUpdate(CView * pSender, LPARAM lHint, CObject* pHint) 
{
	CScadViewerView::OnUpdate(pSender, lHint, pHint);	
	if(!GetDocument() || GetDocument()->m_strFileName.IsEmpty()) 
		return;
	if(!GetDocument()|| (GetDocument()->m_strFileName.IsEmpty() ||
		_tcsicmp(PathFindExtension(GetDocument()->m_strFileName),_T(".mp4"))!=0))
	{
		RebindGL();
		m_bShowMp4 = false;
		return;
	}
	//if (!m_bShowMp4)
	if (m_pDSMP4)
		m_pDSMP4->Release();
	HRESULT hr;
	CLSID clsid;
	::CLSIDFromProgID(L"SeeStorm.DSMP4", &clsid);
	hr = ::CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IDSMP4), reinterpret_cast<void**>(&m_pDSMP4));
	if (FAILED(hr))
		return;
	{
		if (renderWnd.m_hWnd!=nullptr)
			{
				m_pRenderer->ReleaseWindow();
				renderWnd.DestroyWindow();
			}
		CRect rcClient;
		GetClientRect(&rcClient);
		renderWnd.Create(AfxRegisterWndClass(CS_DBLCLKS),_T(""),WS_CHILD | WS_VISIBLE,rcClient,this,0);
		m_pDSMP4->put_HWndParent(long(renderWnd.GetSafeHwnd()));
		m_pDSMP4->QueryInterface(__uuidof(I3DView), reinterpret_cast<void**>(&m_p3DView));
		m_bShowMp4 = true;
	}
	LPCTSTR szFileName = GetDocument()? GetDocument()->m_strFileName: _T("");

	CWaitCursor wc;

	OnFileNew();

	_bstr_t bs(szFileName);
	m_pDSMP4->Open(bs);

	OnFilePlay();

	C3DBoxView::OnUpdate(pSender, lHint, pHint);
}

BOOL CMp4View::OnEraseBkgnd(CDC *pDC)
{
	if(!GetDocument()->m_strFileName.IsEmpty() && _tcsicmp(PathFindExtension(GetDocument()->m_strFileName),_T(".mp4"))==0)
		return TRUE;
	if(GetDocument()&& static_cast<CScadViewerDoc *>(GetDocument())->m_pViewGeometry == nullptr )
		return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMp4View printing
/*
BOOL CMp4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMp4View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}

void CMp4View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}

void CMp4View::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
}

  */
/////////////////////////////////////////////////////////////////////////////
// CMp4View diagnostics

#ifdef _DEBUG
void CMp4View::AssertValid() const
{
	CScadViewerView::AssertValid();
}

void CMp4View::Dump(CDumpContext& dc) const
{
	CScadViewerView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMp4View message handlers

void CMp4View::OnSize(UINT nType, int cx, int cy) 
{
	CScadViewerView::OnSize(nType, cx, cy);
	/*
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_COMPOSITOR);
	if(!pStatic)
		return;

	RECT rect;
	GetClientRect(&rect);
	pStatic->MoveWindow(0, 0, rect.right, rect.bottom);

	CWnd* pwnd = pStatic->GetWindow(GW_CHILD);
	if(pwnd)
		pwnd->MoveWindow(0, 0, rect.right, rect.bottom);
		*/
}


void CMp4View::ZoomAll(void)
{
	if (!m_bShowMp4)
	{
		CScadViewerView::ZoomAll();
		return;
	}
	if (m_p3DView)
		m_p3DView->ZoomAll();
}

void CMp4View::Redraw(BOOL bSwap)
{
	if (!m_bShowMp4)
	{
		CScadViewerView::Redraw(bSwap);
		return;
	}
	if (m_p3DView)
		m_p3DView->Redraw();
}

void CMp4View::EnablePopupMenu(bool bEnable)
{
	if (!m_bShowMp4)
	{
		CScadViewerView::EnablePopupMenu(bEnable);
		return;
	}
	if (m_p3DView)
		m_p3DView->put_PopupNenu_Enabled(BOOL(bEnable));
}

TV3DBState CMp4View::GetStateBeforeCut()
{
	if (!m_bShowMp4)
		return CScadViewerView::GetStateBeforeCut();
	long res = FALSE;
	if (m_p3DView)
		m_p3DView->get_StateBeforeCut(&res);
	return TV3DBState(res);
}

bool CMp4View::Select(CPoint pt)
{
	if (!m_bShowMp4)
		return CScadViewerView::Select(pt);
	HRESULT hr = S_OK;
	if (m_p3DView)
		hr = m_p3DView->Select(pt.x, pt.y);
	return (hr==S_OK);
}


//DEL BOOL CMp4View::OnEraseBkgnd(CDC* pDC) 
//DEL {
//DEL 	return CFormView::OnEraseBkgnd(pDC);//FALSE; //TRUE;
//DEL }


