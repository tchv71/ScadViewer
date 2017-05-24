#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA:: InsertInFormat(INSERT &Ins)
{
       WORD i, k, n;
       FORMAT *pFrmt;

       for ( i=0; i<QuantityElem; i++ ) {
	  pFrmt = (FORMAT*)&pFormat[i];
	  if ( &Ins == &_Insert ) pFrmt->TypeInsert = 0;
	  else if ( &Ins == &_Corner ) pFrmt->TypeCorner = 0;
	       else pFrmt->TypeCornerNapr = 0;
	  }

       Ins.Read();
       for ( i=0; i<Ins.QuantityInsert; i++ )
	  for ( k=0; k<Ins.pInsert[i].Quantity; k++ ) {
	      n = Ins.pInsert[i].List[k];
	      if ( n && n <= QuantityElem ) {
		 pFrmt = (FORMAT*)&pFormat[n-1];
		 if ( &Ins == &_Insert ) pFrmt->TypeInsert = i + 1;
		 else if ( &Ins == &_Corner ) pFrmt->TypeCorner = i + 1;
		 else pFrmt->TypeCornerNapr = i + 1;
                   }
	      }

      DeleteLookBody();
}