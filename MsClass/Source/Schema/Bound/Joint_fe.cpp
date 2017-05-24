#include <stdafx.h>
#include <schema.h>

EXPORT int SCHEMA::JointElem(WORD NumElem,WORD &Mask1, WORD &Mask2)
{
	   WORD i, j;
	   BOUND_LIST *pWork;

	   Mask1 = Mask2 = 0;

	   for ( i=0; i<_Joint.GetQuantityBound(); i++ ) {
	      pWork = (BOUND_LIST*)&_Joint.pBound[i];
	      for ( j=0; j<pWork->Quantity; j++ ) if ( pWork->List[j] == NumElem ) {
                 if ( pWork->Type == 1 ) Mask1 = pWork->Mask;
		 if ( pWork->Type == 2 ) Mask2 = pWork->Mask;
		 }   }

	   if ( Mask1 || Mask2 ) return 1;
           return 0;
}