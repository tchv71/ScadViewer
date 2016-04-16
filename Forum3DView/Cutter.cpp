//---------------------------------------------------------------------------
//#include <vcl.h>
#include "stdafx.h"
#pragma hdrstop
#include "Cutter.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)
//======================== CCutter ============================================

// Реализация отсечения на модели
 CCutter::CCutter(CViewGeometry **GeomAddr)
{
	FGeomAddr = GeomAddr;
	CutChain = nullptr;
}

void  CCutter::FreeCutChain(void)
{
	for(SCutRecord * r = CutChain; r != nullptr;)
	{
		SCutRecord	*r1 = r;
		r = r->Next;
		delete r1;
	}

	CutChain = nullptr;
}

CCutter::~CCutter(void)
{
	FreeCutChain();
}

void  CCutter::DoCut
(
	ECutType	CutType,
	CRotator	*Rot1,
	FLOAT_TYPE		x1,
	FLOAT_TYPE		y1,
	FLOAT_TYPE		x2,
	FLOAT_TYPE		y2,
	NUM_ELEM_TYPE		NumEl
)
{
	SCutRecord	*r_new = new SCutRecord;
	r_new->Rot = *Rot1;
	r_new->Type = CutType;
	r_new->x1 = x1;
	r_new->y1 = y1;
	r_new->x2 = x2;
	r_new->y2 = y2;
	r_new->NumEl = NumEl;
	r_new->Next = nullptr;
	if(CutChain == nullptr)
		CutChain = r_new;
	else
	{
		SCutRecord	*r = CutChain;
		while(r->Next)
			r = r->Next;
		r->Next = r_new;
	}

	PerformCut(r_new);
	(*FGeomAddr)->GetNodeCashe()->Recreate();
}

void  CCutter::PerformCut(SCutRecord *r)
{
	CViewGeometry	*Geometry = *FGeomAddr;
	if (Geometry)
		Geometry->PerformCut(*this,r);
}

void  CCutter::ClearCut(void) const
{
	CViewGeometry	*Geometry = *FGeomAddr;
	if (Geometry)
		Geometry->ClearCut();
}

void  CCutter::CancelCut(void)
{
	ClearCut();
	FreeCutChain();
	(*FGeomAddr)->GetNodeCashe()->Recreate();
}

bool  CCutter::Undo(bool& bNeedZoomAll)
{
	bNeedZoomAll = true;
	SCutRecord	*r = CutChain;
	if(r == nullptr)
		return false;
	ClearCut();
	if(r->Next == nullptr)
	{
		CutChain = nullptr;
	}

	SCutRecord	*r1 = nullptr;
	while(r->Next)
	{
		PerformCut(r);
		r1 = r;
		r = r->Next;
	}
	if (r1)
		r1->Next = nullptr;
	switch (r->Type)
	{
	case HIDE_ELEMENT:
	case HIDE_ELEMENT_PLATE:
		bNeedZoomAll = false;
		break;
	case CUT: break;
	case INV_CUT: break;
	case SHOW_ELEMENT_PLATE: break;
	default: break;
	}
	delete r;
	(*FGeomAddr)->GetNodeCashe()->Recreate();
	return CutChain != nullptr;
}

void  CCutter::RedoAll(void)
{
	SCutRecord	*r = CutChain;
	if(r == nullptr)
		return;
	ClearCut();
	while(r)
	{
		PerformCut(r);
		r = r->Next;
	}
	(*FGeomAddr)->GetNodeCashe()->Recreate();
}
