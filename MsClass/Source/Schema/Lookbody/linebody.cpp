#include <stdafx.h>
#include <schema.h>

int  PunctBody( DECART *pD, ELEM_BODY_FULL & );
int  PunctLine( LINE_BODY &, float x, float z, float &y, float Eps );

int  LineBody( LINE_BODY &LB, ELEM_BODY_FULL &EBF )
{
     int i, j, m;
     LINE_BODY *pLB;
     float d, x, y, z, Eps = EBF.Eps, r;
     ELEM_BODY_GEOM *pEBG = EBF.pEBG;
     DECART *pD1 = LB.pD1, *pD2 = LB.pD2;

     if ( EBF.pEB->Type > 4 ) return 0;

     for ( i=0; i<EBF.QuantityLine; i++ ) {

	     pLB = &EBF.LineBody[i];
 	     d = -LB.zp * pLB->xp + LB.xp * pLB->zp;
	     if ( fabs(d) < Eps ) continue;
	     x = ( LB.c * pLB->xp - LB.xp * pLB->c ) / d;
	     z = ( -LB.zp * pLB->c + LB.c * pLB->zp ) / d;

        if ( fabs(LB.xp) > fabs(LB.zp) ) {
           if ( pD1->x < pD2->x ) {
              if ( x < pD1->x + Eps || x > pD2->x - Eps  ) continue;  }
           else if ( x > pD1->x - Eps || x < pD2->x + Eps  ) continue;
           }
        else  {
           if ( pD1->z < pD2->z ) {
              if ( z < pD1->z + Eps  || z > pD2->z - Eps  ) continue;  }
           else if ( z > pD1->z - Eps  || z < pD2->z + Eps  ) continue;
           }

        if ( fabs(pLB->xp) > fabs(pLB->zp) ) {
           if ( pLB->pD1->x < pLB->pD2->x ) {
              if ( x < pLB->pD1->x + Eps  || x > pLB->pD2->x - Eps  ) continue;  }
           else if ( x > pLB->pD1->x - Eps  || x < pLB->pD2->x + Eps  ) continue;
           }
        else  {
           if ( pLB->pD1->z < pLB->pD2->z ) {
              if ( z < pLB->pD1->z + Eps  || z > pLB->pD2->z - Eps  ) continue;  }
           else if ( z > pLB->pD1->z - Eps  || z < pLB->pD2->z + Eps  ) continue;
           }

	     if ( fabs(LB.xp) > Eps ) y = LB.yp / LB.xp * ( x - pD1->x );
        else  y = LB.yp / LB.zp * ( z - pD1->z );
        y += pD1->y;

	     r = pEBG->a * x + pEBG->b * y + pEBG->c * z + pEBG->d;
	     if ( fabs(r) < Eps ) continue;
	     if ( r < 0 ) m = 1;
	     else m = -1;
	     return m;
	     }

     i = PunctBody(pD1,EBF);
     j = PunctBody(pD2,EBF);
     if ( i * j < 0 ) return 0;
     if ( i ) return i;
     if ( j ) return j;
     return 0;
}