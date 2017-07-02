#pragma once

#include "GridSrc/GridCtrl.h"

// CScalePane

class CScalePane : public CDockablePane
{
	enum EPaletteType {
		PT_HOT,
		PT_COLD,
		PT_GRAY
	} m_paletteType;

	DECLARE_DYNAMIC(CScalePane)

public:
	CScalePane();
	virtual ~CScalePane();

protected:
	CGridCtrl m_grid;
	CComboBox m_combo;
	CButton m_btnHot;
	CButton m_btnCold;
	CButton m_btnGray;
	CButton m_btnUniform;
	struct DefMapInfo *m_pDMI;
	int m_nRow;
	DECLARE_MESSAGE_MAP()
	void OnCbnSelchangeComboNum();
	void OnBnClickedButtonCold();
	void OnBnClickedButtonHot();
	void OnBnClickedButtonGray();
	void OnBnClickedButtonUniform();
	void OnBnClickedButtonInvert();
	void OnUpdateButton(CCmdUI* pCmdUI);

public:
	void SetDmi(const struct DefMapInfo * pDMI);
	virtual BOOL Create(UINT IDD, LPCTSTR lpszWindowName, CWnd* pParentWnd, CSize sizeDefault, BOOL bHasGripper, UINT nID, 
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_HIDE_INPLACE, DWORD dwTabbedStyle = AFX_CBRS_REGULAR_TABS, DWORD dwControlBarStyle = AFX_DEFAULT_DOCKING_PANE_STYLE);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg LRESULT OnSelEndOK(WPARAM wParam, LPARAM lParam);

	void DoDataExchange(CDataExchange* pDX) override;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


