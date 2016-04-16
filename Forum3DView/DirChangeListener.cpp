// DirChangeListener.cpp: implementation of the CDirChangeListener class.
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirChangeListener.h"
#include <process.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirChangeListener::CDirChangeListener()

{
	m_hCancelEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
	m_hStopEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
	UINT nThreadAddr;
	m_hThread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, 0, ThreadProc, this, 0, &nThreadAddr));
}

CDirChangeListener::~CDirChangeListener()
{
	::SetEvent(m_hStopEvent);
	WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hCancelEvent);
	::CloseHandle(m_hStopEvent);
}

unsigned __stdcall CDirChangeListener::ThreadProc(void* pParam)
{
	CDirChangeListener* pThis = static_cast<CDirChangeListener *>(pParam);
	//bool bRun = true;
	HANDLE hEvents[] = {pThis->m_hCancelEvent, pThis->m_hStopEvent};
	DWORD dwRes = ::WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);
	switch (dwRes - WAIT_OBJECT_0)
	{
	case 0:
		pThis->ListenDirChange();
		break;
	}
	return 0;
}


void CDirChangeListener::ListenDirChange() const
{
	bool bRun = true;
	while (bRun)
	{
		HANDLE hChange;

		hChange = FindFirstChangeNotification
			(
				m_strDirName,// directory to watch
				FALSE, // do not watch the subtree
				FILE_NOTIFY_CHANGE_FILE_NAME
			); // watch filename changes
		if (hChange == INVALID_HANDLE_VALUE)
			return;
		bool bCancel = false;
		// Change notification is set.
		while (!bCancel)
		{
			HANDLE hEvents[] = {hChange, m_hCancelEvent, m_hStopEvent};
			DWORD dwRes = WaitForMultipleObjects(3, hEvents, FALSE, INFINITE);

			switch (dwRes - WAIT_OBJECT_0)
			{
			case 0:
				::PostMessage(m_hwndReceiver, WM_DIRCHANGE, 0, 0);
				::FindNextChangeNotification(hChange);
				break;
			case 1:
				bCancel = true;
				break;
			case 2:
				bCancel = true;
				bRun = false;
				break;
			}
		}

		::FindCloseChangeNotification(hChange);
	}
}

void CDirChangeListener::SetDir(CString strDirName, HWND hWndReceiver)
{
	m_strDirName = strDirName;
	m_hwndReceiver = hWndReceiver;
	::SetEvent(m_hCancelEvent);
}

