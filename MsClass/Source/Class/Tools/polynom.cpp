#include <stdafx.h>
#include <math.h>
#include <defclass.h>

EXPORT void PolyDiffer( int Step, double *Inp, double *Out )
{
      int i, j;
      double *d;
      if ( Out == NULL ) d = Inp;
      else {
         memcpy(Out,Inp,7*sizeof(double));
         d = Out;  }
      for ( i=1; i<Step+1; i++ ) {
	      for ( j=0; j<6; j++ )  d[j] = (j+1) * d[j+1];
	      d[7-i]=0;  }
}

EXPORT void PolyDiffer( int Step, long double *Inp, long double *Out )
{
      int i, j;
      long double *d;
      if ( Out == NULL ) d = Inp;
      else {
         memcpy(Out,Inp,7*sizeof(double));
         d = Out;  }
      for ( i=1; i<Step+1; i++ ) {
	      for ( j=0; j<6; j++ )  d[j] = (j+1) * d[j+1];
	      d[7-i]=0;  }
}

EXPORT double PolyValue(int Step, double  *Pol, double  x, int Type )
{
    int i;
	double q=0, a=1;
    if ( Type == 0 ) for ( i=0; i<Step; i++ ) {  q += a * Pol[i];  a *= x;  }
    else for ( i=1; i<Step; i++ ) {  q += i * a * Pol[i];  a *= x;  }
	if ( fabs(q) < 1e-20 )  q = 0;
	return q;
}

EXPORT long double PolyValue(int Step, long double  *Pol, long double  x, int Type )
{
    int i;
	long double q=0, a=1;
    if ( Type == 0 ) for ( i=0; i<Step; i++ ) {  q += a * Pol[i];  a *= x;  }
    else for ( i=1; i<Step; i++ ) {  q += i * a * Pol[i];  a *= x;  }
	if ( fabs(q) < 1e-20 )  q = 0;
	return q;
}