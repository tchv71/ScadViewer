#include <stdafx.h>
#include <defclass.h>
#include <string.h>
#include <convert.h>

EXPORT int  ParamText(LPSTR Param, LPSTR Name, LPSTR Out);

EXPORT int  ParamValue(LPSTR Param, LPSTR Name, int &Value )
{
	char Out[20];
	BYTE n = 0;

	if ( ParamText(Param,Name,Out) ) return 1;
	Value = CharLong(Out,n);
	if ( n ) {  Value = 0;  return 1;  }
	return  0;
}

EXPORT int  ParamValue(LPSTR Param, LPSTR Name, short &Value )
{
         int l;
	int n = ParamValue(Param,Name,l);
	if ( n || abs(l) > 0x7FFF ) {  Value = 0;  return 1;  }
         Value = (short)l;
	return  0;
}