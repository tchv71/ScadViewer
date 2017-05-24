#include <stdafx.h>
#include "gauss.h"

EXPORT void  GaussTape( WORD N, GAUSS_TAPE *GaussTape, WORD K, double * f)
{
	     GAUSS_TAPE   *li, *lj;
	     MEMORY MEM;

	     double *ai, *aj, *air;
	     char *bt, *bi, *bj, *bij, *br;
	     double c, r;
	     double *fi, *fj, *fij;
	     int i, j, k, m;

	     if ( N == 0 ) return;

	     bt = (char*)MemAlloc(N+1,1);

	     for ( bi=bt, li=GaussTape, i=0; i<N; li++, bi++, i++ )  {
		 ai = li->s;   c = ai[0];
		 if ( c == 0 ) Crash("Null diagonal");
		 for ( bij=bi+1, aj=ai+1, j=1; j<li->h; bij++, aj++, j++ ) {
		    if ( *aj ) {  *bij = 1;  *aj /= c;  }
		    else *bij = 0;
		    }
		 for ( bij=bi+1, lj=li+1, j=1; j<li->h; bij++, lj++, ai++, j++ ) if ( *bij ) {
		    aj  = lj->s;
		    air = ai + 1;     r = *air * c;
		    for ( bj=bij, k=j; k<li->h; bj++, aj++, air++, k++ ) {
		       if ( ! (*bj) ) {
			  br = bj;
			  while ( !(*bj) && k<li->h ) {  bj++;  k++;  }
			  if ( k == li->h ) break;
			  aj  += ( bj - br );
			  air += ( bj - br );
			  }
		       *aj -= *air * r;  }
		    }	}
	     if ( GaussTape[N-1].s[0] == 0 ) Crash("Null diagonal");

	     for( fi=(double*)f, k=0; k<K; fi+=N, k++ ) {
		for ( fj=fi, li=GaussTape, i=0; i<N; li++, fj++, i++ )  {
		    ai = li->s;    r = *fj;
		    if ( r == 0 ) continue;
		    for ( fij=fj+1, aj=ai+1, j=1; j<li->h; aj++, fij++, j++ )
		       *fij -= r * *aj;
		    *fj /= ai[0];    }
		for ( fj=fi+N-2, li=(GaussTape+N-2), j=N-2; j>=0; li--, fj--, j-- )  {
		    ai = li->s;
		    for ( fij=fj+1, aj=ai+1, m=1; m<li->h; aj++, fij++, m++ )
		       *fj -=  *fij * *aj;
		    }
		}

	     MemFree(bt);

}



EXPORT void  GaussTapeDirect( WORD N, GAUSS_TAPE *GaussTape )
{
	     GAUSS_TAPE   *li, *lj;
	     MEMORY MEM;

	     double *ai, *aj, *air;
	     char *bt, *bi, *bj, *bij, *br;
	     double r, c;
	     int i, j, k;

	     if ( N == 0 ) return;

	     bt = (char*)MemAlloc(N+1,1);

	     for ( bi=bt, li=GaussTape, i=0; i<N; li++, bi++, i++ )  {
		     ai = li->s;   c = ai[0];
		     if ( c == 0 ) Crash("Null diagonal");
		     for ( bij=bi+1, aj=ai+1, j=1; j<li->h; bij++, aj++, j++ ) {
		        if ( *aj ) {  *bij = 1;  *aj /= c;  }
		        else *bij = 0;
		     }

		  for ( bij=bi+1, lj=li+1, j=1; j<li->h; bij++, lj++, ai++, j++ ) if ( *bij ) {
		     aj  = lj->s;
		     air = ai + 1;     r = *air * c;
		     for ( bj=bij, k=j; k<li->h; bj++, aj++, air++, k++ ) {
		        if ( ! (*bj) ) {
			        br = bj;
			        while ( !(*bj) && k<li->h ) {  bj++;  k++;  }
			        if ( k == li->h ) break;
			        aj  += ( bj - br );
			        air += ( bj - br );
			        }
             *aj -= *air * r;  }
		       }	}

	     if ( GaussTape[N-1].s[0] == 0 ) Crash("Null diagonal");

	     MemFree(bt);

}

EXPORT void  GaussTapeBack( WORD N, GAUSS_TAPE *GaussTape, WORD K, double * f)
{
	     GAUSS_TAPE   *li;
	     double *ai, *aj;
	     double r;
	     double *fi, *fj, *fij;
	     int i, j, k, m;

	     if ( N == 0 ) return;

	     for( fi=(double*)f, k=0; k<K; fi+=N, k++ ) {

		     for ( fj=fi, li=GaussTape, i=0; i<N; li++, fj++, i++ )  {
		        ai = li->s;    r = *fj;
		        if ( r == 0 ) continue;
		        for ( fij=fj+1, aj=ai+1, j=1; j<li->h; aj++, fij++, j++ )
		            *fij -= r * *aj;
		        *fj /= ai[0];    }
           for ( fj=fi+N-2, li=(GaussTape+N-2), j=N-2; j>=0; li--, fj--, j-- )  {
		        ai = li->s;
		        for ( fij=fj+1, aj=ai+1, m=1; m<li->h; aj++, fij++, m++ )
		           *fj -=  *fij * *aj;
		        }
		     }

}

EXPORT void  GaussTape1( WORD N, GAUSS_TAPE *GaussTape, WORD K, double * f)
{
       GaussTapeDirect(N,GaussTape);
       GaussTapeBack(N,GaussTape,K,f);
}
