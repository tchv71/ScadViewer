// IsoViewGeometry.h: interface for the CIsoViewGeometry class.
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISOVIEWGEOMETRY_H__4C37CA27_C39F_4CA2_A109_B18A6D009D03__INCLUDED_)
#define AFX_ISOVIEWGEOMETRY_H__4C37CA27_C39F_4CA2_A109_B18A6D009D03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ViewGeometry.h"
#include "../OglIso/OglIso.h"

struct SOglIsoParam;
//struct DefMapInfo;
#ifndef SCAD11
#ifdef SCAD21
#else
#include "schema.h"
#endif
#else
#include "schema.hpp"
#include "Result.hpp"
//#include "scad.h"
//#include "Grand.h"
#endif




struct SVertexVal;
enum EIntegralFunc;

class CIsoViewerFrame;

class CIsoViewGeometry : public CViewGeometry  
{
public:
	CIsoViewGeometry(CIsoViewerFrame* pFrm, const SViewOptions* pViewOptions, const CDrawOptions *pDrawOptions);
	virtual ~CIsoViewGeometry();
	const COLORREF clIntervalOff;
public:
	void SetDefMapInfo(DefMapInfo* pDMI, const SOglIsoParam *pParams);
	void LoadFactors();
	void OnParamsChanged(void);
	void SetDefScale(double dblDefScale);
	void AddLine(size_t n1, size_t n2, COLORREF c);
	// Public methods
	void SetParams(SOglIsoParam *pParam);
	bool LoadIso(bool bShowProfile, bool bOptimize);
	void Get3DBox(const CRotator *Rot, S3DBox *Box, const CViewVertexArray * pVertexArray=nullptr) override;

	//IModelDraw implementation
	void OnDrawScene(IFemRenderer *pRenderer, const SViewOptions * pViewOptions, const CDrawOptions * pDrawOptions, const SPerspectiveView & rViewPos) override;
	void  DrawOptionsChanged(const CDrawOptions * DrawOptions, bool bShowUsedNodes) override;

	bool  IsIso() const override
	{ return true; }

	CString Format(double val) const override;

	// IGeomCut implementation
	void PerformCut(CCutter& rCutter, SCutRecord *r) override;
	void ClearCut(void) override;

	SOglIsoParam m_Params;
	ptrdiff_t m_nRealElements;

protected:
	struct DefMapInfo m_DMI;

	void IsoFlatElement(int nElement, EIntegralFunc eFunc);
	COLORREF GetColorrefForFactor(double val) const;
	bool GetNumUs(unsigned char &i, const BYTE &nSel);
	bool GetFactorForElVertexLoaded(int nNumElement, int nNumVertex, double & val, int * pnResultPoints);
	bool GetFactorForElVertex(int nNumElement, int nNumVertex,double &val, int* pnResultPoints);
	void SetDeformState(SOglIsoParam *pParam);
	size_t AddPoint(const S3dPoint& pt, const S3dPoint& ptDisp);
	size_t IsoBreakLine(const SVertexVal& p1, const SVertexVal& p2, double val);
	void SetupElementColors(const struct SViewOptions* pOptions, EDrawMode Mode) override;
	void AddQuad(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2, NODE_NUM_TYPE n3, NODE_NUM_TYPE n4, COLORREF c);
	void AddTriangle(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2, NODE_NUM_TYPE n3, COLORREF c);
	void IsoBreakTriangle(const DefMapInfo *DMI, SVertexVal valVertexs[], bool bDrawIsoLines);
	void IsoElement(SOglIsoParam *pParam,  int nElement);
	CViewElement m_curElement;
	std::vector<S3dPoint> m_vecDisp;
	double m_dblDefScale;
	CViewVertexArray m_OriginalVertexs;
	CViewFactorArray m_Factors;
	std::map<NODE_NUM_TYPE, NODE_NUM_TYPE> m_mapVertexFactors;
	int m_nOff;
	double m_dblDefScaleMult;
	CIsoViewerFrame* m_pFrm;
	friend class CIsoViewerFrame;
};

#endif // !defined(AFX_ISOVIEWGEOMETRY_H__4C37CA27_C39F_4CA2_A109_B18A6D009D03__INCLUDED_)
