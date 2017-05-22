// ForumViewGeometry.cpp: implementation of the CForumViewGeometry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "scadviewer.h"
#include "ForumViewGeometry.h"
#ifndef SCAD11
#ifdef SCAD21
#include "SCADAPIX.hxx"
#else
#include "schema.h"
#endif
#else
#include "schema.hpp"
#endif
#include <malloc.h>
#include "SvGluTesselator.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CForumViewGeometry::CForumViewGeometry(const SViewOptions * pViewOptions, const CDrawOptions * pDrawOptions) : CViewGeometry(pViewOptions,pDrawOptions)
{
}

CForumViewGeometry::~CForumViewGeometry()
{

}

/*virtual*/ TOrgElemType CForumViewGeometry::GetElemOrgType(WORD wTypeElem)
{
	switch (wTypeElem) // Стена 1080 - пер, 1085 - крыша
	{
	case 1020: return EL_COLUMN;
	case 1040: return EL_BEAM;
	case 1060:
	case 1061:
		return EL_WALL; 
	case 1080: return EL_SLAB;
	case 1085: return EL_ROOF;
	}
#ifdef SCAD21
	return CViewGeometry::GetElemOrgType(wTypeElem);
#else
	return (TOrgElemType) ElemType(wTypeElem);
#endif
}


void CForumViewGeometry::PostProcessSchema(SCHEMA *Schem, bool bExpandProfiles, bool bExpandPlates)
{
	int nElements =0;
#ifdef SCAD21
	for (UINT j = 0; j < ApiGetElemQuantity(Schem); j++)
	{
/*
		if( !IsElemVis( j + 1 ) )
			continue;
*/
		//if(Schem->GetBitFlag(j+1,7)) continue; // Элемент удален
		//if(Schem->GetBitFlag(j+1,0)) continue; // Элемент вне видимого фрагмента
		nElements++;
		CElemInfApi e;
		ApiElemGetInf(Schem, j+1, &e);
		if (e.IsDeletet)
			continue;
		int nFeElType = e.TypeElem;
		switch(nFeElType)
		{
		case 1060:
		case 1061:
		case 1080:
		case 1085:
			ReadOprPolygon(Schem, j+1, bExpandPlates);
			break;
		default:
			continue;
		}
	}
#else
	int j;
	for (j = 0; j < Schem->GetQuantityElem(); j++)
	{
/*
		if( !IsElemVis( j + 1 ) )
			continue;
*/
		if(Schem->GetBitFlag(j+1,7)) continue; // Элемент удален
		if(Schem->GetBitFlag(j+1,0)) continue; // Элемент вне видимого фрагмента
		nElements++;
		int nFeElType = Schem->GetTypeElem(j + 1);
		switch(nFeElType)
		{
		case 1060:
		case 1061:
		case 1080:
		case 1085:
			ReadOprPolygon(Schem, j+1, bExpandPlates);
			break;
		default:
			continue;
		}
	}
#endif
	m_ModelInfo.m_nElementCount = nElements;

	//DeleteEqualNodes();

};

void CForumViewGeometry::ReadOprPolygon(SCHEMA *m_Project, NUM_ELEM_TYPE Nel, bool bUseThickness )
{
	std::vector<SCUINT32> nIndex;
	std::vector<SCUINT32> nHoles;
	//double Thickness = 0;
#ifdef SCAD21
	CElemInfApiExt e(m_Project);
	ApiElemGetInf(m_Project, Nel, &e);
	if (bUseThickness)
		e.UpdateThickness();
	SCUINT32 QntNode = e.QuantityNode;
	SCUINT32 QntTds;

#else
	WORD QntTds=0;
	FORMAT *pF = m_Project->GetFormat(Nel);
	if(!pF) return;
	SCUINT32 QntNode = pF->QuantityNode;
#endif
#ifdef SCAD21	//SCUINT16 nRes;
	TOrgElemType m_CurrElemOrgType = GetElemOrgType(e.TypeElem);

	QntTds = ApiElemGetQuantityHole(m_Project, Nel);
	CSvGluTesselator Tesselator(VertexArray, ElementArray, m_CurrElemOrgType);
	//CSvGpcTesselator Tesselator(VertexArray, ElementArray, m_CurrElemOrgType);
	nIndex.resize(e.QuantityNode);
	for(UINT i = 0; i < e.QuantityNode; i++)
		nIndex[i] = e.Node[i] - 1;
	if (QntTds == 0)
	{

		SC3DRetCode nRetCode = Tesselator.AddPolygon(e.m_fThickness, Nel,  1 , &QntNode, &nIndex[0] );
		ASSERT(nRetCode==S3DRC_OK);
		return;
	}
	UINT nSumQuantHoleNodes = 0;
	nHoles.resize(QntTds+1);
	for (UINT j=0; j<QntTds; j++)
	{
		UINT nQuantNodes;
		const UINT *pNodes;
		ApiElemGetHole(m_Project, Nel, j+1, &nQuantNodes, &pNodes);
		nSumQuantHoleNodes+=nQuantNodes;
		nHoles[j+1]=nQuantNodes;
	}
	int nQantExt = e.QuantityNode - nSumQuantHoleNodes;
	nHoles[0] = nQantExt;
	SC3DRetCode nRetCode = Tesselator.AddPolygon(e.m_fThickness, Nel,  QntTds+1 , &nHoles[0], &nIndex[0] );
	ASSERT(nRetCode==S3DRC_OK);

#elif defined(SCAD11)
	int i;
	IDENT_STR *IdentList= nullptr;

	//SCUINT16 nRes;
	TOrgElemType m_CurrElemOrgType = GetElemOrgType(pF->TypeElem);

	int Ntg = m_Project->GetElemTypeRigid(Nel);
	FLOAT_TYPE fThickness = 0.0f;
	bool bNoHole = false;
	if(Ntg == 0) // Нет жесткости - нет проемов
		bNoHole = true;
	else
	{
		
		m_Project->_Rigid.GetIdent(Ntg,"GE",3,&IdentList);
		
		if(IdentList)
		{
			if(IdentList->Quantity > 2)
			{
				//UseThickness( TRUE );
				fThickness = bUseThickness? FLOAT_TYPE(IdentList->Data[2]) : 0.0f;
				//SetThickness( (SCDOUBLE32)Thickness );
			}
			else
			{
				fThickness = 0.0f;
				//UseThickness( FALSE );
			}
		}
		m_Project->_Rigid.GetIdent(Ntg,"HOLE",5,&IdentList);
		if(IdentList)
		{
			QntTds = WORD(IdentList->Quantity);			
			if(IdentList->Quantity < 1) // нет проемов
				bNoHole = true;
		}
		else
			bNoHole = true;
	}
	CSvGluTesselator Tesselator(VertexArray, ElementArray, m_CurrElemOrgType);
	//CSvGpcTesselator Tesselator(VertexArray, ElementArray, m_CurrElemOrgType);
	if (bNoHole)
	{
		nIndex.resize(pF->QuantityNode);
		for(i = 0; i < pF->QuantityNode; i++)
			nIndex[i] = pF->pNode[i] - 1;

		SC3DRetCode nRetCode = Tesselator.AddPolygon(fThickness, Nel,  1 , &QntNode, &nIndex[0] );
		ASSERT(nRetCode==S3DRC_OK);

		return;
	}
	nHoles.resize(QntTds+1);
	nHoles[0] = SCUINT32(IdentList->Data[0]) - 1;
	if(IdentList->Data[1] >= pF->QuantityNode)
	{
		return;
	}
	for(i = 1; i < QntTds; i++)
	{
		
		if(IdentList->Data[i] >= pF->QuantityNode)
		{
			return;
		}
		nHoles[i] = SCUINT32(IdentList->Data[i] - IdentList->Data[i - 1]);
	}
	if(IdentList->Data[QntTds - 1] >= pF->QuantityNode)
	{
		return;
	}
	nHoles[QntTds] = SCUINT32(pF->QuantityNode - IdentList->Data[QntTds - 1] + 1);
	QntTds++;
	nIndex.resize(pF->QuantityNode);
	for(i = 0; i < pF->QuantityNode; i++)
		nIndex[i] = pF->pNode[i] - 1;
	QntNode = QntTds;

	SC3DRetCode nRetCode = Tesselator.AddPolygon( fThickness, Nel, QntNode, &nHoles[0], &nIndex[0] );
	ASSERT(nRetCode==S3DRC_OK);
	
#else
	int i;
	//SCUINT16 nRes;
	TYPE_DATA_SF *tds;
	TOrgElemType m_CurrElemOrgType = GetElemOrgType(pF->TypeElem);

	int Ntg = m_Project->GetElemTypeRigid(Nel);
	FLOAT_TYPE fThickness = 0.0f;
	bool bNoHole = false;
	if(Ntg == 0) // Нет жесткости - нет проемов
		bNoHole = true;
	else
	{
		
		m_Project->_Rigid.GetIdent(Ntg,"GE",3,QntTds,&tds);
	
		if( QntTds > 3 )
		{
			//UseThickness( TRUE );
			fThickness = bUseThickness? FLOAT_TYPE(tds[3].d) : 0.0f;
			//SetThickness( (SCDOUBLE32)Thickness );
		}
		else
		{
			fThickness = 0.0f;
			//UseThickness( FALSE );
		}

		m_Project->_Rigid.GetIdent(Ntg,"HOLE",5,QntTds,&tds);
		if(QntTds < 2) // нет проемов
			bNoHole = true;
	}
	CSvGluTesselator Tesselator(VertexArray, ElementArray, m_CurrElemOrgType);
	//CSvGpcTesselator Tesselator(VertexArray, ElementArray, m_CurrElemOrgType);
	if (bNoHole)
	{
		nIndex.resize(pF->QuantityNode);
		for(i = 0; i < pF->QuantityNode; i++)
			nIndex[i] = pF->pNode[i] - 1;

		SC3DRetCode nRetCode = Tesselator.AddPolygon(fThickness, Nel,  1 , &QntNode, nIndex );
		ASSERT(nRetCode==S3DRC_OK);

		return;
	}
	nHoles.resize(QntTds);
	nHoles[0] = SCUINT32(tds[1].d) - 1;
	if(tds[1].d >= pF->QuantityNode)
	{
		return;
	}
	for(i = 2; i < QntTds; i++)
	{
		
		if(tds[i].d >= pF->QuantityNode)
		{
			return;
		}
		nHoles[i - 1] = SCUINT32(tds[i].d - tds[i - 1].d);
	}
	if(tds[QntTds - 1].d >= pF->QuantityNode)
	{
		return;
	}
	nHoles[QntTds - 1] = SCUINT32(pF->QuantityNode - tds[QntTds - 1].d + 1);
	nIndex.resize(pF->QuantityNode);
	for(i = 0; i < pF->QuantityNode; i++)
		nIndex[i] = pF->pNode[i] - 1;
	QntNode = QntTds;

	SC3DRetCode nRetCode = Tesselator.AddPolygon( fThickness, Nel, QntNode, nHoles, nIndex );
	ASSERT(nRetCode==S3DRC_OK);
#endif

}




SC3DRetCode ISvTesselator::AddSimpleTriangle( SCUINT32 elemID, SCUINT32 nPt1, SCUINT32 nPt2, SCUINT32 nPt3 ) const
{
	CViewElement el;
	el.Type = EL_TRIANGLE;
	el.OrgType = m_CurrElemOrgType;
	el.bContoured = false;
	el.DrawFlag = el.FragmentFlag = true;
	el.NumElem = elemID;
	el.Points[0] = nPt1;
	el.Points[1] = nPt2;
	el.Points[2] = nPt3;
	el.Points[3] = -1;

	el.SetNormal(VertexArray.GetVector());
	if (el.Norm.DotProduct(el.Norm)<1e-5)
		return S3DRC_OK; // Вырожденный	треугольник не добавляем
	ElementArray.push_back(el);
	return S3DRC_OK;
}

SC3DRetCode	ISvTesselator::AddSimpleQuad( SCUINT32 elemID, SCUINT32 nPt1, SCUINT32 nPt2, SCUINT32 nPt3, SCUINT32 nPt4 ) const
{
	CViewElement el;
	el.Type = EL_QUAD;
	el.OrgType = m_CurrElemOrgType;
	el.bContoured = false;
	el.DrawFlag = el.FragmentFlag = true;
	el.NumElem = elemID;
	el.Points[0] = nPt1;
	el.Points[1] = nPt2;
	el.Points[2] = nPt4;
	el.Points[3] = nPt3;

	ElementArray.push_back(el);
	return S3DRC_OK;
}

