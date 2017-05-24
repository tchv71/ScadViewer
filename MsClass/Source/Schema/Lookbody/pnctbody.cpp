#include <stdafx.h>
#include <schema.h>

int  PunctBody( DECART *pD, ELEM_BODY_FULL &EBF )
{
     LINE_BODY *pLB;
     int i;
     float s;
     ELEM_BODY_GEOM *pEBG = EBF.pEBG;

     for ( i=0; i<EBF.QuantityLine; i++ ) {
        pLB = &EBF.LineBody[i];
       	if ( pLB->zp * pD->x - pLB->xp * pD->z + pLB->c < EBF.Eps )
//       	if ( pLB->zp * pD->x - pLB->xp * pD->z + pLB->c < EBF.Eps )
        return 0;
        }
     s = pEBG->a * pD->x + pEBG->b * pD->y + pEBG->c * pD->z + pEBG->d;
     if ( fabs(s) < EBF.Eps ) return 0;
     if ( s < 0 ) return 1;
     return -1;
}