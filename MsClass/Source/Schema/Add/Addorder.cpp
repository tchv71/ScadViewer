#include <stdafx.h>

#include "schema.h"
//void MultMatr(double a[], double b[], short ia, short ja,short jb,double c[] );

#define XL CoordNode[1][0]

#define x3 CoordNode[2][0]
#define y3 CoordNode[2][1]

#define x4 CoordNode[3][0]
#define y4 CoordNode[3][1]
#define z4 CoordNode[3][2]

EXPORT WORD SCHEMA::AddElemOrder(WORD TypeElem, WORD QuantityNode,WORD *ListNode, double del )
{
     WORD i, n, List[4], *pL;
     int Control;
     double MC[9];

     if ( QuantityNode != 3 && QuantityNode != 4 ) return 0;

     n = AddElemListNode(TypeElem,QuantityNode,ListNode);
     if ( n == 0 ) return 0;
     pL = pFormat[n-1].pNode;
     if ( QuantityNode == 3 ) {
        if ( SchemaMatrCos(n,MC) ) goto _10;
        if ( MC[8] < 0 || MC[8] == 0 && MC[5] > 0 ) {
           i = pL[1]; pL[1] = pL[2];  pL[2] = i;  }
        return n;   }

     if (  YesOrder(n,ListNode,del) ) return n;

     memcpy(List,ListNode,4*sizeof(WORD));
     i = List[2]; List[2] = List[3];  List[3] = i;
     Control = YesOrder(n,List,del);
     if ( Control == 0 ) {
         memcpy(List,ListNode,4*sizeof(WORD));
         i = List[1]; List[1] = List[2];  List[2] = i;
         Control = YesOrder(n,List,del);
         if ( Control == 0 ) {
            memcpy(List,ListNode,4*sizeof(WORD));
            i = List[1]; List[1] = List[3];  List[3] = i;
            Control = YesOrder(n,List,del);
            }  }

     if ( Control ) {
        if ( Control < 0 ) {
           i = List[1]; List[1] = List[2];  List[2] = i;
           }
        memcpy(pL,List,4*sizeof(WORD));
        return n;  }

_10: QuantityElem--;
     return 0;
}

EXPORT int  MatrCos( double *,double*);

EXPORT int  SCHEMA::YesOrder(WORD NumElem, WORD *ListNode, double del )
{
     WORD i;
     double MC[9], CoordNode[4][3],  Eps, ck[4][3];
     CK *pCK;

     pCK = &Coord[ListNode[0]-1];
     memset(ck,0,3*sizeof(double));
     for ( i=1; i<4; i++ ) {
        memcpy(ck[i],&Coord[ListNode[i]-1],3*sizeof(double));
        ck[i][0] -= pCK->x;  ck[i][1] -= pCK->y;  ck[i][2] -= pCK->z;
        }
     if ( MatrCos((double*)ck,MC) ) return 0;
     for ( i=1; i<4; i++ )
        MultMatr(MC,ck[i],-3,3,1,CoordNode[i]);
     Eps = del * XL;
     if ( y4 < Eps ) return 0;
     if ( y3 * ( x4 - XL ) - y4 * ( x3 - XL ) < Eps * ( XL + y3 ) )return 0;
     if ( y3 * x4 - x3 * y4 < Eps * ( XL + y3  ) ) return 0;

     if ( MC[8] < 0 || MC[8] == 0 && MC[5] > 0 ) return -1;
     return 1;
}