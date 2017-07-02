// OglIso.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "OglIso.h"
#include "schema.hpp"
#include "Result.hpp"
#include "3DIso.hpp"
#include "scad.h"
#include "Grand.h"
#if _MSC_VER >= 1300
#include "atlstr.h"
#else
class CString;
#endif
#include "../Forum3dView/Forum3DView.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


OGLISO_API HWND __stdcall  OGL_3DIso(RESULT *Res, // Указатель на класс результатов
									 int NPr,     // Номер правой части
									 struct DefMapInfo *Scale, // Указатель на цветовую шкалу 
									 eTypeData nTypeData, // Тип отображаемой информации
									 int TypeFactor,     // Вид отображаемой информации (зависит от типа)
									 struct TypeInformationOnSchema *TypeInfo, // Тип информации отображаемой на схеме
									 HWND hWndParent    // Родительское окно
									 )
{

	SOglIsoParam param;
	param.Res = Res;
	param.NPr = NPr;
	param.pDMI = Scale;
	//param.nTypeData = Iso_Nap; //eTypeData(nTypeData); NB!!! Temp
	param.nTypeData = eTypeData(nTypeData); //NB!!! Temp
	param.nTypeFactor = TypeFactor;
	param.pTypeInfo = TypeInfo;
	param.hWndParent = hWndParent;
	param.bDrawIsoLines = true;
	OglIso3D(&param);
	return param.hWndOgl;
}

