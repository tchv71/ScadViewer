// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV

// All Rights Reserved

// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#ifndef DetViewOptsH
#define DetViewOptsH

#include "SettingManager.h"
#include "ViewLib.h"

enum EDrawMode { M_LINES, M_FILL, M_FILL_AND_LINES, M_FILL_AND_LINES_TRANSP };

namespace Graphics
{
		typedef COLORREF TColor;
};


// Опции панели детального просмотра
// Detail view options
struct SViewOptions 
{ 
	int					LineWidth;
	Graphics::TColor	BarColor;
	Graphics::TColor	EdgeColor;
	Graphics::TColor	BackgroundColor;
	Graphics::TColor	NodeColor;
    Graphics::TColor    PlateColor;
    Graphics::TColor    SolidColor;
    Graphics::TColor    DupeColor;
	Graphics::TColor	BoundsColor[6];
	Graphics::TColor	AxesColor;
	int					NodeSize;
	bool				OGL10;
	bool				bLineSmooth;
	bool				SoftOGL;
	bool				bRemoveDupPlanes;
	bool				bDrawOptimize;
    int                 nPrintResolution;
    bool                bPerspective;
	bool				bShowUsedNodes;

	Graphics::TColor	WallColor;
	Graphics::TColor	SlabColor;
	Graphics::TColor	ColumnColor;
	Graphics::TColor	BeamColor;
    Graphics::TColor    RoofColor;
};

class CPersistViewOptions : public SViewOptions, public CSettingManager
{
public:
	CPersistViewOptions() {};
    CPersistViewOptions(SViewOptions opt) : SViewOptions(opt) {};
	BOOL UpdateSettings(bool bLoad, CString strSubkey)
	{
		SetKey(strSubkey);
		UpdateInt(bLoad, _T("LineWidth"),		 &LineWidth,			1);
		UpdateInt(bLoad, _T("BarColor"),		reinterpret_cast<int*>(&BarColor),		clRed);
		UpdateInt(bLoad, _T("EdgeColor"),		reinterpret_cast<int*>(&EdgeColor),		clNavy);
		UpdateInt(bLoad, _T("BackgroundColor"), reinterpret_cast<int*>(&BackgroundColor), clWhite);
		UpdateInt(bLoad, _T("NodeColor"),		reinterpret_cast<int*>(&NodeColor),		clGreen);
		UpdateInt(bLoad, _T("PlateColor"),		reinterpret_cast<int*>(&PlateColor),		clSilver);
		UpdateInt(bLoad, _T("SolidColor"),		reinterpret_cast<int*>(&SolidColor),		clSilver);
		UpdateInt(bLoad, _T("DupeColor"),		reinterpret_cast<int*>(&DupeColor),		clYellow);
		UpdateInt(bLoad, _T("BoundsColorX"),	reinterpret_cast<int*>(&BoundsColor[0]),	clRed);
		UpdateInt(bLoad, _T("BoundsColorY"),	reinterpret_cast<int*>(&BoundsColor[1]),	clLime);
		UpdateInt(bLoad, _T("BoundsColorZ"),	reinterpret_cast<int*>(&BoundsColor[2]),	clBlue);
		UpdateInt(bLoad, _T("BoundsColorUX"),	reinterpret_cast<int*>(&BoundsColor[3]),	clPurple);
		UpdateInt(bLoad, _T("BoundsColorUY"),	reinterpret_cast<int*>(&BoundsColor[4]),	clYellow);
		UpdateInt(bLoad, _T("BoundsColorUZ"),	reinterpret_cast<int*>(&BoundsColor[5]),	clFuchsia);
		UpdateInt(bLoad, _T("AxesColor"),		reinterpret_cast<int*>(&AxesColor),		clGreen);

		UpdateInt(bLoad, _T("NodeSize"),		&NodeSize,				4);
		//UpdateInt(bLoad, _T("Mode"),			(int *)&Mode,			M_FILL_AND_LINES);
		
		UpdateBool(bLoad,_T("OGL10"),			&OGL10,					false);
		UpdateBool(bLoad,_T("LineSmooth"),		&bLineSmooth,			false);
		UpdateBool(bLoad,_T("SoftOGL"),			&SoftOGL,				false);
		UpdateBool(bLoad,_T("RemoveDupPlanes"),	&bRemoveDupPlanes,		false);
		UpdateBool(bLoad,_T("DrawOptimize"),	&bDrawOptimize,			false);
		UpdateBool(bLoad,_T("ShowUsedNodes"),	&bShowUsedNodes,		true);

		UpdateInt(bLoad, _T("PrintResolution"),	&nPrintResolution,		600);
		UpdateBool(bLoad,_T("Perspective"),		&bPerspective,			false);
		
		UpdateInt(bLoad, _T("WallColor"),		reinterpret_cast<int*>(&WallColor),		clSilver);
		UpdateInt(bLoad, _T("SlabColor"),		reinterpret_cast<int*>(&SlabColor),		clSilver);
		UpdateInt(bLoad, _T("ColumnColor"),		reinterpret_cast<int*>(&ColumnColor),		clRed);
		UpdateInt(bLoad, _T("BeamColor"),		reinterpret_cast<int*>(&BeamColor),		clRed);
		UpdateInt(bLoad, _T("RoofColor"),		reinterpret_cast<int*>(&RoofColor),		clSilver);
		return TRUE;
	}
};

typedef std::vector<CString> SCStringVector;
enum SCDefProjType
{
	DPT_Top,
	DPT_Bottom,
	DPT_Front,
	DPT_Back,
	DPT_Left,
	DPT_Right,
	DPT_SouthEast,
	DPT_SouthWest,
	DPT_NorthWest,
	DPT_NortpEast,
	DPT_Dimetry,
	DPT_Size
};

struct	CFLCProperties
{
	SCStringVector	m_vsExt;
	int				m_nItemCX;
	int				m_nItemCY;
	SCDefProjType	m_DefProj;

	int	operator==( const CFLCProperties& prop ) const;
	CFLCProperties operator=( const CFLCProperties& prop );
};



class SViewerOptions: public CSettingManager
{
public:
	CFLCProperties m_ViewProp;
	int nLangID;
	// Опции вывода в RTF
	bool bReportTypeWord97;
	bool bViewReport;
	int	nPaperSize;
	CString strRtfHeaderPath;
	SViewerOptions(): nPaperSize(0)
	{
		nLangID = 1049;
		bReportTypeWord97 = true;
		bViewReport = true;

	}
	BOOL UpdateSettings(bool bLoad, CString strSubkey)
	{
		SetKey(strSubkey);
		UpdateInt(bLoad, _T("ThumbWidth"),	&m_ViewProp.m_nItemCX,	100);
		UpdateInt(bLoad, _T("ThumbHeight"), &m_ViewProp.m_nItemCY,  72);
		UpdateInt(bLoad, _T("DefaultView"), reinterpret_cast<int *>(&m_ViewProp.m_DefProj), int(DPT_Dimetry));
		UpdateStringVector(bLoad, _T("ExtList"),&m_ViewProp.m_vsExt, _T("*.spr,*.opr"));
		UpdateInt(bLoad, _T("LangID"),		&nLangID,		1049);
		UpdateBool(bLoad,  _T("RTWord97"),   &bReportTypeWord97, true);
		UpdateBool(bLoad, _T("ViewReport"),	&bViewReport,	true);
		return TRUE;
	}

};

//---------------------------------------------------------------------------
#endif
