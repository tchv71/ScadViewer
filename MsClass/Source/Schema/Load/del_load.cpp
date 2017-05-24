#include <stdafx.h>
#include "schema.h"

EXPORT void SCHEMA::DeleteZeroLoad()
{
     for ( int i=_LoadList.Quantity; i; i-- )
        if ( _LoadList.Inf[i-1].Load.QuantityForceValue == 0 )
           DeleteLoadInList(i);
}

EXPORT void SCHEMA::DeleteLoadInList(int Num)
{
     LOAD_INF *pLI;
     FORCE_GROUP *pFG;
     FORCE_LIST  *pFL;
     int i, j, k;
     DATA_LOAD *DL;

     if ( Num == 0 || Num > _LoadList.Quantity ) return;
     DeleteLoad(Num);

     for ( i=0; i<_LoadList.Quantity; i++ ) {
        if ( i == Num - 1 ) continue;
        pLI = &_LoadList.Inf[i];   DL = &pLI->Load;    pFG = &DL->ForceLoad;
        for ( j=0; j<pFG->QuantityForceList; j++ ) {
           pFL = &pFG->ForceList[j];
           k = pFL->NumNodeFe;
           if ( k == Num ) pFL->NumNodeFe = 0;
           if ( k > Num )  pFL->NumNodeFe--;
           }
        DL->Compress(*pFG,_LoadList.Quantity-1,NULL);
        if ( i >= Num  ) {
           memcpy(pLI-1,pLI,sizeof(LOAD_INF));
           ZeroMemory(pLI,sizeof(LOAD_INF));
           }
        }

     ZeroMemory(AddrDoc(8),sizeof(DOCUMENT));
     ZeroMemory(AddrDoc(36),sizeof(DOCUMENT));
     ZeroMemory(AddrDoc(37),sizeof(DOCUMENT));

    _LoadList.Quantity--;
    _LoadList.Modify = 1;

}