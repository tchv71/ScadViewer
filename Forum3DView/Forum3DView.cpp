// Forum3DView.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <shlwapi.h>
#ifndef SCAD11
#ifdef SCAD21
#include "SCADAPIX.hxx"
#else
#include "schema.h"
#endif
#else
#include "schema.hpp"
#endif
#include "Forum3DView.h"
#include "ScadViewerFrm.h"
#include "ScadViewerDoc.h"
#include "ForumViewGeometry.h"
#include "SettingManager.h"

#ifdef SCAD11
#include "Result.hpp"
//#include "Grand.h"
#endif
#ifdef SCAD21
//#include "../../Scad11/include/RESULT.HPP"
#endif
#include "../OglIso/OglIso.h"
#include "IsoViewGeometry.h"
#include "IsoViewerFrame.h"
#include "ScadViewerView.h"
#include "resource.h"
#include "ThumbCashe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef MAXPATH
#define MAXPATH  _MAX_PATH
#endif


static AFX_EXTENSION_MODULE Forum3DViewDLL = { NULL, nullptr };
//static AFX_EXTENSION_MODULE Forum3DViewRES = { NULL, NULL };

int nLangID;
HINSTANCE m_hResDLL = nullptr;


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("FORUM3DVIEW.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(Forum3DViewDLL, hInstance))
			return 0;
		//HINSTANCE hInst = LoadLibrary("ForumView_ENG.DLL");

		//if (!AfxInitExtensionModule(Forum3DViewRES, hInst))
		//	return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(Forum3DViewDLL);
		//new CDynLinkLibrary(Forum3DViewRES);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		::FreeLibrary(m_hResDLL);
		TRACE0("FORUM3DVIEW.DLL Terminating!\n");
		// Terminate the library before destructors are called
		//AfxTermExtensionModule(Forum3DViewRES);
		AfxTermExtensionModule(Forum3DViewDLL);
	}
	return 1;   // ok
}


void FORUM3DVIEW_EXPORT LoadLanguage(int nNewLangID)
{
	nLangID = nNewLangID;
	if (m_hResDLL)
		::FreeLibrary(m_hResDLL);
	switch (nLangID)
	{
	case 1033:
#ifdef SCAD11
		m_hResDLL = ::LoadLibrary(_T("ForumView11_ENG.DLL"));
#else
#ifdef SCAD21
		m_hResDLL = ::LoadLibrary(_T("ForumView21_ENG.DLL"));
#else
		m_hResDLL = ::LoadLibrary(_T("ForumView_ENG.DLL"));
#endif
#endif
		break;
	case 1049:
#ifdef SCAD11
		m_hResDLL = ::LoadLibrary(_T("ForumView11_RUS.DLL"));
#else
#ifdef SCAD21
		m_hResDLL = ::LoadLibrary(_T("ForumView21_RUS.DLL"));
#else
		m_hResDLL = ::LoadLibrary(_T("ForumView_RUS.DLL"));
#endif
#endif
		break;
	default:
		ASSERT(FALSE);
	}
	if (!m_hResDLL)
		AfxMessageBox(_T("Can't load resource DLL"),MB_OK | MB_ICONERROR);
	else
		AfxSetResourceHandle(m_hResDLL);
}

class CFakeWinApp
{
public:
	CFakeWinApp() : m_pApp(nullptr) {};
	void Init()
	{
		if (!AfxGetApp())
		{
			m_pApp = new CWinAppEx;
			AfxWinInit(GetModuleHandle(nullptr), nullptr, nullptr, 0);
		}

	}
	~CFakeWinApp()
	{
		delete m_pApp;
	}
	CWinApp *m_pApp;

} theFakeApp;


void FORUM3DVIEW_EXPORT __cdecl Scad3DView(SCHEMA *Prj,LPCSTR strPath,HWND hWnd)
{
	CWnd wnd;
/*
	if (!theApp.m_hInstance)
	{
		AfxWinInit(GetModuleHandle(NULL), NULL, NULL, 0);
	}
*/
	theFakeApp.Init();
	wnd.Attach(hWnd);
	Forum3DView(Prj, CString(strPath), &wnd);
	wnd.Detach();
}

void FORUM3DVIEW_EXPORT __cdecl Forum3DView(SCHEMA *Prj,CString PathToFile,CWnd *p_hWnd)
{

	CWinApp &theApp = *AfxGetApp();
	p_hWnd->EnableWindow(FALSE);
	LPCTSTR pszOldRegistryKey = theApp.m_pszRegistryKey;
	LPCTSTR pszOldProfileName = theApp.m_pszProfileName;
	theApp.m_pszProfileName = _T("ForumViewDll");
	theApp.m_pszRegistryKey = _T("Scad Soft");
	CSettingManager sm;
	sm.SetKey(_T(""));
	sm.UpdateInt(true, _T("Language"), &nLangID, 1049);
	HINSTANCE hOldResInst = AfxGetResourceHandle();
	LoadLanguage(nLangID);

	CScadViewerFrame * p3DFrame = static_cast<CScadViewerFrame*>(RUNTIME_CLASS( CScadViewerFrame )->CreateObject());
	theApp.m_pMainWnd = p3DFrame;
	//CRect r( 0, 0, 10, 10 );
	//BOOL bCreateRes = p3DFrame->Create( NULL, PathToFile, WS_OVERLAPPEDWINDOW | WS_POPUPWINDOW, r, p_hWnd);
	//

	//if(!bCreateRes )
	//	return;


	CScadViewerDoc *pDoc = static_cast<CScadViewerDoc *>(RUNTIME_CLASS(CScadViewerDoc)->CreateObject());
	p3DFrame->LoadFrame(IDR_MAINFRAME);
	pDoc->AddView(p3DFrame->GetActiveView());
	//p3DFrame->SetWindowPos( NULL, 0, 0, 800, 600, SWP_NOOWNERZORDER);
	bool bFrameClosed = false;
	p3DFrame->SetCloseFlag(&bFrameClosed);

	pDoc->SetPathName(PathToFile, FALSE);
	p3DFrame->ActivateFrame();
	pDoc->LoadSchema(Prj);
	p3DFrame->GetActiveView()->OnInitialUpdate();
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;
	MSG msgCur;
	while (!bFrameClosed)
	{
		// phase1: check to see if we can do idle work
		while (bIdle &&
			!::PeekMessage(&msgCur, nullptr, NULL, NULL, PM_NOREMOVE))
		{
			// call OnIdle while in bIdle state
			if (!theApp.OnIdle(lIdleCount++))
				bIdle = FALSE; // assume "no idle" state
		}

		// phase2: pump messages while available
		do
		{
			// pump message, but quit on WM_QUIT
			if (!theApp.PumpMessage())
			{
				goto Exit;
			}

			// reset "no idle" state after pumping "normal" message
			if (theApp.IsIdleMessage(&msgCur))
			{
				bIdle = TRUE;
				lIdleCount = 0;
			}

		} while (::PeekMessage(&msgCur, nullptr, NULL, NULL, PM_NOREMOVE));
	}
Exit:
	sm.UpdateInt(false, _T("Language"), &nLangID, 1049);
	theApp.ExitInstance();
	theApp.m_pszProfileName = pszOldProfileName;
	theApp.m_pszRegistryKey = pszOldRegistryKey;
	AfxSetResourceHandle(hOldResInst);
	p_hWnd->EnableWindow(TRUE);
	::SetActiveWindow(p_hWnd->m_hWnd);
	
}


#define TO_SCR_X(x) int(cx + ((x) - View.Xorg) * View.ScrScale)
#define TO_SCR_Y(x) int(cy - ((x) - View.Yorg) * View.ScrScale)

SCDefProjType ThumbProjection = DPT_Dimetry;

FORUM3DVIEW_EXPORT BOOL __stdcall SCForumMdl3DDraw( HDC hDC, const RECT * r, LPCTSTR sFileName, LPCTSTR sWorkDir, int nDrawFlags, HANDLE hStopEvent )
{
	S3DBox			Box;
	SParallelView			View;
	CRotator		Rot;
	CRect			Region(r);

	TCHAR Path[MAXPATH];
	_tcscpy_s(Path, sFileName);
	PathRemoveFileSpec(Path);
	CThumbCashe cashe(Path);
	SThumbParam param;
	param.nWidth = WORD(r->right-r->left);
	param.nHeight = WORD(r->bottom-r->top);
	param.eType = ThumbProjection;
	if (cashe.Get(PathFindFileName(sFileName), param, hDC))
		return TRUE;
	
	if (_tcsicmp(PathFindExtension(sFileName),_T(".mp4"))==0)
	{
		return FALSE;
	}
	CForumViewGeometry fvg(nullptr,nullptr);
	fvg.m_bForThumbs = true;
	fvg.m_bDeleteInnerPlates = false;
	if(!fvg.LoadFromFile(sFileName, 0, 0, false))
		return FALSE;
	//fvg.ClearCashe();
	fvg.DrawOptionsChanged(nullptr, true); // Show only used nodes
	Rot.SetPredefinedView(ThumbProjection);
	fvg.Get3DBox(&Rot, &Box);
	View.GeometryZoomAll(&Region, 5, &Box);

	Graphics::TColor	cOld = TColor(0);
	HPEN				hPen, hPenOld;

	hPen = CreatePen(PS_SOLID, 0, cOld);
	hPenOld = HPEN(SelectObject(hDC, hPen));

	int cx = (Region.left + Region.right) / 2, cy = (Region.top + Region.bottom) / 2;
	size_t NumElements = fvg.ElementArray.size();
	for(size_t i = 0; i < NumElements /*&& !Terminated*/; i++)
	{
		//int Percent = (k) * 100.0 / nFiles + (i + 1) * 100.0 / (2 * nFiles * NumElements);

		if (::WaitForSingleObject(hStopEvent,0) == WAIT_OBJECT_0)
		{
			::SetEvent(hStopEvent);
			SelectObject(hDC, hPenOld);
			DeleteObject(hPen);
			return FALSE;
		}
		CViewElement		El = fvg.ElementArray[i];
		Graphics::TColor	c = El.Color;

		if(c != cOld)
		{
			SelectObject(hDC, hPenOld);
			DeleteObject(hPen);
			hPen = CreatePen(PS_SOLID, 0, c);
			hPenOld = HPEN(SelectObject(hDC, hPen));
		}

		int				NumPoints = El.NumVertexs();
		if (!El.bContoured)
			continue;
		NODE_NUM_TYPE pn0 = El.Points[0];
		S3dPoint		p1 = S3dPoint(fvg.VertexArray[pn0]);
		Rot.Rotate(p1.x, p1.y, p1.z);
		MoveToEx(hDC, TO_SCR_X(p1.x), TO_SCR_Y(p1.y), nullptr);
		for(int j = 1; j < NumPoints; j++)
		{
			NODE_NUM_TYPE	pn = El.Points[j];
			S3dPoint		p = S3dPoint(fvg.VertexArray[pn]);
			Rot.Rotate(p.x, p.y, p.z);
//			if(!fvg.WasDrawed(pn1, pn))
				LineTo(hDC, TO_SCR_X(p.x), TO_SCR_Y(p.y));
/*
			else
				MoveToEx(hDC, TO_SCR_X(p.x), TO_SCR_Y(p.y), NULL);
*/
		}

//		if(!fvg.WasDrawed(pn0, pn1))
			LineTo(hDC, TO_SCR_X(p1.x), TO_SCR_Y(p1.y));
	}

	SelectObject(hDC, hPenOld);
	DeleteObject(hPen);
	cashe.Put(PathFindFileName(sFileName), param, hDC);
	
	return TRUE;
}

#if defined(SCAD11) || defined(SCAD21)

void FORUM3DVIEW_EXPORT OglIso3D(SOglIsoParam *pParam)
{
	theFakeApp.Init();
	CWinApp &theApp = *AfxGetApp();
	CWnd wnd;
	wnd.Attach(pParam->hWndParent);
	//CWnd *p_hWnd = &wnd;
	CString PathToFile = pParam->pDMI->Caption;
	//p_hWnd->EnableWindow(FALSE);
//	LPCTSTR pszOldRegistryKey = theApp.m_pszRegistryKey;
//	LPCTSTR pszOldProfileName = theApp.m_pszProfileName;
	free(reinterpret_cast<void*>(const_cast<LPTSTR>(theApp.m_pszRegistryKey)));
	free(reinterpret_cast<void*>(const_cast<LPTSTR>(theApp.m_pszProfileName)));
	theApp.m_pszProfileName = _tcsdup(_T("ForumViewIso"));
	theApp.m_pszRegistryKey =  _tcsdup(_T("Scad Soft"));
	CSettingManager sm;
	sm.SetKey(_T(""));
	sm.UpdateInt(true, _T("Language"), &nLangID, 1049);
	//HINSTANCE hOldResInst = AfxGetResourceHandle();
	LoadLanguage(nLangID);

	CIsoViewerFrame * p3DFrame = static_cast<CIsoViewerFrame*>(RUNTIME_CLASS(CIsoViewerFrame)->CreateObject());

	AfxGetThread()->m_pMainWnd = p3DFrame;

	p3DFrame->m_hWndParent = pParam->hWndParent;

	CScadViewerDoc *pDoc = static_cast<CScadViewerDoc *>(RUNTIME_CLASS(CScadViewerDoc)->CreateObject());
	pDoc->m_bViewResults = TRUE;
	p3DFrame->LoadFrame(IDR_MAINFRAME);
	//p3DFrame->SetWindowPos( NULL, 0, 0, 800, 600, SWP_NOOWNERZORDER);
	bool bFrameClosed = false;
	p3DFrame->SetCloseFlag(&bFrameClosed);
	pDoc->AddView(p3DFrame->GetActiveView());
	pDoc->SetDocPathName(PathToFile);
	pDoc->SetTitle(PathToFile);
#ifdef SCAD21
	pDoc->m_pSchem = nullptr;//pParam->Res->SchemaData;
#else
	pDoc->m_pSchem = pParam->Res->SchemaData;
#endif
	p3DFrame->ActivateFrame();
	//AfxGetApp()->m_pMainWnd = NULL;
	CIsoViewGeometry *pIsoGeometry = new CIsoViewGeometry(p3DFrame,nullptr,nullptr);
	pIsoGeometry->SetParams(pParam);
	pIsoGeometry->LoadIso(pDoc->m_bShowProfiles, static_cast<CScadViewerView*>(p3DFrame->GetActiveView())->m_ViewOptions.bDrawOptimize);
	pDoc->m_pViewGeometry = pIsoGeometry;
	p3DFrame->GetActiveView()->OnInitialUpdate();
	pParam->hWndOgl = p3DFrame->m_hWnd;
	wnd.Detach();
	/*
		BOOL bIdle = TRUE;
		LONG lIdleCount = 0;
		MSG msgCur;
		while (!bFrameClosed)
		{
			// phase1: check to see if we can do idle work
			while (bIdle &&
				!::PeekMessage(&msgCur, NULL, NULL, NULL, PM_NOREMOVE))
			{
				// call OnIdle while in bIdle state
				if (!theApp.OnIdle(lIdleCount++))
					bIdle = FALSE; // assume "no idle" state
			}
	
			// phase2: pump messages while available
			do
			{
				// pump message, but quit on WM_QUIT
				if (!theApp.PumpMessage())
				{
					goto Exit;
				}
	
				// reset "no idle" state after pumping "normal" message
				if (theApp.IsIdleMessage(&msgCur))
				{
					bIdle = TRUE;
					lIdleCount = 0;
				}
	
			} while (::PeekMessage(&msgCur, NULL, NULL, NULL, PM_NOREMOVE));
		}
	Exit:
		sm.UpdateInt(false, _T("Language"), &nLangID, 1049);
		theApp.m_pszProfileName = pszOldProfileName;
		theApp.m_pszRegistryKey = pszOldRegistryKey;
		AfxSetResourceHandle(hOldResInst);
		p_hWnd->EnableWindow(TRUE);
		::SetActiveWindow(p_hWnd->m_hWnd);	wnd.Detach();
	
		pParam->hWndOgl = NULL;
	*/
}

#endif