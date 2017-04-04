// ScadViewerDoc.cpp : implementation of the CScadViewerDoc class
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "resource.h"
#include <shlwapi.h>

#include "ScadViewerDoc.h"

#pragma pack( push, abc, 1)
//#include "GeomStub.h"
//#include ".\scadviewerdoc.h"
#include "ForumViewGeometry.h"
#include "IsoViewGeometry.h"
#include "ScadViewerView.h"
#include "IsoViewerFrame.h"
#include "3DIso.hpp"
#pragma pack(pop, abc)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScadViewerDoc

IMPLEMENT_DYNCREATE(CScadViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CScadViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CScadViewerDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_VIEW_RESULTS, OnViewResults)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScadViewerDoc construction/destruction

CScadViewerDoc::CScadViewerDoc() :
	m_pViewGeometry(nullptr),
	m_bShowProfiles(true),
	m_bShowPlateThickness(true),
	m_bViewResults(false),
	m_pSchem(nullptr),
	m_pIsoSchem(nullptr)
{
	memset(&DMI, 0 , sizeof(DMI));
	m_IsoParams.pDMI = &DMI;

}

#define FREE(x) delete x; (x) = nullptr

void CScadViewerDoc::Clear()
{
	FREE(m_pViewGeometry);
	FREE(m_IsoParams.Res);
	FREE(m_IsoParams.pTypeInfo);
#ifdef SCAD21
	if (m_pIsoSchem)
	{
		ApiRelease(&m_pIsoSchem);
		m_pIsoSchem = nullptr;
	}
#endif
}	



CScadViewerDoc::~CScadViewerDoc()
{
	Clear();
}

BOOL CScadViewerDoc::OnNewDocument()
{
	m_strFileName.Empty();
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CScadViewerDoc serialization

void CScadViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		CString strNewPath = ar.GetFile()->GetFilePath();
		ar.GetFile()->Close();
		::CopyFile(GetPathName(), strNewPath, FALSE);
	}
	else
	{
		m_strFileName = ar.GetFile()->GetFilePath();
		Load();
	}
}
void CScadViewerDoc::Load(void)
{
/*
 		TGeometry *Geom = GetGeometry((char *)LPCSTR(strFileName), false, false);
		m_pViewGeometry = new TViewGeometry(Geom);
		FreeGeometry(Geom);
*/
	
	if (m_strFileName.IsEmpty() && m_pSchem== nullptr)
		return;
	CWaitCursor crWait;
	if (_tcsicmp(PathFindExtension(m_strFileName),_T(".mp4"))==0)
	{
		//UpdateAllViews(nullptr);
		return;
	}
	if (m_bViewResults)
	{
		LoadIso();
		return;
	}
	POSITION pos = GetFirstViewPosition();
	CScadViewerView *pView = static_cast<CScadViewerView *>(GetNextView(pos));
	ASSERT_KINDOF(CScadViewerView, pView);
	Clear();
	m_pViewGeometry = new CForumViewGeometry(&pView->m_ViewOptions,&pView->m_DrawOptions);
	m_pViewGeometry->m_bDeleteInnerPlates = pView->m_ViewOptions.bRemoveDupPlanes;
	bool bOptimize = pView->m_ViewOptions.bDrawOptimize | pView->m_ViewOptions.bRemoveDupPlanes;

	if (!m_strFileName.IsEmpty())
		m_pViewGeometry->LoadFromFile(m_strFileName, m_bShowProfiles,
			m_bShowPlateThickness, bOptimize);
	else
		m_pViewGeometry->LoadFromSchema(m_pSchem, m_bShowProfiles, m_bShowPlateThickness, bOptimize);
				
	UpdateAllViews(nullptr);
}

void CScadViewerDoc::LoadSchema(SCHEMA *Schem)
{
	m_pSchem = Schem;
	Load();
}


/////////////////////////////////////////////////////////////////////////////
// CScadViewerDoc diagnostics

#ifdef _DEBUG
void CScadViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScadViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScadViewerDoc commands





void CScadViewerDoc::DeleteContents() 
{
	Clear();
	m_strFileName.Empty();
	
	CDocument::DeleteContents();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void CScadViewerDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetPathName().IsEmpty());
}

void CScadViewerDoc::OnViewResults() 
{
	m_bViewResults = !m_bViewResults;
	POSITION pos = GetFirstViewPosition();
	CScadViewerView *pView = static_cast<CScadViewerView *>(GetNextView(pos));
	ASSERT_KINDOF(CScadViewerView, pView);
	pView->ReloadDoc();
	pView->UpdateToolbar();
}


void CScadViewerDoc::LoadIso()
{

	CIsoViewGeometry *pGeom = static_cast<CIsoViewGeometry *>(m_pViewGeometry);
	if(m_pSchem)
	{
		POSITION pos = GetFirstViewPosition();
		CScadViewerView *pView = static_cast<CScadViewerView *>(GetNextView(pos));
		ASSERT_KINDOF(CScadViewerView, pView);
		pGeom->LoadIso(m_bShowProfiles, pView->m_ViewOptions.bDrawOptimize);
		if (m_bViewResults)
		{
			CIsoViewerFrame *pFrame = static_cast<CIsoViewerFrame *>(pView->GetParentFrame());
			pFrame->OnViewNewResults();
		}
		return;
	}
	POSITION pos = GetFirstViewPosition();
	CScadViewerView *pView = static_cast<CScadViewerView *>(GetNextView(pos));
	ASSERT_KINDOF(CScadViewerView, pView);
	Clear();
	m_IsoParams.pTypeInfo = new TypeInformationOnSchema;
	m_pViewGeometry = pGeom = new CIsoViewGeometry(static_cast<CIsoViewerFrame*>(pView->GetParentFrame()),&pView->m_ViewOptions,&pView->m_DrawOptions);
	m_pViewGeometry->m_bDeleteInnerPlates = pView->m_ViewOptions.bRemoveDupPlanes;
	bool bOptimize = pView->m_ViewOptions.bDrawOptimize | pView->m_ViewOptions.bRemoveDupPlanes;

#ifdef SCAD21
	SCHEMA *pSchem = nullptr;
	ApiCreate(&pSchem);
	m_pIsoSchem = pSchem;
#else
	SCHEMA m_Schem;
	SCHEMA *pSchem = &m_Schem;
#endif
	if (!m_strFileName.IsEmpty())
		m_pViewGeometry->LoadFromFile(m_strFileName, m_bShowProfiles,
			m_bShowPlateThickness, bOptimize, &pSchem);
	else
		m_pViewGeometry->LoadFromSchema(pSchem, m_bShowProfiles, m_bShowPlateThickness, bOptimize);
#ifdef SCAD21
	m_IsoParams.hAPI = pSchem;
	UnitsAPI theUnits[3] =
	{
		{"mm", 1000	},
		{"T",1},
		{"m",1}
	};
	if (ApiInitResult(pSchem, theUnits, "C:\\SWORK")!=APICode_OK )//|| !ApiYesDisplace(pSchem))
	{
		m_bViewResults = false;
		Load();
		return;
	}
#else
	m_IsoParams.Res = new RESULT;
	UNITS theUnits[3] =
	{
		{"mm", 1000	},
		{"T",1},
		{"m",1}
	};
	int nRes = m_IsoParams.Res->Init(*pSchem, theUnits, nullptr);
	if (nRes != 0)
	{
		m_bViewResults = false;
		Load();
		return;
	}
#endif
	//BOOL bRes = ApiYesDisplace(pSchem);
	m_IsoParams.NPr = 0;
	m_IsoParams.nTypeFactor = 0;
	m_IsoParams.nTypeData = Iso_Disp;
	m_IsoParams.bDrawIsoLines = false;
	m_IsoParams.bDrawEggs = false;
	FillIsoParams();
	pGeom->SetParams(&m_IsoParams);
	pGeom->LoadIso(m_bShowProfiles, pView->m_ViewOptions.bDrawOptimize);
	UpdateAllViews(nullptr);
	if (m_bViewResults)
	{
		CIsoViewerFrame *pFrame = static_cast<CIsoViewerFrame *>(pView->GetParentFrame());
		pFrame->OnViewNewResults();
	}
}


static struct DefMapInfo DefDMI=
{
	3,					//short Scale_count;
	0.2,				//double Max
	-0.2,				//doublr Min
	0.2,					//double Step;
	{-0.2,-0.1,0},			//double binter[41];
	{-0.1,0,0.2},			//double einter[41];
	{0},					//double DopArmB[41];
	{0},					//double DopArmE[41];
	{1,1,1},				//char IsDrw[41];
	{clRed, clGreen, clBlue},		//COLORREF col[41];
	0,					//double Zero;
	{0},					//int x[41];
	{0},					//int y[41];
	"Test"				//char Caption[8192];
						//BYTE	LastOp;    // 1 - IsoLines 0 - IsoArea or Map
						//BYTE	IsDopArm;
						//BYTE IsSetScale;
};

struct TypeInformationOnSchema DefTypeInfo =
{
	0,	//	BYTE NumFactor; // Оцифровка фактора
	0,	//	BYTE NumElem;   // Нумерация элементов
	0,	//	BYTE NumNode;   // Нумерация узлов
	1,	//	BYTE OutSupport;// Отображение связей
	1	//BYTE OutNode;   // Отображение узлов
};

void CScadViewerDoc::FillIsoParams()
{
	*(m_IsoParams.pTypeInfo) = DefTypeInfo;
	FillScale(&DMI);	
}

void CScadViewerDoc::FillScale(DefMapInfo *pDMI) const
{
	//*pDMI = DefDMI;
	pDMI->Scale_count = 14;
	(static_cast<CIsoViewGeometry *>(m_pViewGeometry))->SetDefMapInfo(pDMI, &m_IsoParams);
	
}

