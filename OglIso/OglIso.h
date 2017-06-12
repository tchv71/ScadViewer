#ifndef _OGL_ISO_H
#define _OGL_ISO_H
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OGLISO_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OGLISO_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef OGLISO_EXPORTS
#define OGLISO_API __declspec(dllexport)
#else
#define OGLISO_API __declspec(dllimport)
#endif

class RESULT;
enum eTypeData;
struct TypeInformationOnSchema;
struct	APIHandle_tag;
typedef	APIHandle_tag      * ScadAPI;

#pragma pack(push,1)

#if defined(SCAD21) || defined(SCAD11) 
struct DefMapInfo
{
	short Scale_count;
	double Max,Min;
	double Step;
	double binter[64];
	double einter[64];
	double DopArmB[64];
	double DopArmE[64];
	char IsDrw[64];
	COLORREF col[64];
	double Zero;
	int x[64];
	int y[64];
	char Caption[8192];
	BYTE LastOp;    // 1 - IsoLines 0 - IsoArea or Map
	BYTE IsDopArm;
	BYTE IsSetScale;
	DefMapInfo() : Scale_count(14)
	{
		const COLORREF defDmiColors[] =
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
		for (int i = 0; i< Scale_count; i++)
			col[i]=defDmiColors[i];

	}
};
#endif

struct SOglIsoParam
{
	SOglIsoParam() 
	{
		memset(this, 0, sizeof(SOglIsoParam));
		NPr = 0;
		nTypeFactor = 0;
		nTypeData = (eTypeData)1;
		bDrawIsoLines = false;
		bDrawEggs = false;
	};
	CString GetFactorName() const;
	void SetTypeData(eTypeData val);
	RESULT* Res;
#ifdef SCAD21
	ScadAPI hAPI;
#endif
	TCHAR strCurLoad[64];
	int NPr;
	const struct DefMapInfo *pDMI;
	eTypeData nTypeData;
	int nTypeFactor;
	struct TypeInformationOnSchema *pTypeInfo;
	HWND hWndParent;
	HWND hWndOgl;
	bool bDrawIsoLines;
	bool bDrawEggs;
};
#pragma pack(pop)

OGLISO_API  HWND __stdcall OGL_3DIso(RESULT *Res, // Указатель на класс результатов
									 int NPr,     // Номер правой части
									 struct DefMapInfo *Scale, // Указатель на цветовую шкалу 
									 enum eTypeData TypeData, // Тип отображаемой информации
									 int TypeFactor,     // Вид отображаемой информации (зависит от типа)
									 struct TypeInformationOnSchema *TypeInfo, // Тип информации отображаемой на схеме
									 HWND hWndParent    // Родительское окно
									 );



#endif
