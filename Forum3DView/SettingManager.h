// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
// SettingManager.h: interface for the CSettingManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGMANAGER_H__302EF3DA_B4C3_4017_805B_B65DFA750E08__INCLUDED_)
#define AFX_SETTINGMANAGER_H__302EF3DA_B4C3_4017_805B_B65DFA750E08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>

class CSettingManager  
{
public:
	BOOL UpdateDouble(bool bLoad, CString strKey, double *pValue, double dblDefault) const;
	CSettingManager();
	virtual ~CSettingManager();
///protected:
	void SetKey(LPCTSTR pszSubkey)
	{
		m_pszSubkey = pszSubkey;
	}
	BOOL UpdateInt(bool bLoad, CString strKey, int* pValue, int nDefault) const;
	BOOL UpdateBool(bool bLoad, CString strKey, bool* pValue, bool bDefault) const;
	BOOL UpdateString(bool bLoad, CString strKey, CString* pValue, LPCTSTR pszDefault) const;
	BOOL UpdateStringVector(bool bLoad, CString strKey, std::vector<CString>* pValue, LPCTSTR pszDefault) const;
private:
	LPCTSTR m_pszSubkey;
};

#endif // !defined(AFX_SETTINGMANAGER_H__302EF3DA_B4C3_4017_805B_B65DFA750E08__INCLUDED_)
