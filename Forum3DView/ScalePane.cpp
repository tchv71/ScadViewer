// ScalePane.cpp : implementation file
//

#include "stdafx.h"
#include "ScalePane.h"
#include "..\OglIso\OglIso.h"
#include "GridSrc\GridCellCheck.h"
#include "..\ForumView_ENG\resource.h"
#include "IsoViewerFrame.h"
#include "IsoViewGeometry.h"
#ifdef SCAD11
#include "RESULT.HPP"
//#include "scad.h"
//#include "Grand.h"
#endif
#include "ColourPopup.h"
#include "HSV2RGB.h"
#include "DelimDialog.h"

// CScalePane

IMPLEMENT_DYNAMIC(CScalePane, CDockablePane)

CScalePane::CScalePane() : m_paletteType(PT_COLD),
                           m_pDMI(nullptr), m_nRow(0)
{

}

CScalePane::~CScalePane()
{
}


BEGIN_MESSAGE_MAP(CScalePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
    ON_NOTIFY(NM_CLICK, IDC_GRID, OnGridClick)
    ON_MESSAGE(CPN_SELENDOK,     OnSelEndOK)
	ON_WM_ERASEBKGND()
	ON_CBN_SELCHANGE(IDC_COMBO_NUM, OnCbnSelchangeComboNum)
	ON_BN_CLICKED(IDC_BUTTON_HOT, OnBnClickedButtonHot)
	ON_BN_CLICKED(IDC_BUTTON_COLD, OnBnClickedButtonCold)
	ON_BN_CLICKED(IDC_BUTTON_GRAY, OnBnClickedButtonGray)
	ON_BN_CLICKED(IDC_BUTTON_UNIFORM, OnBnClickedButtonUniform)
	ON_BN_CLICKED(IDC_BTN_INVERT_SCALE, OnBnClickedButtonInvert)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_HOT, OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_COLD, OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_GRAY, OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BUTTON_UNIFORM, OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BTN_INVERT_SCALE, OnUpdateButton)

END_MESSAGE_MAP()


// CScalePane message handlers

BOOL  CScalePane::Create(UINT IDD,LPCTSTR lpszWindowName, CWnd* pParentWnd, CSize sizeDefault, BOOL bHasGripper, UINT nID, 
		DWORD dwStyle, DWORD dwTabbedStyle, DWORD dwControlBarStyle)
{
	m_lpszBarTemplateName = MAKEINTRESOURCE(IDD);
	BOOL bRes = CDockablePane::Create(lpszWindowName, pParentWnd, sizeDefault, bHasGripper, nID, dwStyle, dwTabbedStyle, dwControlBarStyle);
	EnableToolTips();
	return bRes;
};



int CScalePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	//CRect rc(0,0,100,100);
	//m_grid.Create(rc, this, IDC_GRID);
	m_grid.SetFixedRowCount(1);
	m_grid.SetFixedColumnCount(0);
	m_grid.SetListMode(FALSE);
	m_grid.EnableSelection(FALSE);
	return 0;
}


void CScalePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	CRect r;
	GetClientRect(&r);
	//int m_nCbHeight = 25;
	if (m_grid.GetSafeHwnd())
	{
		CRect rcGrid;
		m_grid.GetWindowRect(&rcGrid);
		ScreenToClient(&rcGrid);
		m_grid.SetWindowPos( nullptr, rcGrid.left, rcGrid.top,  r.right - rcGrid.left - 5, rcGrid.Height(), SWP_NOZORDER|SWP_NOACTIVATE );
	}
}

void CScalePane::SetDmi(const struct DefMapInfo * pDMI)
{
	//m_list.DeleteAllItems();
	m_grid.SetRowCount(pDMI->Scale_count+1);
	m_grid.SetColumnCount(4);
	m_grid.SetColumnWidth(0, 35);
	m_grid.SetColumnWidth(1, 35);
	m_grid.SetColumnWidth(2, 55);
	m_grid.SetColumnWidth(3, 55);
	m_grid.SetItemText(0,2,_T("Min"));
	m_grid.SetItemText(0,3,_T("Max"));
	m_grid.SetCellType(0, 0, RUNTIME_CLASS(CGridCellCheck));
	CGridCellCheck* pCell = dynamic_cast<CGridCellCheck *>(m_grid.GetCell(0, 0));
	pCell->SetCheck();

	for (int nIndex = 0; nIndex<pDMI->Scale_count;nIndex++)
	{
		int i = nIndex+1;
		m_grid.SetItemBkColour(i, 1, pDMI->col[nIndex]);
		int nHeight = dynamic_cast<CGridDefaultCell *>(m_grid.GetDefaultCell(FALSE,FALSE))->GetHeight();
		m_grid.SetCellType(i, 0, RUNTIME_CLASS(CGridCellCheck));
		CGridCellCheck* p_cell = dynamic_cast<CGridCellCheck *>(m_grid.GetCell(i, 0));
		p_cell->SetCheck(pDMI->IsDrw[nIndex]);
		m_grid.SetRowHeight(i, nHeight-5);
		CString str;
		str.Format(_T("%6.2f"), pDMI->binter[nIndex]);
	    m_grid.SetItemState(i,0, m_grid.GetItemState(i,0) | GVIS_READONLY);
	    m_grid.SetItemState(i,1, m_grid.GetItemState(i,1) | GVIS_READONLY);
	    m_grid.SetItemState(i,2, m_grid.GetItemState(i,2) | GVIS_READONLY);
	    m_grid.SetItemState(i,3, m_grid.GetItemState(i,3) | GVIS_READONLY);

		m_grid.SetItemText(i, 2, str);
		//m_list.SetItem(0, 0, LVIF_IMAGE | LVFIF_TEXT, _T("1.0"), 1, 0, 0, nullptr);
		str.Format(_T("%6.2f"),pDMI->einter[nIndex]);
		m_grid.SetItemText(i, 3, str);
	}
	m_grid.RedrawWindow();
	m_pDMI = const_cast<DefMapInfo *>(pDMI);
}

void CScalePane::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = reinterpret_cast<NM_GRIDVIEW*>(pNotifyStruct);
    //Trace(_T("Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	if (pItem->iRow == 0 && pItem->iColumn == 0)
	{
		CGridCellCheck* pCell = dynamic_cast<CGridCellCheck *>(m_grid.GetCell(0, 0));
		BOOL bCheck = !pCell->GetCheck();
		pCell->SetCheck(bCheck);

		for (int i=0; i<m_pDMI->Scale_count; i++)
		{
			CGridCellCheck* p_cell = dynamic_cast<CGridCellCheck *>(m_grid.GetCell(i+1, 0));
			p_cell->SetCheck(bCheck);
			m_pDMI->IsDrw[i] = bCheck;
		}
		GetParent()->SendMessage(WM_COMMAND, ID_PARAMS_CHANGED, 0);
	}
	else if (pItem->iColumn == 0)
	{
		CGridCellCheck* pCell = dynamic_cast<CGridCellCheck *>(m_grid.GetCell(pItem->iRow, 0));
		pCell->SetCheck(!pCell->GetCheck());
		m_pDMI->IsDrw[pItem->iRow-1] = 	pCell->GetCheck();
		GetParent()->SendMessage(WM_COMMAND, ID_PARAMS_CHANGED, 0);
	}
	else if (pItem->iColumn == 1)
	{
		CPoint p;
		GetCursorPos(&p);
		m_nRow = pItem->iRow;
		new CColourPopup(p, m_pDMI->col[pItem->iRow-1], this, nullptr, _T("Другие цвета..."));
	}
}

LRESULT CScalePane::OnSelEndOK(WPARAM wParam, LPARAM
                               /*wParam*/lParam)
{
	COLORREF Color = COLORREF(wParam);
	m_pDMI->col[m_nRow-1] =  Color;
	m_grid.SetItemBkColour(m_nRow, 1, Color);
	GetParent()->SendMessage(WM_COMMAND, ID_PARAMS_CHANGED, 0);
	m_grid.RedrawWindow();
    return TRUE;
}




void CScalePane::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_GRID, m_grid);             // associate the grid window with a C++ object
	DDX_Control(pDX, IDC_COMBO_NUM, m_combo);
	DDX_Control(pDX, IDC_BUTTON_HOT, m_btnHot);
	DDX_Control(pDX, IDC_BUTTON_COLD, m_btnCold);
	DDX_Control(pDX, IDC_BUTTON_GRAY, m_btnGray);
	DDX_Control(pDX, IDC_BUTTON_UNIFORM, m_btnUniform);
	int IDB=IDB_HOT;
	m_btnHot.SetBitmap(LoadBitmap(AfxFindResourceHandle(MAKEINTRESOURCE(IDB),RT_BITMAP), MAKEINTRESOURCE(IDB)));
	IDB=IDB_COLD;
	m_btnCold.SetBitmap(LoadBitmap(AfxFindResourceHandle(MAKEINTRESOURCE(IDB),RT_BITMAP), MAKEINTRESOURCE(IDB)));
	IDB=IDB_GRAY;
	m_btnGray.SetBitmap(LoadBitmap(AfxFindResourceHandle(MAKEINTRESOURCE(IDB),RT_BITMAP), MAKEINTRESOURCE(IDB)));
	IDB=IDB_UNIFORM;
	m_btnUniform.SetBitmap(LoadBitmap(AfxFindResourceHandle(MAKEINTRESOURCE(IDB),RT_BITMAP), MAKEINTRESOURCE(IDB)));
	//m_btnHot.SizeToContent();
	for (UINT i=2; i<=16; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		m_combo.AddString(str);
	}
	m_combo.AddString(_T("24"));
	m_combo.AddString(_T("32"));
	m_combo.AddString(_T("48"));
	m_combo.AddString(_T("64"));
	m_combo.SetCurSel(12);
	CDockablePane::DoDataExchange(pDX);
}


BOOL CScalePane::OnEraseBkgnd(CDC* pDC)
{
	CRect rectClip;
	pDC->GetClipBox(rectClip);

	CRect rect;
	GetClientRect(rect);

	CMFCVisualManager::GetInstance()->OnFillBarBackground(pDC, this, rect, rectClip);

	return CDockablePane::OnEraseBkgnd(pDC);
}

void CScalePane::OnCbnSelchangeComboNum()
{
	if (!m_pDMI)
		return;
	CString str;
	m_combo.GetWindowText(str);
	int nNum=0;
	_stscanf_s(str, _T("%d"), &nNum);
	m_pDMI->Scale_count = nNum;
	double dMaxFactor = m_pDMI->Max;
	double dMinFactor = m_pDMI->Min;
	m_pDMI->Step = (dMaxFactor-dMinFactor)/(m_pDMI->Scale_count);
	for (UINT i=0; i<UINT(m_pDMI->Scale_count);i++)
	{
		m_pDMI->binter[i]= dMinFactor+m_pDMI->Step*i;
		m_pDMI->einter[i]= dMinFactor+m_pDMI->Step*(i+1);
		m_pDMI->IsDrw[i] = TRUE;
	}
	int nDenom = nNum-1;
	if (m_paletteType==PT_GRAY)
	{
		for(int i=0;i<nNum;i++)
			m_pDMI->col[i] = CHSV2RGB::Hsl2Rgb255(0,0, 64+(240-64)*i/nDenom);
		SetDmi(m_pDMI);
		GetParent()->SendMessage(WM_COMMAND, ID_PARAMS_CHANGED, 0);
		return;
	}
	int Hs = 170;
	int nNumer = nDenom;
	COLORREF *pCol = m_pDMI->col;
	int i =0;
	for(; nNumer>0; nNumer -=4)
	{
		int H = Hs;
		int S = 255*nNumer/nDenom;
		COLORREF c = CHSV2RGB::Hsl2Rgb255(H, S, 128);
		if (m_paletteType == PT_COLD)
			pCol[i++] = c;
		else
			pCol[nDenom-i++] = c;
	}
	nNumer +=4;
	for(nNumer = 4-nNumer; nNumer <= nDenom; nNumer+=4)
	{
		int H = 43;
		int S = 255*nNumer/nDenom;
		COLORREF c = CHSV2RGB::Hsl2Rgb255(H, S, 128);
		if (m_paletteType == PT_COLD)
			pCol[i++] = c;
		else
			pCol[nDenom-i++] = c;
	}
	for(nNumer=1+(nDenom+1)%2; nNumer<=nDenom; nNumer +=2)
	{
		int H = m_paletteType == PT_COLD ? 43+(85-43)*nNumer/nDenom : 43-43*nNumer/nDenom ;
		int S = 255;
		COLORREF c = CHSV2RGB::Hsl2Rgb255(H, S, 128);
		if (m_paletteType == PT_COLD)
			pCol[i++] = c;
		else
			pCol[nDenom-i++] = c;
	}
	SetDmi(m_pDMI);
	GetParent()->SendMessage(WM_COMMAND, ID_PARAMS_CHANGED, 0);
}



void CScalePane::OnBnClickedButtonHot()
{
	m_paletteType = PT_HOT;
	OnCbnSelchangeComboNum();
}

void CScalePane::OnBnClickedButtonCold()
{
	m_paletteType = PT_COLD;
	OnCbnSelchangeComboNum();
}
void CScalePane::OnBnClickedButtonGray()
{
	m_paletteType = PT_GRAY;
	OnCbnSelchangeComboNum();
}

void CScalePane::OnBnClickedButtonUniform()
{
	if (!m_pDMI)
		return;
	CString str = reinterpret_cast<CIsoViewerFrame *>(GetParent())->Geom()->Format((m_pDMI->Max+m_pDMI->Min)/2);
	double val;
	_stscanf_s(str, _T("%lg"), &val);
	CDelimDialog dlg(this, val, m_pDMI );
	if (dlg.DoModal() == IDOK)
	{
		const double fDelim = dlg.m_dblValue;
		int nDelimPos = 0;
		for (; nDelimPos < m_pDMI->Scale_count; nDelimPos++)
		{
			if (fDelim < (m_pDMI->binter[nDelimPos] + m_pDMI->einter[nDelimPos]) / 2)
				break;
		}
		if (nDelimPos == m_pDMI->Scale_count)
			--nDelimPos;
		int H = 170;
		int S = 255;
		int V = 128;
		double fNextVal = nDelimPos == 0 ? m_pDMI->Max - ((m_pDMI->Max- fDelim)/m_pDMI->Scale_count * (m_pDMI->Scale_count-1)) : fDelim;
		if (nDelimPos == 0)
		{
			m_pDMI->einter[0] = fNextVal;
			m_pDMI->col[0] = RGB(255, 255, 255);
		}
		else
		{
			double fStep = (fDelim - m_pDMI->Min) / nDelimPos;
			for (int i = 0; i < nDelimPos; i++)
			{
				m_pDMI->binter[i] = m_pDMI->Min + fStep*i;
				m_pDMI->einter[i] = m_pDMI->Min + fStep*(i + 1);
				V = 128 + 127 * i / nDelimPos;
				m_pDMI->col[i] = CHSV2RGB::Hsl2Rgb255(H, S, V);
			}
		}

		int nCount = nDelimPos == 0 ? m_pDMI->Scale_count - nDelimPos - 1 : m_pDMI->Scale_count - nDelimPos;
		const double fStep = (m_pDMI->Max - fNextVal) / nCount;
		H = 0;
		S = 255;
		V = 255;
		int nSteps = m_pDMI->Scale_count - nDelimPos - 1;
		int j = 1;
		for (int i = nDelimPos == 0 ? 1 : nDelimPos; i < m_pDMI->Scale_count; i++, j++)
		{
			m_pDMI->binter[i] = fNextVal + (j - 1)*fStep;
			m_pDMI->einter[i] = fNextVal + j * fStep;
			V = nDelimPos == 0 ? 255 - 127 * j / nSteps : 255 - 127 * (j-1) / (nSteps+1);
			m_pDMI->col[i] = CHSV2RGB::Hsl2Rgb255(H, S, V);
		}
		SetDmi(m_pDMI);
		GetParent()->SendMessage(WM_COMMAND, ID_PARAMS_CHANGED, 0);
	}
}

void CScalePane::OnBnClickedButtonInvert()
{
	int i = 0;
	int j = m_pDMI->Scale_count - 1;
	for (; i < j; i++, j--)
	{
		std::swap(m_pDMI->col[i], m_pDMI->col[j]);
	}
	SetDmi(m_pDMI);
	GetParent()->SendMessage(WM_COMMAND, ID_PARAMS_CHANGED, 0);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppMemberFunctionMayBeConst
void CScalePane::OnUpdateButton(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}
