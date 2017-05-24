#include <stdafx.h>
#include <defclass.h>
#include <string.h>

EXPORT int ParamText(LPSTR Param, LPSTR Name, LPSTR Out)
{

	short i, kf=0, Reg=0;
	char NameIn[MAXPATH+1], Text[MAXPATH+1], *pS, c;

	strncpy(Text,Param,MAXPATH);  Text[MAXPATH] = 0;
	strupr(Text);

	strncpy(NameIn,Name,MAXPATH);  strncat(NameIn,"=",MAXPATH);
	strupr(NameIn);

	Out[0] = 0;
	pS = strstr(Text,NameIn);
	if ( pS == 0 ) return 1;
   if ( pS != Text ) {
      c = pS[-1];
      if ( c != ',' && c != ' ' ) return 1;
      }
	pS += strlen(NameIn);
   if ( *pS == '\"' ) {  Reg = 1;  pS++;  }

	for ( i=0; *pS ; pS++ )  {
      if ( Reg && *pS == '\"' ) {
         if ( pS[1] != '\"' ) Reg = 0;
         pS++;  }
	   if ( Reg == 0 && strchr(",",*pS) ) break;
	   if ( i > MAXPATH )  {  kf=1;  break;  }
	   Out[i++]  = *pS;  }
	Out[i] = 0;
   if ( Reg ) kf = 1;

	return  kf;

}