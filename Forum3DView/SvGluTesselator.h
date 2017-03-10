// SvGluTesselator.h: interface for the CSvGluTesselator class.
//
//////////////////////////////////////////////////////////////////////
// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_SVGLUTESSELATOR_H__40870B66_0351_47BC_94DB_FA2C4F7F71F9__INCLUDED_)
#define AFX_SVGLUTESSELATOR_H__40870B66_0351_47BC_94DB_FA2C4F7F71F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SvTesselator.h"
#include <gl\glu.h>

class CSvGluTesselator : public ISvTesselator
{
public:
	CSvGluTesselator(CViewVertexArray &rVertexArray, CViewElementArray &rElementArray, TOrgElemType CurrElemOrgType) :
	  ISvTesselator(rVertexArray,rElementArray, CurrElemOrgType), m_Type(0), m_nVertexsReceived(0), m_elemID(0), m_nFirstFanIndex(0)
	{}
	SC3DRetCode			AddPolygon(FLOAT_TYPE fThickness, SCUINT32 elemID, SCUINT32 nContour, const SCUINT32* nPtCount, const SCUINT32* pPtIDs) override;
protected:
	SC3DRetCode			AddSimplePolygon(SCUINT32 elemID, SCUINT32 nContour, const SCUINT32* nPtCount, const SCUINT32* pPtIDs);
	SC3DRetCode			AddThickPolygon(FLOAT_TYPE fThickness, SCUINT32 elemID,  SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs );
	
	void CallbackBegin(GLenum type); 
	void CallbackVertex(void * vertex_data);
	static void __stdcall beginData (GLenum type, void * polygon_data); 
	static void __stdcall vertexData (void * vertex_data, void * polygon_data);
private:
	GLenum m_Type;
	UINT m_nVertexsReceived;
	SCUINT32 m_elemID;
	size_t m_nFirstFanIndex;
};




#endif // !defined(AFX_SVGLUTESSELATOR_H__40870B66_0351_47BC_94DB_FA2C4F7F71F9__INCLUDED_)
