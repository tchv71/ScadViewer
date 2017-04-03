// Copyright (C) 2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#ifndef ViewLibH
#define ViewLibH
#include "SvTypes.h"

class CRotator;
struct S3DBox
{
	FLOAT_TYPE x_min;
	FLOAT_TYPE y_min;
	FLOAT_TYPE z_min;
	FLOAT_TYPE x_max;
	FLOAT_TYPE y_max;
	FLOAT_TYPE z_max;
};

struct SParallelView
{
	FLOAT_TYPE	Xorg;
	FLOAT_TYPE	Yorg;
	FLOAT_TYPE	Zorg;
	FLOAT_TYPE	ScrScale;
	void	GeometryZoomAll(CRect *clr, int Border, S3DBox *Box);
	SParallelView() : Xorg(0), Yorg(0), Zorg(0), ScrScale(1) {}
};

struct SPerspectiveView : public SParallelView
{
	CRotator	*Rot;
	bool		bPerspective;
	FLOAT_TYPE		TargetDist;
	FLOAT_TYPE		FocusLength;

	FLOAT_TYPE		ViewSizeX;
	FLOAT_TYPE		ViewSizeY;
	SPerspectiveView() : Rot(nullptr), bPerspective(false), TargetDist(0), FocusLength(0), ViewSizeX(0), ViewSizeY(0) {}
};
typedef UINT	TColor;


//-- var, const, procedure ---------------------------------------------------
static const TColor clScrollBar = 0x80000000;
static const TColor clBackground = 0x80000001;
static const TColor clActiveCaption = 0x80000002;
static const TColor clInactiveCaption = 0x80000003;
static const TColor clMenu = 0x80000004;
static const TColor clWindow = 0x80000005;
static const TColor clWindowFrame = 0x80000006;
static const TColor clMenuText = 0x80000007;
static const TColor clWindowText = 0x80000008;
static const TColor clCaptionText = 0x80000009;
static const TColor clActiveBorder = 0x8000000a;
static const TColor clInactiveBorder = 0x8000000b;
static const TColor clAppWorkSpace = 0x8000000c;
static const TColor clHighlight = 0x8000000d;
static const TColor clHighlightText = 0x8000000e;
static const TColor clBtnFace = 0x8000000f;
static const TColor clBtnShadow = 0x80000010;
static const TColor clGrayText = 0x80000011;
static const TColor clBtnText = 0x80000012;
static const TColor clInactiveCaptionText = 0x80000013;
static const TColor clBtnHighlight = 0x80000014;
static const TColor cl3DDkShadow = 0x80000015;
static const TColor cl3DLight = 0x80000016;
static const TColor clInfoText = 0x80000017;
static const TColor clInfoBk = 0x80000018;
static const TColor clBlack = 0x0;
static const TColor clMaroon = 0x80;
static const TColor clGreen = 0x8000;
static const TColor clOlive = 0x8080;
static const TColor clNavy = 0x800000;
static const TColor clPurple = 0x800080;
static const TColor clTeal = 0x808000;
static const TColor clGray = 0x808080;
static const TColor clSilver = 0xc0c0c0;
static const TColor clRed = 0xff;
static const TColor clLime = 0xff00;
static const TColor clYellow = 0xffff;
static const TColor clBlue = 0xff0000;
static const TColor clFuchsia = 0xff00ff;
static const TColor clAqua = 0xffff00;
static const TColor clLtGray = 0xc0c0c0;
static const TColor clDkGray = 0x808080;
static const TColor clWhite = 0xffffff;
static const TColor clNone = 0x1fffffff;
static const TColor clDefault = 0x20000000;


//---------------------------------------------------------------------------

#endif
