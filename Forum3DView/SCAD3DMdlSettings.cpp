// Set.cpp: implementation of the CSCAD3DMdlSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ScadViewer.h"
#include "MainScadViewerFrame.h"
#include "SCAD3DMdlSettings.h"
#include "SCADViewerView.h"
#include <Shlwapi.h>
//#include "SCADProfile.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HINSTANCE CSCAD3DMdlSettings::m_h3DModule = nullptr;

CSCAD3DMdlSettings *pMdlSettings = nullptr;

CSCAD3DMdlSettings::CSCAD3DMdlSettings()
{
	m_pFileProcThread = nullptr;
	pMdlSettings = this;
	//m_pLegend = new SC3DLegend;
/*
	AddExtInfo( _T("*.tns"), _T(""), _T(""), _T("tnsapi.dll"), (LPCSTR)MAKELONG( 2, 0), fdtDataHDCRect, FPDLoadData, 0 );
	AddExtInfo( _T("*.cns"), _T(""), _T(""), _T("ModelDLL.dll"), "ConDraw", fdtDataHDCRect, FPDLoadData, 11 );
	AddExtInfo( _T("*.sec"), _T(""), _T(""), _T("sdb.dll"), (LPCSTR)MAKELONG( 2, 0), fdtHDCRectData, FPDLoadData, 0 );
	AddExtInfo( _T("*.spr"), _T(""), _T(""), _T("sdb.dll"), (LPCSTR)MAKELONG( 2, 0), fdtHDCRectNameDirFlag, FPDLoadData, 0 );
*/
	m_pwndFileView = nullptr;
}

CSCAD3DMdlSettings::~CSCAD3DMdlSettings()
{
	SVModuleMap::iterator itModule;
	
	for( itModule = m_ModuleMap.begin(); itModule != m_ModuleMap.end(); ++itModule )
	{
		::FreeLibrary( itModule->second );
		itModule->second = nullptr;
	}
	m_ModuleMap.clear();
	m_ExtFuncMap.clear();
	//m_pLegend->Release();
	//m_pLegend = nullptr;
}


CSCAD3DMdlSettings* CSCAD3DMdlSettings::Get3DS(void)
{
	return pMdlSettings;
}

LPCTSTR CSCAD3DMdlSettings::GetExeFullPath(void) const
{
   return m_ExeFullPath;
}

//DEL SCBOOL CSCAD3DMdlSettings::SetLangID( SCUINT16 lang_id )
//DEL {
//DEL 	SCBOOL bRes = CSCADUIToolsSettings::SetLangID( lang_id );
//DEL 	CMainFrame * pMfrm = (CMainFrame*)AfxGetMainWnd();
//DEL 
//DEL 	if( bRes && pMfrm && pMfrm->IsKindOf( RUNTIME_CLASS( CMainFrame ) ) )
//DEL 		bRes = pMfrm->OnChangeLangID( lang_id, m_BaseRcInstance, m_LocalRcInstance );
//DEL 
//DEL 	return bRes;
//DEL }

void CSCAD3DMdlSettings::SetFileView( CScadViewerView * pView )
{
	m_pwndFileView = pView;
}

void CSCAD3DMdlSettings::Initialize( const CSCADString& sExeFullPath )
{   
	m_ExeFullPath = sExeFullPath;

	//LoadToolsSettings();

//	CSCADString ini=GetIni();
//	TCHAR sBuf[MAX_PATH];
//	TCHAR sKey[MAX_PATH];
//	int nLangID = ::GetPrivateProfileInt( _T("General"), _T("Lang"), 0, ini );
//
//	if( nLangID == 0 || !SetLangID( nLangID ) )
//		SetLangID( 1033 );
//
//	::GetPrivateProfileString( _T("General"), _T("WorkDir"), _T(""), sBuf, MAX_PATH, ini );
//	m_csSCADWorkDir = sBuf;
//
//	int nExtNum = ::GetPrivateProfileInt( _T("General"), _T("ExtentionsNum"), 0, ini );
//	int i;
//
//	for( i = 1; i <= nExtNum; i++ )
//	{
//		sBuf[0] = 0;
//		_stprintf( sKey, _T("Extention_%d"), i );
//		::GetPrivateProfileString( _T("Extentions"), sKey, _T(""), sBuf, MAX_PATH, ini );
//		AddExtInfo( sBuf );
//	}
//
//	::GetPrivateProfileString( _T("State"), _T("ViewFolder"), _T(""), sBuf, MAX_PATH, ini );
//	m_sViewFolder = sBuf;
//	::GetPrivateProfileString( _T("State"), _T("ViewFile"), _T(""), sBuf, MAX_PATH, ini );
//	m_sViewFile = sBuf;
//	m_sLastFile = sBuf;
//
//	if( !LoadLegend( ini ) )
//		DefaultLegend();
	AddExtInfo(_T("spr, SCAD file, scad.exe, ") _3D_DLL _T(".dll, 3, hrndf, name, 0"));
	AddExtInfo(_T("opr, Forum file, Forum.exe, ") _3D_DLL _T(".dll, 3, hrndf, name, 0"));
	AddExtInfo(_T("mp4, Mp4 file, Forum.exe, ") _3D_DLL _T(".dll, 3, hrndf, name, 0"));
}

//DEL void CSCAD3DMdlSettings::SaveAppSettings()
//DEL {
//DEL 	CSCADString ini=GetIni();
//DEL 
//DEL 	WritePrivateProfileInt( _T("General"), _T("Lang"), GetLangID(), ini );
//DEL 	::WritePrivateProfileString( _T("State"), _T("ViewFolder"), m_sViewFolder, ini );
//DEL 	::WritePrivateProfileString( _T("State"), _T("ViewFile"), m_sViewFile, ini );
//DEL 
//DEL 	SaveLegend( ini );
//DEL }

BOOL CSCAD3DMdlSettings::SetCurViewFolder( const TCHAR * sFolderPath )
{
	if( !AfxGetApp()->GetMainWnd() || !AfxGetApp()->GetMainWnd()->IsKindOf( RUNTIME_CLASS( CMainScadViewerFrame ) ) )
		return FALSE;

	CMainScadViewerFrame * pMfrmWnd = static_cast<CMainScadViewerFrame*>(AfxGetApp()->GetMainWnd());

	m_sViewFolder = sFolderPath;

	if( pMfrmWnd )
		return pMfrmWnd->SetCurViewFolder( sFolderPath );

	return TRUE;
}

BOOL CSCAD3DMdlSettings::SetViewFilePath( const TCHAR * sFilePath, const TCHAR * sTypeExt )
{
	m_sViewFile = sFilePath;
	if( m_pwndFileView )
		 m_pwndFileView->SetViewFilePath( sFilePath, sTypeExt );
	TCHAR	szPath[_MAX_PATH];

	_tcscpy_s(szPath, sFilePath);
	PathRemoveFileSpec(szPath);
	CMainScadViewerFrame * pMfrmWnd = static_cast<CMainScadViewerFrame*>(AfxGetApp()->GetMainWnd());
	pMfrmWnd->OnViewInFolder(szPath);	
	return TRUE;
}

BOOL CSCAD3DMdlSettings::StartFileProc()
{
	if( m_pFileProcThread )
		return TRUE;

	m_pFileProcThread = new CFileProc();
	if( !m_pFileProcThread )
		return FALSE;

	return TRUE;
}

BOOL CSCAD3DMdlSettings::StopFileProc()
{
	if( !m_pFileProcThread )
		return TRUE;

	m_pFileProcThread->Finish();
	delete m_pFileProcThread;
	m_pFileProcThread = nullptr;

	return TRUE;
}

BOOL CSCAD3DMdlSettings::SetStartDrawPos( int nStartPos )
{
	if( !m_pFileProcThread )
		return FALSE;

	return m_pFileProcThread->SetStartPos( nStartPos ) ? TRUE : FALSE;
}

BOOL CSCAD3DMdlSettings::DrawFile( int nDFI, FPTDrawFileInfo * pDFI )
{
	if( !m_pFileProcThread )
		return FALSE;

	return m_pFileProcThread->DrawFile( nDFI, pDFI ) ? TRUE : FALSE;
}

BOOL CSCAD3DMdlSettings::CancelDraw()
{
	if( !m_pFileProcThread )
		return FALSE;

	return m_pFileProcThread->CancelDraw() ? TRUE : FALSE;
}



HMODULE CSCAD3DMdlSettings::AddModule( const TCHAR * sPath )
{
	SVModuleMap::iterator it = m_ModuleMap.find( sPath );

	if( it != m_ModuleMap.end() )
		return it->second;

	HMODULE hModule = ::LoadLibrary( sPath );

	if( !hModule )
		return nullptr;

	m_ModuleMap.insert( SVModuleMap::value_type( sPath, hModule) );

	return hModule;
}

BOOL CSCAD3DMdlSettings::AddExtInfo( const TCHAR * sExt, const TCHAR * sDescript, const TCHAR * sExePath, const TCHAR * sModulePath, LPCSTR sFuncName, FPTFileDrawType fdt, FPDLoadDataProc * pfnLoadData, int nOffset )
{
	SVExtFuncMap::iterator itExt = m_ExtFuncMap.find( sExt );

	if( itExt != m_ExtFuncMap.end() )
		return TRUE;

	HMODULE hModule = AddModule( sModulePath );

	if( !hModule )
		return FALSE;

	DHRFileDrawProc * pfnProc = reinterpret_cast<DHRFileDrawProc*>(GetProcAddress(hModule, sFuncName));

	if( !pfnProc )
		return FALSE;

	FPTExtFuncInfo	efi;

	efi.m_sDescript = sDescript;
	efi.m_sExt = sExt;
	efi.m_sExePath = sExePath;
	efi.m_fdtDrawType = fdt;
	efi.m_pfnDHR = pfnProc;
	efi.m_nOffset = nOffset;
	efi.m_pfnLoadProc = pfnLoadData;
	m_ExtFuncMap.insert( SVExtFuncMap::value_type( sExt, efi ) );

	return TRUE;
}

BOOL CSCAD3DMdlSettings::AddExtInfo( const TCHAR * sExtInfo )
{
	enum
	{
		eipExt,
		eipDesc,
		eipExe,
		eipModule,
		eipFunc,
		eipFDT,
		eipLDT,
		eipOffset,
		eipSize
	};

	CSCADString sInfo = sExtInfo;
	CSCADString sItems[eipSize];
	int nDrawFunc;
	int nOffset;
	FPTFileDrawType fdt;
	FPDLoadDataProc * pfnLoadData;
	TCHAR chDelimiter = _T(',');
	int nDlrPos;
	int i;

	for( i = 0; i < eipSize; i++ )
	{
		nDlrPos = sInfo.Find( chDelimiter, 0 );
		if( nDlrPos < 0)
		{
			sItems[i] = sInfo;
			break;
		}

		sItems[i] = sInfo.Left( nDlrPos );
		sInfo.Delete( 0, nDlrPos + 1 );
		sItems[i].TrimLeft();
		sItems[i].TrimRight();
	}

	if( !sItems[eipExt].GetLength() ||
		!sItems[eipModule].GetLength() || 
		!sItems[eipFunc].GetLength() ||
		!sItems[eipFDT].GetLength() ||
		!sItems[eipLDT].GetLength()
	)
		return FALSE;

	sItems[eipExt] = _T("*.") + sItems[eipExt];
	if( _stscanf_s( sItems[eipFunc], _T("%d"), &nDrawFunc ) != 1 )
		nDrawFunc = -1;
	if( _stscanf_s( sItems[eipOffset], _T("%d"), &nOffset ) != 1 )
		nOffset = 0;
	if( sItems[eipFDT].CompareNoCase( _T("dhr") ) == 0 )
		fdt = fdtDataHDCRect;
	else
		if( sItems[eipFDT].CompareNoCase( _T("hrd") ) == 0 )
			fdt = fdtHDCRectData;
		else
			if( sItems[eipFDT].CompareNoCase( _T("hrndf") ) == 0 )
				fdt = fdtHDCRectNameDirFlag;
			else
				return FALSE;
	if( sItems[eipLDT].CompareNoCase( _T("data") ) == 0 )
		pfnLoadData = FPDLoadData;
	else
		if( sItems[eipLDT].CompareNoCase( _T("name") ) == 0 )
			pfnLoadData = FPDGetName;
		else
			return FALSE;

	//LPCSTR sFunc = nDrawFunc < 0 ? sItems[eipFunc].GetBuffer( sItems[eipFunc].GetLength() ) : (LPSTR)MAKELONG( nDrawFunc, 0 );
	LPSTR sNewFunc = reinterpret_cast<LPSTR>(DWORD_PTR(nDrawFunc));
	LPSTR sFunc = nDrawFunc < 0 ? nullptr : sNewFunc;

	return AddExtInfo( sItems[eipExt], 
						sItems[eipDesc], 
						sItems[eipExe], 
						sItems[eipModule], 
						sFunc, 
						fdt, 
						pfnLoadData, 
						nOffset );
}

const FPTExtFuncInfo * CSCAD3DMdlSettings::GetExtFuncInfo( const TCHAR * sExt ) const
{
	SVExtFuncMap::const_iterator itExt = m_ExtFuncMap.find( sExt );

	if( itExt != m_ExtFuncMap.end() )
		return &itExt->second;

	return nullptr;
}

size_t CSCAD3DMdlSettings::GetEFISize() const
{
	return m_ExtFuncMap.size();
}

const FPTExtFuncInfo * CSCAD3DMdlSettings::GetEFIAt( SCUINT32 nPos ) const
{
	if( nPos >= m_ExtFuncMap.size() )
		return nullptr;

	SVExtFuncMap::const_iterator itExt;
	// ReSharper disable once CppPossiblyErroneousEmptyStatements
	for(itExt = m_ExtFuncMap.begin(); nPos; nPos--, ++itExt );

	return &itExt->second;
}

