// Renderer.h: interface for the CRenderer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RENDERER_H__8E378466_D847_4B2B_8A32_3CFF9857A5B1__INCLUDED_)
#define AFX_RENDERER_H__8E378466_D847_4B2B_8A32_3CFF9857A5B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef UNICODE
#define FONT_LIST_SIZE 256
#else
#define FONT_LIST_SIZE 256
#endif

#include "DetViewOpts.h"
#include "SettingManager.h"
#include "SvTypes.h"

//#include "ViewLib.h"
class CViewGeometry;
enum ESvFont
{
	SVF_AXES=0,
	SVF_VALUES,
	SVF_SIZE	// The number of SV fonts
};


#define UpdateByte(bLoad,strKey,pValue, nDefault)\
{ int x= *pValue; UpdateInt(bLoad, strKey, &x, nDefault); *pValue = BYTE(x); }

class SLogFont : public LOGFONT, public CSettingManager
{
public:
	SLogFont() 
	{
		lfHeight = -15;
		lfWidth = 0;
		lfEscapement = 0;
		lfOrientation = 0;
		lfWeight = FW_BOLD;
		lfUnderline = FALSE;
		lfStrikeOut = FALSE;
		lfCharSet = RUSSIAN_CHARSET;
		lfOutPrecision = OUT_TT_PRECIS;
		lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lfQuality = ANTIALIASED_QUALITY;
		lfPitchAndFamily = FF_DONTCARE|DEFAULT_PITCH;
		_tcscpy_s(lfFaceName, _T("Arial"));
		/*
		LOGFONT defFont1 =
		{
		-15,						//LONG      lfHeight;
		0,							//LONG      lfWidth;
		0,							//LONG      lfEscapement;
		0,							//LONG      lfOrientation;
		FW_BOLD,					//LONG      lfWeight;
		FALSE,						//BYTE      lfItalic;
		FALSE,						//BYTE      lfUnderline;
		FALSE,						//BYTE      lfStrikeOut;
		RUSSIAN_CHARSET,			//BYTE      lfCharSet;
		OUT_TT_PRECIS,				//BYTE      lfOutPrecision;
		CLIP_DEFAULT_PRECIS,		//BYTE      lfClipPrecision;
		ANTIALIASED_QUALITY,		//BYTE      lfQuality;
		FF_DONTCARE|DEFAULT_PITCH,	//BYTE      lfPitchAndFamily;
		_T("Arial")					//WCHAR     lfFaceName[LF_FACESIZE];
		};
		*/
		//memcpy((LOGFONT*)this, &defFont1, sizeof(LOGFONT));
	}
	BOOL UpdateSettings(bool bLoad, CString strSubkey)
	{
		SetKey(strSubkey);
		UpdateInt (bLoad, _T("lfHeight"),		reinterpret_cast<INT*>(&lfHeight),		lfHeight);
		UpdateInt (bLoad, _T("lfWidth"),		reinterpret_cast<INT*>(&lfWidth),			0);
		UpdateInt (bLoad, _T("lfEscapement"),	reinterpret_cast<INT*>(&lfEscapement),	0);
		UpdateInt (bLoad, _T("lfOrientation"),	reinterpret_cast<INT*>(&lfOrientation),	0);
		UpdateInt (bLoad, _T("lfWeight"),		reinterpret_cast<INT*>(&lfWeight),		lfWeight);
		UpdateByte(bLoad, _T("lfItalic"),		&lfItalic,				FALSE); 
		UpdateByte(bLoad, _T("lfUnderline"),	&lfUnderline,			FALSE);
		UpdateByte(bLoad, _T("lfStrikeOut"),	&lfStrikeOut,			FALSE);
		CString str(lfFaceName);
		UpdateString(bLoad, _T("lfFaceName"),	&str,					_T("Arial"));
		_tcscpy_s(lfFaceName, str);
		return TRUE;
	}
};


class CDrawOptions : public CSettingManager
{
public:
	EDrawMode	Mode;
	bool	bNodes;
	bool	bBounds;
	bool	bAxes;
	bool	bElements;
	bool	bBars;
	bool	bSolids;

	bool	bElVertical;
	bool	bElHorizontal;
	bool	bElOther;
    bool    bBarHorizontal;
	bool	bBarVertical;
	bool	bBarOther;
	bool	bSortPlanes;
	
	bool	bColumns;
	bool	bBeams;
	bool	bWalls;
	bool	bRoofs;
	bool	bSlabs;

	bool	bLighting;

	FLOAT_TYPE	fDepth;
	double  dblDefScale;
	SLogFont arrLogFonts[SVF_SIZE];
	CDrawOptions()
	{
		bNodes = true;			
		bBounds = true;
		bAxes = false;
		bElements = true;		
		bBars = true;			
		bSolids = true;			
		bElVertical = true;		
		bElHorizontal = true;	
		bElOther = true;		
		bSortPlanes = true;		
		bBarHorizontal = true;	
		bBarVertical = true; 
		bBarOther= true;

		bColumns = true;
		bBeams = true;
		bWalls = true;
		bRoofs = true;
		bSlabs = true;
		Mode = M_FILL_AND_LINES;
		fDepth = 1.0f;
		dblDefScale = 1;
		ZeroMemory(arrLogFonts, sizeof(arrLogFonts));
		arrLogFonts[1].lfHeight *=7;
		arrLogFonts[1].lfHeight /=10;
		arrLogFonts[0].lfWeight = FW_BOLD;
		arrLogFonts[0].lfCharSet = arrLogFonts[1].lfCharSet = RUSSIAN_CHARSET;


		bLighting = true;
	}
	BOOL UpdateSettings(bool bLoad, CString strSubkey)
	{
		SetKey(strSubkey);
		UpdateInt(bLoad, _T("Mode"), reinterpret_cast<int*>(&Mode), M_FILL_AND_LINES);
		UpdateBool(bLoad, _T("ShowNodes"),		&bNodes,	true);
		UpdateBool(bLoad, _T("ShowConstraints"),&bBounds,	true);
		UpdateBool(bLoad, _T("ShowAxes"),		&bAxes,	false);
		UpdateBool(bLoad, _T("ShowBars"),		&bBars,	true);
		UpdateBool(bLoad, _T("ShowElements"),	&bElements, true);
		UpdateBool(bLoad, _T("ShowSolids"),		&bSolids,	true);
		UpdateBool(bLoad, _T("ShowElVertical"),	&bElVertical,true);
		UpdateBool(bLoad, _T("ShowElHorizontal"),&bElHorizontal,true);
		UpdateBool(bLoad, _T("ShowElOther"),	&bElOther, true);
		UpdateBool(bLoad, _T("ShowBarVertical"),&bBarVertical,true);
		UpdateBool(bLoad, _T("ShowBarHorizontal"),&bBarHorizontal,true);
		UpdateBool(bLoad, _T("ShowBarOther"),	&bBarOther, true);

		UpdateBool(bLoad, _T("ShowColumns"),	&bColumns,	true);
		UpdateBool(bLoad, _T("ShowBeams"),		&bBeams,	true);
		UpdateBool(bLoad, _T("ShowWalls"),		&bWalls,	true);
		UpdateBool(bLoad, _T("ShowRoofs"),		&bRoofs,	true);
		UpdateBool(bLoad, _T("ShowSlabs"),		&bSlabs,	true);
		UpdateDouble(bLoad, _T("DefScale"),		&dblDefScale,			1.0);

		arrLogFonts[0].UpdateSettings(bLoad, strSubkey+_T("\\Font0"));
		arrLogFonts[1].UpdateSettings(bLoad, strSubkey+_T("\\Font1"));

		UpdateBool(bLoad, _T("Lighting"),	&bLighting, true);

		return TRUE;
	}
	
};



class CDC;
struct CPrintInfo;
class CView;



class IFemRenderer
{
public:
	virtual ~IFemRenderer()
	{
	}

	virtual HRESULT BindWindow(HWND hBindWnd, bool bUseSoftware, const SLogFont arrLogFonts[]) = 0;
	virtual HRESULT ReleaseWindow(void) = 0;
	virtual HRESULT Render(CViewGeometry *pGeometry, SViewOptions *pViewOptions, CDrawOptions *pDrawOptions) = 0;
	virtual CSize GetFontExtent(ESvFont fontNo, LPCTSTR  pszText, TEXTMETRIC* ptm)=0;
public:
	UINT	m_fontBases[SVF_SIZE];
	FLOAT_TYPE m_fontSizes[SVF_SIZE];
	GLYPHMETRICSFLOAT m_gmfs[SVF_SIZE][FONT_LIST_SIZE];	// Storage For Information About Our Outline Font Characters

//	virtual void	OnBeforePrint(CDC* pDC, CPrintInfo* pInfo, CView* pView, CString strFileName, FLOAT_TYPE &fScale) = 0;
//	virtual void	OnAfterPrint(CDC* pDC) = 0;
//	virtual void	SetViewportSize(int x, int y) = 0;
};


#endif // !defined(AFX_RENDERER_H__8E378466_D847_4B2B_8A32_3CFF9857A5B1__INCLUDED_)
