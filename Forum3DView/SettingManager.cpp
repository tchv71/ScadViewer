// SettingManager.cpp: implementation of the CSettingManager class.
//
//////////////////////////////////////////////////////////////////////
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "SettingManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettingManager::CSettingManager(): m_pszSubkey(nullptr)
{

}

CSettingManager::~CSettingManager()
{

}

BOOL CSettingManager::UpdateInt(bool bLoad,  CString strKey, int *pValue, int nDefault) const
{
	if (bLoad)
		*pValue = AfxGetApp()->GetProfileInt(m_pszSubkey, strKey, nDefault);
	else
		AfxGetApp()->WriteProfileInt(m_pszSubkey, strKey, *pValue);
	return TRUE;
}

BOOL CSettingManager::UpdateBool(bool bLoad, CString strKey, bool* pValue, bool bDefault) const
{
	int nVal = *pValue;
	BOOL bRes = UpdateInt(bLoad, strKey, &nVal, bDefault);
	if (bLoad)
	{
		*pValue = nVal != 0;
	}
	return bRes;
}

BOOL CSettingManager::UpdateString(bool bLoad, CString strKey, CString* pValue, LPCTSTR pszDefault) const
{
	if (bLoad)
		*pValue = AfxGetApp()->GetProfileString(m_pszSubkey, strKey, pszDefault);
	else
		AfxGetApp()->WriteProfileString(m_pszSubkey, strKey, *pValue);
	return TRUE;
}

BOOL CSettingManager::UpdateStringVector(bool bLoad, CString strKey, std::vector<CString>* pValue, LPCTSTR pszDefault) const
{
	CString strList;
	if (bLoad)
	{
		pValue->resize(0);
		UpdateString(bLoad, strKey, &strList, pszDefault);
		int nDlrPos;
		while (!strList.IsEmpty())
		{
			nDlrPos = strList.Find(_T(','), 0 );
			CString strVal;
			if (nDlrPos < 0)
			{
				strVal = strList;
				strList.Empty();
			}
			else
			{
				strVal = strList.Left(nDlrPos);
				strList.Delete(0, nDlrPos+1);

			}
			pValue->push_back(strVal);
		}

	}
	else
	{
		for (UINT i=0; i<pValue->size(); i++)
		{
			strList+= pValue->at(i);
			if (i<pValue->size()-1)
				strList+=_T(",");
		}
		UpdateString(bLoad, strKey, &strList, pszDefault);
	}
	return TRUE;
}

BOOL CSettingManager::UpdateDouble(bool bLoad, CString strKey, double *pValue, double dblDefault) const
{
	if (bLoad)
	{
		CString strDefault;
		strDefault.Format(_T("%g"), dblDefault);
		CString strText = AfxGetApp()->GetProfileString(m_pszSubkey, strKey, strDefault);
		*pValue = _tstof(strText);
	}
	else
	{
		CString strVal;
		strVal.Format(_T("%g"), *pValue);
		AfxGetApp()->WriteProfileString(m_pszSubkey, strKey, strVal);
	}
	return TRUE;

}
