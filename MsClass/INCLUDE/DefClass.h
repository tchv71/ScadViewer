#ifndef DEFINE_CLASS_FLAG_H
#define DEFINE_CLASS_FLAG_H
#pragma pack(push, 1)

#define BITSPERBYTE  8 
#undef  EXPORT
#if defined(__MSCLASS_EXPORTS) 
#define EXPORT  __declspec(dllexport) 
#else
#define EXPORT  __declspec(dllimport) 
#endif
#define MAXDIR   _MAX_DIR    
#define MAXDRIVE _MAX_DRIVE 
#define MAXEXT   _MAX_EXT   
#define MAXPATH  _MAX_PATH 
#define MAXFILE  _MAX_PATH 
#define M_PI     3.1415926535897932384626433832795 
typedef char  *    HPSTR;          /* a huge version of LPSTR */
#define fnmerge  _makepath
#define fnsplit  _splitpath
#pragma pack(pop)

#endif
