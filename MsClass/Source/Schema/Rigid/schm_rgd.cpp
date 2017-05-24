#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA:: RigidInFormat()
{
       int i, k, n;
       WORD l;
       RIGID_LIST *pRgdLst;
       BYTE Control, TypeRigid;
       STRING_PROFILE *pSP;
       INFRGD *infrgd;

       infrgd = (INFRGD*)Memory(100,sizeof(INFRGD));

       _Profile->SetUnit(Units[0],Units[1],Units[2]);

       for ( i=0; i<QuantityElem; i++ ) pFormat[i].TypeRigid = 0;
       _Rigid.Read();

       for ( i=0; i<_Rigid.QuantityRigid; i++ ) {

	       pRgdLst = (RIGID_LIST *)&_Rigid.pRigid[i];
	       pRgdLst->Icon = 0xFF;
	       pRgdLst->Alfa = 0;
          RigidType(pRgdLst->QuantityRgd,pRgdLst->pRgd,infrgd,l,TypeRigid);
          if ( TypeRigid > 1 ) pRgdLst->Type = TypeRigid;

          if ( pRgdLst->Type == 1 ) {
             pSP = _Profile->GetInform(pRgdLst->pRgd,pRgdLst->QuantityRgd,Control);
             if ( pSP ) {
                pRgdLst->Icon = pSP->Group;
                pRgdLst->Alfa = pSP->Alfa;   }
             }

	  for ( k=0; k<pRgdLst->Quantity; k++ ) {
	     n = pRgdLst->List[k];
	     if ( n && n <= QuantityElem )
	        pFormat[n-1].TypeRigid = pRgdLst->Num;
             }

          }

       MemoryFree(infrgd);
}