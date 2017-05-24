#include "stdafx.h"
#include "classwin.h"
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

EXPORT int    BASE_CLASS::AddObject( int Qnt )
{
       LPSTR pS;
       int n = Quantity + 1;
	    if ( Quantity + Qnt > QuantityAlloc ) {
          QuantityAlloc += Qnt + Delta;
          pS = (LPSTR)Memory(QuantityAlloc,LenStr);
          CopyMemory(pS,Objects,Quantity*LenStr);
	       MemoryFree(Objects);
	       Objects = pS;   }
       Quantity += Qnt;
       return n;
}

EXPORT int    BASE_CLASS::AddObject( void *Data, LPSTR Text, ... )
{      int n, k;
       void *pB;
       OBJECT  *pWork;
       BASE_DATA  *pA;
	    va_list arg_ptr;

       AddObject(1);
       pWork = GetObject(Quantity);
       if ( Data ) memcpy(GetObjectData(Quantity),Data,LenObjectDataWrite);
       SetText(Quantity,Text);

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
       return Quantity;
}

EXPORT void   BASE_CLASS::AddObject( BASE_CLASS *Input, int NumComponent, int QuantityNum, int *NewNumber )
{
       int i, n;
	   OBJECT *pOB;
       memcpy(Common,Input->GetCommon(),LenCommon);
       for ( i=1; i<=Input->Quantity; i++ ) {
         pOB = Input->GetObject(i); 
         n = AddObject(pOB);
         if ( NewNumber ) NewNumber[i-1] = n;  }
}

EXPORT int    BASE_CLASS::AddObject( void *Inp, int NumComponent, int QuantityNum, int *NewNumber )
{
       int n, j, *pI;
       BASE_DATA  *pA;
       OBJECT *Input = (OBJECT*)Inp;
       AddObject(1);
       memcpy(GetObjectData(Quantity),(LPSTR)Inp+PosData,LenObjectData);
       if ( Input->Text ) SetText(Quantity,Input->Text);

       for ( n=1; n<=QuantityObject; n++ ) {
          ChangeComponent(Quantity,n,Input->BaseData[n-1].Quantity,Input->BaseData[n-1].Data,0);
          if ( NewNumber ) {
             pA = GetBaseData(Quantity,NumComponent);
             pI = (int*)pA->Data;
             for ( j=0; j<pA->Quantity; j++ )
                if ( pI[j] <= QuantityNum ) pI[j] = NewNumber[pI[j]];
             }   }
       return Quantity;
}



