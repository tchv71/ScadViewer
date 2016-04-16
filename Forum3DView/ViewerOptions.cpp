// ViewerOptions.cpp : implementation file
//
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
//#include "ScadViewer.h"
#include "ViewerOptions.h"


// CViewerOptions

IMPLEMENT_DYNAMIC(CViewerOptions, CPropertySheet)
CViewerOptions::CViewerOptions(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CViewerOptions::CViewerOptions(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CViewerOptions::~CViewerOptions()
{
}


BEGIN_MESSAGE_MAP(CViewerOptions, CPropertySheet)
END_MESSAGE_MAP()


// CViewerOptions message handlers
