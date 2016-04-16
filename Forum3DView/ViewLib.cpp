// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#include "stdafx.h" //<vcl.h>
//#include "ViewGeometry.h"
#pragma hdrstop

#include "ViewLib.h"

//---------------------------------------------------------------------------

//#pragma package(smart_init)


void SParallelView::GeometryZoomAll(CRect *clr, int Border, S3DBox *Box)
{
	int		clw = clr->right - clr->left - Border, clh = clr->bottom - clr->top - Border;

	FLOAT_TYPE	WinX = (Box->x_max - Box->x_min), WinY = (Box->y_max - Box->y_min);

	if((WinX == 0))
		WinX = 1;
	if((WinY == 0))
		WinY = 1;

	FLOAT_TYPE	SclX = clw / FLOAT_TYPE(WinX), SclY = clh / FLOAT_TYPE(WinY);
	FLOAT_TYPE	SclF = (SclX < SclY) ? SclX : SclY;
	ScrScale = SclF;

	Xorg = (Box->x_max + Box->x_min) / 2;
	Yorg = (Box->y_max + Box->y_min) / 2;
	Zorg = (Box->z_max + Box->z_min) / 2;
}
