#include <stdafx.h>
#include <string.h>
#include <defclass.h>

EXPORT void StringRead(LPCSTR String,DWORD LenStr,DWORD & PosStr, LPCSTR & Word)
{
	  if ( LenStr > PosStr ) {
	     Word = (LPCSTR)&String[PosStr];
	     PosStr += strlen(Word) + 1;
	     }
	  else if ( PosStr ) Word = (LPCSTR)&String[PosStr-1];
          else Word = String;
}