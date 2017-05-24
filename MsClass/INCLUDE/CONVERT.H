#ifndef INFORM_CONVERT_H
#define INFORM_CONVERT_H
#pragma pack(push, 1)
EXPORT double CharDouble( LPCSTR s, BYTE & knt );
EXPORT long   CharLong  ( LPCSTR s, BYTE & knt );
EXPORT WORD   CharWord  ( LPCSTR s, BYTE & knt );
EXPORT DWORD  CharDWord ( LPCSTR s, BYTE & knt );

EXPORT void   DoubleChar  ( double Dbl, LPSTR Str, int LenStr);
EXPORT void   DoubleCharP ( double Dbl, LPSTR Str, int LenStr);

EXPORT void   FloatChar   ( float  Flt, LPSTR Str, int LenStr);

EXPORT long   oubleLong(double s,BYTE &i);

#pragma pack(pop)
#endif