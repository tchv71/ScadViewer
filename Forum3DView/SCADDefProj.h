/////////////////////////////////////////////////////////////////////////////
//
// SCADDefProj.h : interface of the default project manager
//
/////////////////////////////////////////////////////////////////////////////


#ifndef SCADDefProj_h
#define SCADDefProj_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Forum3DView\Forum3DView.h"
#include "DetViewOpts.h"
//#include "SC3DPoint.hxx"

#pragma	pack(push,1)

/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
struct FORUM3DVIEW_EXPORT SCDefProjInfo
{
	SCDefProjInfo()
	{
		m_fZ_rot = 0;
		m_fX_rot = 0;
	}

	SCDefProjInfo( const FLOAT_TYPE& fZrot, const FLOAT_TYPE& fXrot)
	{
		m_fZ_rot = fZrot;
		m_fX_rot = fXrot;
	}

	SCDefProjInfo& operator=( const SCDefProjInfo& dpi )
	{
		m_fZ_rot = dpi.m_fZ_rot;
		m_fX_rot = dpi.m_fX_rot;
		return *this;
	}

	FLOAT_TYPE		m_fZ_rot;
	FLOAT_TYPE		m_fX_rot;
};

class FORUM3DVIEW_EXPORT SCADDefProj// : virtual public CSCADBase
{
public:
	static	UINT		GetDefProjSize	() { return DPT_Size;}
	static	bool		GetDefProjAt	( int nPos, SCDefProjType& type, SCDefProjInfo& info );
	static	bool		GetInfo			( SCDefProjType type, SCDefProjInfo& info );
	static	CSCADString	GetDesc			( SCDefProjType type );

public:
	static	SCDefProjInfo	m_Info[DPT_Size];
};

#pragma	pack(pop)

#endif //SCADDefProj_h
