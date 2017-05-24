#include <stdafx.h>
#include <defclass.h>
#include <stdio.h>

EXPORT int  ListText(WORD Quantity, WORD *List, LPSTR Out, int MaxLenOut )
{
       int i, j, k, n, m, Pos=0;
       char s[64];

       for ( i=0; i<Quantity; i++ ) {
	   if ( i ) Out[Pos++] = ' ';
	   m = sprintf(s,"%hu",List[i]);
	   if ( Pos + m > MaxLenOut ) return 1;
	   strcpy(&Out[Pos],s);
	   Pos += m;
	   for ( j=i+1; j<Quantity; ) {
	      n = List[j] - List[j-1]; k = j + 1;
	      while ( k < Quantity ) {
            if ( n != List[k] - List[k-1] ) break;
            k++;  }
	      i = k-1;
	      if ( k > j + 1 ) {
		 if ( n < 2 ) m = sprintf(s,"-%hu",List[k-1]);
		 else m = sprintf(s," r %hu %hu ",List[k-1],n);
		 if ( Pos + m > MaxLenOut ) return 1;
		 strcpy(&Out[Pos],s);
		 Pos += m;
		 }
	      else i--;
	      break;
	      }  }

       return 0;

}