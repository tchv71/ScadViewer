#include <stdafx.h>
#include "schema.h"
int   CheckPlate(SCHEMA &Schem,int n1, int n2, int n3, double mk[9] );
int  CheckPlate(SCHEMA &Schem,int n1, int n2, int n3, double mk[9],
     double &xl, double &xl3, double &yl3 );
void  GetPlateCoord(double xb[3], double x[3], double mk[9], double xyz[3] );

EXPORT int SCHEMA::CheckVolumeOrder( int NumElem )
{
      double Matr[9], s;
      int n, k=5;
      if ( NumElem == 0 || NumElem > QuantityElem ) return 1;
      FORMAT *pF = &pFormat[NumElem-1];
      CK *pCK, *qCK;

      if ( pF->QuantityNode < 4 ) return 1;
      if ( SchemaMatrCos(NumElem,Matr) ) return 1;

      n = pF->TypeElem % 100;
      if ( n == 32 || n == 33 || n == 34 ) k = 4;
      if ( pF->QuantityNode < k ) return 1;
      pCK = &Coord[pF->pNode[k-1]-1];
      qCK = &Coord[pF->pNode[0]-1];

      s = Matr[2] * ( pCK->x - qCK->x )
        + Matr[5] * ( pCK->y - qCK->y )
        + Matr[8] * ( pCK->z - qCK->z );

      if ( s < 0 ) {
         k = pF->pNode[1];  pF->pNode[1] = pF->pNode[2];  pF->pNode[2] = k;
         if ( n == 31 || n == 36 || n == 37 ) {
            k = pF->pNode[5];  pF->pNode[5] = pF->pNode[6];  pF->pNode[6] = k;
            }
         if ( n == 33 || n == 34 ) {
            k = pF->pNode[4];  pF->pNode[4] = pF->pNode[5];  pF->pNode[5] = k;
            }

         }

      return 0;
}


EXPORT WORD SCHEMA::AddVolumeOrder( WORD TypeElem, WORD Quantity,WORD *List, double del )
{
/*     double mk[9];
     int i, j, n, i1, i2, i3, k, npp, m=3;
     int Num[20];
     WORD *pL, ListNum[20];
     CK *pCKI, *pCKJ, *pCKK;
     double d, rC[3], rQ[3], xl, xl3, yl3, XYZ[20][3], MaxZ, MinZ, x, y;

     if ( Quantity < 4 || Quantity > 20 ) return 0;

     memset(Num,0,sizeof(Num));
     npp = AddElemListNode(TypeElem,Quantity,List);
     if ( npp == 0 ) return 0;
     pL = pFormat[npp-1].pNode;

     for ( i=0,l=0; i<Quantity; i++ ) {
        if ( List[i] == 0 || List[j] > QuantityNode ) return 0;
        for ( j=0,n=100; j<Quantity; j++ ) {
           if ( Num[j] ) continue;
           if ( n == 100 ) n = j;
           if ( List[j] == 0 || List[j] > QuantityNode ) return 0;
           pCKI = &Coord[n];
           pCKJ = &Coord[List[j]-1];
           if ( pCKI->x < pCKJ->x ||
                pCKI->x == pCKJ->x && ( pCKI->y < pCKJ->y ||
                pCKI->y == pCKJ->y && ( pCKI->z < pCKJ->z ) ) )  continue;
           n = j;  }
        Num[n] = List[n];  }

     if ( Quantity == 4 ) {
        if ( CheckPlate(*this,Num[0],Num[1],Num[2],mk,xl,xl3,yl3) ) return 0;
        GetPlateCoord((double*)&Coord[Num[0]-1],(double*)&Coord[Num[3]-1],mk,rQ);
        if ( fabs(rQ[2]) < del * xl * yl3 ) return 0;
        if ( rQ[2] < 0 ) {  n = pL[1];  pL[1] = pL[2];  pL[2] = n;   }
        return npp;   }


     ListNum[0] = Num[0];
     for ( i1=1; i1<Quantity; i1++ ) {
        ListNum[1] = Num[i1];
        for ( i2=1; i2<Quantity; i2++ ) {
           if ( i2 == i1 ) continue;
           ListNum[2] = Num[i2];
           if ( CheckPlate(*this,Num[0],Num[i1],Num[i2],mk,xl,xl3,yl3) ) continue;
           MaxZ = 0;
           for ( i3=1,n=0,k=0; i3<Quantity; i3++ ) {
              if ( i3 == i1 || i3 == i2 ) continue;
              GetPlateCoord((double*)&Coord[Num[0]-1],(double*)&Coord[Num[i3]-1],mk,XYZ[n]);
              d = XYZ[n++][2];
              if ( d > MaxZ ) MaxZ = d;
              if ( d < MinZ ) {  MinZ = d;  k = Num[i3];  }
              }
           if ( MinZ < 0 && -MinZ > MaxZ / 4 ) continue;
           if ( Quantity == 6 && k ) continue;
           if ( Quantity == 8 ) {
              if ( k == 0 ) continue;
              x = XYZ[k-1][0];
              y = XYZ[k-1][1];
              if ( y <= 0 || x * yl3 - y * xl3 <= 0 ||
                  yl3 * ( x - xl ) - ( xl3 - xl ) * y <= 0 ) continue;
              ListNum[3] = k;  m = 4;  }


              }   }
        }

        if ( n != 5 ) return 0;
        for ( i=0; i<n; i++ ) {


           }
        }
*/
     return 0;   }