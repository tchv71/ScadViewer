// ScadViewerDoc.h : interface of the CScadViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCADVIEWERDOC_H__F0ABEA1D_493B_11D5_B1B3_000102C8846A__INCLUDED_)
#define AFX_SCADVIEWERDOC_H__F0ABEA1D_493B_11D5_B1B3_000102C8846A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ViewGeometry.h"

#include "Forum3DView.h"
#ifndef SCAD11
#ifdef SCAD21
#include "SCADAPIX.hxx"
#else
#include "schema.h"
#endif
#else
#include "schema.hpp"
#include "Result.hpp"
//#include "scad.h"
//#include "Grand.h"
#endif
#include "3DIso.hpp"
#include "../OglIso/OglIso.h"


class FORUM3DVIEW_EXPORT CScadViewerDoc : public CDocument
{
protected: // create from serialization only
	CScadViewerDoc();
	DECLARE_DYNCREATE(CScadViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScadViewerDoc)
	public:
	BOOL OnNewDocument() override;
	void Serialize(CArchive& ar) override;
	void DeleteContents() override;
	//}}AFX_VIRTUAL

// Implementation
public:
	void Clear();
	CViewGeometry * m_pViewGeometry;
	virtual ~CScadViewerDoc();
	bool	m_bShowProfiles;
	bool	m_bShowPlateThickness;

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

protected:
	SOglIsoParam m_IsoParams;
	TypeInformationOnSchema m_TypeInfo;
	struct DefMapInfo DMI;
// Generated message map functions
protected:
	void FillScale(DefMapInfo* pDMI) const;
	void FillIsoParams();
	//{{AFX_MSG(CScadViewerDoc)
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnViewResults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void LoadIso();
	bool m_bViewResults;
	SCHEMA *m_pSchem;
	SCHEMA *m_pIsoSchem;
#ifndef SCAD21
	SCHEMA m_Schem;
#endif
	void LoadSchema(SCHEMA *Schem);
	void Load(void);
	CString m_strFileName;
	void SetDocPathName(LPCTSTR strPathName)
	{
		m_strPathName = strPathName;
	}
	friend class CIsoViewerFrame;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCADVIEWERDOC_H__F0ABEA1D_493B_11D5_B1B3_000102C8846A__INCLUDED_)
