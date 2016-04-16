#pragma once
#include "afxwin.h"
#include "ColorButton.h"
#include "DetViewOpts.h"
#include "afxcmn.h"


// COptionsMaterial dialog


class COptionsMaterial : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionsMaterial)

public:
	COptionsMaterial(SViewOptions &rViewOptions, bool bShowLanguage=false);
	virtual ~COptionsMaterial();

// Dialog Data
	enum { IDD = IDD_TAB_MATERIAL };
	CComboBox	m_Languages;

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CColorButton m_btnClrBars;
	CColorButton m_btnClrPlate;
	CColorButton m_btnClrBorder;
	CColorButton m_btnClrBackground;
	CColorButton m_btnClrNodes;
	CColorButton m_btnClrSolids;
	CColorButton m_btnClrDupes;
	CColorButton m_btnClrBoundX;
	CColorButton m_btnClrBoundY;
	CColorButton m_btnClrBoundZ;
	CColorButton m_btnClrBoundUX;
	CColorButton m_btnClrBoundUY;
	CColorButton m_btnClrBoundUZ;
	// Forum colors
	CColorButton m_btnClrWall;
	CColorButton m_btnClrSlab;
	CColorButton m_btnClrColumn;
	CColorButton m_btnClrBeam;
	CColorButton m_btnClrRoof;

public:
	int m_nLangID;
	SViewOptions &m_ViewOptions;
	BOOL OnInitDialog() override;
protected:
	bool m_bShowLanguage;
	CEdit m_edtLineWidth;
	CSpinButtonCtrl m_btnLineWidthSpin;
	CEdit m_edtNodeSize;
	CSpinButtonCtrl m_btnNodeSizeSpin;
	CButton m_btnCheckOGL10;
	CButton m_btnCheckHardwAccel;
	CButton m_btnCheckLineSmooth;
	CButton m_btnCheckRemoveDupPlanes;
	CButton m_btnCheckDrawOptimize;
	CButton m_btnShowUsedNodes;
};
