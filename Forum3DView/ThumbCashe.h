// ThumbCashe.h: interface for the CThumbCashe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THUMBCASHE_H__BB403D23_883A_45A2_806C_7524B4655593__INCLUDED_)
#define AFX_THUMBCASHE_H__BB403D23_883A_45A2_806C_7524B4655593__INCLUDED_
#include <windef.h>
#include <string>
#include "DefProjType.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct SThumbParam
{
	WORD nWidth;
	WORD nHeight;
	SCDefProjType eType;
};

class CThumbCashe  
{
public:
	void Delete() const;
	CThumbCashe(LPCTSTR pszDirName);
	virtual ~CThumbCashe();
	void Put(LPCTSTR pszFileName, const SThumbParam &rParam, HDC dc) const;
	bool Get(LPCTSTR pszFileName, const SThumbParam &rParam, HDC dc) const;
protected:
	LPCSTR DbName() const;
	static void GetKey(LPCTSTR pszFileName, const SThumbParam &rParam, std::string &rKey);
	void GetAddData(LPCTSTR pszFileName, const SThumbParam &rParam, std::string &rKey) const;
	std::wstring m_strDir;
	std::wstring m_strDbName;

};

#endif // !defined(AFX_THUMBCASHE_H__BB403D23_883A_45A2_806C_7524B4655593__INCLUDED_)
