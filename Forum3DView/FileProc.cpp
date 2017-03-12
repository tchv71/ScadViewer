// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
// FileProc.cpp : implementation file
//

#include "stdafx.h"
//#include "ScadViewer.h"
#include "FileProc.h"
#include <sys/stat.h>
#include <algorithm>
#include <process.h>
#include "SCAD3DMdlSettings.h"
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

FORUM3DVIEW_EXPORT int __stdcall FPDLoadData( const TCHAR * sPath, char*& data, size_t& data_size )
{
	if( !sPath )
		return FDE_READ_ERR;
	int hFile;
	_tsopen_s(&hFile, sPath, _O_BINARY | _O_RDONLY, _SH_DENYWR, _S_IREAD );
	struct _stat stat;
	int nRet;

	if( hFile == -1 )
		return FDE_READ_ERR;
	
	nRet = _fstat( hFile, &stat );
	data_size = stat.st_size;
	if( nRet == -1 || data_size <= 0 )
	{
		_close( hFile );

		return FDE_READ_ERR;
	}
	data = new char[data_size];
	data_size = _read( hFile, data, unsigned(data_size) );
	_close( hFile );

	return FDE_OK;
}

FORUM3DVIEW_EXPORT int __stdcall FPDGetName(const TCHAR * sPath, char*& data, size_t& data_size)
{
	if( !sPath )
		return FDE_READ_ERR;

	data_size = ( _tcslen( sPath ) + 1 ) * sizeof( TCHAR );
	data = new char[data_size];
	_tcscpy_s( reinterpret_cast<TCHAR*>(data), _tcslen(sPath) + 1, sPath );

	return FDE_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CFileProc

CFileProc::CFileProc()
{
	int i;
	::InitializeCriticalSection(&m_cs);

	m_hDrawCancelEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr );
	for( i = 0; i < FPETSize; i++ )
		m_hEvents[i] = ::CreateEvent(nullptr, FALSE, FALSE, nullptr );
	m_nStartPos = 0;
	UINT nThreadAddr;
	m_hDrawProc = _beginthreadex(nullptr, 0, DrawProc, this, 0, &nThreadAddr );
}

CFileProc::~CFileProc()
{
	int i;
	::DeleteCriticalSection(&m_cs);

	if( !m_hDrawProc )
	{
		::CloseHandle( m_hDrawCancelEvent );
		for( i = 0; i < FPETSize; i++ )
			::CloseHandle( m_hEvents[i] );
	}
}

bool CFileProc::SetStartPos( int nStartPos )
{
	// @@@Section cs( *this );

	if( nStartPos == m_nStartPos )
		return true;
	::EnterCriticalSection(&m_cs);

	if( nStartPos > m_nStartPos )
		while( !m_DFIDeque[0].empty() && m_DFIDeque[0].front().m_nKey < nStartPos )
		{
			m_DFIDeque[1].push_front( m_DFIDeque[0].front() );
			m_DFIDeque[0].pop_front();
		}
	else
		while( !m_DFIDeque[1].empty() && m_DFIDeque[1].front().m_nKey > nStartPos )
		{
			m_DFIDeque[0].push_front( m_DFIDeque[1].front() );
			m_DFIDeque[1].pop_front();
		}
	m_nStartPos = nStartPos; 
	::LeaveCriticalSection(&m_cs);
	return true;
}

bool CFileProc::DrawFile( int nDFI, FPTDrawFileInfo * pDFI )
{
	// @@@Section cs( *this );
	::EnterCriticalSection(&m_cs);
	FPDFIDeque::iterator it;

	if( nDFI >= m_nStartPos )
	{
		it = std::upper_bound( m_DFIDeque[0].begin(), m_DFIDeque[0].end(), FPDrawInfo( nDFI, pDFI ) );
		m_DFIDeque[0].insert( it, FPDrawInfo( nDFI, pDFI ) );
	}
	else
	{
		it = std::upper_bound( m_DFIDeque[1].begin(), m_DFIDeque[1].end(), FPDrawInfo( nDFI, pDFI ) );
		m_DFIDeque[1].insert( it, FPDrawInfo( nDFI, pDFI ) );
	}
	::LeaveCriticalSection(&m_cs);
	::SetEvent( m_hEvents[FPETStartDraw] );

	return true;
}

bool CFileProc::CancelDraw()
{
	// @@@Section cs( *this );
	FPDFIDeque::iterator it;
	int i;

	::SetEvent( m_hDrawCancelEvent );
	::EnterCriticalSection(&m_cs);
	for( i = 0; i < 2; i++ )
	{
		for( it = m_DFIDeque[i].begin(); it != m_DFIDeque[i].end(); ++it )
		{
			delete it->m_pDFI;
			it->m_pDFI = nullptr;
		}
		m_DFIDeque[i].clear();
	}
	::LeaveCriticalSection(&m_cs);
	return true;
}

bool CFileProc::Finish()
{
	// @@@Section cs( *this );

	CancelDraw();
	if( m_hDrawProc )
		::SetEvent( m_hEvents[FPETExit] );
	::WaitForSingleObject(HANDLE(m_hDrawProc), INFINITE);
	return true;
}

unsigned __stdcall CFileProc::DrawProc( void * pParam )
{
	CFileProc * pFP = static_cast<CFileProc*>(pParam);

	if( !pFP )
		return 1;

	HANDLE hDrawCancelEvent;
	HANDLE hEvents[FPETSize];
	int i;
	DWORD dwRes;
	bool bRun = true;

	// @@@pFP->AddRef();
	{
		// @@@Section cs( *pFP );

		hDrawCancelEvent = pFP->m_hDrawCancelEvent;
		for( i = 0; i < FPETSize; i++ )
			hEvents[i] = pFP->m_hEvents[i];
	}

	while( bRun )
	{
		dwRes = ::WaitForMultipleObjects( FPETSize, hEvents, FALSE, INFINITE );
		switch( dwRes - WAIT_OBJECT_0 )
		{
			case FPETStartDraw:
				{
					FPTDrawFileInfo * pDFI;

					do
					{
						{
							// @@@Section cs( *pFP );
							::EnterCriticalSection(&pFP->m_cs);

							pDFI = nullptr;
							::ResetEvent( hDrawCancelEvent );
							if( !pFP->m_DFIDeque[0].empty() )
							{
								pDFI = pFP->m_DFIDeque[0].front().m_pDFI;
								pFP->m_DFIDeque[0].pop_front();
							}
							else
								if( !pFP->m_DFIDeque[1].empty() )
								{
									pDFI = pFP->m_DFIDeque[1].front().m_pDFI;
									pFP->m_DFIDeque[1].pop_front();
								}
							::LeaveCriticalSection(&pFP->m_cs);
						}
						if( pDFI )
						{
							pFP->OnDrawFile( pDFI );
							delete pDFI;
						}
					} while( pDFI );
				}
				break;
			case FPETExit:
				bRun = false;
				// @@@pFP->Release();
				break;
		}
	}
	::CloseHandle( hDrawCancelEvent );
	for( i = 0; i < FPETSize; i++ )
		::CloseHandle( hEvents[i] );

	return 0;
}

void CFileProc::OnDrawFile( FPTDrawFileInfo * pDFI )
{
	if( !pDFI )
		return;
	if( !pDFI->m_hwndReciever )
		return;

	FPTFileBmp * pfbRes = new FPTFileBmp( *pDFI );

	if(
		!pDFI->m_sFilePath.GetLength() || !pDFI->m_pProcInfo->m_pfnLoadProc ||
		!pDFI->m_pProcInfo->m_pfnDHR || pDFI->m_nBmpCX <= 0 || pDFI->m_nBmpCY <= 0 
	  )
	{
		pfbRes->m_nRetCode = FDE_ERROR;
//		PostMessage( pDFI->m_hwndReciever, FPTM_SEND_FILE_BMP, 0, (DWORD)pfbRes );
		SendBmp( pDFI, pfbRes );
		return;
	}

	size_t nFileSize = 0;
	char * pFileData = nullptr;

	pfbRes->m_nRetCode = (*pDFI->m_pProcInfo->m_pfnLoadProc)( pDFI->m_sFilePath, pFileData, nFileSize );
	if( pfbRes->m_nRetCode != FDE_OK )
	{
//		PostMessage( pDFI->m_hwndReciever, FPTM_SEND_FILE_BMP, 0, (DWORD)pfbRes );
		SendBmp( pDFI, pfbRes );
		return;
	}
	if( nFileSize < size_t(pDFI->m_pProcInfo->m_nOffset) )
	{
		delete pFileData;
		pfbRes->m_nRetCode = FDE_ERROR;
//		PostMessage( pDFI->m_hwndReciever, FPTM_SEND_FILE_BMP, 0, (DWORD)pfbRes );
		SendBmp( pDFI, pfbRes );

		return;
	}


	HDC hdcReciever = GetDC(pDFI->m_hwndReciever);//GetDCEx( pDFI->m_hwndReciever, NULL, DCX_WINDOW | DCX_VALIDATE );
	HDC hdcBmp = CreateCompatibleDC( hdcReciever );
	HBITMAP hbmpRes = CreateCompatibleBitmap( hdcReciever, pDFI->m_nBmpCX, pDFI->m_nBmpCY );
	HBITMAP hbmpOld = HBITMAP(SelectObject( hdcBmp, hbmpRes ));
	RECT r = { 0, 0, pDFI->m_nBmpCX, pDFI->m_nBmpCY };
	LOGBRUSH lbBackground;

	ReleaseDC( pDFI->m_hwndReciever, hdcReciever );
	lbBackground.lbColor = RGB( 255, 255, 255 );
	lbBackground.lbHatch = 0;
	lbBackground.lbStyle = BS_SOLID;
	
	HBRUSH hBackground = CreateBrushIndirect( &lbBackground );

	FillRect( hdcBmp, &r, hBackground );
	DeleteObject( hBackground );
	BOOL bRes = FALSE;
	try
	{
		switch( pDFI->m_pProcInfo->m_fdtDrawType )
		{
			case fdtDataHDCRect:
				bRes = (*pDFI->m_pProcInfo->m_pfnDHR)( pFileData + pDFI->m_pProcInfo->m_nOffset, nFileSize - pDFI->m_pProcInfo->m_nOffset, hdcBmp, &r );
				break;
			case fdtHDCRectData:
				(*pDFI->m_pProcInfo->m_pfnHRD)( hdcBmp, &r, pFileData + pDFI->m_pProcInfo->m_nOffset );
				break;
			case fdtHDCRectNameDirFlag:
				CSCAD3DMdlSettings* pSettings = CSCAD3DMdlSettings::Get3DS();
				bRes = (*pDFI->m_pProcInfo->m_pfnHRNDF)( hdcBmp, &r, pFileData, pSettings? pSettings->GetWorkDir() : _T(""), 0 , m_hDrawCancelEvent);
				break;
		}
	}
	catch(...)
	{
		pfbRes->m_nRetCode = FDE_ERROR;
	}
	delete pFileData;
	pFileData = nullptr;
	SelectObject( hdcBmp, hbmpOld );
	DeleteDC( hdcBmp );
	if( pfbRes->m_nRetCode != FDE_OK || !bRes )
	{
		::DeleteObject( hbmpRes );
		hbmpRes = nullptr;
	}
	if (::WaitForSingleObject(m_hDrawCancelEvent,0)==WAIT_OBJECT_0)
	{
		::DeleteObject(hbmpRes);
		delete pfbRes;
		return;
	}
	pfbRes->m_hBmp = hbmpRes;
//	PostMessage( pDFI->m_hwndReciever, FPTM_SEND_FILE_BMP, 0, (DWORD)pfbRes );
	SendBmp( pDFI, pfbRes );
	
	return;
}

void CFileProc::SendBmp(FPTDrawFileInfo *pDFI, FPTFileBmp *pfbRes)
{
	if (!::SendMessage( pDFI->m_hwndReciever, FPTM_SEND_FILE_BMP, 0, DWORD_PTR(pfbRes) ))
		delete pfbRes;
}
