// SCADDefProj.cpp : implementation file
//

#include "stdafx.h"
#include "SCADDefProj.h"
//#include "SCADRes.h"
#include "../ForumView_ENG/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
//		SCADDefProj

SCDefProjInfo SCADDefProj::m_Info[DPT_Size] =
{
	SCDefProjInfo( 0,	0),					// Top
	SCDefProjInfo( 0,	180),				// Bottom			
	SCDefProjInfo( 90,	-90),				// Left
	SCDefProjInfo( -90,	-90),				// Right
	SCDefProjInfo( 0,	-90),				// Front
	SCDefProjInfo( 180,  -90),				// Back
	SCDefProjInfo( 45,	-54.7f),			// SE_ISO
	SCDefProjInfo( -45,	-54.7f),			// SW_ISO
	SCDefProjInfo( -135, -54.7f),			// NE_ISO
	SCDefProjInfo( 135,  -54.7f),			// NW_ISO

	SCDefProjInfo( -20.7048f, -70.5288f)	// Dimetry
};

bool SCADDefProj::GetDefProjAt( int nPos, SCDefProjType& type, SCDefProjInfo& info )
{
	if( nPos < 0 || nPos >= DPT_Size )
		return FALSE;

	type = SCDefProjType(nPos);

	return GetInfo( type, info );
}

bool SCADDefProj::GetInfo( SCDefProjType type, SCDefProjInfo& info )
{
	if( type >= 0 && type < DPT_Size )
	{
		info = m_Info[type];

		return TRUE;
	}

	return FALSE;
}

CSCADString SCADDefProj::GetDesc( SCDefProjType type )
{
	CString strDesc;
	
	if( type >= 0 && type < DPT_Size )
	{
		CMenu menu;
		menu.LoadMenu(IDR_POPUP_MENUS);
		CMenu *pSubmenu = menu.GetSubMenu(0);
		ASSERT(pSubmenu);
		int k = 0;
		for (int i=0; i<pSubmenu->GetMenuItemCount(); i++)
		{
			if (pSubmenu->GetMenuState(i, MF_BYPOSITION) & MF_SEPARATOR)
				continue;
			if (k == type)
			{
				pSubmenu->GetMenuString(i, strDesc, MF_BYPOSITION);
				strDesc.Remove(_T('&'));
				break;
			}
			k++;
		}
	}

	return strDesc;
}

