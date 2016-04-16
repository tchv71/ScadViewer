// TestMfcDoc.h : interface of the CTestMfcDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMFCDOC_H__8812D0CF_EA5D_40E6_B5B5_1F2B9878C27F__INCLUDED_)
#define AFX_TESTMFCDOC_H__8812D0CF_EA5D_40E6_B5B5_1F2B9878C27F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestMfcDoc : public CDocument
{
protected: // create from serialization only
	CTestMfcDoc();
	DECLARE_DYNCREATE(CTestMfcDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMfcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestMfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestMfcDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMFCDOC_H__8812D0CF_EA5D_40E6_B5B5_1F2B9878C27F__INCLUDED_)
