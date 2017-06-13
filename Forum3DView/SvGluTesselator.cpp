// SvGluTesselator.cpp: implementation of the CSvGluTesselator class.
//
//////////////////////////////////////////////////////////////////////
// Portions copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "SvGluTesselator.h"
#include <gl\gl.h>
#include <gl\glu.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

typedef void (_stdcall * GluTessCallbackType)(void);

SC3DRetCode CSvGluTesselator::AddSimplePolygon(SCUINT32 elemID, SCUINT32 nContour, const SCUINT32* nPtCount, const SCUINT32* pPtIDs)
{
	SCUINT32 nPt = 0, i, j;

	for( i = 0; i < nContour; i++ )
		nPt += nPtCount[i];

	if( nPt < 3 )
		return S3DRC_ERR_INVALID_ARG;
	m_elemID = elemID;
	GLUtesselator *tess=gluNewTess();
	gluTessCallback(tess, GLU_TESS_BEGIN_DATA, reinterpret_cast<GluTessCallbackType>(beginData));
	gluTessCallback(tess, GLU_TESS_VERTEX_DATA, reinterpret_cast<GluTessCallbackType>(vertexData));
	
	std::vector<GLdouble> arrCoords(nPt*3);
	GLdouble *ptCoords = &arrCoords[0];
	for (i=0;i<nPt;i++)
	{
		SViewVertex &pt = VertexArray[pPtIDs[i]];
		*ptCoords++ = pt.x;
		*ptCoords++ = pt.y;
		*ptCoords++ = pt.z;
	}
	ptCoords = &arrCoords[0];
	gluTessBeginPolygon(tess, this);
	for (i=0; i<nContour; i++)
	{
		gluTessBeginContour(tess);
		for (j=0; j<nPtCount[i];j++)
		{
			gluTessVertex(tess, ptCoords, ptCoords);
			ptCoords+=3;
		}
		gluTessEndContour(tess);
	}
	gluTessEndPolygon(tess);

	gluDeleteTess(tess);
	return S3DRC_OK;
}

void _stdcall CSvGluTesselator::beginData (GLenum type, void * polygon_data)
{
	static_cast<CSvGluTesselator *>(polygon_data)->CallbackBegin(type);
};
 
void _stdcall CSvGluTesselator::vertexData (void * vertex_data, void * polygon_data)
{
	static_cast<CSvGluTesselator *>(polygon_data)->CallbackVertex(vertex_data);
}

static std::vector<UINT> vertIdxs;


void CSvGluTesselator::CallbackBegin(GLenum type)
{
	m_nVertexsReceived =0;
	m_Type = type;
	m_nFirstFanIndex = 0;
	vertIdxs.clear();
}

void CSvGluTesselator::CallbackVertex(void * vertex_data)
{
	GLdouble *pData = static_cast<GLdouble *>(vertex_data);
	SViewVertex pt;
	pt.FragmentFlag = true;
	pt.Flag =0;
	pt.x = FLOAT_TYPE(*pData++);
	pt.y = FLOAT_TYPE(*pData++);
	pt.z = FLOAT_TYPE(*pData++);
	vertIdxs.push_back((int)VertexArray.push_back_check(pt));
	m_nVertexsReceived++;

	switch (m_Type)
	{
	case GL_TRIANGLES:
		if (m_nVertexsReceived%3 == 0)
			AddSimpleTriangle(m_elemID, vertIdxs[m_nVertexsReceived-3], vertIdxs[m_nVertexsReceived - 2], vertIdxs[m_nVertexsReceived-1]);
		break;
	case GL_TRIANGLE_STRIP:
		if (m_nVertexsReceived>2)
			AddSimpleTriangle(m_elemID, vertIdxs[m_nVertexsReceived - 3], vertIdxs[m_nVertexsReceived - 2], vertIdxs[m_nVertexsReceived - 1]);
		break;
	case GL_TRIANGLE_FAN:
		if (m_nVertexsReceived>2)
			AddSimpleTriangle(m_elemID, vertIdxs[m_nFirstFanIndex], vertIdxs[m_nVertexsReceived - 2], vertIdxs[m_nVertexsReceived-1]);
		break;
	}
}



SC3DRetCode CSvGluTesselator::AddPolygon(FLOAT_TYPE fThickness, SCUINT32 elemID,/* SCUINT16 nFlags,*/ SCUINT32 nContour, const SCUINT32* nPtCount, const SCUINT32* pPtIDs)
{
	if (fabsf(fThickness)<1e-5f)
		return AddSimplePolygon(elemID,  nContour,  nPtCount,  pPtIDs);
	else
		return AddThickPolygon(fThickness, elemID,  nContour,  nPtCount,  pPtIDs);
}

SC3DRetCode CSvGluTesselator::AddThickPolygon(FLOAT_TYPE fThickness, SCUINT32 elemID,  SCUINT32 nContour, const SCUINT32 * nPtCount, const SCUINT32 * pPtIDs )
{
	SCUINT32 nPt = 0, i,j;
	//SC3DRetCode rc = S3DRC_OK;
	
	for( i = 0; i < nContour; i++ )
		nPt += nPtCount[i];

	if( nPt < 3 )
		return S3DRC_ERR_INVALID_ARG;
	
	CVectorType vecNorm(0,0,0);
	for (i=0; i<nPtCount[0];i++)
	{
		SViewVertex &pt1 = VertexArray[pPtIDs[i]];
		SViewVertex &pt2 = VertexArray[pPtIDs[(i+1)%nPtCount[0]]];
		vecNorm.v[0] += (pt1.y-pt2.y)*(pt1.z+pt2.z);
		vecNorm.v[1] += (pt1.z-pt2.z)*(pt1.x+pt2.x);
		vecNorm.v[2] += (pt1.x-pt2.x)*(pt1.y+pt2.y);
	}
	vecNorm.Normalize();
	std::vector<UINT32> ptIndUp(nPt);
	std::vector<UINT32> ptIndDown(nPt);
	for (i=0; i<nPt;i++)
	{
		SViewVertex pt = VertexArray[pPtIDs[i]];
		pt.x+= vecNorm.v[0] * fThickness/2;
		pt.y+= vecNorm.v[1] * fThickness/2;
		pt.z+= vecNorm.v[2] * fThickness/2;
		ptIndUp[i] = UINT(VertexArray.push_back_check(pt));
	}
	for (i=0; i<nPt;i++)
	{
		SViewVertex pt = VertexArray[pPtIDs[i]];
		pt.x-= vecNorm.v[0] * fThickness/2;
		pt.y-= vecNorm.v[1] * fThickness/2;
		pt.z-= vecNorm.v[2] * fThickness/2;
		ptIndDown[i] = UINT(VertexArray.push_back_check(pt));
	}
	AddSimplePolygon( elemID,  nContour, nPtCount, &ptIndUp[0] );
	AddSimplePolygon( elemID, nContour, nPtCount, &ptIndDown[0] );

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
	
	return S3DRC_OK;
}
