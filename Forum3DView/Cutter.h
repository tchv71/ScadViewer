// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV

// All Rights Reserved

// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#ifndef CutterH
#define CutterH

//---------------------------------------------------------------------------
#include "ViewGeometry.h"
#include "Rotate.h"



class	CCutter
{
private:
	SCutRecord		*CutChain;
	void  PerformCut(SCutRecord *r);
	CViewGeometry	**FGeomAddr;
	void  ClearCut(void) const;
public:
	void  FreeCutChain(void);
	void  DoCut
					(
						ECutType	CutType,
						CRotator	*Rot1,
						FLOAT_TYPE		x1,
						FLOAT_TYPE		y1,
						FLOAT_TYPE		x2,
						FLOAT_TYPE		y2,
						NUM_ELEM_TYPE		NumEl =0
					);
	bool  Undo(bool& bNeedZoomAll);
	bool  CanUndo(void) const
	{
		return CutChain != nullptr;
	}
	void  RedoAll(void);
	void  CancelCut(void);
	CCutter(CViewGeometry **GeomAddr = nullptr);
	void SetGeomAddr(CViewGeometry **ppGeometry)
	{
		FGeomAddr = ppGeometry;
	}
	~CCutter(void);
};
#endif
