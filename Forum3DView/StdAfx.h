// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4DE64BEC_8A96_443A_97BE_E3544EF5B62A__INCLUDED_)
#define AFX_STDAFX_H__4DE64BEC_8A96_443A_97BE_E3544EF5B62A__INCLUDED_
#pragma warning( disable : 4284 )

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // основные и стандартные компоненты MFC
#include <afxext.h>         // расширения MFC


 // Выбрана поддержка базы данных с представлением.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // поддержка MFC для типовых элементов управления Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // поддержка MFC для типовых элементов управления Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // поддержка MFC для лент и панелей управления

// Stingray Objective Toolkit
//#include <toolkit\ot_dockingwindows.h>		// Objective Toolkit Docking Windows
//#include <toolkit\ot_toolbar.h>				// Objective Toolkit Customizable Toolbar/Menubar
//#include <toolkit\ot_treectrl.h>			// Objective Toolkit Tree control & Tree view
//#include <Toolkit\ot_progress.h>
typedef CString CSCADString;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#if defined(_DEBUG)
#import "..\..\..\buildingblocks\Bin\Debug\DSMP4.dll" no_namespace raw_interfaces_only
#else
#import "..\..\..\buildingblocks\Bin\Release\DSMP4.dll" no_namespace raw_interfaces_only
#endif

#endif // !defined(AFX_STDAFX_H__4DE64BEC_8A96_443A_97BE_E3544EF5B62A__INCLUDED_)
