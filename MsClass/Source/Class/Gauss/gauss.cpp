#include <stdafx.h>
#include "gauss.h"
#include "math.h"

EXPORT void  GaussTape( WORD N, GAUSS_TAPE *GaussTape, WORD K, double * f);

EXPORT void  GaussTape( WORD N, double *Matr, WORD K, double * f)
{
	     GAUSS_TAPE  *Tape, *TapeWork;
	     MEMORY MEM;

	     LPSTR bn;
	     int i, j;
	     long k;

	     if ( N == 0 ) return;

	     Tape = (GAUSS_TAPE*)MemAlloc(N,sizeof(GAUSS_TAPE));

	     for ( i=0, k=0; i<N; i++ ) {
		Tape[i].s = (double*)&Matr[k];
		k += N - i;  }

	     bn = (LPSTR)MemAlloc(N+1);
	     for ( i=0; i<N; i++ ) {
		TapeWork = &Tape[i];   bn[i] = 1;
		for ( j=0; j<N-i; j++ ) if ( TapeWork->s[j] ) bn[i+j] = 1;
		for ( j=N-i-1; j>=0; j-- ) if ( bn[i+j] ) {
		   TapeWork->h = (WORD)(j + 1);  break;  }
		}
	     MemFree(bn);

	     GaussTape(N,Tape,K,f);

	     MemFree(Tape);
}

void  EEGauss( WORD N, double *Matr, WORD K, double * f)
{
	     int i, j, k;
        double r, *pDI, *pDJ;
#define MT(i,j)  Matr[(i)*N+j]
#define FT(i,j)  f[(i)*N+j]

	     if ( N == 0 ) return;

        for ( i=0; i<N; i++ ) {

           for ( j=i+1,k=i; j<N; j++ )
              if ( fabs(MT(j,i)) > fabs(MT(k,i)) ) k = j;

           if ( k != i ) {
              for ( j=i; j<N; j++ ) {
                 r = MT(k,j);  MT(k,j) = MT(i,j);  MT(i,j) = r;
                 }
              for ( j=0; j<K; j++ ) {
                 r = FT(j,k);  FT(j,k) = FT(j,i);  FT(j,i) = r;
                 }
              }
           r = MT(i,i);
           if ( r == 0 ) Crash("Null diagonal");
           for ( j=i; j<N; j++ ) MT(i,j) /= r;
           for ( j=0; j<K; j++ ) FT(j,i) /= r;
           for ( j=i+1; j<N; j++ ) {
              r = MT(j,i);
              pDJ = &MT(j,0);
              pDI = &MT(i,0);
              for ( k=i+1; k<N; k++ ) pDJ[k] -= pDI[k] * r;
              for ( k=0; k<K; k++ ) FT(k,j) -= FT(k,i) * r;
              }
           }

        for ( i=N-1; i; i-- ) {
           for ( j=0; j<i; j++ ) {
              r = MT(j,i);
              for ( k=0; k<K; k++ ) FT(k,j) -= FT(k,i) * r;
              }
           }

}