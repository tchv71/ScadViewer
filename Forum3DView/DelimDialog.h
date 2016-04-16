#pragma once
#include "afxwin.h"
#include "resource.h"


// CDelimDialog dialog

class CDelimDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDelimDialog)

public:
	CDelimDialog(CWnd* pParent = nullptr, double val = 0);   // standard constructor
	virtual ~CDelimDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_DELIM };

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editValue;
	BOOL OnInitDialog() override;
	double m_dblValue;
};
