//////////////////////////////////////////////////////////////////////
// DibGlRenderer.h: interface for the CDibGlRenderer class.
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBGLRENDERER_H__CD01E6EC_CACC_475F_8B30_B4D70BE854EC__INCLUDED_)
#define AFX_DIBGLRENDERER_H__CD01E6EC_CACC_475F_8B30_B4D70BE854EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GLRenderer.h"

class CViewGeometry;


class CDibGlRenderer : public CGLRenderer  
{
public:
	CDibGlRenderer(const CViewGeometry* pGeometry, SPerspectiveView &rViewPos);
	virtual ~CDibGlRenderer();

	bool BindDib(HWND hWnd, CSize szDib, int nBorder);
	void ReleaseDib();
	void SetClipboardData() const;
	bool SaveImage(LPCTSTR szFileName) const;
	virtual void	OnBeforePrint(CDC* pDC, CPrintInfo* pInfo, CView* pView, CString strFileName, FLOAT_TYPE &fScale);
	virtual void	OnAfterPrint(CDC* pDC);


protected:
	int DrawScale
		(
		CDC			*pDC,
		CRect		&r,
		FLOAT_TYPE	fAspX,
		FLOAT_TYPE	fAspY,
		int			nColumns,
		const struct DefMapInfo *DMI
		) const;
	void DrawPageBorder
		(
		CDC			*pDC,
		CRect		&r,
		FLOAT_TYPE		fAspX,
		FLOAT_TYPE		fAspY,
		int			W,
		int			H,
		CString		strFileName
		) const;
	void DrawFrame(CDC* pDC, CRect &rcDib, CString strFileName) const;
	SPerspectiveView m_ViewPosCopy;
	
	BITMAPINFO	m_bmi;
	LPVOID		m_pBitmapBits;
	HBITMAP		m_hDib;
	CRect		m_rcDIB;
	CSize		m_szPage;
	const CViewGeometry* m_pGeometry;
	CString		m_strFileName;

};

#endif // !defined(AFX_DIBGLRENDERER_H__CD01E6EC_CACC_475F_8B30_B4D70BE854EC__INCLUDED_)
