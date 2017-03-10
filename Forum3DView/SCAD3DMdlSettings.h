// SCAD3DMdlSettings.h: interface for the CSCAD3DMdlSettings class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SCAD3DMdlSettings_h
#define SCAD3DMdlSettings_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "SCAD3DModelAPIDef.hxx"
//#include "SCADSettings.hxx"
//#include "SCADToolsSettings.hxx"
//#include "SCADMathSettings.hxx"
//#include "SCADUIToolsSettings.hxx"
//#include "SC3DLegend.hxx"
//#include "SC3DMaterial.hxx"
//#include "SCAD3DModelSettings.hxx"

//#include "SCADListener.hxx"
#include "FileProc.h"

#include <map>
using namespace std;

#pragma  warning(push)
#pragma warning( disable : 4284 )
#pragma  warning(disable:4250)

class CScadViewerView;

typedef UINT SCUINT32;
/*
	Name: CSCAD3DMdlSettings
	Description:
	Inputs:
	Return Value:
	Remarks:
*/

#ifdef SCAD11
#define _3D_DLL _T("Forum3DView11")
#else
#ifdef SCAD21
#define _3D_DLL _T("Forum3DView21")
#else
#define _3D_DLL _T("Forum3DView")
#endif
#endif

class FORUM3DVIEW_EXPORT CSCAD3DMdlSettings
 /*:
virtual  public CSCADSettings, 
virtual  public CSCADToolsSettings,
virtual  public CSCADUIToolsSettings,
virtual  public CSCAD3DModelSettings
*/
{
public:

	static	CSCAD3DMdlSettings*		Get3DS			(void);
	virtual	LPCTSTR	GetExeFullPath	(void) const;


	virtual	void				SetFileView	( CScadViewerView * pView );
	virtual	CScadViewerView *	GetFileView	() const { return m_pwndFileView;}

	virtual	BOOL		SetCurViewFolder( const TCHAR * sFolderPath );
	virtual	BOOL		SetViewFilePath	( const TCHAR * sFilePath, const TCHAR * sTypeExt );

	virtual	BOOL		SetStartDrawPos	( int nStartPos );
	virtual	BOOL		DrawFile		( int nDFI, FPTDrawFileInfo * pDFI );
	virtual	BOOL		CancelDraw		();


	virtual	const FPTExtFuncInfo *	GetExtFuncInfo	( const TCHAR * sExt ) const;
	virtual size_t GetEFISize() const;
	virtual	const FPTExtFuncInfo *	GetEFIAt		( SCUINT32 nPos ) const;

	virtual	CSCADString	GetWorkDir		() const { return m_csSCADWorkDir;}

	static	void		SetModuleHandle	( HINSTANCE hInst ) { m_h3DModule = hInst;}
	static	HINSTANCE	GetModuleHandle	() { return m_h3DModule;}

protected:
	typedef	map<CSCADString, HMODULE>	SVModuleMap;
	typedef	map<CSCADString, FPTExtFuncInfo>	SVExtFuncMap;

protected:
	CSCAD3DMdlSettings();
	virtual ~CSCAD3DMdlSettings();

	virtual void		Initialize		( const CSCADString& sExeFullPath );
	virtual	BOOL		StartFileProc	();
	virtual	BOOL		StopFileProc	();

	virtual	HMODULE		AddModule		( const TCHAR * sPath );
	BOOL    AddExtInfo( const TCHAR * sExt, const TCHAR * sDescript, const TCHAR * sExePath, const TCHAR * sModulePath, LPCSTR sFuncName, FPTFileDrawType fdt, FPDLoadDataProc * pfnLoadData, int nOffset );
	virtual	BOOL		AddExtInfo		( const TCHAR * sExtInfo );



protected:
	CSCADString		m_ExeFullPath;
	CSCADString		m_IniFullPath;
	CSCADString		m_csSCADWorkDir;
	CScadViewerView*	m_pwndFileView;
	CFileProc*		m_pFileProcThread;
	SVModuleMap		m_ModuleMap;
	SVExtFuncMap	m_ExtFuncMap;
	CSCADString		m_sViewFolder;
	CSCADString		m_sViewFile;
	CSCADString		m_sLastFile;
	//SC3DLegend *	m_pLegend;

	static	HINSTANCE		m_h3DModule;

	friend class CScadViewerApp;
	friend class CMp4PlayerMFCApp;
};

#pragma  warning(pop)

#endif // SCAD3DMdlSettings_h
