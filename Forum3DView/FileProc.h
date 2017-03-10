// Portions Copyright (C) 2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#if !defined(AFX_FILEPROC_H__DD556E6D_2FF3_46A7_97EC_0DEAD95A1311__INCLUDED_)
#define AFX_FILEPROC_H__DD556E6D_2FF3_46A7_97EC_0DEAD95A1311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileProc.h : header file
//
#include "Forum3DView.h"

#pragma warning(push)
#pragma warning(disable:4018 4146)
#include <deque>

/////////////////////////////////////////////////////////////////////////////
// CFileProc thread

#define	FDE_OK			0
#define	FDE_ERROR		-1
#define	FDE_READ_ERR	-2

//Message for drawing of the file (LPARAM - FPTDrawFileInfo, after using you must delete LPARAM by delete)
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
#define	FPTM_DRAW_FILE				(WM_USER+1025)

//Message to main thread for return result BMP (LPARAM - FPTFileBmp, after using you must delete LPARAM by delete)
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
#define	FPTM_SEND_FILE_BMP			(WM_USER+1026)

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
enum FPTFileDrawType
{
	fdtDataHDCRect,
	fdtHDCRectData,
	fdtHDCRectNameDirFlag, 
};

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
typedef BOOL __stdcall DHRFileDrawProc( const char *, size_t, HDC, const RECT * );
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
typedef	void __stdcall HRDFileDrawProc( HDC, const RECT *, const char * );
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
typedef BOOL __stdcall HRNDFFileDrawProc( HDC, const RECT *, const char *, LPCTSTR, int, HANDLE);


//after using the data you must delete it by delete
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
typedef	int __stdcall FPDLoadDataProc( const TCHAR * sPath, char*& data, size_t& data_size );

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
FORUM3DVIEW_EXPORT int __stdcall FPDLoadData( const TCHAR * sPath, char*& data, size_t& data_size );
/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
FORUM3DVIEW_EXPORT int __stdcall FPDGetName(const TCHAR * sPath, char*& data, size_t& data_size);

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
struct	FPTExtFuncInfo
{
	CSCADString			m_sDescript;
	CSCADString			m_sExt;
	CSCADString			m_sExePath;
	FPDLoadDataProc *	m_pfnLoadProc;
	FPTFileDrawType		m_fdtDrawType;
	int					m_nOffset;
	union
	{
		DHRFileDrawProc *	m_pfnDHR;
		HRDFileDrawProc *	m_pfnHRD;
		HRNDFFileDrawProc *	m_pfnHRNDF;
	};
};

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
struct	FPTDrawFileInfo
{
	const FPTExtFuncInfo *	m_pProcInfo;
	HWND					m_hwndReciever;
	intptr_t						m_nItemID;
	CSCADString				m_sFilePath;
	int						m_nBmpCX;
	int						m_nBmpCY;
};

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
struct	FORUM3DVIEW_EXPORT FPTFileBmp
{
	FPTFileBmp( const FPTDrawFileInfo& dfi )
	{
		m_nItemID = dfi.m_nItemID;
		m_sFilePath = dfi.m_sFilePath;
		m_nBmpCX = dfi.m_nBmpCX;
		m_nBmpCY = dfi.m_nBmpCY;
		m_hBmp = nullptr;
		m_nRetCode = 0;
		m_hBmp = nullptr;
	}

	int					m_nRetCode;
	intptr_t			m_nItemID;
	CSCADString			m_sFilePath;
	int					m_nBmpCX;
	int					m_nBmpCY;
	HBITMAP				m_hBmp;
};

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
class FORUM3DVIEW_EXPORT CFileProc // : public SCCounteredMT
{
public:
	CFileProc();
	virtual ~CFileProc();

	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	virtual	bool	SetStartPos	( int nStartPos );
	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	virtual	bool	DrawFile	( int nDFI, FPTDrawFileInfo * pDFI );
	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	virtual	bool	CancelDraw	();
	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	virtual	bool	Finish		();
	
protected:

	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	void	OnDrawFile( FPTDrawFileInfo * pDFI );
	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	static	unsigned __stdcall	DrawProc( void * pParam );

protected:
	void SendBmp( FPTDrawFileInfo * pDFI, FPTFileBmp *pfbRes);
	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	struct FPDrawInfo
	{
		FPDrawInfo(){ m_nKey = 0; m_pDFI = nullptr;}
		FPDrawInfo( const FPDrawInfo& di ){ *this = di;}
		FPDrawInfo( int nDFI, FPTDrawFileInfo * pDFI ){ m_nKey = nDFI; m_pDFI = pDFI;}
		
		FPDrawInfo& operator=( const FPDrawInfo& di ){ m_nKey = di.m_nKey; m_pDFI = di.m_pDFI; return *this;}
		bool		operator<( const FPDrawInfo& di ) const { return m_nKey < di.m_nKey ? true : false;}

		int					m_nKey;
		FPTDrawFileInfo *	m_pDFI;
	};
	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	typedef std::deque<FPDrawInfo> FPDFIDeque;

	/*
		Name:	
		Description:
		Inputs:
		Return Value:
		Remarks:
	*/
	enum FPEventType
	{
		FPETStartDraw,
		FPETExit,
		FPETSize
	};

	int			m_nStartPos;
	FPDFIDeque	m_DFIDeque[2];

	uintptr_t		m_hDrawProc;
	HANDLE		m_hDrawCancelEvent;
	HANDLE		m_hEvents[FPETSize];
	CRITICAL_SECTION m_cs;
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEPROC_H__DD556E6D_2FF3_46A7_97EC_0DEAD95A1311__INCLUDED_)
