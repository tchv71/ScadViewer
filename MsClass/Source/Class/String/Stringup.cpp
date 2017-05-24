#include <stdafx.h>
#include <defclass.h>

EXPORT int strcmpup(LPCSTR Str1, LPCSTR Str2)
{
	char *pS1 = (char*)Str1, *pS2 = (char*)Str2;
	int s1, s2;
	while ( 1 ) {
	   s1 = toupper(*pS1);  s2 = toupper(*pS2);
	   if ( s1 != s2 ) return s1 - s2;
	   if (  s1 == 0 ) break;
	   pS1++;  pS2++;   }
	return 0;
}

EXPORT int strncmpup(LPCSTR Str1, LPCSTR Str2, int Len )
{
	char *pS1 = (char*)Str1, *pS2 = (char*)Str2;
	int s1, s2, i;
	for ( i=0; i<Len; i++ ) {
	   s1 = toupper(*pS1);  s2 = toupper(*pS2);
	   if ( s1 != s2 ) return s1 - s2;
	   if (  s1 == 0 ) break;
	   pS1++;  pS2++;   }
	return 0;
}

EXPORT LPSTR strstrup(LPCSTR Str1, LPCSTR Str2)
{
        int i, k=strlen(Str2);

        for ( i=0; i<(int)strlen(Str1); i++ )
           if ( strncmpup(&Str1[i],Str2,k) == 0 ) return (LPSTR)&Str1[i];
	return NULL;
}