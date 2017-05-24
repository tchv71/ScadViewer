#include <stdafx.h>
#include <defclass.h>

EXPORT BYTE Separate( LPCSTR InpString,  DWORD LengthInpString,
	       DWORD &CurrentPos, LPCSTR SeparateSymbol, LPSTR OutString)
{
     short lq = 0;
     char c;
     BYTE iRet = 0;

_10: while( CurrentPos <= LengthInpString &&
	strchr(SeparateSymbol,InpString[CurrentPos]) == NULL )
	   OutString[lq++] = InpString[CurrentPos++];

     if ( lq == 0 ) {
	c = InpString[CurrentPos++];
	if ( c == ' ' ) goto _10;
	iRet = OutString[lq++] = c;  }

     OutString[lq] = 0;
     return(iRet);

}