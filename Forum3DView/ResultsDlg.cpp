// ResultsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ResultsDlg.h"
#include <tchar.h>
#include <io.h>
#include <shlwapi.h>
#include "addzip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultsDlg dialog


CResultsDlg::CResultsDlg(CString strResultsMask, CWnd* pParent /*=nullptr*/)
	: CDialog(CResultsDlg::IDD, pParent),
	m_strResultsMask(strResultsMask)
{
	//{{AFX_DATA_INIT(CResultsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CResultsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultsDlg)
	DDX_Control(pDX, IDC_LIST, m_ListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultsDlg, CDialog)
	//{{AFX_MSG_MAP(CResultsDlg)
	ON_BN_CLICKED(IDC_SELECT_ALL, OnSelectAll)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_CREATE_ZIP, OnCreateZip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultsDlg message handlers
static int GetSCADType(LPCTSTR Path)
{
	const static LPTSTR	SCADTypes[] =
	{
		_T("spr"),
		_T("F00"),
		_T("F01"),
		_T("F02"),
		_T("F03"),
		_T("F04"),
		_T("F05"),
		_T("F07"),
		_T("F08"),
		_T("F09"),
		_T("F10"),
		_T("F16"),
		_T("F55"),
		_T("F58"),
		_T("F59"),
		_T("P01"),
		_T("P02"),
		_T("P03"),
		_T("P04"),
		_T("P05"),
		_T("P06"),
		_T("P07"),
		_T("P08"),
		_T("P09"),
		_T("P10"),
		_T("P11"),
		_T("P12"),
		_T("P13"),
		_T("P14"),
		_T("P15"),
		_T("P16"),
		_T("P17"),
		_T("P18"),
		_T("P19"),
		_T("P20"),
		_T("P21"),
		_T("P22"),
		_T("P23"),
		_T("P24"),
		_T("P25"),
		_T("P26"),
		_T("P27"),
		_T("P28"),
		_T("P29"),
		_T("F11"),
		_T("F99")
	};

	CString strExt = PathFindExtension(Path);
	for(int i = 0; i < sizeof(SCADTypes) / sizeof(SCADTypes[0]); i++)
	{
		if(_tcsicmp(SCADTypes[i], LPCTSTR(strExt)+1) == 0)
			return i;
	}

	return -1;
}


//---------------------------------------------------------------------------
#define DELIM	'|'

void Skip(char * &Ptr)
{
	while(*(Ptr++) != DELIM);
};

void Copy(char *Buf, char * &Ptr)
{
	while(*Ptr != DELIM)
		*(Buf++) = *(Ptr++);
	*Buf = 0;
};

CString strArchiving;
bool		bZip = false;
static HWND hdlgCancel;

INT16_T CALLBACK mycallback(INT16_T iLibrary, INT16_T iMessage, char *szInfo)
{
	switch(iMessage)
	{
		case AM_ZIPPING:
			char *Ptr = szInfo;

			char		Buf[256];
			CStringA	strText = strArchiving;
			Skip(Ptr);
			Copy(Buf, Ptr);
			strText = (strText + Buf) + _T(" ");
			Skip(Ptr);
			Skip(Ptr);
			Skip(Ptr);
			Copy(Buf, Ptr);
			strText = (strText + Buf) + "%";
			SendDlgItemMessageA(hdlgCancel, 2000, PBM_SETPOS, StrToIntA(Buf), 0);

			SetDlgItemTextA(hdlgCancel, 200, strText);

			//Application->ProcessMessages();
			MSG msg;

			/*
     * Retrieve and remove messages from the thread's message
     * queue.
     */
			while(PeekMessage(LPMSG(& msg), HWND(nullptr), 0, 0, PM_REMOVE))
			{
				/* Process any messages for the Cancel dialog box. */
				if(!IsDialogMessage(hdlgCancel, LPMSG(& msg)))
				{
					TranslateMessage(LPMSG(& msg));
					DispatchMessage(LPMSG(& msg));
				}
			}
	}

	/*
     * Return the global bPrint flag (which is set to FALSE
     * if the user presses the Cancel button).
     */
	return WORD(bZip ? 1 : AM_ABORT);
}

LRESULT CALLBACK AbortZip
(
	HWND	hwndDlg,	/* window handle of dialog box     */
	UINT	message,	/* type of message                 */
	WPARAM	wParam,		/* message-specific information    */
	LPARAM	lParam
)	/* message-specific information    */
{
	switch(message)
	{
		case WM_INITDIALOG: /* message: initialize dialog box  */

			/* Initialize the static text control. */
			//            SetDlgItemText(hwndDlg, IDD_FILE, ofn.lpstrFile);
			return TRUE;

		case WM_COMMAND:	/* message: received a command */

			/* User pressed "Cancel" button--stop print job. */
			//            MessageBox(hwndDlg, "Incoming", "WM_COMMAND", MB_OK);
			bZip = FALSE;

			return TRUE;

		default:
			return FALSE;	/* didn't process a message   */
	}
}


//---------------------------------------------------------------------------

BOOL CResultsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);
	CString strColumnName;
	strColumnName.LoadString(IDS_RES_COLUMN_FILE);
	m_ListCtrl.InsertColumn( 0, strColumnName, LVCFMT_LEFT, 100, 0 );
	strColumnName.LoadString(IDS_RES_COLUMN_SIZE);
	m_ListCtrl.InsertColumn( 1, strColumnName, LVCFMT_RIGHT, 100, 1 );
	strColumnName.LoadString(IDS_RES_COLUMN_COMMENT);
	m_ListCtrl.InsertColumn( 2, strColumnName, LVCFMT_LEFT, 100, 2 );

	ReloadFileList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CResultsDlg::OnSelectAll() 
{
	for (int i=0; i<m_ListCtrl.GetItemCount(); i++)
	{
		m_ListCtrl.SetCheck(i);
	}
	
}

void CResultsDlg::OnDelete() 
{
	for (int i=0; i<m_ListCtrl.GetItemCount(); i++)
	{
		if (m_ListCtrl.GetCheck(i))
			::DeleteFile(m_ListCtrl.GetItemText(i,0));
	}
	ReloadFileList();
}

void CResultsDlg::ReloadFileList()
{
	m_ListCtrl.DeleteAllItems();
	struct _tfinddata_t fd;
	CString strWorkPath = m_strResultsMask;
	PathRemoveFileSpec(strWorkPath.GetBuffer(_MAX_PATH));
	strWorkPath.ReleaseBuffer();
	strWorkPath+="\\";
	long hFindHandle = _tfindfirst( m_strResultsMask, &fd );

	if (hFindHandle!=-1)
	{
		do
		{
			int nType = GetSCADType(fd.name);
			CString strFileType;
			if (nType != -1)
				strFileType.LoadString(nType+9000);
			else
			{
				SHFILEINFO	Sfi;
				if(::SHGetFileInfo(strWorkPath+fd.name, 0, &Sfi, sizeof(Sfi), SHGFI_TYPENAME) != 0)
				{
					strFileType = Sfi.szTypeName;
				}
			}
			extern CString	SizeToStr( _fsize_t fsz );

			int nItem = m_ListCtrl.InsertItem(m_ListCtrl.GetItemCount(), strWorkPath+fd.name);
			m_ListCtrl.SetItemText(nItem, 1, SizeToStr(fd.size));
			m_ListCtrl.SetItemText(nItem, 2, strFileType);
		} while (_tfindnext(hFindHandle, &fd) != -1);
	}
	_findclose(hFindHandle);
	for (int i=0;i<3; i++)
		m_ListCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}

void CResultsDlg::OnCreateZip() 
{
	// ReSharper disable once CppEntityAssignedButNoRead
	BOOL		bReturn;
	CString strZipFileName(m_strResultsMask);
	strArchiving.LoadString(IDS_ARCHIVING);
	CString strArchQuest;
	strArchQuest.LoadString(IDS_ARCH_QUEST);
	int iDelete = ::MessageBox(m_hWnd, strArchQuest, strArchiving, MB_YESNO);
	strArchiving += ": ";
	PathRemoveExtension(strZipFileName.GetBuffer(_MAX_PATH));
	strZipFileName.ReleaseBuffer();
	strZipFileName+= _T(".zip");

	HWND	handle = ::GetActiveWindow();
	::EnableWindow(handle, FALSE);
	hdlgCancel = ::CreateDialog(AfxFindResourceHandle(MAKEINTRESOURCE(IDD_ABORT_ZIP),RT_DIALOG), MAKEINTRESOURCE(IDD_ABORT_ZIP), handle, DLGPROC(AbortZip));

	bZip = true;
	for(int i = 0; i < m_ListCtrl.GetItemCount() && bZip; i++)
	{
		if(m_ListCtrl.GetCheck(i))
		{
			addZIP_Initialise();
			addZIP_InstallCallback(CALLBACKFN(mycallback));
			// ReSharper disable once CppAssignedValueIsNeverUsed
			bReturn = addZIP_SetParentWindowHandle(handle);
#ifdef UNICODE
			char strZipFileNameA[MAX_PATH];
			WideCharToMultiByte(CP_ACP, 0, strZipFileName, -1, strZipFileNameA, sizeof(strZipFileNameA), nullptr, nullptr);
			bReturn = addZIP_ArchiveName(strZipFileNameA);
#else
			bReturn = addZIP_ArchiveName(strZipFileName);
#endif
			bReturn = addZIP_SetCompressionLevel(azCOMPRESSION_MAXIMUM);
			bReturn = addZIP_SaveStructure(azSTRUCTURE_NONE);
#ifdef UNICODE
			char str[MAX_PATH];
			WideCharToMultiByte(CP_ACP, 0, m_ListCtrl.GetItemText(i, 0), -1, str, sizeof(str), nullptr, nullptr);
			bReturn = addZIP_Include(str);
#else
			bReturn = addZIP_Include(m_ListCtrl.GetItemText(i,0));
#endif
			bReturn = addZIP();
			if(iDelete == IDYES)
				DeleteFile(m_ListCtrl.GetItemText(i,0));
		}
	}

	::EnableWindow(handle, TRUE);
	::DestroyWindow(hdlgCancel);

	ReloadFileList();	
}
