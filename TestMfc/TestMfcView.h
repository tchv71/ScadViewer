// TestMfcView.h : interface of the CTestMfcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMFCVIEW_H__B87276CD_3F0D_4974_B089_467C4DFBA072__INCLUDED_)
#define AFX_TESTMFCVIEW_H__B87276CD_3F0D_4974_B089_467C4DFBA072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestMfcView : public CView
{
protected: // create from serialization only
	CTestMfcView();
	DECLARE_DYNCREATE(CTestMfcView)

// Attributes
public:
	CTestMfcDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMfcView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestMfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestMfcView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestMfcView.cpp
inline CTestMfcDoc* CTestMfcView::GetDocument()
   { return (CTestMfcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMFCVIEW_H__B87276CD_3F0D_4974_B089_467C4DFBA072__INCLUDED_)
