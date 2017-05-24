#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

void EXPORT BASE_CLASS::ChangeObject( int Num, void *Data, LPSTR Text, ... )
{
       int n, k;
       void *pB;
       OBJECT  *pWork;
       BASE_DATA  *pA;
	    va_list arg_ptr;

       if ( Num < 1 || Num > Quantity ) return;
       Clear(Num);
       pWork = GetObject(Num);
       if ( Data ) memcpy(GetObjectData(Num),Data,LenObjectDataWrite);
       SetText(Num,Text);

       va_start(arg_ptr,Text);
       for ( n=0; n<QuantityObject; n++ ) {
          pA = &pWork->BaseData[n];
          k = va_arg(arg_ptr,int);
          pB = va_arg(arg_ptr,void*);
          if ( k == 0 ) break;
          if ( pA->Data ) MemoryFree(pA->Data);
          pA->Quantity = k;
          pA->Data = Memory(k*LenData[n]);
          memcpy(pA->Data,pB,k*LenData[n]);
          }
       va_end(arg_ptr);
       SetModify();
}

void EXPORT BASE_CLASS::ChangeData( int Num, void *Data  )
{
       if ( Num < 1 || Num > Quantity ) return;
       memcpy(GetObjectData(Num),Data,LenObjectDataWrite);
       Modify = 1;
}

void EXPORT BASE_CLASS::ChangeComponent( int Num, int NumComponent, int QuantityObjectComp, void *Comp, int Type )
{
       OBJECT  *pWork;
       BASE_DATA  *pA;
       LPSTR pS;
       int Len;

       if ( Num < 1 || Num > Quantity ) return;
       if ( NumComponent < 1 || NumComponent > QuantityObject ) return;

       pWork = GetObject(Num);
       Len = LenData[--NumComponent];
       pA = &pWork->BaseData[NumComponent];
       if ( Type == 0 ) pA->Quantity = 0;
       pS =  (LPSTR)Memory(pA->Quantity+QuantityObjectComp,Len);
       if ( pA->Quantity ) memcpy(pS,pA->Data,pA->Quantity*Len);
       memcpy(&pS[pA->Quantity*Len],Comp,QuantityObjectComp*Len);
       if ( pA->Data ) MemoryFree(pA->Data);
       pA->Quantity = pA->Quantity + QuantityObjectComp;
       pA->Data = (void*)pS;
       Modify = 1;
}

