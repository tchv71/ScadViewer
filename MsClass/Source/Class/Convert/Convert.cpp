#include <stdafx.h>
#include <defclass.h>
#include <stdio.h>
#include <math.h>

EXPORT void  DoubleChar(double Dbl,LPSTR Str,int LenStr)
{
       char *sp, ex[10];
       int i, n = 0, k = 0, Dec, Len, Ln, Sign, El = 0, it;

       Len = ( LenStr > 0 ? LenStr : -LenStr );
       Ln = Len;
       Str[Len] = 0;
       if ( Len == 0 ) return;

       sp = ecvt(Dbl,Len,&Dec,&Sign);     it = Dec;

       if ( Dec < 1 && ( Len == 1 || Len == 2 && Sign ) ) {
	  memset(Str,'0',Len);
	  if ( Len == 2 ) Str[0] = '-';
	  return;  }

       if ( Sign ) {  Str[k++] = '-';  Len--;  }

       if ( Dec > Len || -Dec >= Len - 1 ) {
	  El = sprintf(ex,"e%d",Dec-1);
	  if ( El >= Len ) {
	     if ( Dec < 1 ) {  El = 0;  it = 1 - Len;  goto _10;  }
	     memset(Str,'*',Ln);
	     return;   }
	  Len -= El;  it = 1;  }

_10:   if ( it > 0 ) {
	  memcpy(&Str[k],sp,it);	k += it;  Len -= it;
	  n = it;   }

       if ( Len > 0 ) {  Str[k++] = '.';  Len--;  }

       if ( it < 0 ) {
	  memset(&Str[k],'0',-it);
	  Len += it;  k -= it;  }

       if ( Len )	for ( i=n+Len-1; i>=n; i-- )
	  if ( sp[i] != '0' ) {
	     memcpy(&Str[k],&sp[n],i-n+1);
	     k += i - n + 1;  break;  }

       if ( El ) {   strcpy(&Str[k],ex);  k+= El;  }

       if ( LenStr > 0 ) {
	  memmove(&Str[Ln-k],Str,k);
	  memset(Str,' ',Ln-k);  }
       else memset(&Str[k],' ',Ln-k);

}

EXPORT void  DoubleCharP(double Dbl,LPSTR Str,int LenStr)  {

       if ( Dbl == 0 ) {
	  memset(Str,' ',abs(LenStr));
	  Str[abs(LenStr)] = 0;  }
       else if ( LenStr < -1 && Dbl > 0 ) {
	       DoubleChar(Dbl,&Str[1],LenStr+1);
	       Str[0] = ' ';  }
	    else DoubleChar(Dbl,Str,LenStr);
       }

EXPORT void  FloatChar(float Flt,LPSTR Str,int LenStr)
{      double Dbl = Flt;
       DoubleChar(Dbl,Str,LenStr);
}

EXPORT long  DoubleLong(double s,BYTE &i)
{
      double r;
      long k;

      i = 0;
      k = long(s);  r = double(k);
      if ( fabs(r-s) > 0.001 ) i = 1;

      return (k);  }

EXPORT int  EqDouble( double a1,double a2 )
{
      if ( fabs( a1 - a2 ) < 1e-6 * ( fabs(a1) + fabs(a2) ) ) return 1;
      return 0;
}

EXPORT void  CopyWordToLong( long *Out, WORD *Inp, int Quantity )
{
      for ( int i=0; i<Quantity; i++ ) Out[i] = Inp[i];
}

EXPORT void  CopyFloatToDouble( double *Out, float *Inp, int Quantity )
{
      for ( int i=0; i<Quantity; i++ ) Out[i] = Inp[i];
}

EXPORT void  CopyDoubleToFloat( float *Out, double *Inp, int Quantity )
{
      for ( int i=0; i<Quantity; i++ ) Out[i] = (float)Inp[i];
}