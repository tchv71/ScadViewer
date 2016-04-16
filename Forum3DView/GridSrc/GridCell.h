/////////////////////////////////////////////////////////////////////////////
// GridCell.h : header file
//
// MFC Grid Control - Grid cell class header file
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
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCELL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_GRIDCELL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



class CGridCtrl;
#include "GridCellBase.h"

// Each cell contains one of these. Fields "row" and "column" are not stored since we
// will usually have acces to them in other ways, and they are an extra 8 bytes per
// cell that is probably unnecessary.

class CGridCell : public CGridCellBase
{
	friend class CGridCtrl;
	DECLARE_DYNCREATE(CGridCell)

	// Construction/Destruction
public:
	CGridCell();
	virtual ~CGridCell();

	// Attributes
public:
	void operator=(const CGridCell& cell);
	void SetText(LPCTSTR szText) override;
	void SetImage(int nImage) override;
	void SetData(LPARAM lParam) override;
	void SetGrid(CGridCtrl* pGrid) override;
	// virtual void SetState(const DWORD nState);  -  use base class version   
	void SetFormat(DWORD nFormat) override;
	void SetTextClr(COLORREF clr) override;
	void SetBackClr(COLORREF clr) override;
	void SetFont(const LOGFONT* plf) override;
	void SetMargin(UINT nMargin) override;
	CWnd* GetEditWnd() const override;
	void SetCoords(int /*nRow*/, int /*nCol*/) override;
	// don't need to know the row and
	// column for base implementation
	LPCTSTR GetText() const override;
	int GetImage() const override;
	LPARAM GetData() const override;
	CGridCtrl* GetGrid() const override;
	// virtual DWORD    GetState() const - use base class
	DWORD GetFormat() const override;
	COLORREF GetTextClr() const override;
	// TODO: change to use default cell
	COLORREF GetBackClr() const override;
	LOGFONT* GetFont() const override;
	CFont* GetFontObject() const override;
	UINT GetMargin() const override;
	BOOL IsEditing() const override;
	BOOL IsDefaultFont() const override;
	void Reset() override;

	// editing cells
public:
	BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar) override;
	void EndEdit() override;
protected:
	void OnEndEdit() override;

protected:
	CString m_strText; // Cell text (or binary data if you wish...)
	LPARAM m_lParam; // 32-bit value to associate with item
	int m_nImage; // Index of the list view item’s icon
	DWORD m_nFormat;
	COLORREF m_crFgClr;
	COLORREF m_crBkClr;
	LOGFONT* m_plfFont;
	UINT m_nMargin;

	BOOL m_bEditing; // Cell being edited?

	CGridCtrl* m_pGrid; // Parent grid control
	CWnd* m_pEditWnd;
};

// This class is for storing grid default values. It's a little heavy weight, so
// don't use it in bulk 
class CGridDefaultCell : public CGridCell
{
	DECLARE_DYNCREATE(CGridDefaultCell)

	// Construction/Destruction
public:
	CGridDefaultCell();
	virtual ~CGridDefaultCell();

public:
	virtual DWORD GetStyle() const;
	virtual void SetStyle(DWORD dwStyle);
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual void SetWidth(int nWidth);
	virtual void SetHeight(int nHeight);

	// Disable these properties
	void SetData(LPARAM /*lParam*/) override;

	void SetState(DWORD /*nState*/) override
	{
		ASSERT(FALSE);
	}

	DWORD GetState() const override
	{
		return CGridCell::GetState() | GVIS_READONLY;
	}

	void SetCoords(int /*row*/, int /*col*/) override
	{
		ASSERT(FALSE);
	}

	void SetFont(const LOGFONT* /*plf*/) override;
	LOGFONT* GetFont() const override;
	CFont* GetFontObject() const override;

protected:
	CSize m_Size; // Default Size
	CFont m_Font; // Cached font
	DWORD m_dwStyle; // Cell Style - unused
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCELL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)


