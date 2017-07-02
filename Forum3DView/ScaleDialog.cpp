// ScaleDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "ScaleDialog.h"
#include "Resource.h"
#include "../OglIso/OglIso.h"
#include "GridSrc/GridCellCheck.h"


// диалоговое окно CScaleDialog

IMPLEMENT_DYNAMIC(CScaleDialog, CDepthDialogBar)


CScaleDialog::CScaleDialog() : CDepthDialogBar(IDD)
{
}

CScaleDialog::~CScaleDialog()
{
}



BEGIN_MESSAGE_MAP(CScaleDialog, CDepthDialogBar)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// обработчики сообщений CScaleDialog


INT_PTR CScaleDialog::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// TODO: добавьте специализированный код или вызов базового класса

	return CDepthDialogBar::OnToolHitTest(point, pTI);
}


void CScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_GRID, m_grid);
	m_grid.SetFixedRowCount(1);
	m_grid.SetFixedColumnCount(0);
	m_grid.SetListMode();

	// TODO: добавьте специализированный код или вызов базового класса
	
	CDepthDialogBar::DoDataExchange(pDX);
}


int CScaleDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDepthDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

CSize CScaleDialog::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	m_dwStyle =  m_dwStyle | CBRS_FLYBY;
	CRect rc;
	GetDlgItem(IDC_GRID)->GetWindowRect(rc);
	ScreenToClient(rc);
	return  CSize(rc.right+100, rc.bottom+100);
}


void CScaleDialog::SetDmi(const struct DefMapInfo * pDMI)
{
	//m_list.DeleteAllItems();
	m_grid.SetRowCount(pDMI->Scale_count);
	m_grid.SetColumnCount(4);
	m_grid.SetColumnWidth(0, 35);
	m_grid.SetColumnWidth(1, 35);
	m_grid.SetColumnWidth(2, 55);
	m_grid.SetColumnWidth(3, 55);

	for (int nIndex = 0; nIndex<pDMI->Scale_count;nIndex++)
	{
		m_grid.SetItemBkColour(nIndex, 1, pDMI->col[nIndex]);
		m_grid.SetCellType(nIndex, 0, RUNTIME_CLASS(CGridCellCheck));
		CGridCellCheck* pCell = dynamic_cast<CGridCellCheck *>(m_grid.GetCell(nIndex, 0));
		pCell->SetCheck(TRUE);
		m_grid.SetRowHeight(nIndex, m_grid.GetRowHeight(nIndex)-5);
		CString str;
		str.Format(_T("%6.2f"), pDMI->binter[nIndex]);
	    m_grid.SetItemState(nIndex,1, m_grid.GetItemState(nIndex,1) | GVIS_READONLY);
	    m_grid.SetItemState(nIndex,2, m_grid.GetItemState(nIndex,2) | GVIS_READONLY);
	    m_grid.SetItemState(nIndex,3, m_grid.GetItemState(nIndex,2) | GVIS_READONLY);

		m_grid.SetItemText(nIndex, 2, str);
		//m_list.SetItem(0, 0, LVIF_IMAGE | LVFIF_TEXT, _T("1.0"), 1, 0, 0, NULL);
		str.Format(_T("%6.2f"),pDMI->einter[nIndex]);
		m_grid.SetItemText(nIndex, 3, str);
	}
	m_grid.RedrawWindow();
}
