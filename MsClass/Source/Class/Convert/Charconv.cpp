#include <stdafx.h>
#include <defclass.h>
#include <math.h>

EXPORT double  CharDouble(LPCSTR s,BYTE &i)
{
      double r;
      char q,  *c = &q, *d=(LPSTR)s;

      while ( *d == ' ' ) d++;
      r = strtod(d,&c);  i = 0;
      if ( c ) {
         if ( d[0] && ( c[0] == ' ' || c[0] == 0 ) ) return r;
         if ( c[0] || r == HUGE_VAL || r == -HUGE_VAL ) {  r = 0;  i = 1; }
         }

      return r;  }

EXPORT long CharLong(LPCSTR s,BYTE &i)
{
      long l;
      char q,  *c = &q, *d=(LPSTR)s;

      while ( *d == ' ' ) d++;
      l = strtol(d,&c,10);  i = 0;

      if ( d[0] && ( c[0] == ' ' || c[0] == 0 ) ) return l;
      if ( c[0] || l == 0 && d[0] != '0' ) {   l = 0;  i = 1;  }

      return l;  }

EXPORT DWORD  CharDWord(LPCSTR s,BYTE &i)
{
      DWORD l;
      char q,  *c = &q, *d = (LPSTR)s;

      while ( *d == ' ' ) d++;
      l = strtol(d,&c,10);  i = 0;
      if ( d[0] && ( c[0] == ' ' || c[0] == 0 ) ) return l;
      if ( d[0] == '-' || c[0] != 0 || l == 0 && d[0] != '0' ) {   l = 0;  i = 1;  }

      return l;  }

EXPORT WORD  CharWord(LPCSTR s,BYTE &i)
{
      DWORD l = CharDWord(s,i);
      if ( l > 0xFFFF ) {  i = 1;  return 0;  }
      return (WORD)l;
}