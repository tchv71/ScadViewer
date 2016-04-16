// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_STDAFX_H__F0ABEA19_493B_11D5_B1B3_000102C8846A__INCLUDED_)
#define _ATL_APARTMENT_THREADED 
#define AFX_STDAFX_H__F0ABEA19_493B_11D5_B1B3_000102C8846A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning( disable : 4284 )

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

// отключает функцию скрытия некоторых общих и часто пропускаемых предупреждений MFC
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // основные и стандартные компоненты MFC
#include <afxext.h>         // расширения MFC


#include <afxdisp.h>        // классы автоматизации MFC


 // Выбрана поддержка базы данных с представлением.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // поддержка MFC для типовых элементов управления Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // поддержка MFC для типовых элементов управления Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // поддержка MFC для лент и панелей управления

typedef CString CSCADString;
// Stingray Objective Toolkit
//#include <toolkit\ot_dockingwindows.h>		// Objective Toolkit Docking Windows
//#include <toolkit\ot_toolbar.h>				// Objective Toolkit Customizable Toolbar/Menubar
//#include <toolkit\ot_treectrl.h>			// Objective Toolkit Tree control & Tree view
//#include <Toolkit\ot_progress.h>

#if defined(_DEBUG)
#import "..\..\buildingblocks\Bin\Debug\DSMP4.dll" no_namespace raw_interfaces_only
#else
#import "..\..\buildingblocks\Bin\Release\DSMP4.dll" no_namespace raw_interfaces_only
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F0ABEA19_493B_11D5_B1B3_000102C8846A__INCLUDED_)
