#include <stdafx.h>
//				Debug print
#include <stdio.h>
#include <defclass.h>
//#include <stdarg.h>

EXPORT void Printf(LPCSTR __format, ...)
{
	va_list arg_ptr;
	char Buf[512];

	va_start(arg_ptr,__format);
	vsprintf(Buf,__format,arg_ptr);
//        MessageBox(GetActiveWindow(),debug,"",MB_OK|MB_ICONSTOP);
        MessageBox(NULL,Buf,"",MB_OK|MB_ICONSTOP|MB_SYSTEMMODAL);
	va_end(arg_ptr);
}

EXPORT void dPrintf(LPCSTR __format, ...)
{
	va_list arg_ptr;
    if ( __format == NULL ) {  remove("debug.tmp");  return;   }
	va_start(arg_ptr,__format);
    FILE *Debug;
    Debug = fopen("debug.tmp","a");
    if ( Debug ) {
       vfprintf(Debug,__format,arg_ptr);
       fclose(Debug);  }
	va_end(arg_ptr);
}

EXPORT void dPrintfTime()
{
    SYSTEMTIME SystemTime; 	// address of system time structure
    GetLocalTime(&SystemTime);
    dPrintf("\n%hd-%hd-%hd ",SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay);
    dPrintf("%hd:%hd:%hd:%hd\n",SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,SystemTime.wMilliseconds);
}