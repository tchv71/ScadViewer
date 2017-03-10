// ThumbCashe.cpp: implementation of the CThumbCashe class.
//
//////////////////////////////////////////////////////////////////////
#define __oledb_h__
#include "stdafx.h"
#include "ThumbCashe.h"
#undef DB_UNKNOWN
#include <db_cxx.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include <io.h>


#define DB_NAME "scthumb.db"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThumbCashe::CThumbCashe(LPCTSTR pszDirName) :
	m_strDir(pszDirName), m_strDbName(m_strDir)

{
	m_strDbName+=_T("\\");
	m_strDbName+=DB_NAME;
}

CThumbCashe::~CThumbCashe()
{

}

bool CThumbCashe::Get(LPCTSTR pszFileName, const SThumbParam &rParam, HDC dc) const
{
	u_int32_t oFlags = DB_CREATE; // Open flags;
	Db db(nullptr, 0);
	try
	{
		// Open the database
		db.open(nullptr, // Transaction pointer
			DbName(), // Database file name
			nullptr, // Optional logical database name
			DB_BTREE, // Database access method
			oFlags, // Open flags
			0); // File mode (using defaults)
		// DbException is not subclassed from std::exception, so
		// need to catch both of these.
		// Use our own memory to retrieve the float.
		// For data alignment purposes.
		std::string vecKey;
		GetKey(pszFileName, rParam, vecKey);
		Dbt key(&vecKey[0], vecKey.size()),data;
		db.get(nullptr, &key, &data, 0);
		
		char* pdata = static_cast<char *>(data.get_data());
		size_t nSize = data.get_size();
		if (!pdata)
			return false;
		std::string strAddDataThumb;
		GetAddData(pszFileName, rParam, strAddDataThumb);
		if (nSize<=strAddDataThumb.size())
			return false;
		std::string strAddDataStored;
		strAddDataStored.append(pdata, strAddDataThumb.size());
		pdata+=strAddDataStored.size();
		nSize-=strAddDataStored.size();
		if (strAddDataThumb.compare(strAddDataStored)!=0)
			return false;

		// Now get thumb data
		BITMAPINFO m_bmi;
		memcpy(&m_bmi, pdata, sizeof(m_bmi));
		pdata+=sizeof(m_bmi);
		nSize-=sizeof(m_bmi);
		void *m_pBitmapBits = nullptr;
		HBITMAP m_hDib = ::CreateDIBSection(dc, &m_bmi, DIB_RGB_COLORS, &m_pBitmapBits, nullptr, DWORD(0));
		CDC dcBmp; 
		dcBmp.CreateCompatibleDC( CDC::FromHandle(dc));
		::SetBitmapBits(m_hDib, nSize, pdata);
		//::SetDIBits(dcBmp, m_hDib, 0, rParam.nHeight, pdata, &m_bmi, data.get_size()-sizeof(m_bmi));

		CBitmap * pbmpOld = static_cast<CBitmap*>(dcBmp.SelectObject( CBitmap::FromHandle(m_hDib)));
		::BitBlt(dc, 0,0, rParam.nWidth, rParam.nHeight, dcBmp, 0, 0, SRCCOPY);
		dcBmp.SelectObject(pbmpOld);
		::DeleteObject(m_hDib);
		dcBmp.DeleteDC();
		db.close(0);
		return true;

	}
	catch(DbException &)
	{
		// Error handling code goes here
	}
	catch(std::exception &)
	{
		// Error handling code goes here
	}
	return false;
}

void CThumbCashe::Put(LPCTSTR pszFileName, const SThumbParam &rParam, HDC dc) const
{

	Db db(nullptr, 0);
	try
	{
		// Open the database
		db.open(nullptr, // Transaction pointer
			DbName(), // Database file name
			nullptr, // Optional logical database name
			DB_BTREE, // Database access method
			DB_CREATE, // Open flags
			0); // File mode (using defaults)
		// DbException is not subclassed from std::exception, so
		// need to catch both of these.
		// Use our own memory to retrieve the float.
		// For data alignment purposes.
		std::string vecKey;
		GetKey(pszFileName, rParam, vecKey);
		Dbt key(&vecKey[0], vecKey.size());

		std::string strData;
		GetAddData(pszFileName, rParam, strData);
		
		// Now get thumb data
		BITMAPINFO m_bmi;
		memset(&m_bmi, 0, sizeof(BITMAPINFO));
		m_bmi.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
		m_bmi.bmiHeader.biWidth			= rParam.nWidth;
		m_bmi.bmiHeader.biHeight		= rParam.nHeight;
		m_bmi.bmiHeader.biPlanes		= 1;
		m_bmi.bmiHeader.biBitCount		= 24;
		m_bmi.bmiHeader.biCompression	= BI_RGB;
		m_bmi.bmiHeader.biSizeImage		= ((((rParam.nWidth * 24) + 31) & ~31) >> 3) * rParam.nHeight;
		void *m_pBitmapBits = nullptr;
		HBITMAP m_hDib = ::CreateDIBSection(dc, &m_bmi, DIB_RGB_COLORS, &m_pBitmapBits, nullptr, DWORD(0));
		CDC dcBmp; 
		dcBmp.CreateCompatibleDC( CDC::FromHandle(dc));

		CBitmap * pbmpOld = static_cast<CBitmap*>(dcBmp.SelectObject( CBitmap::FromHandle(m_hDib)));
		dcBmp.BitBlt(0,0, rParam.nWidth, rParam.nHeight, CDC::FromHandle(dc), 0, 0, SRCCOPY);
		strData.append(reinterpret_cast<char*>(&m_bmi), sizeof(m_bmi));
		std::vector<char> vecBits;
		vecBits.resize(m_bmi.bmiHeader.biSizeImage);
		::GetBitmapBits(m_hDib, m_bmi.bmiHeader.biSizeImage, &vecBits[0]);
		//strData.append((char*)m_pBitmapBits, m_bmi.bmiHeader.biSizeImage);
		strData.append(&vecBits[0], vecBits.size());
		Dbt data(reinterpret_cast<void *>(const_cast<char *>(strData.c_str())), strData.size());
		db.put(nullptr, &key, &data, 0);
		dcBmp.SelectObject(pbmpOld);
		::DeleteObject(m_hDib);
		dcBmp.DeleteDC();
		db.close(0);
	}
	catch(DbException /*&e*/)
	{
		// Error handling code goes here
	}
	catch(std::exception /*&e*/)
	{
		// Error handling code goes here
	}
}

void CThumbCashe::GetKey(LPCTSTR pszFileName, const SThumbParam &rParam, std::string &rKey)
{
	rKey.empty();
#ifdef UNICODE
	char buf[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, pszFileName, -1, buf, sizeof(buf), nullptr, nullptr);
	rKey.append(buf, strlen(buf) + 1);
#else
	rKey.append(pszFileName, strlen(pszFileName)+1);
#endif
}

void CThumbCashe::GetAddData(LPCTSTR pszFileName, const SThumbParam &rParam, std::string &rKey) const
{
	rKey.empty();
	rKey.append(reinterpret_cast<char*>(const_cast<WORD *>(&rParam.nWidth)), sizeof(rParam.nWidth));
	rKey.append(reinterpret_cast<char*>(const_cast<WORD *>(&rParam.nHeight)), sizeof(rParam.nHeight));
	rKey.append(reinterpret_cast<char*>(const_cast<SCDefProjType *>(&rParam.eType)), sizeof(rParam.eType));

	struct _tfinddata_t fd;
	ZeroMemory(&fd, sizeof(fd));

	CString sPath(m_strDir);
	sPath.Append(_T("\\"));
	sPath.Append(pszFileName);

	intptr_t hFindHandle = _tfindfirst( sPath, &fd );

	if( hFindHandle == -1 )
		return;
	rKey.append(reinterpret_cast<char*>(const_cast<__time64_t *>(&fd.time_write)), sizeof(fd.time_write));
	_findclose( hFindHandle );
}


void CThumbCashe::Delete() const
{
	Db db(nullptr, 0);

	// Database open and subsequent operations omitted for clarity

	db.remove(DbName(),             // Database file to remove 
			  nullptr,                  // Database to remove. This is
									 // nullptr so the entire file is
									 // removed.  
			 0);                     // Flags. None used.
}

LPCSTR CThumbCashe::DbName() const
{
#ifdef UNICODE
	static char buf[MAX_PATH];
	
	WideCharToMultiByte(CP_ACP, 0, m_strDbName, -1, buf, sizeof(buf), nullptr, nullptr);
	return buf;
#else
	return m_strDbName;
#endif
}
