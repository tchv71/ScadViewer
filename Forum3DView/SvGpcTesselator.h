// SvGpcTesselator.h: interface for the CSvGpcTesselator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGPCTESSELATOR_H__032F2A06_2D8E_480F_9952_97DAA1D118F3__INCLUDED_)
#define AFX_SVGPCTESSELATOR_H__032F2A06_2D8E_480F_9952_97DAA1D118F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SvTesselator.h"

class CSvGpcTesselator : public ISvTesselator
{
public:
	CSvGpcTesselator(CViewVertexArray &rVertexArray, CViewElementArray &rElementArray, TOrgElemType CurrElemOrgType) :
	  ISvTesselator(rVertexArray, rElementArray, CurrElemOrgType)
	  {}

	SC3DRetCode			AddPolygon(FLOAT_TYPE fThickness, SCUINT32 elemID, SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs );
protected:
	SC3DRetCode			AddPolygon( SCUINT32 elemID, SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs );
	SC3DRetCode			AddSimplePolygon( SCUINT32 elemID,  SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs );
	SC3DRetCode			Cnv3Dto2D( SCUINT32 nPtCount, const SCUINT32 * pPtIndSrc, gpc_vertex * pPointsDest, SC3DPointVector& basis );
	SC3DRetCode			Cnv2Dto3D( const SC3DPointVector& basis, SCUINT32 nPtCount, gpc_vertex * pPoints2D, SCDOUBLE32 fZ = 0.0f  );
	SC3DRetCode			Cnv2DtoTristrip( SCUINT32 nContour, const SCUINT32 * nPtCount, const gpc_vertex * pPoints, gpc_tristrip& tristrip );
	SC3DRetCode			AddThickPolygon(FLOAT_TYPE fThickness, SCUINT32 elemID,  SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs );
	SC3DRetCode			Transform3D( SCUINT32 nPtCount, const SCUINT32 * pPtIndSrc, SC3DPoint * pPointsDest, SC3DPointVector& basis ) const;
	SC3DRetCode			Transform3D( const SC3DPointVector& basis, SCUINT32 nPtCount, SC3DPoint * pPointsTrn ) const;
};

#endif // !defined(AFX_SVGPCTESSELATOR_H__032F2A06_2D8E_480F_9952_97DAA1D118F3__INCLUDED_)
