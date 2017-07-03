// ScadViewer.cpp : Defines the class behaviors for the application.
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV

// All Rights Reserved

// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "ScadViewer.h"

#include "Forum3DView/MainScadViewerFrame.h"
#include "Forum3DView/ScadViewerDoc.h"
#include "Forum3DView/ScadViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE


static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScadViewerApp

BEGIN_MESSAGE_MAP(CScadViewerApp, CWinAppEx)
	//{{AFX_MSG_MAP(CScadViewerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinAppEx::OnFilePrintSetup)
//	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScadViewerApp construction

CScadViewerApp::CScadViewerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CScadViewerApp object

CScadViewerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CScadViewerApp initialization

BOOL CScadViewerApp::InitInstance()
{
	m_Settings.Initialize(_T(""));
	m_Settings.StartFileProc();
	AfxOleInit();

	// Standard initialization
/*
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
*/
	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Scad Soft"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)
	LoadLanguage(1049);

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CScadViewerDoc),
		RUNTIME_CLASS(CMainScadViewerFrame),       // main SDI frame window
		RUNTIME_CLASS(CScadViewerView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	//m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CScadViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CScadViewerApp message handlers


BOOL CScadViewerApp::ExitInstance(void)
{
	CMFCVisualManager::DestroyInstance();
	m_Settings.StopFileProc();
	CKeyboardManager::CleanUp();
	return CWinAppEx::ExitInstance();
}


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DWORD dwHandle = 0;
	unsigned uiDataSize = 80;

	LPTSTR pData = NULL;
	// Get the version information block size,
	// then use it to allocate a storage buffer.
	CString strExeName = AfxGetApp()->m_pszExeName;
	strExeName+=_T(".exe");
	DWORD dwSize = ::GetFileVersionInfoSize(strExeName, &dwHandle);
	void *pBuffer = malloc(dwSize);

	// Get the version information block
	::GetFileVersionInfo(strExeName, 0, dwSize, pBuffer);
     //Use the version information block to obtain the file version.
	::VerQueryValue(pBuffer,
		            TEXT("\\StringFileInfo\\040904b0\\FileVersion"),
					(void **)&pData,
					&uiDataSize);
#ifdef _AMD64_
	_tcscat_s(pData, uiDataSize + 3, _T("x64"));
	uiDataSize += 3;
#endif

#ifdef _DEBUG
	_tcscat_s(pData, uiDataSize+2, _T("D"));
#endif

    if (pData)
        GetDlgItem(IDC_ABOUT_VER)->SetWindowText(pData);
    free(pBuffer);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
