#pragma once


// CScaleDlg dialog

class CScaleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScaleDlg)

public:
	CScaleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScaleDlg();

// Dialog Data
	enum { IDD = IDD_SCALE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonHot();
};
