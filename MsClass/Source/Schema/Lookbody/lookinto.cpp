#include <stdafx.h>
#include <schema.h>

void ElemBodyFull( DECART  * Coord,
			ELEM_BODY &EB, ELEM_BODY_GEOM &EBG, ELEM_BODY_FULL &EBF );
int  LineBody( LINE_BODY &, ELEM_BODY_FULL &);
int  BodyBody( ELEM_BODY_FULL &, ELEM_BODY_FULL &);

int   LookInto( long ki, long Num[], long &kGr,  long kGm,  ELEM_BODY  * ElemBody,
	    ELEM_BODY_GEOM  * EBG, DECART  * LookCoord, float Eps, long  *NumElemBody  )
{
       long i, j, n, m, ni, nj;

       ELEM_BODY_GEOM  *pEBGI, *pEBGJ;
       ELEM_BODY_FULL EBFI, EBFJ;
       int Control;
       EBFI.Eps = EBFJ.Eps = Eps;
       BYTE Out = 0;

       for ( ni=0; ni<ki; ni++ ) {

          i = Num[ni];
	       if ( NumElemBody[i] ) continue;
	       pEBGI = &EBG[i];
	       ElemBodyFull(LookCoord,ElemBody[i],*pEBGI,EBFI);

	       n = EBFI.pEB->Type;

	       if ( n == 1 ) goto _20;

	          for ( nj=0; nj<ki; nj++ ) {

                j = Num[nj];    Control = 0;
	             if ( i == j || NumElemBody[j] > 0 ) continue;
	             pEBGJ = &EBG[j];

	             if ( pEBGI->xMin > pEBGJ->xMax + Eps ||
		             pEBGI->xMax < pEBGJ->xMin - Eps ||
		             pEBGI->zMin > pEBGJ->zMax + Eps ||
		             pEBGI->zMax < pEBGJ->zMin - Eps ) continue;
                if ( pEBGI->yMin > pEBGJ->yMax + Eps ) {  Control = -1;  goto _10;  }
	             if ( pEBGI->yMax < pEBGJ->yMin - Eps ) {  Control =  1;  goto _10;  }

	             m = ElemBody[j].Type;
	             if ( m == 1 || n == 2 && m == 2 ) continue;

	             ElemBodyFull(LookCoord,ElemBody[j],*pEBGJ,EBFJ);

	             if ( n == 2 && ( m == 3 || m == 4 ) ) {
		             Control =  LineBody(EBFI.LineBody[0],EBFJ);
		             goto _10;  }
	             if ( ( n == 3 || n == 4 ) && m == 2 ) {
		             Control = -LineBody(EBFJ.LineBody[0],EBFI);
		             goto _10;  }
	             if ( n > 2 && m > 2 ) {
		             if ( n > 4 && m > 4 ) continue;
                   Control = BodyBody(EBFI,EBFJ);
                   goto _10;  }

_10:            if ( Control > 0 ) NumElemBody[j] -= 1;
	             if ( Control < 0 ) {  NumElemBody[i] -= 1;  break;  }

	             }

_20:	       if ( NumElemBody[i] == 0 ) {
                NumElemBody[i] = kGr--;
                Out = 1;
                if ( kGr <= kGm )
                return Out;  }

	          }

    return Out;

}