// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
//#include <vcl.h>
//#pragma hdrstop
#include "StdAfx.h"
#include "ViewGeometry.h"
#include "ForumViewGeometry.h"
//#include "Qsort.h"
#define Mqsort	qsort
#include <math.h>
#include <stdio.h>
#include <map>

#undef GetObject
#define GetObject GetObjectA


#ifndef SCAD11
#ifdef SCAD21
#include "SCADAPIX.hxx"
#else
#include "schema.h"
#endif
#else
#include "schema.hpp"
#endif

#include <string.h>
#include "Timer.h"

#include "GLDraw.h"
#include <algorithm>

#ifndef MAXPATH
#define MAXPATH  _MAX_PATH
#endif
//---------------------------------------------------------------------------
inline NODE_NUM_TYPE NUM(NODE_NUM_TYPE x)
{
	return x - 1;
}

const NODE_NUM_TYPE		NUM_RECODE[] = { 0, 1, 3, 2 };


//#pragma package(smart_init)
// =================== Работа с кэшем ребер ==========================

#define CASHE_SORT // Если определена - упорядочивать узлы в ребре
void CNodeCashe::Construct(void)
{
	if (vecCashe.size()!=0)
		return;

	vecCashe.resize(m_pGeom->VertexArray.size());

	size_t i;
	for(i = 0; i < m_pGeom->VertexArray.size(); i++)
	{
		vecCashe[i].SecondNode = -1;
		vecCashe[i].Next = 0;
	}

	size_t nElements = m_pGeom->ElementArray.size();
	for(i = 0; i < nElements; i++)
	{
		CViewElement	El = m_pGeom->ElementArray[i];
		if(!El.FragmentFlag || !El.DrawFlag || !El.bContoured)
			continue;

		int				NumPoints = El.NumVertexs();
		NODE_NUM_TYPE	pn1 = El.Points[0], pn0 = pn1;
		for(int j = 1; j < NumPoints; j++)
		{
			NODE_NUM_TYPE	pn2 = El.Points[j];
			AddCacheElement(pn1, pn2);
			pn1 = pn2;
		}

		AddCacheElement(pn0, pn1);
	}

};

void CNodeCashe::SetBarsDrawed(void)
{
	for(UINT i = 0; i < m_pGeom->ElementArray.size(); i++)
	{
		CViewElement	El = m_pGeom->ElementArray[i];
		if(!El.FragmentFlag || !El.DrawFlag || El.Type != EL_LINE || El.IsContour())
			continue;

		NODE_NUM_TYPE	pn0 = El.Points[0], pn1 = El.Points[1];
		WasDrawed(pn0, pn1);
	}
};

void CNodeCashe::Destroy(void)
{
	vecCashe.resize(0);
	LineStrips.resize(0);
};

void CNodeCashe::AddCacheElement(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2)
{
#ifdef CASHE_SORT
	if(n1 > n2)
	{
		NODE_NUM_TYPE	tmp = n1;
		n1 = n2;
		n2 = tmp;
	}

	AddCacheElement1(n1, n2);
#else
	AddCacheElement1(n1, n2);
	AddCacheElement1(n2, n1);
#endif
};

void CNodeCashe::AddCacheElement1(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2)
{
	SViewCasheNode	*pnc = &vecCashe[n1];
	NODE_NUM_TYPE pncIndex = n1;
	if(pnc->SecondNode != -1)
	{
		while(pnc->Next != 0)
		{
			if(pnc->SecondNode == n2)
				return;
			pncIndex = pnc->Next;
			pnc = &vecCashe[pnc->Next];
		}

		if(pnc->SecondNode == n2)
			return;
		vecCashe.push_back(SViewCasheNode());
		pnc = &vecCashe[pncIndex];
		pnc->Next = vecCashe.size()-1;
		pnc = &vecCashe[pnc->Next];
	}

	pnc->SecondNode = n2;
	pnc->Next = 0;
#ifdef CASHE_VECTORS

	S3dPoint p1 = S3dPoint(m_pGeom->VertexArray[n1]);
	S3dPoint p2 = S3dPoint(m_pGeom->VertexArray[n2]);
	CVectorType v (p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	v.Normalize();
	pnc->v = v;
#endif
};

void CNodeCashe::Clear(void)
{
	if (!vecCashe.size())
		return;
	SViewCasheNode	*pnc;
	for(UINT i = 0; i < vecCashe.size(); i++)
	{
		pnc = &vecCashe[i];
		if(pnc->SecondNode == -1)
			continue;
		while(pnc)
		{
			pnc->Drawed = false;
			pnc = pnc->Next ? &vecCashe[pnc->Next] : nullptr;
		}
	}
}

bool CNodeCashe::WasDrawed(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2)
{
	if (vecCashe.size()==0)
		return false;
#ifdef CASHE_SORT
	if(n1 > n2)
	{
		std::swap(n1,n2);
	}
	return WasDrawed1(n1, n2);
#else
	WasDrawed1(n1, n2);
	return WasDrawed1(n2, n1);
#endif
}

bool CNodeCashe::WasDrawed1(NODE_NUM_TYPE n1, NODE_NUM_TYPE n2)
{
	if (!vecCashe.size() || n1>=ptrdiff_t(vecCashe.size()) || n2>=ptrdiff_t(vecCashe.size()))
		return false;
	SViewCasheNode	*pnc = &vecCashe[n1];
	if(pnc->SecondNode != -1)
	{
		while(pnc != nullptr&& pnc->SecondNode>=0)
		{
			if(pnc->SecondNode == n2)
			{
				if(pnc->Drawed)
					return true;
				pnc->Drawed = true;
				return false;
			}

			pnc = pnc->Next == 0 ? nullptr : &vecCashe[pnc->Next];
		}
	}

	return false;
}

//====================Создание границ элементов =============================

void CNodeCashe::SetVertex(NODE_NUM_TYPE N)
{
/*
	if(Strip >= StripEnd)
		MessageBox(nullptr, "Ошибка", "Переполнение буффера линий", MB_OK);
	Strip->Vertex = N;
	Strip++;
*/
	SLineStripRec rec;
	rec.Vertex = N;
	LineStrips.push_back(rec);
}

#define Eps 1e-3
/*
inline FLOAT_TYPE DotProduct(S3dPoint v1, S3dPoint v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
*/
void  CNodeCashe::SetupLineStrips()
{
	Clear();
	SetBarsDrawed();
	LineStrips.resize(0);
	//SViewVertex		*Vertexs = m_pGeom->VertexArray.GetVector();
	//SLineStripRec	*Strip = nullptr;//LineStrips;
	for(UINT i = 0; i < m_pGeom->VertexArray.size(); i++)
	{
		SViewCasheNode	*pnc = &vecCashe[i];
		if(pnc->SecondNode != -1)
		{
			do
			{
				if(pnc->Drawed)
				{
					pnc = pnc->Next ? &vecCashe[pnc->Next] : nullptr;
					continue;
				}
				WasDrawed(i, pnc->SecondNode);

				//glBegin(GL_LINE_STRIP);
				SetVertex(i);

				NODE_NUM_TYPE			N = pnc->SecondNode;
#ifdef CASHE_VECTORS
				CVectorType	&v = pnc->v;
#endif
				Restart : SViewCasheNode * pnc1 = &vecCashe[N];
#ifdef CASHE_VECTORS
				if(pnc1->SecondNode != -1)
				{
					SViewCasheNode	*pnc2 = pnc1;
					FLOAT_TYPE			dp=0;
					for(; pnc1; pnc1 =  pnc1->Next ? &vecCashe[pnc1->Next] : nullptr)
					{
						if(pnc1->Drawed)
							continue;
						dp = v.DotProduct(pnc1->v);

						//                       S3dPoint v1=pnc1->v;
						if((fabs(dp-1) < 1e-6) && m_bCheckStraitLines)
						{
							WasDrawed(N, pnc1->SecondNode);
							N = pnc1->SecondNode;
							goto Restart;
						}

						pnc2 = pnc1;
					}

					pnc1 = pnc2;
					if(!pnc1->Drawed && fabs(dp) > Eps)
					{
						v = pnc1->v;
						SetVertex(N);
						WasDrawed(N, pnc1->SecondNode);
						N = pnc1->SecondNode;
						goto Restart;
					}
				}

				SetVertex(N);
#else
				SetVertex(Vertexs, N);
				if(pnc1->SecondNode != -1)
				{
					do
					{
						if(pnc1->Drawed)
							continue;
						pnc1->Drawed = true;
						N = pnc1->SecondNode;
						goto Restart;
					} while(pnc1 = pnc1->Next);
				}
#endif
				SetVertex(-1);	// glEnd();
				pnc = pnc->Next ? &vecCashe[pnc->Next] : nullptr;
			} while(pnc != nullptr);
		}
	}

	SetVertex(-1);
}

//==========================================================================
const FLOAT_TYPE	ComparePrecision = 1e-3f;

static inline int Compare(FLOAT_TYPE x1, FLOAT_TYPE x2)
{
	if(x1 > x2 + ComparePrecision)
		return 1;
	if(x1 < x2 - ComparePrecision)
		return -1;
	return 0;
}

static int CompareInt(const void *v1, const void *v2)
{
	if(* reinterpret_cast<const int *> (v1) > * reinterpret_cast<const int *> (v2))
		return 1;
	if(* reinterpret_cast<const int *> (v1) < * reinterpret_cast<const int *> (v2))
		return -1;
	return 0;
}

static int CompareVert(SSortVertex *p1, SSortVertex *p2)
{
	int c = Compare(p1->x, p2->x);
	if(c != 0)
		return c;
	c = Compare(p1->y, p2->y);
	if(c != 0)
		return c;
	c= Compare(p1->z, p2->z);
	if (c!=0)
		return c;
	return CompareInt(&(p1->N),&(p2->N));
}

static int CompareVert1(SSortVertex *p1, SSortVertex *p2)
{
	int c = Compare(p1->x, p2->x);
	if(c != 0)
		return c;
	c = Compare(p1->y, p2->y);
	if(c != 0)
		return c;
	return Compare(p1->z, p2->z);
}


static int CompareElem(const void *v1, const void *v2)
{
	auto e1 = reinterpret_cast<const SElement *>(v1);
	auto e2 = reinterpret_cast<const SElement *>(v2);
	for(int j = 0; j < 4; j++)
	{
		int c = CompareInt(e1->Points + j, e2->Points + j);
		if(c != 0)
			return c;
	}

	return 0;
}

//extern bool bDeleteInnerPlates;
typedef int (*CmpVertFunc) (const void *, const void *);

void __fastcall CViewGeometry::DeleteEqualNodes()
{
	size_t nVertexs = VertexArray.size();
	size_t nElements = ElementArray.size();
	std::vector<SSortVertex> VertexIndexes;
	VertexIndexes.resize(nVertexs);
	for(size_t i = 0; i < nVertexs; i++)
	{
		VertexIndexes[i].x = VertexArray[i].x;
		VertexIndexes[i].y = VertexArray[i].y;
		VertexIndexes[i].z = VertexArray[i].z;
		VertexIndexes[i].N = i;
	}

	std::sort(VertexIndexes.begin(), VertexIndexes.end());
	//qsort(&VertexIndexes[0], nVertexs, sizeof(SSortVertex), CmpVertFunc(CompareVert));
	
	std::vector<NODE_NUM_TYPE> NodeSubst(nVertexs);
	std::vector<SSortVertex>::iterator v1, v2;

	//int i;
	for(v1 = VertexIndexes.begin(), v2 = v1 + 1; v1 < VertexIndexes.end();)
	{
		while (v2 < VertexIndexes.end() && CompareVert1(&*v1, &*v2) == 0)
		{
			NodeSubst[v2->N] = v1->N;
			++v2;
		}

		NodeSubst[v1->N] = v1->N;
		v1 = v2;
		if (v2 < VertexIndexes.end())
			++v2;
	}

	for(size_t i = 0; i < nElements; i++)
	{
		CViewElement	*El = ElementArray.GetVector()+i;
		for(int j = 0; j < int(El->Type) + 2; j++)
			El->Points[j] = NodeSubst[El->Points[j]];
	}
}

/*virtual*/ TOrgElemType CViewGeometry::GetElemOrgType(WORD wTypeElem)
{
#ifdef SCAD21
	switch (wTypeElem)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 10:
		return EL_BAR;
//  Тип эл-та  Кол-во узлов
	case 11: // 4
	case 12: // 3
	case 13: // 4
	case 14: // 3
	case 15: // 3..6
	case 19: // 4
	case 20: // 4..8
	case 21: // 4
	case 22: // 3
	case 23: // 4
	case 24: // 3
	case 25: // 3..6
	case 27: // 4..8
	case 30: // 4..8
	case 41: // 4
	case 42: // 3
	case 44: // 4
	case 45: // 3..6
	case 50: // 4..8
		return EL_PLATE;
	case 32:
	case 34:
	case 36:
		return EL_SOLID;
	default:
		break;
	}

	return TOrgElemType(wTypeElem);
#else
	return TOrgElemType(ElemType(wTypeElem));
#endif
}


bool CViewGeometry::LoadFromFile(LPCTSTR PathName, BYTE TypeProfile, BYTE TypePlate,  bool bOptimize, SCHEMA ** ppSchem)
{
	TCHAR	NameIn[MAXPATH];
	TCHAR	Path[MAXPATH];

	//strcpy(Path, PathName);
	//PathRemoveFileSpec(Path);
	::GetTempPath(MAXPATH, Path);
#ifdef SCAD21
	SCHEMA*	Schem = ppSchem ? *ppSchem : nullptr ;
	if (Schem== nullptr)
		ApiCreate(&Schem);
//	if (ppSchem)
//		_tcscpy_s(Path, _T("C:\\swork"));
//#ifdef UNICODE
//	char path[MAX_PATH];
//	WideCharToMultiByte(CP_ACP, 0, Path, -1, path, sizeof(path), nullptr, nullptr);
//#else
//	Schem->Init(nullptr, nullptr, Path);
//#endif
	

	_tcscpy_s(NameIn, PathName);
#ifdef UNICODE
	char NameInA[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, NameIn, -1, NameInA, sizeof(NameInA), nullptr, nullptr);
	if (ApiReadProject(Schem, NameInA) != APICode_OK)
#else
	if (ApiReadProject(Schem, NameIn) != APICode_OK)
#endif
	{
		ApiRelease(&Schem);
		return false;
	}
	if (ppSchem)
		return true;
	bool bResult = LoadFromSchema(Schem, TypeProfile, TypePlate, bOptimize);
	if (!ppSchem)
		ApiRelease(&Schem);
	return bResult;

#else
	SCHEMA*	Schem = ppSchem ? *ppSchem : nullptr ;
	if (Schem==nullptr)
		Schem = new SCHEMA;
	//ZeroMemory(Schem, sizeof(SCHEMA));
	if (ppSchem)
		_tcscpy_s(Path, _T("C:\\swork"));
#ifdef SCAD11
#ifdef UNICODE
	char path[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, Path, -1, path, sizeof(path), nullptr, nullptr);
	Schem->Init(path);
#else
	Schem->Init(Path);
#endif
#else
	Schem->Init(nullptr, nullptr, Path);
#endif
	

	_tcscpy_s(NameIn, PathName);
	//int i = strlen(NameIn);
#ifdef SCAD11
#ifdef UNICODE
	char NameInA[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, NameIn, -1, NameInA, sizeof(NameInA), nullptr, nullptr);
	if (Schem->Read(NameInA))
#else
	if (Schem->Read(NameIn))
#endif

#else
	if(Schem->Read(NameIn, 10))
#endif
	{
		delete Schem;
		return false;
	}
	if (ppSchem)
		return true;
	bool bResult = LoadFromSchema(Schem, TypeProfile, TypePlate, bOptimize);
	if (!ppSchem)
	{
		Schem->Destroy();
		delete Schem;
	}
	return bResult;
#endif
}

#ifdef SCAD21
TElemType CElemInfApiExt::GetType() const
{
	switch (TypeElem)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 10:
		return EL_LINE;
		//  Тип эл-та  Кол-во узлов
	case 12: // 3
	case 14: // 3
	case 15: // 3..6
	case 22: // 3
	case 24: // 3
	case 25: // 3..6
	case 42: // 3
	case 45: // 3..6
		return EL_TRIANGLE;
	case 11: // 4
	case 13: // 4
	case 19: // 4
	case 20: // 4..8
	case 21: // 4
	case 23: // 4
	case 27: // 4..8
	case 30: // 4..8
	case 41: // 4
	case 44: // 4
	case 50: // 4..8
		return EL_QUAD;
	default:
		DebugBreak();
		return EL_LINE;
	}
}

bool CElemInfApiExt::getContour(std::vector<S3dPoint>& contour, bool & bClosed)
{
	if (TypeRigid == 0)
		return false;

	char Text[1024];
	UINT nQnt = 0;
	const UINT* ListElem;
	ApiGetRigid(m_lpApi, TypeRigid, Text, sizeof(Text), &nQnt, &ListElem);
	double f0 = 0;
	double f1 = 0;
	double f2 = 0;
	double f3 = 0;
	double f4 = 0;
	double f5 = 0;
	double f6 = 0;

	CStringA strText(Text);
	strText.Replace(".", ",");
	char c = 0;
	int nKind;
	int nPos = 0;
	LPCSTR szRest = (LPCSTR)strText;
	sscanf_s(szRest, "%c", &c, 1);
	szRest++;
	if (c == 'S')
	{
		sscanf_s(szRest, "%d %n", &nKind, &nPos);
		szRest += nPos;
		if (nKind!=7)
			sscanf_s(szRest, "%lg %lg %lg %n", &f0, &f1, &f2, &nPos);
		else
			sscanf_s(szRest, "%lg %lg %n", &f0, &f1, &nPos);
		szRest += nPos;

		switch (nKind)
		{
		case 1:
		case 2:
		case 4:
		case 5:
			sscanf_s(szRest, "%lg %lg %n", &f3, &f4, &nPos);
			szRest += nPos;
			break;
		case 3:
		case 8:
			sscanf_s(szRest, "%lg %lg %lg %lg %n", &f3, &f4, &f5, &f6, &nPos);
			szRest += nPos;
			break;
		}

		switch (nKind)
		{
		case 0:
			contour.push_back(S3dPoint(0, FLOAT_TYPE(-f1/2), FLOAT_TYPE(-f2 / 2)));
			contour.push_back(S3dPoint(0, FLOAT_TYPE(f1 / 2), FLOAT_TYPE(-f2 / 2)));
			contour.push_back(S3dPoint(0, FLOAT_TYPE(f1 / 2), FLOAT_TYPE(f2 / 2)));
			contour.push_back(S3dPoint(0, FLOAT_TYPE(-f1 / 2), FLOAT_TYPE(f2 / 2)));
			bClosed = true;
			return true;
		case 1:
			break;
		}
	}
	return false;
}

void  CElemInfApiExt::UpdateThickness()
{
	if (TypeRigid > 0)
	{
		char Text[1024];
		UINT nQnt = 0;
		const UINT* ListElem;
		ApiGetRigid(m_lpApi, TypeRigid, Text, sizeof(Text), &nQnt, &ListElem);
		double f1 = 0, f2 = 0, f3 = 0;
		CStringA strText(Text);
		strText.Replace(".", ",");
		sscanf_s((LPCSTR)strText, "%lg %lg %lg", &f1, &f2, &f3);
		m_fThickness = (FLOAT_TYPE)f3;
	}
}

bool CViewGeometry::ProcessSpecialTypes(CElemInfApiExt &e)
{
	if (e.TypeElem == 36)
	{
		static const int arrCoord[] = { 0,2,3,1, 0,4,5,1, 1,3,7,5, 3,2,6,7, 2,6,4,0, 7,6,4,5 };
		const int *pArr = arrCoord;
		for (UINT i1 = 0; i1<6; i1++)
		{
			CViewElement el(RGB(192, 192, 192));
			el.OrgType = GetElemOrgType(e.TypeElem);
			el.NumElem = i1 + 1;
			el.Type = EL_QUAD;
			for (UINT j = 0; j<4; j++)
				el.Points[j] = NUM(e.Node[*pArr++]);
			ElementArray.push_back(el);
		}
		return true;
	}
	else if (e.TypeElem == 32)
	{
		static const int arrCoord[] = { 0,2,1, 0,1,3, 1,2,3, 2,0,3 };
		const int *pArr = arrCoord;
		for (UINT i1 = 0; i1<4; i1++)
		{
			CViewElement el(RGB(192, 192, 192));
			el.OrgType = GetElemOrgType(e.TypeElem);
			el.NumElem = i1 + 1;
			el.Type = EL_TRIANGLE;
			for (UINT j = 0; j<3; j++)
				el.Points[j] = NUM(e.Node[*pArr++]);
			ElementArray.push_back(el);
		}
		return true;
	}
	else if (e.TypeElem == 34)
	{
		static const int arrCoord[] = { 0,2,1, 3,4,5, 0,3,4,1, 1,2,5,4, 0,3,5,2 };
		const int *pArr = arrCoord;
		for (UINT i1 = 0; i1<2; i1++)
		{
			CViewElement el(RGB(192, 192, 192));
			el.OrgType = GetElemOrgType(e.TypeElem);
			el.NumElem = i1 + 1;
			el.Type = EL_TRIANGLE;
			for (UINT j = 0; j<3; j++)
				el.Points[j] = NUM(e.Node[*pArr++]);
			ElementArray.push_back(el);
		}
		for (UINT i1 = 0; i1<3; i1++)
		{
			CViewElement el(RGB(192, 192, 192));
			el.OrgType = GetElemOrgType(e.TypeElem);
			el.NumElem = i1 + 1;
			el.Type = EL_QUAD;
			for (UINT j = 0; j<4; j++)
				el.Points[j] = NUM(e.Node[*pArr++]);
			ElementArray.push_back(el);
		}
		return true;
	}
	return false;
}

void CViewGeometry::AddOprContours(const UINT &nQuantNodes, CElemInfApiExt &e, const UINT &i, const BYTE &TypePlate, const UINT * pNodes, CVectorType &Norm)
{
	for (UINT k = 0; k<nQuantNodes; k++)
	{
		CViewElement el(RGB(192, 192, 192));
		el.OrgType = GetElemOrgType(e.TypeElem);
		el.Type = EL_LINE;
		el.NumElem = i + 1;
		if (TypePlate && e.m_fThickness > 1e-5)
		{
			size_t nVertexIdx = VertexArray.size();
			const S3dPoint pt1 = VertexArray[NUM(pNodes[k])];
			const S3dPoint pt1in = pt1 + Norm*(e.m_fThickness / 2);
			const S3dPoint pt1out = pt1 + Norm*(-e.m_fThickness / 2);
			VertexArray.push_back(pt1in);
			VertexArray.push_back(pt1out);
			const S3dPoint pt2 = VertexArray[NUM(pNodes[(k + 1) % nQuantNodes])];
			const S3dPoint pt2in = pt2 + Norm*(e.m_fThickness / 2);
			const S3dPoint pt2out = pt2 + Norm*(-e.m_fThickness / 2);
			VertexArray.push_back(pt2in);
			VertexArray.push_back(pt2out);
			el.Points[0] = nVertexIdx;
			el.Points[1] = nVertexIdx + 1;
			ElementArray.push_back(el);
			el.Points[0] = nVertexIdx;
			el.Points[1] = nVertexIdx + 2;
			ElementArray.push_back(el);
			el.Points[0] = nVertexIdx + 1;
			el.Points[1] = nVertexIdx + 3;
			ElementArray.push_back(el);

		}
		else
		{
			el.Points[0] = NUM(pNodes[k]);
			el.Points[1] = NUM(pNodes[(k + 1) % nQuantNodes]);
			ElementArray.push_back(el);
		}
	}
}
#endif


void __fastcall CViewElement::SetNormal(SViewVertex *Vertexs)
{
/*
	if(NumVertexs() == 2)
	{
		Norm = CVectorType(1,1,1);
		return;
	}

	S3dPoint	p[3];
	for(int i = 0; i < 3; i++)
		p[i] = Vertexs[Points[i]];

	CVectorType	p1v(p[1].x - p[0].x, p[1].y - p[0].y, p[1].z - p[0].z );
	CVectorType p2v(p[2].x - p[1].x, p[2].y - p[1].y, p[2].z - p[1].z );
	Norm.SetCrossProduct(p1v, p2v);
*/
	if (IsContour())
		return;
	if(NumVertexs() == 2)
	{
		S3dPoint	p[2];
		for(int i = 0; i < 2; i++)
			p[i] = S3dPoint(Vertexs[Points[i]]);
		OrgNorm = Norm = CVectorType(p[1].x - p[0].x, p[1].y - p[0].y, p[1].z - p[0].z);
		return;
	}

	S3dPoint	p[3];
	for(int i = 0; i < 3; i++)
		p[i] = S3dPoint(Vertexs[Points[i]]);

    if (IsBarLike())
    {
		OrgNorm = CVectorType(p[2].x - p[1].x, p[2].y - p[1].y, p[2].z - p[1].z);

	    CVectorType	p1v(p[1].x - p[0].x, p[1].y - p[0].y, p[1].z - p[0].z );
	    CVectorType p2v(p[2].x - p[1].x, p[2].y - p[1].y, p[2].z - p[1].z );
	    Norm.SetCrossProduct(p1v, p2v);
		Norm.Normalize();
		return;
    }

	CVectorType	p1v(p[1].x - p[0].x, p[1].y - p[0].y, p[1].z - p[0].z);
	CVectorType p2v(p[2].x - p[1].x, p[2].y - p[1].y, p[2].z - p[1].z);
	Norm.SetCrossProduct(p1v, p2v);
	Norm.Normalize();
}

void __fastcall CViewGeometry::SetupNormals(void)
{
/*
	int nElements = ElementArray.size();
	for(int i = 0; i < nElements; i++)
		ElementArray[i].SetNormal(VertexArray.GetVector());
*/
	size_t nElements = ElementArray.size();;
	size_t nMaxRealElementNumber = 0;
	size_t i;
    for (i=0; i<nElements; i++)
        if (size_t(ElementArray[i].NumElem) > nMaxRealElementNumber)
            nMaxRealElementNumber = ElementArray[i].NumElem;

    int *anFirstElements = new int[nMaxRealElementNumber];
    for (i=0;i < nMaxRealElementNumber; i++)
        anFirstElements[i] = -1;
 	for(i = 0; i < nElements; i++)
    {
        CViewElement& CurElement =ElementArray[i];
        int nOrgNumElem = CurElement.NumElem-1;
		if (CurElement.IsContour())
			continue;
        if (anFirstElements[nOrgNumElem]<0)
        {
            // Need to calculate the normal
    		CurElement.SetNormal(VertexArray.GetVector());
            anFirstElements[nOrgNumElem] = i;
            if (!CurElement.IsBarLike())
                CurElement.OrgNorm = CurElement.Norm;
        }
        else
		{
    		CurElement.SetNormal(VertexArray.GetVector());
            // Just copy the calculated normal
            if (!CurElement.IsBarLike())
                CurElement.OrgNorm = ElementArray[anFirstElements[nOrgNumElem]].Norm;
		}
    } // for
	for (i = 0; i < nElements; i++)
	{
        CViewElement& CurElement =ElementArray[i];
        int nOrgNumElem = CurElement.NumElem-1;
		//ASSERT(anFirstElements[nOrgNumElem]>=0);
		if (anFirstElements[nOrgNumElem] >=0 && !CurElement.IsBarLike())
         CurElement.OrgNorm = ElementArray[anFirstElements[nOrgNumElem]].Norm;
	}

	delete [] anFirstElements;
}

inline CViewElement::CViewElement(const SElement &OldElem)
{
	Color = OldElem.Color;
	Type = OldElem.Type;
	OrgType = OldElem.OrgType;
	if(Type != EL_QUAD)
		for(int j = 0; j < NumVertexs(); j++)
			Points[j] = NUM(OldElem.Points[j]);
	else
	{
		for(int j = 0; j < NumVertexs(); j++)
			Points[j] = NUM(OldElem.Points[N_S(j)]);
	}

	FragmentFlag = DrawFlag = true;
}

CViewElement::CViewElement(): FragmentFlag(true), DrawFlag(true), bContoured(true), bContourOnly(false), m_nExtraPoints(-1)
{}

CViewElement::CViewElement(TColor color): m_nExtraPoints(-1)
{
	Color = color;
	FragmentFlag = DrawFlag = true;
	bContoured = true;
	bContourOnly = false;
}

void CViewElementArray::BuildArrays( CViewVertexArray& VertexArray, CViewElement * pElements, size_t nElements)
{
	m_triangles.resize(0);
	m_quads.resize(0);
	bool bMapExist = m_mapVertexs.size() > 0;
	UINT32 nMaxIndex = VertexArray.size();
	m_colors.resize(nMaxIndex);
	m_normals.resize(nMaxIndex);
	std::map<UINT32, bool> mapVertexUsed;
	for (size_t i=0; i<nElements; i++)
	{
		CViewElement &el = pElements[i];
		if (!el.DrawFlag || !el.FragmentFlag || el.bContourOnly)
			continue;
		for (int j = 0; j < el.NumVertexs(); j++)
		{
			UINT32 nPoint = el.Points[j];
			if (!mapVertexUsed[nPoint])
			{
				mapVertexUsed[nPoint] = true;
				m_colors[nPoint] = el.Color | (128 << 24);
				m_normals[nPoint] = el.Norm;
			}
			else
			{
				VertexArray.push_back(VertexArray[nPoint]);
				if (!bMapExist)
					m_mapVertexs.push_back(std::make_pair(nPoint, VertexArray.size() - 1));
				nPoint = VertexArray.size() - 1;
				el.Points[j] = nPoint;
				m_colors.push_back(el.Color | (128 << 24));
				m_normals.push_back(el.Norm);
			}

			if (el.NumVertexs() == 3)
				m_triangles.push_back(nPoint);
			else if (el.NumVertexs()==4)
				m_quads.push_back(nPoint);
		}
	}
	m_bRebuildArrays = true;
}

void __fastcall CViewGeometry::DeleteEqualElements()
{
	//CViewElementArray ElementsCopy(ElementArray);
	size_t			nElements = ElementArray.size();
	std::vector<SSortElement>	ElemIndexes(nElements);
	SSortElement	*Ei = &ElemIndexes[0];
	CViewElement	*El = ElementArray.GetVector();
	size_t i=0;
	for(i = 0; i < nElements; i++)
	{
		int nPoints = int(El->Type) + 2;
		for(int j = 0; j < 4; j++)
			Ei->Points[j] = (j < nPoints) ? El->Points[j] : -1;
		qsort(Ei->Points, 4, sizeof(int), CompareInt);
		Ei->N = i;
		Ei->OrgType = El->OrgType;
		Ei->Type = El->Type;
		Ei->NumElem = El->NumElem;
		El++;
		Ei++;
	}

	qsort(&ElemIndexes[0], nElements, sizeof(SSortElement), CompareElem);

	std::vector<SSortElement>::iterator	v1, v2;
	std::vector<bool> bvecKeepElements(ElementArray.size(), false);
	for(v1 = ElemIndexes.begin(), v2 = v1 + 1; v1 < ElemIndexes.end();)
	{
		bool	bInner = false;
		while
		(
			v2 < ElemIndexes.end() &&
			CompareElem(&*v1, &*v2) == 0 &&
			v1->OrgType == v2->OrgType &&
			(v1->Type == EL_PLATE || m_pFlatGeometry == nullptr)
		)
		{
			bInner = true;
			++v2;
		}
		if (!m_pFlatGeometry)
			for (std::vector<SSortElement>::iterator v=v1; v<v2 && bInner; ++v)
			{
				if (ElementArray[v->N].IsContour())
					continue;
				m_DuplicatedElements.insert(v->NumElem);
				bvecKeepElements[v->N] = true;
			}

		else
			for (std::vector<SSortElement>::iterator v=v1; v<v2 && bInner; ++v)
			{
				if (m_DuplicatedElements.count(v->NumElem)!=0)
					bvecKeepElements[v->N] = true;
			};
		if(m_bDeleteInnerPlates == false || !bInner || ElementArray[v1->N].IsContour())
		{
			//ElementArray[i] = ElementsCopy[v1->N];
			//ElementArray[i++].FragmentFlag = true;
			bvecKeepElements[v1->N] = true;
		}

		v1 = v2;
		if (v2 < ElemIndexes.end())
			++v2;

	}

	//ementArray.resize(i);
	for (i=0; i<ElementArray.size(); i++)
		ElementArray[i].DrawFlag = bvecKeepElements[i];
}

#if 1
void _TRACE(LPCTSTR szFormat, LPCTSTR szBuffer)
{
	TCHAR buf[512];
	_stprintf_s(buf, szFormat, szBuffer);
	OutputDebugString(buf);
}
#else
#define _TRACE TRACE
#endif

void CViewGeometry::SetupAndOptimize(bool bReduceGeometry)
{
	if(bReduceGeometry)
	{
		CTimer Timer;
		Timer.Start();
		DeleteEqualNodes();

		_TRACE(_T("DeleteEqualNodes() = %s\n"), Timer.StopStr());//Application->MessageBox(S,"Удаление ненужных узлов",MB_OK);
	}

	//ElementArray->Elements = Elements;
	if(m_bDeleteInnerPlates)
	{
		CTimer Timer;
		Timer.Start();
		DeleteEqualElements();

		_TRACE(_T("DeleteEqualElements() = %s\n"), Timer.StopStr());//Application->MessageBox(S,"Удаление ненужных элементов",MB_OK);
	}
	CTimer Timer;
	Timer.Start();
	CTimer Timer1;
	Timer1.Start();
	SetupNormals();
    _TRACE(_T("\tSetupNormals() = %s\n"), Timer1.StopStr());//	AfxMessageBox(S);
	DeleteNondrawableElements();
	if (bReduceGeometry)
	{
		Retriangulate();
		Timer1.Start();
		GetNodeCashe()->Construct();
		_TRACE(_T("\tConstructNodeCashe() = %s\n"), Timer1.StopStr());
		//AfxMessageBox(S);
//		int nLineStripMaxSize = ElementArray.size() * 12 + 1;
//		LineStrips = new SLineStripRec[nLineStripMaxSize];
//		StripEnd = LineStrips + nLineStripMaxSize;
		Timer1.Start();
		GetNodeCashe()->SetupLineStrips();
		_TRACE(_T("\tSetupLineStrips() = %s\n"), Timer1.StopStr());//	AfxMessageBox(S);
	}
    _TRACE(_T("OtherGeometrySetup = %s\n"), Timer.StopStr());//	AfxMessageBox(S);
}

CViewGeometry::~CViewGeometry(void)
{
	delete m_pFlatGeometry;
	m_pFlatGeometry = nullptr;
	delete m_pNodeCashe;
	m_pNodeCashe = nullptr; 
	delete m_pNodeCashe;
}

void CViewGeometry::RecreateCashe(void) const
{
	if (!m_bOptimize)
		return;
	m_pNodeCashe->Recreate();
}

// Учет фильтров отрисовки элементов по ориентации
bool ElementToBeDrawn(const CVectorType &Norm, const CDrawOptions * DrOpt)
{
	if(fabs(Norm.v[2]) < Eps)
		return DrOpt->bElVertical;
	else if(fabs(Norm.v[0]) < Eps && fabs(Norm.v[1]) < Eps)
		return DrOpt->bElHorizontal;
	else
		return DrOpt->bElOther;
}

bool BarToBeDrawn(CViewElement &El, const CDrawOptions * DrOpt)
{
	if(fabs(El.OrgNorm.v[2]) < Eps)
		return DrOpt->bBarHorizontal;
	else if(fabs(El.OrgNorm.v[0]) < Eps && fabs(El.OrgNorm.v[1]) < Eps)
		return DrOpt->bBarVertical;
	return DrOpt->bBarOther;
}
void CViewGeometry::DrawOptionsChanged(const CDrawOptions * DrawOptions, bool bShowUsedNodes)
{
	m_bShowUsedNodes = bShowUsedNodes;
	if (DrawOptions)
	{
		size_t nElements = ElementArray.size();
		for(size_t i = 0; i < nElements; i++)
		{
			CViewElement	*El = &ElementArray[i];
			TOrgElemType	OrgType = El->OrgType;
			switch(OrgType) {
			case EL_BAR:
				El->DrawFlag = DrawOptions->bBars;
				break;
			case EL_PLATE:
			case EL_ISO:
				El->DrawFlag = DrawOptions->bElements;
				break;
			case EL_SOLID:
				El->DrawFlag = DrawOptions->bSolids;
				break;
			case EL_COLUMN:
				El->DrawFlag = DrawOptions->bColumns && DrawOptions->bBars; 
				break;
			case EL_BEAM:
				El->DrawFlag = DrawOptions->bBeams && DrawOptions->bBars;
				break;
			case EL_WALL:
				El->DrawFlag = DrawOptions->bWalls && DrawOptions->bElements;
				break;
			case EL_ROOF:
				El->DrawFlag = DrawOptions->bRoofs && DrawOptions->bElements;
				break;
			case EL_SLAB:
				El->DrawFlag = DrawOptions->bSlabs && DrawOptions->bElements;
				break;
			default:
				El->DrawFlag = true;
			}
			El->DrawFlag = El->DrawFlag &&
				(
					((El->OrgType == EL_PLATE ||El->OrgType == EL_WALL || El->OrgType == EL_SLAB || El->OrgType == EL_ROOF || El->OrgType == EL_ISO) && ElementToBeDrawn(El->OrgNorm, DrawOptions)) ||
					((El->OrgType == EL_BAR || El->OrgType == EL_COLUMN || El->OrgType == EL_BEAM) && BarToBeDrawn(*El, DrawOptions)) ||
					(El->OrgType == EL_SOLID)
				);
		}
	}

	CorrectVertexVisibility();
	Get3DBox(nullptr, &m_FragmentBox);
}


inline void UpdateBox(const CRotator* Rot, S3DBox *Box, const S3dPoint& p1)
{
	S3dPoint p=p1;

	if (Rot)
		Rot->Rotate(p.x, p.y, p.z);
	if(p.x > Box->x_max)
		Box->x_max = p.x;
	if(p.x < Box->x_min)
		Box->x_min = p.x;
	if(p.y > Box->y_max)
		Box->y_max = p.y;
	if(p.y < Box->y_min)
		Box->y_min = p.y;
	if(p.z > Box->z_max)
		Box->z_max = p.z;
	if(p.z < Box->z_min)
		Box->z_min = p.z;
}

void CViewGeometry::Get3DBox(const CRotator *Rot, S3DBox *Box, const CViewVertexArray * pVertexArray)
{

	// Определяем ограничивающий параллелепипед
	// при текущем угле поворота
	const CViewVertexArray &va = pVertexArray ? *pVertexArray : VertexArray;
	SViewVertex			p;
	if(va.size() != 0)
	{
		p = va[0];
	}
	else
	{
		p.x = p.y = p.z = 0;
	}

	if (Rot)
		Rot->Rotate(p.x, p.y, p.z);
	Box->x_min = Box->y_min = Box->z_min = 1e30f;
	Box->x_max = Box->y_max = Box->z_max = -1e30f;
	size_t nVertexs = va.size();
	for(size_t i = 0; i < nVertexs ; i++)
	{
		p = va[i];
		if(!p.FragmentFlag || (p.Flag & VF_DELETED) != 0)
			continue;
		UpdateBox(Rot, Box, p);
	}
}

void CViewGeometry::GetMax3DBox(const CRotator *Rot, S3DBox *Box)
{
	Box->x_min = Box->y_min = Box->z_min = 1e30f;
	Box->x_max = Box->y_max = Box->z_max = -1e30f;
	S3DBox b;
	CViewGeometry::Get3DBox(nullptr, &b);
	UpdateBox(Rot, Box, S3dPoint(b.x_min, b.y_min, b.z_min)); 
	UpdateBox(Rot, Box, S3dPoint(b.x_min, b.y_min, b.z_max)); 
	UpdateBox(Rot, Box, S3dPoint(b.x_min, b.y_max, b.z_min)); 
	UpdateBox(Rot, Box, S3dPoint(b.x_min, b.y_max, b.z_max)); 
	UpdateBox(Rot, Box, S3dPoint(b.x_max, b.y_min, b.z_min)); 
	UpdateBox(Rot, Box, S3dPoint(b.x_max, b.y_min, b.z_max)); 
	UpdateBox(Rot, Box, S3dPoint(b.x_max, b.y_max, b.z_min)); 
	UpdateBox(Rot, Box, S3dPoint(b.x_max, b.y_max, b.z_max)); 
	return;
}

void CViewGeometry::Retriangulate()
{
}

void CViewGeometry::BuildArrays()
{
	if (m_pOptions&&m_pDrawOptions)
		SetupElementColors(m_pOptions, m_pDrawOptions->Mode);
	ElementArray.BuildArrays(VertexArray, ElementArray.GetVector(), ElementArray.size());
	if (m_bOptimize)
		BuildLineStrips();
}

void CViewGeometry::BuildLineStrips()
{
	SLineStripRec	*Strip = GetNodeCashe()->Strips(0);
	if (Strip == nullptr)
		return;
	std::vector<UINT32> &linestrips = ElementArray.m_linestrips;
	linestrips.resize(0);
	while (Strip->Vertex != -1)
	{
		linestrips.push_back(0);
		size_t nSize = linestrips.size() - 1;
		UINT32 nCount = 0;
		for (; Strip->Vertex != -1; Strip++)
		{
			linestrips.push_back(Strip->Vertex);
			nCount++;
		}
		linestrips[nSize] = nCount;
		Strip++;
	}
}

void CViewGeometry::PerformCut(CCutter& rCutter, SCutRecord *r)
{
	if (m_pFlatGeometry != nullptr)
	{
		m_pFlatGeometry->PerformCut(rCutter, r);
		size_t i;
		for (i=0; i<NumRealVertexs; i++)
			VertexArray[i].FragmentFlag = m_pFlatGeometry->VertexArray[i].FragmentFlag;
		for (i=NumRealVertexs; i<VertexArray.size(); i++)
			VertexArray[i].FragmentFlag = false;
		
		int nMaxRealElemNum = ElementArray.GetMaxElemID();
		std::vector<bool> bvecShowRealElements(nMaxRealElemNum+1, false);
		for(i = 0; i <m_pFlatGeometry->ElementArray.size(); i++)
			if (m_pFlatGeometry->ElementArray[i].FragmentFlag)
				bvecShowRealElements[m_pFlatGeometry->ElementArray[i].NumElem] = true;
		for(i=0; i<ElementArray.size(); i++)
		{
			CViewElement &El = ElementArray[i];
			El.FragmentFlag = bvecShowRealElements[El.NumElem];
		}
		if (ElementArray.GetSelectedElement()==r->NumEl)
			ElementArray.UnselectElements();
		CorrectVertexVisibility();
		return;

	}
	size_t nElements = ElementArray.size();
	switch (r->Type)
	{
		case INV_CUT:
		{
			UINT i;
			for(i = 0; i < nElements; i++)
			{
				CViewElement	El = ElementArray[i];
				if(!El.FragmentFlag)
					continue;

				bool	bAllIn = true;
				for(int j = 0; j < El.NumVertexs(); j++)
				{
					SViewVertex v = VertexArray[El.Points[j]];
					r->Rot.Rotate(v.x, v.y, v.z);
					bAllIn = bAllIn && (v.x > r->x1 && v.x < r->x2 && v.y > r->y1 && v.y < r->y2);
				}

				ElementArray[i].FragmentFlag = !bAllIn;
			}

			size_t nVertexs = VertexArray.size();
			for(i = 0; i < nVertexs; i++)
			{
				SViewVertex v = VertexArray[i];
				if(!v.FragmentFlag)
					continue;
				r->Rot.Rotate(v.x, v.y, v.z);
				VertexArray[i].FragmentFlag = !(v.x > r->x1 && v.x < r->x2 && v.y > r->y1 && v.y < r->y2);
			}

			int nMaxRealElemNum = ElementArray.GetMaxElemID();
			std::vector<bool> bvecShowRealElements(nMaxRealElemNum+1, false);
			for(i = 0; i < nElements; i++)
			{
				CViewElement	El = ElementArray[i];
				if(!El.FragmentFlag)
					continue;
				bvecShowRealElements[El.NumElem] = true;
			}
			for(i = 0; i < nElements; i++)
			{
				CViewElement	&El = ElementArray[i];
				El.FragmentFlag = bvecShowRealElements[El.NumElem];
			}

		}
		break;
	case CUT:
		{
			size_t nVertexs = VertexArray.size();
			size_t i;
			for(i = 0; i < nVertexs; i++)
			{
				SViewVertex v = VertexArray[i];
				if(!v.FragmentFlag)
					continue;
				r->Rot.Rotate(v.x, v.y, v.z);
				VertexArray[i].FragmentFlag =
					(
						v.x > r->x1 &&
						v.x < r->x2 && v.y > r->y1 &&
						v.y < r->y2
					);
			}

			int nMaxRealElemNum = ElementArray.GetMaxElemID();
			std::vector<bool> bvecShowRealElements(nMaxRealElemNum+1, true);

			for(i = 0; i < nElements; i++)
			{
				CViewElement	&El = ElementArray[i];
				if(!El.FragmentFlag)
				{
					bvecShowRealElements[El.NumElem] = false;
					continue;
				}
				for(int j = 0; j < El.NumVertexs(); j++)
				{
					if(!VertexArray[El.Points[j]].FragmentFlag)
					{
						El.FragmentFlag = false;
						bvecShowRealElements[El.NumElem] = false;
						break;
					}
				}
			}
			for(i = 0; i < nElements; i++)
			{
				CViewElement &El = ElementArray[i];
				if (!bvecShowRealElements[El.NumElem])
					El.FragmentFlag = false;
			}

		}
		break;
	case HIDE_ELEMENT:
		{
			for (UINT i=0; i<ElementArray.size(); i++)
			{
				CViewElement &el = ElementArray[i];
				if (el.NumElem == r->NumEl)
				{
					el.FragmentFlag = false;
				}
			}
			
		}
		ElementArray.UnselectElements();
		break;
	case HIDE_ELEMENT_PLATE:
		{
			double a=0,b=0,c=0,d=0;
			UINT i;
			for (i=0; i<nElements; i++)
			{
				CViewElement &el = ElementArray[i];
				if (el.NumElem == r->NumEl && !el.IsContour())
				{
					a = el.OrgNorm.v[0];
					b = el.OrgNorm.v[1];
					c = el.OrgNorm.v[2];
					S3dPoint pt = S3dPoint(VertexArray[el.Points[0]]);
					d = pt.x*a + pt.y*b+ pt.z*c;
					break;
				}
			}
			for (i=0; i<nElements; i++)
			{
				CViewElement	El = ElementArray[i];
				if(!El.FragmentFlag)
					continue;

				bool	bAllIn = true;
				for(int j = 0; j < El.NumVertexs(); j++)
				{
					SViewVertex v = VertexArray[El.Points[j]];
					bAllIn = bAllIn && (fabs(v.x*a+v.y*b+v.z*c - d) < 1e-3);
				}

				ElementArray[i].FragmentFlag = !bAllIn;
			}
			int nMaxRealElemNum = ElementArray.GetMaxElemID();
			std::vector<bool> bvecShowRealElements(nMaxRealElemNum+1, false);
			for(i = 0; i < nElements; i++)
			{
				CViewElement	El = ElementArray[i];
				if(!El.FragmentFlag)
					continue;
				bvecShowRealElements[El.NumElem] = true;
			}
			for(i = 0; i < nElements; i++)
			{
				CViewElement	&El = ElementArray[i];
				El.FragmentFlag = bvecShowRealElements[El.NumElem];
			}

			
		}
		ElementArray.UnselectElements();
		break;
	case SHOW_ELEMENT_PLATE:
		{
			double a=0,b=0,c=0,d=0;
			UINT i;
			for (i=0; i<nElements; i++)
			{
				CViewElement &el = ElementArray[i];
				if (el.NumElem == r->NumEl && !el.IsContour())
				{
					a = el.OrgNorm.v[0];
					b = el.OrgNorm.v[1];
					c = el.OrgNorm.v[2];
					S3dPoint pt = S3dPoint(VertexArray[el.Points[0]]);
					d = pt.x*a + pt.y*b+ pt.z*c;
					break;
				}
			}
			int nMaxRealElemNum = ElementArray.GetMaxElemID();
			std::vector<bool> bvecShowRealElements(nMaxRealElemNum+1, true);
			for (i=0; i<nElements; i++)
			{
				CViewElement	El = ElementArray[i];
				if(!El.FragmentFlag)
				{
					bvecShowRealElements[El.NumElem] = false;
					continue;
				}
				bool	bAllIn = true;
				for(int j = 0; j < El.NumVertexs(); j++)
				{
					SViewVertex v = VertexArray[El.Points[j]];
					bAllIn = bAllIn && (fabs(v.x*a+v.y*b+v.z*c - d) < 1e-3);
				}

				ElementArray[i].FragmentFlag = bAllIn;
				if (!bAllIn)
					bvecShowRealElements[El.NumElem] = false;
			}
			for(i = 0; i < nElements; i++)
			{
				CViewElement &El = ElementArray[i];
				if (!bvecShowRealElements[El.NumElem])
					El.FragmentFlag = false;
			}
	
		}
		ElementArray.UnselectElements();
		break;
		
	}
	CorrectVertexVisibility();
}

void CViewGeometry::ClearCut()
{
	if (m_pFlatGeometry)
		m_pFlatGeometry->ClearCut();
	size_t	nVertexs = VertexArray.size();
	size_t i;
	for(i = 0; i < nVertexs; i++)
		VertexArray[i].FragmentFlag = true;

	size_t nElements = ElementArray.size();
	for(i = 0; i < nElements; i++)
	{
		ElementArray[i].FragmentFlag = true;
	}
	CorrectVertexVisibility();
}

#ifdef SCAD21
void CViewGeometry::ProcessOprElement(CElemInfApiExt &e, SCHEMA * Schem, const UINT & i, BYTE TypePlate)
{
	S3dPoint	p[3];
	for (int i = 0; i < 3; i++)
		p[i] = S3dPoint(VertexArray[NUM(e.Node[i])]);

	CVectorType	p1v(p[1].x - p[0].x, p[1].y - p[0].y, p[1].z - p[0].z);
	CVectorType p2v(p[2].x - p[1].x, p[2].y - p[1].y, p[2].z - p[1].z);
	CVectorType Norm;
	Norm.SetCrossProduct(p1v, p2v);
	Norm.Normalize();

	UINT nHoles = ApiElemGetQuantityHole(Schem, i + 1);
	UINT nSumQuantHoleNodes = 0;
	for (UINT j = 0; j<nHoles; j++)
	{
		UINT nQuantNodes = 0;
		const UINT *pNodes;
		ApiElemGetHole(Schem, i + 1, j + 1, &nQuantNodes, &pNodes);
		nSumQuantHoleNodes += nQuantNodes;
		AddOprContours(nQuantNodes, e, i, TypePlate, pNodes, Norm);
	}
	int nQantExt = e.QuantityNode - nSumQuantHoleNodes;
	AddOprContours(nQantExt, e, i, TypePlate, e.Node, Norm);
}
#endif

bool CViewGeometry::LoadFromSchema(SCHEMA * Schem, BYTE TypeProfile, BYTE TypePlate, bool bOptimize)
{

	m_bOptimize = bOptimize;
	m_DuplicatedElements.clear();
#ifdef SCAD21
	m_bForumGeometry = ApiGetTypeSchema(Schem) == 2;
#else
	m_bForumGeometry = ::PathMatchSpecA(Schem->FileName, "*.opr") == TRUE;
#endif
	if (TypeProfile != 0 || TypePlate != 0)
	{
		delete m_pFlatGeometry;
		m_pFlatGeometry = new CForumViewGeometry(m_pOptions, m_pDrawOptions);
		m_pFlatGeometry->m_bDeleteInnerPlates = m_bDeleteInnerPlates;
		if (!m_pFlatGeometry->LoadFromSchema(Schem, 0, 0, true))
			return false;
		m_DuplicatedElements = m_pFlatGeometry->m_DuplicatedElements;
	}
#ifdef SCAD21
	UINT nNodes = ApiGetQuantityNode(Schem);
	VertexArray.reserve(nNodes);
	VertexArray.resize(0/*Schem->QuantityNode + Schem->Video.QuantityNodeBody*/);

	UINT nVertexs = 0;
	for (UINT i = 0; i < nNodes; i++)
	{
		SViewVertex v;
		LPCNodeApi pNode = ApiGetNode(Schem, i + 1);
		v.x = FLOAT_TYPE(pNode->x);
		v.y = FLOAT_TYPE(pNode->y);
		v.z = FLOAT_TYPE(pNode->z);
		v.FragmentFlag = true;
		v.Flag = 0;
		if (!(pNode->Flag & VF_DELETED)/* && !Schem->GetNodeBitFlag(i+1,8)*/)
			nVertexs++;
		else
		{
			v.FragmentFlag = false;
			v.Flag |= VF_DELETED;
		}
		v.nMainVertex = -1;
		VertexArray.push_back(v);
	}
	m_ModelInfo.m_nNodeCount = nVertexs;
	NumRealVertexs = VertexArray.size();
	//pCK = Schem->Video.Coord;
	//for(i = 0; i < Schem->Video.QuantityNodeBody; i++)
	//{
	//	SViewVertex v;
	//	v.x = FLOAT_TYPE(pCK[i].x);
	//	v.y = FLOAT_TYPE(pCK[i].y);
	//	v.z = FLOAT_TYPE(pCK[i].z);
	//	v.FragmentFlag = true;
	//	v.Flag = 0;
	//	v.nMainVertex = -1;
	//	VertexArray.push_back(v);
	//}

	UINT nElem = ApiGetElemQuantity(Schem);
	ElementArray.reserve(nElem);
	ElementArray.resize(0);
	m_vecExtraPoints.resize(0);
	//pEB = Video->ElemBody;
	for (UINT i = 0; i < nElem; i++/*, pEB++*/)
	{
		CElemInfApiExt e(Schem);
		ApiElemGetInf(Schem, i + 1, &e);
		if (e.IsDeletet)
			continue;
		e.UpdateThickness();
		if (m_bForumGeometry)
		{
			//void *p = *((void **)Schem);
			ProcessOprElement(e, Schem, i, TypePlate);
			continue;
		}
		if (ProcessSpecialTypes(e))
			continue;
		CViewElement el(RGB(192, 192, 192));
		el.OrgType = GetElemOrgType(e.TypeElem);
		el.NumElem = i + 1;//e.NumElem;

		if (e.GetType() == EL_LINE && TypeProfile)
		{
			std::vector<S3dPoint> vecContour;
			bool bClosed = false;
			if (e.getContour(vecContour, bClosed))
			{
				double sk[16];
				UINT nQnt = 0;
				ApiGetSystemCoordElemOne(Schem, el.NumElem, (BYTE*)&e.TypeElem, &nQnt, sk);
				const S3dPoint pt1 = VertexArray[NUM(e.Node[0])];
				const S3dPoint pt2 = VertexArray[NUM(e.Node[1])];
				const CVectorType v12 = CVectorType(pt2) - pt1;
				const CVectorType vCan(1, 0, 0);
				FLOAT_TYPE ang = vCan.AngleTo(v12);
				CVectorType axis = vCan.CrossProduct(v12);
				CVectorType vx(1, 0, 0);
				CVectorType vy(0, 1, 0);
				CVectorType vz(0, 0, 1);
				vx.RotateAroundAxis(axis, ang);
				vy.RotateAroundAxis(axis, ang);
				vz.RotateAroundAxis(axis, ang);
				const size_t nIdx = VertexArray.size();
				for (size_t i = 0; i < vecContour.size(); i++)
				{
					const S3dPoint& pti = vecContour[i];
					CVectorType vecShift = vx*pti.x + vy*pti.y + vz*pti.z;
					SViewVertex vtx1(pt1 + vecShift);
					vtx1.nMainVertex = NUM(e.Node[0]);
					SViewVertex vtx2(pt2 + vecShift);
					vtx2.nMainVertex = NUM(e.Node[1]);

					VertexArray.push_back(vtx1);
					VertexArray.push_back(vtx2);
				}
				for (size_t i = 0; i < vecContour.size()+ (bClosed ? 0:-1); i++)
				{
					el.Type = EL_QUAD;
					el.Points[3] = nIdx + i * 2;
					el.Points[2] = nIdx + i * 2+1;
					el.Points[1] = nIdx + ((i+1)%vecContour.size()) * 2 + 1;
					el.Points[0] = nIdx + ((i+1)%vecContour.size()) * 2;
					el.SetNormal(VertexArray.GetVector());
					ElementArray.push_back(el);
				}
				continue;
			}
			int n = 0;
		}
		ElementArray.push_back(el);
		const size_t nEl = ElementArray.size() - 1;
		CViewElement *pE = &ElementArray[nEl];
		pE->Type = e.GetType();

		if (pE->Type == EL_QUAD)
		{
			for (int j = 0; j < 4; j++)
				pE->Points[j] = NUM(e.Node[N_S(j)]);
		}
		else
		{
			for (int j = 0; j < pE->NumVertexs(); j++)
				pE->Points[j] = NUM(e.Node[j]);
		}

		if (TypePlate && e.m_fThickness > 1e-5 && pE->Type != EL_LINE)
		{
			size_t nNewVertexsIdx = VertexArray.size();
			pE->SetNormal(VertexArray.GetVector());
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < pE->NumVertexs(); j++)
				{
					S3dPoint pt = VertexArray[pE->Points[j]];
					float fShift = e.m_fThickness / 2 * (i == 0 ? -1 : 1);
					pt.x += pE->Norm.v[0] * fShift;
					pt.y += pE->Norm.v[1] * fShift;
					pt.z += pE->Norm.v[2] * fShift;
					VertexArray.push_back(SViewVertex(pt));
				}
			for (int j = 0; j < pE->NumVertexs(); j++)
				pE->Points[pE->NumVertexs()-1-j] = nNewVertexsIdx + j;
			for (int j = 0; j < pE->NumVertexs(); j++)
			{
				el.Points[0] = nNewVertexsIdx + j;
				el.Points[1] = nNewVertexsIdx + (j + 1) % pE->NumVertexs();
				el.Points[2] = nNewVertexsIdx + (j + 1) % pE->NumVertexs() + pE->NumVertexs();
				el.Points[3] = nNewVertexsIdx + j + pE->NumVertexs();
				el.SetNormal(VertexArray.GetVector());
				el.OrgNorm = pE->Norm;
				el.Type = EL_QUAD;
				ElementArray.push_back(el);
				pE = &ElementArray[nEl];
			}
			for (int j = 0; j < pE->NumVertexs(); j++)
				el.Points[j] = nNewVertexsIdx + pE->NumVertexs() + j;
			el.Norm = pE->Norm*(-1.0f);
			el.OrgNorm = pE->OrgNorm;
			el.Type = pE->Type;
			ElementArray.push_back(el);
			pE = &ElementArray[nEl];
		}

		int j = e.QuantityNode - pE->NumVertexs(); //Schem->pFormat[pEB->NumElem - 1].QuantityNode - pE->NumVertexs();
		if (j>0)
		{
			pE->m_nExtraPoints = m_vecExtraPoints.size();
			m_vecExtraPoints.push_back(e.QuantityNode);
			for (int k = pE->NumVertexs(); j>0; j--, k++)
				m_vecExtraPoints.push_back(NUM(e.Node[k]));
		}
		else
		{
			pE->m_nExtraPoints = -1;
		}
	}
	m_ModelInfo.m_nElementCount = nElem;
	//m_nContouredElements = ElementArray.size();
	//VertexFlag = new byte[Schem->QuantityNode];


	// Заполнение флагов связей в узлах
	for (UINT i = 0; i < nNodes; i++)
	{
		UINT nFlag = ApiGetBound(Schem, i + 1);
		if (nFlag == 0)
			continue;
		VertexArray[i].Flag |= byte(nFlag);
	}

#else
	int		i;
	CK			*pCK;
	LOOK_BODY	*Video;
	ELEM_BODY	*pEB;
	Schem->LookBody(nullptr, TypeProfile, TypePlate);
	Video = &Schem->Video;

	VertexArray.reserve(Schem->QuantityNode + Schem->Video.QuantityNodeBody);
	VertexArray.resize(0/*Schem->QuantityNode + Schem->Video.QuantityNodeBody*/);

	pCK = Schem->GetCoord();
	UINT nVertexs = 0;
	for (i = 0; i < Schem->QuantityNode; i++)
	{
		SViewVertex v;
		v.x = FLOAT_TYPE(pCK[i].x);
		v.y = FLOAT_TYPE(pCK[i].y);
		v.z = FLOAT_TYPE(pCK[i].z);
		v.FragmentFlag = true;
		v.Flag = 0;
		if (!(pCK[i].Flag & VF_DELETED) && !Schem->GetNodeBitFlag(i + 1, 8))
			nVertexs++;
		else
		{
			v.FragmentFlag = false;
			v.Flag |= VF_DELETED;
		}
		v.nMainVertex = -1;
		VertexArray.push_back(v);
	}
	m_ModelInfo.m_nNodeCount = nVertexs;
	NumRealVertexs = VertexArray.size();
	pCK = Schem->Video.Coord;
	for (i = 0; i < Schem->Video.QuantityNodeBody; i++)
	{
		SViewVertex v;
		v.x = FLOAT_TYPE(pCK[i].x);
		v.y = FLOAT_TYPE(pCK[i].y);
		v.z = FLOAT_TYPE(pCK[i].z);
		v.FragmentFlag = true;
		v.Flag = 0;
		v.nMainVertex = -1;
		VertexArray.push_back(v);
	}

	ElementArray.reserve(Video->QuantityElemBody);
	ElementArray.resize(Video->QuantityElemBody);
	m_vecExtraPoints.resize(0);
	ElementArray.m_mapVertexs.clear();
	pEB = Video->ElemBody;
	for (i = 0; i < Video->QuantityElemBody; i++, pEB++)
	{
		CViewElement *pE = &ElementArray[i];
		pE->Color = RGB(192, 192, 192);
		pE->FragmentFlag = pE->DrawFlag = true;
		pE->bContoured = true;
		pE->bContourOnly = false;

		pE->OrgType = GetElemOrgType(Schem->pFormat[pEB->NumElem - 1].TypeElem);
		//		if (pE->OrgType>EL_SOLID && pEB->Type!=2)
		//			continue;
		pE->NumElem = pEB->NumElem;

		if (pEB->Type == 2)
			pE->Type = EL_LINE;
		if (pEB->Type == 3 || pEB->Type == 5)
			pE->Type = EL_TRIANGLE;
		if (pEB->Type == 4 || pEB->Type == 6)
			pE->Type = EL_QUAD;

		if (pE->Type != EL_QUAD)
		{
			for (int j = 0; j < 4; j++)
				pE->Points[j] = NUM(pEB->Node[j]);
		}
		else
		{
			for (int j = 0; j < 4; j++)
				pE->Points[j] = NUM(pEB->Node[N_S(j)]);
			if (pE->OrgType == EL_BAR)
			{
				VertexArray[pE->Points[0]].nMainVertex = NUM(Schem->pFormat[pEB->NumElem - 1].pNode[0]);
				VertexArray[pE->Points[1]].nMainVertex = NUM(Schem->pFormat[pEB->NumElem - 1].pNode[0]);
				VertexArray[pE->Points[2]].nMainVertex = NUM(Schem->pFormat[pEB->NumElem - 1].pNode[1]);
				VertexArray[pE->Points[3]].nMainVertex = NUM(Schem->pFormat[pEB->NumElem - 1].pNode[1]);
			}
		}
		FORMAT& frm = Schem->pFormat[pEB->NumElem - 1];
		RIGID_STR * pRigid = Schem->_Rigid.Get(frm.TypeRigid);
		RIGID_LIST_OLD *pRigidOld = Schem->_Rigid.GetRigid(frm.TypeRigid);
		int j = frm.QuantityNode - pE->NumVertexs();
		if (j>0)
		{
			pE->m_nExtraPoints = m_vecExtraPoints.size();
			m_vecExtraPoints.push_back(frm.QuantityNode);
			for (int k = pE->NumVertexs(); j>0; j--, k++)
				m_vecExtraPoints.push_back(NUM(frm.pNode[k]));
		}
		else
		{
			pE->m_nExtraPoints = -1;
		}
	}
	m_ModelInfo.m_nElementCount = Video->QuantityElemBody;
	//m_nContouredElements = ElementArray.size();
	//VertexFlag = new byte[Schem->QuantityNode];


	// Заполнение флагов связей в узлах
#ifdef SCAD11
	int nBounds = Schem->_Bound.GetQuantity();
#else
	int nBounds = Schem->_Bound.GetQuantityBound();
#endif
	for (i = 0; i < nBounds; i++)
	{
#ifdef SCAD11
		OBJECT_LIST_STR	*bl = Schem->_Bound.Get(i + 1);
#else
		BOUND_LIST	*bl = Schem->_Bound.GetBound(i + 1);
#endif
		if (bl->Type != 0)
			continue;
		for (int j = 0; j < bl->Quantity; j++)
		{
			if (bl->List[j])
				VertexArray[bl->List[j] - 1].Flag |= bl->Mask;
		}
	}

	Schem->DeleteLookBody();
#endif
	if (m_bForThumbs)
		return true;
	LoadAxesInfo(Schem);
	PostProcessSchema(Schem, TypeProfile != 0, TypePlate != 0);
	SetupAndOptimize(bOptimize);
	return true;
}

void CViewGeometry::CorrectVertexVisibility()
{
	CViewGeometry *Geometry = m_pFlatGeometry ? m_pFlatGeometry : this;
	std::vector<bool> bvecShowRealElements(ElementArray.GetMaxElemID()+1, false);
	UINT i;
	if (m_bShowUsedNodes)
	{
		for (i=0; i<VertexArray.size(); i++)
			VertexArray[i].FragmentFlag = false;
	}
	for(i = 0; i <ElementArray.size(); i++)
		if (ElementArray[i].FragmentFlag && ElementArray[i].DrawFlag)
			bvecShowRealElements[ElementArray[i].NumElem] = true;
	if (m_pFlatGeometry)
		for(i = 0; i < Geometry->ElementArray.size(); i++)
		{
			CViewElement	El = Geometry->ElementArray[i];
			if(bvecShowRealElements[El.NumElem])
				continue;
			int j;
			for(j = 0; j < El.NumVertexs(); j++)
			{
				Geometry->VertexArray[El.Points[j]].FragmentFlag = false;
			}
		}
	for(i = 0; i < ElementArray.size(); i++)
	{
		CViewElement	El = ElementArray[i];
		if(bvecShowRealElements[El.NumElem])
			continue;
		for(int j = 0; j < ElementArray[i].NumVertexs(); j++)
		{
			VertexArray[ElementArray[i].Points[j]].FragmentFlag = false;
		}
	}
	if (m_pFlatGeometry)
		for(i = 0; i < Geometry->ElementArray.size(); i++)
		{
			CViewElement	El = Geometry->ElementArray[i];
			if(!bvecShowRealElements[El.NumElem])
				continue;
			int j;
			for(j = 0; j < El.NumVertexs(); j++)
			{
				Geometry->VertexArray[El.Points[j]].FragmentFlag = true;
			}
		}
	for(i = 0; i < ElementArray.size(); i++)
	{
		CViewElement	El = ElementArray[i];
		if(!bvecShowRealElements[El.NumElem])
			continue;
		for(int j = 0; j < ElementArray[i].NumVertexs(); j++)
		{
			VertexArray[ElementArray[i].Points[j]].FragmentFlag = true;
		}
	}
	if (m_pNodeCashe)
		m_pNodeCashe->Recreate();
	BuildArrays();
}

void CViewGeometry::DeleteNondrawableElements()
{

    UINT nDrawableElements =0;
    for (UINT i=0; i<ElementArray.size(); i++)
	{
        if (ElementArray[i].DrawFlag)
            ElementArray[nDrawableElements++] =  ElementArray[i];
	}
    ElementArray.resize(nDrawableElements);
}

void CViewGeometry::SetElColor(CViewElement& el, const struct SViewOptions* pOptions, EDrawMode Mode) const
{
    switch (el.OrgType)
    {
    case  EL_BAR:
        el.Color = pOptions->BarColor;
        break;
	case  EL_COLUMN:
        el.Color = pOptions->ColumnColor;
        break;
	case  EL_BEAM:
        el.Color = pOptions->BeamColor;
        break;
    case  EL_PLATE:
        el.Color = pOptions->PlateColor;
        break;
    case  EL_SOLID:
        el.Color = pOptions->SolidColor;
        break;
	case  EL_SLAB:
	case  EL_ROOF:
	case  EL_WALL:
		if (el.Type == EL_LINE && Mode != M_LINES)
			el.Color =  pOptions->EdgeColor;
		else
			switch (el.OrgType)
			{
			case  EL_SLAB:
		        el.Color = pOptions->SlabColor;
				break;
			case  EL_ROOF:
		        el.Color = pOptions->RoofColor;
				break;
			case  EL_WALL:
		        el.Color = pOptions->WallColor;
				break;
			default: break;
			}
		break;
    case EL_ISO: break;
    default: break;
    }
	if (!el.IsContour() && IsElDuplicated(el.NumElem))
		el.Color = pOptions->DupeColor;
	if (!el.IsContour() && ElementArray.GetSelectedElement() !=0 && el.NumElem == ElementArray.GetSelectedElement())
		el.Color ^= 0xffffff;
}

void CViewGeometry::SetupElementColors(const struct SViewOptions* pOptions, EDrawMode Mode)
{
    // Замена цвета элемента на настройки
	for (UINT i =0; i<ElementArray.size(); i++)
	{
		CViewElement &el = ElementArray[i];
		SetElColor(el, pOptions, Mode);
	}
}

#if !defined(SCAD11) && !defined(SCAD21)
typedef S_Doc21 COORD_LINE_OLD;
typedef KOORLINE COORD_LINE_AXIS_OLD;
#endif

#ifdef SCAD21
struct COORD_LINE_AXIS_OLD {	BYTE Type; char Name[16]; double Pos; };
struct COORD_LINE_OLD  { WORD XLineQuantity; WORD YLineQuantity; WORD HLineQuantity; COORD_LINE_AXIS_OLD Line[1]; };
#endif

static void CopyAxes(TAxeSet &axe, COORD_LINE_AXIS_OLD Line[],WORD nCount, WORD &index)
{
	WORD i;
	for (i=0;i<nCount;i++, index++)
	{
		SAxe a;
		a.m_name = Line[index].Name;
		a.m_pos =  FLOAT_TYPE(Line[index].Pos);
		axe.push_back(a);
	}

}

void CViewGeometry::LoadAxesInfo(SCHEMA *Schem)
{
	if (!Schem)
		return;
#ifdef SCAD11
COORD_LINE_OLD *pCoordLine = Schem->_CoordLine.GetOld();
#else
#ifdef SCAD21
COORD_LINE_OLD *pCoordLine = nullptr;
#else
COORD_LINE_OLD *pCoordLine = (COORD_LINE_OLD *)Schem->ReadDocument(21);
#endif
#endif

	m_Axes.X.resize(0);
	m_Axes.Y.resize(0);
	m_Axes.Z.resize(0);
	if (pCoordLine && (pCoordLine->XLineQuantity !=0 || pCoordLine->YLineQuantity !=0 || pCoordLine->HLineQuantity))
	{
		WORD index=0;
		CopyAxes(m_Axes.X, pCoordLine->Line, pCoordLine->XLineQuantity, index);
		CopyAxes(m_Axes.Y, pCoordLine->Line, pCoordLine->YLineQuantity, index);
		CopyAxes(m_Axes.Z, pCoordLine->Line, pCoordLine->HLineQuantity, index);
	}
#if !defined(SCAD11) && !defined(SCAD21) 
	if (pCoordLine)
		Schem->MemoryFree(pCoordLine);
#endif
}

void CViewGeometry::Render(IFemRenderer *pRenderer, const SViewOptions * pViewOptions, const CDrawOptions * pDrawOptions)
{
	pRenderer->Render(this, pViewOptions, pDrawOptions);
}

void CViewGeometry::OnDrawScene(IFemRenderer *pRenderer, const SViewOptions * pViewOptions, const CDrawOptions * pDrawOptions, const SPerspectiveView & rViewPos)
{
	CGLDraw	GlDraw(this, &rViewPos, pViewOptions, pDrawOptions, pRenderer /*, 15*pViewOptions->LineWidth*/);
	GlDraw.Draw();
}

INodeCashe* CViewGeometry::GetNodeCashe()
{
	return m_pNodeCashe ? m_pNodeCashe : (m_pNodeCashe=new CNodeCashe(this, m_bOptimize));
}

