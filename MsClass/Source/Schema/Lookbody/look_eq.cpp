#include <stdafx.h>
#include <schema.h>

void SCHEMA::LookEqBody( DECART  * LookCoord, double Eps )
{
       double Matr[9];
       FORMAT *pF;
       long i, j, k, n, mi, mj, in, jn;
       DECART  *LC, *LCJ;
       double x, y, z, r, ri, rj;
       ELEM_BODY *EBI, *EBJ;

       for ( i=0; i<Video.QuantityElemBody; i++ ) {

          if ( Video.DeleteProcess ) {  DeleteLookBody();  goto _10;  }
          EBI = &Video.ElemBody[i];
	       if ( EBI->NumElem == 0 ) continue;
          mi = ElemType(pFormat[EBI->NumElem-1].TypeElem);
          if ( mi < 2 || mi > 3 ) continue;
          in = EBI->Type;  if ( in > 4 ) in -= 2;

          for ( j=i+1; j<Video.QuantityElemBody; j++ ) {

             EBJ = &Video.ElemBody[j];
             if ( EBJ->NumElem == 0 ) continue;
             mj = ElemType(pFormat[EBJ->NumElem-1].TypeElem);
             if ( mj < 2 || mj > 3 ) continue;
             jn = EBJ->Type;  if ( jn > 4 ) jn -= 2;

             for ( k=0; k<in; k++ ) {
                LC = &LookCoord[EBI->Node[k]-1];
	             for ( n=0; n<jn; n++ ) {
                   LCJ = &LookCoord[EBJ->Node[n]-1];
		             if ( fabs(LC->x-LCJ->x) > Eps || fabs(LC->y-LCJ->y) > Eps ||
		                  fabs(LC->z-LCJ->z) > Eps ) continue;
                   break;  }
                if ( n == jn ) goto _10;  }

             if ( Video.FragmParam == 0 ) {  EBI->NumElem = 0;  goto _10;  }

             if ( mi == mj && mi == 3 ) {
                LC = &LookCoord[EBI->Node[0]-1];
                x = LC->x;    y = LC->y;   z = LC->z;
                LC = &LookCoord[EBI->Node[1]-1];
                Matr[0] = LC->x - x;    Matr[1] = LC->y - y;   Matr[2] = LC->z - z;
                LC = &LookCoord[EBI->Node[2]-1];
                Matr[3] = LC->x - x;    Matr[4] = LC->y - y;   Matr[5] = LC->z - z;
                pF = &pFormat[EBI->NumElem-1];
                for ( n=0, ri=0; n<pF->QuantityNode; n++ ) {
                   LC = &LookCoord[pF->pNode[n]-1];
                   Matr[6] = LC->x - x;   Matr[7] = LC->y - y;   Matr[8] = LC->z - z;
                   r = det3x3(Matr);
                   if ( fabs(r) > fabs(ri) ) ri = r;
                   }
                pF = &pFormat[EBJ->NumElem-1];
                for ( n=0, rj=0; n<pF->QuantityNode; n++ ) {
                   LC = &LookCoord[pF->pNode[n]-1];
                   Matr[6] = LC->x - x;   Matr[7] = LC->y - y;   Matr[8] = LC->z - z;
                   r = det3x3(Matr);
                   if ( fabs(r) > fabs(rj) ) rj = r;
                   }
                EBI->NumElem = 0;
                if ( ri * rj < 0 ) EBJ->NumElem = 0;
                }
             else if ( mi != mj ) {
                if ( mi == 3 ) EBI->NumElem = 0;
                if ( mj == 3 ) EBJ->NumElem = 0;
                }
             else EBJ->NumElem = 0;
             if ( EBJ->NumElem == 0 ) break;

_10:;         }  }

       for ( i=0,n=0; i<Video.QuantityElemBody; i++ ) {
	       EBI = &Video.ElemBody[i];
	       if ( EBI->NumElem ) {
		       if ( n < i ) SpaceCopy(&Video.ElemBody[n],EBI,sizeof(ELEM_BODY));
             n++;  }
          }
       Video.QuantityElemBody = n;
}