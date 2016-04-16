// GridCell.cpp : implementation file
//
// MFC Grid Control - Main grid cell class
//
// Provides the implementation for the "default" cell type of the
// grid control. Adds in cell editing.
//
// Written by Chris Maunder <chris@codeproject.com>
// Copyright (c) 1998-2005. All Rights Reserved.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// An email letting me know how you are using it would be nice as well. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// For use with CGridCtrl v2.20+
//
// History:
// Eric Woodruff - 20 Feb 2000 - Added PrintCell() plus other minor changes
// Ken Bertelson - 12 Apr 2000 - Split CGridCell into CGridCell and CGridCellBase
// <kenbertelson@hotmail.com>
// C Maunder     - 17 Jun 2000 - Font handling optimsed, Added CGridDefaultCell
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCell.h"
#include "InPlaceEdit.h"
#include "GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGridCell, CGridCellBase)

IMPLEMENT_DYNCREATE(CGridDefaultCell, CGridCell)

/////////////////////////////////////////////////////////////////////////////
// GridCell

CGridCell::CGridCell()
{
	m_plfFont = nullptr;
	CGridCell::Reset();
}

CGridCell::~CGridCell()
{
	delete m_plfFont;
}

/////////////////////////////////////////////////////////////////////////////
// GridCell Attributes

void CGridCell::operator=(const CGridCell& cell)
{
	if (this != &cell) CGridCellBase::operator=(cell);
}

void CGridCell::SetText(LPCTSTR szText)
{
	m_strText = szText;
}

void CGridCell::SetImage(int nImage)
{
	m_nImage = nImage;
}

void CGridCell::SetData(LPARAM lParam)
{
	m_lParam = lParam;
}

void CGridCell::SetGrid(CGridCtrl* pGrid)
{
	m_pGrid = pGrid;
}

void CGridCell::SetFormat(DWORD nFormat)
{
	m_nFormat = nFormat;
}

void CGridCell::SetTextClr(COLORREF clr)
{
	m_crFgClr = clr;
}

void CGridCell::SetBackClr(COLORREF clr)
{
	m_crBkClr = clr;
}

void CGridCell::Reset()
{
	CGridCellBase::Reset();

	m_strText.Empty();
	m_nImage = -1;
	m_lParam = 0; // BUG FIX J. Bloggs 20/10/03
	m_pGrid = nullptr;
	m_bEditing = FALSE;
	m_pEditWnd = nullptr;

	m_nFormat = DWORD(-1); // Use default from CGridDefaultCell
	m_crBkClr = CLR_DEFAULT; // Background colour (or CLR_DEFAULT)
	m_crFgClr = CLR_DEFAULT; // Forground colour (or CLR_DEFAULT)
	m_nMargin = UINT(-1); // Use default from CGridDefaultCell

	delete m_plfFont;
	m_plfFont = nullptr; // Cell font
}

void CGridCell::SetFont(const LOGFONT* plf)
{
	if (plf == nullptr)
	{
		delete m_plfFont;
		m_plfFont = nullptr;
	}
	else
	{
		if (!m_plfFont)
			m_plfFont = new LOGFONT;
		if (m_plfFont)
			memcpy(m_plfFont, plf, sizeof(LOGFONT));
	}
}

void CGridCell::SetMargin(UINT nMargin)
{
	m_nMargin = nMargin;
}

CWnd* CGridCell::GetEditWnd() const
{
	return m_pEditWnd;
}

void CGridCell::SetCoords(int, int)
{
}

COLORREF CGridCell::GetBackClr() const
{
	return m_crBkClr;
}

LOGFONT* CGridCell::GetFont() const
{
	if (m_plfFont == nullptr)
	{
		const CGridDefaultCell* pDefaultCell = static_cast<const CGridDefaultCell*>(GetConstDefaultCell());
		if (!pDefaultCell)
			return nullptr;

		return pDefaultCell->GetFont();
	}

	return m_plfFont;
}

CFont* CGridCell::GetFontObject() const
{
	// If the default font is specified, use the default cell implementation
	if (m_plfFont == nullptr)
	{
		const CGridDefaultCell* pDefaultCell = static_cast<const CGridDefaultCell*>(GetConstDefaultCell());
		if (!pDefaultCell)
			return nullptr;

		return pDefaultCell->GetFontObject();
	}
	else
	{
		static CFont Font;
		Font.DeleteObject();
		Font.CreateFontIndirect(m_plfFont);
		return &Font;
	}
}

LPCTSTR CGridCell::GetText() const
{
	return (m_strText.IsEmpty()) ? _T("") : LPCTSTR(m_strText);
}

int CGridCell::GetImage() const
{
	return m_nImage;
}

LPARAM CGridCell::GetData() const
{
	return m_lParam;
}

CGridCtrl* CGridCell::GetGrid() const
{
	return m_pGrid;
}

DWORD CGridCell::GetFormat() const
{
	if (m_nFormat == DWORD(-1))
	{
		const CGridDefaultCell* pDefaultCell = static_cast<const CGridDefaultCell*>(GetConstDefaultCell());
		if (!pDefaultCell)
			return 0;

		return pDefaultCell->GetFormat();
	}

	return m_nFormat;
}

COLORREF CGridCell::GetTextClr() const
{
	return m_crFgClr;
}

UINT CGridCell::GetMargin() const
{
	if (m_nMargin == UINT(-1))
	{
		const CGridDefaultCell* pDefaultCell = static_cast<const CGridDefaultCell*>(GetConstDefaultCell());
		if (!pDefaultCell)
			return 0;

		return pDefaultCell->GetMargin();
	}

	return m_nMargin;
}

BOOL CGridCell::IsEditing() const
{
	return m_bEditing;
}

BOOL CGridCell::IsDefaultFont() const
{
	return (m_plfFont == nullptr);
}

/////////////////////////////////////////////////////////////////////////////
// GridCell Operations

BOOL CGridCell::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, UINT nID, UINT nChar)
{
	if (m_bEditing)
	{
		if (m_pEditWnd)
			m_pEditWnd->SendMessage(WM_CHAR, nChar);
	}
	else
	{
		DWORD dwStyle = ES_LEFT;
		if (GetFormat() & DT_RIGHT)
			dwStyle = ES_RIGHT;
		else if (GetFormat() & DT_CENTER)
			dwStyle = ES_CENTER;

		m_bEditing = TRUE;

		// InPlaceEdit auto-deletes itself
		CGridCtrl* pGrid = GetGrid();
		m_pEditWnd = new CInPlaceEdit(pGrid, rect, dwStyle, nID, nRow, nCol, GetText(), nChar);
	}
	return TRUE;
}

void CGridCell::EndEdit()
{
	if (m_pEditWnd)
		static_cast<CInPlaceEdit*>(m_pEditWnd)->EndEdit();
}

void CGridCell::OnEndEdit()
{
	m_bEditing = FALSE;
	m_pEditWnd = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// CGridDefaultCell

CGridDefaultCell::CGridDefaultCell()
{
#ifdef _WIN32_WCE
    m_nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX;
#else
	m_nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS;
#endif
	m_crFgClr = CLR_DEFAULT;
	m_crBkClr = CLR_DEFAULT;
	m_Size = CSize(30, 10);
	m_dwStyle = 0;

#ifdef _WIN32_WCE
    LOGFONT lf;
    GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
    SetFont(&lf);
#else // not CE


	NONCLIENTMETRICS ncm;
#if defined(_MSC_VER) && (_MSC_VER < 1300)
    ncm.cbSize = sizeof(NONCLIENTMETRICS); // NONCLIENTMETRICS has an extra element after VC6
#else
	// Check the operating system's version
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (!GetVersionEx(reinterpret_cast<OSVERSIONINFO *>(&osvi)))
	{
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(reinterpret_cast<OSVERSIONINFO *>(&osvi));
	}

	if (osvi.dwMajorVersion > 5)
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
	else
		ncm.cbSize = sizeof(NONCLIENTMETRICS); //- sizeof(ncm.iPaddedBorderWidth);
#endif
	VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));

	CGridDefaultCell::SetFont(&(ncm.lfMessageFont));
#endif
}

CGridDefaultCell::~CGridDefaultCell()
{
	m_Font.DeleteObject();
}

DWORD CGridDefaultCell::GetStyle() const
{
	return m_dwStyle;
}

void CGridDefaultCell::SetStyle(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}

int CGridDefaultCell::GetWidth() const
{
	return m_Size.cx;
}

int CGridDefaultCell::GetHeight() const
{
	return m_Size.cy;
}

void CGridDefaultCell::SetWidth(int nWidth)
{
	m_Size.cx = nWidth;
}

void CGridDefaultCell::SetHeight(int nHeight)
{
	m_Size.cy = nHeight;
}

void CGridDefaultCell::SetData(LPARAM)
{
	ASSERT(FALSE);
}

void CGridDefaultCell::SetFont(const LOGFONT* plf)
{
	ASSERT(plf);

	if (!plf) return;

	m_Font.DeleteObject();
	m_Font.CreateFontIndirect(plf);

	CGridCell::SetFont(plf);

	// Get the font size and hence the default cell size
	CDC* pDC = CDC::FromHandle(::GetDC(nullptr));
	if (pDC)
	{
		CFont* pOldFont = pDC->SelectObject(&m_Font);

		SetMargin(pDC->GetTextExtent(_T(" "), 1).cx);
		m_Size = pDC->GetTextExtent(_T(" XXXXXXXXXXXX "), 14);
		m_Size.cy = (m_Size.cy * 3) / 2;

		pDC->SelectObject(pOldFont);
		ReleaseDC(nullptr, pDC->GetSafeHdc());
	}
	else
	{
		SetMargin(3);
		m_Size = CSize(40, 16);
	}
}

LOGFONT* CGridDefaultCell::GetFont() const
{
	ASSERT(m_plfFont); // This is the default - it CAN'T be nullptr!
	return m_plfFont;
}

CFont* CGridDefaultCell::GetFontObject() const
{
	ASSERT(m_Font.GetSafeHandle());
	return const_cast<CFont*>(&m_Font);
}

