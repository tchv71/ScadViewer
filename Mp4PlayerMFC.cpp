// Mp4PlayerMFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Mp4PlayerMFC.h"
#include "Forum3DView\MainScadViewerFrame.h"
#include "Forum3DView\ScadViewerDoc.h"
#include "Forum3DView\Mp4View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMp4PlayerMFCApp, CScadViewerApp)
	//{{AFX_MSG_MAP(CMp4PlayerMFCApp)
	//ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard print setup command
	//ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CMp4PlayerMFCApp::CMp4PlayerMFCApp() :
	m_bFileOpened(false),
	m_bRunning(false)
{
}

CMp4PlayerMFCApp theApp;

BOOL CMp4PlayerMFCApp::InitInstance()
{
	//if (!CScadViewerApp::InitInstance())
	//	return false;
	CWinAppEx::InitInstance();
	m_Settings.Initialize(_T(""));
	m_Settings.StartFileProc();
	AfxOleInit();
	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	// Standard initialization

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Scad Soft"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)


	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CScadViewerDoc),
		RUNTIME_CLASS(CMainScadViewerFrame),       // main SDI frame window
		RUNTIME_CLASS(CMp4View));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//m_pMainWnd = pFrame;
#if 0
	HRESULT hr;
	CLSID clsid;
	::CLSIDFromProgID(L"SeeStorm.DSMP4", &clsid);
	hr = ::CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IDSMP4), (void**)&m_pDSMP4);
	if (FAILED(hr))
		return FALSE;
#endif
	//m_pDSMP4->put_HWndParent((long)(pFrame->GetMp4View()->GetSafeHwnd()));

	//m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CMp4PlayerMFCApp::ExitInstance(void)
{
	return CScadViewerApp::ExitInstance();
}
/*
void CMp4View::OnFileOpen()
{
	HRESULT hr;

	CFileDialog fd(TRUE, NULL, NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_SHAREAWARE,
		"MPEG-4 files (*.mp4;*.trif)|*.mp4;*.trif|DirectShow Graph files (*.grf)|*.grf|All Files (*.*)|*.*||",
		this);

	const int BUFSZ = 4096*10;
	char buf[BUFSZ];
	memset(buf, '\0', BUFSZ);
	fd.m_ofn.nMaxFile = BUFSZ-1;
	fd.m_ofn.lpstrFile = buf;

	int irc = (int)(fd.DoModal());
	if( irc != IDOK )
		return;

	char* pc = buf + fd.m_ofn.nFileOffset;

	CString sFileName;

	if( *(pc-1) == '\0' )
	{
		CString path(buf);
		path += "\\";
		while(*pc)
		{
			//ImportImage(path+pc);
			sFileName = path + pc;
			pc += strlen(pc);
			pc++;
		}
	}
	else
	{
		//ImportImage(buf);
		sFileName = buf;
	}

	//char szFileName[] = "C:\\Scenes\\Scene\\Scene.mp4";
	LPCSTR szFileName = (LPCSTR)sFileName;

	CWaitCursor wc;

	\m_pMainWnd->ShowWindow(SW_SHOW);
	OnFileNew();

	
	OnFilePlay();

	return;
}
*/

