#include <stdafx.h>
#include "schema.h"

EXPORT int SCHEMA::CompareSchem(SCHEMA &S2,int Level)
{
         int i, j, n, ne, nu, iRet = 0;
         FORMAT *F1,  *F2;
         CK  *pC1, *pC2;
         double MazSize, r;
         BYTE *YesNode, *KD1, *KD2;

         if ( TypeSystem.QuantityStep != S2.TypeSystem.QuantityStep ) return 11;
         for ( i=0; i<TypeSystem.QuantityStep; i++ )
            if ( TypeSystem.NumStep[i] != S2.TypeSystem.NumStep[i] ) return 11;

         ne = S2.QuantityElem;
         if ( QuantityElem < ne ) ne = QuantityElem;

         nu = S2.QuantityNode;
         if ( QuantityNode < nu ) nu = QuantityNode;

         YesNode = (BYTE*)Memory(nu+1);

         KD1 = (BYTE*)Memory(ne+1);
	      BoundList(_List[0],ne,KD1);
         KD2 = (BYTE*)Memory(ne+1);
	      BoundList(S2._List[0],ne,KD2);

         for ( i=0; i<ne; i++ ) {
            F1 = &pFormat[i];
            F2 = &S2.pFormat[i];
            if ( F2->TypeElem == 200 || BitRead((BYTE*)&F2->Flags,7) ) continue;
            if ( F1->TypeElem != F2->TypeElem ) {  iRet = 14;  goto _10;  }
            if ( F1->QuantityNode != F2->QuantityNode ) {  iRet = 15;  goto _10;  }
            for ( j=0; j<F1->QuantityNode; j++ ) {
               if ( F1->pNode[j] != F2->pNode[j] ) {  iRet = 16;  goto _10;  }
               YesNode[F1->pNode[j]] = 1;
               }
            n = F1->TypeElem % 100;
            if ( n && n <= 10 && KD1[i] != KD2[i] ) {  iRet = 18;  goto _10;  }
            }

         if ( Level == 0 ) goto _10;

         for ( i=0,MazSize=0; i<nu; i++ ) {
            pC1 = &Coord[i];
            r = fabs(pC1->x) + fabs(pC1->y) + fabs(pC1->z);
            if ( r > MazSize ) MazSize = r;
            }

         for ( i=0; i<nu; i++ ) {
            if ( YesNode[i+1] == 0 ) continue;
            pC1 = &Coord[i];
            pC2 = &S2.Coord[i];
            r = fabs(pC1->x-pC2->x) + fabs(pC1->y-pC2->y) + fabs(pC1->z-pC2->z);
            if ( r > 1e-4*MazSize ) {  iRet = 17;  goto _10;  }
            }

_10:     MemoryFree(YesNode);
         return iRet;
}