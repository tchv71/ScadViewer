// SvGpcTesselator.cpp: implementation of the CSvGpcTesselator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SvGpcTesselator.h"
#include "gpc.h"
#include "SC3DMatrix.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SC3DRetCode CSvGpcTesselator::AddPolygon( FLOAT_TYPE fThickness, SCUINT32 elemID,/* SCUINT16 nFlags,*/ SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs )
{
	if (fabsf(fThickness)<1e-5f)
		return AddSimplePolygon(elemID,  nContour,  nPtCount,  pPtIDs);
	else
		return AddThickPolygon(fThickness, elemID,  nContour,  nPtCount,  pPtIDs);
}

SC3DRetCode CSvGpcTesselator::AddPolygon( SCUINT32 elemID, SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs )
{
	SCUINT32 nPt = 0, i;
	
	for( i = 0; i < nContour; i++ )
		nPt += nPtCount[i];

	if( nPt < 3 )
		return S3DRC_ERR_INVALID_ARG;

	return AddSimplePolygon( elemID, nContour, nPtCount, pPtIDs );
}

SC3DRetCode CSvGpcTesselator::AddSimplePolygon( SCUINT32 elemID, /*SCUINT16 nFlags,*/ SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs )
{
	SCUINT32 nPt = 0, i, j;
	SC3DRetCode rc;
	
	for( i = 0; i < nContour; i++ )
		nPt += nPtCount[i];

	if( nPt < 3 )
		return S3DRC_ERR_INVALID_ARG;
	
	SC3DPointVector basis;
	gpc_tristrip tristrip;
	gpc_vertex_list * pStrip;
	SCUINT32 nStartInd, nEndInd;	
	gpc_vertex * p2DPoints = (gpc_vertex*)_alloca( sizeof(gpc_vertex) * nPt );
	SC3DPoint ptOldNormal;
	SCBOOL bResetNormal = FALSE;

	rc = Cnv3Dto2D( nPt, pPtIDs, p2DPoints, basis );
	if( rc != S3DRC_OK )
		return rc;

	tristrip.num_strips = 0;
	tristrip.strip = NULL;

	rc = Cnv2DtoTristrip( nContour, nPtCount, p2DPoints, tristrip );

	if( rc != S3DRC_OK )
		return rc;
	{
		int i;
		for( i = 0; i < tristrip.num_strips; i++ )
		{
			pStrip = tristrip.strip + i;

			nStartInd = VertexArray.size();
			Cnv2Dto3D( basis, pStrip->num_vertices, pStrip->vertex/*, m_VertexArray*/ );
			nEndInd = VertexArray.size() - 2;
			for( j = nStartInd; j < nEndInd; j++ )
				if( ( j % 2 ) ^ ( nStartInd % 2 ) )
					AddSimpleTriangle( elemID,  j, j + 1, j + 2 );
				else
					AddSimpleTriangle( elemID,  j, j + 2, j + 1 );
		}
	}
	gpc_free_tristrip( &tristrip );
	return rc;
}

inline SC3DPoint pt(SViewVertex v)
{
	return SC3DPoint(v.x,v.y,v.z);
}

inline SViewVertex vertex(SC3DPoint vPt)
{
	SViewVertex v;
	v.x = vPt.m_fX;
	v.y = vPt.m_fY;
	v.z = vPt.m_fZ;
	v.FragmentFlag = v.Flag = true;
	return v;
}

SC3DRetCode CSvGpcTesselator::Cnv3Dto2D( SCUINT32 nPtCount, const SCUINT32 * pPtIndSrc, gpc_vertex * pPointsDest, SC3DPointVector& basis )
{
	if( !pPtIndSrc || !pPointsDest || nPtCount < 3 )
		return S3DRC_ERR_INVALID_ARG;

	SC3DPoint vX, vY, vZ, vRes;
	SCUINT32 i;
	bool bv1 = false, bv2 = false;
	SC3DMatrix mtrCnv;

	for( i = 0; i < nPtCount; i++ )
		if( pPtIndSrc[i] >= VertexArray.size() )
			return S3DRC_ERR_INVALID_ARG;

	for( i = 1; i < nPtCount; i++ )
		if( !bv1 )
		{
			if( pt(VertexArray[pPtIndSrc[0]]) != pt(VertexArray[pPtIndSrc[i]]) )
			{	
				vX = pt(VertexArray[pPtIndSrc[i]]) - pt(VertexArray[pPtIndSrc[0]]);
				bv1 = true;
			}
		}
		else
			if( !bv2 )
			{
				if( pt(VertexArray[pPtIndSrc[0]]) != pt(VertexArray[pPtIndSrc[i]]) )
				{	
					vY = pt(VertexArray[pPtIndSrc[i]]) - pt(VertexArray[pPtIndSrc[0]]);
					vZ = vY.CrossProduct( vX );
					if( vZ.AbsValue() != 0 )
					{
						bv2 = true;
						break;
					}
				}
			}
			else
				break;

	if( !bv1 || !bv2 )
		return S3DRC_ERR_INVALID_ARG;

	vX.Normalize();
	vZ.Normalize();
	vY = vX.CrossProduct( vZ );
	vY.Normalize();

	mtrCnv.m_fElements[0][0] = vX.m_fX;
	mtrCnv.m_fElements[0][1] = vX.m_fY;
	mtrCnv.m_fElements[0][2] = vX.m_fZ;
	mtrCnv.m_fElements[1][0] = vY.m_fX;
	mtrCnv.m_fElements[1][1] = vY.m_fY;
	mtrCnv.m_fElements[1][2] = vY.m_fZ;
	mtrCnv.m_fElements[2][0] = vZ.m_fX;
	mtrCnv.m_fElements[2][1] = vZ.m_fY;
	mtrCnv.m_fElements[2][2] = vZ.m_fZ;

	for( i = 0; i < nPtCount; i++ )
	{
		vRes = ( pt(VertexArray[pPtIndSrc[i]]) - pt(VertexArray[pPtIndSrc[0]]) ) * mtrCnv;
		pPointsDest[i].x = vRes.m_fX;
		pPointsDest[i].y = vRes.m_fY;
	}

	basis.clear();
	basis.push_back( pt(VertexArray[pPtIndSrc[0]]) );
	basis.push_back( vX );
	basis.push_back( vY );
	basis.push_back( vZ );

	return S3DRC_OK;
}

SC3DRetCode CSvGpcTesselator::Cnv2Dto3D( const SC3DPointVector& basis, SCUINT32 nPtCount, gpc_vertex * pPoints2D,  SCDOUBLE32 fZ)
{
	if( nPtCount == 0 )
		return S3DRC_OK;

	if( basis.size() != 4 || !pPoints2D )
		return S3DRC_ERR_INVALID_ARG;

	SC3DMatrix mtrCnv;
	SC3DPoint vPt;

	mtrCnv.m_fElements[0][0] = basis[1].m_fX;
	mtrCnv.m_fElements[0][1] = basis[1].m_fY;
	mtrCnv.m_fElements[0][2] = basis[1].m_fZ;
	mtrCnv.m_fElements[1][0] = basis[2].m_fX;
	mtrCnv.m_fElements[1][1] = basis[2].m_fY;
	mtrCnv.m_fElements[1][2] = basis[2].m_fZ;
	mtrCnv.m_fElements[2][0] = basis[3].m_fX;
	mtrCnv.m_fElements[2][1] = basis[3].m_fY;
	mtrCnv.m_fElements[2][2] = basis[3].m_fZ;
	mtrCnv.Inversing();

	for( UINT i = 0; i < nPtCount; i++ )
	{
		vPt.m_fX = (SCDOUBLE32)pPoints2D[i].x;
		vPt.m_fY = (SCDOUBLE32)pPoints2D[i].y;
		vPt.m_fZ = fZ;
		vPt = vPt * mtrCnv;
		vPt += basis[0];
		//vRes.push_back( vPt );
		VertexArray.push_back(vertex(vPt));
	}

	return S3DRC_OK;
}

SC3DRetCode	CSvGpcTesselator::Cnv2DtoTristrip( SCUINT32 nContour, const SCUINT32 * nPtCount, const gpc_vertex * pPoints, gpc_tristrip& tristrip )
{
	if( nContour == 0 || !nPtCount || !pPoints )
		return S3DRC_ERR_INVALID_ARG;

	gpc_polygon pgonarr[3];
	gpc_polygon *pgonsrc = &pgonarr[0], *pgonclip = &pgonarr[1], *pgonres = &pgonarr[2], *pgon;
	gpc_vertex_list vlist;
	UINT i;

	for( i = 0; i < 3; i++ )
	{
		pgonarr[i].num_contours = 0;
		pgonarr[i].hole = NULL;
		pgonarr[i].contour = NULL;
	}

	vlist.num_vertices = nPtCount[0];
	vlist.vertex = (gpc_vertex*)pPoints;
	gpc_add_contour( pgonres, &vlist, 0 );
	pPoints += nPtCount[0];

	if( pgonres->num_contours == 0 )
		return S3DRC_ERR_INVALID_ARG;

	for( i = 1; i < nContour; i++ )
	{
		gpc_free_polygon( pgonsrc );
		gpc_free_polygon( pgonclip );
		pgon = pgonsrc;
		pgonsrc = pgonres;
		pgonres = pgon;
		vlist.num_vertices = nPtCount[i];
		vlist.vertex = (gpc_vertex*)pPoints;
		gpc_add_contour( pgonclip, &vlist, 0 );
		gpc_polygon_clip( GPC_DIFF, pgonsrc, pgonclip, pgonres );
		pPoints += nPtCount[i];
	}	
	gpc_free_polygon( pgonsrc );
	gpc_free_polygon( pgonclip );
	
	if( pgonres->num_contours )
		gpc_polygon_to_tristrip( pgonres, &tristrip );
	else
		return S3DRC_ERR_INVALID_ARG;

	gpc_free_polygon( pgonres );

	return S3DRC_OK;
}

SC3DRetCode CSvGpcTesselator::AddThickPolygon(FLOAT_TYPE fThickness, SCUINT32 elemID,  SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs )
{
	SCUINT32 nPt = 0, i, j;
	SC3DRetCode rc = S3DRC_OK;
	
	for( i = 0; i < nContour; i++ )
		nPt += nPtCount[i];

	if( nPt < 3 )
		return S3DRC_ERR_INVALID_ARG;
/*
	if( SC_GET_PR_TYPE( nFlags ) == 0 )
		nFlags |= SC_MEPT_PRIM;
	if( SC_GET_ORIENT( nFlags ) == 0 )
		nFlags |= CalcOrient( pPtIDs[0], pPtIDs[1], pPtIDs[2] );
*/
	SC3DPoint * pPt = new SC3DPoint[nPt];
	SC3DPoint * pPtCnv = new SC3DPoint[nPt];
	SCUINT32 * ptIndUp = new SCUINT32[nPt];
	SCUINT32 * ptIndDown = new SCUINT32[nPt];
	SC3DPointVector basis;

	Transform3D( nPt, pPtIDs, pPt, basis );
	for( i = 0; i < nPt; i++ )
	{
		pPtCnv[i] = pPt[i];
		pPtCnv[i].m_fZ = fThickness / 2.f;
	}
	Transform3D( basis, nPt, pPtCnv );
	for( i = 0; i < nPt; i++ )
	{
		VertexArray.push_back(vertex(pPtCnv[i]));
		ptIndUp[i] = VertexArray.size()-1;//AddVertex( pPtCnv[i] );
	}

	for( i = 0; i < nPt; i++ )
	{
		pPtCnv[i] = pPt[i];
		pPtCnv[i].m_fZ = -fThickness / 2.f;
	}
	Transform3D( basis, nPt, pPtCnv );
	for( i = 0; i < nPt; i++ )
	{
		VertexArray.push_back(vertex(pPtCnv[i]));
		ptIndDown[i] = VertexArray.size()-1;//AddVertex( pPtCnv[i] );
	}

/*
	SC3DPoint vNormal, vOldNormal;
	SCBOOL bUseNormal;

	if( m_nGenMode & SC_MGT_NORMAL_DEMO )
	{
		vNormal = VertexArray[ptIndUp[0]] - VertexArray[pPtIDs[0]];
		vNormal.Normalize();
		bUseNormal = m_bUseNormal;
		vOldNormal = m_ptNormal;
		m_ptNormal = vNormal;
		m_bUseNormal = TRUE;
	}

	m_bUseThickness = FALSE;
*/	AddPolygon( elemID,  nContour, nPtCount, ptIndUp );

/*
	if( m_nGenMode & SC_MGT_NORMAL_DEMO )
	{
		vNormal *= -1.f;
		m_ptNormal = vNormal;
	}
*/
	AddPolygon( elemID, nContour, nPtCount, ptIndDown );
	//m_bUseThickness = TRUE;

/*
	if( m_nGenMode & SC_MGT_NORMAL_DEMO )
	{
		m_bUseNormal = bUseNormal;
		m_ptNormal = vOldNormal;
	}
*/
//	if( m_nGenMode & SC_MGT_FILL )
	{
		SCUINT32 nStart, nCurPt;

		nCurPt = 0;
		for( i = 0; i < nContour; i++ )
		{
			nStart = nCurPt;
			for( j = 0; j < nPtCount[i]-1; j++, nCurPt++ )
				if( i )
					AddSimpleQuad( elemID, ptIndUp[nCurPt+1], ptIndUp[nCurPt], ptIndDown[nCurPt+1], ptIndDown[nCurPt] );
				else
					AddSimpleQuad( elemID, ptIndUp[nCurPt], ptIndUp[nCurPt+1], ptIndDown[nCurPt], ptIndDown[nCurPt+1] );
			if( i )
				AddSimpleQuad( elemID, ptIndUp[nCurPt], ptIndUp[nStart], ptIndDown[nCurPt], ptIndDown[nStart] );
			else
				AddSimpleQuad( elemID, ptIndUp[nStart], ptIndUp[nCurPt], ptIndDown[nStart], ptIndDown[nCurPt] );
			nCurPt++;
		}	
	}
/*
	if( m_nGenMode & SC_MGT_WIREFRAME )
	{
		nFlags &= ~SC_MEPT_MASK;
		nFlags |= SC_MEPT_BORDER;

		for( i = 0; i < nPt; i++ )
			AddLine( elemID, nFlags, ptIndUp[i], ptIndDown[i] );
	}
*/
	delete [] pPt;
	delete [] pPtCnv;
	delete [] ptIndUp;
	delete [] ptIndDown;

	return rc;
}

SC3DRetCode CSvGpcTesselator::Transform3D( const SC3DPointVector& basis, SCUINT32 nPtCount, SC3DPoint * pPointsTrn ) const
{
	if( nPtCount == 0 )
		return S3DRC_OK;

	if( basis.size() != 4 || !pPointsTrn )
		return S3DRC_ERR_INVALID_ARG;

	SC3DMatrix mtrCnv;

	mtrCnv.m_fElements[0][0] = basis[1].m_fX;
	mtrCnv.m_fElements[0][1] = basis[1].m_fY;
	mtrCnv.m_fElements[0][2] = basis[1].m_fZ;
	mtrCnv.m_fElements[1][0] = basis[2].m_fX;
	mtrCnv.m_fElements[1][1] = basis[2].m_fY;
	mtrCnv.m_fElements[1][2] = basis[2].m_fZ;
	mtrCnv.m_fElements[2][0] = basis[3].m_fX;
	mtrCnv.m_fElements[2][1] = basis[3].m_fY;
	mtrCnv.m_fElements[2][2] = basis[3].m_fZ;
	mtrCnv.Inversing();

	for( UINT i = 0; i < nPtCount; i++ )
	{
		pPointsTrn[i] = pPointsTrn[i] * mtrCnv;
		pPointsTrn[i] += basis[0];
	}

	return S3DRC_OK;
}

SC3DRetCode CSvGpcTesselator::Transform3D( SCUINT32 nPtCount, const SCUINT32 * pPtIndSrc, SC3DPoint * pPointsDest, SC3DPointVector& basis ) const
{
	if( !pPtIndSrc || !pPointsDest || nPtCount < 3 )
		return S3DRC_ERR_INVALID_ARG;

	SC3DPoint vX, vY, vZ, vRes;
	SCUINT32 i;
	bool bv1 = false, bv2 = false;
	SC3DMatrix mtrCnv;

	for( i = 0; i < nPtCount; i++ )
		if( pPtIndSrc[i] >= VertexArray.size() )
			return S3DRC_ERR_INVALID_ARG;

	for( i = 1; i < nPtCount; i++ )
		if( !bv1 )
		{
			if( pt(VertexArray[pPtIndSrc[0]]) != pt(VertexArray[pPtIndSrc[i]]) )
			{	
				vX = pt(VertexArray[pPtIndSrc[i]]) - pt(VertexArray[pPtIndSrc[0]]);
				bv1 = true;
			}
		}
		else
			if( !bv2 )
			{
				if( pt(VertexArray[pPtIndSrc[0]]) != pt(VertexArray[pPtIndSrc[i]]) )
				{	
					vY = pt(VertexArray[pPtIndSrc[i]]) - pt(VertexArray[pPtIndSrc[0]]);
					vZ = vY.CrossProduct( vX );
					if( vZ.AbsValue() != 0 )
					{
						bv2 = true;
						break;
					}
				}
			}
			else
				break;

	if( !bv1 || !bv2 )
		return S3DRC_ERR_INVALID_ARG;

	vX.Normalize();
	vZ.Normalize();
	vY = vX.CrossProduct( vZ );
	vY.Normalize();

	mtrCnv.m_fElements[0][0] = vX.m_fX;
	mtrCnv.m_fElements[0][1] = vX.m_fY;
	mtrCnv.m_fElements[0][2] = vX.m_fZ;
	mtrCnv.m_fElements[1][0] = vY.m_fX;
	mtrCnv.m_fElements[1][1] = vY.m_fY;
	mtrCnv.m_fElements[1][2] = vY.m_fZ;
	mtrCnv.m_fElements[2][0] = vZ.m_fX;
	mtrCnv.m_fElements[2][1] = vZ.m_fY;
	mtrCnv.m_fElements[2][2] = vZ.m_fZ;

	for( i = 0; i < nPtCount; i++ )
	{
		vRes = ( pt(VertexArray[pPtIndSrc[i]]) - pt(VertexArray[pPtIndSrc[0]]) ) * mtrCnv;
		pPointsDest[i].m_fX = vRes.m_fX;
		pPointsDest[i].m_fY = vRes.m_fY;
		pPointsDest[i].m_fZ = 0.f;
	}

	basis.clear();
	basis.push_back( pt(VertexArray[pPtIndSrc[0]]) );
	basis.push_back( vX );
	basis.push_back( vY );
	basis.push_back( vZ );

	return S3DRC_OK;
}