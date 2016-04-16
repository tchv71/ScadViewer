// TestMfcView.cpp : implementation of the CTestMfcView class
//

#include "stdafx.h"
#include "TestMfc.h"

#include "TestMfcDoc.h"
#include "TestMfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestMfcView

IMPLEMENT_DYNCREATE(CTestMfcView, CView)

BEGIN_MESSAGE_MAP(CTestMfcView, CView)
	//{{AFX_MSG_MAP(CTestMfcView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMfcView construction/destruction

CTestMfcView::CTestMfcView()
{
	// TODO: add construction code here

}

CTestMfcView::~CTestMfcView()
{
}

BOOL CTestMfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestMfcView drawing

void CTestMfcView::OnDraw(CDC* pDC)
{
	CTestMfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestMfcView printing

BOOL CTestMfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestMfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestMfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestMfcView diagnostics

#ifdef _DEBUG
void CTestMfcView::AssertValid() const
{
	CView::AssertValid();
}

void CTestMfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestMfcDoc* CTestMfcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestMfcDoc)));
	return (CTestMfcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestMfcView message handlers
