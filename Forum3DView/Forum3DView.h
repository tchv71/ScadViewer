// Forum3DView.h : main header file for the FOURM3DVIEW DLL
//

#if !defined(AFX_FOURM3DVIEW_H__CCB6D586_62E2_4590_966E_5FED2704A14E__INCLUDED_)
#define AFX_FOURM3DVIEW_H__CCB6D586_62E2_4590_966E_5FED2704A14E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//class CString;

//typedef CString CSCADString;

#ifdef SCAD21
#include "SCADAPIX.hxx"

typedef APIHandle_tag SCHEMA; 
#else
class SCHEMA;
#endif

class CWnd;
#if defined(FORUM3DVIEW_EXPORTS) 
#define FORUM3DVIEW_EXPORT  __declspec(dllexport) 
#else
#define FORUM3DVIEW_EXPORT  __declspec(dllimport) 
#endif
void FORUM3DVIEW_EXPORT LoadLanguage(int nNewLangID);

struct SOglIsoParam;

void FORUM3DVIEW_EXPORT OglIso3D(SOglIsoParam *pParam);

void FORUM3DVIEW_EXPORT __cdecl Forum3DView(SCHEMA *Prj,CString PathToFile,CWnd *p_hWnd);
void FORUM3DVIEW_EXPORT __cdecl Scad3DView(SCHEMA *Prj,LPCSTR strPath,HWND hWnd);
extern "C"
{
FORUM3DVIEW_EXPORT BOOL __stdcall SCForumMdl3DDraw( HDC hdc, const RECT * r, LPCTSTR sFileName, LPCTSTR sWorkDir, int nDrawFlags, HANDLE nStopEvent);
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOURM3DVIEW_H__CCB6D586_62E2_4590_966E_5FED2704A14E__INCLUDED_)
