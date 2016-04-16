// TestMfcDoc.cpp : implementation of the CTestMfcDoc class
//

#include "stdafx.h"
#include "TestMfc.h"

#include "TestMfcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestMfcDoc

IMPLEMENT_DYNCREATE(CTestMfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestMfcDoc, CDocument)
	//{{AFX_MSG_MAP(CTestMfcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMfcDoc construction/destruction

CTestMfcDoc::CTestMfcDoc()
{
	// TODO: add one-time construction code here

}

CTestMfcDoc::~CTestMfcDoc()
{
}

BOOL CTestMfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestMfcDoc serialization

void CTestMfcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestMfcDoc diagnostics

#ifdef _DEBUG
void CTestMfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestMfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestMfcDoc commands
