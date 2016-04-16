#pragma once
#include "Resource.h"
#include "depthdialogbar.h"
#include "GridSrc\GridCtrl.h"

struct DefMapInfo;

// диалоговое окно CScaleDialog

class CScaleDialog : public CDepthDialogBar
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog();   // стандартный конструктор
	virtual ~CScaleDialog();

// Данные диалогового окна

	enum { IDD = IDD_SCALE };

protected:

	DECLARE_MESSAGE_MAP()
public:
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	CGridCtrl m_grid;
	//CListCtrl m_list;
	//CImageList m_il;

public:
	void SetDmi(const struct DefMapInfo * pDMI);
};
