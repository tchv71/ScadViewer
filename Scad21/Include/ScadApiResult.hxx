#ifndef ScadResult_C_FLAG_H
#define ScadResult_C_FLAG_H

#pragma pack(push,1)

APICode    SCAD_WINAPI  ApiInitResult( ScadAPI lpAPI, const UnitsAPI *Un, LPCSTR NameWorkCatalog );

BYTE       SCAD_WINAPI  ApiTypeProcess ( ScadAPI lpAPI );
BOOL       SCAD_WINAPI  ApiYesModal ( ScadAPI lpAPI );
BOOL       SCAD_WINAPI  ApiYesDisplace ( ScadAPI lpAPI );
BOOL       SCAD_WINAPI  ApiYesEffors ( ScadAPI lpAPI );
BOOL       SCAD_WINAPI  ApiYesCombCalcul ( ScadAPI lpAPI );
BOOL       SCAD_WINAPI  ApiYesRSU ( ScadAPI lpAPI );
BOOL       SCAD_WINAPI  ApiYesRSD ( ScadAPI lpAPI );

UINT       SCAD_WINAPI  ApiGetResultQuantityLoad ( ScadAPI lpAPI );
UINT       SCAD_WINAPI  ApiGetResultQuantityFixedStep ( ScadAPI lpAPI );
UINT       SCAD_WINAPI  ApiGetResultQuantityLoadDynamic ( ScadAPI lpAPI );
UINT       SCAD_WINAPI  ApiGetResultQuantityComb ( ScadAPI lpAPI );

UINT       SCAD_WINAPI  ApiGetQuantityLoadStr ( ScadAPI lpAPI, API_RESULT_DATA Type, UINT NumData );
APICode    SCAD_WINAPI  ApiGetResultData ( ScadAPI lpAPI, API_RESULT_DATA Type, UINT NumData, UINT NumStr, ApiLoadingData * APD );

lpDouble   SCAD_WINAPI  ApiGetDisplace( ScadAPI lpAPI, UINT NumLoad, UINT NumStr, UINT NumNode );
lpDouble   SCAD_WINAPI  ApiGetCombDisplace( ScadAPI lpAPI, UINT NumComb, UINT NumNode );

lpDouble   SCAD_WINAPI  ApiGetMassa( ScadAPI lpAPI, UINT NumLoad, UINT NumNode );
lpDouble   SCAD_WINAPI  ApiGetMode( ScadAPI lpAPI, UINT NumLoad, UINT NumMode, UINT NumNode );

lpDouble   SCAD_WINAPI  ApiGetReak( ScadAPI lpAPI, UINT NumLoad, UINT NumStr, UINT NumNode );
lpDouble   SCAD_WINAPI  ApiGetCombReak( ScadAPI lpAPI, UINT NumComb, UINT NumNode );

lpDouble   SCAD_WINAPI  ApiGetReakFragment( ScadAPI lpAPI, UINT NumLoad, UINT NumStr, UINT NumNode );
lpDouble   SCAD_WINAPI  ApiGetCombReakFragment( ScadAPI lpAPI, UINT NumComb, UINT NumNode );

APICode    SCAD_WINAPI  ApiGetEffors( ScadAPI lpAPI, UINT NumElem, ApiElemEffors ** Effors, BYTE TypeRead );
APICode    SCAD_WINAPI  ApiGetRsu( ScadAPI lpAPI, UINT NumElem, ApiElemRsu * rsu );
APICode    SCAD_WINAPI  ApiGetRsd( ScadAPI lpAPI, UINT NumElem, ApiElemRsu * rsu );

#pragma pack(pop)

#endif
