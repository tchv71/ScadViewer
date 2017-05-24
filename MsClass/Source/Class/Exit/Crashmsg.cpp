#include <stdafx.h>
#include <classwin.h>
//#include <stdio.h>
//#include <stdarg.h>

EXPORT LPCSTR  GetPath(LPCSTR Name);

EXPORT void CrashMessage()
{
    LPCSTR lpMsgBuf;
    DWORD Num = GetLastError();

	if ( Num == 0 ) return;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,  Num,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
       (LPTSTR) &lpMsgBuf,
       0, NULL );
    MessageBox( NULL, lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );
    LocalFree( (void*)lpMsgBuf );
}

EXPORT  void CrashMessage( int NumError ... )
{
    HINSTANCE hString;
    char Text[256], OutText[256];
	 va_list arg_ptr;

//    CrashMessage();

    hString = LoadLibrary(GetPath("classerr.dll"));
    if ( hString == NULL ) throw;

    if ( LoadString(hString,NumError,Text,sizeof(Text)) == 0 ) goto _10;

    va_start(arg_ptr,NumError);
	 vsprintf(OutText,Text,arg_ptr);
	 va_end(arg_ptr);

    Printf(OutText);

_10:FreeLibrary(hString);
    ExitProcess(1);
}