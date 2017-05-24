#include <stdafx.h>
#include <schema.h>

void ElemBodyGeom ( DECART  * Coord, float Eps ,
		    ELEM_BODY &EB, ELEM_BODY_GEOM &EBG )
{
     int i, n;
     DECART *pD, *pD1, *pD2, *pD3, D1, D2;
     float a, dl1, dl2;

     pD = (DECART*)&Coord[EB.Node[0]-1];
     EBG.xMax = EBG.xMin = pD->x;
     EBG.yMax = EBG.yMin = pD->y;
     EBG.zMax = EBG.zMin = pD->z;

     for ( i=0; i<4 && ( n = EB.Node[i] ) > 0 ; i++ ) {
	     pD = (DECART*)&Coord[n-1];
	     if ( EBG.xMax < pD->x ) EBG.xMax = pD->x;
	     if ( EBG.xMin > pD->x ) EBG.xMin = pD->x;
	     if ( EBG.yMax < pD->y ) EBG.yMax = pD->y;
	     if ( EBG.yMin > pD->y ) EBG.yMin = pD->y;
	     if ( EBG.zMax < pD->z ) EBG.zMax = pD->z;
	     if ( EBG.zMin > pD->z ) EBG.zMin = pD->z;
	     }

     if ( i > 2 ) {
	     pD1 = (DECART*)&Coord[EB.Node[0]-1];
	     pD2 = (DECART*)&Coord[EB.Node[1]-1];
	     pD3 = (DECART*)&Coord[EB.Node[2]-1];
	     D1.x = pD2->x - pD1->x;
	     D1.y = pD2->y - pD1->y;
	     D1.z = pD2->z - pD1->z;
	     dl1 = fabs(D1.x) + fabs(D1.y) + fabs(D1.z);
	     D2.x = pD3->x - pD1->x;
	     D2.y = pD3->y - pD1->y;
	     D2.z = pD3->z - pD1->z;
	     dl2 = fabs(D2.x) + fabs(D2.y) + fabs(D2.z);
	     EBG.a = D1.y * D2.z - D1.z * D2.y;
	     EBG.b = D1.z * D2.x - D1.x * D2.z;
	     EBG.c = D1.x * D2.y - D1.y * D2.x;
	     EBG.d = -EBG.a * pD1->x - EBG.b * pD1->y - EBG.c * pD1->z;
	     a = fabs(EBG.a) + fabs(EBG.b) + fabs(EBG.c);
	     if ( a > EPSILON * dl1 * dl2 ) {
	        if ( EBG.b < 0 ) a = -a;
	        EBG.a /= a;  EBG.b /= a;  EBG.c /= a;  EBG.d /= a;
	        }
	     else memset(&EBG.a,0,4*sizeof(float));
	     if ( fabs(EBG.b) < EPSILON ) EB.Type += 2;
	     }

}

void ElemBodyFull( DECART  *Coord, ELEM_BODY &EB, ELEM_BODY_GEOM &EBG, ELEM_BODY_FULL &EBF )
{
     static BYTE nL3[] = { 0,1,2, 1,2,0, 2,0,1 };
     static BYTE nL4[] = { 0,1,2, 1,3,0, 3,2,0, 2,0,1 };
     short i;
     DECART *pD1, *pD2;
     BYTE *nL;
     LINE_BODY *pLB;
     float a, b;

     if ( EB.Type == 1 ) return;

     EBF.pEB  = &EB;
     EBF.pEBG = &EBG;

     EBF.QuantityLine = 0;
     nL = nL3;
     if ( EBF.pEB->Type == 4 || EBF.pEB->Type == 6 ) nL = nL4;

     for ( i=0; ; i+=3 ) {

	     pLB = &EBF.LineBody[EBF.QuantityLine];
	     pD1 = pLB->pD1 = &Coord[EB.Node[nL[i]]-1];
	     pD2 = pLB->pD2 = &Coord[EB.Node[nL[i+1]]-1];
	     pLB->xp = pD2->x - pD1->x;
	     pLB->yp = pD2->y - pD1->y;
	     pLB->zp = pD2->z - pD1->z;

	     a = fabs(pLB->xp) + fabs(pLB->zp);
        b = 1;
        pLB->c = pLB->xp * pD1->z - pLB->zp * pD1->x;
        if ( EBF.pEB->Type > 2 ) {
	        pD2 = (DECART*)&Coord[EB.Node[nL[i+2]]-1];
	        b = pLB->zp * pD2->x - pLB->xp * pD2->z + pLB->c;
           }
	     if ( a > EBF.Eps ) {
	         if ( b < 0 ) a = -a;
	         pLB->xp /= a;  pLB->yp /= a;  pLB->zp /= a;  pLB->c /= a;
	         EBF.QuantityLine++;  }
	     else pLB->xp = pLB->zp = pLB->c = 0;

	     if ( EBF.pEB->Type < 3 || nL[i+1] == 0 ) break;

	     }

     if ( EBF.QuantityLine == 0 && EBF.pEB->Type == 2 ) EBF.pEB->Type = 1;

}