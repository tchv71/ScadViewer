#include "stdafx.h"
#include <ClassWin.h>
#include "BaseClass.hpp"
#include "ObjectList.hpp"
#include "ObjectString.hpp"

void    EXPORT BASE_CLASS::Destroy()
{
       Delete();
       if ( Common ) MemoryFree(Common);  Common = NULL;
}


void    EXPORT BASE_CLASS::DeleteType( BYTE Type, int PosType )
{
       BYTE *pB;
       int i;
       if ( PosType < 0 ) return;
       for ( i=Quantity; i; i-- ) {
          pB = (BYTE*)( (LPSTR)GetObjectData(i) + PosType );
          if ( *pB != Type  ) continue;
          Delete(i);  }
}

void    EXPORT BASE_CLASS:: Delete()
{
       int i;
       if ( Common ) ZeroMemory(Common,LenCommonWrite);
       if ( Objects ) {
          for ( i=Quantity; i; ) if ( i ) Delete(i--);
          MemoryFree(Objects);
          Objects = NULL;    }
       Quantity = QuantityAlloc = 0;
}

void    EXPORT BASE_CLASS::Delete( int Num )
{
       if ( Num < 1 || Num > Quantity ) return;
       Clear(Num);
       for ( int n=Num; n<Quantity; n++ ) memcpy(GetObject(n),GetObject(n+1),LenStr);
       ZeroMemory(GetObject(Quantity),LenStr);
       Quantity--;
}


