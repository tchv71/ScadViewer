// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#pragma once



// CViewerOptions

class CViewerOptions : public CPropertySheet
{
	DECLARE_DYNAMIC(CViewerOptions)

public:
	CViewerOptions(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CViewerOptions(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CViewerOptions();

protected:
	DECLARE_MESSAGE_MAP()
};


