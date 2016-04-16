#ifndef _I_SV_TESSELATOR_H
#define _I_SV_TESSELATOR_H
#include "ViewGeometry.h"

class ISvTesselator
{
public:
	virtual ~ISvTesselator()
	{
	}

	ISvTesselator(CViewVertexArray &rVertexArray, CViewElementArray &rElementArray, TOrgElemType CurrElemOrgType) :
	  VertexArray(rVertexArray), ElementArray(rElementArray), m_CurrElemOrgType(CurrElemOrgType)
	  {
	  }
	virtual SC3DRetCode AddPolygon( FLOAT_TYPE fThickness, SCUINT32 elemID,/* SCUINT16 nFlags,*/ SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs ) = 0;
protected:
	SC3DRetCode			AddSimpleTriangle( SCUINT32 elemID, SCUINT32 nPt1, SCUINT32 nPt2, SCUINT32 nPt3 ) const;
	SC3DRetCode			AddSimpleQuad( SCUINT32 elemID, SCUINT32 nPt1, SCUINT32 nPt2, SCUINT32 nPt3, SCUINT32 nPt4 ) const;
	CViewVertexArray &VertexArray;
	CViewElementArray &ElementArray;
	TOrgElemType	m_CurrElemOrgType;
};


#endif