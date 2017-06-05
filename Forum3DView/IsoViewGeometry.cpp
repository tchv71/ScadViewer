// IsoViewGeometry.cpp: implementation of the CIsoViewGeometry class.
//
// Copyright (C) 2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#if defined(SCAD11) || defined(SCAD21)
#include "IsoViewGeometry.h"
#include "..\ogliso\OglIso.h"
#include "GlDraw.h"
#include "3diso.hpp"
#include "Renderer.h"
#include "IsoViewerFrame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIsoViewGeometry::CIsoViewGeometry(CIsoViewerFrame* pFrm, const SViewOptions * pViewOptions, const CDrawOptions * pDrawOptions) :
	CViewGeometry(pViewOptions,pDrawOptions),
	clIntervalOff(clWhite+1), m_dblDefScale(0),
	m_nOff(0),
	m_nRealElements(-1),
	m_dblDefScaleMult(1),
	m_pFrm(pFrm)
{

}

CIsoViewGeometry::~CIsoViewGeometry()
{

}

void CIsoViewGeometry::SetDeformState(SOglIsoParam *pParam)
{
	S3DBox box;
	Get3DBox(nullptr, &box);
	FLOAT_TYPE fSchemaSize = C3DVector<FLOAT_TYPE>(box.x_max-box.x_min, box.y_max-box.y_min, box.z_max - box.z_min).Length();
	FLOAT_TYPE fMaxDisp = 0;
	size_t nVertexs = m_OriginalVertexs.size();
	m_vecDisp.resize(0);
    for (UINT i=0; i<nVertexs; i++)
	{
		S3dPoint v;
#ifdef SCAD21
		double* val = ApiGetDisplace(pParam->hAPI, pParam->NPr+1, 1, i+1);
#else
		double* val = pParam->Res->GetDisplaceNode(pParam->NPr, i+1, 1);
#endif
		v.x = FLOAT_TYPE(val?val[0]:0);
		v.y = FLOAT_TYPE(val?val[1]:0);
		v.z = FLOAT_TYPE(val?val[2]:0);
		FLOAT_TYPE fDisp = C3DVector<FLOAT_TYPE>(v).Length();
		if (fDisp>fMaxDisp)
			fMaxDisp = fDisp;
		m_vecDisp.push_back(v);
	}
	FLOAT_TYPE fNorm = fSchemaSize*0.001f/fMaxDisp;
    for (UINT i=0; i<nVertexs; i++)
	{
		S3dPoint &v = m_vecDisp[i];
		v.x *= fNorm;
		v.y *= fNorm;
		v.z *= fNorm;
	}
	LoadFactors();
}

void CIsoViewGeometry::SetParams(SOglIsoParam *pParam)
{
	m_Params = *pParam;
	m_DMI = *(pParam->pDMI);
	m_Params.pDMI = &m_DMI;
}

bool CIsoViewGeometry::LoadIso(bool bShowProfile, bool bOptimize)
{
#ifdef SCAD21
	bool bRes = LoadFromSchema(m_Params.hAPI, bShowProfile, 0, false);
#else
	bool bRes = LoadFromSchema(m_Params.Res->GetSchema(), bShowProfile, 0, false);
#endif
	m_nRealElements = ElementArray.size();
	UINT i;
	m_OriginalVertexs = VertexArray;
	SetDeformState(&m_Params);
	//LoadFactors();
	// Set bContourOnly flag for all plates
	size_t nElements = ElementArray.size();
    for (i=0; i<nElements; i++)
	{
		CViewElement& el = ElementArray[i];
        if (el.OrgType != EL_BAR && el.DrawFlag && el.FragmentFlag)
		{
			if (m_Params.nTypeData != Iso_Nap_Flat)
				IsoElement(&m_Params, i);
			else
				IsoFlatElement(i, EIF_MAXMIN);
		}
	}
	if (m_pNodeCashe)
		delete m_pNodeCashe;
	m_pNodeCashe = new CNodeCashe(this, false);
	if (bOptimize)
		m_pNodeCashe->SetupLineStrips();
	m_bOptimize = bOptimize;
	m_OriginalVertexs = VertexArray;
	return bRes;
}


struct SVertexVal
{
	NODE_NUM_TYPE nVertex;
	double dblVal;
};

static double GetDispByOff(RESULT* pResData, NODE_NUM_TYPE Nuz, int npr, LRESULT off/*, int& Error*/)
{
	double* val;
#ifdef SCAD21
	SCHEMA *Prj = reinterpret_cast<SCHEMA  *>(pResData);
	switch (off)
	{

	case 16:
		// SUM
		val = ApiGetDisplace(Prj, npr+1, 1, UINT(Nuz+1));
		if (val == nullptr)
			return 0;
		return sqrt(pow(val[0], 2) + pow(val[1], 2) + 	pow(val[2], 2));

/*
	case 17:
		return FormCalc(Nuz, Error);//((s_prm.IsFormula) ? FormCalc(Nuz, Error) : 0.);
*/

	default:
		val =ApiGetDisplace(Prj, npr+1, 1, UINT(Nuz+1));
		return val ? val[off] : 0;
	}
#else
	SCHEMA *Prj = pResData->GetSchema();
	//int Error;
//	Error = POK;
	switch (off)
	{

	case 16:
		// SUM
		val = pResData->GetDisplaceNode(npr, Nuz+1, 1);
		if (!val)
			return 0;
		return sqrt(pow(val[0], 2) + pow(val[1], 2) + pow(val[2], 2));

/*
	case 17:
		return FormCalc(Nuz, Error);//((s_prm.IsFormula) ? FormCalc(Nuz, Error) : 0.);
*/

	default:
		val = pResData->GetDisplaceNode(npr, Nuz+1, 1);
		return val ? val[off] : 0;
	}
#endif
}

void CIsoViewGeometry::IsoFlatElement(int nElement, EIntegralFunc eFunc)
{
	CViewElement &el = ElementArray[nElement];
	short i;
	double valFunc = 0;
	for (i=0; i<el.NumVertexs()+1; i++)
	{
		double val = 0;
		if (!GetFactorForElVertex(nElement, i, val, nullptr))
			continue;
		switch(eFunc)
		{
		case EIF_AVG:
			valFunc+=val;
			break;
		case EIF_MIN:
			valFunc = min(valFunc, val);
			break;
		case EIF_MAX:
			valFunc = min(valFunc, val);
			break;
		case EIF_MAXMIN:
			if (fabs(val)>fabs(valFunc))
				valFunc = val;
			break;

		}
	}
	el.Color = el.OriginalColor = GetColorrefForFactor(valFunc);
	el.OrgType = EL_ISO;
	el.bContoured = true;
	el.bContourOnly = false;
}


void CIsoViewGeometry::IsoElement(SOglIsoParam *pParam, int nElement)
{
	CViewElement &El = ElementArray[nElement];
	const DefMapInfo *DMI = pParam->pDMI;
	El.bContourOnly = true;
	m_curElement = El;
	bool bDrawIsoLines = pParam->bDrawIsoLines;
	//SCHEMA *Prj = pParam->Res->GetSchema();

	if (El.Type == EL_TRIANGLE && m_Params.nTypeData == Iso_Disp)
	{
		SVertexVal valVertexs[3];
		for (UINT i=0; i<3; i++)
		{
			valVertexs[i].nVertex = El.Points[i];
			GetFactorForElVertexLoaded(nElement, i, valVertexs[i].dblVal, nullptr) ;
		}
		IsoBreakTriangle(pParam->pDMI, valVertexs, bDrawIsoLines);
	}
	else if (El.Type == EL_QUAD || (m_Params.nTypeData == Iso_Nap && El.Type == EL_TRIANGLE))
	{	
		S3dPoint ptMiddle(0,0,0);
		S3dPoint ptMiddleDisp(0,0,0);
		
		double dblMiddle = 0;
		const short nElPoints = El.NumVertexs();
		SVertexVal valElVertexs[8];
		SVertexVal valMiddle;
		short i;
		double valMax = 0;
		double valMin = 0;
		int nResultPoints = nElPoints+1;
		if (m_Params.nTypeData == Iso_Nap)
		{
			GetFactorForElVertexLoaded(nElement, 0, valMiddle.dblVal, &nResultPoints);
		}
		for (i=0; i<nResultPoints-1; i++)
		{
			valElVertexs[i].nVertex = i<nElPoints ? El.Points[i] : m_vecExtraPoints[El.m_nExtraPoints+1+i-nElPoints];
			double val =  0;
			GetFactorForElVertexLoaded(nElement, i, val, nullptr);
			valElVertexs[i].dblVal = val;
			if (i==0)
			{
				valMax = valMin = val;
			}
			else 
			{
				if (val>valMax)
					valMax = val;
				if (val<valMin)
					valMin = val;
			}
			if (i>=nElPoints)
				continue;
			S3dPoint pt=S3dPoint(VertexArray[valElVertexs[i].nVertex]);
			ptMiddle.x+= pt.x/nElPoints;
			ptMiddle.y+= pt.y/nElPoints;
			ptMiddle.z+= pt.z/nElPoints;
			pt=m_vecDisp[valElVertexs[i].nVertex];
			ptMiddleDisp.x+= pt.x/nElPoints;
			ptMiddleDisp.y+= pt.y/nElPoints;
			ptMiddleDisp.z+= pt.z/nElPoints;
			dblMiddle+= valElVertexs[i].dblVal/nElPoints; 
		}

		// Check to see that all values in in the same interval
		for (i=0; i<DMI->Scale_count; i++)
		{
			if (DMI->einter[i]<valMin)
				continue;
			if (DMI->einter[i]>valMax && m_Params.nTypeData != Iso_Nap)
			{
				COLORREF c = DMI->IsDrw[i] ? DMI->col[i] : clWhite;
				if (nElPoints == 4)
					AddQuad(El.Points[0], El.Points[1], El.Points[2], El.Points[3], c);
				else if (nElPoints == 3)
					AddTriangle(El.Points[0], El.Points[1], El.Points[2], c);
				return;
			}
			else
				break;
		}
		if (m_Params.nTypeData == Iso_Nap)
		{
			GetFactorForElVertexLoaded(nElement, nElPoints, valMiddle.dblVal, &nResultPoints);
			if (nResultPoints-1 != nElPoints)
				GetFactorForElVertexLoaded(nElement, nResultPoints-1, valMiddle.dblVal, nullptr);
		}
		else
			valMiddle.dblVal = dblMiddle;
		valMiddle.nVertex = AddPoint(ptMiddle, ptMiddleDisp);
		for (i=0; i<nElPoints; i++)
		{
 			SVertexVal valVertexs[3];
			valVertexs[0] = valElVertexs[i];
			valVertexs[1] = valElVertexs[(i+1)%nElPoints];
			valVertexs[2] = valMiddle;

			S3dPoint p1 = S3dPoint(VertexArray[valVertexs[0].nVertex]);
			S3dPoint p2 = S3dPoint(VertexArray[valVertexs[1].nVertex]);
			int k = nElPoints;
			for (; k<nResultPoints-1; k++) 
			{
				S3dPoint p = S3dPoint(VertexArray[valElVertexs[k].nVertex]);
				C3DVector<double> v1(p.x-p1.x,p.y-p1.y,p.z-p1.z);
				C3DVector<double> v2(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
				if (v1.CrossProduct(v2).Length()<1e-5)
				{
					// Доп. точка внутри грани
					SVertexVal valSave = valVertexs[1];
					valVertexs[1] = valElVertexs[k];
					IsoBreakTriangle(pParam->pDMI, valVertexs, bDrawIsoLines);
					valVertexs[0] = valElVertexs[k];
					valVertexs[1] = valSave;
					break;
				}
			}
			valVertexs[2] = valMiddle;
			IsoBreakTriangle(pParam->pDMI, valVertexs, bDrawIsoLines);
		}
	

	}
	
}

void CIsoViewGeometry::IsoBreakTriangle(const DefMapInfo *DMI, SVertexVal valVertexs[], bool bDrawIsoLines)
{
	std::vector<NODE_NUM_TYPE> vec;
	COLORREF clIsoLine = clBlack;
	// Sort triangle points by value
	{
		if (valVertexs[0].dblVal > valVertexs[1].dblVal)
			std::swap(valVertexs[0], valVertexs[1]);
		if (valVertexs[1].dblVal > valVertexs[2].dblVal)
			std::swap(valVertexs[1],valVertexs[2]);
		if (valVertexs[0].dblVal > valVertexs[1].dblVal)
			std::swap(valVertexs[0],valVertexs[1]);
	}
	vec.push_back(valVertexs[0].nVertex);
	double lastVal = valVertexs[0].dblVal;
	for (short i=0; i<DMI->Scale_count; i++)
	{
		double dmiVal = DMI->einter[i];
		if (dmiVal<valVertexs[0].dblVal)
			continue;
		COLORREF c = DMI->IsDrw[i] ? DMI->col[i] : clWhite;
		if (dmiVal<valVertexs[1].dblVal)
		{
			size_t n1 = IsoBreakLine(valVertexs[0], valVertexs[1],  dmiVal);
			size_t n2 = IsoBreakLine(valVertexs[0], valVertexs[2],  dmiVal);
			if (bDrawIsoLines && DMI->IsDrw[i])
				AddLine(n1, n2, clIsoLine);
			if (vec.size()==1)
			{
				AddTriangle(vec[0], n2, n1, c);
			}
			else
			{
				//AddQuad(vec[0], vec[1], n2, n1, c);
				AddTriangle(vec[0], vec[1], n2, c);
				AddTriangle(vec[0], n2, n1, c);
			}
			vec.resize(0);
			vec.push_back(n1);
			vec.push_back(n2);
			lastVal = DMI->einter[i];
		}
		else if (dmiVal<valVertexs[2].dblVal)
		{
			size_t n1 = IsoBreakLine(valVertexs[1], valVertexs[2], dmiVal);
			size_t n2 = IsoBreakLine(valVertexs[0], valVertexs[2], dmiVal);
			if (bDrawIsoLines && DMI->IsDrw[i])
				AddLine(n1, n2, clIsoLine);
			if (lastVal < valVertexs[1].dblVal)
			{
				if (vec.size()==1)
				{
					//AddQuad(vec[0], n2, n1,  valVertexs[1].nVertex, c);
					AddTriangle(vec[0], n2, n1, c);
					AddTriangle(vec[0], n1, valVertexs[1].nVertex, c);
				}
				else
				{
					AddTriangle(vec[0], vec[1], valVertexs[1].nVertex, c);
					//AddQuad(vec[1], n2, n1, valVertexs[1].nVertex, c);
					AddTriangle(vec[1], n1, valVertexs[1].nVertex, c);
					AddTriangle(vec[1], n2, n1, c);
				}
			}
			else
			{
				if (vec.size()==1)
				{
					AddTriangle(vec[0], n2, n1, c);
					AddTriangle(vec[0], n1, valVertexs[1].nVertex, c);
				}
				else
				{
					//AddQuad(vec[0], vec[1], n2, n1, c);
					AddTriangle(vec[0], vec[1], n2, c);
					AddTriangle(vec[0], n2, n1, c);
				}
			}
			vec.resize(0);
			vec.push_back(n1);
			vec.push_back(n2);
			lastVal = dmiVal;
		}
		else 
		{
			if (lastVal < valVertexs[1].dblVal)
			{
				if (vec.size()==1)
				{
					AddTriangle(vec[0], valVertexs[2].nVertex, valVertexs[1].nVertex, c);
				}
				else
				{
					//AddQuad(vec[0], vec[1], valVertexs[2].nVertex, valVertexs[1].nVertex, c);
					AddTriangle(vec[0], vec[1], valVertexs[2].nVertex, c);
					AddTriangle(vec[0], valVertexs[2].nVertex, valVertexs[1].nVertex, c);
				}
			}
			else
			{
				if (vec.size()==1)
				{
					AddTriangle(vec[0], valVertexs[2].nVertex, valVertexs[1].nVertex, c);
				}
				else
				{
					AddTriangle(vec[0], vec[1], valVertexs[2].nVertex, c);
				}
			}
			break;
		}
	}
}

// Break the line between p1 and p2 by val
// Return the newly created vertex index
size_t CIsoViewGeometry::IsoBreakLine(const SVertexVal& p1, const SVertexVal& p2, double val)
{
	S3dPoint pt1 = S3dPoint(VertexArray[p1.nVertex]);
	S3dPoint pt2 = S3dPoint(VertexArray[p2.nVertex]);
	double t = (val - p1.dblVal)/(p2.dblVal - p1.dblVal);
	S3dPoint pt;
	pt.x = FLOAT_TYPE(pt1.x+(pt2.x-pt1.x)*t);
	pt.y = FLOAT_TYPE(pt1.y+(pt2.y-pt1.y)*t);
	pt.z = FLOAT_TYPE(pt1.z+(pt2.z-pt1.z)*t);

	S3dPoint ptDisp;
	S3dPoint pt1d = m_vecDisp[p1.nVertex];
	S3dPoint pt2d = m_vecDisp[p2.nVertex];
	ptDisp.x = FLOAT_TYPE(pt1d.x+(pt2d.x-pt1d.x)*t);
	ptDisp.y = FLOAT_TYPE(pt1d.y+(pt2d.y-pt1d.y)*t);
	ptDisp.z = FLOAT_TYPE(pt1d.z+(pt2d.z-pt1d.z)*t);
	return AddPoint(pt, ptDisp);
}

size_t CIsoViewGeometry::AddPoint(const S3dPoint& pt, const S3dPoint& ptDisp)
{
	SViewVertex v;
	v.x = pt.x;
	v.y = pt.y;
	v.z = pt.z;
	v.Flag = 0;
	v.FragmentFlag = false;
	v.nMainVertex = -1;
	VertexArray.push_back(v);
	m_vecDisp.push_back(ptDisp);
	return VertexArray.size() -1;
}

void CIsoViewGeometry::AddLine(size_t n1, size_t n2, COLORREF c)
{
	CViewElement el;
	el.DrawFlag = el.FragmentFlag = true;
	el.Color = el.OriginalColor = c;
	el.bContoured = true;
	el.Type = EL_LINE;
	el.OrgType = EL_ISO;
	el.Norm = m_curElement.Norm;
	el.OrgNorm = m_curElement.OrgNorm;
	el.NumElem = m_curElement.NumElem;
	el.Points[0] = n1;
	el.Points[1] = n2;
	el.Points[2] = el.Points[3] = -1;

	ElementArray.push_back(el);

}


void CIsoViewGeometry::AddTriangle(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2, NODE_NUM_TYPE n3, COLORREF c)
{
	CViewElement el;
	el.DrawFlag = m_curElement.DrawFlag;
	el.FragmentFlag = m_curElement.FragmentFlag;
	el.Color = el.OriginalColor = c;
	el.bContoured = false;
	el.Type = EL_TRIANGLE;
	el.OrgType = m_curElement.OrgType;
	el.Norm = m_curElement.Norm;
	el.OrgNorm = m_curElement.OrgNorm;
	el.NumElem = m_curElement.NumElem;
	el.Points[0] = n1;
	el.Points[1] = n2;
	el.Points[2] = n3;
	el.Points[3] = -1;
	ElementArray.push_back(el);
}

void CIsoViewGeometry::AddQuad(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2, NODE_NUM_TYPE n3, NODE_NUM_TYPE n4, COLORREF c)
{
	CViewElement el;
	el.DrawFlag = m_curElement.DrawFlag;
	el.FragmentFlag = m_curElement.FragmentFlag;
	el.Color = el.OriginalColor = c;
	el.bContoured = false;
	el.Type = EL_QUAD;
	el.OrgType = m_curElement.OrgType;
	el.Norm = m_curElement.Norm;
	el.OrgNorm = m_curElement.OrgNorm;
	el.NumElem = m_curElement.NumElem;
	el.Points[0] = n1;
	el.Points[1] = n2;
	el.Points[2] = n3;
	el.Points[3] = n4;
	ElementArray.push_back(el);

}

void CIsoViewGeometry::SetupElementColors(const struct SViewOptions* pOptions, EDrawMode Mode)
{
    // Замена цвета элемента на настройки
	for (UINT i =0; i<ElementArray.size(); i++)
	{
		CViewElement &el = ElementArray[i];
		if (el.OrgType == EL_ISO)
			continue;
		if (!el.bContoured)
		{
			el.Color = el.OriginalColor;
			if (!el.IsContour() && ElementArray.GetSelectedElement() !=0 && el.NumElem == ElementArray.GetSelectedElement())
				el.Color ^= 0xffffff;

			continue;
		}
		SetElColor(el, pOptions, Mode); 
	}

}

void CIsoViewGeometry::ClearCut(void)
{
	CViewGeometry::ClearCut();
	LoadFactors();
};

void CIsoViewGeometry::PerformCut(CCutter& rCutter, SCutRecord *r)
{
	double dblSave = m_dblDefScale;
	SetDefScale(0);
	CViewGeometry::PerformCut(rCutter, r);
	LoadFactors();
	SetDefScale(dblSave);
}


void CIsoViewGeometry::SetDefScale(double dblDefScale)
{
	m_dblDefScale = dblDefScale;
	size_t nVertexs = m_OriginalVertexs.size();
	ASSERT(VertexArray.size()>=m_OriginalVertexs.size());
	if (VertexArray.size()!=m_OriginalVertexs.size()+ElementArray.m_mapVertexs.size())
		return;
	for (UINT i = 0; i < nVertexs; i++)
	{
		SViewVertex& vO = m_OriginalVertexs[i];
		SViewVertex& v = VertexArray[i];
		NODE_NUM_TYPE nDispIndex = v.nMainVertex == -1 ? i : v.nMainVertex;
		v.x = vO.x + FLOAT_TYPE(m_vecDisp[nDispIndex].x*dblDefScale*m_dblDefScaleMult);
		v.y = vO.y + FLOAT_TYPE(m_vecDisp[nDispIndex].y*dblDefScale*m_dblDefScaleMult);
		v.z = vO.z + FLOAT_TYPE(m_vecDisp[nDispIndex].z*dblDefScale*m_dblDefScaleMult);
	}
	for (auto it = ElementArray.m_mapVertexs.begin(); it != ElementArray.m_mapVertexs.end(); ++it)
	{
		UINT i = it->first;
		SViewVertex& vO = m_OriginalVertexs[i];
		SViewVertex &v1 = VertexArray[it->second];
		NODE_NUM_TYPE nDispIndex = v1.nMainVertex == -1 ? i : v1.nMainVertex;
		v1.x = vO.x + FLOAT_TYPE(m_vecDisp[nDispIndex].x*dblDefScale*m_dblDefScaleMult);
		v1.y = vO.y + FLOAT_TYPE(m_vecDisp[nDispIndex].y*dblDefScale*m_dblDefScaleMult);
		v1.z = vO.z + FLOAT_TYPE(m_vecDisp[nDispIndex].z*dblDefScale*m_dblDefScaleMult);
	}

	LoadFactors();
}

#include "Cutter.h"
/*
void CIsoViewGeometry::PerformCut(CCutter& rCutter, SCutRecord *r)
{
	static bool bRec = false;
	if (bRec)
	{
		CViewGeometry::PerformCut(rCutter, r);
		return;
	}

	CViewVertexArray v = VertexArray;
	VertexArray = m_OriginalVertexs;
	ElementArray.resize(m_nRealElements);
	CViewGeometry::PerformCut(rCutter, r);

//    for (UINT i=0; i<VertexArray.size(); i++)
//	{
//		S3dPoint& vO= m_OriginalVertexs[i];
//		VertexArray[i].x = v[i].x;
//		VertexArray[i].y = v[i].y;
//		VertexArray[i].z = v[i].z;
//	}

	OnParamsChanged();
	bRec = true;
	rCutter.RedoAll();
	bRec = false;
}
*/
// ReSharper disable once CppMemberFunctionMayBeConst
void CIsoViewGeometry::OnParamsChanged()
{
	m_pFrm->OnParamsChanged();
/*
	bool bRes = false;
	//m_OriginalVertexs = VertexArray;
	CViewElementArray els = ElementArray;
	int nOldElements = els.size();
	bRes = LoadFromSchema(m_Params.Res->GetSchema(), 0, 0, false);
	UINT i;

	UINT nElements = ElementArray.size();
	SetDeformState(&m_Params);
	//LoadFactors(m_Params.nTypeFactor);
	// Set bContourOnly flag for all plates
    for (i=0; i<nElements; i++)
	{
		ElementArray[i].FragmentFlag = els[i].FragmentFlag;
		ElementArray[i].DrawFlag = els[i].DrawFlag;
        if (ElementArray[i].Type != EL_LINE)
            IsoElement(&m_Params, i);
	}
	if (m_pNodeCashe)
		delete m_pNodeCashe;
	m_pNodeCashe = new CNodeCashe(this, false);
	m_bOptimize = true;
	//m_OriginalVertexs = VertexArray;
	SetDefScale(m_dblDefScale);
*/
}

#ifdef SCAD21

namespace spr
{
	class CSchema;
	class CElemForm;
	class CElemData
	{
	public:
		unsigned char SetElem(class spr::CElemForm const &, unsigned int, unsigned int);
	};
	
	class CResultElemEffors : public ApiElemEffors {};


	class CResult
	{
	public:
		unsigned char  GetElemEffors(spr::CResultElemEffors &, unsigned int, unsigned char, unsigned char, unsigned char);
	};
	class CPhraseText;
};

template<>
class std::vector<spr::CPhraseText, std::allocator<spr::CPhraseText>>
{
public:
	void clear();
};

APICode _ApiGetEfforsXXX(unsigned NumElem, spr::CSchema * pSchem, ApiElemEffors ** ppEffors, DWORD TypeRead)
{
	*ppEffors = nullptr;
	std::vector<spr::CPhraseText, std::allocator<spr::CPhraseText>> *pVec = reinterpret_cast<std::vector<spr::CPhraseText, std::allocator<spr::CPhraseText>> *>((BYTE*)pSchem + 0x67fb6);
	pVec->clear();
	*(WORD*)((BYTE*)pSchem + 0x67fb4) = 0;
	//int edx_13 = SLICE((pSchem->dw67BFA - pSchem->ptr67BF6) *s 0x4EC4EC4F, word32, 32);
	if (true) //edx_13 >> 0x05 >> 0x1F != 0x00)
	{
		//Eq_724 eax_67 = pSchem->t9CBC;
		if (true)//pSchem->dw9CC0 - eax_67 >> 0x03 >= 0x01 && eax_67 != 0x00)
		{
			spr::CElemData *pElem = reinterpret_cast<spr::CElemData*>((BYTE*)pSchem + 0x67d80);
			if (pElem->SetElem(reinterpret_cast<spr::CElemForm const &>(*((BYTE*)pSchem + 0x433e)), NumElem, 0x00) != 0x00)
			{
				//Eq_724 eax_96 = pSchem->t9CBC;
				//if (pSchem->dw9CC0 - eax_96 >> 0x03 < 0x01 || (eax_96 == 0x00 || (((eax_96 - 0x08))[ebx].dw0000 & *(eax_96 - 0x04)) == ~0x00))
				//	return;
				spr::CResult *pRes = reinterpret_cast<spr::CResult*>((BYTE*)pSchem + 0x2f67);
				spr::CResultElemEffors &rEff = reinterpret_cast<spr::CResultElemEffors &>(*((BYTE*)pSchem + 0x67f54));
				if (pRes->GetElemEffors(rEff, NumElem, 1, (BYTE)TypeRead, 2/*1*/) != 0x00)
				{
					*ppEffors = &rEff;
					return APICode::APICode_OK;
				}
				else
					return APICode::APICode_InternalError;
			}
			else
				return APICode::APICode_IndexError;
		}
	}
	return APICode::APICode_NoResult;
}





APICode ApiGetEfforsXXX(ScadAPI lpAPI, UINT NumElem, ApiElemEffors ** Effors, BYTE TypeRead)
{
	return _ApiGetEfforsXXX(NumElem, (spr::CSchema*)((DWORD*)lpAPI)[0], Effors, TypeRead);
}
#endif


bool CIsoViewGeometry::GetFactorForElVertexLoaded(int nNumElement, int nNumVertex, double &val, int* pnResultPoints)
{
	if ((m_Params.nTypeData != Iso_Nap && m_Params.nTypeData != Iso_Nap_Flat) || nNumVertex >= ElementArray[nNumElement].NumVertexs())
	{
		return GetFactorForElVertex(nNumElement, nNumVertex, val, pnResultPoints);
	}
	int nVertex = ElementArray[nNumElement].Points[nNumVertex];
	val = m_Factors[m_mapVertexFactors[nVertex]-1].fFactor;
	if (pnResultPoints)
		*pnResultPoints = ElementArray[nNumElement].NumVertexs() + 1;
	return true;
}

bool CIsoViewGeometry::GetFactorForElVertex(int nNumElement, int nNumVertex, double &val, int* pnResultPoints)
{
	switch (m_Params.nTypeData)
	{
	case 0:
	case Iso_Disp:
#ifdef SCAD21
		val =  GetDispByOff(reinterpret_cast<RESULT *>(m_Params.hAPI), ElementArray[nNumElement].Points[nNumVertex], m_Params.NPr, m_nOff);
#else
		val =  GetDispByOff(m_Params.Res, ElementArray[nNumElement].Points[nNumVertex], m_Params.NPr, m_nOff);
#endif
		return true;
	case Iso_Nap:
	case Iso_Nap_Flat:
		// ReSharper disable once CppEntityAssignedButNoRead
		double *res;
#ifdef SCAD21
		{
			static double Res[9 * 10];
			res = Res;
			static BYTE qUs;
			static BYTE qP;
			static UINT nNumElemReaded = (UINT)-1;
			UINT nNumElem = ElementArray[nNumElement].NumElem;
			if (nNumVertex == 0 || nNumElem != nNumElemReaded)
			{
				nNumElemReaded = nNumElem;
				ApiElemEffors *pEffors = nullptr;
				ApiGetEfforsXXX(m_Params.hAPI, nNumElem, &pEffors, 1);
				//ApiGetEffors(m_Params.hAPI, nNumElem, &pEffors, 1);
				// ReSharper disable once CppAssignedValueIsNeverUsed 
				qP = pEffors->QuantityPoint;
				if (pEffors->QuantityPoint < 4)
					return false;
				memcpy(Res, pEffors->Us, pEffors->QuantityDataUs * sizeof(double));

				qUs = pEffors->QuantityUs;
			}
			if (pnResultPoints)
				*pnResultPoints = qP;
			int nVertexs = ElementArray[nNumElement].NumVertexs();
			int nPos = nNumVertex >= nVertexs ? nNumVertex : ( nVertexs == 4 ? N_S(nNumVertex) : nNumVertex);
			val = res[qUs*(nPos) + m_Params.nTypeFactor];
		}
		return true;
	case Iso_Arm: break;
	case Iso_Lit: break;
	case Iso_Energy: break;
	default: break;
#else
		LPSTR  NusElem=nullptr;
		WORD nPoints=0;
		CViewElement &el = ElementArray[nNumElement]; 
		if (el.Type == EL_LINE)
			return 0;
		if (el.Type == EL_QUAD && nNumVertex<4)
			nNumVertex = N_S(nNumVertex);
		BYTE nSel = BYTE(m_Params.nTypeFactor);
		unsigned char i=0;
		if (!GetNumUs(i, nSel))
			return false;
		double *coord = nullptr;
		m_Params.Res->GetEfforsElem(m_Params.NPr, el.NumElem, i+8, nPoints, &NusElem, &coord, &res);
		if (!res || nPoints == 0)
			return false;
		if (pnResultPoints)
			*pnResultPoints = nPoints;
 		val = res[nNumVertex];
		return true;
#endif
	}
	return false;
}

void CIsoViewGeometry::LoadFactors()
{
#ifdef SCAD21
	SCHEMA *Prj = m_Params.hAPI;
	int off = m_Params.nTypeFactor;
	if (off == 6)
		off = 16;
	else
	{
		if (off <  6)
			off =  off;
		else
			off = 17;
	}
	m_nOff = off;
	switch (m_Params.nTypeData)
	{
	case Iso_Disp:
		{
			const static UnitsAPI Un[] = { { "mm", 1000 },{ "T", 1 } };
			ApiInitResult(m_Params.hAPI, Un, "c:\\swork");
		}
		break;
	case Iso_Nap:
	case Iso_Nap_Flat:
		{
			const static UnitsAPI Un[] = { { "m", 1 },{ "T", 1 } };
			ApiInitResult(m_Params.hAPI, Un, "c:\\swork");
		}
		break;
	}
#else
	SCHEMA *Prj = m_Params.Res->GetSchema();
	int off = m_Params.nTypeFactor;
	if (off == Prj->TypeSystem.QuantityStep)
		off = 16;
	else
	{
		if (off <  Prj->TypeSystem.QuantityStep)
			off =  Prj->TypeSystem.NumStep[off] - 1;
		else
			off = 17;
	}
	m_nOff = off;
#endif
	//UINT nVertexs = VertexArray.size();
	m_Factors.clear();
	m_mapVertexFactors.clear();
	if (m_nRealElements<0)
	{
		LoadFromSchema(Prj, 0, 0, false);
		m_nRealElements = ElementArray.size();
	}
	switch (m_Params.nTypeData)
	{
	case 0:
	case Iso_Disp:
	case Iso_Nap:
	case Iso_Nap_Flat:
	{
		for (int i = 0; i < m_nRealElements; i++)
		{
			CViewElement el = ElementArray[i];
			if (!el.DrawFlag || !el.FragmentFlag/* || el.Type == EL_LINE*/)
				continue;

			if (el.OrgType == EL_BAR && el.Type != EL_LINE)
			{
				if (m_Params.nTypeData != Iso_Disp)
					continue;
				for (int j = 0; j < el.NumVertexs(); j += 2)
				{
					NODE_NUM_TYPE nVertex = el.Points[j];
					nVertex = VertexArray[nVertex].nMainVertex;
					if (nVertex == -1)
						continue;
					if (m_Factors.size() > 1 && m_Factors[m_Factors.size() - 2].nVertex == nVertex)
						continue;
					SViewFactorVertex p = VertexArray[nVertex];
#ifdef SCAD21
					double val = GetDispByOff(reinterpret_cast<RESULT *>(Prj), nVertex, m_Params.NPr, m_nOff);
#else
					double val = GetDispByOff(m_Params.Res, nVertex, m_Params.NPr, m_nOff);
#endif
					p.fFactor = val;
					p.clr = GetColorrefForFactor(val);
					p.nElement = -1;
					p.nVertex = nVertex;
					p.nVertexIndex = 0;
					m_Factors.push_back(p);

				}
				continue;
			}

			int j = 0;
			S3dPoint ptMiddle(0, 0, 0);
			double val = 0;
			if (el.OrgType == EL_BAR)
			{
				continue;
			}
			for (; j < el.NumVertexs(); j++)
			{
				NODE_NUM_TYPE nVertex = el.Points[j];
				if (!GetFactorForElVertex(i, j, val, nullptr))
					continue;
				if (m_mapVertexFactors[nVertex] > 0 && m_Factors[m_mapVertexFactors[nVertex] - 1].fFactor == val)
					continue;
				if (m_mapVertexFactors[nVertex] == 0)
				{
					SViewFactorVertex pNew(VertexArray[nVertex]);
					m_Factors.push_back(pNew);
					m_mapVertexFactors[nVertex] = m_Factors.size();
				}
				SViewFactorVertex& p = m_Factors[m_mapVertexFactors[nVertex] - 1];
				ptMiddle.x += p.x;
				ptMiddle.y += p.y;
				ptMiddle.z += p.z;
				if (p.nVertexs == 0)
				{
					p.fFactor = val;
				}
				else
				{
					p.fFactor = (p.fFactor * p.nVertexs + val) / (p.nVertexs + 1);
				}
				++(p.nVertexs);
				p.clr = GetColorrefForFactor(p.fFactor);
				if (m_Params.bDrawEggs && (m_Params.nTypeData == Iso_Nap || p.clr == clIntervalOff))
					continue;
				p.nElement = i;
				p.nVertex = nVertex;
				p.nVertexIndex = j;
			}
			int nResultPoints = el.NumVertexs();
			if (m_Params.nTypeData == Iso_Nap && GetFactorForElVertex(i, el.NumVertexs(), val, &nResultPoints))
			{
				GetFactorForElVertex(i, nResultPoints - 1, val, nullptr);
				SViewFactorVertex p = SViewVertex(ptMiddle);
				p.x /= el.NumVertexs();
				p.y /= el.NumVertexs();
				p.z /= el.NumVertexs();

				p.fFactor = val;
				p.clr = GetColorrefForFactor(val);
				if (m_Params.bDrawEggs && (p.clr == clIntervalOff))
					continue;
				p.nElement = i;
				p.nVertex = -1;
				p.nVertexIndex = j;
				m_Factors.push_back(p);
			}

		}
	}
	case Iso_Arm: break;
	case Iso_Lit: break;
	case Iso_Energy: break;
	default: break;
	} // case	
}

//DEL void CIsoViewGeometry::Render(IFemRenderer *pRenderer, SViewOptions *pViewOptions, CDrawOptions *pDrawOptions)
//DEL {
//DEL 	pRenderer->Render(this, pViewOptions, pDrawOptions);
//DEL }
void CIsoViewGeometry::OnDrawScene(IFemRenderer *pRenderer, const SViewOptions * pViewOptions, const CDrawOptions * pDrawOptions, const SPerspectiveView & rViewPos)
{
	CDrawOptions dr = *pDrawOptions;
	if (m_Params.bDrawEggs)
	{
		dr.bNodes = FALSE;
		dr.Mode = M_LINES;
	}
	CGLDraw	GlDraw(this, &rViewPos, pViewOptions, &dr, pRenderer /*, 15*pViewOptions->LineWidth*/);
	GlDraw.Draw();
	if (!m_Params.pTypeInfo)
		return;
	if (m_Params.pTypeInfo->NumFactor)
		GlDraw.DrawFactorValues(m_Factors, m_Params.bDrawEggs);
	if (m_Params.bDrawEggs)
		GlDraw.DrawEggs(m_Factors);
	
}

COLORREF CIsoViewGeometry::GetColorrefForFactor(double val) const
{
	const DefMapInfo *DMI = m_Params.pDMI;
	
	for (short i=0; i<DMI->Scale_count; i++)
	{
		double dmiVal = DMI->einter[i];
		if (dmiVal<val)
			continue;
		COLORREF c = DMI->IsDrw[i] ? DMI->col[i] : clIntervalOff;
		return c;
	}
	return clIntervalOff;
}

#ifndef SCAD21
bool CIsoViewGeometry::GetNumUs(unsigned char & i, const BYTE & nSel)
{
	unsigned char nBit = 0;
	unsigned char mask = 1;
	for (i = 0; i<64 - 8 && nBit <= nSel; i++)
	{
		char val = m_Params.Res->SumNus[i / 8 + 1];
		if (val == 0)
		{
			i += 8;

			mask = 1;
		}
		if (val&mask)
		{
			if (nBit == nSel)
				break;
			nBit++;
		}
		mask <<= 1;
		if (mask == 0)
			mask = 1;
	}
	if (nBit != nSel)
		return false;
	return true;
}
#endif

COLORREF defDmiColors[]=
{
	RGB(0,0,128),
	RGB(0,0,255),
	RGB(0,255,255),
	RGB(128,255,255),
	RGB(255,255,128),
	RGB(255,255,64),
	RGB(255,255,0),
	RGB(128,255,128),
	RGB(128,255,64),
	RGB(128,255,0),
	RGB(0,255,64),
	RGB(0,255,0),
	RGB(0,255,0),
	RGB(0,128,0)
};

// Set the default scale for the given factor
void CIsoViewGeometry::SetDefMapInfo(DefMapInfo *pDMI, const SOglIsoParam *pParams)
{
	//if (!pParams)
	//	return;
	m_Params = *pParams;
	LoadFactors();
	size_t nVertexs =	m_Factors.size();
	double dMaxFactor = 0;
	double dMinFactor = 0;
	unsigned int i;
    for (i=0; i<nVertexs; i++)
	{
		double f = m_Factors[i].fFactor;
		if (i==0)
			dMaxFactor = dMinFactor = f;
		else
		{
			if (f>dMaxFactor)
				dMaxFactor = f;
			if (f<dMinFactor)
				dMinFactor = f;
		}
	}
	pDMI->Max = dMaxFactor;
	pDMI->Min = dMinFactor;
	pDMI->Step = (dMaxFactor-dMinFactor)/(pDMI->Scale_count);
	for (i=0; i<UINT(pDMI->Scale_count);i++)
	{
		pDMI->col[i]=defDmiColors[i];
		pDMI->binter[i]= dMinFactor+pDMI->Step*i;
		pDMI->einter[i]= dMinFactor+pDMI->Step*(i+1);
		pDMI->IsDrw[i] = TRUE;
	}
}

void CIsoViewGeometry::DrawOptionsChanged(const CDrawOptions * DrawOptions, bool bShowUsedNodes)
{
	CViewGeometry::DrawOptionsChanged(DrawOptions, bShowUsedNodes);
	ASSERT(VertexArray.size()>=m_OriginalVertexs.size());
    for (UINT i=0; i<m_OriginalVertexs.size(); i++)
	{
		SViewVertex& vO= m_OriginalVertexs[i];
		SViewVertex& v= VertexArray[i];
		vO.Flag = v.Flag;
		vO.FragmentFlag = v.FragmentFlag;
	}
	Get3DBox(nullptr, &m_FragmentBox, &m_OriginalVertexs);
	m_dblDefScaleMult = DrawOptions->dblDefScale;
	SetDefScale(m_dblDefScale);
}

CString  CIsoViewGeometry::Format(double val) const
{
	CString str;
	str.Format(_T("%6.2f"), val);
	return str;
}

void  CIsoViewGeometry::Get3DBox(const CRotator *Rot, S3DBox *Box, const CViewVertexArray * pVertexArray)
{
	CViewGeometry::Get3DBox(Rot, Box, &m_OriginalVertexs);
}

#endif









