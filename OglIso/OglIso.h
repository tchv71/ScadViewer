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

#ifdef SCAD21 
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
};
#endif

struct SOglIsoParam
{
	SOglIsoParam() 
	{
		memset(this, 0, sizeof(SOglIsoParam));
	};
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

OGLISO_API  HWND __stdcall OGL_3DIso(RESULT *Res, // ��������� �� ����� �����������
									 int NPr,     // ����� ������ �����
									 struct DefMapInfo *Scale, // ��������� �� �������� ����� 
									 enum eTypeData TypeData, // ��� ������������ ����������
									 int TypeFactor,     // ��� ������������ ���������� (������� �� ����)
									 struct TypeInformationOnSchema *TypeInfo, // ��� ���������� ������������ �� �����
									 HWND hWndParent    // ������������ ����
									 );



#endif
