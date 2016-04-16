// ForumViewGeometry.h: interface for the CForumViewGeometry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORUMVIEWGEOMETRY_H__559B3728_2BB4_442F_AAFC_3860198E6839__INCLUDED_)
#define AFX_FORUMVIEWGEOMETRY_H__559B3728_2BB4_442F_AAFC_3860198E6839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ViewGeometry.h"

class CForumViewGeometry : public CViewGeometry  
{
public:
	CForumViewGeometry();
	virtual ~CForumViewGeometry();
protected:
	/****** Forum objects support ********/
	void				ReadOprPolygon(SCHEMA *m_Project, NUM_ELEM_TYPE Nel, bool bUseThickness);

	void PostProcessSchema(SCHEMA *m_Project, bool bExpandProfiles, bool bExpandPlates) override;
	TOrgElemType GetElemOrgType(WORD wTypeElem) override;


};




#endif // !defined(AFX_FORUMVIEWGEOMETRY_H__559B3728_2BB4_442F_AAFC_3860198E6839__INCLUDED_)
