// DirChangeListener.h: interface for the CDirChangeListener class.
//
// Copyright (C) 2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRCHANGELISTENER_H__5589616F_FE43_42E3_BB94_F5CB1C869B78__INCLUDED_)
#define AFX_DIRCHANGELISTENER_H__5589616F_FE43_42E3_BB94_F5CB1C869B78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_DIRCHANGE (WM_USER+1027)

class CDirChangeListener  
{
public:
	void SetDir(CString strDirName, HWND hWndReceiver);
	HANDLE m_hThread;
	CDirChangeListener();
	virtual ~CDirChangeListener();

protected:
	void ListenDirChange() const;
	HANDLE m_hCancelEvent;
	HANDLE m_hStopEvent;
	HWND m_hwndReceiver;
	CString m_strDirName;
	static unsigned __stdcall ThreadProc(void *pParam);
};

#endif // !defined(AFX_DIRCHANGELISTENER_H__5589616F_FE43_42E3_BB94_F5CB1C869B78__INCLUDED_)
