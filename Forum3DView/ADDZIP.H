// addzip.h
//
// C/C++ header file for addZIP compression libraries
//
// Copyright © 1995-1999 Stephen Darlington. All rights reserved.

#ifndef _ADDZIP_H
#define _ADDZIP_H

#ifndef DLLENTRY
	#if defined(__BORLANDC__) && (__BORLANDC__ < 0x500)
		#defined DLLENTRY extern
	#else
	#if defined(__WIN32__) || defined(_WIN32)
		#define DLLENTRY __declspec(dllimport)
	#else
		#define DLLENTRY extern
	#endif
   #endif
#endif

#undef WINAPI
#define WINAPI __stdcall
// Redefine the function import/export identifiers for use in static import library
#ifdef _STATIC_LIB
#	undef DLLENTRY
#	define DLLENTRY __declspec(dllexport)
#	undef WINAPI
#	define WINAPI
#endif

#ifndef _BYTE_T_DEFINED
#	define _BYTE_T_DEFINED
	typedef unsigned char BYTE_T;
#endif

#ifndef _BOOLEAN_T_DEFINED
#	define _BOOLEAN_T_DEFINED
	typedef char BOOLEAN_T;
#endif

#ifndef _UINT16_T_DEFINED
#	define _UINT16_T_DEFINED
	typedef unsigned short UINT16_T;
#endif

#ifndef _UINT32_T_DEFINED
#	define _UINT32_T_DEFINED
	typedef unsigned long UINT32_T;
#endif

#ifndef _CHAR_T_DEFINED
#	define _CHAR_T_DEFINED
	typedef char CHAR_T;
#endif

#ifndef _INT16_T_DEFINED
#	define _INT16_T_DEFINED
	typedef short INT16_T;
#endif

#ifndef _INT32_T_DEFINED
#	define _INT32_T_DEFINED
	typedef long INT32_T;
#endif

#ifndef _LPARAM_T_DEFINED
#	define _LPARAM_T_DEFINED
	typedef unsigned long LPARAM_T;
#endif

#ifndef _LPSTR_T_DEFINED
#	define _LPSTR_T_DEFINED
	typedef char FAR * LPSTR_T;
	typedef const char FAR * LPCSTR_T;
#endif
	
#ifndef _CALLBACKS_T_DEFINED
#	define _CALLBACKS_T_DEFINED
	typedef int (CALLBACK *CALLBACKFN)(UINT16_T, UINT16_T, LPSTR_T);
	typedef int (CALLBACK *CALLBACKFNEX)(UINT16_T, UINT16_T, LPSTR_T, LPARAM_T);
#endif

#ifdef __cplusplus
extern "C"
{
#endif

DLLENTRY INT32_T WINAPI addZIP(void);
DLLENTRY INT16_T WINAPI addZIP_Abort(INT16_T bAbort);
DLLENTRY INT16_T WINAPI addZIP_ArchiveName(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_BuildSFX(INT16_T bBuildSFX);
DLLENTRY INT16_T WINAPI addZIP_ClearAttributes(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_Comment(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_Delete(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_DeleteComment(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_DisplayComment(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_Encrypt(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_Exclude(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_ExcludeListFile(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_Freshen(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_FromMemory(LPSTR_T pszBuffer, UINT32_T ulBufferLen); // added v0.69d
DLLENTRY INT16_T WINAPI addZIP_GetLastError(void);
DLLENTRY INT16_T WINAPI addZIP_GetLastWarning(void);
DLLENTRY void    WINAPI addZIP_GetVersion(UINT16_T *, UINT16_T *);
DLLENTRY INT16_T WINAPI addZIP_Include(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_IncludeFilesNewer(LPCSTR cDate);
DLLENTRY INT16_T WINAPI addZIP_IncludeFilesOlder(LPCSTR cDate);
DLLENTRY INT16_T WINAPI addZIP_IncludeArchive(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_IncludeDirectoryEntries(INT16_T flag);
DLLENTRY INT16_T WINAPI addZIP_IncludeEmptyDirectoryEntries(INT16_T flag); // added v0.69d
DLLENTRY INT16_T WINAPI addZIP_IncludeHidden(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_IncludeReadOnly(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_IncludeSystem(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_IncludeListFile(LPCSTR);
DLLENTRY void    WINAPI addZIP_Initialise(void);
DLLENTRY INT32_T WINAPI addZIP_InMemory(LPSTR_T lpszInBuffer, UINT32_T u4_InLength, LPSTR_T lpszOutBuffer, UINT32_T u4_OutLength);
DLLENTRY INT16_T WINAPI addZIP_InstallCallback(CALLBACKFN cbFunction);
DLLENTRY INT16_T WINAPI addZIP_InstallCallbackEx(CALLBACKFNEX cbFunction, LPARAM_T lParam); // added v0.69d
DLLENTRY INT16_T WINAPI addZIP_KeepCompatible(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_Move(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_Overwrite(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_Register(LPCSTR, UINT32_T);
DLLENTRY INT16_T WINAPI addZIP_Recurse(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_SaveAttributes(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_SaveConfiguration(LPCSTR szFile);
DLLENTRY INT16_T WINAPI addZIP_SaveRelativeTo(LPCSTR cPath);
DLLENTRY INT16_T WINAPI addZIP_SaveStructure(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_SetArchiveDate(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_SetCompressionLevel(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_SetParentWindowHandle(HWND);
DLLENTRY INT16_T WINAPI addZIP_SetTempDrive(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_SFXAutoExecute(LPSTR szCommand, LPSTR szOptions);
DLLENTRY INT16_T WINAPI addZIP_SFXAutoPasswordPrompt(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_SFXExtractTo(LPSTR szPath); // added v0.69e
DLLENTRY INT16_T WINAPI addZIP_SFXRestoreStructure(INT16_T iFlag);
DLLENTRY INT16_T WINAPI addZIP_SetWindowHandle(HWND);
DLLENTRY INT16_T WINAPI addZIP_Span(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_SpanCreateImages(INT16_T flag);
DLLENTRY INT16_T WINAPI addZIP_SpanSizes(UINT32_T ulFirst, UINT32_T ulOthers);
DLLENTRY INT16_T WINAPI addZIP_Store(LPCSTR);
DLLENTRY INT16_T WINAPI addZIP_ToMemory(LPSTR pszBuffer, UINT32_T ulBufferLen); // added v0.69d
DLLENTRY INT16_T WINAPI addZIP_Update(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_UseLFN(INT16_T);
DLLENTRY INT16_T WINAPI addZIP_View(INT16_T);

#ifdef __cplusplus
}
#endif

// constants for addZIP_CreateSFX(...)
#define azSFX_NO 0x00
#define azSFX_DOS16 0x01
#define azSFX_DOS32 0x02
#define azSFX_WIN16 0x03
#define azSFX_WIN32 0x04

// constants for addZIP_SetCompressionLevel(...)
#define azCOMPRESSION_NONE    0x00
#define azCOMPRESSION_MINIMUM 0x01
#define azCOMPRESSION_NORMAL  0x02
#define azCOMPRESSION_MAXIMUM 0x03

// constants for addZIP_SaveStructure(...)
#define azSTRUCTURE_NONE     0x00
#define azSTRUCTURE_RELATIVE 0x01
#define azSTRUCTURE_ABSOLUTE 0x02

// constants for addZIP_Overwrite(...)
#define azOVERWRITE_QUERY 0x0a
#define azOVERWRITE_ALL   0x0b
#define azOVERWRITE_NONE  0x0c

// constants for addZIP_SetArchiveDate();
#define DATE_ORIGINAL  0x00
#define DATE_TODAY     0x01
#define DATE_OLDEST    0x02
#define DATE_NEWEST    0x03

// constants for addZIP_IncludeXXX attribute functions
#define azNEVER  0x00  // files must never have this attribute set
#define azYES    0x01  // files may or may not have this attribute set
#define azALWAYS 0xff  // files must always have this attribute set

// constants for addZIP_ClearAttributes(...)
#define azATTR_NONE 0
#define azATTR_READONLY 1
#define azATTR_HIDDEN 2
#define azATTR_SYSTEM 4
#define azATTR_ARCHIVE 32
#define azATTR_ALL 39

// constants used in messages to identify library
#define azLIBRARY_ADDZIP 0

//
#define AM_SEARCHING      0x0a
#define AM_ZIPCOMMENT     0x0b
#define AM_ZIPPING        0x0c
#define AM_ZIPPED         0x0d
#define AM_UNZIPPING      0x0e
#define AM_UNZIPPED       0x0f
#define AM_TESTING        0x10
#define AM_TESTED         0x11
#define AM_DELETING       0x12
#define AM_DELETED        0x13
#define AM_DISKCHANGE     0x14
#define AM_VIEW           0x15
#define AM_ERROR          0x16
#define AM_WARNING        0x17
#define AM_QUERYOVERWRITE 0x18
#define AM_COPYING        0x19
#define AM_COPIED         0x1a
//#define AM_REPAIRING      0x1b
//#define AM_FILECOMMENT    0x1c
//#define AM_PASSWORD       0x1d
#define AM_ABORT          0xff

// Constants for compression method in AM_VIEW
#define azCM_NONE 0              0x00
#define azCM_SHRUNK              0x0a
#define azCM_REDUCED_1           0x14
#define azCM_REDUCED_2           0x1e
#define azCM_REDUCED_3           0x28
#define azCM_REDUCED_4           0x32
#define azCM_IMPLODED            0x3c
#define azCM_TOKENISED           0x46
#define azCM_DEFLATED_NORMAL     0x50
#define azCM_DEFLATED_MAXIMUM    0x51
#define azCM_DEFLATED_FAST       0x52
#define azCM_DEFLATED_SUPERFAST  0x53
#define azCM_UNKNOWN             0xff

//Constants for whether file is encrypted or not in AM_VIEW
#define azFT_NOT_ENCRYPTED 0x00
#define azFT_ENCRYPTED     0x01

//Constants for whether file is text or binary in AM_VIEW
#define azFT_TEXT   0x00
#define azFT_BINARY 0x01

// Constants used in returning from a AM_QUERYOVERWRITE message
#define AQO_YES      0x00
#define AQO_YESTOALL 0x01
#define AQO_NO       0x02
#define AQO_NOTOALL  0x03
#define AQO_RENAME   0x04
#endif
