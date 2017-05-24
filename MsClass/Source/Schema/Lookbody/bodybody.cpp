#include <stdafx.h>
#include <schema.h>

int  PunctBody( DECART *, ELEM_BODY_FULL & );
int  LineBody(  LINE_BODY &, ELEM_BODY_FULL & );

int  BodyBody( ELEM_BODY_FULL &EBFI, ELEM_BODY_FULL &EBFJ )
{
     int i, n=0, m=0;

/*     ELEM_BODY_GEOM *EBGI = EBFI.pEBG, *EBGJ = EBFJ.pEBG;
     if ( fabs(EBGI->a-EBGJ->a) + fabs(EBGI->b-EBGJ->b) +
          fabs(EBGI->c-EBGJ->c) < EPSILON ) {
        if ( fabs(EBGI->d - EBGJ->d ) < EPSILON ) return 0;
        if ( EBFI.pEBG->d < EBFJ.pEBG->d ) return -1;
        if ( EBFI.pEBG->d > EBFJ.pEBG->d ) return 1;
        }*/

     if ( EBFJ.pEB->Type < 5 ) for ( i=0; i<EBFI.QuantityLine; i++ ) {
	     n = LineBody(EBFI.LineBody[i],EBFJ);
	     if ( n ) break;  }

     if ( EBFI.pEB->Type < 5 ) for ( i=0; i<EBFJ.QuantityLine; i++ ) {
     	  m = -LineBody(EBFJ.LineBody[i],EBFI);
	     if ( m ) break;  }

     if ( n == m ) return n;
     return 0;

}