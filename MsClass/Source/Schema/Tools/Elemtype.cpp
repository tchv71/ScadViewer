#include <stdafx.h>
#include <classwin.h>

EXPORT int ElemType(short NTPR)
{
     short n;

     if ( NTPR == 1020 || NTPR == 1040 || NTPR == 1021) return 1;
	 if ( NTPR == 1060 || NTPR == 1080 || NTPR == 1085) return 2;
     n = NTPR % 100;
     if ( NTPR > 2000 && NTPR == 200 || n == 0 ) return 0;
     if ( n <= 10 ) return 1;
     if ( n <= 30 || n > 40 && n <= 50 ) return 2;
     if ( n > 30 && n <= 40 ) return 3;
     if ( n > 50 && n <= 60 ) return 4;
     if ( n > 60 && n <= 70 ) return 5;
     if ( n > 70 && n <= 80 ) return 6;
     if ( n > 80 && n <= 90 ) return 7;
     if ( n == 1020 || n == 1040) return 1;
     return 0;
}