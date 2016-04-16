// Mp4PlayerMFC.h : main header file for the MP4PLAYERMFC application
//

#if !defined(AFX_MP4PLAYERMFC_H__98E0F75A_CCD7_4231_8B7D_A7D86CC47EC6__INCLUDED_)
#define AFX_MP4PLAYERMFC_H__98E0F75A_CCD7_4231_8B7D_A7D86CC47EC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ScadViewer.h"

struct IDSMP4;

class CMp4PlayerMFCApp : public CScadViewerApp
{
public:
	CMp4PlayerMFCApp();
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	//{{AFX_MSG(CMp4PlayerMFCApp)
	//afx_msg void OnFileOpen();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	bool m_bFileOpened;
	bool m_bRunning;
};

extern CMp4PlayerMFCApp theApp;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MP4PLAYERMFC_H__98E0F75A_CCD7_4231_8B7D_A7D86CC47EC6__INCLUDED_)
