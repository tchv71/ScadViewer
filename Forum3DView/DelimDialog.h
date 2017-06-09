#pragma once
#include "afxwin.h"
#include "..\ForumView_ENG\resource.h"


// CDelimDialog dialog
struct DefMapInfo;

class CDelimDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDelimDialog)
	const struct DefMapInfo* m_pDMI;
public:
	CDelimDialog(CWnd * pParent, double val, const DefMapInfo * pDMI);
	// standard constructor
	virtual ~CDelimDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_DELIM };

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_editValue;
	BOOL OnInitDialog() override;
	double m_dblValue;
	afx_msg void OnCbnSelchangeCombo1();
	virtual void OnOK();
};
