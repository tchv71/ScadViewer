#ifndef	_SCADAPIX_hxx_FLAG_
#define	_SCADAPIX_hxx_FLAG_

#pragma pack(push,1)

#ifdef SCADAPIX_EXPORTS
#define ApiDLL __declspec(dllexport)
#else
#define ApiDLL __declspec(dllimport)
#endif

#define SCAD_WINAPI   ApiDLL  WINAPI

#include "ScadStructHelpAPI.hxx"

typedef	enum 
#ifndef _lint
	:UINT16
#endif
{
	APICode_OK		        = 0,
	APICode_InvalidHandle	= 1,
	APICode_InternalError	= 2,
	APICode_FatalError	    = 3,
	APICode_IndexError	    = 4,
	APICode_ReadError       = 5,
	APICode_WriteError      = 6,
	APICode_NoSchema        = 7,
	APICode_NoResult        = 8,
	APICode_NoResultCalc    = 9,
    }  APICode;

#ifdef __cplusplus
extern "C" {
#endif

	struct	APIHandle_tag;
	typedef	APIHandle_tag      * ScadAPI;

APICode SCAD_WINAPI  ApiCreate	( ScadAPI * lpAPI );
APICode SCAD_WINAPI  ApiRelease	( ScadAPI * lpAPI );

APICode SCAD_WINAPI  ApiGetLastError ( const ScadAPI lpAPI );
UINT    SCAD_WINAPI  ApiGetQuantityPhrase ( const ScadAPI lpAPI );
LPCSTR  SCAD_WINAPI  ApiGetPhrase (  const ScadAPI lpAPI, UINT Num );
APICode SCAD_WINAPI  ApiClearPhrase (  ScadAPI lpAPI );
APICode SCAD_WINAPI  APIPhrase( ScadAPI	handle, APICode Out  ); 	

void    SCAD_WINAPI  ApiMsg( LPCSTR Text );

#ifdef __cplusplus
};
#endif

#include "ScadAPISchema.hxx"
#include "ScadAPIResult.hxx"

#pragma pack(pop)

#endif	//~_SCADAPIX_hxx_FLAG_

